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

package com.liferay.portlet.blogs.service;


/**
 * <a href="BlogsStatsUserLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.blogs.service.impl.BlogsStatsUserLocalServiceImpl</code>.
 * Modify methods in that class and rerun ServiceBuilder to populate this class
 * and all other generated classes.
 * </p>
 *
 * <p>
 * This is a local service. Methods of this service will not have security checks based on the propagated JAAS credentials because this service can only be accessed from within the same VM.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.blogs.service.BlogsStatsUserLocalServiceFactory
 * @see com.liferay.portlet.blogs.service.BlogsStatsUserLocalServiceUtil
 *
 */
public interface BlogsStatsUserLocalService {
	public com.liferay.portlet.blogs.model.BlogsStatsUser addBlogsStatsUser(
		com.liferay.portlet.blogs.model.BlogsStatsUser model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.blogs.model.BlogsStatsUser updateBlogsStatsUser(
		com.liferay.portlet.blogs.model.BlogsStatsUser model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence getBlogsEntryPersistence();

	public void setBlogsEntryPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence blogsEntryPersistence);

	public com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder getBlogsEntryFinder();

	public void setBlogsEntryFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder blogsEntryFinder);

	public com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence getBlogsStatsUserPersistence();

	public void setBlogsStatsUserPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence blogsStatsUserPersistence);

	public com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder getBlogsStatsUserFinder();

	public void setBlogsStatsUserFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder blogsStatsUserFinder);

	public com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence();

	public void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence);

	public com.liferay.portal.service.persistence.GroupFinder getGroupFinder();

	public void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder);

	public void afterPropertiesSet();

	public void deleteStatsUserByGroupId(long groupId)
		throws com.liferay.portal.SystemException;

	public void deleteStatsUserByUserId(long userId)
		throws com.liferay.portal.SystemException;

	public java.util.List getCompanyStatsUsers(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int getCompanyStatsUsersCount(long companyId)
		throws com.liferay.portal.SystemException;

	public java.util.List getGroupStatsUsers(long groupId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int getGroupStatsUsersCount(long groupId)
		throws com.liferay.portal.SystemException;

	public java.util.List getOrganizationStatsUsers(long organizationId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int getOrganizationStatsUsersCount(long organizationId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.blogs.model.BlogsStatsUser getStatsUser(
		long groupId, long userId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void updateStatsUser(long groupId, long userId,
		java.util.Date lastPostDate)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}