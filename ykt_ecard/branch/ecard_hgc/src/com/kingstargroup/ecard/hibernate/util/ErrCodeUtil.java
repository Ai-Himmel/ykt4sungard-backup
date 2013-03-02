/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AreaPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ErrCodeUtil extends BasicPersistence {

	/**
	 * Description:根据地域ID得到地域名称
	 * @param areaId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public String getErrMsg(String errCode) throws DBSystemException {
		Session s = getSession();
		String errMsg = "";
		Query query = null;
		try {
			query = s.createSQLQuery("select EMSG from YKT_CUR.T_PIF_ERRCODE where ECODE=:ecode");
			query.setString("ecode",errCode);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()){
				Object row = (Object)iter.next();
				errMsg = row.toString();
			}
			return errMsg;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(ErrCodeUtil.class);
}
