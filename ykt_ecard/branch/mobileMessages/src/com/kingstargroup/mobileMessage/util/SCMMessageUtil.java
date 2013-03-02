package com.kingstargroup.mobileMessage.util;

import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;

import com.jasson.im.api.APIClient;
import com.jasson.im.api.MOItem;
import com.kingstargroup.mobileMessage.dao.RecMessageDao;
import com.kingstargroup.mobileMessage.dao.SendMessageDao;
import com.kingstargroup.mobileMessage.hibernate.RCmMessages;
import com.kingstargroup.mobileMessage.hibernate.SCmMessages;

public  class SCMMessageUtil extends BasicUtil {
	
	private static final String  srcID=KSConfiguration.getInstance().getProperty("srcID");
	private static final String  imIP=KSConfiguration.getInstance().getProperty("imIP");
	private static final String  loginName=KSConfiguration.getInstance().getProperty("loginName");
	private static final String  loginPWD=KSConfiguration.getInstance().getProperty("loginPWD");
	private static final String  apiCode=KSConfiguration.getInstance().getProperty("apiCode");
	private static final String  dbName=KSConfiguration.getInstance().getProperty("dbName");
	private static APIClient handler = new APIClient();
	private static long   smId = 1;
	
   public  synchronized static int  init(){
	   
	   int connectRe = handler.init(imIP,loginName,loginPWD,apiCode, dbName);
	   return connectRe;
	 
	   /*    if(connectRe == APIClient.IMAPI_SUCC)
		   log.info("---��ʼ���ɹ�---");
		   else if(connectRe == APIClient.IMAPI_CONN_ERR)
		   log.error("---����ʧ��---");
		   else if(connectRe == APIClient.IMAPI_API_ERR)
		   log.error("---apiID������---");*/
	}

	private static SendMessageDao dao = SendMessageDao.getInstance();
	private static RecMessageDao recdao = RecMessageDao.getInstance();

	public  synchronized static List getSendMessages(Integer spro) {
		return dao.getSendMessage(spro);// 0��ʾδ����,����Ϣ
	}
	
	//ͨ��������Ϣ����S_CM_Messages���s_success
	public synchronized  static boolean  updateSuccessMessage(){
		 //Transaction t = beginTransaction();
		  try{
		  MOItem[] item = handler.receiveSM();
		  for(int i=0;i<item.length;i++){
			   MOItem  mo =item[i];
			   dao.updateSuccessMessage(new Long(mo.getSmID()));   
		  }
		  return true;
		  }catch(Exception e){
		//	  t.rollback();
			  log.error("--���·�����Ϣʧ��--");
			  return false;
		  }
	}

	// begin send Messages of not send
	public synchronized  static boolean BeginSendMessages() {
		//Transaction t = beginTransaction();
		try {
			log.info("---------BeginSendMessages-----");
			// get all not Send Messages
			List notSend = getSendMessages(new Integer(0));
			if(notSend==null){
			   log.info("-----û�пɷ��͵���Ϣ-------");
			   return false;
			}
			init();//�������ݿ�
			Iterator it = notSend.iterator();
			
			while (it.hasNext()) {
				SCmMessages sMsg = (SCmMessages) it.next();
				
				// send Message to Mms
				String[] mobile = new String[1];
				mobile[0]=sMsg.getSObject();
				
				int result = handler.sendSM(mobile, sMsg.getSContent(), smId, Long.parseLong(srcID));
				/*log.info("-------�ֻ���-----"+mobile[0]);
				log.info("-------����-----"+sMsg.getSContent());
				log.info("-------smid-----"+smId);
				log.info("-------srcID---------"+srcID);
				log.info("---------result---------------"+result);*/
				updateSProMessages(sMsg.getId());
				/*  if(result == APIClient.IMAPI_SUCC)
			        {            
					    log.info("���ͳɹ�\n");
			        }else if(result == APIClient.IMAPI_INIT_ERR)
			        	log.info("----δ��ʼ��----");
			         else if(result == APIClient.IMAPI_CONN_ERR)
			        	log.info("----���ݿ�����ʧ��----");
			        else if(result == APIClient.IMAPI_DATA_ERR)
			        	log.info("---��������----");
			        else if(result == APIClient.IMAPI_DATA_TOOLONG)
			        	log.info("----��Ϣ����̫��---");
			        else if(result == APIClient.IMAPI_INS_ERR)
			        	log.info("---���ݿ�������----");
			        else
			        	log.info("--������������---"+result);*/
			}
			return true;
		} catch (Exception e) {
		//	t.rollback();
			return false;
		}finally{
			// release();
		}

	}
	public static void release()
	{
		handler.release();
		Thread.currentThread().interrupt();
	}

	// update send success Message set s_pro = 1
	private synchronized static boolean updateSProMessages(Long id) {
		return dao.updateSProMessages(id);
	}
	
	public synchronized static SCmMessages getSendMessageByPk(Long id){
		return dao.getSendMessageByPk(id);
	}
	
	public synchronized  static  boolean insertRCMMessages(){
		try{
		
		MOItem[] item =handler.receiveSM();
		if ( item == null){
			log.info("---δ��ʼ�������ʧ��----");
			return false;
		}
		if(item.length==0){
			log.info("----û��MO����-----");
			return false;
		}
		for(int i=0;i<item.length;i++){
			RCmMessages RMsg =new  RCmMessages();
			recdao.insertRCMMessage(item[i]);
		}
		return true;
		}catch(Exception e){
			log.info("---���ն���ʧ��----"+e);
			return false;
		}finally{
		//	release();
		}
		
	}
	public static void  cancelSend(){
		release();
		System.exit(0);
	}
	/*private  void testMessage(){
		Calendar c =Calendar.getInstance();
		timer =new  Timer(true);
		timer.schedule(new TestShowMessage(), c.getTime(),seconds*1000);
	}*/
	

	private static  Logger log = Logger.getLogger(SCMMessageUtil.class);
}
