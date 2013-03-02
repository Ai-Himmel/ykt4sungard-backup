package com.kingstargroup.ecard.hibernate.subsyslog;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import com.kingstargroup.ecard.hibernate.subsyslog.TSubsysLog;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.service.persistence.BasePersistence;

public class SysLogPersistence extends BasePersistence {

	public void save(TSubsysLog info) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.saveOrUpdate(info);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	private static final Log _log = LogFactory.getLog(SysLogPersistence.class);

}
