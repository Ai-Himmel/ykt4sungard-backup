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
 * <a href="BlogsEntryService.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public interface BlogsEntryService {
	public com.liferay.portlet.blogs.model.BlogsEntry addEntry(
		java.lang.String categoryId, java.lang.String title,
		java.lang.String content, int displayMonth, int displayDay,
		int displayYear, int displayHour, int displayMinute, boolean sharing,
		boolean commentable)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public void deleteEntry(java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public void deleteEntry(com.liferay.portlet.blogs.model.BlogsEntry entry)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.blogs.model.BlogsEntry getEntry(
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getEntries(java.lang.String userId, int begin, int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getEntries(java.lang.String userId,
		java.lang.String categoryId, int begin, int end)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getEntries(java.lang.String userId,
		java.util.Calendar cal)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.util.List getEntries(java.lang.String userId,
		java.lang.String categoryId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public int getEntriesSize(java.lang.String userId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public int getEntriesSize(java.lang.String userId,
		java.lang.String categoryId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public java.lang.String getEntriesXML(java.lang.String userId,
		java.lang.String categoryId, java.lang.String type, int begin, int end,
		java.lang.String findEntryUrl)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.blogs.model.BlogsEntry getLatestEntry(
		java.lang.String userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.blogs.model.BlogsEntry getLatestEntry(
		java.lang.String userId, java.lang.String categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public boolean hasEntries(java.lang.String userId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public boolean hasEntries(java.lang.String userId,
		java.lang.String categoryId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.util.lucene.Hits search(java.lang.String companyId,
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String[] blogsUserIds, java.lang.String keywords)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.blogs.model.BlogsEntry updateEntry(
		java.lang.String entryId, java.lang.String categoryId,
		java.lang.String title, java.lang.String content, int displayMonth,
		int displayDay, int displayYear, int displayHour, int displayMinute,
		boolean sharing, boolean commentable)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.blogs.model.BlogsEntry updateSharing(
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.blogs.model.BlogsEntry updatePropsCount(
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;

	public com.liferay.portlet.blogs.model.BlogsEntry updateCommentsCount(
		java.lang.String entryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException;
}