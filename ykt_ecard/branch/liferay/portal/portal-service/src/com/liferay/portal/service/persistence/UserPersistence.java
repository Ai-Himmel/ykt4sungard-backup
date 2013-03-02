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
 * <a href="UserPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface UserPersistence {
	public com.liferay.portal.model.User create(long userId);

	public com.liferay.portal.model.User remove(long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User remove(
		com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User update(
		com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User update(
		com.liferay.portal.model.User user, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User updateImpl(
		com.liferay.portal.model.User user, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User findByPrimaryKey(long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User fetchByPrimaryKey(long userId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUuid(java.lang.String uuid, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUuid(java.lang.String uuid, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User[] findByUuid_PrevAndNext(long userId,
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User findByCompanyId_First(long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User findByCompanyId_Last(long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User[] findByCompanyId_PrevAndNext(
		long userId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User findByContactId(long contactId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User fetchByContactId(long contactId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User findByPortraitId(long portraitId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User fetchByPortraitId(long portraitId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User findByC_U(long companyId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User fetchByC_U(long companyId, long userId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User findByC_DU(long companyId,
		boolean defaultUser)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User fetchByC_DU(long companyId,
		boolean defaultUser) throws com.liferay.portal.SystemException;

	public java.util.List findByC_P(long companyId, java.lang.String password)
		throws com.liferay.portal.SystemException;

	public java.util.List findByC_P(long companyId, java.lang.String password,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findByC_P(long companyId, java.lang.String password,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User findByC_P_First(long companyId,
		java.lang.String password,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User findByC_P_Last(long companyId,
		java.lang.String password,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User[] findByC_P_PrevAndNext(long userId,
		long companyId, java.lang.String password,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User findByC_SN(long companyId,
		java.lang.String screenName)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User fetchByC_SN(long companyId,
		java.lang.String screenName) throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.User findByC_EA(long companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public com.liferay.portal.model.User fetchByC_EA(long companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findAll() throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public void removeByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException;

	public void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public void removeByContactId(long contactId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeByPortraitId(long portraitId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeByC_U(long companyId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeByC_DU(long companyId, boolean defaultUser)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeByC_P(long companyId, java.lang.String password)
		throws com.liferay.portal.SystemException;

	public void removeByC_SN(long companyId, java.lang.String screenName)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeByC_EA(long companyId, java.lang.String emailAddress)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException;

	public int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public int countByContactId(long contactId)
		throws com.liferay.portal.SystemException;

	public int countByPortraitId(long portraitId)
		throws com.liferay.portal.SystemException;

	public int countByC_U(long companyId, long userId)
		throws com.liferay.portal.SystemException;

	public int countByC_DU(long companyId, boolean defaultUser)
		throws com.liferay.portal.SystemException;

	public int countByC_P(long companyId, java.lang.String password)
		throws com.liferay.portal.SystemException;

	public int countByC_SN(long companyId, java.lang.String screenName)
		throws com.liferay.portal.SystemException;

	public int countByC_EA(long companyId, java.lang.String emailAddress)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;

	public java.util.List getGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getGroups(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getGroups(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public int getGroupsSize(long pk) throws com.liferay.portal.SystemException;

	public boolean containsGroup(long pk, long groupPK)
		throws com.liferay.portal.SystemException;

	public boolean containsGroups(long pk)
		throws com.liferay.portal.SystemException;

	public void addGroup(long pk, long groupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void addGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void addGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void addGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void clearGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeGroup(long pk, long groupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void removeGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void removeGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void removeGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void setGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void setGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getOrganizations(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getOrganizations(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getOrganizations(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public int getOrganizationsSize(long pk)
		throws com.liferay.portal.SystemException;

	public boolean containsOrganization(long pk, long organizationPK)
		throws com.liferay.portal.SystemException;

	public boolean containsOrganizations(long pk)
		throws com.liferay.portal.SystemException;

	public void addOrganization(long pk, long organizationPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public void addOrganization(long pk,
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public void addOrganizations(long pk, long[] organizationPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public void addOrganizations(long pk, java.util.List organizations)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public void clearOrganizations(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeOrganization(long pk, long organizationPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public void removeOrganization(long pk,
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public void removeOrganizations(long pk, long[] organizationPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public void removeOrganizations(long pk, java.util.List organizations)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public void setOrganizations(long pk, long[] organizationPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public void setOrganizations(long pk, java.util.List organizations)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getPermissions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getPermissions(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getPermissions(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public int getPermissionsSize(long pk)
		throws com.liferay.portal.SystemException;

	public boolean containsPermission(long pk, long permissionPK)
		throws com.liferay.portal.SystemException;

	public boolean containsPermissions(long pk)
		throws com.liferay.portal.SystemException;

	public void addPermission(long pk, long permissionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public void addPermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public void addPermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public void addPermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public void clearPermissions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removePermission(long pk, long permissionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public void removePermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public void removePermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public void removePermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public void setPermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public void setPermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getRoles(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getRoles(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getRoles(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public int getRolesSize(long pk) throws com.liferay.portal.SystemException;

	public boolean containsRole(long pk, long rolePK)
		throws com.liferay.portal.SystemException;

	public boolean containsRoles(long pk)
		throws com.liferay.portal.SystemException;

	public void addRole(long pk, long rolePK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public void addRole(long pk, com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public void addRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public void addRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public void clearRoles(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeRole(long pk, long rolePK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public void removeRole(long pk, com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public void removeRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public void removeRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public void setRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public void setRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getUserGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getUserGroups(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public java.util.List getUserGroups(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public int getUserGroupsSize(long pk)
		throws com.liferay.portal.SystemException;

	public boolean containsUserGroup(long pk, long userGroupPK)
		throws com.liferay.portal.SystemException;

	public boolean containsUserGroups(long pk)
		throws com.liferay.portal.SystemException;

	public void addUserGroup(long pk, long userGroupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void addUserGroup(long pk,
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void addUserGroups(long pk, long[] userGroupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void addUserGroups(long pk, java.util.List userGroups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void clearUserGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException;

	public void removeUserGroup(long pk, long userGroupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void removeUserGroup(long pk,
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void removeUserGroups(long pk, long[] userGroupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void removeUserGroups(long pk, java.util.List userGroups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void setUserGroups(long pk, long[] userGroupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void setUserGroups(long pk, java.util.List userGroups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException;
}