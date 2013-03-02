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

package com.liferay.portlet.bookmarks.service.http;

import com.liferay.portlet.bookmarks.service.spring.BookmarksFolderServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="BookmarksFolderServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BookmarksFolderServiceSoap {
	public static com.liferay.portlet.bookmarks.model.BookmarksFolderModel addFolder(
		java.lang.String groupId, java.lang.String parentFolderId,
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portlet.bookmarks.model.BookmarksFolder returnValue = BookmarksFolderServiceUtil.addFolder(groupId,
					parentFolderId, name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFolder(java.lang.String folderId)
		throws RemoteException {
		try {
			BookmarksFolderServiceUtil.deleteFolder(folderId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFolder(
		com.liferay.portlet.bookmarks.model.BookmarksFolder folder)
		throws RemoteException {
		try {
			BookmarksFolderServiceUtil.deleteFolder(folder);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolderModel getFolder(
		java.lang.String folderId) throws RemoteException {
		try {
			com.liferay.portlet.bookmarks.model.BookmarksFolder returnValue = BookmarksFolderServiceUtil.getFolder(folderId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolderModel[] getFolders(
		java.lang.String groupId, java.lang.String parentFolderId)
		throws RemoteException {
		try {
			java.util.List returnValue = BookmarksFolderServiceUtil.getFolders(groupId,
					parentFolderId);

			return (com.liferay.portlet.bookmarks.model.BookmarksFolder[])returnValue.toArray(new com.liferay.portlet.bookmarks.model.BookmarksFolder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.bookmarks.util.FolderView getFolderView(
		java.lang.String groupId) throws RemoteException {
		try {
			com.liferay.portlet.bookmarks.util.FolderView returnValue = BookmarksFolderServiceUtil.getFolderView(groupId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getPath(java.lang.String folderId)
		throws RemoteException {
		try {
			java.lang.String returnValue = BookmarksFolderServiceUtil.getPath(folderId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolderModel updateFolder(
		java.lang.String folderId, java.lang.String parentFolderId,
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portlet.bookmarks.model.BookmarksFolder returnValue = BookmarksFolderServiceUtil.updateFolder(folderId,
					parentFolderId, name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}