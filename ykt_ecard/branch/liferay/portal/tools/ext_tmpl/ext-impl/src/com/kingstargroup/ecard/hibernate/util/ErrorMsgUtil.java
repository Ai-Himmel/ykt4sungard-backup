package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.tradedetail.ErrorMsgPersistence;

public class ErrorMsgUtil {
	
	public static String getErrorMsg(int code) throws PortalException {
			return getPersistence().getErrorMsgByCode(code);
	}
	
	
	public static ErrorMsgPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(ErrorMsgPersistence persistence) {
		_persistence = persistence;
	}

	private static ErrorMsgUtil _getUtil() {
		if (_util == null) {
			_util = (ErrorMsgUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ErrorMsgUtil.class.getName();
	private static ErrorMsgUtil _util;
	private ErrorMsgPersistence _persistence;
}
