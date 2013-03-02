/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.io.Serializable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: BasicDAO.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-9  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class BasicDAO {
	/**
	 * Description:得到数据库的Session
	 * @return
	 * Modify History:
	 */
	protected Session getSession() {
		return HibernateSessionFactory.currentSession();
	}
	
	public void saveOrUpdate(Object obj) throws HibernateException {
		Session s = getSession();
		try {
			s.saveOrUpdate(obj);			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public void save(Object obj) throws HibernateException {
		Session s = getSession();
		try {
			s.save(obj);			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public void delete(Object obj) throws HibernateException {
		Session s = getSession();
		try {
			s.delete(obj);			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public Object findByPrimaryKey(Class pClass, Serializable key) throws HibernateException{
		Session s = getSession();
		try {
			return s.get(pClass, key);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	Log _log = LogFactory.getLog(BasicDAO.class.getClass());
}
