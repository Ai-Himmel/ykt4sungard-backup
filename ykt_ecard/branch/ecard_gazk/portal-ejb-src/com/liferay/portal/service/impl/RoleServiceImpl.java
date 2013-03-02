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
import com.liferay.portal.service.persistence.RoleUtil;
import com.liferay.portal.service.spring.RoleLocalServiceUtil;
import com.liferay.portal.service.spring.RoleService;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="RoleServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class RoleServiceImpl extends PrincipalBean implements RoleService {

	// Business methods

	public boolean addGroup(String roleId, Group group)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.addGroup(roleId, group);
	}

	public boolean addGroups(String roleId, List groups)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.addGroups(roleId, groups);
	}

	public Role addRole(String name)
		throws PortalException, SystemException {

		String companyId = getUser().getCompanyId();

		if (!hasAdministrator(companyId)) {
			throw new PrincipalException();
		}

		return RoleLocalServiceUtil.addRole(companyId, name);
	}

	public boolean addUser(String roleId, User user)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.addUser(roleId, user);
	}

	public boolean addUsers(String roleId, List users)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.addUsers(roleId, users);
	}

	public void checkSystemRoles(String companyId) throws SystemException {
		RoleLocalServiceUtil.checkSystemRoles(companyId);
	}

	public boolean deleteGroup(String roleId, Group group)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.removeGroup(roleId, group);
	}

	public void deleteRole(String roleId)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		RoleLocalServiceUtil.deleteRole(roleId);
	}

	public boolean deleteUser(String roleId, User user)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.removeUser(roleId, user);
	}

	public boolean exists(String name) throws PortalException, SystemException {
		return RoleLocalServiceUtil.exists(getUser().getCompanyId(), name);
	}

	public boolean exists(String[] names)
		throws PortalException, SystemException {

		return RoleLocalServiceUtil.exists(getUser().getCompanyId(), names);
	}

	public List getGroups(String roleId)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.getGroups(roleId);
	}

	public List getGroups(String roleId, int begin, int end)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.getGroups(roleId, begin, end);
	}

	public int getGroupsSize(String roleId)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.getGroupsSize(roleId);
	}

	public Role getRoleById(String roleId)
		throws PortalException, SystemException {

		return RoleLocalServiceUtil.getRoleById(roleId);
	}

	public Role getRoleByName(String name)
		throws PortalException, SystemException {

		return RoleLocalServiceUtil.getRoleByName(
			getUser().getCompanyId(), name);
	}

	public List getUsers(String roleId)
		throws PortalException, SystemException {

		Role role = RoleUtil.findByPrimaryKey(roleId);

		if (hasAdministrator(role.getCompanyId())) {
			return RoleUtil.getUsers(roleId);
		}
		else if (getUser().getCompanyId().equals(role.getCompanyId())) {
			List users = new ArrayList();

			Iterator itr = RoleUtil.getUsers(roleId).iterator();

			while (itr.hasNext()) {
				users.add((User)((User)itr.next()).getProtected());
			}

			return users;
		}
		else {
			throw new PrincipalException();
		}
	}

	public List getUsers(String roleId, int begin, int end)
		throws PortalException, SystemException {

		Role role = RoleUtil.findByPrimaryKey(roleId);

		if (hasAdministrator(role.getCompanyId())) {
			return RoleUtil.getUsers(roleId, begin, end);
		}
		else if (getUser().getCompanyId().equals(role.getCompanyId())) {
			List users = new ArrayList();

			Iterator itr = RoleUtil.getUsers(roleId, begin, end).iterator();

			while (itr.hasNext()) {
				users.add((User)((User)itr.next()).getProtected());
			}

			return users;
		}
		else {
			throw new PrincipalException();
		}
	}

	public int getUsersSize(String roleId)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.getUsersSize(roleId);
	}

	public boolean hasRole(String userId, String roleName)
		throws PortalException, SystemException {

		return RoleLocalServiceUtil.hasRole(userId, roleName);
	}

	public boolean hasRoles(String userId, String[] roleNames)
		throws PortalException, SystemException {

		return RoleLocalServiceUtil.hasRoles(userId, roleNames);
	}

	public boolean isAdministrator(String userId)
		throws PortalException, SystemException {

		return RoleLocalServiceUtil.isAdministrator(userId);
	}

	public boolean isGuest(String userId)
		throws PortalException, SystemException {

		return RoleLocalServiceUtil.isGuest(userId);
	}

	public boolean isPowerUser(String userId)
		throws PortalException, SystemException {

		return RoleLocalServiceUtil.isPowerUser(userId);
	}

	public boolean isUser(String userId)
		throws PortalException, SystemException {

		return RoleLocalServiceUtil.isUser(userId);
	}

	public boolean removeGroups(String roleId, String[] groupIds)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.removeGroups(roleId, groupIds);
	}

	public boolean removeUsers(String roleId, String[] userIds)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		return RoleUtil.removeUsers(roleId, userIds);
	}

	public Role renameRoleById(String roleId, String newName)
		throws PortalException, SystemException {

		Role role = RoleUtil.findByPrimaryKey(roleId);

		if (!hasAdministrator(role.getCompanyId())) {
			throw new PrincipalException();
		}

		return RoleLocalServiceUtil.renameRoleById(roleId, newName);
	}

	public Role renameRoleByName(String oldName, String newName)
		throws PortalException, SystemException {

		String companyId = getUser().getCompanyId();

		if (!hasAdministrator(companyId)) {
			throw new PrincipalException();
		}

		return RoleLocalServiceUtil.renameRoleByName(
			companyId, oldName, newName);
	}

	public void setGroups(String roleId, String[] groupIds)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		RoleUtil.setGroups(roleId, groupIds);
	}

	public void setUsers(String roleId, String[] userIds)
		throws PortalException, SystemException {

		if (!hasAdmin(roleId)) {
			throw new PrincipalException();
		}

		RoleUtil.setUsers(roleId, userIds);
	}

	// Permission methods

	public boolean hasAdmin(String roleId)
		throws PortalException, SystemException {

		Role role = RoleUtil.findByPrimaryKey(roleId);

		if (hasAdministrator(role.getCompanyId())) {
			return true;
		}
		else {
			return false;
		}
	}

}