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

package com.liferay.portlet.documentlibrary.util;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PropsValues;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceUtil;
import com.liferay.util.CollectionFactory;

import java.util.Set;

import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

import javax.servlet.jsp.PageContext;

/**
 * <a href="DLUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLUtil {

	public static String getBreadcrumbs(
			long folderId, String name, PageContext pageContext,
			RenderRequest req, RenderResponse res)
		throws Exception {

		if ((folderId > 0) && Validator.isNotNull(name)) {
			DLFileEntry fileEntry = DLFileEntryLocalServiceUtil.getFileEntry(
				folderId, name);

			return getBreadcrumbs(
				fileEntry.getFolder(), fileEntry, pageContext, req, res);
		}
		else {
			DLFolder folder = null;

			try {
				folder = DLFolderLocalServiceUtil.getFolder(folderId);
			}
			catch (Exception e) {
			}

			return getBreadcrumbs(folder, null, pageContext, req, res);
		}
	}

	public static String getBreadcrumbs(
			DLFolder folder, DLFileEntry fileEntry, PageContext pageContext,
			RenderRequest req, RenderResponse res)
		throws Exception {

		long groupId = ParamUtil.getLong(req, "groupId");

		if ((fileEntry != null) && (folder == null)) {
			folder = fileEntry.getFolder();
		}

		PortletURL foldersURL = res.createRenderURL();

		WindowState windowState = req.getWindowState();

		if (windowState.equals(LiferayWindowState.POP_UP)) {
			foldersURL.setWindowState(LiferayWindowState.POP_UP);

			String strutsAction = ParamUtil.getString(req, "struts_action");

			foldersURL.setParameter("struts_action", strutsAction);
			foldersURL.setParameter("groupId", String.valueOf(groupId));
		}
		else {
			//foldersURL.setWindowState(WindowState.MAXIMIZED);

			foldersURL.setParameter("struts_action", "/document_library/view");
		}

		String foldersLink =
			"<a href=\"" + foldersURL.toString() + "\">" +
				LanguageUtil.get(pageContext, "folders") + "</a>";

		if (folder == null) {
			return foldersLink;
		}

		String breadcrumbs = StringPool.BLANK;

		if (folder != null) {
			for (int i = 0;; i++) {
				folder = folder.toEscapedModel();

				PortletURL portletURL = res.createRenderURL();

				if (windowState.equals(LiferayWindowState.POP_UP)) {
					portletURL.setWindowState(LiferayWindowState.POP_UP);

					String strutsAction = ParamUtil.getString(
						req, "struts_action");

					portletURL.setParameter("struts_action", strutsAction);
					portletURL.setParameter("groupId", String.valueOf(groupId));
					portletURL.setParameter(
						"folderId", String.valueOf(folder.getFolderId()));
				}
				else {
					portletURL.setWindowState(WindowState.MAXIMIZED);

					portletURL.setParameter(
						"struts_action", "/document_library/view");
					portletURL.setParameter(
						"folderId", String.valueOf(folder.getFolderId()));
				}

				String folderLink =
					"<a href=\"" + portletURL.toString() + "\">" +
						folder.getName() + "</a>";

				if (i == 0) {
					breadcrumbs = folderLink;
				}
				else {
					breadcrumbs = folderLink + " &raquo; " + breadcrumbs;
				}

				if (folder.isRoot()) {
					break;
				}

				folder = DLFolderLocalServiceUtil.getFolder(
					folder.getParentFolderId());
			}
		}

		breadcrumbs = foldersLink + " &raquo; " + breadcrumbs;

		if (fileEntry != null) {
			fileEntry = fileEntry.toEscapedModel();

			PortletURL fileEntryURL = res.createRenderURL();

			fileEntryURL.setWindowState(WindowState.MAXIMIZED);

			fileEntryURL.setParameter(
				"struts_action", "/document_library/edit_file_entry");
			fileEntryURL.setParameter(
				"folderId", String.valueOf(fileEntry.getFolderId()));
			fileEntryURL.setParameter("name", fileEntry.getName());

			String fileEntryLink =
				"<a href=\"" + fileEntryURL.toString() + "\">" +
					fileEntry.getName() + "</a>";

			breadcrumbs = breadcrumbs + " &raquo; " + fileEntryLink;
		}

		return breadcrumbs;
	}

	public static String getFileExtension(String name) {
		return _instance._getFileExtension(name);
	}

	public static String getLockId(long folderId, String name) {
		StringMaker sm = new StringMaker();

		sm.append(folderId);
		sm.append(StringPool.POUND);
		sm.append(name);

		return sm.toString();
	}

	private DLUtil() {
		_fileExtensions = CollectionFactory.getHashSet();

		String[] fileExtensions = PropsValues.DL_FILE_EXTENSIONS;

		for (int i = 0; i < fileExtensions.length; i++) {

			// Only process non wildcard extensions

			if (!StringPool.STAR.equals(fileExtensions[i])) {

				// Strip starting period

				String extension = fileExtensions[i];
				extension = extension.substring(1, extension.length());

				_fileExtensions.add(extension);
			}
		}
	}

	private String _getFileExtension(String name) {
		String extension = StringPool.BLANK;

		int pos = name.lastIndexOf(StringPool.PERIOD);

		if (pos != -1) {
			extension = name.substring(pos + 1, name.length()).toLowerCase();
		}

		if (!_fileExtensions.contains(extension)) {
			extension = _DEFAULT_FILE_EXTENSION;
		}

		return extension;
	}

	private static final String _DEFAULT_FILE_EXTENSION = "page";

	private static DLUtil _instance = new DLUtil();

	private Set _fileExtensions;

}