/**
 * 
 */
package com.kingstargroup.ecard.hibernate.tradedetail;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;

/**
 * @author hjw
 *
 */
public class GetErrorMsg extends BasicPersistence {

	public String getErrorMsgByCode(int code)throws DBSystemException {
		Session s = getSession();
		try {
			Query q = s.getNamedQuery("ErrorMsgSQL");
			q.setInteger("code",code);
			return q.list().get(0).toString();
		} catch (HibernateException he) {
			_log.error(he);
			throw new DBSystemException(he.getMessage());
		}
	}
	
	private static final Log _log = LogFactory
			.getLog(GetErrorMsg.class);
}
