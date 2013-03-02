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

import com.kingstargroup.conference.common.WebKeys;

/**
 * @author Õı”®
 *
 */
public class AttGroupNameDAO extends BasicDAO {
	private static AttGroupNameDAO _instance;
	private Logger errlog = Logger.getLogger("Errlog");
	
	public static AttGroupNameDAO getInstance() {
		if (_instance == null) {
			_instance = new AttGroupNameDAO();
		}
		return _instance;
	}
	
	public List getAttGroupName(String groupname) {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TGroup a where a.groupName=? ");	
			q.setString(0, groupname);
			return q.list();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	public List getAttGroupName(String operid, String groupname) {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TGroup where 1=1 ");
		if(!"".equals(groupname)) {
			sqlStr.append(" and groupName='" + groupname + "' ");
		}
		if(!"".equals(operid)) {
			sqlStr.append(" and operId ='" + operid + "' ");
		}
		try {
			Query q = s.createQuery(sqlStr.toString());	
			return q.list();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public List getAttGroupName() {
		Session s = getSession();
		String userkey = WebKeys.USER_KEY;
		try {
			Query q = s.createQuery(" from TGroup where operId ='" + userkey + "' ");	
			return q.list();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public void deleteAttGroupName(String[] ids) {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TGroup a where a.groupId in ("+ ids[0]);		
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
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
}
