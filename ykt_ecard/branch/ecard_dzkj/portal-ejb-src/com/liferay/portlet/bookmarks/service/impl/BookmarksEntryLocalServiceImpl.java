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

package com.liferay.portlet.bookmarks.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portlet.bookmarks.EntryURLException;
import com.liferay.portlet.bookmarks.NoSuchFolderException;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryUtil;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksEntryLocalService;
import com.liferay.util.Validator;

import java.net.MalformedURLException;
import java.net.URL;

import java.util.Date;
import java.util.List;

/**
 * <a href="BookmarksEntryLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class BookmarksEntryLocalServiceImpl
	implements BookmarksEntryLocalService {

	// Business methods

	public BookmarksEntry addEntry(
			String userId, String groupId, String folderId, String name,
			String url, String comments)
		throws PortalException, SystemException {

		User user = UserLocalServiceUtil.getUserById(userId);

		folderId = _getFolderId(user, folderId);

		_validate(url);

		String entryId = Long.toString(CounterServiceUtil.increment(
			BookmarksEntry.class.getName()));

		BookmarksEntry entry = BookmarksEntryUtil.create(entryId);

		Date now = new Date();

		if (Validator.isNull(name)) {
			name = url;
		}

		entry.setGroupId(groupId);
		entry.setCompanyId(user.getCompanyId());
		entry.setUserId(user.getUserId());
		entry.setCreateDate(now);
		entry.setModifiedDate(now);
		entry.setFolderId(folderId);
		entry.setName(name);
		entry.setUrl(url);
		entry.setComments(comments);

		BookmarksEntryUtil.update(entry);

		return entry;
	}

	public void deleteAllByGroup(String groupId) throws SystemException {
		BookmarksEntryUtil.removeByGroupId(groupId);
	}

	public void deleteAllByUser(String userId) throws SystemException {
		BookmarksEntryUtil.removeByG_U(Group.DEFAULT_PARENT_GROUP_ID, userId);
	}

	public void deleteEntry(String entryId)
		throws PortalException, SystemException {

		BookmarksEntryUtil.remove(entryId);
	}

	public BookmarksEntry getEntry(String entryId)
		throws PortalException, SystemException {

		return BookmarksEntryUtil.findByPrimaryKey(entryId);
	}

	public List getEntries(String groupId, String userId, String folderId)
		throws SystemException {

		if (groupId.equals(Group.DEFAULT_PARENT_GROUP_ID)) {
			return BookmarksEntryUtil.findByG_U_F(groupId, userId, folderId);
		}
		else {
			return BookmarksEntryUtil.findByG_F(groupId, folderId);
		}
	}

	public BookmarksEntry openEntry(String entryId)
		throws PortalException, SystemException {

		BookmarksEntry entry = BookmarksEntryUtil.findByPrimaryKey(entryId);

		entry.setVisits(entry.getVisits() + 1);

		BookmarksEntryUtil.update(entry);

		return entry;
	}

	public BookmarksEntry updateEntry(
			String userId, String entryId, String folderId, String name,
			String url, String comments)
		throws PortalException, SystemException {

		User user = UserLocalServiceUtil.getUserById(userId);

		folderId = _getFolderId(user, folderId);

		_validate(url);

		BookmarksEntry entry = BookmarksEntryUtil.findByPrimaryKey(entryId);

		if (Validator.isNull(name)) {
			name = url;
		}

		entry.setModifiedDate(new Date());
		entry.setFolderId(folderId);
		entry.setName(name);
		entry.setUrl(url);
		entry.setComments(comments);

		BookmarksEntryUtil.update(entry);

		return entry;
	}

	// Private methods

	private String _getFolderId(User user, String folderId)
		throws SystemException {

		if (!folderId.equals(BookmarksFolder.DEFAULT_PARENT_FOLDER_ID)) {

			// Ensure folder exists and belongs to the proper company

			try {
				BookmarksFolder folder =
					BookmarksFolderUtil.findByPrimaryKey(folderId);

				if (!folder.getCompanyId().equals(user.getCompanyId())) {
					folderId = BookmarksFolder.DEFAULT_PARENT_FOLDER_ID;
				}
			}
			catch (NoSuchFolderException nsfe) {
				folderId = BookmarksFolder.DEFAULT_PARENT_FOLDER_ID;
			}
		}

		return folderId;
	}

	private void _validate(String url) throws PortalException {
		if (Validator.isNull(url)) {
			throw new EntryURLException();
		}
		else {
			try {
				new URL(url);
			}
			catch (MalformedURLException murle) {
				throw new EntryURLException();
			}
		}
	}

}