/**
 * 
 */
package com.kingstargroup.mobileMessage.dao;

import java.io.Serializable;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.mobileMessage.hibernate.HibernateSessionFactory;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: BasicDAO.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-11-9  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class BasicDAO {
	/**
	 * Description:�õ����ݿ��Session
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

	private final Logger _log = Logger.getLogger(BasicDAO.class);
}
