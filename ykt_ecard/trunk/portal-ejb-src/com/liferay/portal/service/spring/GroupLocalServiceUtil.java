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
 * <a href="GroupLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class GroupLocalServiceUtil {
	public static com.liferay.portal.model.Group addGroup(
		java.lang.String companyId, java.lang.String name,
		java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.addGroup(companyId, name, friendlyURL);
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

	public static boolean addRole(java.lang.String groupId,
		java.lang.String roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.addRole(groupId, roleId);
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

	public static boolean addRole(java.lang.String groupId,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.addRole(groupId, role);
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

	public static boolean addRoles(java.lang.String groupId,
		java.lang.String[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.addRoles(groupId, roleIds);
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

	public static boolean addRoles(java.lang.String groupId,
		java.util.List roles)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.addRoles(groupId, roles);
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

	public static boolean addUser(java.lang.String groupId,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.addUser(groupId, userId);
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

	public static boolean addUser(java.lang.String groupId,
		com.liferay.portal.model.User user)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.addUser(groupId, user);
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

	public static boolean addUsers(java.lang.String groupId,
		java.lang.String[] userIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.addUsers(groupId, userIds);
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

	public static boolean addUsers(java.lang.String groupId,
		java.util.List users)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.addUsers(groupId, users);
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

	public static void checkSystemGroups(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();
			groupLocalService.checkSystemGroups(companyId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteGroup(java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();
			groupLocalService.deleteGroup(groupId);
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

	public static boolean deleteRole(java.lang.String groupId,
		java.lang.String roleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.deleteRole(groupId, roleId);
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

	public static boolean deleteRole(java.lang.String groupId,
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.deleteRole(groupId, role);
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

	public static boolean deleteUser(java.lang.String groupId,
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.deleteUser(groupId, userId);
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

	public static boolean deleteUser(java.lang.String groupId,
		com.liferay.portal.model.User user)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.deleteUser(groupId, user);
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

	public static boolean exists(java.lang.String companyId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.exists(companyId, name);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean exists(java.lang.String companyId,
		java.lang.String[] names) throws com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.exists(companyId, names);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portal.model.Group getGroupByFriendlyURL(
		java.lang.String companyId, java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getGroupByFriendlyURL(companyId,
				friendlyURL);
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

	public static com.liferay.portal.model.Group getGroupById(
		java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getGroupById(groupId);
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

	public static com.liferay.portal.model.Group getGroupByName(
		java.lang.String companyId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getGroupByName(companyId, name);
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

	public static java.lang.String getGroupId(java.lang.String companyId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getGroupId(companyId, name);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getLayouts(java.lang.String groupId,
		java.lang.String parentLayoutId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getLayouts(groupId, parentLayoutId);
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

	public static int getLayoutsSize(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getLayoutsSize(groupId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getRoles(java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getRoles(groupId);
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

	public static java.util.List getRoles(java.lang.String groupId, int begin,
		int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getRoles(groupId, begin, end);
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

	public static int getRolesSize(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getRolesSize(groupId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getUsers(java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getUsers(groupId);
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

	public static java.util.List getUsers(java.lang.String groupId, int begin,
		int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getUsers(groupId, begin, end);
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

	public static int getUsersSize(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.getUsersSize(groupId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean removeRoles(java.lang.String groupId,
		java.lang.String[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.removeRoles(groupId, roleIds);
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

	public static boolean removeRoles(java.lang.String groupId,
		java.util.List roles)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.removeRoles(groupId, roles);
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

	public static boolean removeUsers(java.lang.String groupId,
		java.lang.String[] userIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.removeUsers(groupId, userIds);
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

	public static boolean removeUsers(java.lang.String groupId,
		java.util.List users)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.removeUsers(groupId, users);
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

	public static com.liferay.portal.model.Group renameGroupById(
		java.lang.String groupId, java.lang.String newName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.renameGroupById(groupId, newName);
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

	public static com.liferay.portal.model.Group renameGroupByName(
		java.lang.String companyId, java.lang.String oldName,
		java.lang.String newName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.renameGroupByName(companyId, oldName,
				newName);
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

	public static void setLayouts(java.lang.String groupId,
		java.lang.String parentLayoutId, java.lang.String[] layoutIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();
			groupLocalService.setLayouts(groupId, parentLayoutId, layoutIds);
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

	public static void setRoles(java.lang.String groupId,
		java.lang.String[] roleIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();
			groupLocalService.setRoles(groupId, roleIds);
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

	public static void setRoles(java.lang.String groupId, java.util.List roles)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();
			groupLocalService.setRoles(groupId, roles);
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

	public static void setUsers(java.lang.String groupId,
		java.lang.String[] userIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();
			groupLocalService.setUsers(groupId, userIds);
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

	public static void setUsers(java.lang.String groupId, java.util.List users)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();
			groupLocalService.setUsers(groupId, users);
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

	public static com.liferay.portal.model.Group updateFriendlyURL(
		java.lang.String groupId, java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.updateFriendlyURL(groupId, friendlyURL);
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

	public static com.liferay.portal.model.Group updateLookAndFeel(
		java.lang.String groupId, java.lang.String themeId,
		java.lang.String colorSchemeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();

			return groupLocalService.updateLookAndFeel(groupId, themeId,
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

	public static void validate(java.lang.String companyId,
		java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();
			groupLocalService.validate(companyId, name);
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

	public static void validate(java.lang.String groupId,
		java.lang.String companyId, java.lang.String friendlyURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			GroupLocalService groupLocalService = GroupLocalServiceFactory.getService();
			groupLocalService.validate(groupId, companyId, friendlyURL);
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