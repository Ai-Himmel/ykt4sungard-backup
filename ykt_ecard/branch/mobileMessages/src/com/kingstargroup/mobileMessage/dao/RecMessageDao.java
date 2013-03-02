package com.kingstargroup.mobileMessage.dao;

import org.apache.log4j.Logger;
import org.hibernate.Session;

import com.jasson.im.api.MOItem;
import com.kingstargroup.mobileMessage.hibernate.RCmMessages;
import com.kingstargroup.mobileMessage.util.DateUtilExtend;


public class RecMessageDao extends BasicDAO {

	private static RecMessageDao _instance;
	private final  Logger _log = Logger.getLogger(RecMessageDao.class);
	
	
	public static RecMessageDao getInstance() {
		if (_instance == null) {
			_instance = new RecMessageDao();
		}
		return _instance;
	}
	
	public   boolean insertRCMMessage(MOItem item){ 
		try{
		Session sess = getSession();
		RCmMessages RMsg = new RCmMessages();
		RMsg.setRObject(item.getMobile());
		RMsg.setRContent(item.getContent());
	/*	_log.info("------手机-----------"+item.getMobile());
		_log.info("-----接收内容------------"+item.getContent());
		_log.info("-----接收日期---------"+item.getMoTime());*/
//		2008-09-27 18:19:21.0
		String time =item.getMoTime();
		String sDate = DateUtilExtend.formatDate2(time.substring(0, 10));
		String sTime = time.substring(11,13)+time.substring(14,16)+time.substring(17,19);
	/*	_log.info("-----sDate---------"+sDate);
		_log.info("-----sTime---------"+sTime);*/
		RMsg.setRDate(sDate);
		RMsg.setRTime(sTime);
		RMsg.setRCardId("00000");
		RMsg.setRPro(new Integer(0));
		//RMsg.setRDate(item.getMoTime());
		sess.save(RMsg);
		sess.flush();
		return false;
		}catch(Exception e){
			return true;
		}
		
		
	}
}
