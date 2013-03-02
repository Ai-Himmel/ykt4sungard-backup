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

package com.liferay.portlet.ratings.service;


/**
 * <a href="RatingsEntryLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.ratings.service.RatingsEntryLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.ratings.service.RatingsEntryLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.ratings.service.RatingsEntryLocalService
 * @see com.liferay.portlet.ratings.service.RatingsEntryLocalServiceFactory
 *
 */
public class RatingsEntryLocalServiceUtil {
	public static com.liferay.portlet.ratings.model.RatingsEntry addRatingsEntry(
		com.liferay.portlet.ratings.model.RatingsEntry model)
		throws com.liferay.portal.SystemException {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.addRatingsEntry(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry updateRatingsEntry(
		com.liferay.portlet.ratings.model.RatingsEntry model)
		throws com.liferay.portal.SystemException {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.updateRatingsEntry(model);
	}

	public static com.liferay.portlet.ratings.service.persistence.RatingsEntryPersistence getRatingsEntryPersistence() {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getRatingsEntryPersistence();
	}

	public static void setRatingsEntryPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsEntryPersistence ratingsEntryPersistence) {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		ratingsEntryLocalService.setRatingsEntryPersistence(ratingsEntryPersistence);
	}

	public static com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence getRatingsStatsPersistence() {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getRatingsStatsPersistence();
	}

	public static void setRatingsStatsPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence ratingsStatsPersistence) {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		ratingsEntryLocalService.setRatingsStatsPersistence(ratingsStatsPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		ratingsEntryLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		ratingsEntryLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence getBlogsEntryPersistence() {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getBlogsEntryPersistence();
	}

	public static void setBlogsEntryPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence blogsEntryPersistence) {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		ratingsEntryLocalService.setBlogsEntryPersistence(blogsEntryPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder getBlogsEntryFinder() {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getBlogsEntryFinder();
	}

	public static void setBlogsEntryFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder blogsEntryFinder) {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		ratingsEntryLocalService.setBlogsEntryFinder(blogsEntryFinder);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence getBlogsStatsUserPersistence() {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getBlogsStatsUserPersistence();
	}

	public static void setBlogsStatsUserPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence blogsStatsUserPersistence) {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		ratingsEntryLocalService.setBlogsStatsUserPersistence(blogsStatsUserPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder getBlogsStatsUserFinder() {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getBlogsStatsUserFinder();
	}

	public static void setBlogsStatsUserFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder blogsStatsUserFinder) {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		ratingsEntryLocalService.setBlogsStatsUserFinder(blogsStatsUserFinder);
	}

	public static void afterPropertiesSet() {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		ratingsEntryLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry getEntry(
		long userId, java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getEntry(userId, className, classPK);
	}

	public static java.util.List getEntries(java.lang.String className,
		long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.getEntries(className, classPK);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry updateEntry(
		long userId, java.lang.String className, long classPK, double score)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RatingsEntryLocalService ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getService();

		return ratingsEntryLocalService.updateEntry(userId, className, classPK,
			score);
	}
}