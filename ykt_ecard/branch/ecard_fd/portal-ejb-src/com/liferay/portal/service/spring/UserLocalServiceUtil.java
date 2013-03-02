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
 * <a href="UserLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class UserLocalServiceUtil {
	public static boolean addGroup(java.lang.String userId,
		java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.addGroup(userId, groupId);
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

	public static boolean addGroup(java.lang.String userId,
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.addGroup(userId, group);
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
		java.lang.String roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.addRole(userId, roleId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.addRole(userId, role);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.addUser(companyId, autoUserId, userId,
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

	public static boolean deleteGroup(java.lang.String userId,
		java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.deleteGroup(userId, groupId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.deleteGroup(userId, group);
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
		java.lang.String roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.deleteRole(userId, roleId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.deleteRole(userId, role);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.deleteUser(userId);
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

	public static java.util.List findByC_SMS(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.findByC_SMS(companyId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getDefaultUser(companyId);
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

	public static java.util.List getLayouts(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getLayouts(userId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getLayouts(userId, parentLayoutId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getLayoutsSize(userId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getGroups(userId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getGroups(userId, begin, end);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getGroupsSize(userId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getProjProjects(userId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getProjTasks(userId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getRoles(userId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getRoles(userId, begin, end);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getRolesSize(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.User getUserByEmailAddress(
		java.lang.String companyId, java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getUserByEmailAddress(companyId,
				emailAddress);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getUserById(userId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.getUserById(companyId, userId);
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

	public static boolean hasGroupById(java.lang.String userId,
		java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.hasGroupById(userId, groupId);
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

	public static boolean hasGroupByName(java.lang.String companyId,
		java.lang.String userId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.hasGroupByName(companyId, userId, name);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.setGroups(userId, groupIds);
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

	public static void setGroups(java.lang.String userId, java.util.List groups)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.setGroups(userId, groups);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.setLayouts(userId, parentLayoutId, layoutIds);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.setProjProjects(userId, projProjectIds);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.setProjProjects(userId, projProjects);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.setProjTasks(userId, projTaskIds);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.setProjTasks(userId, projTasks);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.setRoles(userId, roleIds);
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

	public static void setRoles(java.lang.String userId, java.util.List roles)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.setRoles(userId, roles);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.updateActive(userId, active);
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
		java.lang.String userId, java.lang.String themeId,
		java.lang.String colorSchemeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.updateLookAndFeel(userId, themeId,
				colorSchemeId);
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.updateUser(userId, password1, password2,
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
			UserLocalService userLocalService = UserLocalServiceFactory.getService();

			return userLocalService.updateUser(userId, password, firstName,
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

	public static void validate(java.lang.String companyId, boolean autoUserId,
		java.lang.String userId, boolean autoPassword,
		java.lang.String password1, java.lang.String password2,
		java.lang.String firstName, java.lang.String lastName,
		java.lang.String emailAddress)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.validate(companyId, autoUserId, userId,
				autoPassword, password1, password2, firstName, lastName,
				emailAddress);
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

	public static void validate(java.lang.String userId,
		java.lang.String password1, java.lang.String password2)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.validate(userId, password1, password2);
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

	public static void validate(java.lang.String userId,
		java.lang.String firstName, java.lang.String lastName,
		java.lang.String emailAddress, java.lang.String smsId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			UserLocalService userLocalService = UserLocalServiceFactory.getService();
			userLocalService.validate(userId, firstName, lastName,
				emailAddress, smsId);
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