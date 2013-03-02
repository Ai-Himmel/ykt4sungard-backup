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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksFolderLocalServiceUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksFolderService;
import com.liferay.portlet.bookmarks.util.FolderView;

import java.util.List;

/**
 * <a href="BookmarksFolderServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class BookmarksFolderServiceImpl
	extends PrincipalBean implements BookmarksFolderService {

	// Business methods

	public BookmarksFolder addFolder(
			String groupId, String parentFolderId, String name)
		throws PortalException, SystemException {

		return BookmarksFolderLocalServiceUtil.addFolder(
			getUserId(), groupId, parentFolderId, name);
	}

	public void deleteFolder(String folderId)
		throws PortalException, SystemException {

		BookmarksFolder folder = BookmarksFolderUtil.findByPrimaryKey(folderId);

		deleteFolder(folder);
	}

	public void deleteFolder(BookmarksFolder folder)
		throws PortalException, SystemException {

		BookmarksFolderLocalServiceUtil.deleteFolder(folder);
	}

	public BookmarksFolder getFolder(String folderId)
		throws PortalException, SystemException {

		return BookmarksFolderLocalServiceUtil.getFolder(folderId);
	}

	public List getFolders(String groupId, String parentFolderId)
		throws PortalException, SystemException {

		return BookmarksFolderLocalServiceUtil.getFolders(
			groupId, getUserId(), parentFolderId);
	}

	public FolderView getFolderView(String groupId)
		throws PortalException, SystemException {

		return BookmarksFolderLocalServiceUtil.getFolderView(
			groupId, getUserId());
	}

	public String getPath(String folderId)
		throws PortalException, SystemException {

		return BookmarksFolderLocalServiceUtil.getPath(folderId);
	}

	public BookmarksFolder updateFolder(
			String folderId, String parentFolderId, String name)
		throws PortalException, SystemException {

		BookmarksFolder folder = BookmarksFolderUtil.findByPrimaryKey(folderId);

		return BookmarksFolderLocalServiceUtil.updateFolder(
			getUserId(), folderId, parentFolderId, name);
	}

}