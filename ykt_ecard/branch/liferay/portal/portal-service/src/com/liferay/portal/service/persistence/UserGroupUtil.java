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
 * <a href="UserGroupUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserGroupUtil {
	public static com.liferay.portal.model.UserGroup create(long userGroupId) {
		return getPersistence().create(userGroupId);
	}

	public static com.liferay.portal.model.UserGroup remove(long userGroupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().remove(userGroupId);
	}

	public static com.liferay.portal.model.UserGroup remove(
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(userGroup);
	}

	public static com.liferay.portal.model.UserGroup update(
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(userGroup);
	}

	public static com.liferay.portal.model.UserGroup update(
		com.liferay.portal.model.UserGroup userGroup, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(userGroup, merge);
	}

	public static com.liferay.portal.model.UserGroup updateImpl(
		com.liferay.portal.model.UserGroup userGroup, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(userGroup, merge);
	}

	public static com.liferay.portal.model.UserGroup findByPrimaryKey(
		long userGroupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().findByPrimaryKey(userGroupId);
	}

	public static com.liferay.portal.model.UserGroup fetchByPrimaryKey(
		long userGroupId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(userGroupId);
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

	public static com.liferay.portal.model.UserGroup findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.UserGroup findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.UserGroup[] findByCompanyId_PrevAndNext(
		long userGroupId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().findByCompanyId_PrevAndNext(userGroupId,
			companyId, obc);
	}

	public static java.util.List findByC_P(long companyId,
		long parentUserGroupId) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_P(companyId, parentUserGroupId);
	}

	public static java.util.List findByC_P(long companyId,
		long parentUserGroupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_P(companyId, parentUserGroupId, begin,
			end);
	}

	public static java.util.List findByC_P(long companyId,
		long parentUserGroupId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_P(companyId, parentUserGroupId, begin,
			end, obc);
	}

	public static com.liferay.portal.model.UserGroup findByC_P_First(
		long companyId, long parentUserGroupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().findByC_P_First(companyId, parentUserGroupId,
			obc);
	}

	public static com.liferay.portal.model.UserGroup findByC_P_Last(
		long companyId, long parentUserGroupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().findByC_P_Last(companyId, parentUserGroupId, obc);
	}

	public static com.liferay.portal.model.UserGroup[] findByC_P_PrevAndNext(
		long userGroupId, long companyId, long parentUserGroupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().findByC_P_PrevAndNext(userGroupId, companyId,
			parentUserGroupId, obc);
	}

	public static com.liferay.portal.model.UserGroup findByC_N(long companyId,
		java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().findByC_N(companyId, name);
	}

	public static com.liferay.portal.model.UserGroup fetchByC_N(
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

	public static void removeByC_P(long companyId, long parentUserGroupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_P(companyId, parentUserGroupId);
	}

	public static void removeByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().removeByC_N(companyId, name);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByC_P(long companyId, long parentUserGroupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_P(companyId, parentUserGroupId);
	}

	public static int countByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_N(companyId, name);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static java.util.List getUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().getUsers(pk);
	}

	public static java.util.List getUsers(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		return getPersistence().getUsers(pk, begin, end);
	}

	public static java.util.List getUsers(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
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
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, userPK);
	}

	public static void addUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUser(pk, user);
	}

	public static void addUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, userPKs);
	}

	public static void addUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().addUsers(pk, users);
	}

	public static void clearUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException {
		getPersistence().clearUsers(pk);
	}

	public static void removeUser(long pk, long userPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, userPK);
	}

	public static void removeUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUser(pk, user);
	}

	public static void removeUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, userPKs);
	}

	public static void removeUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().removeUsers(pk, users);
	}

	public static void setUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, userPKs);
	}

	public static void setUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException {
		getPersistence().setUsers(pk, users);
	}

	public static UserGroupPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(UserGroupPersistence persistence) {
		_persistence = persistence;
	}

	private static UserGroupUtil _getUtil() {
		if (_util == null) {
			_util = (UserGroupUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = UserGroupUtil.class.getName();
	private static UserGroupUtil _util;
	private UserGroupPersistence _persistence;
}