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
 * <a href="UserUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserUtil {
	public static com.liferay.portal.model.User create(long userId) {
		return getPersistence().create(userId);
	}

	public static com.liferay.portal.model.User remove(long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().remove(userId);
	}

	public static com.liferay.portal.model.User remove(
		com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(user);
	}

	public static com.liferay.portal.model.User update(
		com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(user);
	}

	public static com.liferay.portal.model.User update(
		com.liferay.portal.model.User user, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(user, merge);
	}

	public static com.liferay.portal.model.User updateImpl(
		com.liferay.portal.model.User user, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(user, merge);
	}

	public static com.liferay.portal.model.User findByPrimaryKey(long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByPrimaryKey(userId);
	}

	public static com.liferay.portal.model.User fetchByPrimaryKey(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(userId);
	}

	public static java.util.List findByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end, obc);
	}

	public static com.liferay.portal.model.User findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portal.model.User findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portal.model.User[] findByUuid_PrevAndNext(
		long userId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByUuid_PrevAndNext(userId, uuid, obc);
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

	public static com.liferay.portal.model.User findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.User findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.User[] findByCompanyId_PrevAndNext(
		long userId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByCompanyId_PrevAndNext(userId, companyId,
			obc);
	}

	public static com.liferay.portal.model.User findByContactId(long contactId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByContactId(contactId);
	}

	public static com.liferay.portal.model.User fetchByContactId(long contactId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByContactId(contactId);
	}

	public static com.liferay.portal.model.User findByPortraitId(
		long portraitId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByPortraitId(portraitId);
	}

	public static com.liferay.portal.model.User fetchByPortraitId(
		long portraitId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPortraitId(portraitId);
	}

	public static com.liferay.portal.model.User findByC_U(long companyId,
		long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByC_U(companyId, userId);
	}

	public static com.liferay.portal.model.User fetchByC_U(long companyId,
		long userId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_U(companyId, userId);
	}

	public static com.liferay.portal.model.User findByC_DU(long companyId,
		boolean defaultUser)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByC_DU(companyId, defaultUser);
	}

	public static com.liferay.portal.model.User fetchByC_DU(long companyId,
		boolean defaultUser) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_DU(companyId, defaultUser);
	}

	public static java.util.List findByC_P(long companyId,
		java.lang.String password) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_P(companyId, password);
	}

	public static java.util.List findByC_P(long companyId,
		java.lang.String password, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_P(companyId, password, begin, end);
	}

	public static java.util.List findByC_P(long companyId,
		java.lang.String password, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_P(companyId, password, begin, end, obc);
	}

	public static com.liferay.portal.model.User findByC_P_First(
		long companyId, java.lang.String password,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByC_P_First(companyId, password, obc);
	}

	public static com.liferay.portal.model.User findByC_P_Last(long companyId,
		java.lang.String password,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByC_P_Last(companyId, password, obc);
	}

	public static com.liferay.portal.model.User[] findByC_P_PrevAndNext(
		long userId, long companyId, java.lang.String password,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByC_P_PrevAndNext(userId, companyId,
			password, obc);
	}

	public static com.liferay.portal.model.User findByC_SN(long companyId,
		java.lang.String screenName)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByC_SN(companyId, screenName);
	}

	public static com.liferay.portal.model.User fetchByC_SN(long companyId,
		java.lang.String screenName) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_SN(companyId, screenName);
	}

	public static com.liferay.portal.model.User findByC_EA(long companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().findByC_EA(companyId, emailAddress);
	}

	public static com.liferay.portal.model.User fetchByC_EA(long companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_EA(companyId, emailAddress);
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

	public static void removeByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUuid(uuid);
	}

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByContactId(long contactId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeByContactId(contactId);
	}

	public static void removeByPortraitId(long portraitId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeByPortraitId(portraitId);
	}

	public static void removeByC_U(long companyId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeByC_U(companyId, userId);
	}

	public static void removeByC_DU(long companyId, boolean defaultUser)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeByC_DU(companyId, defaultUser);
	}

	public static void removeByC_P(long companyId, java.lang.String password)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_P(companyId, password);
	}

	public static void removeByC_SN(long companyId, java.lang.String screenName)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeByC_SN(companyId, screenName);
	}

	public static void removeByC_EA(long companyId,
		java.lang.String emailAddress)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeByC_EA(companyId, emailAddress);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByContactId(long contactId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByContactId(contactId);
	}

	public static int countByPortraitId(long portraitId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByPortraitId(portraitId);
	}

	public static int countByC_U(long companyId, long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_U(companyId, userId);
	}

	public static int countByC_DU(long companyId, boolean defaultUser)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_DU(companyId, defaultUser);
	}

	public static int countByC_P(long companyId, java.lang.String password)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_P(companyId, password);
	}

	public static int countByC_SN(long companyId, java.lang.String screenName)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_SN(companyId, screenName);
	}

	public static int countByC_EA(long companyId, java.lang.String emailAddress)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_EA(companyId, emailAddress);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getGroups(pk);
	}

	public static java.util.List getGroups(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getGroups(pk, begin, end);
	}

	public static java.util.List getGroups(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
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
			com.liferay.portal.NoSuchUserException {
		getPersistence().addGroup(pk, groupPK);
	}

	public static void addGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addGroup(pk, group);
	}

	public static void addGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addGroups(pk, groupPKs);
	}

	public static void addGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addGroups(pk, groups);
	}

	public static void clearGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().clearGroups(pk);
	}

	public static void removeGroup(long pk, long groupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeGroup(pk, groupPK);
	}

	public static void removeGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeGroup(pk, group);
	}

	public static void removeGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeGroups(pk, groupPKs);
	}

	public static void removeGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeGroups(pk, groups);
	}

	public static void setGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setGroups(pk, groupPKs);
	}

	public static void setGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setGroups(pk, groups);
	}

	public static java.util.List getOrganizations(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getOrganizations(pk);
	}

	public static java.util.List getOrganizations(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getOrganizations(pk, begin, end);
	}

	public static java.util.List getOrganizations(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
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
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addOrganization(pk, organizationPK);
	}

	public static void addOrganization(long pk,
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addOrganization(pk, organization);
	}

	public static void addOrganizations(long pk, long[] organizationPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addOrganizations(pk, organizationPKs);
	}

	public static void addOrganizations(long pk, java.util.List organizations)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addOrganizations(pk, organizations);
	}

	public static void clearOrganizations(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().clearOrganizations(pk);
	}

	public static void removeOrganization(long pk, long organizationPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeOrganization(pk, organizationPK);
	}

	public static void removeOrganization(long pk,
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeOrganization(pk, organization);
	}

	public static void removeOrganizations(long pk, long[] organizationPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeOrganizations(pk, organizationPKs);
	}

	public static void removeOrganizations(long pk, java.util.List organizations)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeOrganizations(pk, organizations);
	}

	public static void setOrganizations(long pk, long[] organizationPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setOrganizations(pk, organizationPKs);
	}

	public static void setOrganizations(long pk, java.util.List organizations)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setOrganizations(pk, organizations);
	}

	public static java.util.List getPermissions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getPermissions(pk);
	}

	public static java.util.List getPermissions(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getPermissions(pk, begin, end);
	}

	public static java.util.List getPermissions(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
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
			com.liferay.portal.NoSuchUserException {
		getPersistence().addPermission(pk, permissionPK);
	}

	public static void addPermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addPermission(pk, permission);
	}

	public static void addPermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addPermissions(pk, permissionPKs);
	}

	public static void addPermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addPermissions(pk, permissions);
	}

	public static void clearPermissions(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().clearPermissions(pk);
	}

	public static void removePermission(long pk, long permissionPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removePermission(pk, permissionPK);
	}

	public static void removePermission(long pk,
		com.liferay.portal.model.Permission permission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removePermission(pk, permission);
	}

	public static void removePermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removePermissions(pk, permissionPKs);
	}

	public static void removePermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removePermissions(pk, permissions);
	}

	public static void setPermissions(long pk, long[] permissionPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setPermissions(pk, permissionPKs);
	}

	public static void setPermissions(long pk, java.util.List permissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPermissionException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setPermissions(pk, permissions);
	}

	public static java.util.List getRoles(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getRoles(pk);
	}

	public static java.util.List getRoles(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getRoles(pk, begin, end);
	}

	public static java.util.List getRoles(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
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
			com.liferay.portal.NoSuchUserException {
		getPersistence().addRole(pk, rolePK);
	}

	public static void addRole(long pk, com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addRole(pk, role);
	}

	public static void addRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addRoles(pk, rolePKs);
	}

	public static void addRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addRoles(pk, roles);
	}

	public static void clearRoles(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().clearRoles(pk);
	}

	public static void removeRole(long pk, long rolePK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeRole(pk, rolePK);
	}

	public static void removeRole(long pk, com.liferay.portal.model.Role role)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeRole(pk, role);
	}

	public static void removeRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeRoles(pk, rolePKs);
	}

	public static void removeRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeRoles(pk, roles);
	}

	public static void setRoles(long pk, long[] rolePKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setRoles(pk, rolePKs);
	}

	public static void setRoles(long pk, java.util.List roles)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchRoleException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setRoles(pk, roles);
	}

	public static java.util.List getUserGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getUserGroups(pk);
	}

	public static java.util.List getUserGroups(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		return getPersistence().getUserGroups(pk, begin, end);
	}

	public static java.util.List getUserGroups(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
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
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().addUserGroup(pk, userGroupPK);
	}

	public static void addUserGroup(long pk,
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().addUserGroup(pk, userGroup);
	}

	public static void addUserGroups(long pk, long[] userGroupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().addUserGroups(pk, userGroupPKs);
	}

	public static void addUserGroups(long pk, java.util.List userGroups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().addUserGroups(pk, userGroups);
	}

	public static void clearUserGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().clearUserGroups(pk);
	}

	public static void removeUserGroup(long pk, long userGroupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().removeUserGroup(pk, userGroupPK);
	}

	public static void removeUserGroup(long pk,
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().removeUserGroup(pk, userGroup);
	}

	public static void removeUserGroups(long pk, long[] userGroupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().removeUserGroups(pk, userGroupPKs);
	}

	public static void removeUserGroups(long pk, java.util.List userGroups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().removeUserGroups(pk, userGroups);
	}

	public static void setUserGroups(long pk, long[] userGroupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().setUserGroups(pk, userGroupPKs);
	}

	public static void setUserGroups(long pk, java.util.List userGroups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().setUserGroups(pk, userGroups);
	}

	public static UserPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(UserPersistence persistence) {
		_persistence = persistence;
	}

	private static UserUtil _getUtil() {
		if (_util == null) {
			_util = (UserUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = UserUtil.class.getName();
	private static UserUtil _util;
	private UserPersistence _persistence;
}