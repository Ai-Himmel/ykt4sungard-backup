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
import com.liferay.portal.RequiredUserException;
import com.liferay.portal.ReservedUserEmailAddressException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.base.UserServiceBaseImpl;
import com.liferay.portal.service.permission.GroupPermissionUtil;
import com.liferay.portal.service.permission.OrganizationPermissionUtil;
import com.liferay.portal.service.permission.PasswordPolicyPermissionUtil;
import com.liferay.portal.service.permission.RolePermissionUtil;
import com.liferay.portal.service.permission.UserGroupPermissionUtil;
import com.liferay.portal.service.permission.UserPermissionUtil;

import java.util.List;
import java.util.Locale;

/**
 * <a href="UserServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brian Myunghun Kim
 * @author Scott Lee
 * @author Jorge Ferrer
 *
 */
public class UserServiceImpl extends UserServiceBaseImpl {

	public void addGroupUsers(long groupId, long[] userIds)
		throws PortalException, SystemException {

		try {
			GroupPermissionUtil.check(
				getPermissionChecker(), groupId, ActionKeys.ASSIGN_MEMBERS);
		}
		catch (PrincipalException pe) {

			// Allow any user to join open communities

			boolean hasPermission = false;

			if (userIds.length == 0) {
				hasPermission = true;
			}
			else if (userIds.length == 1) {
				User user = getUser();

				if (user.getUserId() == userIds[0]) {
					Group group = groupPersistence.findByPrimaryKey(groupId);

					if (user.getCompanyId() == group.getCompanyId()) {
						int type = group.getType();

						if (type == GroupImpl.TYPE_COMMUNITY_OPEN) {
							hasPermission = true;
						}
					}
				}
			}

			if (!hasPermission) {
				throw new PrincipalException();
			}
		}

		userLocalService.addGroupUsers(groupId, userIds);
	}

	public void addOrganizationUsers(long organizationId, long[] userIds)
		throws PortalException, SystemException {

		OrganizationPermissionUtil.check(
			getPermissionChecker(), organizationId, ActionKeys.ASSIGN_MEMBERS);

		userLocalService.addOrganizationUsers(organizationId, userIds);
	}

	public void addPasswordPolicyUsers(long passwordPolicyId, long[] userIds)
		throws PortalException, SystemException {

		PasswordPolicyPermissionUtil.check(
			getPermissionChecker(), passwordPolicyId,
			ActionKeys.ASSIGN_MEMBERS);

		userLocalService.addPasswordPolicyUsers(passwordPolicyId, userIds);
	}

	public void addRoleUsers(long roleId, long[] userIds)
		throws PortalException, SystemException {

		RolePermissionUtil.check(
			getPermissionChecker(), roleId, ActionKeys.ASSIGN_MEMBERS);

		userLocalService.addRoleUsers(roleId, userIds);
	}

	public void addUserGroupUsers(long userGroupId, long[] userIds)
		throws PortalException, SystemException {

		UserGroupPermissionUtil.check(
			getPermissionChecker(), userGroupId, ActionKeys.ASSIGN_MEMBERS);

		userLocalService.addUserGroupUsers(userGroupId, userIds);
	}

	public User addUser(
			long companyId, boolean autoPassword, String password1,
			String password2, boolean autoScreenName, String screenName,
			String emailAddress, Locale locale, String firstName,
			String middleName, String lastName, int prefixId, int suffixId,
			boolean male, int birthdayMonth, int birthdayDay, int birthdayYear,
			String jobTitle, long[] organizationIds, boolean sendEmail)
		throws PortalException, SystemException {

		Company company = companyPersistence.findByPrimaryKey(companyId);

		if (!company.isStrangers()) {
			checkPermission(0, organizationIds, ActionKeys.ADD_USER);
		}

		long creatorUserId = 0;

		try {
			creatorUserId = getUserId();
		}
		catch (PrincipalException pe) {
		}

		if (creatorUserId == 0) {
			if (!company.isStrangersWithMx() &&
				company.hasCompanyMx(emailAddress)) {

				throw new ReservedUserEmailAddressException();
			}
		}

		return userLocalService.addUser(
			creatorUserId, companyId, autoPassword, password1, password2,
			autoScreenName, screenName, emailAddress, locale, firstName,
			middleName, lastName, prefixId, suffixId, male, birthdayMonth,
			birthdayDay, birthdayYear, jobTitle, organizationIds, sendEmail);
	}

	public void deleteRoleUser(long roleId, long userId)
		throws PortalException, SystemException {

		RolePermissionUtil.check(
			getPermissionChecker(), roleId, ActionKeys.ASSIGN_MEMBERS);

		userLocalService.deleteRoleUser(roleId, userId);
	}

