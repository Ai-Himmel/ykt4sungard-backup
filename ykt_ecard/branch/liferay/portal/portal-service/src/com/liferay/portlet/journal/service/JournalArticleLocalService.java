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
 * <a href="JournalArticleLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.journal.service.impl.JournalArticleLocalServiceImpl</code>.
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
 * @see com.liferay.portlet.journal.service.JournalArticleLocalServiceFactory
 * @see com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil
 *
 */
public interface JournalArticleLocalService {
	public com.liferay.portlet.journal.model.JournalArticle addJournalArticle(
		com.liferay.portlet.journal.model.JournalArticle model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticle updateJournalArticle(
		com.liferay.portlet.journal.model.JournalArticle model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence();

	public void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder();

	public void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder);

	public com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence();

	public void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence();

	public void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence();

	public void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence);

	public com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence();

	public void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence);

	public com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder();

	public void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder);

	public com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence();

	public void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder();

	public void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder);

	public com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence();

	public void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder();

	public void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder);

	public com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence();

	public void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence);

	public com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence();

	public void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence);

	public com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder();

	public void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder);

	public com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence();

	public void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence);

	public com.liferay.portal.service.persistence.ResourceFinder getResourceFinder();

	public void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder);

	public com.liferay.portal.service.persistence.UserPersistence getUserPersistence();

	public void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence);

	public com.liferay.portal.service.persistence.UserFinder getUserFinder();

	public void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder);

	public com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence();

	public void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence);

	public com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder();

	public void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder);

	public com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence getRatingsStatsPersistence();

	public void setRatingsStatsPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence ratingsStatsPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence();

	public void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder();

	public void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder);

	public com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence();

	public void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder();

	public void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder);

	public void afterPropertiesSet();

	public com.liferay.portlet.journal.model.JournalArticle addArticle(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle addArticle(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle addArticle(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle addArticle(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle addArticleToGroup(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addArticleResources(long groupId, java.lang.String articleId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addArticleResources(
		com.liferay.portlet.journal.model.JournalArticle article,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addArticleResources(long groupId, java.lang.String articleId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addArticleResources(
		com.liferay.portlet.journal.model.JournalArticle article,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle approveArticle(
		long userId, long groupId, java.lang.String articleId, double version,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle checkArticleResourcePrimKey(
		long groupId, java.lang.String articleId, double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void checkArticles()
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void checkNewLine(long groupId, java.lang.String articleId,
		double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void checkStructure(long groupId, java.lang.String articleId,
		double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteArticle(long groupId, java.lang.String articleId,
		double version, java.lang.String articleURL,
		javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteArticle(
		com.liferay.portlet.journal.model.JournalArticle article,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteArticles(long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void expireArticle(long groupId, java.lang.String articleId,
		double version, java.lang.String articleURL,
		javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void expireArticle(
		com.liferay.portlet.journal.model.JournalArticle article,
		java.lang.String articleURL, javax.portlet.PortletPreferences prefs)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle getArticle(long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle getArticle(
		long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle getArticle(
		long groupId, java.lang.String articleId, double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.lang.String getArticleContent(long groupId,
		java.lang.String articleId, java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.lang.String getArticleContent(long groupId,
		java.lang.String articleId, java.lang.String templateId,
		java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.lang.String getArticleContent(long groupId,
		java.lang.String articleId, double version,
		java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.lang.String getArticleContent(long groupId,
		java.lang.String articleId, double version,
		java.lang.String templateId, java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, java.lang.String languageId,
		int page, java.lang.String xmlRequest,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, java.lang.String templateId,
		java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, java.lang.String templateId,
		java.lang.String languageId, int page, java.lang.String xmlRequest,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, double version,
		java.lang.String templateId, java.lang.String languageId,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticleDisplay getArticleDisplay(
		long groupId, java.lang.String articleId, double version,
		java.lang.String templateId, java.lang.String languageId, int page,
		java.lang.String xmlRequest,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getArticles()
		throws com.liferay.portal.SystemException;

	public java.util.List getArticles(long groupId)
		throws com.liferay.portal.SystemException;

	public java.util.List getArticles(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getArticles(long groupId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public java.util.List getArticlesBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException;

	public int getArticlesCount(long groupId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticle getDisplayArticle(
		long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle getLatestArticle(
		long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle getLatestArticle(
		long groupId, java.lang.String articleId, java.lang.Boolean approved)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public double getLatestVersion(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public double getLatestVersion(long groupId, java.lang.String articleId,
		java.lang.Boolean approved)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getStructureArticles(long groupId,
		java.lang.String structureId) throws com.liferay.portal.SystemException;

	public java.util.List getStructureArticles(long groupId,
		java.lang.String structureId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int getStructureArticlesCount(long groupId,
		java.lang.String structureId) throws com.liferay.portal.SystemException;

	public java.util.List getTemplateArticles(long groupId,
		java.lang.String templateId) throws com.liferay.portal.SystemException;

	public java.util.List getTemplateArticles(long groupId,
		java.lang.String templateId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int getTemplateArticlesCount(long groupId,
		java.lang.String templateId) throws com.liferay.portal.SystemException;

	public boolean hasArticle(long groupId, java.lang.String articleId)
		throws com.liferay.portal.SystemException;

	public boolean isLatestVersion(long groupId, java.lang.String articleId,
		double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public boolean isLatestVersion(long groupId, java.lang.String articleId,
		double version, java.lang.Boolean active)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticle removeArticleLocale(
		long groupId, java.lang.String articleId, double version,
		java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, java.lang.String keywords)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, java.lang.String keywords, java.lang.String sortField)
		throws com.liferay.portal.SystemException;

	public java.util.List search(long companyId, long groupId,
		java.lang.String keywords, java.lang.Double version,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, java.util.Date displayDateGT,
		java.util.Date displayDateLT, java.lang.Boolean approved,
		java.lang.Boolean expired, java.util.Date reviewDate, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public java.util.List search(long companyId, long groupId,
		java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public java.util.List search(long companyId, long groupId,
		java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String[] structureIds, java.lang.String[] templateIds,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int searchCount(long companyId, long groupId,
		java.lang.String keywords, java.lang.Double version,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, java.util.Date displayDateGT,
		java.util.Date displayDateLT, java.lang.Boolean approved,
		java.lang.Boolean expired, java.util.Date reviewDate)
		throws com.liferay.portal.SystemException;

	public int searchCount(long companyId, long groupId,
		java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator)
		throws com.liferay.portal.SystemException;

	public int searchCount(long companyId, long groupId,
		java.lang.String articleId, java.lang.Double version,
		java.lang.String title, java.lang.String description,
		java.lang.String content, java.lang.String type,
		java.lang.String[] structureIds, java.lang.String[] templateIds,
		java.util.Date displayDateGT, java.util.Date displayDateLT,
		java.lang.Boolean approved, java.lang.Boolean expired,
		java.util.Date reviewDate, boolean andOperator)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalArticle updateArticle(
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
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalArticle updateContent(
		long groupId, java.lang.String articleId, double version,
		java.lang.String content)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void updateTagsAsset(long userId,
		com.liferay.portlet.journal.model.JournalArticle article,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}