/**
 * 
 */
package com.kingstargroup.ecard.hibernate.area;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
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
public class AreaPersistence extends BasicPersistence {
	
	/**
	 * Description:根据地域ID得到地域名称
	 * @param areaId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TPifArea getAreaById(String areaId) throws DBSystemException {
		Session s = getSession();
		try {
			//_log.info("-------getAreaById----------");
			TPifArea tpifarea =(TPifArea) s.get(TPifArea.class, Integer.valueOf(areaId));
		//	_log.info("-------getAreaById---end-------");
			return tpifarea;
			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(AreaPersistence.class);
}
