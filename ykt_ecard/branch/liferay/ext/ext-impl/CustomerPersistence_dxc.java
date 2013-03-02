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
import com.kingstargroup.ecard.hibernate.account.TAccount;
import com.kingstargroup.ecard.hibernate.device.VTerm;
import com.liferay.portal.service.persistence.BasePersistence;

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
public class CustomerPersistence extends BasePersistence {
	
	/**
	 * Description:根据传入的客户号（客户表的主键）得到客户对象
	 * @param customerId 查询客户号
	 * @return TCifCustomer持久化对象
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
	 * Description:根据学工号得到对应客户
	 * @param stuempNo
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TCustomer getCustomerByStuempno(String stuempno) throws DBSystemException {
		Session s = null;		
		try {
			s = openSession();
//			Query query = s.createQuery("from TCustomer where upper(stuempno) = :stuempno");
//			query.setString("stuempno", stuempno);
			//用的是客户号
			Query query = s.createQuery("from TCustomer where custid = :stuempno");
			query.setLong("stuempno", Long.parseLong(stuempno));	
			return (TCustomer) query.uniqueResult();
		} catch (HibernateException ex) {
			_log.error(ex);
			ex.printStackTrace();
			throw new DBSystemException(ex.getMessage());
		}finally{
			closeSession(s);
		}
	}
	
	
	public TCustomer getCustomerByAccno(String accno) throws DBSystemException {
		Session s = null;		
		try {
			s = openSession();
			TAccount taccount = (TAccount) s.get(TAccount.class, accno);
			if(taccount!=null){
				return (TCustomer) s.get(TCustomer.class, taccount.getCustid());
			}			
			return null;
		} catch (HibernateException ex) {
			_log.error(ex);
			ex.printStackTrace();
			throw new DBSystemException(ex.getMessage());
		}finally{
			closeSession(s);
		}
	}
	private static final Log _log = LogFactory.getLog(CustomerPersistence.class);
}
