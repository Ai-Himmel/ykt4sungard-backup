/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.device.DevicePersistence;
import com.kingstargroup.ecard.hibernate.device.TDevice;
import com.kingstargroup.ecard.hibernate.device.TPifDevice;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: DeviceUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class DeviceUtil{

	/**
	 * Description:根据设备ID得到设备对象
	 * @param deviceId 
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TDevice getDeviceById(String deviceid) throws PortalException {
		TDevice device = null;
		try {
			device = getPersistence().getDeviceById(deviceid);
		} catch (DBSystemException e) {
			throw e;
		} 
		return device;
	}
	
	public static DevicePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(DevicePersistence persistence) {
		_persistence = persistence;
	}

	private static DeviceUtil _getUtil() {
		if (_util == null) {
			_util = (DeviceUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = DeviceUtil.class.getName();
	private static DeviceUtil _util;
	private DevicePersistence _persistence;
	

}
