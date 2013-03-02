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
 * <a href="TagsAssetLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.tags.service.impl.TagsAssetLocalServiceImpl</code>.
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
 * @see com.liferay.portlet.tags.service.TagsAssetLocalServiceFactory
 * @see com.liferay.portlet.tags.service.TagsAssetLocalServiceUtil
 *
 */
public interface TagsAssetLocalService {
	public com.liferay.portlet.tags.model.TagsAsset addTagsAsset(
		com.liferay.portlet.tags.model.TagsAsset model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAsset updateTagsAsset(
		com.liferay.portlet.tags.model.TagsAsset model)
		throws com.liferay.portal.SystemException;

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

	public com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence getTagsPropertyPersistence();

	public void setTagsPropertyPersistence(
		com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence tagsPropertyPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsPropertyFinder getTagsPropertyFinder();

	public void setTagsPropertyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyFinder tagsPropertyFinder);

	public com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder getTagsPropertyKeyFinder();

	public void setTagsPropertyKeyFinder(
		com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder tagsPropertyKeyFinder);

	public com.liferay.portlet.tags.service.persistence.TagsSourcePersistence getTagsSourcePersistence();

	public void setTagsSourcePersistence(
		com.liferay.portlet.tags.service.persistence.TagsSourcePersistence tagsSourcePersistence);

	public com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence();

	public void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence);

	public com.liferay.portal.service.persistence.GroupPersistence getGroupPersistence();

	public void setGroupPersistence(
		com.liferay.portal.service.persistence.GroupPersistence groupPersistence);

	public com.liferay.portal.service.persistence.GroupFinder getGroupFinder();

	public void setGroupFinder(
		com.liferay.portal.service.persistence.GroupFinder groupFinder);

	public com.liferay.portal.service.persistence.UserPersistence getUserPersistence();

