package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.hibernate.pos.PosPersistence;


public class PosUtil {
	public static PosPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PosPersistence persistence) {
		_persistence = persistence;
	}

	private static PosUtil _getUtil() {
		if (_util == null) {
			_util = (PosUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PosUtil.class.getName();
	private static PosUtil _util;
	private PosPersistence _persistence;
}
