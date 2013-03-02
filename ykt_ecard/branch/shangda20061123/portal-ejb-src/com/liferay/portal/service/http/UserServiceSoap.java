/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

import com.liferay.portal.service.spring.UserServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="UserServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class UserServiceSoap {
	public static int authenticateByEmailAddress(java.lang.String companyId,
		java.lang.String emailAddress, java.lang.String password)
		throws RemoteException {
		try {
			int returnValue = UserServiceUtil.authenticateByEmailAddress(companyId,
					emailAddress, password);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int authenticateByUserId(java.lang.String companyId,
		java.lang.String userId, java.lang.String password)
		throws RemoteException {
		try {
			int returnValue = UserServiceUtil.authenticateByUserId(companyId,
					userId, password);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.util.KeyValuePair decryptUserId(
		java.lang.String companyId, java.lang.String userId,
		java.lang.String password) throws RemoteException {
		try {
			com.liferay.util.KeyValuePair returnValue = UserServiceUtil.decryptUserId(companyId,
					userId, password);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteUser(java.lang.String userId)
		throws RemoteException {
		try {
			UserServiceUtil.deleteUser(userId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String encryptUserId(java.lang.String userId)
		throws RemoteException {
		try {
			java.lang.String returnValue = UserServiceUtil.encryptUserId(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] findByAnd_C_FN_MN_LN_EA_M_BD_IM_A(
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, java.lang.String emailAddress,
		java.lang.Boolean male, java.util.Date age1, java.util.Date age2,
		java.lang.String im, java.lang.String street1,
		java.lang.String street2, java.lang.String city,
		java.lang.String state, java.lang.String zip, java.lang.String phone,
		java.lang.String fax, java.lang.String cell) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.findByAnd_C_FN_MN_LN_EA_M_BD_IM_A(firstName,
					middleName, lastName, emailAddress, male, age1, age2, im,
					street1, street2, city, state, zip, phone, fax, cell);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] findByC_SMS()
		throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.findByC_SMS();

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] findByOr_C_FN_MN_LN_EA_M_BD_IM_A(
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, java.lang.String emailAddress,
		java.lang.Boolean male, java.util.Date age1, java.util.Date age2,
		java.lang.String im, java.lang.String street1,
		java.lang.String street2, java.lang.String city,
		java.lang.String state, java.lang.String zip, java.lang.String phone,
		java.lang.String fax, java.lang.String cell) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.findByOr_C_FN_MN_LN_EA_M_BD_IM_A(firstName,
					middleName, lastName, emailAddress, male, age1, age2, im,
					street1, street2, city, state, zip, phone, fax, cell);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getCompanyId(java.lang.String userId)
		throws RemoteException {
		try {
			java.lang.String returnValue = UserServiceUtil.getCompanyId(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel getDefaultUser(
		java.lang.String companyId) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.getDefaultUser(companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] getGroups(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getGroups(userId);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] getGroups(
		java.lang.String userId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getGroups(userId,
					begin, end);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getGroupsSize(java.lang.String userId)
		throws RemoteException {
		try {
			int returnValue = UserServiceUtil.getGroupsSize(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] getLayouts(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getLayouts(userId);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] getLayouts(
		java.lang.String userId, java.lang.String parentLayoutId)
		throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getLayouts(userId,
					parentLayoutId);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getLayoutsSize(java.lang.String userId)
		throws RemoteException {
		try {
			int returnValue = UserServiceUtil.getLayoutsSize(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] getProjProjects(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getProjProjects(userId);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] getProjTasks(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getProjTasks(userId);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] getRoles(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getRoles(userId);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel[] getRoles(
		java.lang.String userId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = UserServiceUtil.getRoles(userId,
					begin, end);

			return (com.liferay.portal.model.User[])returnValue.toArray(new com.liferay.portal.model.User[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getRolesSize(java.lang.String userId)
		throws RemoteException {
		try {
			int returnValue = UserServiceUtil.getRolesSize(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel getUserByEmailAddress(
		java.lang.String emailAddress) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.getUserByEmailAddress(emailAddress);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel getUserById(
		java.lang.String userId) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.getUserById(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel getUserById(
		java.lang.String companyId, java.lang.String userId)
		throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.getUserById(companyId,
					userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getUserId(java.lang.String companyId,
		java.lang.String emailAddress) throws RemoteException {
		try {
			java.lang.String returnValue = UserServiceUtil.getUserId(companyId,
					emailAddress);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int notifyNewUsers() throws RemoteException {
		try {
			int returnValue = UserServiceUtil.notifyNewUsers();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void sendPassword(java.lang.String companyId,
		java.lang.String emailAddress) throws RemoteException {
		try {
			UserServiceUtil.sendPassword(companyId, emailAddress);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setGroups(java.lang.String userId,
		java.lang.String[] groupIds) throws RemoteException {
		try {
			UserServiceUtil.setGroups(userId, groupIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setLayouts(java.lang.String userId,
		java.lang.String parentLayoutId, java.lang.String[] layoutIds)
		throws RemoteException {
		try {
			UserServiceUtil.setLayouts(userId, parentLayoutId, layoutIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setProjProjects(java.lang.String userId,
		java.lang.String[] projProjectIds) throws RemoteException {
		try {
			UserServiceUtil.setProjProjects(userId, projProjectIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setProjProjects(java.lang.String userId,
		java.util.List projProjects) throws RemoteException {
		try {
			UserServiceUtil.setProjProjects(userId, projProjects);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setProjTasks(java.lang.String userId,
		java.lang.String[] projTaskIds) throws RemoteException {
		try {
			UserServiceUtil.setProjTasks(userId, projTaskIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setProjTasks(java.lang.String userId,
		java.util.List projTasks) throws RemoteException {
		try {
			UserServiceUtil.setProjTasks(userId, projTasks);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setRoles(java.lang.String userId,
		java.lang.String[] roleIds) throws RemoteException {
		try {
			UserServiceUtil.setRoles(userId, roleIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel updateActive(
		java.lang.String userId, boolean active) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateActive(userId,
					active);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel updateAgreedToTermsOfUse(
		boolean agreedToTermsOfUse) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateAgreedToTermsOfUse(agreedToTermsOfUse);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel updateLastLogin(
		java.lang.String loginIP) throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateLastLogin(loginIP);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel updateLookAndFeel(
		java.lang.String themeId, java.lang.String colorSchemeId)
		throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateLookAndFeel(themeId,
					colorSchemeId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void updatePortrait(java.lang.String userId, byte[] bytes)
		throws RemoteException {
		try {
			UserServiceUtil.updatePortrait(userId, bytes);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel updateUser(
		java.lang.String userId, java.lang.String password1,
		java.lang.String password2, boolean passwordReset)
		throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateUser(userId,
					password1, password2, passwordReset);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.UserModel updateUser(
		java.lang.String userId, java.lang.String password,
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, java.lang.String nickName, boolean male,
		java.util.Date birthday, java.lang.String emailAddress,
		java.lang.String smsId, java.lang.String aimId, java.lang.String icqId,
		java.lang.String msnId, java.lang.String ymId,
		java.lang.String favoriteActivity, java.lang.String favoriteBibleVerse,
		java.lang.String favoriteFood, java.lang.String favoriteMovie,
		java.lang.String favoriteMusic, java.lang.String languageId,
		java.lang.String timeZoneId, java.lang.String themeId,
		java.lang.String colorSchemeId, java.lang.String greeting,
		java.lang.String resolution, java.lang.String comments)
		throws RemoteException {
		try {
			com.liferay.portal.model.User returnValue = UserServiceUtil.updateUser(userId,
					password, firstName, middleName, lastName, nickName, male,
					birthday, emailAddress, smsId, aimId, icqId, msnId, ymId,
					favoriteActivity, favoriteBibleVerse, favoriteFood,
					favoriteMovie, favoriteMusic, languageId, timeZoneId,
					themeId, colorSchemeId, greeting, resolution, comments);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String userId)
		throws RemoteException {
		try {
			boolean returnValue = UserServiceUtil.hasAdmin(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}