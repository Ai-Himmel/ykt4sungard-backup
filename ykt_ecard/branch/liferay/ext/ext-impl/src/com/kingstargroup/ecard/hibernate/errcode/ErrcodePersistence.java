/**
 * 
 */
package com.kingstargroup.ecard.hibernate.errcode;

import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: SysDatePersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-9-29 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class ErrcodePersistence extends BasePersistence {

	public String getErrMsg(String errcode) throws DBSystemException {
		Session s = null;
		String errMsg = "";
		Query query = null;
		try {
			s = openSession();
			query = s
					.createQuery("from TErrcode where errcode=:errcode");
			query.setLong("errcode", Long.valueOf(errcode));
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				TErrcode terrcode = (TErrcode) iter.next();
				errMsg = terrcode.getErrmsg();
			}
			return errMsg;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	private static final Log _log = LogFactory.getLog(ErrcodePersistence.class);

}
