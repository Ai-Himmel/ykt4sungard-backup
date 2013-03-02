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
import com.liferay.portlet.bookmarks.FolderNameException;
import com.liferay.portlet.bookmarks.NoSuchFolderException;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryUtil;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksEntryServiceUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksFolderLocalService;
import com.liferay.portlet.bookmarks.util.FolderLister;
import com.liferay.portlet.bookmarks.util.FolderView;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="BookmarksFolderLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class BookmarksFolderLocalServiceImpl
	implements BookmarksFolderLocalService {

	// Business methods

	public BookmarksFolder addFolder(
			String userId, String groupId, String parentFolderId, String name)
		throws PortalException, SystemException {

		User user = UserLocalServiceUtil.getUserById(userId);

		parentFolderId = _getParentFolderId(user, parentFolderId);

		_validate(name);

		String folderId = Long.toString(CounterServiceUtil.increment(
			BookmarksFolder.class.getName()));

		BookmarksFolder folder = BookmarksFolderUtil.create(folderId);

		Date now = new Date();

		folder.setGroupId(groupId);
		folder.setCompanyId(user.getCompanyId());
		folder.setUserId(user.getUserId());
		folder.setCreateDate(now);
		folder.setModifiedDate(now);
		folder.setParentFolderId(parentFolderId);
		folder.setName(name);

		BookmarksFolderUtil.update(folder);

		return folder;
	}

	public void deleteAllByGroup(String groupId)
		throws PortalException, SystemException {

		Iterator itr1 = BookmarksFolderUtil.findByGroupId(groupId).iterator();

		while (itr1.hasNext()) {
			BookmarksFolder folder = (BookmarksFolder)itr1.next();

			List childEntries = BookmarksEntryUtil.findByG_F(
				groupId, folder.getFolderId());

			Iterator itr2 = childEntries.iterator();

			while (itr2.hasNext()) {
				BookmarksEntryServiceUtil.deleteEntry(
					(BookmarksEntry)itr2.next());
			}

			BookmarksFolderUtil.remove(folder.getFolderId());
		}
	}

	public void deleteAllByUser(String userId)
		throws PortalException, SystemException {

		Iterator itr1 = BookmarksFolderUtil.findByG_U(
			Group.DEFAULT_PARENT_GROUP_ID, userId).iterator();

		while (itr1.hasNext()) {
			BookmarksFolder folder = (BookmarksFolder)itr1.next();

			List childEntries = BookmarksEntryUtil.findByG_U_F(
				Group.DEFAULT_PARENT_GROUP_ID, userId, folder.getFolderId());

			Iterator itr2 = childEntries.iterator();

			while (itr2.hasNext()) {
				BookmarksEntryServiceUtil.deleteEntry(
					(BookmarksEntry)itr2.next());
			}

			BookmarksFolderUtil.remove(folder.getFolderId());
		}
	}

	public void deleteFolder(String folderId)
		throws PortalException, SystemException {

		BookmarksFolder folder = BookmarksFolderUtil.findByPrimaryKey(folderId);

		deleteFolder(folder);
	}

	public void deleteFolder(BookmarksFolder folder)
		throws PortalException, SystemException {

		List childFolders = null;
		if (folder.getGroupId().equals(Group.DEFAULT_PARENT_GROUP_ID)) {
			childFolders = BookmarksFolderUtil.findByG_U_P(
				folder.getGroupId(), folder.getUserId(), folder.getFolderId());
		}
		else {
			childFolders = BookmarksFolderUtil.findByG_P(
				folder.getGroupId(), folder.getFolderId());
		}

		Iterator itr = childFolders.iterator();

		while (itr.hasNext()) {
			deleteFolder((BookmarksFolder)itr.next());
		}

		List childEntries = null;
		if (folder.getGroupId().equals(Group.DEFAULT_PARENT_GROUP_ID)) {
			childEntries = BookmarksEntryUtil.findByG_U_F(
				folder.getGroupId(), folder.getUserId(), folder.getFolderId());
		}
		else {
			childEntries = BookmarksEntryUtil.findByG_F(
				folder.getGroupId(), folder.getFolderId());
		}

		while (itr.hasNext()) {
			BookmarksEntryServiceUtil.deleteEntry((BookmarksEntry)itr.next());
		}

		BookmarksFolderUtil.remove(folder.getFolderId());
	}

	public BookmarksFolder getFolder(String folderId)
		throws PortalException, SystemException {

		return BookmarksFolderUtil.findByPrimaryKey(folderId);
	}

	public List getFolders(
			String groupId, String userId, String parentFolderId)
		throws SystemException {

		if (groupId.equals(Group.DEFAULT_PARENT_GROUP_ID)) {
			return BookmarksFolderUtil.findByG_U_P(
				groupId, userId, parentFolderId);
		}
		else {
			return BookmarksFolderUtil.findByG_P(groupId, parentFolderId);
		}
	}

	public FolderView getFolderView(String groupId, String userId)
		throws SystemException {

		return new FolderLister().getFolderView(groupId, userId);
	}

	public String getPath(String folderId)
		throws PortalException, SystemException {

		String path = "";

		while (!folderId.equals(BookmarksFolder.DEFAULT_PARENT_FOLDER_ID)) {
			try {
				BookmarksFolder folder =
					BookmarksFolderUtil.findByPrimaryKey(folderId);

				path = "/" + folder.getName() + path;

				folderId = folder.getParentFolderId();
			}
			catch (NoSuchFolderException nsfe) {
				folderId = BookmarksFolder.DEFAULT_PARENT_FOLDER_ID;
			}
		}

		if (path.equals("")) {
			path = "/";
		}

		return path;
	}

	public BookmarksFolder updateFolder(
			String userId, String folderId, String parentFolderId, String name)
		throws PortalException, SystemException {

		User user = UserLocalServiceUtil.getUserById(userId);

		parentFolderId = _getParentFolderId(user, parentFolderId);

		_validate(name);

		BookmarksFolder folder = BookmarksFolderUtil.findByPrimaryKey(folderId);

		folder.setModifiedDate(new Date());
		folder.setParentFolderId(parentFolderId);
		folder.setName(name);

		BookmarksFolderUtil.update(folder);

		return folder;
	}

	// Private methods

	private String _getParentFolderId(User user, String parentFolderId)
		throws SystemException {

		if (!parentFolderId.equals(BookmarksFolder.DEFAULT_PARENT_FOLDER_ID)) {

			// Ensure folder exists and belongs to the proper company

			try {
				BookmarksFolder parentFolder =
					BookmarksFolderUtil.findByPrimaryKey(parentFolderId);

				if (!parentFolder.getCompanyId().equals(user.getCompanyId())) {
					parentFolderId = BookmarksFolder.DEFAULT_PARENT_FOLDER_ID;
				}
			}
			catch (NoSuchFolderException nsfe) {
				parentFolderId = BookmarksFolder.DEFAULT_PARENT_FOLDER_ID;
			}
		}

		return parentFolderId;
	}

	private void _validate(String name) throws PortalException {
		if ((Validator.isNull(name)) || (name.indexOf("\\\\") != -1) ||
			(name.indexOf("//") != -1)) {

			throw new FolderNameException();
		}
	}

}