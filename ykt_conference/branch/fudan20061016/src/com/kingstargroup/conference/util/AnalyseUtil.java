/**
 * 
 */
package com.kingstargroup.conference.util;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

import org.hibernate.HibernateException;

import com.kingstargroup.conference.dao.AnalyseDAO;
import com.kingstargroup.conference.dao.DictionaryDAO;
import com.kingstargroup.conference.hibernate.form.TCifPhoto;
import com.kingstargroup.conference.hibernate.form.TConference;

public class AnalyseUtil extends BasicUtil {
	
	public static List getAllSignStatus() {
		AnalyseDAO dao = AnalyseDAO.getInstance();
		try {
			return dao.getAllSignStatus();
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}

	/* 
	 * 取得已发生会议
	 */
	public static List getAllConfenece() {
		AnalyseDAO dao = AnalyseDAO.getInstance();
		try {
			return dao.getAllConference();
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	public static boolean  isConferenceOver(String confid){
		try{
			TConference  conference= AnalyseUtil.getConference(new Integer(confid));
			int endDate = Integer.parseInt(conference.getConEnddate());
			int endTime = Integer.parseInt(conference.getConEndtime());
			SimpleDateFormat df = new SimpleDateFormat("yyyyMMdd-HHmm");
			String current=df.format(new Date());
			int currentDate =Integer.parseInt(current.substring(0,current.lastIndexOf("-")));
			int  currendTime = Integer.parseInt(current.substring(current.indexOf("-")+1,current.length()));
			if((endDate<currentDate)||(endDate==currentDate && endTime<currendTime)){
				return true;
			}else{
				return false;
			}
		}catch (HibernateException he) {
			he.printStackTrace();
			return false;
		} finally {
			closeSession();
		}
	}
	/*
	 * 按主键取得会议信息
	 */ 
	public static TConference getConference(Integer conId) {
		AnalyseDAO dao = AnalyseDAO.getInstance();		
		try {
			return (TConference) dao.findByPrimaryKey(TConference.class, conId);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	/*
	 * 按主键取得会议信息
	 */
	public static List getConference(Integer conId, String conType, String begindate, String enddate) {
		AnalyseDAO dao = AnalyseDAO.getInstance();		
		try {			
			return dao.getConference(conId, conType, begindate, enddate);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	/*
	 * 按主键取得会议信息
	 */
	public static List getConferenceBySign(Integer conId, String duty, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();		
		try {			
			return dao.getConferenceBySign(conId, duty, sign);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/* 
	 * 按主键取得会议统计人数
	 */
	public static ArrayList getAtteCount(Integer conId) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		ArrayList list = new ArrayList();
		int count = 0;
		try {
			/* 应出席 */
			count = dao.getAtteCountById(conId, null);
			list.add(0,new Integer(count));
			
			/* 实出席 */
			count = dao.getAtteCountById(conId, "11");
			count += dao.getAtteCountById(conId, "12");
			count += dao.getAtteCountById(conId, "13");
			count += dao.getAtteCountById(conId, "21");
			count += dao.getAtteCountById(conId, "22");
			count += dao.getAtteCountById(conId, "23");
			list.add(1,new Integer(count));
		
			/* 迟到 */
			count = dao.getAtteCountById(conId, "21");
			count += dao.getAtteCountById(conId, "22");
			count += dao.getAtteCountById(conId, "23");
			list.add(2,new Integer(count));
			
			/* 代签 */
			count = dao.getAtteCountById(conId, "13");
			count += dao.getAtteCountById(conId, "23");
			list.add(3,new Integer(count));
			
			/* 请假 */
			count = dao.getAtteCountById(conId, "30");
			list.add(4,new Integer(count));		
		
			return list;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}		
	/* 
	 * 按会议类型取得会议统计人数
	 */
	public static ArrayList getAtteCount(Integer conId, String conType, String begindate, String enddate) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		ArrayList list = new ArrayList();
		int count = 0;
		try {			
			/* 应出席 */
			count = dao.getAtteCountByType(conId, conType, null, begindate, enddate);
			list.add(0,new Integer(count));
			
			/* 实出席 */
			count = dao.getAtteCountByType(conId, conType, "11", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "12", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "13", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "21", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "22", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "23", begindate, enddate);
			list.add(1,new Integer(count));					
			
			/* 请假 */
			count = dao.getAtteCountByType(conId, conType, "30", begindate, enddate);
			list.add(2,new Integer(count));
			
			/* 缺席 */
			count = dao.getAtteCountByType(conId, conType, "00", begindate, enddate);
			list.add(3,new Integer(count));
			
			
			/*
			正常签到（持卡签到）
			 */
			count = dao.getAtteCountByType(conId, conType, "11", begindate, enddate);
			list.add(4,new Integer(count));
			/*
			无卡签到
			 */
			count = dao.getAtteCountByType(conId, conType, "12", begindate, enddate);
			list.add(5,new Integer(count));
			/*
			代替签到
			 */
			count = dao.getAtteCountByType(conId, conType, "13", begindate, enddate);
			list.add(6,new Integer(count));
			/*
			持卡签到（迟到）
			 */
			count = dao.getAtteCountByType(conId, conType, "21", begindate, enddate);
			list.add(7,new Integer(count));
			/*  
			无卡签到（迟到）
			 */
			count = dao.getAtteCountByType(conId, conType, "22", begindate, enddate);
			list.add(8,new Integer(count));
			/*
			代替签到（迟到）  
			 */
			count = dao.getAtteCountByType(conId, conType, "23", begindate, enddate);
			list.add(9,new Integer(count));
			
			/* 迟到 */
			count = dao.getAtteCountByType(conId, conType, "21", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "22", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "23", begindate, enddate);
			list.add(10,new Integer(count));
			/*其他签到人员（正常）*/
			count = dao.getAtteCountByNoInform(conId,"11");
			list.add(11,new Integer(count));
			/*其他签到人员（迟到）*/
			count = dao.getAtteCountByNoInform(conId,"21");
			list.add(12,new Integer(count));
			return list;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	/* 
	 * 取得会议统计人数，与会者签到专用
	 */
	public static ArrayList getAtteCount(Integer conId, String duty, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		ArrayList list = new ArrayList();
		int count = 0;
		try {	
			/* 应出席 */
			count = dao.getAtteCountBySign(conId, duty, null);						
			list.add(0,new Integer(count));
			count = 0;
			
			/* 实出席 */
			count = dao.getAtteCountBySign(conId, duty, "11");
			count += dao.getAtteCountBySign(conId, duty, "12");
			count += dao.getAtteCountBySign(conId, duty, "13");
			count += dao.getAtteCountBySign(conId, duty, "21");
			count += dao.getAtteCountBySign(conId, duty, "22");
			count += dao.getAtteCountBySign(conId, duty, "23");
			list.add(1,new Integer(count));
			count = 0;
			
			/* 迟到 */
			count = dao.getAtteCountBySign(conId, duty, "21");
			count += dao.getAtteCountBySign(conId, duty, "22");
			count += dao.getAtteCountBySign(conId, duty, "23");
			list.add(2,new Integer(count));
			count = 0;
			
			/* 代签 */
			count = dao.getAtteCountBySign(conId, duty, "13");
			count += dao.getAtteCountBySign(conId, duty, "23");
			list.add(3,new Integer(count));
			count = 0;
			
			/* 请假 */
			count = dao.getAtteCountBySign(conId, duty, "30");
			list.add(4,new Integer(count));
			count = 0;
			
			/* 选中状态 */
			count = dao.getAtteCountBySign(conId, duty, sign);
			list.add(5,new Integer(count));
			
			return list;
			
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	/* 
	 * 取得与会人员列表
	 */
	public static List getAttendeeList(Integer conId, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		DictionaryDAO dictdao = DictionaryDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getAttendeeList(conId, sign);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("cutName",convent(objects[0]));
				map.put("deptName", convent(objects[1]));
				map.put("dutyName", convent(objects[2]));
				map.put("tel", convent(objects[3]));				
				map.put("sendSign", eqwith(objects[4]));
				map.put("informSign", eqwith(objects[5]));
				map.put("attendSign",dictdao.getAttendeeStatus(convent(objects[6])));
				map.put("attendTime",objects[7]);
				result.add(map);
			}
			return result;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	/**
		* File name: AnalyseUtil.java<br>
		* Description: <br>
		* Return: @param conId
		* Return: @param sign
		* Return: @param attendeetime
		* Return: @return<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-5-15  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public static List getPicAttendeeList(String conId, String attendeetime,String flag) {
		AnalyseDAO dao = AnalyseDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getPicAttendeeList(conId, attendeetime,flag);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				String dutyName = convent(objects[3]);
				if(i+1<l){
					Object[] objects1 = (Object[]) list.get(i+1);
					if(convent(objects[0]).equals(convent(objects1[0]))){
						dutyName += ", "+convent(objects1[3]);
						i++;
						for(int j=i+1;j<l;j++){
							objects1 = (Object[]) list.get(j);
							if(convent(objects[0]).equals(convent(objects1[0]))){
								dutyName += ","+convent(objects1[3]);
								i++;
								continue;
							}else{
								break;
							}
						}						
					}
				}
				
				
				HashMap map = new HashMap();
				map.put("custId",convent(objects[0]));
				map.put("cutName",convent(objects[1]));
				map.put("deptName", convent(objects[2]));
				map.put("dutyName", dutyName);
				map.put("stuempNo", convent(objects[4]));				
				map.put("attendTime",convent(objects[5]));
				result.add(map);
			}
			return result;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	/**
		* File name: AnalyseUtil.java<br>
		* Description: <br>
		* Return: @param conId
		* Return: @param attendeetime
		* Return: @param flag
		* Return: @return<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-5-21  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public static List getPicAttendeeListTest(String conId, String attendeetime,String flag) {
		AnalyseDAO dao = AnalyseDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getPicAttendeeListTest(conId, attendeetime,flag);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("custId",convent(objects[0]));			
				map.put("attendTime",convent(objects[1]));
				result.add(map);
			}
			return result;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	
	public static List getTTAttendeeList(Integer conId, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		DictionaryDAO dictdao = DictionaryDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getTTAttendeeList(conId, sign);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				
				String dutyName = convent(objects[2]);
				if(i+1<l){
					Object[] objects1 = (Object[]) list.get(i+1);
					if(convent(objects[0]).equals(convent(objects1[0]))){
						dutyName += ", "+convent(objects1[2]);
						i++;
						for(int j=i+1;j<l;j++){
							objects1 = (Object[]) list.get(j);
							if(convent(objects[0]).equals(convent(objects1[0]))){
								dutyName += ","+convent(objects1[2]);
								i++;
								continue;
							}else{
								break;
							}
						}						
					}
				}
				
				HashMap map = new HashMap();
				map.put("cutName",convent(objects[0]));
				map.put("deptName", convent(objects[1]));
				map.put("dutyName", dutyName);
				map.put("tel", convent(objects[3]));		
				map.put("sendSign", eqwith(objects[4]));
				map.put("informSign", eqwith(objects[5]));
				map.put("attendSign",dictdao.getAttendeeStatus(convent(objects[6])));
				map.put("attendTime",objects[7]);
				result.add(map);
			}
			return result;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	/* 
	 * 取得与会人员列表
	 */
	public static List getAttendeeList(Integer conId, String duty, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		DictionaryDAO dictdao = DictionaryDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getAttendeeList(conId, sign, duty);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();				
				map.put("cutName",convent(objects[0]));
				map.put("deptName", convent(objects[1]));
				map.put("dutyName", convent(objects[2]));
				map.put("tel", convent(objects[3]));				
				map.put("sendSign", eqwith(objects[4]));
				map.put("informSign", eqwith(objects[5]));
				map.put("attendSign",dictdao.getAttendeeStatus(convent(objects[6])));
				map.put("attendTime",objects[7]);
				result.add(map);
			}
			return result;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	public static TCifPhoto getCifPhoto(Integer custId){
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		try {
			TCifPhoto photo = dao.getCifPhoto(custId);
			return photo;
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			return null;
		}
	}
	
	public static TCifPhoto getfudanCifPhoto(String stuempNo){
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		try {
			TCifPhoto photo = dao.getfudanCifPhoto(stuempNo);
			return photo;
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			return null;
		}
	}

	/* 
	 * 取得所有已发生会议类型
	 */
	public static List getAllConfType(){
		AnalyseDAO dao = AnalyseDAO.getInstance();
		List typeList = new ArrayList();
		try {
			typeList = dao.getConfType();
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return typeList;
	}

	private static String convent (Object ss){
		if (null==ss){
			return "";
		}else{
			return ss.toString();
		}
	}
	
	/* 
	 * 为会议人员列表设计
	 * 判断是否下发通知
	 */
	private static String eqwith(Object ss) {
		String yes = "是";
		String no = "否";
		if (null==ss){
			return "";
		}else{
			int temp = Integer.parseInt(ss.toString());
			if(temp==0) {
				return no;
			} else if(temp==1) {			
				return yes;
			}
			return "";
		}
	}

		

	
}
