package com.kingstargroup.ecard.hibernate.util;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.sysdate.SysDatePersistence;

public class SysDateUtil {

	public static String getSysDate(int day) throws PortalException {
		return getPersistence().getSysDate(day);

	}

	public static SysDatePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(SysDatePersistence persistence) {
		_persistence = persistence;
	}

	private static SysDateUtil _getUtil() {
		if (_util == null) {
			_util = (SysDateUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = SysDateUtil.class.getName();
	private static SysDateUtil _util;
	private SysDatePersistence _persistence;

}
