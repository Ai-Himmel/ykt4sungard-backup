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

import com.kingstargroup.conference.hibernate.form.TDelegate;

/**
 * @author 人员分组相关代码
 * 
 */
public class DelegateDAO extends BasicDAO {
	private static DelegateDAO _instance;

	private Logger errlog = Logger.getLogger("Errlog");

	public static DelegateDAO getInstance() {
		if (_instance == null) {
			_instance = new DelegateDAO();
		}
		return _instance;
	}

	public TDelegate getDelegate(String id) throws HibernateException {
		Session s = getSession();
		TDelegate dlgt = null;
		try {
			Query q = s.createQuery("from TDelegate where dlgtId=" + id);
			List list = q.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				dlgt = (TDelegate) iter.next();
			}
		} catch (HibernateException e) {
			e.printStackTrace();
			errlog.error(e);
			throw e;
		}
		return dlgt;
	}

	public List getAllDelegates(String operId) throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("from TDelegate where operId ='" + operId + "' order by dlgtId");	
			return q.list();
		} catch (HibernateException e) {
			e.printStackTrace();
			errlog.error(e);
			throw e;
		}

	}
	
	public List getDelegates(String operId,String dlgtName) throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("from TDelegate where dlgtName like '%"+dlgtName+"%' and operId ='" + operId + "' ");
			return q.list();
		} catch (HibernateException e) {
			e.printStackTrace();
			errlog.error(e);
			throw e;
		}
	}
	
	public List getConfDlgt(String id) throws HibernateException,Exception {
		Session s = getSession();
		try {

			Query q = s.createQuery("from TAttendeeList where delegray=" + id
					+ "");
			List list = q.list();
			return list;
		} catch (HibernateException e) {
			e.printStackTrace();
			errlog.error(e);
			throw e;
		}catch (Exception e) {
			e.printStackTrace();
			errlog.error(e);
			throw e;
		}

	}

	public void deleteDelegates(String ids[]) throws HibernateException {
		Session s = getSession();
		try {
			for (int i = 0; i < ids.length; i++) {
				s.delete(getDelegate(ids[i]));
			}
		} catch (HibernateException e) {
			e.printStackTrace();
			errlog.error(e);
			throw e;
		}
	}

	public void deleteAllDelegates() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("delete from TDelegate");
			q.executeUpdate();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

}
