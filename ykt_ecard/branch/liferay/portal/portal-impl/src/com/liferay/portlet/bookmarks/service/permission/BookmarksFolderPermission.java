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

package com.liferay.portlet.bookmarks.service.permission;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.bookmarks.model.impl.BookmarksFolderImpl;
import com.liferay.portlet.bookmarks.service.BookmarksFolderLocalServiceUtil;

/**
 * <a href="BookmarksFolderPermission.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BookmarksFolderPermission {

	public static void check(
			PermissionChecker permissionChecker, long plid, long folderId,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, plid, folderId, actionId)) {
			throw new PrincipalException();
		}
	}

	public static void check(
			PermissionChecker permissionChecker, long folderId,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, folderId, actionId)) {
			throw new PrincipalException();
		}
	}

	public static void check(
			PermissionChecker permissionChecker, BookmarksFolder folder,
			String actionId)
		throws PortalException, SystemException {

		if (!contains(permissionChecker, folder, actionId)) {
			throw new PrincipalException();
		}
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long plid, long folderId,
			String actionId)
		throws PortalException, SystemException {

		if (folderId == BookmarksFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
			return PortletPermissionUtil.contains(
				permissionChecker, plid, PortletKeys.BOOKMARKS, actionId);
		}
		else {
			return contains(permissionChecker, folderId, actionId);
		}
	}

	public static boolean contains(
			PermissionChecker permissionChecker, long folderId,
			String actionId)
		throws PortalException, SystemException {

		BookmarksFolder folder =
			BookmarksFolderLocalServiceUtil.getFolder(folderId);

		return contains(permissionChecker, folder, actionId);
	}

	public static boolean contains(
			PermissionChecker permissionChecker, BookmarksFolder folder,
			String actionId)
		throws PortalException, SystemException {

		if (actionId.equals(ActionKeys.ADD_FOLDER)) {
			actionId = ActionKeys.ADD_SUBFOLDER;
		}

		long folderId = folder.getFolderId();

		while (folderId != BookmarksFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
			folder = BookmarksFolderLocalServiceUtil.getFolder(folderId);

			folderId = folder.getParentFolderId();

			if (permissionChecker.hasPermission(
					folder.getGroupId(), BookmarksFolder.class.getName(),
					folder.getFolderId(), actionId)) {

				return true;
			}

			if (actionId.equals(ActionKeys.VIEW)) {
				break;
			}
		}

		return false;
	}

}