	public void deleteUser(long userId)
		throws PortalException, SystemException {

		if (getUserId() == userId) {
			throw new RequiredUserException();
		}

		checkPermission(userId, ActionKeys.DELETE);

		userLocalService.deleteUser(userId);
	}

	public long getDefaultUserId(long companyId)
		throws PortalException, SystemException {

		return userLocalService.getDefaultUserId(companyId);
	}

	public List getGroupUsers(long groupId)
		throws PortalException, SystemException {

		return userLocalService.getGroupUsers(groupId);
	}

	public List getRoleUsers(long roleId)
		throws PortalException, SystemException {

		return userLocalService.getRoleUsers(roleId);
	}

	public User getUserByEmailAddress(long companyId, String emailAddress)
		throws PortalException, SystemException {

		User user = userLocalService.getUserByEmailAddress(
			companyId, emailAddress);

		checkPermission(user.getUserId(), ActionKeys.VIEW);

		return user;
	}

	public User getUserById(long userId)
		throws PortalException, SystemException {

		User user = userLocalService.getUserById(userId);

		checkPermission(user.getUserId(), ActionKeys.VIEW);

		return user;
	}

	public User getUserByScreenName(long companyId, String screenName)
		throws PortalException, SystemException {

		User user = userLocalService.getUserByScreenName(
			companyId, screenName);

		checkPermission(user.getUserId(), ActionKeys.VIEW);

		return user;
	}

	public long getUserIdByEmailAddress(long companyId, String emailAddress)
		throws PortalException, SystemException {

		User user = getUserByEmailAddress(companyId, emailAddress);

		return user.getUserId();
	}

	public long getUserIdByScreenName(long companyId, String screenName)
		throws PortalException, SystemException {

		User user = getUserByScreenName(companyId, screenName);

		return user.getUserId();
	}

	public boolean hasGroupUser(long groupId, long userId)
		throws PortalException, SystemException {

		return userLocalService.hasGroupUser(groupId, userId);
	}

	public boolean hasRoleUser(long roleId, long userId)
		throws PortalException, SystemException {

		return userLocalService.hasRoleUser(roleId, userId);
	}

	public void setRoleUsers(long roleId, long[] userIds)
		throws PortalException, SystemException {

		RolePermissionUtil.check(
			getPermissionChecker(), roleId, ActionKeys.ASSIGN_MEMBERS);

		userLocalService.setRoleUsers(roleId, userIds);
	}

	public void setUserGroupUsers(long userGroupId, long[] userIds)
		throws PortalException, SystemException {

		UserGroupPermissionUtil.check(
			getPermissionChecker(), userGroupId, ActionKeys.ASSIGN_MEMBERS);

		userLocalService.setUserGroupUsers(userGroupId, userIds);
	}

	public void unsetGroupUsers(long groupId, long[] userIds)
		throws PortalException, SystemException {

		try {
			GroupPermissionUtil.check(
				getPermissionChecker(), groupId, ActionKeys.ASSIGN_MEMBERS);
		}
		catch (PrincipalException pe) {

			// Allow any user to leave open and restricted communities

			boolean hasPermission = false;

			if (userIds.length == 0) {
				hasPermission = true;
			}
			else if (userIds.length == 1) {
				User user = getUser();

				if (user.getUserId() == userIds[0]) {
					Group group = groupPersistence.findByPrimaryKey(groupId);

					if (user.getCompanyId() == group.getCompanyId()) {
						int type = group.getType();

						if ((type == GroupImpl.TYPE_COMMUNITY_OPEN) ||
							(type == GroupImpl.TYPE_COMMUNITY_RESTRICTED)) {

							hasPermission = true;
						}
					}
				}
			}

			if (!hasPermission) {
				throw new PrincipalException();
			}
		}

		userLocalService.unsetGroupUsers(groupId, userIds);
	}

	public void unsetOrganizationUsers(long organizationId, long[] userIds)
		throws PortalException, SystemException {

		OrganizationPermissionUtil.check(
			getPermissionChecker(), organizationId, ActionKeys.ASSIGN_MEMBERS);

		userLocalService.unsetOrganizationUsers(organizationId, userIds);
	}

	public void unsetPasswordPolicyUsers(long passwordPolicyId, long[] userIds)
		throws PortalException, SystemException {

		PasswordPolicyPermissionUtil.check(
			getPermissionChecker(), passwordPolicyId,
			ActionKeys.ASSIGN_MEMBERS);

		userLocalService.unsetPasswordPolicyUsers(passwordPolicyId, userIds);
	}

	public void unsetRoleUsers(long roleId, long[] userIds)
		throws PortalException, SystemException {

		RolePermissionUtil.check(
			getPermissionChecker(), roleId, ActionKeys.ASSIGN_MEMBERS);

		userLocalService.unsetRoleUsers(roleId, userIds);
	}

