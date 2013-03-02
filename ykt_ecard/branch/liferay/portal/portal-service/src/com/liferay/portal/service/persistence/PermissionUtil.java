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

package com.liferay.portal.service.persistence;

/**
 * <a href="PermissionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionUtil {
	public static com.liferay.portal.model.Permission create(long permissionId) {
		return getPersistence().create(permissionId);
	}

	public static com.liferay.portal.model.Permission remove(long permissionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().remove(permissionId);
	}

	public static com.liferay.portal.model.Permission remove(
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(permission);
	}

	public static com.liferay.portal.model.Permission update(
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(permission);
	}

	public static com.liferay.portal.model.Permission update(
		com.liferay.portal.model.Permission permission, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(permission, merge);
	}

	public static com.liferay.portal.model.Permission updateImpl(
		com.liferay.portal.model.Permission permission, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(permission, merge);
	}

	public static com.liferay.portal.model.Permission findByPrimaryKey(
		long permissionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().findByPrimaryKey(permissionId);
	}

	public static com.liferay.portal.model.Permission fetchByPrimaryKey(
		long permissionId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(permissionId);
	}

	public static java.util.List findByResourceId(long resourceId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByResourceId(resourceId);
	}

	public static java.util.List findByResourceId(long resourceId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByResourceId(resourceId, begin, end);
	}

	public static java.util.List findByResourceId(long resourceId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByResourceId(resourceId, begin, end, obc);
	}

	public static com.liferay.portal.model.Permission findByResourceId_First(
		long resourceId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().findByResourceId_First(resourceId, obc);
	}

	public static com.liferay.portal.model.Permission findByResourceId_Last(
		long resourceId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().findByResourceId_Last(resourceId, obc);
	}

	public static com.liferay.portal.model.Permission[] findByResourceId_PrevAndNext(
		long permissionId, long resourceId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().findByResourceId_PrevAndNext(permissionId,
			resourceId, obc);
	}

	public static com.liferay.portal.model.Permission findByA_R(
		java.lang.String actionId, long resourceId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().findByA_R(actionId, resourceId);
	}

	public static com.liferay.portal.model.Permission fetchByA_R(
		java.lang.String actionId, long resourceId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByA_R(actionId, resourceId);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer, begin,
			end);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll();
	}

	public static java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end);
	}

	public static java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end, obc);
	}

	public static void removeByResourceId(long resourceId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByResourceId(resourceId);
	}

	public static void removeByA_R(java.lang.String actionId, long resourceId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().removeByA_R(actionId, resourceId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByResourceId(long resourceId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByResourceId(resourceId);
	}

	public static int countByA_R(java.lang.String actionId, long resourceId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByA_R(actionId, resourceId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().getGroups(pk);
	}

	public static java.util.List getGroups(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().getGroups(pk, begin, end);
	}

	public static java.util.List getGroups(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().getGroups(pk, begin, end, obc);
	}

	public static int getGroupsSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getGroupsSize(pk);
	}

	public static boolean containsGroup(long pk, long groupPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsGroup(pk, groupPK);
	}

	public static boolean containsGroups(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsGroups(pk);
	}

	public static void addGroup(long pk, long groupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().addGroup(pk, groupPK);
	}

	public static void addGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().addGroup(pk, group);
	}

	public static void addGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().addGroups(pk, groupPKs);
	}

	public static void addGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().addGroups(pk, groups);
	}

	public static void clearGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().clearGroups(pk);
	}

	public static void removeGroup(long pk, long groupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().removeGroup(pk, groupPK);
	}

	public static void removeGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().removeGroup(pk, group);
	}

	public static void removeGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().removeGroups(pk, groupPKs);
	}

	public static void removeGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().removeGroups(pk, groups);
	}

	public static void setGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().setGroups(pk, groupPKs);
	}

	public static void setGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().setGroups(pk, groups);
	}

	public static java.util.List getRoles(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().getRoles(pk);
	}

	public static java.util.List getRoles(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().getRoles(pk, begin, end);
	}

	public static java.util.List getRoles(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().getRoles(pk, begin, end, obc);
	}

	public static int getRolesSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getRolesSize(pk);
	}

	public static boolean containsRole(long pk, long rolePK)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsRole(pk, rolePK);
	}

	public static boolean containsRoles(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsRoles(pk);
	}

	public static void addRole(long pk, long rolePK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().addRole(pk, rolePK);
	}

	public static void addRole(long pk, com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().addRole(pk, role);
	}

	public static void addRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().addRoles(pk, rolePKs);
	}

	public static void addRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().addRoles(pk, roles);
	}

	public static void clearRoles(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().clearRoles(pk);
	}

	public static void removeRole(long pk, long rolePK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().removeRole(pk, rolePK);
	}

	public static void removeRole(long pk, com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().removeRole(pk, role);
	}

	public static void removeRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().removeRoles(pk, rolePKs);
	}

	public static void removeRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().removeRoles(pk, roles);
	}

	public static void setRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().setRoles(pk, rolePKs);
	}

	public static void setRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().setRoles(pk, roles);
	}

	public static java.util.List getUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().getUsers(pk);
	}

	public static java.util.List getUsers(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().getUsers(pk, begin, end);
	}

	public static java.util.List getUsers(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		return getPersistence().getUsers(pk, begin, end, obc);
	}

	public static int getUsersSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getUsersSize(pk);
	}

	public static boolean containsUser(long pk, long userPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsUser(pk, userPK);
	}

	public static boolean containsUsers(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsUsers(pk);
	}

	public static void addUser(long pk, long userPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, userPK);
	}

	public static void addUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, user);
	}

	public static void addUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, userPKs);
	}

	public static void addUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, users);
	}

	public static void clearUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException {
		getPersistence().clearUsers(pk);
	}

	public static void removeUser(long pk, long userPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, userPK);
	}

	public static void removeUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, user);
	}

	public static void removeUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, userPKs);
	}

	public static void removeUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, users);
	}

	public static void setUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, userPKs);
	}

	public static void setUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, users);
	}

	public static PermissionPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PermissionPersistence persistence) {
		_persistence = persistence;
	}

	private static PermissionUtil _getUtil() {
		if (_util == null) {
			_util = (PermissionUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PermissionUtil.class.getName();
	private static PermissionUtil _util;
	private PermissionPersistence _persistence;
}