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
 * <a href="BookmarksFolderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BookmarksFolderUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.bookmarks.model.BookmarksFolder"),
			"com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.bookmarks.model.BookmarksFolder"));

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder create(
		java.lang.String folderId) {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(folderId);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder remove(
		java.lang.String folderId)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(folderId));
		}

		com.liferay.portlet.bookmarks.model.BookmarksFolder bookmarksFolder = persistence.remove(folderId);

		if (listener != null) {
			listener.onAfterRemove(bookmarksFolder);
		}

		return bookmarksFolder;
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder update(
		com.liferay.portlet.bookmarks.model.BookmarksFolder bookmarksFolder)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = bookmarksFolder.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(bookmarksFolder);
			}
			else {
				listener.onBeforeUpdate(bookmarksFolder);
			}
		}

		bookmarksFolder = persistence.update(bookmarksFolder);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(bookmarksFolder);
			}
			else {
				listener.onAfterUpdate(bookmarksFolder);
			}
		}

		return bookmarksFolder;
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder findByPrimaryKey(
		java.lang.String folderId)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(folderId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder findByGroupId_First(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder findByGroupId_Last(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder[] findByGroupId_PrevAndNext(
		java.lang.String folderId, java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_PrevAndNext(folderId, groupId, obc);
	}

	public static java.util.List findByG_U(java.lang.String groupId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U(groupId, userId);
	}

	public static java.util.List findByG_U(java.lang.String groupId,
		java.lang.String userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U(groupId, userId, begin, end);
	}

	public static java.util.List findByG_U(java.lang.String groupId,
		java.lang.String userId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U(groupId, userId, begin, end, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_U_First(
		java.lang.String groupId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_First(groupId, userId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_U_Last(
		java.lang.String groupId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_Last(groupId, userId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder[] findByG_U_PrevAndNext(
		java.lang.String folderId, java.lang.String groupId,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_PrevAndNext(folderId, groupId, userId, obc);
	}

	public static java.util.List findByG_P(java.lang.String groupId,
		java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_P(groupId, parentFolderId);
	}

	public static java.util.List findByG_P(java.lang.String groupId,
		java.lang.String parentFolderId, int begin, int end)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_P(groupId, parentFolderId, begin, end);
	}

	public static java.util.List findByG_P(java.lang.String groupId,
		java.lang.String parentFolderId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_P(groupId, parentFolderId, begin, end, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_P_First(
		java.lang.String groupId, java.lang.String parentFolderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_P_First(groupId, parentFolderId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_P_Last(
		java.lang.String groupId, java.lang.String parentFolderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_P_Last(groupId, parentFolderId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder[] findByG_P_PrevAndNext(
		java.lang.String folderId, java.lang.String groupId,
		java.lang.String parentFolderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_P_PrevAndNext(folderId, groupId,
			parentFolderId, obc);
	}

	public static java.util.List findByG_U_P(java.lang.String groupId,
		java.lang.String userId, java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_P(groupId, userId, parentFolderId);
	}

	public static java.util.List findByG_U_P(java.lang.String groupId,
		java.lang.String userId, java.lang.String parentFolderId, int begin,
		int end) throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_P(groupId, userId, parentFolderId, begin,
			end);
	}

	public static java.util.List findByG_U_P(java.lang.String groupId,
		java.lang.String userId, java.lang.String parentFolderId, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_P(groupId, userId, parentFolderId, begin,
			end, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_U_P_First(
		java.lang.String groupId, java.lang.String userId,
		java.lang.String parentFolderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_P_First(groupId, userId, parentFolderId,
			obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder findByG_U_P_Last(
		java.lang.String groupId, java.lang.String userId,
		java.lang.String parentFolderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_P_Last(groupId, userId, parentFolderId, obc);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder[] findByG_U_P_PrevAndNext(
		java.lang.String folderId, java.lang.String groupId,
		java.lang.String userId, java.lang.String parentFolderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.bookmarks.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_U_P_PrevAndNext(folderId, groupId, userId,
			parentFolderId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByGroupId(groupId);
	}

	public static void removeByG_U(java.lang.String groupId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_U(groupId, userId);
	}

	public static void removeByG_P(java.lang.String groupId,
		java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_P(groupId, parentFolderId);
	}

	public static void removeByG_U_P(java.lang.String groupId,
		java.lang.String userId, java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_U_P(groupId, userId, parentFolderId);
	}

	public static int countByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByGroupId(groupId);
	}

	public static int countByG_U(java.lang.String groupId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_U(groupId, userId);
	}

	public static int countByG_P(java.lang.String groupId,
		java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_P(groupId, parentFolderId);
	}

	public static int countByG_U_P(java.lang.String groupId,
		java.lang.String userId, java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderPersistence persistence = (BookmarksFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_U_P(groupId, userId, parentFolderId);
	}

	private static final Log _log = LogFactory.getLog(BookmarksFolderUtil.class);
}