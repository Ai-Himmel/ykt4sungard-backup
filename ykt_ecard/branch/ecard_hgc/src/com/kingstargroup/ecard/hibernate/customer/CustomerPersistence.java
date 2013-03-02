/**
 * 
 */
package com.kingstargroup.ecard.hibernate.customer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: CustomerPersistence.java
 * Description: 客户表持久操作对象
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CustomerPersistence extends BasicPersistence {
	
	/**
	 * Description:根据传入的客户号（客户表的主键）得到客户对象
	 * @param customerId 查询客户号
	 * @return TCifCustomer持久化对象
	 * Modify History:
	 */
	public TCifCustomer getCustomerById(int customerId) throws DBSystemException {
		TCifCustomer customer = null;
		Session s = getSession();
		try {			
			customer = (TCifCustomer) s.get(TCifCustomer.class, new Integer(customerId));			
			return customer;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:根据学工号得到对应客户
	 * @param stuempNo
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TCifCustomer getCustomerByStuempNo(String stuempNo) throws DBSystemException {
		Session s = getSession();		
		try {
			Query query = s.createQuery("from TCifCustomer as customer where customer.stuempNo = :stuempNo");
			query.setString("stuempNo", stuempNo);
			return (TCifCustomer) query.uniqueResult();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	private static final Log _log = LogFactory.getLog(CustomerPersistence.class);
}