	public void unsetUserGroupUsers(long userGroupId, long[] userIds)
		throws PortalException, SystemException {

		UserGroupPermissionUtil.check(
			getPermissionChecker(), userGroupId, ActionKeys.ASSIGN_MEMBERS);

		userLocalService.unsetUserGroupUsers(userGroupId, userIds);
	}

	public User updateActive(long userId, boolean active)
		throws PortalException, SystemException {

		if ((getUserId() == userId) && !active) {
			throw new RequiredUserException();
		}

		checkPermission(userId, ActionKeys.DELETE);

		return userLocalService.updateActive(userId, active);
	}

	public User updateAgreedToTermsOfUse(
			long userId, boolean agreedToTermsOfUse)
		throws PortalException, SystemException {

		checkPermission(userId, ActionKeys.UPDATE);

		return userLocalService.updateAgreedToTermsOfUse(
			userId, agreedToTermsOfUse);
	}

	public User updateLockout(long userId, boolean lockout)
		throws PortalException, SystemException {

		checkPermission(userId, ActionKeys.DELETE);

		return userLocalService.updateLockoutById(userId, lockout);
	}

	public void updateOrganizations(long userId, long[] organizationIds)
		throws PortalException, SystemException {

		checkPermission(userId, ActionKeys.UPDATE);

		userLocalService.updateOrganizations(userId, organizationIds);
	}

	public User updatePassword(
			long userId, String password1, String password2,
			boolean passwordReset)
		throws PortalException, SystemException {

		checkPermission(userId, ActionKeys.UPDATE);

		return userLocalService.updatePassword(
			userId, password1, password2, passwordReset);
	}

	public void updatePortrait(long userId, byte[] bytes)
		throws PortalException, SystemException {

		checkPermission(userId, ActionKeys.UPDATE);

		userLocalService.updatePortrait(userId, bytes);
	}

	public User updateUser(
			long userId, String oldPassword, boolean passwordReset,
			String screenName, String emailAddress, String languageId,
			String timeZoneId, String greeting, String comments,
			String firstName, String middleName, String lastName, int prefixId,
			int suffixId, boolean male, int birthdayMonth, int birthdayDay,
			int birthdayYear, String smsSn, String aimSn, String icqSn,
			String jabberSn, String msnSn, String skypeSn, String ymSn,
			String jobTitle, long[] organizationIds)
		throws PortalException, SystemException {

		String newPassword1 = StringPool.BLANK;
		String newPassword2 = StringPool.BLANK;

		return updateUser(
			userId, oldPassword, newPassword1, newPassword2, passwordReset,
			screenName, emailAddress, languageId, timeZoneId, greeting,
			comments, firstName, middleName, lastName, prefixId, suffixId, male,
			birthdayMonth, birthdayDay, birthdayYear, smsSn, aimSn, icqSn,
			jabberSn, msnSn, skypeSn, ymSn, jobTitle, organizationIds);
	}

	public User updateUser(
			long userId, String oldPassword, String newPassword1,
			String newPassword2, boolean passwordReset, String screenName,
			String emailAddress, String languageId, String timeZoneId,
			String greeting, String comments, String firstName,
			String middleName, String lastName, int prefixId, int suffixId,
			boolean male, int birthdayMonth, int birthdayDay, int birthdayYear,
			String smsSn, String aimSn, String icqSn, String jabberSn,
			String msnSn, String skypeSn, String ymSn, String jobTitle,
			long[] organizationIds)
		throws PortalException, SystemException {

		checkPermission(userId, organizationIds, ActionKeys.UPDATE);

		long curUserId = getUserId();

		if (curUserId == userId) {
			emailAddress = emailAddress.trim().toLowerCase();

			User user = userPersistence.findByPrimaryKey(userId);

			if (!emailAddress.equalsIgnoreCase(user.getEmailAddress())) {
				if (!user.hasCompanyMx() && user.hasCompanyMx(emailAddress)) {
					Company company = companyPersistence.findByPrimaryKey(
						user.getCompanyId());

					if (!company.isStrangersWithMx()) {
						throw new ReservedUserEmailAddressException();
					}
				}
			}
		}

		return userLocalService.updateUser(
			userId, oldPassword, newPassword1, newPassword2, passwordReset,
			screenName, emailAddress, languageId, timeZoneId, greeting,
			comments, firstName, middleName, lastName, prefixId, suffixId, male,
			birthdayMonth, birthdayDay, birthdayYear, smsSn, aimSn, icqSn,
			jabberSn, msnSn, skypeSn, ymSn, jobTitle, organizationIds);
	}

	protected void checkPermission(long userId, String actionId)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);

		checkPermission(userId, user.getOrganizationIds(), actionId);
	}

	protected void checkPermission(
			long userId, long[] organizationIds, String actionId)
		throws PortalException, SystemException {

		UserPermissionUtil.check(
			getPermissionChecker(), userId, organizationIds, actionId);
	}

}