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

import com.liferay.portal.service.spring.RoleServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="RoleServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class RoleServiceSoap {
	public static boolean addGroups(java.lang.String roleId,
		java.util.List groups) throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.addGroups(roleId, groups);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleModel addRole(
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.addRole(name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean addUsers(java.lang.String roleId, java.util.List users)
		throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.addUsers(roleId, users);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void checkSystemRoles(java.lang.String companyId)
		throws RemoteException {
		try {
			RoleServiceUtil.checkSystemRoles(companyId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteRole(java.lang.String roleId)
		throws RemoteException {
		try {
			RoleServiceUtil.deleteRole(roleId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean exists(java.lang.String name)
		throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.exists(name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean exists(java.lang.String[] names)
		throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.exists(names);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleModel[] getGroups(
		java.lang.String roleId) throws RemoteException {
		try {
			java.util.List returnValue = RoleServiceUtil.getGroups(roleId);

			return (com.liferay.portal.model.Role[])returnValue.toArray(new com.liferay.portal.model.Role[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleModel[] getGroups(
		java.lang.String roleId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = RoleServiceUtil.getGroups(roleId,
					begin, end);

			return (com.liferay.portal.model.Role[])returnValue.toArray(new com.liferay.portal.model.Role[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getGroupsSize(java.lang.String roleId)
		throws RemoteException {
		try {
			int returnValue = RoleServiceUtil.getGroupsSize(roleId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleModel getRoleById(
		java.lang.String roleId) throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.getRoleById(roleId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleModel getRoleByName(
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.getRoleByName(name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleModel[] getUsers(
		java.lang.String roleId) throws RemoteException {
		try {
			java.util.List returnValue = RoleServiceUtil.getUsers(roleId);

			return (com.liferay.portal.model.Role[])returnValue.toArray(new com.liferay.portal.model.Role[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleModel[] getUsers(
		java.lang.String roleId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = RoleServiceUtil.getUsers(roleId,
					begin, end);

			return (com.liferay.portal.model.Role[])returnValue.toArray(new com.liferay.portal.model.Role[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getUsersSize(java.lang.String roleId)
		throws RemoteException {
		try {
			int returnValue = RoleServiceUtil.getUsersSize(roleId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasRole(java.lang.String userId,
		java.lang.String roleName) throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.hasRole(userId, roleName);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasRoles(java.lang.String userId,
		java.lang.String[] roleNames) throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.hasRoles(userId, roleNames);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean isAdministrator(java.lang.String userId)
		throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.isAdministrator(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean isGuest(java.lang.String userId)
		throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.isGuest(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean isPowerUser(java.lang.String userId)
		throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.isPowerUser(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean isUser(java.lang.String userId)
		throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.isUser(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean removeGroups(java.lang.String roleId,
		java.lang.String[] groupIds) throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.removeGroups(roleId, groupIds);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean removeUsers(java.lang.String roleId,
		java.lang.String[] userIds) throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.removeUsers(roleId, userIds);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleModel renameRoleById(
		java.lang.String roleId, java.lang.String newName)
		throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.renameRoleById(roleId,
					newName);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.RoleModel renameRoleByName(
		java.lang.String oldName, java.lang.String newName)
		throws RemoteException {
		try {
			com.liferay.portal.model.Role returnValue = RoleServiceUtil.renameRoleByName(oldName,
					newName);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setGroups(java.lang.String roleId,
		java.lang.String[] groupIds) throws RemoteException {
		try {
			RoleServiceUtil.setGroups(roleId, groupIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setUsers(java.lang.String roleId,
		java.lang.String[] userIds) throws RemoteException {
		try {
			RoleServiceUtil.setUsers(roleId, userIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String roleId)
		throws RemoteException {
		try {
			boolean returnValue = RoleServiceUtil.hasAdmin(roleId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}