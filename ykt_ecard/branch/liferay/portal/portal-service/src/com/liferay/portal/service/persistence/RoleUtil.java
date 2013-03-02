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
 * <a href="RoleUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RoleUtil {
	public static com.liferay.portal.model.Role create(long roleId) {
		return getPersistence().create(roleId);
	}

	public static com.liferay.portal.model.Role remove(long roleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().remove(roleId);
	}

	public static com.liferay.portal.model.Role remove(
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(role);
	}

	public static com.liferay.portal.model.Role update(
		com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(role);
	}

	public static com.liferay.portal.model.Role update(
		com.liferay.portal.model.Role role, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(role, merge);
	}

	public static com.liferay.portal.model.Role updateImpl(
		com.liferay.portal.model.Role role, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(role, merge);
	}

	public static com.liferay.portal.model.Role findByPrimaryKey(long roleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().findByPrimaryKey(roleId);
	}

	public static com.liferay.portal.model.Role fetchByPrimaryKey(long roleId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(roleId);
	}

	public static java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portal.model.Role findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Role findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Role[] findByCompanyId_PrevAndNext(
		long roleId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().findByCompanyId_PrevAndNext(roleId, companyId,
			obc);
	}

	public static com.liferay.portal.model.Role findByC_N(long companyId,
		java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().findByC_N(companyId, name);
	}

	public static com.liferay.portal.model.Role fetchByC_N(long companyId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_N(companyId, name);
	}

	public static com.liferay.portal.model.Role findByC_C_C(long companyId,
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().findByC_C_C(companyId, classNameId, classPK);
	}

	public static com.liferay.portal.model.Role fetchByC_C_C(long companyId,
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_C_C(companyId, classNameId, classPK);
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

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removeByC_N(companyId, name);
	}

	public static void removeByC_C_C(long companyId, long classNameId,
		long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removeByC_C_C(companyId, classNameId, classPK);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_N(companyId, name);
	}

	public static int countByC_C_C(long companyId, long classNameId,
		long classPK) throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C_C(companyId, classNameId, classPK);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().getGroups(pk);
	}

	public static java.util.List getGroups(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().getGroups(pk, begin, end);
	}

	public static java.util.List getGroups(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
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
			com.liferay.portal.NoSuchRoleException {
		getPersistence().addGroup(pk, groupPK);
	}

	public static void addGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().addGroup(pk, group);
	}

	public static void addGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().addGroups(pk, groupPKs);
	}

	public static void addGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().addGroups(pk, groups);
	}

	public static void clearGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().clearGroups(pk);
	}

	public static void removeGroup(long pk, long groupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removeGroup(pk, groupPK);
	}

	public static void removeGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removeGroup(pk, group);
	}

	public static void removeGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removeGroups(pk, groupPKs);
	}

	public static void removeGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removeGroups(pk, groups);
	}

	public static void setGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().setGroups(pk, groupPKs);
	}

	public static void setGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().setGroups(pk, groups);
	}

	public static java.util.List getPermissions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().getPermissions(pk);
	}

	public static java.util.List getPermissions(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().getPermissions(pk, begin, end);
	}

	public static java.util.List getPermissions(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().getPermissions(pk, begin, end, obc);
	}

	public static int getPermissionsSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getPermissionsSize(pk);
	}

	public static boolean containsPermission(long pk, long permissionPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsPermission(pk, permissionPK);
	}

	public static boolean containsPermissions(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsPermissions(pk);
	}

	public static void addPermission(long pk, long permissionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().addPermission(pk, permissionPK);
	}

	public static void addPermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().addPermission(pk, permission);
	}

	public static void addPermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().addPermissions(pk, permissionPKs);
	}

	public static void addPermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().addPermissions(pk, permissions);
	}

	public static void clearPermissions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().clearPermissions(pk);
	}

	public static void removePermission(long pk, long permissionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removePermission(pk, permissionPK);
	}

	public static void removePermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removePermission(pk, permission);
	}

	public static void removePermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removePermissions(pk, permissionPKs);
	}

	public static void removePermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().removePermissions(pk, permissions);
	}

	public static void setPermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().setPermissions(pk, permissionPKs);
	}

	public static void setPermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().setPermissions(pk, permissions);
	}

	public static java.util.List getUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().getUsers(pk);
	}

	public static java.util.List getUsers(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		return getPersistence().getUsers(pk, begin, end);
	}

	public static java.util.List getUsers(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
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
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, userPK);
	}

	public static void addUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, user);
	}

	public static void addUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, userPKs);
	}

	public static void addUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, users);
	}

	public static void clearUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException {
		getPersistence().clearUsers(pk);
	}

	public static void removeUser(long pk, long userPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, userPK);
	}

	public static void removeUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, user);
	}

	public static void removeUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, userPKs);
	}

	public static void removeUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, users);
	}

	public static void setUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, userPKs);
	}

	public static void setUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, users);
	}

	public static RolePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(RolePersistence persistence) {
		_persistence = persistence;
	}

	private static RoleUtil _getUtil() {
		if (_util == null) {
			_util = (RoleUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = RoleUtil.class.getName();
	private static RoleUtil _util;
	private RolePersistence _persistence;
}