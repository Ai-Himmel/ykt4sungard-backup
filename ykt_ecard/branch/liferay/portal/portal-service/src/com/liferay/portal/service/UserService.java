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

package com.liferay.portal.service;


/**
 * <a href="UserService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portal.service.impl.UserServiceImpl</code>.
 * Modify methods in that class and rerun ServiceBuilder to populate this class
 * and all other generated classes.
 * </p>
 *
 * <p>
 * This is a remote service. Methods of this service are expected to have security checks based on the propagated JAAS credentials because this service can be accessed remotely.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.UserServiceFactory
 * @see com.liferay.portal.service.UserServiceUtil
 *
 */
public interface UserService {
	public void addGroupUsers(long groupId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addOrganizationUsers(long organizationId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addPasswordPolicyUsers(long passwordPolicyId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addRoleUsers(long roleId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addUserGroupUsers(long userGroupId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User addUser(long companyId,
		boolean autoPassword, java.lang.String password1,
		java.lang.String password2, boolean autoScreenName,
		java.lang.String screenName, java.lang.String emailAddress,
		java.util.Locale locale, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName, int prefixId,
		int suffixId, boolean male, int birthdayMonth, int birthdayDay,
		int birthdayYear, java.lang.String jobTitle, long[] organizationIds,
		boolean sendEmail)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteRoleUser(long roleId, long userId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteUser(long userId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public long getDefaultUserId(long companyId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getGroupUsers(long groupId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getRoleUsers(long roleId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User getUserByEmailAddress(long companyId,
		java.lang.String emailAddress)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User getUserById(long userId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User getUserByScreenName(long companyId,
		java.lang.String screenName)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public long getUserIdByEmailAddress(long companyId,
		java.lang.String emailAddress)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public long getUserIdByScreenName(long companyId,
		java.lang.String screenName)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public boolean hasGroupUser(long groupId, long userId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public boolean hasRoleUser(long roleId, long userId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void setRoleUsers(long roleId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void setUserGroupUsers(long userGroupId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void unsetGroupUsers(long groupId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void unsetOrganizationUsers(long organizationId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void unsetPasswordPolicyUsers(long passwordPolicyId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void unsetRoleUsers(long roleId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void unsetUserGroupUsers(long userGroupId, long[] userIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User updateActive(long userId,
		boolean active)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User updateAgreedToTermsOfUse(long userId,
		boolean agreedToTermsOfUse)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User updateLockout(long userId,
		boolean lockout)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void updateOrganizations(long userId, long[] organizationIds)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User updatePassword(long userId,
		java.lang.String password1, java.lang.String password2,
		boolean passwordReset)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void updatePortrait(long userId, byte[] bytes)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User updateUser(long userId,
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
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.User updateUser(long userId,
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
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}