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

package com.liferay.portlet.blogs.service.persistence;

/**
 * <a href="BlogsEntryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BlogsEntryUtil {
	public static com.liferay.portlet.blogs.model.BlogsEntry create(
		long entryId) {
		return getPersistence().create(entryId);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry remove(
		long entryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().remove(entryId);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry remove(
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(blogsEntry);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry update(
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(blogsEntry);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry update(
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(blogsEntry, merge);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry updateImpl(
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(blogsEntry, merge);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByPrimaryKey(
		long entryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByPrimaryKey(entryId);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry fetchByPrimaryKey(
		long entryId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(entryId);
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

	public static com.liferay.portlet.blogs.model.BlogsEntry findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByUuid_PrevAndNext(
		long entryId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByUuid_PrevAndNext(entryId, uuid, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByUUID_G(uuid, groupId);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry fetchByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByUUID_G(uuid, groupId);
	}

	public static java.util.List findByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByGroupId_PrevAndNext(
		long entryId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByGroupId_PrevAndNext(entryId, groupId, obc);
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

	public static com.liferay.portlet.blogs.model.BlogsEntry findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByCompanyId_PrevAndNext(
		long entryId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByCompanyId_PrevAndNext(entryId, companyId,
			obc);
	}

	public static java.util.List findByG_U(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_U(groupId, userId);
	}

	public static java.util.List findByG_U(long groupId, long userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_U(groupId, userId, begin, end);
	}

	public static java.util.List findByG_U(long groupId, long userId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_U(groupId, userId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByG_U_First(
		long groupId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByG_U_First(groupId, userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByG_U_Last(
		long groupId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByG_U_Last(groupId, userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByG_U_PrevAndNext(
		long entryId, long groupId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByG_U_PrevAndNext(entryId, groupId, userId,
			obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByG_UT(
		long groupId, java.lang.String urlTitle)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByG_UT(groupId, urlTitle);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry fetchByG_UT(
		long groupId, java.lang.String urlTitle)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_UT(groupId, urlTitle);
	}

	public static java.util.List findByC_U(long companyId, long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_U(companyId, userId);
	}

	public static java.util.List findByC_U(long companyId, long userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_U(companyId, userId, begin, end);
	}

	public static java.util.List findByC_U(long companyId, long userId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_U(companyId, userId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByC_U_First(
		long companyId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByC_U_First(companyId, userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByC_U_Last(
		long companyId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByC_U_Last(companyId, userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByC_U_PrevAndNext(
		long entryId, long companyId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		return getPersistence().findByC_U_PrevAndNext(entryId, companyId,
			userId, obc);
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

	public static void removeByUUID_G(java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		getPersistence().removeByUUID_G(uuid, groupId);
	}

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByG_U(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_U(groupId, userId);
	}

	public static void removeByG_UT(long groupId, java.lang.String urlTitle)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchEntryException {
		getPersistence().removeByG_UT(groupId, urlTitle);
	}

	public static void removeByC_U(long companyId, long userId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_U(companyId, userId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByUUID_G(java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUUID_G(uuid, groupId);
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByG_U(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_U(groupId, userId);
	}

	public static int countByG_UT(long groupId, java.lang.String urlTitle)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_UT(groupId, urlTitle);
	}

	public static int countByC_U(long companyId, long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_U(companyId, userId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static BlogsEntryPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(BlogsEntryPersistence persistence) {
		_persistence = persistence;
	}

	private static BlogsEntryUtil _getUtil() {
		if (_util == null) {
			_util = (BlogsEntryUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = BlogsEntryUtil.class.getName();
	private static BlogsEntryUtil _util;
	private BlogsEntryPersistence _persistence;
}