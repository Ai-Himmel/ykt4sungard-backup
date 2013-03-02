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
			StringBuffer buff = new StringBuffer();
			buff.append("select to_char(sysdate ").append("+ interval '").append(days).append("' day,'yyyymmddhh24miss') tdate from dual ");
			SQLQuery query = s.createSQLQuery(buff.toString());
			query.addScalar("tdate", Hibernate.STRING);
			String returnString = (String) query.uniqueResult();
			return returnString;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(SysDatePersistence.class);

}
