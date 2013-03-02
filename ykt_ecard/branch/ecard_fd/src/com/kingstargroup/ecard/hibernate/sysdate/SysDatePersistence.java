/**
 * 
 */
package com.kingstargroup.ecard.hibernate.sysdate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.util.lang.FastStringBuffer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: SysDatePersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-29  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class SysDatePersistence extends BasicPersistence {
	
	/**
	 * Description:
	 * @param days 需要计算的天数
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public String getSysDate(int days) throws DBSystemException {
		Session s = getSession();
		try {
			String validDays = null;
			if (String.valueOf(days).indexOf('-') == -1) {
				validDays = "+" + days;
			}
			FastStringBuffer buff = new FastStringBuffer();
			buff.append("select substr(d,1,4)||substr(d,6,2)||substr(d,9,2)")
				.append("||substr(t,1,2)||substr(t,4,2)||substr(t,7,2) tdate  ")
				.append("  from (SELECT char(CURRENT date")
				.append(validDays)
				.append(" DAYS,ISO) d ,char(current time,ISO) t ")
				.append(" FROM SYSIBM.SYSDUMMY1 ) aaa");
			SQLQuery query = s.createSQLQuery(buff.toString());
			query.addScalar("tdate", Hibernate.STRING);			
			return (String) query.uniqueResult();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(SysDatePersistence.class);

}
