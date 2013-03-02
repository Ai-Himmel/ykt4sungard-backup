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

package com.liferay.portlet.tags.service;


/**
 * <a href="TagsAssetLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.tags.service.TagsAssetLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.tags.service.TagsAssetLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.TagsAssetLocalService
 * @see com.liferay.portlet.tags.service.TagsAssetLocalServiceFactory
 *
 */
public class TagsAssetLocalServiceUtil {
	public static com.liferay.portlet.tags.model.TagsAsset addTagsAsset(
		com.liferay.portlet.tags.model.TagsAsset model)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.addTagsAsset(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.tags.model.TagsAsset updateTagsAsset(
		com.liferay.portlet.tags.model.TagsAsset model)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.updateTagsAsset(model);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTagsAssetPersistence();
	}

	public static void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setTagsAssetPersistence(tagsAssetPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTagsAssetFinder();
	}

	public static void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setTagsAssetFinder(tagsAssetFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTagsEntryPersistence();
	}

	public static void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setTagsEntryPersistence(tagsEntryPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTagsEntryFinder();
	}

	public static void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setTagsEntryFinder(tagsEntryFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence getTagsPropertyPersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTagsPropertyPersistence();
	}

	public static void setTagsPropertyPersistence(
		com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence tagsPropertyPersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setTagsPropertyPersistence(tagsPropertyPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsPropertyFinder getTagsPropertyFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTagsPropertyFinder();
	}

	public static void setTagsPropertyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyFinder tagsPropertyFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setTagsPropertyFinder(tagsPropertyFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder getTagsPropertyKeyFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTagsPropertyKeyFinder();
	}

	public static void setTagsPropertyKeyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder tagsPropertyKeyFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setTagsPropertyKeyFinder(tagsPropertyKeyFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsSourcePersistence getTagsSourcePersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTagsSourcePersistence();
	}

	public static void setTagsSourcePersistence(
		com.liferay.portlet.tags.service.persistence.TagsSourcePersistence tagsSourcePersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setTagsSourcePersistence(tagsSourcePersistence);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getGroupPersistence();
	}

	public static void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setGroupPersistence(groupPersistence);
	}

