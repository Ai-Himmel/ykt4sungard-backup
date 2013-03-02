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

package com.liferay.portlet.blogs.service.spring;

/**
 * <a href="BlogsEntryServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsEntryServiceUtil {
	public static final String PORTLET_ID = "33";

	public static com.liferay.portlet.blogs.model.BlogsEntry addEntry(
		java.lang.String categoryId, java.lang.String title,
		java.lang.String content, int displayMonth, int displayDay,
		int displayYear, int displayHour, int displayMinute, boolean sharing,
		boolean commentable)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.addEntry(categoryId, title, content,
				displayMonth, displayDay, displayYear, displayHour,
				displayMinute, sharing, commentable);
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
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();
			blogsEntryService.deleteEntry(entryId);
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
		com.liferay.portlet.blogs.model.BlogsEntry entry)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();
			blogsEntryService.deleteEntry(entry);
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

	public static com.liferay.portlet.blogs.model.BlogsEntry getEntry(
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getEntry(entryId);
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

	public static java.util.List getEntries(java.lang.String userId, int begin,
		int end) throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getEntries(userId, begin, end);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEntries(java.lang.String userId,
		java.lang.String categoryId, int begin, int end)
		throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getEntries(userId, categoryId, begin, end);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEntries(java.lang.String userId,
		java.util.Calendar cal) throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getEntries(userId, cal);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getEntries(java.lang.String userId,
		java.lang.String categoryId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getEntries(userId, categoryId, cal);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getEntriesSize(java.lang.String userId,
		java.util.Calendar cal) throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getEntriesSize(userId, cal);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getEntriesSize(java.lang.String userId,
		java.lang.String categoryId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getEntriesSize(userId, categoryId, cal);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.lang.String getEntriesXML(java.lang.String userId,
		java.lang.String categoryId, java.lang.String type, int begin, int end,
		java.lang.String findEntryUrl)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getEntriesXML(userId, categoryId, type,
				begin, end, findEntryUrl);
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

	public static com.liferay.portlet.blogs.model.BlogsEntry getLatestEntry(
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getLatestEntry(userId);
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

	public static com.liferay.portlet.blogs.model.BlogsEntry getLatestEntry(
		java.lang.String userId, java.lang.String categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.getLatestEntry(userId, categoryId);
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

	public static boolean hasEntries(java.lang.String userId,
		java.util.Calendar cal) throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.hasEntries(userId, cal);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasEntries(java.lang.String userId,
		java.lang.String categoryId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.hasEntries(userId, categoryId, cal);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();
			blogsEntryService.reIndex(ids);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String[] blogsUserIds,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.search(companyId, portletId, groupId,
				blogsUserIds, keywords);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry updateEntry(
		java.lang.String entryId, java.lang.String categoryId,
		java.lang.String title, java.lang.String content, int displayMonth,
		int displayDay, int displayYear, int displayHour, int displayMinute,
		boolean sharing, boolean commentable)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.updateEntry(entryId, categoryId, title,
				content, displayMonth, displayDay, displayYear, displayHour,
				displayMinute, sharing, commentable);
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

	public static com.liferay.portlet.blogs.model.BlogsEntry updateSharing(
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.updateSharing(entryId);
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

	public static com.liferay.portlet.blogs.model.BlogsEntry updatePropsCount(
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.updatePropsCount(entryId);
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

	public static com.liferay.portlet.blogs.model.BlogsEntry updateCommentsCount(
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			BlogsEntryService blogsEntryService = BlogsEntryServiceFactory.getService();

			return blogsEntryService.updateCommentsCount(entryId);
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