/**
 * 
 */
package com.kingstargroup.ecard.hibernate.device;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: DevicePersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class DevicePersistence extends BasicPersistence {

	/**
	 * Description: 根据设备ID得到对应的设备对象
	 * @param deviceId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TPifDevice getDeviceById(String deviceId) throws DBSystemException {
		Session s = getSession();
		try {
			return (TPifDevice) s.get(TPifDevice.class, Integer.valueOf(deviceId));
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(DevicePersistence.class);
}
