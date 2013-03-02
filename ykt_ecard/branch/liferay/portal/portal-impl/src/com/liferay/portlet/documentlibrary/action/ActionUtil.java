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

package com.liferay.portlet.documentlibrary.action;

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.documentlibrary.NoSuchFileEntryException;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.DLFileShortcut;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl;
import com.liferay.portlet.documentlibrary.service.DLFileEntryServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFileShortcutServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFolderServiceUtil;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActionUtil {

	public static void getFileEntry(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFileEntry(httpReq);
	}

	public static void getFileEntry(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFileEntry(httpReq);
	}

	public static void getFileEntry(HttpServletRequest req) throws Exception {
		long folderId = ParamUtil.getLong(req, "folderId");
		long newFolderId = ParamUtil.getLong(req, "newFolderId");
		String name = ParamUtil.getString(req, "name");

		DLFileEntry fileEntry = null;

		if ((folderId > 0) && Validator.isNotNull(name)) {
			try {
				fileEntry = DLFileEntryServiceUtil.getFileEntry(folderId, name);
			}
			catch (NoSuchFileEntryException nsfe) {

				// This only happens when you're moving a file to a different
				// folder

				fileEntry = DLFileEntryServiceUtil.getFileEntry(
					newFolderId, name);
			}
		}

		req.setAttribute(WebKeys.DOCUMENT_LIBRARY_FILE_ENTRY, fileEntry);
	}

	public static void getFileShortcut(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFileShortcut(httpReq);
	}

	public static void getFileShortcut(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFileShortcut(httpReq);
	}

	public static void getFileShortcut(HttpServletRequest req)
		throws Exception {

		long fileShortcutId = ParamUtil.getLong(req, "fileShortcutId");

		DLFileShortcut fileShortcut = null;

		if (fileShortcutId > 0) {
			fileShortcut = DLFileShortcutServiceUtil.getFileShortcut(
				fileShortcutId);
		}

		req.setAttribute(WebKeys.DOCUMENT_LIBRARY_FILE_SHORTCUT, fileShortcut);
	}

	public static void getFolder(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFolder(httpReq);
	}

	public static void getFolder(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFolder(httpReq);
	}

	public static void getFolder(HttpServletRequest req) throws Exception {
		long folderId = ParamUtil.getLong(req, "folderId");

		DLFolder folder = null;

		if ((folderId > 0) &&
			(folderId != DLFolderImpl.DEFAULT_PARENT_FOLDER_ID)) {

			folder = DLFolderServiceUtil.getFolder(folderId);
		}

		req.setAttribute(WebKeys.DOCUMENT_LIBRARY_FOLDER, folder);
	}

}