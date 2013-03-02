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

package com.liferay.portlet.biblejournal.service.http;

import com.liferay.portlet.biblejournal.service.spring.BJEntryServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="BJEntryServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BJEntryServiceSoap {
	public static com.liferay.portlet.biblejournal.model.BJEntryModel addEntry(
		java.lang.String name, java.lang.String content,
		java.lang.String verses, java.lang.String[] topicIds)
		throws RemoteException {
		try {
			com.liferay.portlet.biblejournal.model.BJEntry returnValue = BJEntryServiceUtil.addEntry(name,
					content, verses, topicIds);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteEntry(java.lang.String entryId)
		throws RemoteException {
		try {
			BJEntryServiceUtil.deleteEntry(entryId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteEntry(
		com.liferay.portlet.biblejournal.model.BJEntry entry)
		throws RemoteException {
		try {
			BJEntryServiceUtil.deleteEntry(entry);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJEntryModel[] getEntriesByCompany(
		java.lang.String companyId) throws RemoteException {
		try {
			java.util.List returnValue = BJEntryServiceUtil.getEntriesByCompany(companyId);

			return (com.liferay.portlet.biblejournal.model.BJEntry[])returnValue.toArray(new com.liferay.portlet.biblejournal.model.BJEntry[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJEntryModel[] getEntriesByUser(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = BJEntryServiceUtil.getEntriesByUser(userId);

			return (com.liferay.portlet.biblejournal.model.BJEntry[])returnValue.toArray(new com.liferay.portlet.biblejournal.model.BJEntry[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJEntryModel getEntry(
		java.lang.String entryId) throws RemoteException {
		try {
			com.liferay.portlet.biblejournal.model.BJEntry returnValue = BJEntryServiceUtil.getEntry(entryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJEntryModel[] getTopics(
		java.lang.String entryId) throws RemoteException {
		try {
			java.util.List returnValue = BJEntryServiceUtil.getTopics(entryId);

			return (com.liferay.portlet.biblejournal.model.BJEntry[])returnValue.toArray(new com.liferay.portlet.biblejournal.model.BJEntry[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String[] getTopicIds(java.lang.String entryId)
		throws RemoteException {
		try {
			java.lang.String[] returnValue = BJEntryServiceUtil.getTopicIds(entryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJEntryModel[] getVerses(
		java.lang.String entryId) throws RemoteException {
		try {
			java.util.List returnValue = BJEntryServiceUtil.getVerses(entryId);

			return (com.liferay.portlet.biblejournal.model.BJEntry[])returnValue.toArray(new com.liferay.portlet.biblejournal.model.BJEntry[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJEntryModel updateEntry(
		java.lang.String entryId, java.lang.String name,
		java.lang.String content, java.lang.String verses,
		java.lang.String[] topicIds) throws RemoteException {
		try {
			com.liferay.portlet.biblejournal.model.BJEntry returnValue = BJEntryServiceUtil.updateEntry(entryId,
					name, content, verses, topicIds);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}