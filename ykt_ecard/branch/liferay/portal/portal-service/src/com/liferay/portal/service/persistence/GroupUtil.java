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
 * <a href="GroupUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GroupUtil {
	public static com.liferay.portal.model.Group create(long groupId) {
		return getPersistence().create(groupId);
	}

	public static com.liferay.portal.model.Group remove(long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().remove(groupId);
	}

	public static com.liferay.portal.model.Group remove(
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(group);
	}

	public static com.liferay.portal.model.Group update(
		com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(group);
	}

	public static com.liferay.portal.model.Group update(
		com.liferay.portal.model.Group group, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(group, merge);
	}

	public static com.liferay.portal.model.Group updateImpl(
		com.liferay.portal.model.Group group, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(group, merge);
	}

	public static com.liferay.portal.model.Group findByPrimaryKey(long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().findByPrimaryKey(groupId);
	}

	public static com.liferay.portal.model.Group fetchByPrimaryKey(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(groupId);
	}

	public static com.liferay.portal.model.Group findByLiveGroupId(
		long liveGroupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().findByLiveGroupId(liveGroupId);
	}

	public static com.liferay.portal.model.Group fetchByLiveGroupId(
		long liveGroupId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByLiveGroupId(liveGroupId);
	}

	public static com.liferay.portal.model.Group findByC_N(long companyId,
		java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().findByC_N(companyId, name);
	}

	public static com.liferay.portal.model.Group fetchByC_N(long companyId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_N(companyId, name);
	}

	public static com.liferay.portal.model.Group findByC_F(long companyId,
		java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().findByC_F(companyId, friendlyURL);
	}

	public static com.liferay.portal.model.Group fetchByC_F(long companyId,
		java.lang.String friendlyURL) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_F(companyId, friendlyURL);
	}

	public static com.liferay.portal.model.Group findByC_C_C(long companyId,
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().findByC_C_C(companyId, classNameId, classPK);
	}

	public static com.liferay.portal.model.Group fetchByC_C_C(long companyId,
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

	public static void removeByLiveGroupId(long liveGroupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removeByLiveGroupId(liveGroupId);
	}

	public static void removeByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removeByC_N(companyId, name);
	}

	public static void removeByC_F(long companyId, java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removeByC_F(companyId, friendlyURL);
	}

	public static void removeByC_C_C(long companyId, long classNameId,
		long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removeByC_C_C(companyId, classNameId, classPK);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByLiveGroupId(long liveGroupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByLiveGroupId(liveGroupId);
	}

	public static int countByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_N(companyId, name);
	}

	public static int countByC_F(long companyId, java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_F(companyId, friendlyURL);
	}

	public static int countByC_C_C(long companyId, long classNameId,
		long classPK) throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C_C(companyId, classNameId, classPK);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getOrganizations(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getOrganizations(pk);
	}

	public static java.util.List getOrganizations(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getOrganizations(pk, begin, end);
	}

	public static java.util.List getOrganizations(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getOrganizations(pk, begin, end, obc);
	}

	public static int getOrganizationsSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getOrganizationsSize(pk);
	}

	public static boolean containsOrganization(long pk, long organizationPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsOrganization(pk, organizationPK);
	}

	public static boolean containsOrganizations(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsOrganizations(pk);
	}

	public static void addOrganization(long pk, long organizationPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().addOrganization(pk, organizationPK);
	}

	public static void addOrganization(long pk,
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().addOrganization(pk, organization);
	}

	public static void addOrganizations(long pk, long[] organizationPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().addOrganizations(pk, organizationPKs);
	}

	public static void addOrganizations(long pk, java.util.List organizations)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().addOrganizations(pk, organizations);
	}

	public static void clearOrganizations(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().clearOrganizations(pk);
	}

	public static void removeOrganization(long pk, long organizationPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().removeOrganization(pk, organizationPK);
	}

	public static void removeOrganization(long pk,
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().removeOrganization(pk, organization);
	}

	public static void removeOrganizations(long pk, long[] organizationPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().removeOrganizations(pk, organizationPKs);
	}

	public static void removeOrganizations(long pk, java.util.List organizations)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().removeOrganizations(pk, organizations);
	}

	public static void setOrganizations(long pk, long[] organizationPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().setOrganizations(pk, organizationPKs);
	}

	public static void setOrganizations(long pk, java.util.List organizations)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().setOrganizations(pk, organizations);
	}

	public static java.util.List getPermissions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getPermissions(pk);
	}

	public static java.util.List getPermissions(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getPermissions(pk, begin, end);
	}

	public static java.util.List getPermissions(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
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
			com.liferay.portal.NoSuchGroupException {
		getPersistence().addPermission(pk, permissionPK);
	}

	public static void addPermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().addPermission(pk, permission);
	}

	public static void addPermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().addPermissions(pk, permissionPKs);
	}

	public static void addPermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().addPermissions(pk, permissions);
	}

	public static void clearPermissions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().clearPermissions(pk);
	}

	public static void removePermission(long pk, long permissionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removePermission(pk, permissionPK);
	}

	public static void removePermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removePermission(pk, permission);
	}

	public static void removePermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removePermissions(pk, permissionPKs);
	}

	public static void removePermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removePermissions(pk, permissions);
	}

	public static void setPermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().setPermissions(pk, permissionPKs);
	}

	public static void setPermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().setPermissions(pk, permissions);
	}

	public static java.util.List getRoles(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getRoles(pk);
	}

	public static java.util.List getRoles(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getRoles(pk, begin, end);
	}

	public static java.util.List getRoles(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
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
			com.liferay.portal.NoSuchGroupException {
		getPersistence().addRole(pk, rolePK);
	}

	public static void addRole(long pk, com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().addRole(pk, role);
	}

	public static void addRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().addRoles(pk, rolePKs);
	}

	public static void addRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().addRoles(pk, roles);
	}

	public static void clearRoles(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().clearRoles(pk);
	}

	public static void removeRole(long pk, long rolePK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removeRole(pk, rolePK);
	}

	public static void removeRole(long pk, com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removeRole(pk, role);
	}

	public static void removeRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removeRoles(pk, rolePKs);
	}

	public static void removeRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().removeRoles(pk, roles);
	}

	public static void setRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().setRoles(pk, rolePKs);
	}

	public static void setRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().setRoles(pk, roles);
	}

	public static java.util.List getUserGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getUserGroups(pk);
	}

	public static java.util.List getUserGroups(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getUserGroups(pk, begin, end);
	}

	public static java.util.List getUserGroups(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getUserGroups(pk, begin, end, obc);
	}

	public static int getUserGroupsSize(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().getUserGroupsSize(pk);
	}

	public static boolean containsUserGroup(long pk, long userGroupPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsUserGroup(pk, userGroupPK);
	}

	public static boolean containsUserGroups(long pk)
		throws com.liferay.portal.SystemException {
		return getPersistence().containsUserGroups(pk);
	}

	public static void addUserGroup(long pk, long userGroupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().addUserGroup(pk, userGroupPK);
	}

	public static void addUserGroup(long pk,
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().addUserGroup(pk, userGroup);
	}

	public static void addUserGroups(long pk, long[] userGroupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().addUserGroups(pk, userGroupPKs);
	}

	public static void addUserGroups(long pk, java.util.List userGroups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().addUserGroups(pk, userGroups);
	}

	public static void clearUserGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().clearUserGroups(pk);
	}

	public static void removeUserGroup(long pk, long userGroupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().removeUserGroup(pk, userGroupPK);
	}

	public static void removeUserGroup(long pk,
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().removeUserGroup(pk, userGroup);
	}

	public static void removeUserGroups(long pk, long[] userGroupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().removeUserGroups(pk, userGroupPKs);
	}

	public static void removeUserGroups(long pk, java.util.List userGroups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().removeUserGroups(pk, userGroups);
	}

	public static void setUserGroups(long pk, long[] userGroupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().setUserGroups(pk, userGroupPKs);
	}

	public static void setUserGroups(long pk, java.util.List userGroups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().setUserGroups(pk, userGroups);
	}

	public static java.util.List getUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getUsers(pk);
	}

	public static java.util.List getUsers(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		return getPersistence().getUsers(pk, begin, end);
	}

	public static java.util.List getUsers(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
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
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, userPK);
	}

	public static void addUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, user);
	}

	public static void addUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, userPKs);
	}

	public static void addUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, users);
	}

	public static void clearUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException {
		getPersistence().clearUsers(pk);
	}

	public static void removeUser(long pk, long userPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, userPK);
	}

	public static void removeUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, user);
	}

	public static void removeUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, userPKs);
	}

	public static void removeUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, users);
	}

	public static void setUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, userPKs);
	}

	public static void setUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, users);
	}

	public static GroupPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(GroupPersistence persistence) {
		_persistence = persistence;
	}

	private static GroupUtil _getUtil() {
		if (_util == null) {
			_util = (GroupUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = GroupUtil.class.getName();
	private static GroupUtil _util;
	private GroupPersistence _persistence;
}