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

import com.liferay.portlet.biblejournal.service.spring.BJVerseServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="BJVerseServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BJVerseServiceSoap {
	public static com.liferay.portlet.biblejournal.model.BJVerseModel[] getEntries(
		int book, int chapter, int verse) throws RemoteException {
		try {
			java.util.List returnValue = BJVerseServiceUtil.getEntries(book,
					chapter, verse);

			return (com.liferay.portlet.biblejournal.model.BJVerse[])returnValue.toArray(new com.liferay.portlet.biblejournal.model.BJVerse[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJVerseModel[] getTopics(
		int book, int chapter, int verse) throws RemoteException {
		try {
			java.util.List returnValue = BJVerseServiceUtil.getTopics(book,
					chapter, verse);

			return (com.liferay.portlet.biblejournal.model.BJVerse[])returnValue.toArray(new com.liferay.portlet.biblejournal.model.BJVerse[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasEntries(int book, int chapter, int verse)
		throws RemoteException {
		try {
			boolean returnValue = BJVerseServiceUtil.hasEntries(book, chapter,
					verse);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String[] parseVerseIds(java.lang.String verses)
		throws RemoteException {
		try {
			java.lang.String[] returnValue = BJVerseServiceUtil.parseVerseIds(verses);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJVerseModel[] parseVerses(
		java.lang.String verses) throws RemoteException {
		try {
			com.liferay.portlet.biblejournal.model.BJVerse[] returnValue = BJVerseServiceUtil.parseVerses(verses);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJVerseModel _getBJVerse(
		java.lang.String companyId, java.lang.String userId,
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portlet.biblejournal.model.BJVerse returnValue = BJVerseServiceUtil._getBJVerse(companyId,
					userId, name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String _getBJVerseId(java.lang.String companyId,
		java.lang.String userId, java.lang.String name)
		throws RemoteException {
		try {
			java.lang.String returnValue = BJVerseServiceUtil._getBJVerseId(companyId,
					userId, name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}