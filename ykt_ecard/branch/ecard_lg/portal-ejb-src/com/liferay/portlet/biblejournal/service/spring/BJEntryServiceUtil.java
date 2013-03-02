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
 * <a href="BJEntryServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BJEntryServiceUtil {
	public static com.liferay.portlet.biblejournal.model.BJEntry addEntry(
		java.lang.String name, java.lang.String content,
		java.lang.String verses, java.lang.String[] topicIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();

			return bjEntryService.addEntry(name, content, verses, topicIds);
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

	public static void deleteEntry(java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();
			bjEntryService.deleteEntry(entryId);
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

	public static void deleteEntry(
		com.liferay.portlet.biblejournal.model.BJEntry entry)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();
			bjEntryService.deleteEntry(entry);
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

	public static java.util.List getEntriesByCompany(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();

			return bjEntryService.getEntriesByCompany(companyId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEntriesByUser(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();

			return bjEntryService.getEntriesByUser(userId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJEntry getEntry(
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();

			return bjEntryService.getEntry(entryId);
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

	public static java.util.List getTopics(java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();

			return bjEntryService.getTopics(entryId);
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

	public static java.lang.String[] getTopicIds(java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();

			return bjEntryService.getTopicIds(entryId);
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

	public static java.util.List getVerses(java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();

			return bjEntryService.getVerses(entryId);
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

	public static com.liferay.portlet.biblejournal.model.BJEntry updateEntry(
		java.lang.String entryId, java.lang.String name,
		java.lang.String content, java.lang.String verses,
		java.lang.String[] topicIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BJEntryService bjEntryService = BJEntryServiceFactory.getService();

			return bjEntryService.updateEntry(entryId, name, content, verses,
				topicIds);
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
}