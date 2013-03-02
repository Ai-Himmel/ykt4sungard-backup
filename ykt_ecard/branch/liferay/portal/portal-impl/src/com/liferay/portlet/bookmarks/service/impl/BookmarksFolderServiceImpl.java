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

package com.liferay.portlet.bookmarks.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.bookmarks.service.base.BookmarksFolderServiceBaseImpl;
import com.liferay.portlet.bookmarks.service.permission.BookmarksFolderPermission;

/**
 * <a href="BookmarksFolderServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BookmarksFolderServiceImpl extends BookmarksFolderServiceBaseImpl {

	public BookmarksFolder addFolder(
			long plid, long parentFolderId, String name, String description,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		BookmarksFolderPermission.check(
			getPermissionChecker(), plid, parentFolderId,
			ActionKeys.ADD_FOLDER);

		return bookmarksFolderLocalService.addFolder(
			getUserId(), plid, parentFolderId, name, description,
			addCommunityPermissions, addGuestPermissions);
	}

	public BookmarksFolder addFolder(
			long plid, long parentFolderId, String name, String description,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		BookmarksFolderPermission.check(
			getPermissionChecker(), plid, parentFolderId,
			ActionKeys.ADD_FOLDER);

		return bookmarksFolderLocalService.addFolder(
			getUserId(), plid, parentFolderId, name, description,
			communityPermissions, guestPermissions);
	}

	public void deleteFolder(long folderId)
		throws PortalException, SystemException {

		BookmarksFolderPermission.check(
			getPermissionChecker(), folderId, ActionKeys.DELETE);

		bookmarksFolderLocalService.deleteFolder(folderId);
	}

	public BookmarksFolder getFolder(long folderId)
		throws PortalException, SystemException {

		BookmarksFolderPermission.check(
			getPermissionChecker(), folderId, ActionKeys.VIEW);

		return bookmarksFolderLocalService.getFolder(folderId);
	}

	public BookmarksFolder updateFolder(
			long folderId, long parentFolderId, String name,
			String description, boolean mergeWithParentFolder)
		throws PortalException, SystemException {

		BookmarksFolderPermission.check(
			getPermissionChecker(), folderId, ActionKeys.UPDATE);

		return bookmarksFolderLocalService.updateFolder(
			folderId, parentFolderId, name, description, mergeWithParentFolder);
	}

}