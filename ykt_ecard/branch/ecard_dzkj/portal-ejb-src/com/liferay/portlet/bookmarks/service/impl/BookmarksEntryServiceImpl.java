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
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksEntryLocalServiceUtil;
import com.liferay.portlet.bookmarks.service.spring.BookmarksEntryService;

import java.util.List;

/**
 * <a href="BookmarksEntryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class BookmarksEntryServiceImpl
	extends PrincipalBean implements BookmarksEntryService {

	// Business methods

	public BookmarksEntry addEntry(
			String groupId, String folderId, String name, String url,
			String comments)
		throws PortalException, SystemException {

		return BookmarksEntryLocalServiceUtil.addEntry(
			getUserId(), groupId, folderId, name, url, comments);
	}

	public void deleteEntry(String entryId)
		throws PortalException, SystemException {

		BookmarksEntry entry = BookmarksEntryUtil.findByPrimaryKey(entryId);

		deleteEntry(entry);
	}

	public void deleteEntry(BookmarksEntry entry)
		throws PortalException, SystemException {

		BookmarksEntryLocalServiceUtil.deleteEntry(entry.getEntryId());
	}

	public BookmarksEntry getEntry(String entryId)
		throws PortalException, SystemException {

		return BookmarksEntryLocalServiceUtil.getEntry(entryId);
	}

	public List getEntries(String groupId, String folderId)
		throws PortalException, SystemException {

		return BookmarksEntryLocalServiceUtil.getEntries(
			groupId, getUserId(), folderId);
	}

	public BookmarksEntry openEntry(String entryId)
		throws PortalException, SystemException {

		BookmarksEntry entry = BookmarksEntryUtil.findByPrimaryKey(entryId);

		return BookmarksEntryLocalServiceUtil.openEntry(entryId);
	}

	public BookmarksEntry updateEntry(
			String entryId, String folderId, String name, String url,
			String comments)
		throws PortalException, SystemException {

		BookmarksEntry entry = BookmarksEntryUtil.findByPrimaryKey(entryId);

		return BookmarksEntryLocalServiceUtil.updateEntry(
			getUserId(), entryId, folderId, name, url, comments);
	}

}