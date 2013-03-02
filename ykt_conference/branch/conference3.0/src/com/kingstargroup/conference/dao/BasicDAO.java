/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.io.Serializable;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Session;

public class BasicDAO {
	/**
	 * Description:得到数据库的Session
	 * @return
	 * Modify History:
	 */
	protected Session getSession() {
		return com.kingstargroup.conference.hibernate.HibernateSessionFactory.currentSession();
	}
	
	public void saveOrUpdate(Object obj) throws HibernateException {
		Session s = getSession();
		try {
			s.saveOrUpdate(obj);			
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	public void save(Object obj) throws HibernateException {
		Session s = getSession();
		try {
			s.save(obj);
			//s.flush();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	public void delete(Object obj) throws HibernateException {
		Session s = getSession();
		try {
			s.delete(obj);			
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	public Object findByPrimaryKey(Class pClass, Serializable key) throws HibernateException{
		Session s = getSession();
		try {
			return s.get(pClass, key);
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	Logger errlog = Logger.getLogger("Errlog");
	Logger bizlog=Logger.getLogger("Businesslog");
}