	public void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence);

	public com.liferay.portal.service.persistence.UserFinder getUserFinder();

	public void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder);

	public com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence getBlogsEntryPersistence();

	public void setBlogsEntryPersistence(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence blogsEntryPersistence);

	public com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder getBlogsEntryFinder();

	public void setBlogsEntryFinder(
		com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder blogsEntryFinder);

	public com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistence getBookmarksEntryPersistence();

	public void setBookmarksEntryPersistence(
		com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistence bookmarksEntryPersistence);

	public com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinder getBookmarksEntryFinder();

	public void setBookmarksEntryFinder(
		com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinder bookmarksEntryFinder);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence getDLFileEntryPersistence();

	public void setDLFileEntryPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence dlFileEntryPersistence);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder getDLFileEntryFinder();

	public void setDLFileEntryFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder dlFileEntryFinder);

	public com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence();

	public void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder();

	public void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder);

	public com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence();

	public void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence);

	public com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence();

	public void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence);

	public com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder();

	public void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder);

	public com.liferay.portlet.wiki.service.persistence.WikiPagePersistence getWikiPagePersistence();

	public void setWikiPagePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPagePersistence wikiPagePersistence);

	public com.liferay.portlet.wiki.service.persistence.WikiPageFinder getWikiPageFinder();

	public void setWikiPageFinder(
		com.liferay.portlet.wiki.service.persistence.WikiPageFinder wikiPageFinder);

	public com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence getWikiPageResourcePersistence();

	public void setWikiPageResourcePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence wikiPageResourcePersistence);

	public void afterPropertiesSet();

	public void deleteAsset(long assetId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteAsset(java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteAsset(com.liferay.portlet.tags.model.TagsAsset asset)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.tags.model.TagsAsset getAsset(long assetId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.tags.model.TagsAsset getAsset(
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.tags.model.TagsAssetType[] getAssetTypes(
		java.lang.String languageId);

	public java.util.List getAssets(long[] entryIds, long[] notEntryIds,
		boolean andOperator, boolean excludeZeroViewCount, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getAssets(long groupId, long[] classNameIds,
		long[] entryIds, long[] notEntryIds, boolean andOperator,
		boolean excludeZeroViewCount, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getAssets(long[] entryIds, long[] notEntryIds,
		boolean andOperator, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate, int begin,
		int end) throws com.liferay.portal.SystemException;

	public java.util.List getAssets(long groupId, long[] classNameIds,
		long[] entryIds, long[] notEntryIds, boolean andOperator,
		boolean excludeZeroViewCount, java.util.Date publishDate,
		java.util.Date expirationDate, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getAssets(long[] entryIds, long[] notEntryIds,
		boolean andOperator, java.lang.String orderByCol1,
		java.lang.String orderByCol2, java.lang.String orderByType1,
		java.lang.String orderByType2, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate, int begin,
		int end) throws com.liferay.portal.SystemException;

	public java.util.List getAssets(long groupId, long[] classNameIds,
		long[] entryIds, long[] notEntryIds, boolean andOperator,
		java.lang.String orderByCol1, java.lang.String orderByCol2,
		java.lang.String orderByType1, java.lang.String orderByType2,
		boolean excludeZeroViewCount, java.util.Date publishDate,
		java.util.Date expirationDate, int begin, int end)
		throws com.liferay.portal.SystemException;

	public int getAssetsCount(long[] entryIds, long[] notEntryIds,
		boolean andOperator, boolean excludeZeroViewCount)
		throws com.liferay.portal.SystemException;

	public int getAssetsCount(long groupId, long[] entryIds,
		long[] notEntryIds, boolean andOperator, boolean excludeZeroViewCount)
		throws com.liferay.portal.SystemException;

	public int getAssetsCount(long[] entryIds, long[] notEntryIds,
		boolean andOperator, boolean excludeZeroViewCount,
		java.util.Date publishDate, java.util.Date expirationDate)
		throws com.liferay.portal.SystemException;

	public int getAssetsCount(long groupId, long[] classNameIds,
		long[] entryIds, long[] notEntryIds, boolean andOperator,
		boolean excludeZeroViewCount, java.util.Date publishDate,
		java.util.Date expirationDate)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAssetDisplay[] getCompanyAssetDisplays(
		long companyId, int begin, int end, java.lang.String languageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getCompanyAssets(long companyId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public int getCompanyAssetsCount(long companyId)
		throws com.liferay.portal.SystemException;

	public java.util.List getTopViewedAssets(java.lang.String className,
		boolean asc, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getTopViewedAssets(java.lang.String[] className,
		boolean asc, int begin, int end)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAsset incrementViewCounter(
		java.lang.String className, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.kernel.search.Hits search(long companyId,
		java.lang.String portletId, java.lang.String keywords)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAssetDisplay[] searchAssetDisplays(
		long companyId, java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId, int begin, int end)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public int searchAssetDisplaysCount(long companyId,
		java.lang.String portletId, java.lang.String keywords,
		java.lang.String languageId) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.tags.model.TagsAsset updateAsset(long userId,
		long groupId, java.lang.String className, long classPK,
		java.lang.String[] entryNames)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.tags.model.TagsAsset updateAsset(long userId,
		long groupId, java.lang.String className, long classPK,
		java.lang.String[] entryNames, java.util.Date startDate,
		java.util.Date endDate, java.util.Date publishDate,
		java.util.Date expirationDate, java.lang.String mimeType,
		java.lang.String title, java.lang.String description,
		java.lang.String summary, java.lang.String url, int height, int width,
		java.lang.Integer priority)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.tags.model.TagsAsset updateAsset(long userId,
		long groupId, java.lang.String className, long classPK,
		java.lang.String[] entryNames, java.util.Date startDate,
		java.util.Date endDate, java.util.Date publishDate,
		java.util.Date expirationDate, java.lang.String mimeType,
		java.lang.String title, java.lang.String description,
		java.lang.String summary, java.lang.String url, int height, int width,
		java.lang.Integer priority, boolean sync)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void validate(java.lang.String className,
		java.lang.String[] entryNames)
		throws com.liferay.portal.PortalException;
}