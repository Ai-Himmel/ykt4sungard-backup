package com.kingstargroup.utils;

import org.apache.log4j.Logger;

import org.apache.xml.utils.FastStringBuffer;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.commons.HibernateSessionFactory;

public class DB2TimeUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DB2TimeUtil.class);

	public static String getSysDate(int days) throws HibernateException {
		if (logger.isDebugEnabled()) {
			logger.debug("getSysDate(int, Session) - start"); //$NON-NLS-1$
		}

		Session s = HibernateSessionFactory.currentSession();
		try {
			String validDays = null;
			if (String.valueOf(days).indexOf('-') == -1) {
				validDays = "+" + days;
			}
			StringBuffer buff = new StringBuffer();
			buff.append("select substr(d,1,4)||substr(d,6,2)||substr(d,9,2)")
				.append("||substr(t,1,2)||substr(t,4,2)||substr(t,7,2) tdate  ")
				.append("  from (SELECT char(CURRENT date")
				.append(validDays)
				.append(" DAYS,ISO) d ,char(current time,ISO) t ")
				.append(" FROM SYSIBM.SYSDUMMY1 ) aaa");
			SQLQuery query = s.createSQLQuery(buff.toString());
			query.addScalar("tdate", Hibernate.STRING);			

			String returnString = (String) query.uniqueResult();
			if (logger.isDebugEnabled()) {
				logger.debug("getSysDate(int, Session) - end"); //$NON-NLS-1$
			}
			return returnString;
		} catch (HibernateException ex) {
			logger.error("getSysDate(int, Session)", ex); //$NON-NLS-1$
			return null;
		}
	}
}
