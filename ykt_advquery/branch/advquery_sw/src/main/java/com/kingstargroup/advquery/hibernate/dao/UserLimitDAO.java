/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: UserLimitDAO.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-10  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class UserLimitDAO extends BasicDAO {

	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static UserLimitDAO getInstance() {
		if (_instance == null) {
			_instance = new UserLimitDAO();
		}
		return _instance;
	}
	
	public List getFuncList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			Query query = s.createQuery(" select id.funcCode from TLeadqueryOperlimit where id.operCode = :userId");
			query.setString("userId", userId);
			return query.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public void deleteFuncList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			Query query = s.createQuery(" from TLeadqueryOperlimit where id.operCode = :userId");
			
			query.setString("userId", userId);			
			Iterator it = query.iterate();
			while (it.hasNext()) {
				s.delete(it.next());
			}			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public void deleteFuncList(String userIds[]) throws HibernateException {		
		try {
			for (int i = 0; i < userIds.length; i++) {
				deleteFuncList(userIds[i]);
			}
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	private static UserLimitDAO _instance;

}
