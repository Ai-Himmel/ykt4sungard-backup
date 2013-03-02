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

package com.liferay.portlet.messageboards.service;


/**
 * <a href="MBMessageFlagLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.messageboards.service.MBMessageFlagLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.messageboards.service.MBMessageFlagLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.MBMessageFlagLocalService
 * @see com.liferay.portlet.messageboards.service.MBMessageFlagLocalServiceFactory
 *
 */
public class MBMessageFlagLocalServiceUtil {
	public static com.liferay.portlet.messageboards.model.MBMessageFlag addMBMessageFlag(
		com.liferay.portlet.messageboards.model.MBMessageFlag model)
		throws com.liferay.portal.SystemException {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.addMBMessageFlag(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageFlag updateMBMessageFlag(
		com.liferay.portlet.messageboards.model.MBMessageFlag model)
		throws com.liferay.portal.SystemException {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.updateMBMessageFlag(model);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBBanPersistence getMBBanPersistence() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBBanPersistence();
	}

	public static void setMBBanPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBBanPersistence mbBanPersistence) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBBanPersistence(mbBanPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence getMBCategoryPersistence() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBCategoryPersistence();
	}

	public static void setMBCategoryPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence mbCategoryPersistence) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBCategoryPersistence(mbCategoryPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder getMBCategoryFinder() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBCategoryFinder();
	}

	public static void setMBCategoryFinder(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder mbCategoryFinder) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBCategoryFinder(mbCategoryFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistence getMBDiscussionPersistence() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBDiscussionPersistence();
	}

	public static void setMBDiscussionPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistence mbDiscussionPersistence) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBDiscussionPersistence(mbDiscussionPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence getMBMessageFlagPersistence() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBMessageFlagPersistence();
	}

	public static void setMBMessageFlagPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence mbMessageFlagPersistence) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBMessageFlagPersistence(mbMessageFlagPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder getMBMessageFlagFinder() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBMessageFlagFinder();
	}

	public static void setMBMessageFlagFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder mbMessageFlagFinder) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBMessageFlagFinder(mbMessageFlagFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence getMBStatsUserPersistence() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBStatsUserPersistence();
	}

	public static void setMBStatsUserPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence mbStatsUserPersistence) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBStatsUserPersistence(mbStatsUserPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence getMBThreadPersistence() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBThreadPersistence();
	}

	public static void setMBThreadPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence mbThreadPersistence) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBThreadPersistence(mbThreadPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBThreadFinder getMBThreadFinder() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getMBThreadFinder();
	}

	public static void setMBThreadFinder(
		com.liferay.portlet.messageboards.service.persistence.MBThreadFinder mbThreadFinder) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setMBThreadFinder(mbThreadFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.afterPropertiesSet();
	}

	public static void addReadFlags(long userId, java.util.List messages)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.addReadFlags(userId, messages);
	}

	public static void deleteFlags(long userId)
		throws com.liferay.portal.SystemException {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		mbMessageFlagLocalService.deleteFlags(userId);
	}

	public static boolean hasReadFlag(long userId, long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageFlagLocalService mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getService();

		return mbMessageFlagLocalService.hasReadFlag(userId, messageId);
	}
}