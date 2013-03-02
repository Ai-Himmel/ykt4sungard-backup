/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.area.AreaPersistence;
import com.kingstargroup.ecard.hibernate.area.TArea;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AreaUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AreaUtil{

	/**
	 * Description:根据地域ID得到地域对象
	 * @param areaId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public static TArea getAreaBycode(String areacode) throws PortalException {
		return getPersistence().getAreaBycode(areacode);
	}
	
	public static AreaPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(AreaPersistence persistence) {
		_persistence = persistence;
	}

	private static AreaUtil _getUtil() {
		if (_util == null) {
			_util = (AreaUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = AreaUtil.class.getName();
	private static AreaUtil _util;
	private AreaPersistence _persistence;

}
