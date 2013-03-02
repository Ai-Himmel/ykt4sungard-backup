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

package com.liferay.portlet.bookmarks.service.spring;

/**
 * <a href="BookmarksFolderRemoteServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BookmarksFolderRemoteServiceUtil {
	public static com.liferay.portlet.bookmarks.model.BookmarksFolder addFolder(
		java.lang.String userId, java.lang.String groupId,
		java.lang.String parentFolderId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();

			return bookmarksFolderRemoteService.addFolder(userId, groupId,
				parentFolderId, name);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteAllByGroup(java.lang.String groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();
			bookmarksFolderRemoteService.deleteAllByGroup(groupId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteAllByUser(java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();
			bookmarksFolderRemoteService.deleteAllByUser(userId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteFolder(java.lang.String folderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();
			bookmarksFolderRemoteService.deleteFolder(folderId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteFolder(
		com.liferay.portlet.bookmarks.model.BookmarksFolder folder)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();
			bookmarksFolderRemoteService.deleteFolder(folder);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder getFolder(
		java.lang.String folderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();

			return bookmarksFolderRemoteService.getFolder(folderId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getFolders(java.lang.String groupId,
		java.lang.String userId, java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();

			return bookmarksFolderRemoteService.getFolders(groupId, userId,
				parentFolderId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.bookmarks.util.FolderView getFolderView(
		java.lang.String groupId, java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();

			return bookmarksFolderRemoteService.getFolderView(groupId, userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.lang.String getPath(java.lang.String folderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();

			return bookmarksFolderRemoteService.getPath(folderId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder updateFolder(
		java.lang.String userId, java.lang.String folderId,
		java.lang.String parentFolderId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BookmarksFolderRemoteService bookmarksFolderRemoteService = BookmarksFolderRemoteServiceFactory.getService();

			return bookmarksFolderRemoteService.updateFolder(userId, folderId,
				parentFolderId, name);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}