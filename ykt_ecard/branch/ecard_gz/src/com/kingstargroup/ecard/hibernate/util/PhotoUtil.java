/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.photo.PhotoPersistence;
import com.kingstargroup.ecard.hibernate.photo.TCifPhoto;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PhotoUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-10-19  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class PhotoUtil extends BasicUtil {
	/**
	 * Description:���ݿͻ�����ѧ���ŵõ���ǰ�û���Ƭ
	 * @param cutId
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TCifPhoto getPhoto(String cutId) throws PortalException {
		PhotoPersistence persistence = (PhotoPersistence) getPersistence(PhotoPersistence.class.getName());
		Transaction t = beginTransaction();
		TCifPhoto photo = null;
		try {
			photo = persistence.getPhotobyCutId(cutId);
			t.commit();
		} catch (PortalException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return photo;
	}
}
