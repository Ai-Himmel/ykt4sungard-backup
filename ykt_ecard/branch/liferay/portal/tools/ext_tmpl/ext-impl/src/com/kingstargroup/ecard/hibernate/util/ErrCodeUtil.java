/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.errcode.ErrcodePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AreaPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 
 * ===================================<br>
 *     Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ErrCodeUtil {

	/**
	 * Description
	 * @param areaId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public String getErrMsg(String errCode) throws PortalException {
			return getPersistence().getErrMsg(errCode);

	}
	
	
	public static ErrcodePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(ErrcodePersistence persistence) {
		_persistence = persistence;
	}

	private static ErrCodeUtil _getUtil() {
		if (_util == null) {
			_util = (ErrCodeUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ErrCodeUtil.class.getName();
	private static ErrCodeUtil _util;
	private ErrcodePersistence _persistence;
	
	private static final Log _log = LogFactory.getLog(ErrCodeUtil.class);
}
