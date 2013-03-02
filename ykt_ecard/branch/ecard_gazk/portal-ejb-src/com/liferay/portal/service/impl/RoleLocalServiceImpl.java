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

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.DuplicateRoleException;
import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.NoSuchRoleException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PortalException;
import com.liferay.portal.RequiredRoleException;
import com.liferay.portal.RoleNameException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.GroupUtil;
import com.liferay.portal.service.persistence.RoleUtil;
import com.liferay.portal.service.persistence.UserUtil;
import com.liferay.portal.service.spring.RoleLocalService;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.SimpleCachePool;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * <a href="RoleLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class RoleLocalServiceImpl implements RoleLocalService {

	// Business methods

	public boolean addGroup(String roleId, String groupId)
		throws PortalException, SystemException {

		return RoleUtil.addGroup(roleId, groupId);
	}

	public boolean addGroup(String roleId, Group group)
		throws PortalException, SystemException {

		return RoleUtil.addGroup(roleId, group);
	}

	public boolean addGroups(String roleId, String[] groupIds)
		throws PortalException, SystemException {

		return RoleUtil.addGroups(roleId, groupIds);
	}

	public boolean addGroups(String roleId, List groups)
		throws PortalException, SystemException {

		return RoleUtil.addGroups(roleId, groups);
	}

	public Role addRole(String companyId, String name)
		throws PortalException, SystemException {

		validate(companyId, name);

		String roleId = Long.toString(CounterServiceUtil.increment(
			Role.class.getName()));

		Role role = RoleUtil.create(roleId);

		role.setCompanyId(companyId);
		role.setName(name);

		RoleUtil.update(role);

		return role;
	}

	public boolean addUser(String roleId, String userId)
		throws PortalException, SystemException {

		return RoleUtil.addUser(roleId, userId);
	}

	public boolean addUser(String roleId, User user)
		throws PortalException, SystemException {

		return RoleUtil.addUser(roleId, user);
	}

	public boolean addUsers(String roleId, String[] userIds)
		throws PortalException, SystemException {

		return RoleUtil.addUsers(roleId, userIds);
	}

	public boolean addUsers(String roleId, List users)
		throws PortalException, SystemException {

		return RoleUtil.addUsers(roleId, users);
	}

	public void checkSystemRoles(String companyId) throws SystemException {
		Set existingRoles = CollectionFactory.getHashSet();

		Iterator itr = RoleUtil.findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			Role role = (Role)itr.next();

			existingRoles.add(role.getName());
		}

		String[] systemRoles = PortalUtil.getSystemRoles();

		for (int i = 0; i < systemRoles.length; i++) {
			if (!existingRoles.contains(systemRoles[i])) {

				// Add system role

				String roleId = Long.toString(CounterServiceUtil.increment(
					Role.class.getName()));

				Role role = RoleUtil.create(roleId);

				role.setCompanyId(companyId);
				role.setName(systemRoles[i]);

				RoleUtil.update(role);
			}
		}
	}

	public boolean deleteGroup(String roleId, String groupId)
		throws PortalException, SystemException {

		return RoleUtil.removeGroup(roleId, groupId);
	}

	public boolean deleteGroup(String roleId, Group group)
		throws PortalException, SystemException {

		return RoleUtil.removeGroup(roleId, group);
	}

	public void deleteRole(String roleId)
		throws PortalException, SystemException {

		Role role = RoleUtil.findByPrimaryKey(roleId);

		if (PortalUtil.isSystemRole(role.getName())) {
			throw new RequiredRoleException();
		}

		RoleUtil.remove(roleId);
	}

	public boolean deleteUser(String roleId, String userId)
		throws PortalException, SystemException {

		return RoleUtil.removeUser(roleId, userId);
	}

	public boolean deleteUser(String roleId, User user)
		throws PortalException, SystemException {

		return RoleUtil.removeUser(roleId, user);
	}

	public boolean exists(String companyId, String name)
		throws SystemException {

		Iterator itr = RoleUtil.findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			Role role = (Role)itr.next();

			if (role.getName().equalsIgnoreCase(name)) {
				return true;
			}
		}

		return false;
	}

	public boolean exists(String companyId, String[] names)
		throws SystemException {

		for (int i = 0; i < names.length; i++) {
			if (!exists(companyId, names[i])) {
				return false;
			}
		}

		return true;
	}

	public List getGroups(String roleId)
		throws PortalException, SystemException {

		return RoleUtil.getGroups(roleId);
	}

	public List getGroups(String roleId, int begin, int end)
		throws PortalException, SystemException {

		return RoleUtil.getGroups(roleId, begin, end);
	}

	public int getGroupsSize(String roleId) throws SystemException {
		return RoleUtil.getGroupsSize(roleId);
	}

	public Role getRoleById(String roleId)
		throws PortalException, SystemException {

		return RoleUtil.findByPrimaryKey(roleId);
	}

	public Role getRoleByName(String companyId, String name)
		throws PortalException, SystemException {

		if (PortalUtil.isSystemRole(name)) {
			Map rolesPool = _getRolesPool(companyId);

			Role role = (Role)rolesPool.get(name);

			if (role == null) {
				role = RoleUtil.findByC_N(companyId, name);

				rolesPool.put(name, role);
			}

			return role;
		}
		else {
			return RoleUtil.findByC_N(companyId, name);
		}
	}

	public String getRoleId(String companyId, String name)
		throws SystemException {

		Iterator itr = RoleUtil.findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			Role role = (Role)itr.next();

			if (role.getName().equalsIgnoreCase(name)) {
				return role.getRoleId();
			}
		}

		return null;
	}

	public List getUsers(String roleId)
		throws PortalException, SystemException {

		return RoleUtil.getUsers(roleId);
	}

	public List getUsers(String roleId, int begin, int end)
		throws PortalException, SystemException {

		return RoleUtil.getUsers(roleId, begin, end);
	}

	public int getUsersSize(String roleId) throws SystemException {
		return RoleUtil.getUsersSize(roleId);
	}

	public boolean hasRole(String userId, String roleName)
		throws PortalException, SystemException {

		return hasRole(userId, null, roleName);
	}

	public boolean hasRole(String userId, List userRoles, String roleName)
		throws PortalException, SystemException {

		User user = UserUtil.findByPrimaryKey(userId);

		// Check for default user

		if (user.isDefaultUser()) {
			if (roleName.equalsIgnoreCase(Role.GUEST)) {
				return true;
			}
			else {
				return false;
			}
		}

		List roles = userRoles;
		if (roles == null) {
			roles = UserUtil.getRoles(userId);
		}

		// Administrators have access to all roles

		Role adminRole = getRoleByName(user.getCompanyId(), Role.ADMINISTRATOR);

		if (roles.contains(adminRole)) {
			return true;
		}

		// Check for role name

		try {
			Role role = getRoleByName(user.getCompanyId(), roleName);

			if (roles.contains(role)) {
				return true;
			}
			else {

				// Check roles inherited from groups

				Iterator itr = UserUtil.getGroups(userId).iterator();

				while (itr.hasNext()) {
					Group group = (Group)itr.next();

					List groupRoles = GroupUtil.getRoles(group.getGroupId());

					if (groupRoles.contains(adminRole) ||
						groupRoles.contains(role)) {

						return true;
					}
				}
			}
		}
		catch (NoSuchGroupException nsge) {
		}
		catch (NoSuchRoleException nsre) {
		}
		catch (NoSuchUserException nsue) {
		}

		return false;
	}

	public boolean hasRoles(String userId, String[] roleNames)
		throws PortalException, SystemException {

		if ((roleNames == null) || (roleNames.length == 0)) {
			return true;
		}

		for (int i = 0; i < roleNames.length; i++) {
			if (hasRole(userId, roleNames[i])) {
				return true;
			}
		}

		return false;
	}

	public boolean hasRoles(String userId, List userRoles, String[] roleNames)
		throws PortalException, SystemException {

		if ((roleNames == null) || (roleNames.length == 0)) {
			return true;
		}

		for (int i = 0; i < roleNames.length; i++) {
			if (hasRole(userId, userRoles, roleNames[i])) {
				return true;
			}
		}

		return false;
	}

	public boolean isAdministrator(String userId)
		throws PortalException, SystemException {

		return hasRole(userId, Role.ADMINISTRATOR);
	}

	public boolean isGuest(String userId)
		throws PortalException, SystemException {

		return hasRole(userId, Role.GUEST);
	}

	public boolean isPowerUser(String userId)
		throws PortalException, SystemException {

		return hasRole(userId, Role.POWER_USER);
	}

	public boolean isUser(String userId)
		throws PortalException, SystemException {

		return hasRole(userId, Role.USER);
	}

	public boolean removeGroups(String roleId, String[] groupIds)
		throws PortalException, SystemException {

		return RoleUtil.removeGroups(roleId, groupIds);
	}

	public boolean removeGroups(String roleId, List groups)
		throws PortalException, SystemException {

		return RoleUtil.removeGroups(roleId, groups);
	}

	public boolean removeUsers(String roleId, String[] userIds)
		throws PortalException, SystemException {

		return RoleUtil.removeUsers(roleId, userIds);
	}

	public boolean removeUsers(String roleId, List users)
		throws PortalException, SystemException {

		return RoleUtil.removeUsers(roleId, users);
	}

	public Role renameRoleById(String roleId, String newName)
		throws PortalException, SystemException {

		Role role = RoleUtil.findByPrimaryKey(roleId);

		if (role.getName().equalsIgnoreCase(newName)) {
			return role;
		}

		if (PortalUtil.isSystemRole(role.getName())) {
			throw new RequiredRoleException();
		}

		validate(role.getCompanyId(), newName);

		role.setName(newName);

		RoleUtil.update(role);

		return role;
	}

	public Role renameRoleByName(
			String companyId, String oldName, String newName)
		throws PortalException, SystemException {

		if (oldName.equalsIgnoreCase(newName)) {
			return RoleUtil.findByPrimaryKey(getRoleId(companyId, oldName));
		}

		try {
			validate(companyId, oldName);
		}
		catch (DuplicateRoleException dge) {
			if (PortalUtil.isSystemRole(oldName)) {
				throw new RequiredRoleException();
			}

			validate(companyId, newName);

			Role role = RoleUtil.findByPrimaryKey(
				getRoleId(companyId, oldName));

			role.setName(newName);

			RoleUtil.update(role);

			return role;
		}

		throw new NoSuchRoleException();
	}

	public void setGroups(String roleId, String[] groupIds)
		throws PortalException, SystemException {

		RoleUtil.setGroups(roleId, groupIds);
	}

	public void setGroups(String roleId, List groups)
		throws PortalException, SystemException {

		RoleUtil.setGroups(roleId, groups);
	}

	public void setUsers(String roleId, String[] userIds)
		throws PortalException, SystemException {

		RoleUtil.setUsers(roleId, userIds);
	}

	public void setUsers(String roleId, List users)
		throws PortalException, SystemException {

		RoleUtil.setUsers(roleId, users);
	}

	public void validate(String companyId, String name)
		throws PortalException, SystemException {

		if ((Validator.isNull(name)) || (Validator.isNumber(name)) ||
			(name.indexOf(StringPool.COMMA) != -1) ||
			(name.indexOf(StringPool.STAR) != -1)) {

			throw new RoleNameException();
		}
		else if (exists(companyId, name)) {
			throw new DuplicateRoleException();
		}
	}

	// Private methods

	private Map _getRolesPool(String id) {
		String scpId = RoleLocalServiceImpl.class.getName() + "." + id;

		Map rolesPool = (Map)SimpleCachePool.get(scpId);

		if (rolesPool == null) {
			rolesPool = CollectionFactory.getSyncHashMap();

			SimpleCachePool.put(scpId, rolesPool);
		}

		return rolesPool;
	}

}