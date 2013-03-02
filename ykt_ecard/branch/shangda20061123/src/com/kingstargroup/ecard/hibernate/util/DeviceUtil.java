/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.device.DevicePersistence;
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
public class DeviceUtil extends BasicUtil {

	/**
	 * Description:根据设备ID得到设备对象
	 * @param deviceId 
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TPifDevice getDeviceById(String deviceId) throws PortalException {
		DevicePersistence persistence = (DevicePersistence) getPersistence(DevicePersistence.class.getName());
		Transaction t = beginTransaction();
		TPifDevice device = null;
		try {
			device = persistence.getDeviceById(deviceId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return device;
	}

}
