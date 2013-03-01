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
 * File name: UserStoreLimitDAO.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-10  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class UserStoreLimitDAO extends BasicDAO {

	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static UserStoreLimitDAO getInstance() {
		if (_instance == null) {
			_instance = new UserStoreLimitDAO();
		}
		return _instance;
	}
	
	public List getStoreList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			Query query = s.createQuery(" select id.storeCode from TLeadqueryStorelimit where id.operCode = :userId");			
			query.setString("userId", userId);
			return query.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public void deleteStoreList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			Query query = s.createQuery(" from TLeadqueryStorelimit where id.operCode = :userId");
			
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
	
	public void deleteStoreList(String userIds[]) throws HibernateException {		
		try {
			for (int i = 0; i < userIds.length; i++) {
				deleteStoreList(userIds[i]);
			}
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	private static UserStoreLimitDAO _instance;

}
