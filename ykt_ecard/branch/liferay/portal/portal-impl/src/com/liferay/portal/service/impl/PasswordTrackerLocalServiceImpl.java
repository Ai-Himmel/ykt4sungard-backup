/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.model.PasswordTracker;
import com.liferay.portal.model.User;
import com.liferay.portal.security.pwd.PwdEncryptor;
import com.liferay.portal.service.base.PasswordTrackerLocalServiceBaseImpl;

import java.util.Date;
import java.util.Iterator;

/**
 * <a href="PasswordTrackerLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 * @author Scott Lee
 */
public class PasswordTrackerLocalServiceImpl
	extends PasswordTrackerLocalServiceBaseImpl {

	public void deletePasswordTrackers(long userId) throws SystemException {
		passwordTrackerPersistence.removeByUserId(userId);
	}

	public boolean isSameAsCurrentPassword(long userId, String newClearTextPwd)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);

		String currentPwd = user.getPassword();

		if (user.isPasswordEncrypted()) {
			String newEncPwd = PwdEncryptor.encrypt(
				newClearTextPwd, user.getPassword());

			if (currentPwd.equals(newEncPwd)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (currentPwd.equals(newClearTextPwd)) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	public boolean isValidPassword(long userId, String newClearTextPwd)
		throws PortalException, SystemException {

		PasswordPolicy passwordPolicy =
			passwordPolicyLocalService.getPasswordPolicyByUserId(userId);

		if (!passwordPolicy.getHistory()) {
			return true;
		}

		// Check password history

		int historyCount = 1;

		Iterator itr = passwordTrackerPersistence.findByUserId(
			userId).iterator();

		while (itr.hasNext()) {
			if (historyCount > passwordPolicy.getHistoryCount()) {
				break;
			}

			PasswordTracker passwordTracker = (PasswordTracker)itr.next();

			String oldEncPwd = passwordTracker.getPassword();
			String newEncPwd = PwdEncryptor.encrypt(newClearTextPwd, oldEncPwd);

			if (oldEncPwd.equals(newEncPwd)) {
				return false;
			}

			historyCount++;
		}

		return true;
	}

	public void trackPassword(long userId, String encPwd)
		throws PortalException, SystemException {

		long passwordTrackerId = counterLocalService.increment();

		PasswordTracker passwordTracker = passwordTrackerPersistence.create(
			passwordTrackerId);

		passwordTracker.setUserId(userId);
		passwordTracker.setCreateDate(new Date());
		passwordTracker.setPassword(encPwd);

		passwordTrackerPersistence.update(passwordTracker);
	}

}