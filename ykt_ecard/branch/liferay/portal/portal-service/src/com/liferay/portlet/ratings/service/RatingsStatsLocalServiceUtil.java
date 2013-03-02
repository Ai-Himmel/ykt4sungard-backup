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
 * <a href="RatingsStatsLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.ratings.service.RatingsStatsLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.ratings.service.RatingsStatsLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.ratings.service.RatingsStatsLocalService
 * @see com.liferay.portlet.ratings.service.RatingsStatsLocalServiceFactory
 *
 */
public class RatingsStatsLocalServiceUtil {
	public static com.liferay.portlet.ratings.model.RatingsStats addRatingsStats(
		com.liferay.portlet.ratings.model.RatingsStats model)
		throws com.liferay.portal.SystemException {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		return ratingsStatsLocalService.addRatingsStats(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		return ratingsStatsLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		return ratingsStatsLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.ratings.model.RatingsStats updateRatingsStats(
		com.liferay.portlet.ratings.model.RatingsStats model)
		throws com.liferay.portal.SystemException {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		return ratingsStatsLocalService.updateRatingsStats(model);
	}

	public static com.liferay.portlet.ratings.service.persistence.RatingsEntryPersistence getRatingsEntryPersistence() {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		return ratingsStatsLocalService.getRatingsEntryPersistence();
	}

	public static void setRatingsEntryPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsEntryPersistence ratingsEntryPersistence) {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		ratingsStatsLocalService.setRatingsEntryPersistence(ratingsEntryPersistence);
	}

	public static com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence getRatingsStatsPersistence() {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		return ratingsStatsLocalService.getRatingsStatsPersistence();
	}

	public static void setRatingsStatsPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence ratingsStatsPersistence) {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		ratingsStatsLocalService.setRatingsStatsPersistence(ratingsStatsPersistence);
	}

	public static void afterPropertiesSet() {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		ratingsStatsLocalService.afterPropertiesSet();
	}

	public static void deleteStats(java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		ratingsStatsLocalService.deleteStats(className, classPK);
	}

	public static com.liferay.portlet.ratings.model.RatingsStats getStats(
		long statsId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		return ratingsStatsLocalService.getStats(statsId);
	}

	public static com.liferay.portlet.ratings.model.RatingsStats getStats(
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		RatingsStatsLocalService ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getService();

		return ratingsStatsLocalService.getStats(className, classPK);
	}
}