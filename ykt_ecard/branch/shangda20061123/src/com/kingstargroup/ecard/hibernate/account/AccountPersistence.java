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

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.card.TPifCard;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: AccountPersistence.java
 * Description: �ʺű�־ò�������
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AccountPersistence extends BasicPersistence {
	
	/**
	 * Description: �����û����Ų�ѯ���ʺŶ���,����ֻ�ܶ�Ӧ��һ���ʺŶ���
	 * @param cardId ��ѯ�û�����
	 * @return TAifAccount�־ö���
	 * Modify History:
	 */
	public TAifAccount getAccountByCardId(String cardId) throws DBSystemException {		
		TAifAccount account = null;
		Session s = getSession();
		try {
			StringBuffer hsql = new StringBuffer();
			hsql.append("FROM com.kingstargroup.ecard.hibernate.account.TAifAccount as account where")
				.append(" account.cardId = ?");
			Query q = s.createQuery(hsql.toString());
			q.setInteger(0, Integer.parseInt(cardId));
			account = (TAifAccount) q.list().get(0);			
			return account;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public List getCardNoByCustNo(int custId) throws DBSystemException{
		Session s = getSession();
		try {
			StringBuffer sqlStr = new StringBuffer();
			sqlStr.append(" from com.kingstargroup.ecard.hibernate.card.TPifCard as card where ")
			.append(" card.cosumerId="+custId);
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			throw new DBSystemException(he.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(AccountPersistence.class);
}
