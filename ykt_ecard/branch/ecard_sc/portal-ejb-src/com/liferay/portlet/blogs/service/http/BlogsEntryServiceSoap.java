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

package com.liferay.portlet.blogs.service.http;

import com.liferay.portlet.blogs.service.spring.BlogsEntryServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="BlogsEntryServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsEntryServiceSoap {
	public static com.liferay.portlet.blogs.model.BlogsEntryModel addEntry(
		java.lang.String categoryId, java.lang.String title,
		java.lang.String content, int displayMonth, int displayDay,
		int displayYear, int displayHour, int displayMinute, boolean sharing,
		boolean commentable) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsEntry returnValue = BlogsEntryServiceUtil.addEntry(categoryId,
					title, content, displayMonth, displayDay, displayYear,
					displayHour, displayMinute, sharing, commentable);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteEntry(java.lang.String entryId)
		throws RemoteException {
		try {
			BlogsEntryServiceUtil.deleteEntry(entryId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteEntry(
		com.liferay.portlet.blogs.model.BlogsEntry entry)
		throws RemoteException {
		try {
			BlogsEntryServiceUtil.deleteEntry(entry);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel getEntry(
		java.lang.String entryId) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsEntry returnValue = BlogsEntryServiceUtil.getEntry(entryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel[] getEntries(
		java.lang.String userId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = BlogsEntryServiceUtil.getEntries(userId,
					begin, end);

			return (com.liferay.portlet.blogs.model.BlogsEntry[])returnValue.toArray(new com.liferay.portlet.blogs.model.BlogsEntry[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel[] getEntries(
		java.lang.String userId, java.lang.String categoryId, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = BlogsEntryServiceUtil.getEntries(userId,
					categoryId, begin, end);

			return (com.liferay.portlet.blogs.model.BlogsEntry[])returnValue.toArray(new com.liferay.portlet.blogs.model.BlogsEntry[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel[] getEntries(
		java.lang.String userId, java.util.Calendar cal)
		throws RemoteException {
		try {
			java.util.List returnValue = BlogsEntryServiceUtil.getEntries(userId,
					cal);

			return (com.liferay.portlet.blogs.model.BlogsEntry[])returnValue.toArray(new com.liferay.portlet.blogs.model.BlogsEntry[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel[] getEntries(
		java.lang.String userId, java.lang.String categoryId,
		java.util.Calendar cal) throws RemoteException {
		try {
			java.util.List returnValue = BlogsEntryServiceUtil.getEntries(userId,
					categoryId, cal);

			return (com.liferay.portlet.blogs.model.BlogsEntry[])returnValue.toArray(new com.liferay.portlet.blogs.model.BlogsEntry[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getEntriesSize(java.lang.String userId,
		java.util.Calendar cal) throws RemoteException {
		try {
			int returnValue = BlogsEntryServiceUtil.getEntriesSize(userId, cal);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getEntriesSize(java.lang.String userId,
		java.lang.String categoryId, java.util.Calendar cal)
		throws RemoteException {
		try {
			int returnValue = BlogsEntryServiceUtil.getEntriesSize(userId,
					categoryId, cal);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getEntriesXML(java.lang.String userId,
		java.lang.String categoryId, java.lang.String type, int begin, int end,
		java.lang.String findEntryUrl) throws RemoteException {
		try {
			java.lang.String returnValue = BlogsEntryServiceUtil.getEntriesXML(userId,
					categoryId, type, begin, end, findEntryUrl);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel getLatestEntry(
		java.lang.String userId) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsEntry returnValue = BlogsEntryServiceUtil.getLatestEntry(userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel getLatestEntry(
		java.lang.String userId, java.lang.String categoryId)
		throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsEntry returnValue = BlogsEntryServiceUtil.getLatestEntry(userId,
					categoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasEntries(java.lang.String userId,
		java.util.Calendar cal) throws RemoteException {
		try {
			boolean returnValue = BlogsEntryServiceUtil.hasEntries(userId, cal);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasEntries(java.lang.String userId,
		java.lang.String categoryId, java.util.Calendar cal)
		throws RemoteException {
		try {
			boolean returnValue = BlogsEntryServiceUtil.hasEntries(userId,
					categoryId, cal);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void reIndex(java.lang.String[] ids)
		throws RemoteException {
		try {
			BlogsEntryServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String[] blogsUserIds,
		java.lang.String keywords) throws RemoteException {
		try {
			com.liferay.util.lucene.Hits returnValue = BlogsEntryServiceUtil.search(companyId,
					portletId, groupId, blogsUserIds, keywords);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel updateEntry(
		java.lang.String entryId, java.lang.String categoryId,
		java.lang.String title, java.lang.String content, int displayMonth,
		int displayDay, int displayYear, int displayHour, int displayMinute,
		boolean sharing, boolean commentable) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsEntry returnValue = BlogsEntryServiceUtil.updateEntry(entryId,
					categoryId, title, content, displayMonth, displayDay,
					displayYear, displayHour, displayMinute, sharing,
					commentable);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel updateSharing(
		java.lang.String entryId) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsEntry returnValue = BlogsEntryServiceUtil.updateSharing(entryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel updatePropsCount(
		java.lang.String entryId) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsEntry returnValue = BlogsEntryServiceUtil.updatePropsCount(entryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntryModel updateCommentsCount(
		java.lang.String entryId) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsEntry returnValue = BlogsEntryServiceUtil.updateCommentsCount(entryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}