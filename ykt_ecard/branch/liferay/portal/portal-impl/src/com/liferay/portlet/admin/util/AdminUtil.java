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

package com.liferay.portlet.admin.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.util.PortalUtil;

import java.rmi.RemoteException;

import java.util.Calendar;

import javax.portlet.ActionRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="AdminUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class AdminUtil {

	public static String getUpdateUserPassword(
		HttpServletRequest req, long userId) {

		String password = PortalUtil.getUserPassword(req);

		if (userId != PortalUtil.getUserId(req)) {
			password = StringPool.BLANK;
		}

		return password;
	}

	public static String getUpdateUserPassword(ActionRequest req, long userId) {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		return getUpdateUserPassword(httpReq, userId);
	}

	public static User updateUser(
			HttpServletRequest req, long userId, String screenName,
			String emailAddress, String languageId, String timeZoneId,
			String greeting, String comments, String smsSn, String aimSn,
			String icqSn, String jabberSn, String msnSn, String skypeSn,
			String ymSn)
		throws PortalException, RemoteException, SystemException {

		String password = getUpdateUserPassword(req, userId);

		User user = UserLocalServiceUtil.getUserById(userId);

		Contact contact = user.getContact();

		Calendar birthdayCal = CalendarFactoryUtil.getCalendar();

		birthdayCal.setTime(contact.getBirthday());

		int birthdayMonth = birthdayCal.get(Calendar.MONTH);
		int birthdayDay = birthdayCal.get(Calendar.DATE);
		int birthdayYear = birthdayCal.get(Calendar.YEAR);

		return UserServiceUtil.updateUser(
			userId, password, user.isPasswordReset(), screenName, emailAddress,
			languageId, timeZoneId, greeting, comments, contact.getFirstName(),
			contact.getMiddleName(), contact.getLastName(),
			contact.getPrefixId(), contact.getSuffixId(), contact.isMale(),
			birthdayMonth, birthdayDay, birthdayYear, smsSn, aimSn, icqSn,
			jabberSn, msnSn, skypeSn, ymSn, contact.getJobTitle(),
			user.getOrganizationIds());
	}

	public static User updateUser(
			ActionRequest req, long userId, String screenName,
			String emailAddress, String languageId, String timeZoneId,
			String greeting, String comments, String smsSn, String aimSn,
			String icqSn, String jabberSn, String msnSn, String skypeSn,
			String ymSn)
		throws PortalException, RemoteException, SystemException {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		return updateUser(
			httpReq, userId, screenName, emailAddress, languageId, timeZoneId,
			greeting, comments, smsSn, aimSn, icqSn, jabberSn, msnSn, skypeSn,
			ymSn);
	}

}