/**
 * 
 */
package com.kingstargroup.ecard.hibernate.area;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AreaPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-27  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AreaPersistence extends BasePersistence {

	/**
	 * Description:���ݵ���ID�õ���������
	 * @param areaId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public TArea getAreaBycode(String areacode) throws DBSystemException {
		Session s = openSession();
		try {
			return (TArea) s.get(TArea.class, Integer.valueOf(areacode));
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}finally{
			closeSession(s);
		}
	}
	
	private static final Log _log = LogFactory.getLog(AreaPersistence.class);
}
