/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.photo.PhotoPersistence;
import com.kingstargroup.ecard.hibernate.photo.TPhoto;

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
public class PhotoUtil {
	/**
	 * Description:根据客户类别和学工号得到当前用户照片
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TPhoto getPhoto(String stuempno) throws PortalException {
			return  getPersistence().getPhoto(stuempno);
	}
	
	public static PhotoPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PhotoPersistence persistence) {
		_persistence = persistence;
	}

	private static PhotoUtil _getUtil() {
		if (_util == null) {
			_util = (PhotoUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PhotoUtil.class.getName();
	private static PhotoUtil _util;
	private PhotoPersistence _persistence;
}
