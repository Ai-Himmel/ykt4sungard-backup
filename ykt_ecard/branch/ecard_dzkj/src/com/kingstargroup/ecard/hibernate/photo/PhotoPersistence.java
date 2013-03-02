/**
 * 
 */
package com.kingstargroup.ecard.hibernate.photo;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PhotoPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-10-19  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class PhotoPersistence extends BasicPersistence {
	public TCifPhoto getPhoto(String stuempNo) throws DBSystemException {
		Session s = getSession();
		try {
			return (TCifPhoto) s.get(TCifPhoto.class, stuempNo);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(PhotoPersistence.class);
}
