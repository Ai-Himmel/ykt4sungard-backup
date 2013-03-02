package com.kingstargroup.ecard.common;

import java.io.Serializable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.util.HibernateUtil;

public class BasicPersistence {

	protected Session getSession() {
		return HibernateUtil.openLocalSession();
	}
	
	public void saveOrUpdate(Object obj) throws DBSystemException {
		Session s = getSession();
		try {
			s.saveOrUpdate(obj);			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex);
		}
	}
	
	public void save(Object obj) throws DBSystemException {
		Session s = getSession();
		try {
			s.save(obj);			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex);
		}
	}
	
	public void delete(Object obj) throws DBSystemException {
		Session s = getSession();
		try {
			s.delete(obj);			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex);
		}
	}
	
	public Object findByPrimaryKey(Class pClass, Serializable key) throws DBSystemException{
		Session s = getSession();
		try {
			return s.get(pClass, key);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex);
		}
	}
	
	Log _log = LogFactory.getLog(BasicPersistence.class.getClass());
}
