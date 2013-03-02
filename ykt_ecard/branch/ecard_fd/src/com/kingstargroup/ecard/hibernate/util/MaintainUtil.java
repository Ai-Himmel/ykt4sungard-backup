package com.kingstargroup.ecard.hibernate.util;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.mail.AuthenticationFailedException;

import org.apache.commons.mail.SimpleEmail;
import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.equipment.Maintain;
import com.kingstargroup.ecard.hibernate.equipment.MaintainPersistence;
import com.kingstargroup.ecard.hibernate.equipment.MaintainType;
import com.kingstargroup.ecard.hibernate.equipment.MaintainTypePersistence;
import com.kingstargroup.ecard.hibernate.web.DictionaryPersistence;
import com.kingstargroup.ecard.hibernate.web.WebDictionary;
import com.kingstargroup.ecard.hibernate.web.WebDictionaryKey;
import com.kingstargroup.ecard.util.DateFormatUtil;
import com.kingstargroup.ecard.util.EcardConstants;
public class MaintainUtil extends BasicUtil {
	
	
	public static void sendEmail(String applyInfo)throws PortalException {
		try{
		
	      List list =	WebDictionaryUtil.getDictionaryByDicNo("008");
	  	WebDictionary  webservice= WebDictionaryUtil.getDictionary("003","01");
		String service="";
		if(webservice!=null){
			service=webservice.getDicCaption();
		}
		
		WebDictionary  websendEmail= WebDictionaryUtil.getDictionary("004","01");
		String sendEmail="";
		if(websendEmail!=null){
			sendEmail=websendEmail.getDicCaption();
		}
		
		WebDictionary  webusername= WebDictionaryUtil.getDictionary("005","01");
		String username="";
		if(webusername!=null){
			username=webusername.getDicCaption();
		}
		
		WebDictionary  webpassword= WebDictionaryUtil.getDictionary("006","01");
		String password ="";
		if(webpassword!=null){
			password=webpassword.getDicCaption();
		}
		
		WebDictionary  webtitle = WebDictionaryUtil.getDictionary("007","01");
		String title ="";
		if(webtitle!=null){
			title=webtitle.getDicCaption();
		}
	      if(list != null){
		   for(int i=0;i<list.size();i++){
			   WebDictionary dic = (WebDictionary)list.get(i);
			   if(dic.getDicCaption()!=null && !dic.getDicCaption().equals("")){
			     SimpleEmail email = new SimpleEmail();   
			     email.setHostName(service);//邮件服务器   
			     email.setFrom(sendEmail, EcardConstants.MAINTAIN);//发信者   
			     email.addTo(dic.getDicCaption());//收信者  
			     email.setAuthentication(username, password);//smtp认证的用户名和密码   
			     email.setSubject(title);//标题     
			     email.setCharset("gb2312");//编码格式 
			     email.setMsg(applyInfo);//内容   
			     
			     email.send();//发送   
			   }
	        }
	      }
	  }catch(AuthenticationFailedException e){      
		    System.out.println("发送邮件失败");
            e.printStackTrace();    
		}
     catch(DBSystemException e) {			
		throw e;
	}catch(Exception mex) {
		mex.printStackTrace();
	}finally {
		closeSession();
	}
		
	}
	
	public static void updateMaintain(String id ,String applyPeopleAnswer)throws PortalException {
		MaintainPersistence persistence = (MaintainPersistence) getPersistence(MaintainPersistence.class.getName());
		Maintain  maintain = getMaintainById(id);
		Transaction t = beginTransaction();		
		try{
			maintain.setApplyPeopleAnswer(applyPeopleAnswer);
			persistence.saveOrUpdate(maintain);
		    t.commit();
	   } catch (DBSystemException e) {			
		throw e;
	   } finally {
		closeSession();
     	}
	}
		

	
	
