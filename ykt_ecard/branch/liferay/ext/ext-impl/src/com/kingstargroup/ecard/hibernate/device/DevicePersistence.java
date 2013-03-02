/**
 * 
 */
package com.kingstargroup.ecard.hibernate.device;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.service.persistence.BasePersistence;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: DevicePersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class DevicePersistence extends BasePersistence {

	/**
	 * Description: �����豸ID�õ���Ӧ���豸����
	 * @param deviceId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TDevice getDeviceById(String deviceid) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			return (TDevice) s.get(TDevice.class, Long.valueOf(deviceid));
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally{
			closeSession(s);
		}
	}
	
	public VTerm getVTermById(String termid) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			return (VTerm) s.get(VTerm.class, Long.valueOf(termid));
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally{
			closeSession(s);
		}
	}
	
	private static final Log _log = LogFactory.getLog(DevicePersistence.class);
}
