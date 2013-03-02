/**
 * 
 */
package com.kingstargroup.ecard.hibernate.account;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: AccountPersistence.java
 * Description: 帐号表持久操作对象
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AccountPersistence extends BasePersistence {
	
	/**
	 * Description: 根据用户卡号查询到帐号对象,这里只能对应出一个帐号对象
	 * @param cardId 查询用户卡号
	 * @return TAifAccount持久对象
	 * Modify History:
	 */
	public TAccount getAccountByCardno(String cardno) throws DBSystemException {		
		TAccount account = null;
		Session s = null;
		try {
			s = openSession();
			StringBuffer hsql = new StringBuffer();
			hsql.append("FROM com.kingstargroup.ecard.hibernate.account.TAccount account where")
				.append(" account.cardno = ?");
			Query q = s.createQuery(hsql.toString());
			q.setInteger(0, Integer.parseInt(cardno));
			account = (TAccount) q.list().get(0);			
			return account;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}finally{
			closeSession(s);
		}
	}
	
	public List getCardnoByCustid(int custid) throws DBSystemException{
		Session s = null;
		try {
			s = openSession();			
			StringBuffer sqlStr = new StringBuffer();
			sqlStr.append(" from com.kingstargroup.ecard.hibernate.card.TCard card where ")
			.append(" card.custid="+custid);
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			throw new DBSystemException(he.getMessage());
		}finally{
			closeSession(s);
		}
	}
	
	public List getCustomerByStuempno(String stuempno)throws DBSystemException{
		Session s = null;
		try {
			s = openSession();
			StringBuffer sqlStr = new StringBuffer();
			sqlStr.append(" from com.kingstargroup.ecard.hibernate.customer.TCustomer cust where ")
			.append(" cust.stuempno='"+stuempno+"' and cust.status='1'");
			Query q = s.createQuery(sqlStr.toString());
			List list = q.list();
			return list;
		} catch (HibernateException he) {
			_log.error(he);
			throw new DBSystemException(he.getMessage());
		}finally{
			closeSession(s);
		}
	}
	
	private static final Log _log = LogFactory.getLog(AccountPersistence.class);
}