	public static com.liferay.portal.service.persistence.GroupFinder getGroupFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getGroupFinder();
	}

	public static void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setGroupFinder(groupFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence getBlogsEntryPersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getBlogsEntryPersistence();
	}

	public static void setBlogsEntryPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence blogsEntryPersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setBlogsEntryPersistence(blogsEntryPersistence);
	}

	public static com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder getBlogsEntryFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getBlogsEntryFinder();
	}

	public static void setBlogsEntryFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder blogsEntryFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setBlogsEntryFinder(blogsEntryFinder);
	}

	public static com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistence getBookmarksEntryPersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getBookmarksEntryPersistence();
	}

	public static void setBookmarksEntryPersistence(
		com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistence bookmarksEntryPersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setBookmarksEntryPersistence(bookmarksEntryPersistence);
	}

	public static com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinder getBookmarksEntryFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getBookmarksEntryFinder();
	}

	public static void setBookmarksEntryFinder(
		com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinder bookmarksEntryFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setBookmarksEntryFinder(bookmarksEntryFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence getDLFileEntryPersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getDLFileEntryPersistence();
	}

	public static void setDLFileEntryPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence dlFileEntryPersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setDLFileEntryPersistence(dlFileEntryPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder getDLFileEntryFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getDLFileEntryFinder();
	}

	public static void setDLFileEntryFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder dlFileEntryFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setDLFileEntryFinder(dlFileEntryFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getJournalArticlePersistence();
	}

	public static void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setJournalArticlePersistence(journalArticlePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getJournalArticleFinder();
	}

	public static void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setJournalArticleFinder(journalArticleFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getJournalArticleResourcePersistence();
	}

	public static void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setJournalArticleResourcePersistence(journalArticleResourcePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPagePersistence getWikiPagePersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getWikiPagePersistence();
	}

	public static void setWikiPagePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPagePersistence wikiPagePersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setWikiPagePersistence(wikiPagePersistence);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPageFinder getWikiPageFinder() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getWikiPageFinder();
	}

	public static void setWikiPageFinder(
		com.liferay.portlet.wiki.service.persistence.WikiPageFinder wikiPageFinder) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setWikiPageFinder(wikiPageFinder);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence getWikiPageResourcePersistence() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getWikiPageResourcePersistence();
	}

	public static void setWikiPageResourcePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence wikiPageResourcePersistence) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.setWikiPageResourcePersistence(wikiPageResourcePersistence);
	}

	public static void afterPropertiesSet() {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.afterPropertiesSet();
	}

	public static void deleteAsset(long assetId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.deleteAsset(assetId);
	}

	public static void deleteAsset(java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.deleteAsset(className, classPK);
	}

	public static void deleteAsset(
		com.liferay.portlet.tags.model.TagsAsset asset)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.deleteAsset(asset);
	}

	public static com.liferay.portlet.tags.model.TagsAsset getAsset(
		long assetId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAsset(assetId);
	}

	public static com.liferay.portlet.tags.model.TagsAsset getAsset(
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAsset(className, classPK);
	}

	public static com.liferay.portlet.tags.model.TagsAssetType[] getAssetTypes(
		java.lang.String languageId) {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssetTypes(languageId);
	}

	public static java.util.List getAssets(long[] entryIds, long[] notEntryIds,
		boolean andOperator, boolean excludeZeroViewCount, int begin, int end)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssets(entryIds, notEntryIds,
			andOperator, excludeZeroViewCount, begin, end);
	}

	public static java.util.List getAssets(long groupId, long[] classNameIds,
		long[] entryIds, long[] notEntryIds, boolean andOperator,
		boolean excludeZeroViewCount, int begin, int end)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssets(groupId, classNameIds, entryIds,
			notEntryIds, andOperator, excludeZeroViewCount, begin, end);
	}

	public static java.util.List getAssets(long[] entryIds, long[] notEntryIds,
		boolean andOperator, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate, int begin,
		int end) throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssets(entryIds, notEntryIds,
			andOperator, excludeZeroViewCount, publishDate, expirationDate,
			begin, end);
	}

	public static java.util.List getAssets(long groupId, long[] classNameIds,
		long[] entryIds, long[] notEntryIds, boolean andOperator,
		boolean excludeZeroViewCount, java.util.Date publishDate,
		java.util.Date expirationDate, int begin, int end)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssets(groupId, classNameIds, entryIds,
			notEntryIds, andOperator, excludeZeroViewCount, publishDate,
			expirationDate, begin, end);
	}

	public static java.util.List getAssets(long[] entryIds, long[] notEntryIds,
		boolean andOperator, java.lang.String orderByCol1,
		java.lang.String orderByCol2, java.lang.String orderByType1,
		java.lang.String orderByType2, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate, int begin,
		int end) throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssets(entryIds, notEntryIds,
			andOperator, orderByCol1, orderByCol2, orderByType1, orderByType2,
			excludeZeroViewCount, publishDate, expirationDate, begin, end);
	}

	public static java.util.List getAssets(long groupId, long[] classNameIds,
		long[] entryIds, long[] notEntryIds, boolean andOperator,
		java.lang.String orderByCol1, java.lang.String orderByCol2,
		java.lang.String orderByType1, java.lang.String orderByType2,
		boolean excludeZeroViewCount, java.util.Date publishDate,
		java.util.Date expirationDate, int begin, int end)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssets(groupId, classNameIds, entryIds,
			notEntryIds, andOperator, orderByCol1, orderByCol2, orderByType1,
			orderByType2, excludeZeroViewCount, publishDate, expirationDate,
			begin, end);
	}

	public static int getAssetsCount(long[] entryIds, long[] notEntryIds,
		boolean andOperator, boolean excludeZeroViewCount)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssetsCount(entryIds, notEntryIds,
			andOperator, excludeZeroViewCount);
	}

	public static int getAssetsCount(long groupId, long[] entryIds,
		long[] notEntryIds, boolean andOperator, boolean excludeZeroViewCount)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssetsCount(groupId, entryIds,
			notEntryIds, andOperator, excludeZeroViewCount);
	}

	public static int getAssetsCount(long[] entryIds, long[] notEntryIds,
		boolean andOperator, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssetsCount(entryIds, notEntryIds,
			andOperator, excludeZeroViewCount, publishDate, expirationDate);
	}

	public static int getAssetsCount(long groupId, long[] classNameIds,
		long[] entryIds, long[] notEntryIds, boolean andOperator,
		boolean excludeZeroViewCount, java.util.Date publishDate,
		java.util.Date expirationDate)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getAssetsCount(groupId, classNameIds,
			entryIds, notEntryIds, andOperator, excludeZeroViewCount,
			publishDate, expirationDate);
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] getCompanyAssetDisplays(
		long companyId, int begin, int end, java.lang.String languageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getCompanyAssetDisplays(companyId, begin,
			end, languageId);
	}

	public static java.util.List getCompanyAssets(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getCompanyAssets(companyId, begin, end);
	}

	public static int getCompanyAssetsCount(long companyId)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getCompanyAssetsCount(companyId);
	}

	public static java.util.List getTopViewedAssets(
		java.lang.String className, boolean asc, int begin, int end)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTopViewedAssets(className, asc, begin,
			end);
	}

	public static java.util.List getTopViewedAssets(
		java.lang.String[] className, boolean asc, int begin, int end)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.getTopViewedAssets(className, asc, begin,
			end);
	}

	public static com.liferay.portlet.tags.model.TagsAsset incrementViewCounter(
		java.lang.String className, long classPK)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.incrementViewCounter(className, classPK);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		java.lang.String portletId, java.lang.String keywords)
		throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.search(companyId, portletId, keywords);
	}

	public static com.liferay.portlet.tags.model.TagsAssetDisplay[] searchAssetDisplays(
		long companyId, java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.searchAssetDisplays(companyId, portletId,
			keywords, languageId, begin, end);
	}

	public static int searchAssetDisplaysCount(long companyId,
		java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId) throws com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.searchAssetDisplaysCount(companyId,
			portletId, keywords, languageId);
	}

	public static com.liferay.portlet.tags.model.TagsAsset updateAsset(
		long userId, long groupId, java.lang.String className, long classPK,
		java.lang.String[] entryNames)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.updateAsset(userId, groupId, className,
			classPK, entryNames);
	}

	public static com.liferay.portlet.tags.model.TagsAsset updateAsset(
		long userId, long groupId, java.lang.String className, long classPK,
		java.lang.String[] entryNames, java.util.Date startDate,
		java.util.Date endDate, java.util.Date publishDate,
		java.util.Date expirationDate, java.lang.String mimeType,
		java.lang.String title, java.lang.String description,
		java.lang.String summary, java.lang.String url, int height, int width,
		java.lang.Integer priority)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.updateAsset(userId, groupId, className,
			classPK, entryNames, startDate, endDate, publishDate,
			expirationDate, mimeType, title, description, summary, url, height,
			width, priority);
	}

	public static com.liferay.portlet.tags.model.TagsAsset updateAsset(
		long userId, long groupId, java.lang.String className, long classPK,
		java.lang.String[] entryNames, java.util.Date startDate,
		java.util.Date endDate, java.util.Date publishDate,
		java.util.Date expirationDate, java.lang.String mimeType,
		java.lang.String title, java.lang.String description,
		java.lang.String summary, java.lang.String url, int height, int width,
		java.lang.Integer priority, boolean sync)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		return tagsAssetLocalService.updateAsset(userId, groupId, className,
			classPK, entryNames, startDate, endDate, publishDate,
			expirationDate, mimeType, title, description, summary, url, height,
			width, priority, sync);
	}

	public static void validate(java.lang.String className,
		java.lang.String[] entryNames)
		throws com.liferay.portal.PortalException {
		TagsAssetLocalService tagsAssetLocalService = TagsAssetLocalServiceFactory.getService();

		tagsAssetLocalService.validate(className, entryNames);
	}
}