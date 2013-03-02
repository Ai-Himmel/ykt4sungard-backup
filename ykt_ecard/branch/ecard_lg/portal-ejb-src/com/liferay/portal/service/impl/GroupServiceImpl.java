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

package com.liferay.portal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.GroupUtil;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.GroupService;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="GroupServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class GroupServiceImpl extends PrincipalBean implements GroupService {

	// Business methods

	public Group addGroup(String name, String friendlyURL)
		throws PortalException, SystemException {

		String companyId = getUser().getCompanyId();

		if (!hasAdministrator(companyId)) {
			throw new PrincipalException();
		}

		return GroupLocalServiceUtil.addGroup(companyId, name, friendlyURL);
	}

	public boolean addRole(String groupId, Role role)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.addRole(groupId, role);
	}

	public boolean addRoles(String groupId, List roles)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.addRoles(groupId, roles);
	}

	public boolean addUser(String groupId, User user)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.addUser(groupId, user);
	}

	public boolean addUsers(String groupId, List users)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.addUsers(groupId, users);
	}

	public void deleteGroup(String groupId)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		GroupLocalServiceUtil.deleteGroup(groupId);
	}

	public boolean deleteRole(String groupId, Role role)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.removeRole(groupId, role);
	}

	public boolean deleteUser(String groupId, User user)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.removeUser(groupId, user);
	}

	public boolean exists(String name)
		throws PortalException, SystemException {

		return GroupLocalServiceUtil.exists(getUser().getCompanyId(), name);
	}

	public Group getGroupById(String groupId)
		throws PortalException, SystemException {

		return GroupLocalServiceUtil.getGroupById(groupId);
	}

	public Group getGroupByName(String name)
		throws PortalException, SystemException {

		return GroupLocalServiceUtil.getGroupByName(
			getUser().getCompanyId(), name);
	}

	public List getLayouts(String groupId, String parentLayoutId)
		throws PortalException, SystemException {

		return GroupLocalServiceUtil.getLayouts(groupId, parentLayoutId);
	}

	public int getLayoutsSize(String groupId) throws SystemException {
		return GroupLocalServiceUtil.getLayoutsSize(groupId);
	}

	public List getRoles(String groupId)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.getRoles(groupId);
	}

	public List getRoles(String groupId, int begin, int end)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.getRoles(groupId, begin, end);
	}

	public int getRolesSize(String groupId)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.getRolesSize(groupId);
	}

	public List getUsers(String groupId)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		if (hasAdministrator(group.getCompanyId())) {
			return GroupUtil.getUsers(groupId);
		}
		else if (getUser().getCompanyId().equals(group.getCompanyId())) {
			List users = new ArrayList();

			Iterator itr = GroupUtil.getUsers(groupId).iterator();

			while (itr.hasNext()) {
				users.add((User)((User)itr.next()).getProtected());
			}

			return users;
		}
		else {
			throw new PrincipalException();
		}
	}

	public List getUsers(String groupId, int begin, int end)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		if (hasAdministrator(group.getCompanyId())) {
			return GroupUtil.getUsers(groupId, begin, end);
		}
		else if (getUser().getCompanyId().equals(group.getCompanyId())) {
			List users = new ArrayList();

			Iterator itr = GroupUtil.getUsers(groupId, begin, end).iterator();

			while (itr.hasNext()) {
				users.add((User)((User)itr.next()).getProtected());
			}

			return users;
		}
		else {
			throw new PrincipalException();
		}
	}

	public int getUsersSize(String groupId)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.getUsersSize(groupId);
	}

	public boolean removeRoles(String groupId, String[] roleIds)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupUtil.removeRoles(groupId, roleIds);
	}

	public boolean removeUsers(String groupId, String[] userIds)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return  GroupUtil.removeUsers(groupId, userIds);
	}

	public Group renameGroupById(String groupId, String newName)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		if (!hasAdministrator(group.getCompanyId())) {
			throw new PrincipalException();
		}

		return GroupLocalServiceUtil.renameGroupById(groupId, newName);
	}

	public Group renameGroupByName(String oldName, String newName)
		throws PortalException, SystemException {

		String companyId = getUser().getCompanyId();

		if (!hasAdministrator(companyId)) {
			throw new PrincipalException();
		}

		return GroupLocalServiceUtil.renameGroupByName(
			companyId, oldName, newName);
	}

	public void setLayouts(
			String groupId, String parentLayoutId, String[] layoutIds)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		if (!hasAdministrator(group.getCompanyId())) {
			throw new PrincipalException();
		}

		GroupLocalServiceUtil.setLayouts(groupId, parentLayoutId, layoutIds);
	}

	public void setRoles(String groupId, String[] roleIds)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		GroupUtil.setRoles(groupId, roleIds);
	}

	public void setUsers(String groupId, String[] userIds)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		GroupUtil.setUsers(groupId, userIds);
	}

	public Group updateFriendlyURL(String groupId, String friendlyURL)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupLocalServiceUtil.updateFriendlyURL(groupId, friendlyURL);
	}

	public Group updateLookAndFeel(
			String groupId, String themeId, String colorSchemeId)
		throws PortalException, SystemException {

		if (!hasAdmin(groupId)) {
			throw new PrincipalException();
		}

		return GroupLocalServiceUtil.updateLookAndFeel(
			groupId, themeId, colorSchemeId);
	}

	// Permission methods

	public boolean hasAdmin(String groupId)
		throws PortalException, SystemException {

		Group group = GroupUtil.findByPrimaryKey(groupId);

		if (hasAdministrator(group.getCompanyId())) {
			return true;
		}
		else {
			return false;
		}
	}

}