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

import com.liferay.portlet.bookmarks.service.spring.BookmarksEntryServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="BookmarksEntryServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BookmarksEntryServiceSoap {
	public static com.liferay.portlet.bookmarks.model.BookmarksEntryModel addEntry(
		java.lang.String groupId, java.lang.String folderId,
		java.lang.String name, java.lang.String url, java.lang.String comments)
		throws RemoteException {
		try {
			com.liferay.portlet.bookmarks.model.BookmarksEntry returnValue = BookmarksEntryServiceUtil.addEntry(groupId,
					folderId, name, url, comments);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteEntry(java.lang.String entryId)
		throws RemoteException {
		try {
			BookmarksEntryServiceUtil.deleteEntry(entryId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteEntry(
		com.liferay.portlet.bookmarks.model.BookmarksEntry entry)
		throws RemoteException {
		try {
			BookmarksEntryServiceUtil.deleteEntry(entry);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntryModel getEntry(
		java.lang.String entryId) throws RemoteException {
		try {
			com.liferay.portlet.bookmarks.model.BookmarksEntry returnValue = BookmarksEntryServiceUtil.getEntry(entryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntryModel[] getEntries(
		java.lang.String groupId, java.lang.String folderId)
		throws RemoteException {
		try {
			java.util.List returnValue = BookmarksEntryServiceUtil.getEntries(groupId,
					folderId);

			return (com.liferay.portlet.bookmarks.model.BookmarksEntry[])returnValue.toArray(new com.liferay.portlet.bookmarks.model.BookmarksEntry[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntryModel openEntry(
		java.lang.String entryId) throws RemoteException {
		try {
			com.liferay.portlet.bookmarks.model.BookmarksEntry returnValue = BookmarksEntryServiceUtil.openEntry(entryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksEntryModel updateEntry(
		java.lang.String entryId, java.lang.String folderId,
		java.lang.String name, java.lang.String url, java.lang.String comments)
		throws RemoteException {
		try {
			com.liferay.portlet.bookmarks.model.BookmarksEntry returnValue = BookmarksEntryServiceUtil.updateEntry(entryId,
					folderId, name, url, comments);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}