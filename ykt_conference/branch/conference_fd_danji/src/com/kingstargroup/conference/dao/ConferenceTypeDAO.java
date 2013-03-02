/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;


/**
 * @author 王莹
 * 
 */
public class ConferenceTypeDAO extends BasicDAO {
	private static ConferenceTypeDAO _instance;
	private Logger errlog = Logger.getLogger("Errlog");

	public static ConferenceTypeDAO getInstance() {
		if (_instance == null) {
			_instance = new ConferenceTypeDAO();
		}
		return _instance;
	}
	
	public void deleteConferenceType(String[] ids) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TConferenceType where typeId in (" + ids[0]);
		for(int i=1, l=ids.length; i<l; i++) {
			sqlStr.append(", " + ids[i]);
		}
		sqlStr.append(")");
		try {
			Query q = s.createQuery(sqlStr.toString());
			Iterator iter = q.iterate();
			while (iter.hasNext()){
				s.delete(iter.next());
			}
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	public void deleteAllConferenceType() throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("delete from TConferenceType");
		try {
			Query q = s.createQuery(sqlStr.toString());
			q.executeUpdate();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	// 未测试
	public List getConfType() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TConferenceType");
			return q.list();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	// 未测试
	public List getConfType(String typename) throws HibernateException {
		Session s = getSession();
		try {
			Query q = null;
			if("".equals(typename)) {
				return getConfType();
			} else {
				String sql = " from TConferenceType a where a.typeName='" + typename + "' ";
				q = s.createQuery(sql);	
				return q.list();
			}		
			
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	

	public List getConfTypeForQue(String typename) throws HibernateException {
		Session s = getSession();
		try {
			Query q = null;
			if("".equals(typename)) {
				return getConfType();
			} else {
				String sql = " from TConferenceType a where a.typeName like '%" + typename + "%' ";
				q = s.createQuery(sql);	
				return q.list();
			}		
			
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceTypeDAO根据会议类型查询会议<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      王莹    2006-4-5  <br>
	 * @author   王莹
	 * @version 
	 * @since 1.0
	 */
	public List getConferenceByType(
			String typename
			)throws HibernateException{
		Session s = getSession();
		String sql = " from TConference a where a.typeName='" + typename + "' ";
		try {
			Query q = s.createQuery(sql);
			return q.list();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}	
	
	public int getMaxConId(){
		Session s = getSession();
		String sql = "select max(conId) from TConference ";
		int ret = 1;
		try {
			Query q = s.createQuery(sql);
			List list = q.list();
			Iterator iter = list.iterator();
			if(iter.hasNext()){
				ret = Integer.parseInt(iter.next().toString());
			}
			return ret;
		} catch (HibernateException ex) {
			errlog.error(ex);
		}catch (Exception e) {
			errlog.error(e);
		}
		return ret;

	}
}
