/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.rmi.RemoteException;

import com.kingstargroup.ecard.exceptions.OldPwdErrorException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.exceptions.UnpairedPwdException;
import com.liferay.portal.PwdEncryptorException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.User;
import com.liferay.portal.security.pwd.PwdEncryptor;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.service.persistence.UserUtil;
import com.liferay.util.Encryptor;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: SystemManagementUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-10-20 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class SystemManagementUtil {

	public static void changePassword(long userId, String oldPwd,
			String newPwd, String confirmPwd) throws PortalException {

		User user = null;
		try {
			user = UserServiceUtil.getUserById(userId);
		} catch (Exception e) {
			throw new PortalException(e);
		}
		if (!newPwd.equals(confirmPwd)) {
			throw new UnpairedPwdException();
		}
		try {
			oldPwd = PwdEncryptor.encrypt(oldPwd);
		} catch (PwdEncryptorException e) {
			throw new PortalException(e);
		}
		if (!user.getPassword().equals(oldPwd)) {
			throw new OldPwdErrorException();
		}
		try {
			UserServiceUtil.updatePassword(userId, newPwd, confirmPwd, false);
		} catch (Exception se) {
			throw new PortalException(se);
		}
	}

}
