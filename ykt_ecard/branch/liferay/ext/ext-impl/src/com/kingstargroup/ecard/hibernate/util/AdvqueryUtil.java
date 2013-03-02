/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.hibernate.advquery.AdvqueryPersistence;
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
public class AdvqueryUtil{

	public static AdvqueryPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(AdvqueryPersistence persistence) {
		_persistence = persistence;
	}

	private static AdvqueryUtil _getUtil() {
		if (_util == null) {
			_util = (AdvqueryUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = AdvqueryUtil.class.getName();
	private static AdvqueryUtil _util;
	private AdvqueryPersistence _persistence;
}
