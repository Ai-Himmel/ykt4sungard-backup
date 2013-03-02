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

package com.liferay.portlet.biblejournal.service.spring;

/**
 * <a href="BJVerseServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BJVerseServiceUtil {
	public static java.util.List getEntries(int book, int chapter, int verse)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJVerseService bjVerseService = BJVerseServiceFactory.getService();

			return bjVerseService.getEntries(book, chapter, verse);
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

	public static java.util.List getTopics(int book, int chapter, int verse)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJVerseService bjVerseService = BJVerseServiceFactory.getService();

			return bjVerseService.getTopics(book, chapter, verse);
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

	public static boolean hasEntries(int book, int chapter, int verse)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJVerseService bjVerseService = BJVerseServiceFactory.getService();

			return bjVerseService.hasEntries(book, chapter, verse);
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

	public static java.lang.String[] parseVerseIds(java.lang.String verses)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJVerseService bjVerseService = BJVerseServiceFactory.getService();

			return bjVerseService.parseVerseIds(verses);
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

	public static com.liferay.portlet.biblejournal.model.BJVerse[] parseVerses(
		java.lang.String verses)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJVerseService bjVerseService = BJVerseServiceFactory.getService();

			return bjVerseService.parseVerses(verses);
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

	public static com.liferay.portlet.biblejournal.model.BJVerse _getBJVerse(
		java.lang.String companyId, java.lang.String userId,
		java.lang.String name) throws com.liferay.portal.SystemException {
		try {
			BJVerseService bjVerseService = BJVerseServiceFactory.getService();

			return bjVerseService._getBJVerse(companyId, userId, name);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.lang.String _getBJVerseId(java.lang.String companyId,
		java.lang.String userId, java.lang.String name)
		throws com.liferay.portal.SystemException {
		try {
			BJVerseService bjVerseService = BJVerseServiceFactory.getService();

			return bjVerseService._getBJVerseId(companyId, userId, name);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}