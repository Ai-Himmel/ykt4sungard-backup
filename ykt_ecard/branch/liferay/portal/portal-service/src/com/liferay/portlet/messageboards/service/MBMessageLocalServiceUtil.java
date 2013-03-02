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
 * <a href="MBMessageLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.messageboards.service.MBMessageLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.messageboards.service.MBMessageLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.MBMessageLocalService
 * @see com.liferay.portlet.messageboards.service.MBMessageLocalServiceFactory
 *
 */
public class MBMessageLocalServiceUtil {
	public static com.liferay.portlet.messageboards.model.MBMessage addMBMessage(
		com.liferay.portlet.messageboards.model.MBMessage model)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addMBMessage(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage updateMBMessage(
		com.liferay.portlet.messageboards.model.MBMessage model)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.updateMBMessage(model);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBBanPersistence getMBBanPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBBanPersistence();
	}

	public static void setMBBanPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBBanPersistence mbBanPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBBanPersistence(mbBanPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence getMBCategoryPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBCategoryPersistence();
	}

	public static void setMBCategoryPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence mbCategoryPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBCategoryPersistence(mbCategoryPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder getMBCategoryFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBCategoryFinder();
	}

	public static void setMBCategoryFinder(
		com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder mbCategoryFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBCategoryFinder(mbCategoryFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistence getMBDiscussionPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBDiscussionPersistence();
	}

	public static void setMBDiscussionPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistence mbDiscussionPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBDiscussionPersistence(mbDiscussionPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence getMBMessageFlagPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBMessageFlagPersistence();
	}

	public static void setMBMessageFlagPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence mbMessageFlagPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBMessageFlagPersistence(mbMessageFlagPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder getMBMessageFlagFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBMessageFlagFinder();
	}

	public static void setMBMessageFlagFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder mbMessageFlagFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBMessageFlagFinder(mbMessageFlagFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence getMBStatsUserPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBStatsUserPersistence();
	}

	public static void setMBStatsUserPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence mbStatsUserPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBStatsUserPersistence(mbStatsUserPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence getMBThreadPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBThreadPersistence();
	}

	public static void setMBThreadPersistence(
		com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence mbThreadPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBThreadPersistence(mbThreadPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBThreadFinder getMBThreadFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMBThreadFinder();
	}

	public static void setMBThreadFinder(
		com.liferay.portlet.messageboards.service.persistence.MBThreadFinder mbThreadFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setMBThreadFinder(mbThreadFinder);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerPersistence getActivityTrackerPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getActivityTrackerPersistence();
	}

	public static void setActivityTrackerPersistence(
		com.liferay.portal.service.persistence.ActivityTrackerPersistence activityTrackerPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setActivityTrackerPersistence(activityTrackerPersistence);
	}

	public static com.liferay.portal.service.persistence.ActivityTrackerFinder getActivityTrackerFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getActivityTrackerFinder();
	}

	public static void setActivityTrackerFinder(
		com.liferay.portal.service.persistence.ActivityTrackerFinder activityTrackerFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setActivityTrackerFinder(activityTrackerFinder);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.SubscriptionPersistence getSubscriptionPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getSubscriptionPersistence();
	}

	public static void setSubscriptionPersistence(
		com.liferay.portal.service.persistence.SubscriptionPersistence subscriptionPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setSubscriptionPersistence(subscriptionPersistence);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence getBlogsEntryPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getBlogsEntryPersistence();
	}

	public static void setBlogsEntryPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence blogsEntryPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setBlogsEntryPersistence(blogsEntryPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder getBlogsEntryFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getBlogsEntryFinder();
	}

	public static void setBlogsEntryFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder blogsEntryFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setBlogsEntryFinder(blogsEntryFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getTagsAssetPersistence();
	}

	public static void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setTagsAssetPersistence(tagsAssetPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getTagsAssetFinder();
	}

	public static void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setTagsAssetFinder(tagsAssetFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getTagsEntryPersistence();
	}

	public static void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setTagsEntryPersistence(tagsEntryPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getTagsEntryFinder();
	}

	public static void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder) {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.setTagsEntryFinder(tagsEntryFinder);
	}