	//统计信息
	public static List  adminTotal(String beginDate,String endDate)throws PortalException {
		MaintainPersistence persistence = (MaintainPersistence) getPersistence(MaintainPersistence.class.getName());
		try {
			return persistence.adminTotal(beginDate,endDate);
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}
	
	//管理员按条件查询信息
	public static ResultPage adminQry(String userId,String status,String  type,String appBeginDate,String appEndDate,String asrBeginDate,String asrEndDate,int page,int size)throws PortalException {
		MaintainPersistence persistence = (MaintainPersistence) getPersistence(MaintainPersistence.class.getName());
		try {
			return persistence.adminQry(userId,status,type,appBeginDate,appEndDate,asrBeginDate,asrEndDate,page,size);
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}
	//管理员回答维修信息
	public static boolean  answerMaintainInfo(String id,String userId,String answerInfo,String[] MaintainType,String operator,
			                                  String accidentExplain,String  operatorDepend ,String operatorStep,
			                                  String applyPeople,String applyEmail)throws PortalException {
		MaintainPersistence persistence = (MaintainPersistence) getPersistence(MaintainPersistence.class.getName());
		MaintainTypePersistence  typePersistence = (MaintainTypePersistence) getPersistence(MaintainTypePersistence.class.getName());
		boolean success = false;
		Maintain  maintain = getMaintainById(id);
		Transaction t = beginTransaction();		
		try{
			maintain.setAnswerInfo(answerInfo);
			maintain.setAnswerPeople(userId);
			maintain.setAnswerTime(DateFormatUtil.getNowDate());
			maintain.setStatus("1");
			maintain.setOperator(operator);
			maintain.setOperatorDepend(operatorDepend);
			maintain.setOperatorStep(operatorStep);
			maintain.setAccidentExplain(accidentExplain);
			persistence.saveOrUpdate(maintain);
			//删除原先的维修类型
			List list = typePersistence.getMaintainTypeByMaintainId(new Integer(id));
			if(list != null){
				for(int i=0;i<list.size();i++){
					typePersistence.deleteMaintainTypeByMaintain((MaintainType)list.get(i));
				}
			}
			
			//插入新的维修类型
			for(int i=0;i<MaintainType.length;i++){
				MaintainType  type = new  MaintainType();
				type.setMaintainId(maintain);
				type.setDicValue(MaintainType[i]);
				typePersistence.save(type);
			}
			t.commit();
			if(applyEmail!=null && !applyEmail.equals("")){
			 sendApplyPeopleEmail( answerInfo, applyPeople, applyEmail);
		    }
			success=true;
		}catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return success;
	}
	private static void sendApplyPeopleEmail(String answerInfo,String  applyPeople,String applyEmail) throws PortalException {
		try{
		
		
		WebDictionary  webservice= WebDictionaryUtil.getDictionary("003","01");
		String service="";
		if(webservice!=null){
			service=webservice.getDicCaption();
		}
		WebDictionary  websendEmail= WebDictionaryUtil.getDictionary("004","01");
		String sendEmail="";
		if(websendEmail!=null){
			sendEmail=websendEmail.getDicCaption();
		}
		WebDictionary  webusername= WebDictionaryUtil.getDictionary("005","01");
		String username="";
		if(webusername!=null){
			username=webusername.getDicCaption();
		}
		
		WebDictionary  webpassword= WebDictionaryUtil.getDictionary("006","01");
		String password ="";
		if(webpassword!=null){
			password=webpassword.getDicCaption();
		}
		     String title = "复旦设备报修回复";
		     SimpleEmail email = new SimpleEmail();   
		     email.setHostName(service);//邮件服务器   
		     email.setFrom(sendEmail, EcardConstants.MAINTAIN);//发信者   
		     email.addTo(applyEmail);//收信者  
		     email.setAuthentication(username, password);//smtp认证的用户名和密码   
		     email.setSubject(title);//标题   
		     email.setCharset("gb2312");//编码格式 
		     email.setMsg(answerInfo);//内容   
		     email.send();//发送   
		          
		}catch(AuthenticationFailedException e){      
		    System.out.println("发送邮件失败");
            e.printStackTrace();    
           
		}
        catch(DBSystemException e) {
		throw e;
		
	   }catch(Exception mex) {
		mex.printStackTrace();
		
	   }finally {
		closeSession();
	  }
	}
	
	//通过报修信息取得报修的类别
	public static List  getDictionaryByMaintain(Integer  maintainId)throws PortalException {
		MaintainTypePersistence  mtPersistence = (MaintainTypePersistence) getPersistence(MaintainTypePersistence.class.getName());
		List dicList = new ArrayList();
		List list = mtPersistence.getMaintainTypeByMaintainId(maintainId);
		Iterator it = list.iterator();
	    WebDictionary dict = null;
		while (it.hasNext()){
			MaintainType mt =   (MaintainType)it.next();
			DictionaryPersistence dicPersistence = (DictionaryPersistence) getPersistence(DictionaryPersistence.class.getName());
			WebDictionaryKey key = new WebDictionaryKey();
			key.setDicNo("001");
			key.setDicValue(mt.getDicValue());
			dict = dicPersistence.getDictionaryByPK(key);
			dicList.add(dict);
		}
		return dicList;
	}
	
	//取得报修信息
	public static Maintain getMaintainById(String id)throws PortalException  {
		MaintainPersistence persistence = (MaintainPersistence) getPersistence(MaintainPersistence.class.getName());
		Maintain  maintain = null;
		Transaction t = beginTransaction();		
		try {
			maintain = persistence.getMaintainById(id);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return maintain;
	}
	
	
/*	public static void  addMaintain(String applyTitle,String applyInfo,String[] MaintainType,String applyPeople)throws PortalException {
		
		MaintainTypePersistence typePersistence = (MaintainTypePersistence) getPersistence(MaintainTypePersistence.class.getName());
		try {
			 Transaction t = beginTransaction();
			 Maintain   info = new Maintain();
			 info.setApplyTitle(applyTitle);
			 info.setApplyPeople(applyPeople);
			 info.setApplyTime(DateFormatUtil.getNowDate());
			 info.setApplyInfo(applyInfo);
			 
			 for(int i=0;i<MaintainType.length;i++){
				 MaintainType mType = new MaintainType();
				 mType.setDicValue(MaintainType[i]);
				 mType.setMaintainId(info);
				 typePersistence.addMaintainType(mType);
			 }
			 
			 t.commit();
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}*/
	//添加报修信息
	public static void  addMaintain(String applyTitle,String applyInfo,String applyPeople,String contact,String school,String accidentDate,String  accidentTime,String inputPeople ,String applyEmail)throws PortalException {
		
		MaintainPersistence Persistence = (MaintainPersistence)getPersistence(MaintainPersistence.class.getName());
		try {
			 Transaction t = beginTransaction();
			 Maintain   info = new Maintain();
			 info.setApplyTitle(applyTitle);
			 info.setApplyPeople(applyPeople);
			 info.setApplyTime(DateFormatUtil.getNowDate());
			 info.setApplyInfo(applyInfo);
			 info.setContactMethod(contact);
			 info.setAccidentDate(accidentDate);
			 info.setAccidentTime(accidentTime);
			 info.setSchoolArea(school);
			 info.setStatus("0");
			 info.setInputPeople(inputPeople);
			 info.setApplyEmail(applyEmail);
			 Persistence.save(info);
			 t.commit();
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}
	
	//取得所有的维修类型
	public static List   getMaintainType(String dicNo)throws PortalException{
		MaintainPersistence persistence = (MaintainPersistence)getPersistence(MaintainPersistence.class.getName());
		try{
			return persistence.getMainType(dicNo);
		}catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}
	
	
	
	public static ResultPage list(String title,String userId,String status,int page ,int size) throws PortalException {
		return search(title,userId,status,page, size);
	}

	/**
	 * Description:根据用户提供的查询项查询出结果集
	 * @param title 查询标题
	 * @param content 查询内容
	 * @param infoType 查询信息类型
	 * @param page 需要查询的页
	 * @throws PortalException
	 * @return
	 * Modify History:
	 */
	public static ResultPage search(String title,String userId,String status, int page) throws PortalException {
		return search(title,userId ,status ,page, EcardConstants.LIST_MORE_SIZE);
	}
	
	/**
	 * Description:根据用户提供的查询项查询出结果集
	 * @param title 查询标题
	 * @param content 查询内容
	 * @param infoType 查询信息类型
	 * @param page 需要查询的页
	 * @param size 指定一页返回多少记录
	 * @throws PortalException
	 * @return
	 * Modify History:
	 */

	
	public static ResultPage search(String title,String userId,String status,int page, int size) throws PortalException {
		MaintainPersistence persistence = (MaintainPersistence) getPersistence(MaintainPersistence.class.getName());
		try {
			return persistence.search(title,userId,status,page, size);
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}

}
