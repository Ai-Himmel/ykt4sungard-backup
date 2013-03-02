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

package com.liferay.portal.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.service.UserServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="UserServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portal.service.UserServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portal.model.UserSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portal.model.User</code>,
 * that is translated to a <code>com.liferay.portal.model.UserSoap</code>.
 * Methods that SOAP cannot safely wire are skipped.
 * </p>
 *
 * <p>
 * The benefits of using the SOAP utility is that it is cross platform
 * compatible. SOAP allows different languages like Java, .NET, C++, PHP, and
 * even Perl, to call the generated services. One drawback of SOAP is that it is
 * slow because it needs to serialize all calls into a text format (XML).
 * </p>
 *
 * <p>
 * You can see a list of services at
 * http://localhost:8080/tunnel-web/secure/axis. Set the property
 * <code>tunnel.servlet.hosts.allowed</code> in portal.properties to configure
 * security.
 * </p>
 *
 * <p>
 * The SOAP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.UserServiceUtil
 * @see com.liferay.portal.service.http.UserServiceHttp
 * @see com.liferay.portal.service.model.UserSoap
 *
 */
public class UserServiceSoap {
	public static void addGroupUsers(long groupId, long[] userIds)
		throws RemoteException {
		try {
			UserServiceUtil.addGroupUsers(groupId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void addOrganizationUsers(long organizationId, long[] userIds)
		throws RemoteException {
		try {
			UserServiceUtil.addOrganizationUsers(organizationId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void addPasswordPolicyUsers(long passwordPolicyId,
		long[] userIds) throws RemoteException {
		try {
			UserServiceUtil.addPasswordPolicyUsers(passwordPolicyId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void addRoleUsers(long roleId, long[] userIds)
		throws RemoteException {
		try {
			UserServiceUtil.addRoleUsers(roleId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void addUserGroupUsers(long userGroupId, long[] userIds)
		throws RemoteException {
		try {
			UserServiceUtil.addUserGroupUsers(userGroupId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap addUser(long companyId,
		boolean autoPassword, java.lang.String password1,
		java.lang.String password2, boolean autoScreenName,
		java.lang.String screenName, java.lang.String emailAddress,
		String locale, java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, int prefixId, int suffixId, boolean male,
		int birthdayMonth, int birthdayDay, int birthdayYear,
		java.lang.String jobTitle, long[] organizationIds, boolean sendEmail)
		throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.addUser(companyId,
					autoPassword, password1, password2, autoScreenName,
					screenName, emailAddress, new java.util.Locale(locale),
					firstName, middleName, lastName, prefixId, suffixId, male,
					birthdayMonth, birthdayDay, birthdayYear, jobTitle,
					organizationIds, sendEmail);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteRoleUser(long roleId, long userId)
		throws RemoteException {
		try {
			UserServiceUtil.deleteRoleUser(roleId, userId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteUser(long userId) throws RemoteException {
		try {
			UserServiceUtil.deleteUser(userId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static long getDefaultUserId(long companyId)
		throws RemoteException {
		try {
			long returnValue = UserServiceUtil.getDefaultUserId(companyId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap[] getGroupUsers(
		long groupId) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getGroupUsers(groupId);

			return com.liferay.portal.model.UserSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap[] getRoleUsers(long roleId)
		throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getRoleUsers(roleId);

			return com.liferay.portal.model.UserSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap getUserByEmailAddress(
		long companyId, java.lang.String emailAddress)
		throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.getUserByEmailAddress(companyId,
					emailAddress);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap getUserById(long userId)
		throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.getUserById(userId);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap getUserByScreenName(
		long companyId, java.lang.String screenName) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.getUserByScreenName(companyId,
					screenName);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static long getUserIdByEmailAddress(long companyId,
		java.lang.String emailAddress) throws RemoteException {
		try {
			long returnValue = UserServiceUtil.getUserIdByEmailAddress(companyId,
					emailAddress);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static long getUserIdByScreenName(long companyId,
		java.lang.String screenName) throws RemoteException {
		try {
			long returnValue = UserServiceUtil.getUserIdByScreenName(companyId,
					screenName);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasGroupUser(long groupId, long userId)
		throws RemoteException {
		try {
			boolean returnValue = UserServiceUtil.hasGroupUser(groupId, userId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasRoleUser(long roleId, long userId)
		throws RemoteException {
		try {
			boolean returnValue = UserServiceUtil.hasRoleUser(roleId, userId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void setRoleUsers(long roleId, long[] userIds)
		throws RemoteException {
		try {
			UserServiceUtil.setRoleUsers(roleId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void setUserGroupUsers(long userGroupId, long[] userIds)
		throws RemoteException {
		try {
			UserServiceUtil.setUserGroupUsers(userGroupId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsetGroupUsers(long groupId, long[] userIds)
		throws RemoteException {
		try {
			UserServiceUtil.unsetGroupUsers(groupId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsetOrganizationUsers(long organizationId,
		long[] userIds) throws RemoteException {
		try {
			UserServiceUtil.unsetOrganizationUsers(organizationId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsetPasswordPolicyUsers(long passwordPolicyId,
		long[] userIds) throws RemoteException {
		try {
			UserServiceUtil.unsetPasswordPolicyUsers(passwordPolicyId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsetRoleUsers(long roleId, long[] userIds)
		throws RemoteException {
		try {
			UserServiceUtil.unsetRoleUsers(roleId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsetUserGroupUsers(long userGroupId, long[] userIds)
		throws RemoteException {
		try {
			UserServiceUtil.unsetUserGroupUsers(userGroupId, userIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap updateActive(long userId,
		boolean active) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateActive(userId,
					active);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap updateAgreedToTermsOfUse(
		long userId, boolean agreedToTermsOfUse) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateAgreedToTermsOfUse(userId,
					agreedToTermsOfUse);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap updateLockout(long userId,
		boolean lockout) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateLockout(userId,
					lockout);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void updateOrganizations(long userId, long[] organizationIds)
		throws RemoteException {
		try {
			UserServiceUtil.updateOrganizations(userId, organizationIds);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap updatePassword(
		long userId, java.lang.String password1, java.lang.String password2,
		boolean passwordReset) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updatePassword(userId,
					password1, password2, passwordReset);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void updatePortrait(long userId, byte[] bytes)
		throws RemoteException {
		try {
			UserServiceUtil.updatePortrait(userId, bytes);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap updateUser(long userId,
		java.lang.String oldPassword, boolean passwordReset,
		java.lang.String screenName, java.lang.String emailAddress,
		java.lang.String languageId, java.lang.String timeZoneId,
		java.lang.String greeting, java.lang.String comments,
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, int prefixId, int suffixId, boolean male,
		int birthdayMonth, int birthdayDay, int birthdayYear,
		java.lang.String smsSn, java.lang.String aimSn, java.lang.String icqSn,
		java.lang.String jabberSn, java.lang.String msnSn,
		java.lang.String skypeSn, java.lang.String ymSn,
		java.lang.String jobTitle, long[] organizationIds)
		throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateUser(userId,
					oldPassword, passwordReset, screenName, emailAddress,
					languageId, timeZoneId, greeting, comments, firstName,
					middleName, lastName, prefixId, suffixId, male,
					birthdayMonth, birthdayDay, birthdayYear, smsSn, aimSn,
					icqSn, jabberSn, msnSn, skypeSn, ymSn, jobTitle,
					organizationIds);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserSoap updateUser(long userId,
		java.lang.String oldPassword, java.lang.String newPassword1,
		java.lang.String newPassword2, boolean passwordReset,
		java.lang.String screenName, java.lang.String emailAddress,
		java.lang.String languageId, java.lang.String timeZoneId,
		java.lang.String greeting, java.lang.String comments,
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, int prefixId, int suffixId, boolean male,
		int birthdayMonth, int birthdayDay, int birthdayYear,
		java.lang.String smsSn, java.lang.String aimSn, java.lang.String icqSn,
		java.lang.String jabberSn, java.lang.String msnSn,
		java.lang.String skypeSn, java.lang.String ymSn,
		java.lang.String jobTitle, long[] organizationIds)
		throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateUser(userId,
					oldPassword, newPassword1, newPassword2, passwordReset,
					screenName, emailAddress, languageId, timeZoneId, greeting,
					comments, firstName, middleName, lastName, prefixId,
					suffixId, male, birthdayMonth, birthdayDay, birthdayYear,
					smsSn, aimSn, icqSn, jabberSn, msnSn, skypeSn, ymSn,
					jobTitle, organizationIds);

			return com.liferay.portal.model.UserSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(UserServiceSoap.class);
}