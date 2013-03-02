/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.hibernate.shop.ShopPersistence;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ShopUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-13  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ShopUtil{

	public static ShopPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(ShopPersistence persistence) {
		_persistence = persistence;
	}

	private static ShopUtil _getUtil() {
		if (_util == null) {
			_util = (ShopUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ShopUtil.class.getName();
	private static ShopUtil _util;
	private ShopPersistence _persistence;
}
