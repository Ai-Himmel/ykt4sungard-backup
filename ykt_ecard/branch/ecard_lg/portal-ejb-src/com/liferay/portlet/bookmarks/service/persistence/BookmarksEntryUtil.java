/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.bookmarks.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="BookmarksEntryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BookmarksEntryUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.bookmarks.model.BookmarksEntry"),
			"com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.bookmarks.model.BookmarksEntry"));

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry create(
		java.lang.String entryId) {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(entryId);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry remove(
		java.lang.String entryId)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (listener != null) {
			listener.onBeforeRemove(findByPrimaryKey(entryId));
		}

		com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry = persistence.remove(entryId);

		if (listener != null) {
			listener.onAfterRemove(bookmarksEntry);
		}

		return bookmarksEntry;
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry update(
		com.liferay.portlet.bookmarks.model.BookmarksEntry bookmarksEntry)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = bookmarksEntry.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(bookmarksEntry);
			}
			else {
				listener.onBeforeUpdate(bookmarksEntry);
			}
		}

		bookmarksEntry = persistence.update(bookmarksEntry);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(bookmarksEntry);
			}
			else {
				listener.onAfterUpdate(bookmarksEntry);
			}
		}

		return bookmarksEntry;
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry findByPrimaryKey(
		java.lang.String entryId)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(entryId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry findByGroupId_First(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry findByGroupId_Last(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry[] findByGroupId_PrevAndNext(
		java.lang.String entryId, java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_PrevAndNext(entryId, groupId, obc);
	}

	public static java.util.List findByG_U(java.lang.String groupId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U(groupId, userId);
	}

	public static java.util.List findByG_U(java.lang.String groupId,
		java.lang.String userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U(groupId, userId, begin, end);
	}

	public static java.util.List findByG_U(java.lang.String groupId,
		java.lang.String userId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U(groupId, userId, begin, end, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_U_First(
		java.lang.String groupId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_First(groupId, userId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_U_Last(
		java.lang.String groupId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_Last(groupId, userId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry[] findByG_U_PrevAndNext(
		java.lang.String entryId, java.lang.String groupId,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_PrevAndNext(entryId, groupId, userId, obc);
	}

	public static java.util.List findByG_F(java.lang.String groupId,
		java.lang.String folderId) throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_F(groupId, folderId);
	}

	public static java.util.List findByG_F(java.lang.String groupId,
		java.lang.String folderId, int begin, int end)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_F(groupId, folderId, begin, end);
	}

	public static java.util.List findByG_F(java.lang.String groupId,
		java.lang.String folderId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_F(groupId, folderId, begin, end, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_F_First(
		java.lang.String groupId, java.lang.String folderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_F_First(groupId, folderId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_F_Last(
		java.lang.String groupId, java.lang.String folderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_F_Last(groupId, folderId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry[] findByG_F_PrevAndNext(
		java.lang.String entryId, java.lang.String groupId,
		java.lang.String folderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_F_PrevAndNext(entryId, groupId, folderId, obc);
	}

	public static java.util.List findByG_U_F(java.lang.String groupId,
		java.lang.String userId, java.lang.String folderId)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_F(groupId, userId, folderId);
	}

	public static java.util.List findByG_U_F(java.lang.String groupId,
		java.lang.String userId, java.lang.String folderId, int begin, int end)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_F(groupId, userId, folderId, begin, end);
	}

	public static java.util.List findByG_U_F(java.lang.String groupId,
		java.lang.String userId, java.lang.String folderId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_F(groupId, userId, folderId, begin, end,
			obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_U_F_First(
		java.lang.String groupId, java.lang.String userId,
		java.lang.String folderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_F_First(groupId, userId, folderId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry findByG_U_F_Last(
		java.lang.String groupId, java.lang.String userId,
		java.lang.String folderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_F_Last(groupId, userId, folderId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntry[] findByG_U_F_PrevAndNext(
		java.lang.String entryId, java.lang.String groupId,
		java.lang.String userId, java.lang.String folderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_F_PrevAndNext(entryId, groupId, userId,
			folderId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByGroupId(groupId);
	}

	public static void removeByG_U(java.lang.String groupId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_U(groupId, userId);
	}

	public static void removeByG_F(java.lang.String groupId,
		java.lang.String folderId) throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_F(groupId, folderId);
	}

	public static void removeByG_U_F(java.lang.String groupId,
		java.lang.String userId, java.lang.String folderId)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_U_F(groupId, userId, folderId);
	}

	public static int countByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByGroupId(groupId);
	}

	public static int countByG_U(java.lang.String groupId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_U(groupId, userId);
	}

	public static int countByG_F(java.lang.String groupId,
		java.lang.String folderId) throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_F(groupId, folderId);
	}

	public static int countByG_U_F(java.lang.String groupId,
		java.lang.String userId, java.lang.String folderId)
		throws com.liferay.portal.SystemException {
		BookmarksEntryPersistence persistence = (BookmarksEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_U_F(groupId, userId, folderId);
	}

	private static final Log _log = LogFactory.getLog(BookmarksEntryUtil.class);
}