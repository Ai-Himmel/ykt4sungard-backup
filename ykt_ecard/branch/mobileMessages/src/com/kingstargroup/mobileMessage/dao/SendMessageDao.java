package com.kingstargroup.mobileMessage.dao;

import java.util.List;

import com.jasson.im.api.APIClient;
import com.jasson.im.api.MOItem;
import com.kingstargroup.mobileMessage.hibernate.SCmMessages;
import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;


public class SendMessageDao extends BasicDAO{

	private static SendMessageDao _instance;
	private final Logger _log = Logger.getLogger(SendMessageDao.class);
	
	
	public static SendMessageDao getInstance() { 
		if (_instance == null) {
			_instance = new SendMessageDao();
		}
		return _instance;
	}
	
   public  boolean updateSuccessMessage(Long id){
		try{   
			   Session sess = getSession();
			   SCmMessages sMsg = this.getSendMessageByPk(id);   
			   sess.saveOrUpdate(sMsg);
			   sess.flush();
			   return true;
		  }
		  catch(HibernateException e){
			_log.error(e);
			return false;
		}
	  }
	
	public  List getSendMessage(Integer spro)throws HibernateException{
		Session sess = getSession();
		try{
			String hql =" from  SCmMessages  sMsg"
				       +" where  SPro="+spro;
			Query q = sess.createQuery(hql);
			return q.list();
		}catch(HibernateException e){
			_log.error(e);
			return null;
		}
	}
	
	public SCmMessages getSendMessageByPk(Long id){
		SCmMessages sMsg =(SCmMessages)this.findByPrimaryKey(SCmMessages.class,id);
		return sMsg;
	}
	
	//update send success  Messages  , set  spro=1;
	public boolean updateSProMessages(Long id){
		Session sess = getSession();
	
		try{
			SCmMessages sMsg = 	getSendMessageByPk(id);
			sMsg.setSPro(new Integer(1));
			sess.saveOrUpdate(sMsg);
			sess.flush();
			return true;
		}catch(HibernateException e){
			_log.error(e);
			return false;
		}
	}

}
