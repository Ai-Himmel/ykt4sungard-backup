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
 * <a href="BlogsStatsUserLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.blogs.service.BlogsStatsUserLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.blogs.service.BlogsStatsUserLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.blogs.service.BlogsStatsUserLocalService
 * @see com.liferay.portlet.blogs.service.BlogsStatsUserLocalServiceFactory
 *
 */
public class BlogsStatsUserLocalServiceUtil {
	public static com.liferay.portlet.blogs.model.BlogsStatsUser addBlogsStatsUser(
		com.liferay.portlet.blogs.model.BlogsStatsUser model)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.addBlogsStatsUser(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser updateBlogsStatsUser(
		com.liferay.portlet.blogs.model.BlogsStatsUser model)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.updateBlogsStatsUser(model);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence getBlogsEntryPersistence() {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getBlogsEntryPersistence();
	}

	public static void setBlogsEntryPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence blogsEntryPersistence) {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.setBlogsEntryPersistence(blogsEntryPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder getBlogsEntryFinder() {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getBlogsEntryFinder();
	}

	public static void setBlogsEntryFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder blogsEntryFinder) {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.setBlogsEntryFinder(blogsEntryFinder);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence getBlogsStatsUserPersistence() {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getBlogsStatsUserPersistence();
	}

	public static void setBlogsStatsUserPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence blogsStatsUserPersistence) {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.setBlogsStatsUserPersistence(blogsStatsUserPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder getBlogsStatsUserFinder() {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getBlogsStatsUserFinder();
	}

	public static void setBlogsStatsUserFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder blogsStatsUserFinder) {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.setBlogsStatsUserFinder(blogsStatsUserFinder);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.setGroupFinder(groupFinder);
	}

	public static void afterPropertiesSet() {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.afterPropertiesSet();
	}

	public static void deleteStatsUserByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.deleteStatsUserByGroupId(groupId);
	}

	public static void deleteStatsUserByUserId(long userId)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.deleteStatsUserByUserId(userId);
	}

	public static java.util.List getCompanyStatsUsers(long companyId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getCompanyStatsUsers(companyId,
			begin, end, obc);
	}

	public static int getCompanyStatsUsersCount(long companyId)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getCompanyStatsUsersCount(companyId);
	}

	public static java.util.List getGroupStatsUsers(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getGroupStatsUsers(groupId, begin,
			end, obc);
	}

	public static int getGroupStatsUsersCount(long groupId)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getGroupStatsUsersCount(groupId);
	}

	public static java.util.List getOrganizationStatsUsers(
		long organizationId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getOrganizationStatsUsers(organizationId,
			begin, end, obc);
	}

	public static int getOrganizationStatsUsersCount(long organizationId)
		throws com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getOrganizationStatsUsersCount(organizationId);
	}

	public static com.liferay.portlet.blogs.model.BlogsStatsUser getStatsUser(
		long groupId, long userId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		return blogsStatsUserLocalService.getStatsUser(groupId, userId);
	}

	public static void updateStatsUser(long groupId, long userId,
		java.util.Date lastPostDate)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BlogsStatsUserLocalService blogsStatsUserLocalService = BlogsStatsUserLocalServiceFactory.getService();

		blogsStatsUserLocalService.updateStatsUser(groupId, userId, lastPostDate);
	}
}