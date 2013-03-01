/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

public class CutTypeDAO extends BasicDAO {
	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static CutTypeDAO getInstance() {
		if (_instance == null) {
			_instance = new CutTypeDAO();
		}
		return _instance;
	}
	
	public List getCutType()throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TCifCuttypefee ");
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}
	}
	private static CutTypeDAO _instance;
	private Log _log = LogFactory.getLog(CutTypeDAO.class.getClass());
}
