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
 * <a href="MBCategoryLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.messageboards.service.MBCategoryLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.messageboards.service.MBCategoryLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.MBCategoryLocalService
 * @see com.liferay.portlet.messageboards.service.MBCategoryLocalServiceFactory
 *
 */
public class MBCategoryLocalServiceUtil {
	public static com.liferay.portlet.messageboards.model.MBCategory addMBCategory(
		com.liferay.portlet.messageboards.model.MBCategory model)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.addMBCategory(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.messageboards.model.MBCategory updateMBCategory(
		com.liferay.portlet.messageboards.model.MBCategory model)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.updateMBCategory(model);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBBanPersistence getMBBanPersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBBanPersistence();
	}

	public static void setMBBanPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBBanPersistence mbBanPersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBBanPersistence(mbBanPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence getMBCategoryPersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBCategoryPersistence();
	}

	public static void setMBCategoryPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence mbCategoryPersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBCategoryPersistence(mbCategoryPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder getMBCategoryFinder() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBCategoryFinder();
	}

	public static void setMBCategoryFinder(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder mbCategoryFinder) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBCategoryFinder(mbCategoryFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistence getMBDiscussionPersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBDiscussionPersistence();
	}

	public static void setMBDiscussionPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistence mbDiscussionPersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBDiscussionPersistence(mbDiscussionPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence getMBMessageFlagPersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBMessageFlagPersistence();
	}

	public static void setMBMessageFlagPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence mbMessageFlagPersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBMessageFlagPersistence(mbMessageFlagPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder getMBMessageFlagFinder() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBMessageFlagFinder();
	}

	public static void setMBMessageFlagFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder mbMessageFlagFinder) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBMessageFlagFinder(mbMessageFlagFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence getMBStatsUserPersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBStatsUserPersistence();
	}

	public static void setMBStatsUserPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence mbStatsUserPersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBStatsUserPersistence(mbStatsUserPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence getMBThreadPersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBThreadPersistence();
	}

	public static void setMBThreadPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence mbThreadPersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBThreadPersistence(mbThreadPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBThreadFinder getMBThreadFinder() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getMBThreadFinder();
	}

	public static void setMBThreadFinder(
		com.liferay.portlet.messageboards.service.persistence.MBThreadFinder mbThreadFinder) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setMBThreadFinder(mbThreadFinder);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getTagsEntryPersistence();
	}

	public static void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setTagsEntryPersistence(tagsEntryPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getTagsEntryFinder();
	}

	public static void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder) {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.setTagsEntryFinder(tagsEntryFinder);
	}

	public static void afterPropertiesSet() {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.messageboards.model.MBCategory addCategory(
		long userId, long plid, long parentCategoryId, java.lang.String name,
		java.lang.String description, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.addCategory(userId, plid,
			parentCategoryId, name, description, addCommunityPermissions,
			addGuestPermissions);
	}

	public static com.liferay.portlet.messageboards.model.MBCategory addCategory(
		java.lang.String uuid, long userId, long plid, long parentCategoryId,
		java.lang.String name, java.lang.String description,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.addCategory(uuid, userId, plid,
			parentCategoryId, name, description, addCommunityPermissions,
			addGuestPermissions);
	}

	public static com.liferay.portlet.messageboards.model.MBCategory addCategory(
		long userId, long plid, long parentCategoryId, java.lang.String name,
		java.lang.String description, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.addCategory(userId, plid,
			parentCategoryId, name, description, communityPermissions,
			guestPermissions);
	}

	public static com.liferay.portlet.messageboards.model.MBCategory addCategory(
		java.lang.String uuid, long userId, long plid, long parentCategoryId,
		java.lang.String name, java.lang.String description,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.addCategory(uuid, userId, plid,
			parentCategoryId, name, description, addCommunityPermissions,
			addGuestPermissions, communityPermissions, guestPermissions);
	}

	public static void addCategoryResources(long categoryId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.addCategoryResources(categoryId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addCategoryResources(
		com.liferay.portlet.messageboards.model.MBCategory category,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.addCategoryResources(category,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addCategoryResources(long categoryId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.addCategoryResources(categoryId,
			communityPermissions, guestPermissions);
	}

	public static void addCategoryResources(
		com.liferay.portlet.messageboards.model.MBCategory category,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.addCategoryResources(category,
			communityPermissions, guestPermissions);
	}

	public static void deleteCategories(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.deleteCategories(groupId);
	}

	public static void deleteCategory(long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.deleteCategory(categoryId);
	}

	public static void deleteCategory(
		com.liferay.portlet.messageboards.model.MBCategory category)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.deleteCategory(category);
	}

	public static java.util.List getCategories(long groupId,
		long parentCategoryId, int begin, int end)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getCategories(groupId, parentCategoryId,
			begin, end);
	}

	public static int getCategoriesCount(long groupId)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getCategoriesCount(groupId);
	}

	public static int getCategoriesCount(long groupId, long parentCategoryId)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getCategoriesCount(groupId,
			parentCategoryId);
	}

	public static com.liferay.portlet.messageboards.model.MBCategory getCategory(
		long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getCategory(categoryId);
	}

	public static void getSubcategoryIds(java.util.List categoryIds,
		long groupId, long categoryId)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.getSubcategoryIds(categoryIds, groupId,
			categoryId);
	}

	public static java.util.List getSubscribedCategories(long groupId,
		long userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getSubscribedCategories(groupId, userId,
			begin, end);
	}

	public static int getSubscribedCategoriesCount(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getSubscribedCategoriesCount(groupId,
			userId);
	}

	public static com.liferay.portlet.messageboards.model.MBCategory getSystemCategory()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.getSystemCategory();
	}

	public static void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.reIndex(ids);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, long[] categoryIds, long threadId,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.search(companyId, groupId, categoryIds,
			threadId, keywords);
	}

	public static com.liferay.portlet.messageboards.model.MBCategory updateCategory(
		long categoryId, long parentCategoryId, java.lang.String name,
		java.lang.String description, boolean mergeWithParentCategory)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		return mbCategoryLocalService.updateCategory(categoryId,
			parentCategoryId, name, description, mergeWithParentCategory);
	}

	public static void subscribeCategory(long userId, long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.subscribeCategory(userId, categoryId);
	}

	public static void unsubscribeCategory(long userId, long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBCategoryLocalService mbCategoryLocalService = MBCategoryLocalServiceFactory.getService();

		mbCategoryLocalService.unsubscribeCategory(userId, categoryId);
	}
}