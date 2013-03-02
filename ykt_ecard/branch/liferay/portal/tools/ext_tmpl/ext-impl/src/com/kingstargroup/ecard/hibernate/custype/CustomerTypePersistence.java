/**
 * 
 */
package com.kingstargroup.ecard.hibernate.custype;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: CustomerTypePersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-19  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CustomerTypePersistence extends BasePersistence {

	public TCusttype getCustomertype(Integer id) throws DBSystemException {
		Session session = null;		
		try {
			session = openSession();
			return (TCusttype) session.get(TCusttype.class, id);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}finally {
			closeSession(session);
		}
	}
	
	private static final Log _log = LogFactory.getLog(CustomerTypePersistence.class);
}
