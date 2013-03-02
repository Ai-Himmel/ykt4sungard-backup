/**
 * 
 */
package com.kingstargroup.ecard.common;


import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.liferay.portal.util.HibernateConfiguration;
import com.liferay.portal.util.HibernateUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: EcardTransactionManager.java
 * Description: 
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-16  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class EcardTransactionManager {
	Transaction t;
	
	public EcardTransactionManager() {
		super();
	}
	/**
	 * Description:��ʼһ������
	 * Modify History:
	 */
	public void beginTransaction() {
		t = openSession().beginTransaction();
	}
	
	/**
	 * Description:�ύһ������
	 * Modify History:
	 */
	public void commitTransaction() {
		t.commit();
		closeSession();
	}
	
	public void rollback() {
		t.rollback();
		closeSession();
	}
	
	public Session getSession() {
		return openSession();		
	}
	
	Session openSession() throws HibernateException {
		return HibernateUtil.openLocalSession();		
	}	
	
	void closeSession() {
		HibernateUtil.closeSession();
	}

}
