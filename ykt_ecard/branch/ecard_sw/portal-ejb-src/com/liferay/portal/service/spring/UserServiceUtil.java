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

package com.liferay.portal.service.spring;

/**
 * <a href="UserServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class UserServiceUtil {
	public static boolean addGroup(java.lang.String userId,
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.addGroup(userId, group);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean addRole(java.lang.String userId,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.addRole(userId, role);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User addUser(
		java.lang.String companyId, boolean autoUserId,
		java.lang.String userId, boolean autoPassword,
		java.lang.String password1, java.lang.String password2,
		boolean passwordReset, java.lang.String firstName,
		java.lang.String middleName, java.lang.String lastName,
		java.lang.String nickName, boolean male, java.util.Date birthday,
		java.lang.String emailAddress, java.util.Locale locale)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.addUser(companyId, autoUserId, userId,
				autoPassword, password1, password2, passwordReset, firstName,
				middleName, lastName, nickName, male, birthday, emailAddress,
				locale);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int authenticateByEmailAddress(java.lang.String companyId,
		java.lang.String emailAddress, java.lang.String password)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.authenticateByEmailAddress(companyId,
				emailAddress, password);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int authenticateByUserId(java.lang.String companyId,
		java.lang.String userId, java.lang.String password)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.authenticateByUserId(companyId, userId, password);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.util.KeyValuePair decryptUserId(
		java.lang.String companyId, java.lang.String userId,
		java.lang.String password)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.decryptUserId(companyId, userId, password);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean deleteGroup(java.lang.String userId,
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.deleteGroup(userId, group);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean deleteRole(java.lang.String userId,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.deleteRole(userId, role);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteUser(java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.deleteUser(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.lang.String encryptUserId(java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.encryptUserId(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List findByAnd_C_FN_MN_LN_EA_M_BD_IM_A(
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, java.lang.String emailAddress,
		java.lang.Boolean male, java.util.Date age1, java.util.Date age2,
		java.lang.String im, java.lang.String street1,
		java.lang.String street2, java.lang.String city,
		java.lang.String state, java.lang.String zip, java.lang.String phone,
		java.lang.String fax, java.lang.String cell)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.findByAnd_C_FN_MN_LN_EA_M_BD_IM_A(firstName,
				middleName, lastName, emailAddress, male, age1, age2, im,
				street1, street2, city, state, zip, phone, fax, cell);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List findByC_SMS()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.findByC_SMS();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List findByOr_C_FN_MN_LN_EA_M_BD_IM_A(
		java.lang.String firstName, java.lang.String middleName,
		java.lang.String lastName, java.lang.String emailAddress,
		java.lang.Boolean male, java.util.Date age1, java.util.Date age2,
		java.lang.String im, java.lang.String street1,
		java.lang.String street2, java.lang.String city,
		java.lang.String state, java.lang.String zip, java.lang.String phone,
		java.lang.String fax, java.lang.String cell)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.findByOr_C_FN_MN_LN_EA_M_BD_IM_A(firstName,
				middleName, lastName, emailAddress, male, age1, age2, im,
				street1, street2, city, state, zip, phone, fax, cell);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.lang.String getCompanyId(java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getCompanyId(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User getDefaultUser(
		java.lang.String companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getDefaultUser(companyId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getGroups(java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getGroups(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getGroups(java.lang.String userId, int begin,
		int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getGroups(userId, begin, end);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getGroupsSize(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getGroupsSize(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getLayouts(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getLayouts(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getLayouts(java.lang.String userId,
		java.lang.String parentLayoutId)
		throws com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getLayouts(userId, parentLayoutId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getLayoutsSize(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getLayoutsSize(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getProjProjects(java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getProjProjects(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getProjTasks(java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getProjTasks(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getRoles(java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getRoles(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getRoles(java.lang.String userId, int begin,
		int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getRoles(userId, begin, end);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getRolesSize(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getRolesSize(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User getUserByEmailAddress(
		java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getUserByEmailAddress(emailAddress);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User getUserById(
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getUserById(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User getUserById(
		java.lang.String companyId, java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getUserById(companyId, userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.lang.String getUserId(java.lang.String companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.getUserId(companyId, emailAddress);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int notifyNewUsers()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.notifyNewUsers();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void sendPassword(java.lang.String companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.sendPassword(companyId, emailAddress);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void setGroups(java.lang.String userId,
		java.lang.String[] groupIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.setGroups(userId, groupIds);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void setLayouts(java.lang.String userId,
		java.lang.String parentLayoutId, java.lang.String[] layoutIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.setLayouts(userId, parentLayoutId, layoutIds);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void setProjProjects(java.lang.String userId,
		java.lang.String[] projProjectIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.setProjProjects(userId, projProjectIds);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void setProjProjects(java.lang.String userId,
		java.util.List projProjects)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.setProjProjects(userId, projProjects);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void setProjTasks(java.lang.String userId,
		java.lang.String[] projTaskIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.setProjTasks(userId, projTaskIds);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void setProjTasks(java.lang.String userId,
		java.util.List projTasks)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.setProjTasks(userId, projTasks);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void setRoles(java.lang.String userId,
		java.lang.String[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.setRoles(userId, roleIds);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User updateActive(
		java.lang.String userId, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.updateActive(userId, active);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User updateAgreedToTermsOfUse(
		boolean agreedToTermsOfUse)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.updateAgreedToTermsOfUse(agreedToTermsOfUse);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User updateLastLogin(
		java.lang.String loginIP)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.updateLastLogin(loginIP);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User updateLookAndFeel(
		java.lang.String themeId, java.lang.String colorSchemeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.updateLookAndFeel(themeId, colorSchemeId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void updatePortrait(java.lang.String userId, byte[] bytes)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();
			userService.updatePortrait(userId, bytes);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User updateUser(
		java.lang.String userId, java.lang.String password1,
		java.lang.String password2, boolean passwordReset)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.updateUser(userId, password1, password2,
				passwordReset);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User updateUser(
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
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.updateUser(userId, password, firstName,
				middleName, lastName, nickName, male, birthday, emailAddress,
				smsId, aimId, icqId, msnId, ymId, favoriteActivity,
				favoriteBibleVerse, favoriteFood, favoriteMovie, favoriteMusic,
				languageId, timeZoneId, themeId, colorSchemeId, greeting,
				resolution, comments);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasAdmin(java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserService userService = UserServiceFactory.getService();

			return userService.hasAdmin(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}