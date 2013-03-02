/**
 * 
 */
package com.kingstargroup.ecard.hibernate.tradedetail;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;

/**
 * @author hjw
 * 
 */
public class ErrorMsgPersistence extends
		com.liferay.portal.service.persistence.BasePersistence {

	public String getErrorMsgByCode(int code) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Query q = s.getNamedQuery("ErrorMsgSQL");
			q.setInteger("code", code);
			return q.list().get(0).toString();
		} catch (HibernateException he) {
			_log.error(he);
			throw new DBSystemException(he.getMessage());
		} finally {
			closeSession(s);
		}
	}

	private static final Log _log = LogFactory
			.getLog(ErrorMsgPersistence.class);
}
