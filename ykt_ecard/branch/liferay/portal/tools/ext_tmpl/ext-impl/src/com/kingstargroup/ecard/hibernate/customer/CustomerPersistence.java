/**
 * 
 */
package com.kingstargroup.ecard.hibernate.customer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: CustomerPersistence.java
 * Description: �ͻ���־ò�������
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CustomerPersistence extends BasePersistence {
	
	/**
	 * Description:���ݴ���Ŀͻ��ţ��ͻ�����������õ��ͻ�����
	 * @param customerId ��ѯ�ͻ���
	 * @return TCifCustomer�־û�����
	 * Modify History:
	 */
	public TCustomer getCustomerById(long custid) throws DBSystemException {
		TCustomer customer = null;
		Session s = null;
		try {		
			s = openSession();
			customer = (TCustomer) s.get(TCustomer.class, new Long(custid));			
			return customer;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}finally{
			closeSession(s);
		}
	}
	
	/**
	 * Description:����ѧ���ŵõ���Ӧ�ͻ�
	 * @param stuempNo
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TCustomer getCustomerByStuempno(String stuempno) throws DBSystemException {
		Session s = null;		
		try {
			s = openSession();
			Query query = s.createQuery("from TCustomer where stuempno = :stuempno");
			query.setString("stuempno", stuempno);
			return (TCustomer) query.uniqueResult();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}finally{
			closeSession(s);
		}
	}
	private static final Log _log = LogFactory.getLog(CustomerPersistence.class);
}
