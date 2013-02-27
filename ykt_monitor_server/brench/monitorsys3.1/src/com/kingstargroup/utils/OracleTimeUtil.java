package com.kingstargroup.utils;

import org.apache.log4j.Logger;

import org.apache.xml.utils.FastStringBuffer;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.commons.HibernateSessionFactory;

public class OracleTimeUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(OracleTimeUtil.class);

	public static String getSysDate(int days) throws HibernateException {
		if (logger.isDebugEnabled()) {
			logger.debug("getSysDate(int, Session) - start"); //$NON-NLS-1$
		}

		Session s = HibernateSessionFactory.currentSession();
		try {

			StringBuffer buff = new StringBuffer();
			buff.append("select to_char(sysdate ")
			.append("+ interval '")
			.append(days)
			.append("' day,'yyyymmddhh24miss') tdate from dual ");
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
