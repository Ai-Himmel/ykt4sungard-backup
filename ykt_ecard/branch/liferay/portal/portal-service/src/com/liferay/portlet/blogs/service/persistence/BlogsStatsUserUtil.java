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
 * <a href="BlogsStatsUserUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BlogsStatsUserUtil {
	public static com.liferay.portlet.blogs.model.BlogsStatsUser create(
		long statsUserId) {
		return getPersistence().create(statsUserId);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser remove(
		long statsUserId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().remove(statsUserId);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser remove(
		com.liferay.portlet.blogs.model.BlogsStatsUser blogsStatsUser)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(blogsStatsUser);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser update(
		com.liferay.portlet.blogs.model.BlogsStatsUser blogsStatsUser)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(blogsStatsUser);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser update(
		com.liferay.portlet.blogs.model.BlogsStatsUser blogsStatsUser,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(blogsStatsUser, merge);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser updateImpl(
		com.liferay.portlet.blogs.model.BlogsStatsUser blogsStatsUser,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(blogsStatsUser, merge);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByPrimaryKey(
		long statsUserId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByPrimaryKey(statsUserId);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser fetchByPrimaryKey(
		long statsUserId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(statsUserId);
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

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser[] findByGroupId_PrevAndNext(
		long statsUserId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByGroupId_PrevAndNext(statsUserId, groupId,
			obc);
	}

	public static java.util.List findByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId);
	}

	public static java.util.List findByUserId(long userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(long userId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser[] findByUserId_PrevAndNext(
		long statsUserId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByUserId_PrevAndNext(statsUserId, userId,
			obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByG_U(
		long groupId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByG_U(groupId, userId);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser fetchByG_U(
		long groupId, long userId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_U(groupId, userId);
	}

	public static java.util.List findByG_E(long groupId, int entryCount)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_E(groupId, entryCount);
	}

	public static java.util.List findByG_E(long groupId, int entryCount,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByG_E(groupId, entryCount, begin, end);
	}

	public static java.util.List findByG_E(long groupId, int entryCount,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_E(groupId, entryCount, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByG_E_First(
		long groupId, int entryCount,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByG_E_First(groupId, entryCount, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByG_E_Last(
		long groupId, int entryCount,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByG_E_Last(groupId, entryCount, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser[] findByG_E_PrevAndNext(
		long statsUserId, long groupId, int entryCount,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByG_E_PrevAndNext(statsUserId, groupId,
			entryCount, obc);
	}

	public static java.util.List findByC_E(long companyId, int entryCount)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_E(companyId, entryCount);
	}

	public static java.util.List findByC_E(long companyId, int entryCount,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_E(companyId, entryCount, begin, end);
	}

	public static java.util.List findByC_E(long companyId, int entryCount,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_E(companyId, entryCount, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByC_E_First(
		long companyId, int entryCount,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByC_E_First(companyId, entryCount, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser findByC_E_Last(
		long companyId, int entryCount,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByC_E_Last(companyId, entryCount, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser[] findByC_E_PrevAndNext(
		long statsUserId, long companyId, int entryCount,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		return getPersistence().findByC_E_PrevAndNext(statsUserId, companyId,
			entryCount, obc);
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

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByUserId(long userId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUserId(userId);
	}

	public static void removeByG_U(long groupId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.blogs.NoSuchStatsUserException {
		getPersistence().removeByG_U(groupId, userId);
	}

	public static void removeByG_E(long groupId, int entryCount)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_E(groupId, entryCount);
	}

	public static void removeByC_E(long companyId, int entryCount)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_E(companyId, entryCount);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUserId(userId);
	}

	public static int countByG_U(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_U(groupId, userId);
	}

	public static int countByG_E(long groupId, int entryCount)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_E(groupId, entryCount);
	}

	public static int countByC_E(long companyId, int entryCount)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_E(companyId, entryCount);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static BlogsStatsUserPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(BlogsStatsUserPersistence persistence) {
		_persistence = persistence;
	}

	private static BlogsStatsUserUtil _getUtil() {
		if (_util == null) {
			_util = (BlogsStatsUserUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = BlogsStatsUserUtil.class.getName();
	private static BlogsStatsUserUtil _util;
	private BlogsStatsUserPersistence _persistence;
}