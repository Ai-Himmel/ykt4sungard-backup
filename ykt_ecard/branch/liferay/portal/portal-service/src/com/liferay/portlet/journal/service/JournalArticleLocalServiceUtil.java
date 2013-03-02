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

package com.liferay.portlet.journal.service;


/**
 * <a href="JournalArticleLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.journal.service.JournalArticleLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.journal.service.JournalArticleLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.JournalArticleLocalService
 * @see com.liferay.portlet.journal.service.JournalArticleLocalServiceFactory
 *
 */
public class JournalArticleLocalServiceUtil {
	public static com.liferay.portlet.journal.model.JournalArticle addJournalArticle(
		com.liferay.portlet.journal.model.JournalArticle model)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.addJournalArticle(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.journal.model.JournalArticle updateJournalArticle(
		com.liferay.portlet.journal.model.JournalArticle model)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.updateJournalArticle(model);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalArticlePersistence();
	}

	public static void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalArticlePersistence(journalArticlePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalArticleFinder();
	}

	public static void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalArticleFinder(journalArticleFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalArticleImagePersistence();
	}

	public static void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalArticleImagePersistence(journalArticleImagePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalArticleResourcePersistence();
	}

	public static void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalArticleResourcePersistence(journalArticleResourcePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalContentSearchPersistence();
	}

	public static void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalContentSearchPersistence(journalContentSearchPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalFeedPersistence();
	}

	public static void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalFeedPersistence(journalFeedPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalFeedFinder();
	}

	public static void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalFeedFinder(journalFeedFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalStructurePersistence();
	}

	public static void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalStructurePersistence(journalStructurePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalStructureFinder();
	}

	public static void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalStructureFinder(journalStructureFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalTemplatePersistence();
	}

	public static void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalTemplatePersistence(journalTemplatePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getJournalTemplateFinder();
	}

