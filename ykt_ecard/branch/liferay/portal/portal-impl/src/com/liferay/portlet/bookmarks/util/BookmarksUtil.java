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

package com.liferay.portlet.bookmarks.util;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.bookmarks.service.BookmarksEntryLocalServiceUtil;
import com.liferay.portlet.bookmarks.service.BookmarksFolderLocalServiceUtil;
import com.liferay.portlet.bookmarks.util.comparator.EntryCreateDateComparator;
import com.liferay.portlet.bookmarks.util.comparator.EntryModifiedDateComparator;
import com.liferay.portlet.bookmarks.util.comparator.EntryNameComparator;
import com.liferay.portlet.bookmarks.util.comparator.EntryPriorityComparator;
import com.liferay.portlet.bookmarks.util.comparator.EntryURLComparator;
import com.liferay.portlet.bookmarks.util.comparator.EntryVisitsComparator;

import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

import javax.servlet.jsp.PageContext;

/**
 * <a href="BookmarksUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BookmarksUtil {

	public static String getBreadcrumbs(
			long folderId, long entryId, PageContext pageContext,
			RenderRequest req, RenderResponse res)
		throws Exception {

		if (entryId > 0) {
			BookmarksEntry entry =
				BookmarksEntryLocalServiceUtil.getEntry(entryId);

			return getBreadcrumbs(
				entry.getFolder(), entry, pageContext, req, res);
		}
		else {
			BookmarksFolder folder = null;

			try {
				folder = BookmarksFolderLocalServiceUtil.getFolder(folderId);
			}
			catch (Exception e) {
			}

			return getBreadcrumbs(folder, null, pageContext, req, res);
		}
	}

	public static String getBreadcrumbs(
			BookmarksFolder folder, BookmarksEntry entry,
			PageContext pageContext, RenderRequest req, RenderResponse res)
		throws Exception {

		if ((entry != null) && (folder == null)) {
			folder = entry.getFolder();
		}

		PortletURL foldersURL = res.createRenderURL();

		WindowState windowState = req.getWindowState();

		if (windowState.equals(LiferayWindowState.POP_UP)) {
			foldersURL.setWindowState(LiferayWindowState.POP_UP);

			foldersURL.setParameter("struts_action", "/bookmarks/select_folder");
		}
		else {
			foldersURL.setWindowState(WindowState.MAXIMIZED);

			foldersURL.setParameter("struts_action", "/bookmarks/view");
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

					portletURL.setParameter(
						"struts_action", "/bookmarks/select_folder");
					portletURL.setParameter(
						"folderId", String.valueOf(folder.getFolderId()));
				}
				else {
					portletURL.setWindowState(WindowState.MAXIMIZED);

					portletURL.setParameter("struts_action", "/bookmarks/view");
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

				folder = BookmarksFolderLocalServiceUtil.getFolder(
					folder.getParentFolderId());
			}
		}

		breadcrumbs = foldersLink + " &raquo; " + breadcrumbs;

		if (entry != null) {
			entry = entry.toEscapedModel();

			PortletURL entryURL = res.createRenderURL();

			entryURL.setWindowState(WindowState.MAXIMIZED);

			entryURL.setParameter("struts_action", "/bookmarks/edit_entry");
			entryURL.setParameter(
				"entryId", String.valueOf(entry.getEntryId()));

			String entryLink =
				"<a href=\"" + entryURL.toString() + "\">" +
					entry.getEntryId() + "</a>";

			breadcrumbs = breadcrumbs + " &raquo; " + entryLink;
		}

		return breadcrumbs;
	}

	public static OrderByComparator getEntriesOrderByComparator(
		String orderByCol, String orderByType) {

		boolean orderByAsc = false;

		if (orderByType.equals("asc")) {
			orderByAsc = true;
		}

		OrderByComparator orderByComparator = null;

		if (orderByCol.equals("create-date")) {
			orderByComparator = new EntryCreateDateComparator(orderByAsc);
		}
		else if (orderByCol.equals("modified-date")) {
			orderByComparator = new EntryModifiedDateComparator(orderByAsc);
		}
		else if (orderByCol.equals("name")) {
			orderByComparator = new EntryNameComparator(orderByAsc);
		}
		else if (orderByCol.equals("priority")) {
			orderByComparator = new EntryPriorityComparator(orderByAsc);
		}
		else if (orderByCol.equals("url")) {
			orderByComparator = new EntryURLComparator(orderByAsc);
		}
		else if (orderByCol.equals("visits")) {
			orderByComparator = new EntryVisitsComparator(orderByAsc);
		}

		return orderByComparator;
	}

}