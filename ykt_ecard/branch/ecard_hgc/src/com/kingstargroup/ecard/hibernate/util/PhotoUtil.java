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
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-19  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class PhotoUtil extends BasicUtil {
	/**
	 * Description:根据客户类别和学工号得到当前用户照片
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TCifPhoto getPhoto(String stuempNo) throws PortalException {
		PhotoPersistence persistence = (PhotoPersistence) getPersistence(PhotoPersistence.class.getName());
		Transaction t = beginTransaction();
		TCifPhoto photo = null;
		try {
			photo = persistence.getPhoto(stuempNo);
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
