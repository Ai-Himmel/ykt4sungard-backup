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
 * <a href="OrganizationUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrganizationUtil {
	public static com.liferay.portal.model.Organization create(
		long organizationId) {
		return getPersistence().create(organizationId);
	}

	public static com.liferay.portal.model.Organization remove(
		long organizationId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().remove(organizationId);
	}

	public static com.liferay.portal.model.Organization remove(
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(organization);
	}

	public static com.liferay.portal.model.Organization update(
		com.liferay.portal.model.Organization organization)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(organization);
	}

	public static com.liferay.portal.model.Organization update(
		com.liferay.portal.model.Organization organization, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(organization, merge);
	}

	public static com.liferay.portal.model.Organization updateImpl(
		com.liferay.portal.model.Organization organization, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(organization, merge);
	}

	public static com.liferay.portal.model.Organization findByPrimaryKey(
		long organizationId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByPrimaryKey(organizationId);
	}

	public static com.liferay.portal.model.Organization fetchByPrimaryKey(
		long organizationId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(organizationId);
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

	public static com.liferay.portal.model.Organization findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Organization findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Organization[] findByCompanyId_PrevAndNext(
		long organizationId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByCompanyId_PrevAndNext(organizationId,
			companyId, obc);
	}

	public static java.util.List findByLocations(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByLocations(companyId);
	}

	public static java.util.List findByLocations(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByLocations(companyId, begin, end);
	}

	public static java.util.List findByLocations(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByLocations(companyId, begin, end, obc);
	}

	public static com.liferay.portal.model.Organization findByLocations_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByLocations_First(companyId, obc);
	}

	public static com.liferay.portal.model.Organization findByLocations_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByLocations_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Organization[] findByLocations_PrevAndNext(
		long organizationId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByLocations_PrevAndNext(organizationId,
			companyId, obc);
	}

	public static java.util.List findByC_P(long companyId,
		long parentOrganizationId) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_P(companyId, parentOrganizationId);
	}

	public static java.util.List findByC_P(long companyId,
		long parentOrganizationId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_P(companyId, parentOrganizationId,
			begin, end);
	}

	public static java.util.List findByC_P(long companyId,
		long parentOrganizationId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_P(companyId, parentOrganizationId,
			begin, end, obc);
	}

	public static com.liferay.portal.model.Organization findByC_P_First(
		long companyId, long parentOrganizationId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByC_P_First(companyId,
			parentOrganizationId, obc);
	}

	public static com.liferay.portal.model.Organization findByC_P_Last(
		long companyId, long parentOrganizationId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByC_P_Last(companyId, parentOrganizationId,
			obc);
	}

	public static com.liferay.portal.model.Organization[] findByC_P_PrevAndNext(
		long organizationId, long companyId, long parentOrganizationId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByC_P_PrevAndNext(organizationId,
			companyId, parentOrganizationId, obc);
	}

	public static com.liferay.portal.model.Organization findByC_N(
		long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().findByC_N(companyId, name);
	}

	public static com.liferay.portal.model.Organization fetchByC_N(
		long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_N(companyId, name);
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

	public static void removeByLocations(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByLocations(companyId);
	}

	public static void removeByC_P(long companyId, long parentOrganizationId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_P(companyId, parentOrganizationId);
	}

	public static void removeByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().removeByC_N(companyId, name);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByLocations(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByLocations(companyId);
	}

	public static int countByC_P(long companyId, long parentOrganizationId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_P(companyId, parentOrganizationId);
	}

	public static int countByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_N(companyId, name);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().getGroups(pk);
	}

	public static java.util.List getGroups(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().getGroups(pk, begin, end);
	}

	public static java.util.List getGroups(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
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
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().addGroup(pk, groupPK);
	}

	public static void addGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().addGroup(pk, group);
	}

	public static void addGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().addGroups(pk, groupPKs);
	}

	public static void addGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().addGroups(pk, groups);
	}

	public static void clearGroups(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().clearGroups(pk);
	}

	public static void removeGroup(long pk, long groupPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().removeGroup(pk, groupPK);
	}

	public static void removeGroup(long pk, com.liferay.portal.model.Group group)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().removeGroup(pk, group);
	}

	public static void removeGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().removeGroups(pk, groupPKs);
	}

	public static void removeGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().removeGroups(pk, groups);
	}

	public static void setGroups(long pk, long[] groupPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().setGroups(pk, groupPKs);
	}

	public static void setGroups(long pk, java.util.List groups)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchGroupException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().setGroups(pk, groups);
	}

	public static java.util.List getUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().getUsers(pk);
	}

	public static java.util.List getUsers(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		return getPersistence().getUsers(pk, begin, end);
	}

	public static java.util.List getUsers(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
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
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, userPK);
	}

	public static void addUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, user);
	}

	public static void addUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, userPKs);
	}

	public static void addUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, users);
	}

	public static void clearUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException {
		getPersistence().clearUsers(pk);
	}

	public static void removeUser(long pk, long userPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, userPK);
	}

	public static void removeUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, user);
	}

	public static void removeUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, userPKs);
	}

	public static void removeUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, users);
	}

	public static void setUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, userPKs);
	}

	public static void setUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchOrganizationException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, users);
	}

	public static OrganizationPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(OrganizationPersistence persistence) {
		_persistence = persistence;
	}

	private static OrganizationUtil _getUtil() {
		if (_util == null) {
			_util = (OrganizationUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = OrganizationUtil.class.getName();
	private static OrganizationUtil _util;
	private OrganizationPersistence _persistence;
}