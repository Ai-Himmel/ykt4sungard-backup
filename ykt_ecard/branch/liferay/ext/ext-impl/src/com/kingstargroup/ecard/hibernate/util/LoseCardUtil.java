/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.hibernate.losecard.LoseCardPersistence;

public class LoseCardUtil{

	public static LoseCardPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(LoseCardPersistence persistence) {
		_persistence = persistence;
	}

	private static LoseCardUtil _getUtil() {
		if (_util == null) {
			_util = (LoseCardUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = LoseCardUtil.class.getName();
	private static LoseCardUtil _util;
	private LoseCardPersistence _persistence;
}
