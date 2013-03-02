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

package com.liferay.portlet.journal.service.persistence;

/**
 * <a href="JournalFeedUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalFeedUtil {
	public static com.liferay.portlet.journal.model.JournalFeed create(long id) {
		return getPersistence().create(id);
	}

	public static com.liferay.portlet.journal.model.JournalFeed remove(long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().remove(id);
	}

	public static com.liferay.portlet.journal.model.JournalFeed remove(
		com.liferay.portlet.journal.model.JournalFeed journalFeed)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(journalFeed);
	}

	public static com.liferay.portlet.journal.model.JournalFeed update(
		com.liferay.portlet.journal.model.JournalFeed journalFeed)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(journalFeed);
	}

	public static com.liferay.portlet.journal.model.JournalFeed update(
		com.liferay.portlet.journal.model.JournalFeed journalFeed, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(journalFeed, merge);
	}

	public static com.liferay.portlet.journal.model.JournalFeed updateImpl(
		com.liferay.portlet.journal.model.JournalFeed journalFeed, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(journalFeed, merge);
	}

	public static com.liferay.portlet.journal.model.JournalFeed findByPrimaryKey(
		long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().findByPrimaryKey(id);
	}

	public static com.liferay.portlet.journal.model.JournalFeed fetchByPrimaryKey(
		long id) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(id);
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

	public static com.liferay.portlet.journal.model.JournalFeed findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.journal.model.JournalFeed findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.journal.model.JournalFeed[] findByUuid_PrevAndNext(
		long id, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().findByUuid_PrevAndNext(id, uuid, obc);
	}

	public static com.liferay.portlet.journal.model.JournalFeed findByUUID_G(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().findByUUID_G(uuid, groupId);
	}

	public static com.liferay.portlet.journal.model.JournalFeed fetchByUUID_G(
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

	public static com.liferay.portlet.journal.model.JournalFeed findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalFeed findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalFeed[] findByGroupId_PrevAndNext(
		long id, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().findByGroupId_PrevAndNext(id, groupId, obc);
	}

	public static com.liferay.portlet.journal.model.JournalFeed findByG_F(
		long groupId, java.lang.String feedId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		return getPersistence().findByG_F(groupId, feedId);
	}

	public static com.liferay.portlet.journal.model.JournalFeed fetchByG_F(
		long groupId, java.lang.String feedId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByG_F(groupId, feedId);
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
			com.liferay.portlet.journal.NoSuchFeedException {
		getPersistence().removeByUUID_G(uuid, groupId);
	}

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByG_F(long groupId, java.lang.String feedId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.journal.NoSuchFeedException {
		getPersistence().removeByG_F(groupId, feedId);
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

	public static int countByG_F(long groupId, java.lang.String feedId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_F(groupId, feedId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static JournalFeedPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(JournalFeedPersistence persistence) {
		_persistence = persistence;
	}

	private static JournalFeedUtil _getUtil() {
		if (_util == null) {
			_util = (JournalFeedUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = JournalFeedUtil.class.getName();
	private static JournalFeedUtil _util;
	private JournalFeedPersistence _persistence;
}