	public static void afterPropertiesSet() {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addDiscussionMessage(
		long userId, java.lang.String subject, java.lang.String body)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addDiscussionMessage(userId, subject, body);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addDiscussionMessage(
		long userId, long groupId, java.lang.String className, long classPK,
		long threadId, long parentMessageId, java.lang.String subject,
		java.lang.String body)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addDiscussionMessage(userId, groupId,
			className, classPK, threadId, parentMessageId, subject, body);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addDiscussionMessage(
		long userId, long groupId, java.lang.String className, long classPK,
		long threadId, long parentMessageId, java.lang.String subject,
		java.lang.String body,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addDiscussionMessage(userId, groupId,
			className, classPK, threadId, parentMessageId, subject, body,
			themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long userId, long categoryId, java.lang.String subject,
		java.lang.String body, java.util.List files, boolean anonymous,
		double priority, java.lang.String[] tagsEntries,
		javax.portlet.PortletPreferences prefs,
		boolean addCommunityPermissions, boolean addGuestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addMessage(userId, categoryId, subject,
			body, files, anonymous, priority, tagsEntries, prefs,
			addCommunityPermissions, addGuestPermissions, themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long userId, long categoryId, java.lang.String subject,
		java.lang.String body, java.util.List files, boolean anonymous,
		double priority, java.lang.String[] tagsEntries,
		javax.portlet.PortletPreferences prefs,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addMessage(userId, categoryId, subject,
			body, files, anonymous, priority, tagsEntries, prefs,
			communityPermissions, guestPermissions, themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long userId, long categoryId, java.lang.String subject,
		java.lang.String body, java.util.List files, boolean anonymous,
		double priority, java.lang.String[] tagsEntries,
		javax.portlet.PortletPreferences prefs,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addMessage(userId, categoryId, subject,
			body, files, anonymous, priority, tagsEntries, prefs,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions, themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long userId, long categoryId, long threadId, long parentMessageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		javax.portlet.PortletPreferences prefs,
		boolean addCommunityPermissions, boolean addGuestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addMessage(userId, categoryId, threadId,
			parentMessageId, subject, body, files, anonymous, priority,
			tagsEntries, prefs, addCommunityPermissions, addGuestPermissions,
			themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long userId, long categoryId, long threadId, long parentMessageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		javax.portlet.PortletPreferences prefs,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addMessage(userId, categoryId, threadId,
			parentMessageId, subject, body, files, anonymous, priority,
			tagsEntries, prefs, communityPermissions, guestPermissions,
			themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		java.lang.String uuid, long userId, long categoryId, long threadId,
		long parentMessageId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries, javax.portlet.PortletPreferences prefs,
		boolean addCommunityPermissions, boolean addGuestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addMessage(uuid, userId, categoryId,
			threadId, parentMessageId, subject, body, files, anonymous,
			priority, tagsEntries, prefs, addCommunityPermissions,
			addGuestPermissions, themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		java.lang.String uuid, long userId, long categoryId, long threadId,
		long parentMessageId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries, javax.portlet.PortletPreferences prefs,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.addMessage(uuid, userId, categoryId,
			threadId, parentMessageId, subject, body, files, anonymous,
			priority, tagsEntries, prefs, addCommunityPermissions,
			addGuestPermissions, communityPermissions, guestPermissions,
			themeDisplay);
	}

	public static void addMessageResources(long categoryId, long messageId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.addMessageResources(categoryId, messageId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addMessageResources(long categoryId,
		java.lang.String topicId, long messageId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.addMessageResources(categoryId, topicId,
			messageId, addCommunityPermissions, addGuestPermissions);
	}

	public static void addMessageResources(
		com.liferay.portlet.messageboards.model.MBCategory category,
		com.liferay.portlet.messageboards.model.MBMessage message,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.addMessageResources(category, message,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addMessageResources(long categoryId, long messageId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.addMessageResources(categoryId, messageId,
			communityPermissions, guestPermissions);
	}

	public static void addMessageResources(long categoryId,
		java.lang.String topicId, long messageId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.addMessageResources(categoryId, topicId,
			messageId, communityPermissions, guestPermissions);
	}

	public static void addMessageResources(
		com.liferay.portlet.messageboards.model.MBCategory category,
		com.liferay.portlet.messageboards.model.MBMessage message,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.addMessageResources(category, message,
			communityPermissions, guestPermissions);
	}

	public static void deleteDiscussionMessage(long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.deleteDiscussionMessage(messageId);
	}

	public static void deleteDiscussionMessages(java.lang.String className,
		long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.deleteDiscussionMessages(className, classPK);
	}

	public static void deleteMessage(long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.deleteMessage(messageId);
	}

	public static void deleteMessage(
		com.liferay.portlet.messageboards.model.MBMessage message)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.deleteMessage(message);
	}

	public static java.util.List getCategoryMessages(long categoryId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getCategoryMessages(categoryId, begin, end);
	}

	public static java.util.List getCategoryMessages(long categoryId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getCategoryMessages(categoryId, begin,
			end, obc);
	}

	public static int getCategoryMessagesCount(long categoryId)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getCategoryMessagesCount(categoryId);
	}

	public static int getCategoriesMessagesCount(java.util.List categoryIds)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getCategoriesMessagesCount(categoryIds);
	}

	public static java.util.List getCompanyMessages(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getCompanyMessages(companyId, begin, end);
	}

	public static java.util.List getCompanyMessages(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getCompanyMessages(companyId, begin, end,
			obc);
	}

	public static int getCompanyMessagesCount(long companyId)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getCompanyMessagesCount(companyId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageDisplay getDiscussionMessageDisplay(
		long userId, java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getDiscussionMessageDisplay(userId,
			className, classPK);
	}

	public static int getDiscussionMessagesCount(long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getDiscussionMessagesCount(classNameId,
			classPK);
	}

	public static java.util.List getGroupMessages(long groupId, int begin,
		int end) throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getGroupMessages(groupId, begin, end);
	}

	public static java.util.List getGroupMessages(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getGroupMessages(groupId, begin, end, obc);
	}

	public static java.util.List getGroupMessages(long groupId, long userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getGroupMessages(groupId, userId, begin,
			end);
	}

	public static java.util.List getGroupMessages(long groupId, long userId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getGroupMessages(groupId, userId, begin,
			end, obc);
	}

	public static int getGroupMessagesCount(long groupId)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getGroupMessagesCount(groupId);
	}

	public static int getGroupMessagesCount(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getGroupMessagesCount(groupId, userId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage getMessage(
		long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMessage(messageId);
	}

	public static java.util.List getMessages(java.lang.String className,
		long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMessages(className, classPK);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageDisplay getMessageDisplay(
		long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMessageDisplay(messageId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageDisplay getMessageDisplay(
		com.liferay.portlet.messageboards.model.MBMessage message)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getMessageDisplay(message);
	}

	public static java.util.List getNoAssetMessages()
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getNoAssetMessages();
	}

	public static java.util.List getThreadMessages(long threadId)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getThreadMessages(threadId);
	}

	public static java.util.List getThreadMessages(long threadId,
		java.util.Comparator comparator)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getThreadMessages(threadId, comparator);
	}

	public static int getThreadMessagesCount(long threadId)
		throws com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.getThreadMessagesCount(threadId);
	}

	public static void subscribeMessage(long userId, long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.subscribeMessage(userId, messageId);
	}

	public static void unsubscribeMessage(long userId, long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.unsubscribeMessage(userId, messageId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage updateDiscussionMessage(
		long userId, long messageId, java.lang.String subject,
		java.lang.String body)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.updateDiscussionMessage(userId, messageId,
			subject, body);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage updateMessage(
		long userId, long messageId, java.lang.String subject,
		java.lang.String body, java.util.List files, double priority,
		java.lang.String[] tagsEntries, javax.portlet.PortletPreferences prefs,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.updateMessage(userId, messageId, subject,
			body, files, priority, tagsEntries, prefs, themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage updateMessage(
		long messageId, java.util.Date createDate, java.util.Date modifiedDate)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.updateMessage(messageId, createDate,
			modifiedDate);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage updateMessage(
		long messageId, java.lang.String body)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		return mbMessageLocalService.updateMessage(messageId, body);
	}

	public static void updateTagsAsset(long userId,
		com.liferay.portlet.messageboards.model.MBMessage message,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		MBMessageLocalService mbMessageLocalService = MBMessageLocalServiceFactory.getService();

		mbMessageLocalService.updateTagsAsset(userId, message, tagsEntries);
	}
}