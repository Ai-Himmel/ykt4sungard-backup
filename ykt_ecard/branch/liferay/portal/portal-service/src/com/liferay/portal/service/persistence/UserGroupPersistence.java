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
 * <a href="UserGroupPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface UserGroupPersistence {
	public com.liferay.portal.model.UserGroup create(long userGroupId);

	public com.liferay.portal.model.UserGroup remove(long userGroupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public com.liferay.portal.model.UserGroup remove(
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.UserGroup update(
		com.liferay.portal.model.UserGroup userGroup)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.UserGroup update(
		com.liferay.portal.model.UserGroup userGroup, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.UserGroup updateImpl(
		com.liferay.portal.model.UserGroup userGroup, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.UserGroup findByPrimaryKey(long userGroupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public com.liferay.portal.model.UserGroup fetchByPrimaryKey(
		long userGroupId) throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByCompanyId(long companyId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.UserGroup findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public com.liferay.portal.model.UserGroup findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public com.liferay.portal.model.UserGroup[] findByCompanyId_PrevAndNext(
		long userGroupId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public java.util.List findByC_P(long companyId, long parentUserGroupId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByC_P(long companyId, long parentUserGroupId,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findByC_P(long companyId, long parentUserGroupId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.model.UserGroup findByC_P_First(long companyId,
		long parentUserGroupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public com.liferay.portal.model.UserGroup findByC_P_Last(long companyId,
		long parentUserGroupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public com.liferay.portal.model.UserGroup[] findByC_P_PrevAndNext(
		long userGroupId, long companyId, long parentUserGroupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public com.liferay.portal.model.UserGroup findByC_N(long companyId,
		java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public com.liferay.portal.model.UserGroup fetchByC_N(long companyId,
		java.lang.String name) throws com.liferay.portal.SystemException;

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

	public void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public void removeByC_P(long companyId, long parentUserGroupId)
		throws com.liferay.portal.SystemException;

	public void removeByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException;

	public int countByC_P(long companyId, long parentUserGroupId)
		throws com.liferay.portal.SystemException;

	public int countByC_N(long companyId, java.lang.String name)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;

	public java.util.List getUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public java.util.List getUsers(long pk, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public java.util.List getUsers(long pk, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public int getUsersSize(long pk) throws com.liferay.portal.SystemException;

	public boolean containsUser(long pk, long userPK)
		throws com.liferay.portal.SystemException;

	public boolean containsUsers(long pk)
		throws com.liferay.portal.SystemException;

	public void addUser(long pk, long userPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void addUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void addUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void addUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void clearUsers(long pk)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException;

	public void removeUser(long pk, long userPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void removeUser(long pk, com.liferay.portal.model.User user)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void removeUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void removeUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void setUsers(long pk, long[] userPKs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;

	public void setUsers(long pk, java.util.List users)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchUserGroupException, 
			com.liferay.portal.NoSuchUserException;
}