	public static void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setJournalTemplateFinder(journalTemplateFinder);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence getRatingsStatsPersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getRatingsStatsPersistence();
	}

	public static void setRatingsStatsPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence ratingsStatsPersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setRatingsStatsPersistence(ratingsStatsPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getTagsAssetPersistence();
	}

	public static void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setTagsAssetPersistence(tagsAssetPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getTagsAssetFinder();
	}

	public static void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setTagsAssetFinder(tagsAssetFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getTagsEntryPersistence();
	}

	public static void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setTagsEntryPersistence(tagsEntryPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getTagsEntryFinder();
	}

	public static void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder) {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.setTagsEntryFinder(tagsEntryFinder);
	}

	public static void afterPropertiesSet() {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.journal.model.JournalArticle addArticle(
		long userId, java.lang.String articleId, boolean autoArticleId,
		long plid, java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		int displayDateMonth, int displayDateDay, int displayDateYear,
		int displayDateHour, int displayDateMinute, int expirationDateMonth,
		int expirationDateDay, int expirationDateYear, int expirationDateHour,
		int expirationDateMinute, boolean neverExpire, int reviewDateMonth,
		int reviewDateDay, int reviewDateYear, int reviewDateHour,
		int reviewDateMinute, boolean neverReview, boolean indexable,
		boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, java.util.Map images,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs,
		java.lang.String[] tagsEntries, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.addArticle(userId, articleId,
			autoArticleId, plid, title, description, content, type,
			structureId, templateId, displayDateMonth, displayDateDay,
			displayDateYear, displayDateHour, displayDateMinute,
			expirationDateMonth, expirationDateDay, expirationDateYear,
			expirationDateHour, expirationDateMinute, neverExpire,
			reviewDateMonth, reviewDateDay, reviewDateYear, reviewDateHour,
			reviewDateMinute, neverReview, indexable, smallImage,
			smallImageURL, smallFile, images, articleURL, prefs, tagsEntries,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalArticle addArticle(
		java.lang.String uuid, long userId, java.lang.String articleId,
		boolean autoArticleId, long plid, java.lang.String title,
		java.lang.String description, java.lang.String content,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, int displayDateMonth, int displayDateDay,
		int displayDateYear, int displayDateHour, int displayDateMinute,
		int expirationDateMonth, int expirationDateDay, int expirationDateYear,
		int expirationDateHour, int expirationDateMinute, boolean neverExpire,
		int reviewDateMonth, int reviewDateDay, int reviewDateYear,
		int reviewDateHour, int reviewDateMinute, boolean neverReview,
		boolean indexable, boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, java.util.Map images,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs,
		java.lang.String[] tagsEntries, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.addArticle(uuid, userId, articleId,
			autoArticleId, plid, title, description, content, type,
			structureId, templateId, displayDateMonth, displayDateDay,
			displayDateYear, displayDateHour, displayDateMinute,
			expirationDateMonth, expirationDateDay, expirationDateYear,
			expirationDateHour, expirationDateMinute, neverExpire,
			reviewDateMonth, reviewDateDay, reviewDateYear, reviewDateHour,
			reviewDateMinute, neverReview, indexable, smallImage,
			smallImageURL, smallFile, images, articleURL, prefs, tagsEntries,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalArticle addArticle(
		long userId, java.lang.String articleId, boolean autoArticleId,
		long plid, java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		int displayDateMonth, int displayDateDay, int displayDateYear,
		int displayDateHour, int displayDateMinute, int expirationDateMonth,
		int expirationDateDay, int expirationDateYear, int expirationDateHour,
		int expirationDateMinute, boolean neverExpire, int reviewDateMonth,
		int reviewDateDay, int reviewDateYear, int reviewDateHour,
		int reviewDateMinute, boolean neverReview, boolean indexable,
		boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, java.util.Map images,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs,
		java.lang.String[] tagsEntries,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.addArticle(userId, articleId,
			autoArticleId, plid, title, description, content, type,
			structureId, templateId, displayDateMonth, displayDateDay,
			displayDateYear, displayDateHour, displayDateMinute,
			expirationDateMonth, expirationDateDay, expirationDateYear,
			expirationDateHour, expirationDateMinute, neverExpire,
			reviewDateMonth, reviewDateDay, reviewDateYear, reviewDateHour,
			reviewDateMinute, neverReview, indexable, smallImage,
			smallImageURL, smallFile, images, articleURL, prefs, tagsEntries,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalArticle addArticle(
		java.lang.String uuid, long userId, java.lang.String articleId,
		boolean autoArticleId, long plid, java.lang.String title,
		java.lang.String description, java.lang.String content,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, int displayDateMonth, int displayDateDay,
		int displayDateYear, int displayDateHour, int displayDateMinute,
		int expirationDateMonth, int expirationDateDay, int expirationDateYear,
		int expirationDateHour, int expirationDateMinute, boolean neverExpire,
		int reviewDateMonth, int reviewDateDay, int reviewDateYear,
		int reviewDateHour, int reviewDateMinute, boolean neverReview,
		boolean indexable, boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, java.util.Map images,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs,
		java.lang.String[] tagsEntries,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.addArticle(uuid, userId, articleId,
			autoArticleId, plid, title, description, content, type,
			structureId, templateId, displayDateMonth, displayDateDay,
			displayDateYear, displayDateHour, displayDateMinute,
			expirationDateMonth, expirationDateDay, expirationDateYear,
			expirationDateHour, expirationDateMinute, neverExpire,
			reviewDateMonth, reviewDateDay, reviewDateYear, reviewDateHour,
			reviewDateMinute, neverReview, indexable, smallImage,
			smallImageURL, smallFile, images, articleURL, prefs, tagsEntries,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalArticle addArticleToGroup(
		java.lang.String uuid, long userId, java.lang.String articleId,
		boolean autoArticleId, long groupId, java.lang.String title,
		java.lang.String description, java.lang.String content,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, int displayDateMonth, int displayDateDay,
		int displayDateYear, int displayDateHour, int displayDateMinute,
		int expirationDateMonth, int expirationDateDay, int expirationDateYear,
		int expirationDateHour, int expirationDateMinute, boolean neverExpire,
		int reviewDateMonth, int reviewDateDay, int reviewDateYear,
		int reviewDateHour, int reviewDateMinute, boolean neverReview,
		boolean indexable, boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, java.util.Map images,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs,
		java.lang.String[] tagsEntries,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.addArticleToGroup(uuid, userId,
			articleId, autoArticleId, groupId, title, description, content,
			type, structureId, templateId, displayDateMonth, displayDateDay,
			displayDateYear, displayDateHour, displayDateMinute,
			expirationDateMonth, expirationDateDay, expirationDateYear,
			expirationDateHour, expirationDateMinute, neverExpire,
			reviewDateMonth, reviewDateDay, reviewDateYear, reviewDateHour,
			reviewDateMinute, neverReview, indexable, smallImage,
			smallImageURL, smallFile, images, articleURL, prefs, tagsEntries,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public static void addArticleResources(long groupId,
		java.lang.String articleId, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.addArticleResources(groupId, articleId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addArticleResources(
		com.liferay.portlet.journal.model.JournalArticle article,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.addArticleResources(article,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addArticleResources(long groupId,
		java.lang.String articleId, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.addArticleResources(groupId, articleId,
			communityPermissions, guestPermissions);
	}

	public static void addArticleResources(
		com.liferay.portlet.journal.model.JournalArticle article,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.addArticleResources(article,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalArticle approveArticle(
		long userId, long groupId, java.lang.String articleId, double version,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.approveArticle(userId, groupId,
			articleId, version, articleURL, prefs);
	}

	public static com.liferay.portlet.journal.model.JournalArticle checkArticleResourcePrimKey(
		long groupId, java.lang.String articleId, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.checkArticleResourcePrimKey(groupId,
			articleId, version);
	}

	public static void checkArticles()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.checkArticles();
	}

	public static void checkNewLine(long groupId, java.lang.String articleId,
		double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.checkNewLine(groupId, articleId, version);
	}

	public static void checkStructure(long groupId, java.lang.String articleId,
		double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.checkStructure(groupId, articleId, version);
	}

	public static void deleteArticle(long groupId, java.lang.String articleId,
		double version, java.lang.String articleURL,
		javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.deleteArticle(groupId, articleId, version,
			articleURL, prefs);
	}

	public static void deleteArticle(
		com.liferay.portlet.journal.model.JournalArticle article,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.deleteArticle(article, articleURL, prefs);
	}

	public static void deleteArticles(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.deleteArticles(groupId);
	}

	public static void expireArticle(long groupId, java.lang.String articleId,
		double version, java.lang.String articleURL,
		javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.expireArticle(groupId, articleId, version,
			articleURL, prefs);
	}

	public static void expireArticle(
		com.liferay.portlet.journal.model.JournalArticle article,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.expireArticle(article, articleURL, prefs);
	}

	public static com.liferay.portlet.journal.model.JournalArticle getArticle(
		long id)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticle(id);
	}

	public static com.liferay.portlet.journal.model.JournalArticle getArticle(
		long groupId, java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticle(groupId, articleId);
	}

	public static com.liferay.portlet.journal.model.JournalArticle getArticle(
		long groupId, java.lang.String articleId, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticle(groupId, articleId, version);
	}

	public static java.lang.String getArticleContent(long groupId,
		java.lang.String articleId, java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleContent(groupId, articleId,
			languageId, themeDisplay);
	}

	public static java.lang.String getArticleContent(long groupId,
		java.lang.String articleId, java.lang.String templateId,
		java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleContent(groupId, articleId,
			templateId, languageId, themeDisplay);
	}

	public static java.lang.String getArticleContent(long groupId,
		java.lang.String articleId, double version,
		java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleContent(groupId, articleId,
			version, languageId, themeDisplay);
	}

	public static java.lang.String getArticleContent(long groupId,
		java.lang.String articleId, double version,
		java.lang.String templateId, java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleContent(groupId, articleId,
			version, templateId, languageId, themeDisplay);
	}

	public static com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleDisplay(groupId, articleId,
			languageId, themeDisplay);
	}

	public static com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, java.lang.String languageId,
		int page, java.lang.String xmlRequest,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleDisplay(groupId, articleId,
			languageId, page, xmlRequest, themeDisplay);
	}

	public static com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, java.lang.String templateId,
		java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleDisplay(groupId, articleId,
			templateId, languageId, themeDisplay);
	}

	public static com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, java.lang.String templateId,
		java.lang.String languageId, int page, java.lang.String xmlRequest,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleDisplay(groupId, articleId,
			templateId, languageId, page, xmlRequest, themeDisplay);
	}

	public static com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, double version,
		java.lang.String templateId, java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleDisplay(groupId, articleId,
			version, templateId, languageId, themeDisplay);
	}

	public static com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, double version,
		java.lang.String templateId, java.lang.String languageId, int page,
		java.lang.String xmlRequest,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticleDisplay(groupId, articleId,
			version, templateId, languageId, page, xmlRequest, themeDisplay);
	}

	public static java.util.List getArticles()
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticles();
	}

	public static java.util.List getArticles(long groupId)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticles(groupId);
	}

	public static java.util.List getArticles(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticles(groupId, begin, end);
	}

	public static java.util.List getArticles(long groupId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticles(groupId, begin, end, obc);
	}

	public static java.util.List getArticlesBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticlesBySmallImageId(smallImageId);
	}

	public static int getArticlesCount(long groupId)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getArticlesCount(groupId);
	}

	public static com.liferay.portlet.journal.model.JournalArticle getDisplayArticle(
		long groupId, java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getDisplayArticle(groupId, articleId);
	}

	public static com.liferay.portlet.journal.model.JournalArticle getLatestArticle(
		long groupId, java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getLatestArticle(groupId, articleId);
	}

	public static com.liferay.portlet.journal.model.JournalArticle getLatestArticle(
		long groupId, java.lang.String articleId, java.lang.Boolean approved)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getLatestArticle(groupId, articleId,
			approved);
	}

	public static double getLatestVersion(long groupId,
		java.lang.String articleId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getLatestVersion(groupId, articleId);
	}

	public static double getLatestVersion(long groupId,
		java.lang.String articleId, java.lang.Boolean approved)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getLatestVersion(groupId, articleId,
			approved);
	}

	public static java.util.List getStructureArticles(long groupId,
		java.lang.String structureId) throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getStructureArticles(groupId,
			structureId);
	}

	public static java.util.List getStructureArticles(long groupId,
		java.lang.String structureId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getStructureArticles(groupId,
			structureId, begin, end, obc);
	}

	public static int getStructureArticlesCount(long groupId,
		java.lang.String structureId) throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getStructureArticlesCount(groupId,
			structureId);
	}

	public static java.util.List getTemplateArticles(long groupId,
		java.lang.String templateId) throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getTemplateArticles(groupId,
			templateId);
	}

	public static java.util.List getTemplateArticles(long groupId,
		java.lang.String templateId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getTemplateArticles(groupId,
			templateId, begin, end, obc);
	}

	public static int getTemplateArticlesCount(long groupId,
		java.lang.String templateId) throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.getTemplateArticlesCount(groupId,
			templateId);
	}

	public static boolean hasArticle(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.hasArticle(groupId, articleId);
	}

	public static boolean isLatestVersion(long groupId,
		java.lang.String articleId, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.isLatestVersion(groupId, articleId,
			version);
	}

	public static boolean isLatestVersion(long groupId,
		java.lang.String articleId, double version, java.lang.Boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.isLatestVersion(groupId, articleId,
			version, active);
	}

	public static void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.reIndex(ids);
	}

	public static com.liferay.portlet.journal.model.JournalArticle removeArticleLocale(
		long groupId, java.lang.String articleId, double version,
		java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.removeArticleLocale(groupId,
			articleId, version, languageId);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, java.lang.String keywords)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.search(companyId, groupId, keywords);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, java.lang.String keywords, java.lang.String sortField)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.search(companyId, groupId, keywords,
			sortField);
	}

	public static java.util.List search(long companyId, long groupId,
		java.lang.String keywords, java.lang.Double version,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, java.util.Date displayDateGT,
		java.util.Date displayDateLT, java.lang.Boolean approved,
		java.lang.Boolean expired, java.util.Date reviewDate, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.search(companyId, groupId, keywords,
			version, type, structureId, templateId, displayDateGT,
			displayDateLT, approved, expired, reviewDate, begin, end, obc);
	}

	public static java.util.List search(long companyId, long groupId,
		java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.search(companyId, groupId, articleId,
			version, title, description, content, type, structureId,
			templateId, displayDateGT, displayDateLT, approved, expired,
			reviewDate, andOperator, begin, end, obc);
	}

	public static java.util.List search(long companyId, long groupId,
		java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String[] structureIds, java.lang.String[] templateIds,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.search(companyId, groupId, articleId,
			version, title, description, content, type, structureIds,
			templateIds, displayDateGT, displayDateLT, approved, expired,
			reviewDate, andOperator, begin, end, obc);
	}

	public static int searchCount(long companyId, long groupId,
		java.lang.String keywords, java.lang.Double version,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, java.util.Date displayDateGT,
		java.util.Date displayDateLT, java.lang.Boolean approved,
		java.lang.Boolean expired, java.util.Date reviewDate)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.searchCount(companyId, groupId,
			keywords, version, type, structureId, templateId, displayDateGT,
			displayDateLT, approved, expired, reviewDate);
	}

	public static int searchCount(long companyId, long groupId,
		java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.searchCount(companyId, groupId,
			articleId, version, title, description, content, type, structureId,
			templateId, displayDateGT, displayDateLT, approved, expired,
			reviewDate, andOperator);
	}

	public static int searchCount(long companyId, long groupId,
		java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String[] structureIds, java.lang.String[] templateIds,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator)
		throws com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.searchCount(companyId, groupId,
			articleId, version, title, description, content, type,
			structureIds, templateIds, displayDateGT, displayDateLT, approved,
			expired, reviewDate, andOperator);
	}

	public static com.liferay.portlet.journal.model.JournalArticle updateArticle(
		long userId, long groupId, java.lang.String articleId, double version,
		boolean incrementVersion, java.lang.String title,
		java.lang.String description, java.lang.String content,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, int displayDateMonth, int displayDateDay,
		int displayDateYear, int displayDateHour, int displayDateMinute,
		int expirationDateMonth, int expirationDateDay, int expirationDateYear,
		int expirationDateHour, int expirationDateMinute, boolean neverExpire,
		int reviewDateMonth, int reviewDateDay, int reviewDateYear,
		int reviewDateHour, int reviewDateMinute, boolean neverReview,
		boolean indexable, boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, java.util.Map images,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.updateArticle(userId, groupId,
			articleId, version, incrementVersion, title, description, content,
			type, structureId, templateId, displayDateMonth, displayDateDay,
			displayDateYear, displayDateHour, displayDateMinute,
			expirationDateMonth, expirationDateDay, expirationDateYear,
			expirationDateHour, expirationDateMinute, neverExpire,
			reviewDateMonth, reviewDateDay, reviewDateYear, reviewDateHour,
			reviewDateMinute, neverReview, indexable, smallImage,
			smallImageURL, smallFile, images, articleURL, prefs, tagsEntries);
	}

	public static com.liferay.portlet.journal.model.JournalArticle updateContent(
		long groupId, java.lang.String articleId, double version,
		java.lang.String content)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		return journalArticleLocalService.updateContent(groupId, articleId,
			version, content);
	}

	public static void updateTagsAsset(long userId,
		com.liferay.portlet.journal.model.JournalArticle article,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalArticleLocalService journalArticleLocalService = JournalArticleLocalServiceFactory.getService();

		journalArticleLocalService.updateTagsAsset(userId, article, tagsEntries);
	}
}