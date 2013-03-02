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
 * <a href="MBBanLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.messageboards.service.MBBanLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.messageboards.service.MBBanLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.MBBanLocalService
 * @see com.liferay.portlet.messageboards.service.MBBanLocalServiceFactory
 *
 */
public class MBBanLocalServiceUtil {
	public static com.liferay.portlet.messageboards.model.MBBan addMBBan(
		com.liferay.portlet.messageboards.model.MBBan model)
		throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.addMBBan(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.messageboards.model.MBBan updateMBBan(
		com.liferay.portlet.messageboards.model.MBBan model)
		throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.updateMBBan(model);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBBanPersistence getMBBanPersistence() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBBanPersistence();
	}

	public static void setMBBanPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBBanPersistence mbBanPersistence) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBBanPersistence(mbBanPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence getMBCategoryPersistence() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBCategoryPersistence();
	}

	public static void setMBCategoryPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence mbCategoryPersistence) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBCategoryPersistence(mbCategoryPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder getMBCategoryFinder() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBCategoryFinder();
	}

	public static void setMBCategoryFinder(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder mbCategoryFinder) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBCategoryFinder(mbCategoryFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistence getMBDiscussionPersistence() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBDiscussionPersistence();
	}

	public static void setMBDiscussionPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistence mbDiscussionPersistence) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBDiscussionPersistence(mbDiscussionPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence getMBMessageFlagPersistence() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBMessageFlagPersistence();
	}

	public static void setMBMessageFlagPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence mbMessageFlagPersistence) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBMessageFlagPersistence(mbMessageFlagPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder getMBMessageFlagFinder() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBMessageFlagFinder();
	}

	public static void setMBMessageFlagFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder mbMessageFlagFinder) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBMessageFlagFinder(mbMessageFlagFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence getMBStatsUserPersistence() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBStatsUserPersistence();
	}

	public static void setMBStatsUserPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence mbStatsUserPersistence) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBStatsUserPersistence(mbStatsUserPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence getMBThreadPersistence() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBThreadPersistence();
	}

	public static void setMBThreadPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence mbThreadPersistence) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBThreadPersistence(mbThreadPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBThreadFinder getMBThreadFinder() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getMBThreadFinder();
	}

	public static void setMBThreadFinder(
		com.liferay.portlet.messageboards.service.persistence.MBThreadFinder mbThreadFinder) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setMBThreadFinder(mbThreadFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.messageboards.model.MBBan addBan(
		long userId, long plid, long banUserId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.addBan(userId, plid, banUserId);
	}

	public static void checkBan(long groupId, long banUserId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.checkBan(groupId, banUserId);
	}

	public static void deleteBan(long plid, long banUserId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.deleteBan(plid, banUserId);
	}

	public static void deleteBansByBanUserId(long banUserId)
		throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.deleteBansByBanUserId(banUserId);
	}

	public static void deleteBansByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.deleteBansByGroupId(groupId);
	}

	public static void expireBans() throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		mbBanLocalService.expireBans();
	}

	public static java.util.List getBans(long groupId, int start, int end)
		throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getBans(groupId, start, end);
	}

	public static int getBansCount(long groupId)
		throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.getBansCount(groupId);
	}

	public static boolean hasBan(long groupId, long banUserId)
		throws com.liferay.portal.SystemException {
		MBBanLocalService mbBanLocalService = MBBanLocalServiceFactory.getService();

		return mbBanLocalService.hasBan(groupId, banUserId);
	}
}