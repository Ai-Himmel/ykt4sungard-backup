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

package com.liferay.portlet.tags.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.Document;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsValues;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.tags.model.TagsAsset;
import com.liferay.portlet.tags.model.TagsAssetDisplay;
import com.liferay.portlet.tags.model.TagsAssetType;
import com.liferay.portlet.tags.model.TagsEntry;
import com.liferay.portlet.tags.service.base.TagsAssetLocalServiceBaseImpl;
import com.liferay.portlet.tags.util.TagsAssetValidator;
import com.liferay.portlet.tags.util.TagsUtil;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.util.ListUtil;
import com.liferay.util.lucene.HitsImpl;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.index.Term;
import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.TermQuery;

/**
 * <a href="TagsAssetLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsAssetLocalServiceImpl extends TagsAssetLocalServiceBaseImpl {

	public void deleteAsset(long assetId)
		throws PortalException, SystemException {

		TagsAsset asset = tagsAssetPersistence.findByPrimaryKey(assetId);

		deleteAsset(asset);
	}

	public void deleteAsset(String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		TagsAsset asset = tagsAssetPersistence.fetchByC_C(classNameId, classPK);

		if (asset != null) {
			deleteAsset(asset);
		}
	}

	public void deleteAsset(TagsAsset asset)
		throws PortalException, SystemException {

		tagsAssetPersistence.remove(asset.getAssetId());
	}

	public TagsAsset getAsset(long assetId)
		throws PortalException, SystemException {

		return tagsAssetPersistence.findByPrimaryKey(assetId);
	}

	public TagsAsset getAsset(String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return tagsAssetPersistence.findByC_C(classNameId, classPK);
	}

	public TagsAssetType[] getAssetTypes(String languageId) {
		TagsAssetType[] assetTypes =
			new TagsAssetType[TagsUtil.ASSET_TYPE_CLASS_NAMES.length];

		for (int i = 0; i < TagsUtil.ASSET_TYPE_CLASS_NAMES.length; i++) {
			assetTypes[i] = getAssetType(
				TagsUtil.ASSET_TYPE_CLASS_NAMES[i], languageId);
		}

		return assetTypes;
	}

	public List getAssets(
			long[] entryIds, long[] notEntryIds, boolean andOperator,
			boolean excludeZeroViewCount, int begin, int end)
		throws SystemException {

		return getAssets(
			0, new long[0], entryIds, notEntryIds, andOperator,
			excludeZeroViewCount, null, null, begin, end);
	}

	public List getAssets(
			long groupId, long[] classNameIds, long[] entryIds,
			long[] notEntryIds, boolean andOperator,
			boolean excludeZeroViewCount, int begin, int end)
		throws SystemException {

		return getAssets(
			groupId, classNameIds, entryIds, notEntryIds, andOperator,
			excludeZeroViewCount, null, null, begin, end);
	}

	public List getAssets(
			long[] entryIds, long[] notEntryIds, boolean andOperator,
			boolean excludeZeroViewCount, Date publishDate, Date expirationDate,
			int begin, int end)
		throws SystemException {

		return getAssets(
			0, new long[0], entryIds, notEntryIds, andOperator,
			excludeZeroViewCount, null, null, begin, end);
	}

	public List getAssets(
			long groupId, long[] classNameIds, long[] entryIds,
			long[] notEntryIds, boolean andOperator,
			boolean excludeZeroViewCount, Date publishDate, Date expirationDate,
			int begin, int end)
		throws SystemException {

		if (andOperator) {
			return tagsAssetFinder.findByAndEntryIds(
				groupId, classNameIds, entryIds, notEntryIds, null, null, null,
				null, excludeZeroViewCount, publishDate, expirationDate, begin,
				end);
		}
		else {
			return tagsAssetFinder.findByOrEntryIds(
				groupId, classNameIds, entryIds, notEntryIds, null, null, null,
				null, excludeZeroViewCount, publishDate, expirationDate, begin,
				end);
		}
	}

	public List getAssets(
			long[] entryIds, long[] notEntryIds, boolean andOperator,
			String orderByCol1, String orderByCol2, String orderByType1,
			String orderByType2, boolean excludeZeroViewCount, Date publishDate,
			Date expirationDate, int begin, int end)
		throws SystemException {

		return getAssets(
			0, new long[0], entryIds, notEntryIds, andOperator,
			excludeZeroViewCount, publishDate, expirationDate, begin, end);
	}

	public List getAssets(
			long groupId, long[] classNameIds, long[] entryIds,
			long[] notEntryIds, boolean andOperator, String orderByCol1,
			String orderByCol2, String orderByType1, String orderByType2,
			boolean excludeZeroViewCount, Date publishDate, Date expirationDate,
			int begin, int end)
		throws SystemException {

		if (andOperator) {
			return tagsAssetFinder.findByAndEntryIds(
				groupId, classNameIds, entryIds, notEntryIds, orderByCol1,
				orderByCol2, orderByType1, orderByType2, excludeZeroViewCount,
				publishDate, expirationDate, begin, end);
		}
		else {
			return tagsAssetFinder.findByOrEntryIds(
				groupId, classNameIds, entryIds, notEntryIds, orderByCol1,
				orderByCol2, orderByType1, orderByType2, excludeZeroViewCount,
				publishDate, expirationDate, begin, end);
		}
	}

	public int getAssetsCount(
			long[] entryIds, long[] notEntryIds, boolean andOperator,
			boolean excludeZeroViewCount)
		throws SystemException {

		return getAssetsCount(
			0, new long[0], entryIds, notEntryIds, andOperator,
			excludeZeroViewCount, null, null);
	}

	public int getAssetsCount(
			long groupId, long[] entryIds, long[] notEntryIds,
			boolean andOperator, boolean excludeZeroViewCount)
		throws SystemException {

		return getAssetsCount(
			groupId, new long[0], entryIds, notEntryIds, andOperator,
			excludeZeroViewCount, null, null);
	}

	public int getAssetsCount(
			long[] entryIds, long[] notEntryIds, boolean andOperator,
			boolean excludeZeroViewCount, Date publishDate, Date expirationDate)
		throws SystemException {

		return getAssetsCount(
			0, new long[0], entryIds, notEntryIds, andOperator,
			excludeZeroViewCount, publishDate, expirationDate);
	}

	public int getAssetsCount(
			long groupId, long[] classNameIds, long[] entryIds,
			long[] notEntryIds, boolean andOperator,
			boolean excludeZeroViewCount, Date publishDate, Date expirationDate)
		throws SystemException {

		if (andOperator) {
			return tagsAssetFinder.countByAndEntryIds(
				groupId, classNameIds, entryIds, notEntryIds,
				excludeZeroViewCount, publishDate, expirationDate);
		}
		else {
			return tagsAssetFinder.countByOrEntryIds(
				groupId, classNameIds, entryIds, notEntryIds,
				excludeZeroViewCount, publishDate, expirationDate);
		}
	}

	public TagsAssetDisplay[] getCompanyAssetDisplays(
			long companyId, int begin, int end, String languageId)
		throws PortalException, SystemException {

		return getAssetDisplays(
			getCompanyAssets(companyId, begin, end), languageId);
	}

	public List getCompanyAssets(long companyId, int begin, int end)
		throws SystemException {

		return tagsAssetPersistence.findByCompanyId(companyId, begin, end);
	}

	public int getCompanyAssetsCount(long companyId) throws SystemException {
		return tagsAssetPersistence.countByCompanyId(companyId);
	}

	public List getTopViewedAssets(
			String className, boolean asc, int begin, int end)
		throws SystemException {

		return getTopViewedAssets(new String[] {className}, asc, begin, end);
	}

	public List getTopViewedAssets(
			String[] className, boolean asc, int begin, int end)
		throws SystemException {

		long[] classNameIds = new long[className.length];

		for (int i = 0; i < className.length; i++) {
			classNameIds[i] = PortalUtil.getClassNameId(className[i]);
		}

		return tagsAssetFinder.findByViewCount(classNameIds, asc, begin, end);
	}

	public TagsAsset incrementViewCounter(String className, long classPK)
		throws PortalException, SystemException {

		if (classPK <= 0) {
			return null;
		}

		long classNameId = PortalUtil.getClassNameId(className);

		TagsAsset asset = tagsAssetPersistence.fetchByC_C(classNameId, classPK);

		if (asset != null) {
			asset.setViewCount(asset.getViewCount() + 1);

			tagsAssetPersistence.update(asset);
		}

		return asset;
	}

	public Hits search(long companyId, String portletId, String keywords)
		throws SystemException {

		Searcher searcher = null;

		try {
			HitsImpl hits = new HitsImpl();

			BooleanQuery contextQuery = new BooleanQuery();

			if (Validator.isNotNull(portletId)) {
				LuceneUtil.addRequiredTerm(
					contextQuery, LuceneFields.PORTLET_ID, portletId);
			}
			else {
				BooleanQuery portletIdsQuery = new BooleanQuery();

				for (int i = 0; i < TagsUtil.ASSET_TYPE_PORTLET_IDS.length;
						i++) {

					Term term = new Term(
						LuceneFields.PORTLET_ID,
						TagsUtil.ASSET_TYPE_PORTLET_IDS[i]);
					TermQuery termQuery = new TermQuery(term);

					portletIdsQuery.add(termQuery, BooleanClause.Occur.SHOULD);
				}

				contextQuery.add(portletIdsQuery, BooleanClause.Occur.MUST);
			}

			BooleanQuery searchQuery = new BooleanQuery();

			if (Validator.isNotNull(keywords)) {
				LuceneUtil.addTerm(searchQuery, LuceneFields.TITLE, keywords);
				LuceneUtil.addTerm(searchQuery, LuceneFields.CONTENT, keywords);
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.DESCRIPTION, keywords);
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.PROPERTIES, keywords);
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.TAG_ENTRY, keywords);
			}

			BooleanQuery fullQuery = new BooleanQuery();

			fullQuery.add(contextQuery, BooleanClause.Occur.MUST);

			if (searchQuery.clauses().size() > 0) {
				fullQuery.add(searchQuery, BooleanClause.Occur.MUST);
			}

			searcher = LuceneUtil.getSearcher(companyId);

			hits.recordHits(searcher.search(fullQuery), searcher);

			return hits;
		}
		catch (Exception e) {
			return LuceneUtil.closeSearcher(searcher, keywords, e);
		}
	}

	public TagsAssetDisplay[] searchAssetDisplays(
			long companyId, String portletId, String keywords,
			String languageId, int begin, int end)
		throws PortalException, SystemException {

		List assets = new ArrayList();

		Hits hits = search(companyId, portletId, keywords);

		hits = hits.subset(begin, end);

		List hitsList = hits.toList();

		for (int i = 0; i < hitsList.size(); i++) {
			Document doc = (Document)hitsList.get(i);

			try {
				TagsAsset asset = getAsset(doc);

				if (asset != null) {
					assets.add(asset);
				}
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(e);
				}
			}
		}

		return getAssetDisplays(assets, languageId);
	}

	public int searchAssetDisplaysCount(
			long companyId, String portletId, String keywords,
			String languageId)
		throws SystemException {

		Hits hits = search(companyId, portletId, keywords);

		return hits.getLength();
	}

	public TagsAsset updateAsset(
			long userId, long groupId, String className, long classPK,
			String[] entryNames)
		throws PortalException, SystemException {

		return updateAsset(
			userId, groupId, className, classPK, entryNames, null, null, null,
			null, null, null, null, null, null, 0, 0, null);
	}

	public TagsAsset updateAsset(
			long userId, long groupId, String className, long classPK,
			String[] entryNames, Date startDate, Date endDate, Date publishDate,
			Date expirationDate, String mimeType, String title,
			String description, String summary, String url, int height,
			int width, Integer priority)
		throws PortalException, SystemException {

		return updateAsset(
			userId, groupId, className, classPK, entryNames, startDate,
			endDate, publishDate, expirationDate, mimeType, title, description,
			summary, url, height, width, priority, true);
	}

	public TagsAsset updateAsset(
			long userId, long groupId, String className, long classPK,
			String[] entryNames, Date startDate, Date endDate, Date publishDate,
			Date expirationDate, String mimeType, String title,
			String description, String summary, String url, int height,
			int width, Integer priority, boolean sync)
		throws PortalException, SystemException {

		// Asset

		User user = userPersistence.findByPrimaryKey(userId);
		long classNameId = PortalUtil.getClassNameId(className);

		if (entryNames == null) {
			entryNames = new String[0];
		}

		title = StringUtil.shorten(title, 300, StringPool.BLANK);
		Date now = new Date();

		validate(className, entryNames);

		TagsAsset asset = tagsAssetPersistence.fetchByC_C(classNameId, classPK);

		if (asset == null) {
			long assetId = counterLocalService.increment();

			asset = tagsAssetPersistence.create(assetId);

			asset.setCompanyId(user.getCompanyId());
			asset.setUserId(user.getUserId());
			asset.setUserName(user.getFullName());
			asset.setCreateDate(now);
			asset.setClassNameId(classNameId);
			asset.setClassPK(classPK);
			asset.setPublishDate(publishDate);
			asset.setExpirationDate(expirationDate);

			if (priority == null) {
				asset.setPriority(0);
			}

			asset.setViewCount(0);
		}

		asset.setGroupId(groupId);
		asset.setModifiedDate(now);
		asset.setStartDate(startDate);
		asset.setEndDate(endDate);
		asset.setPublishDate(publishDate);
		asset.setExpirationDate(expirationDate);
		asset.setMimeType(mimeType);
		asset.setTitle(title);
		asset.setDescription(description);
		asset.setSummary(summary);
		asset.setUrl(url);
		asset.setHeight(height);
		asset.setWidth(width);

		if (priority != null) {
			asset.setPriority(priority.intValue());
		}

		tagsAssetPersistence.update(asset);

		// Entries

		List entries = new ArrayList(entryNames.length);

		for (int i = 0; i < entryNames.length; i++) {
			String name = entryNames[i].trim().toLowerCase();

			TagsEntry entry = tagsEntryPersistence.fetchByC_N(
				user.getCompanyId(), name);

			if (entry == null) {
				entry = tagsEntryLocalService.addEntry(
					user.getUserId(), entryNames[i],
					TagsEntryLocalServiceImpl.DEFAULT_PROPERTIES);
			}

			entries.add(entry);
		}

		tagsAssetPersistence.setTagsEntries(asset.getAssetId(), entries);

		// Synchronize

		if (!sync) {
			return asset;
		}

		if (className.equals(BlogsEntry.class.getName())) {
			BlogsEntry entry = blogsEntryPersistence.findByPrimaryKey(classPK);

			entry.setTitle(title);

			blogsEntryPersistence.update(entry);
		}
		else if (className.equals(BookmarksEntry.class.getName())) {
			BookmarksEntry entry = bookmarksEntryPersistence.findByPrimaryKey(
				classPK);

			entry.setName(title);
			entry.setComments(description);
			entry.setUrl(url);

			bookmarksEntryPersistence.update(entry);
		}
		else if (className.equals(DLFileEntry.class.getName())) {
			DLFileEntry fileEntry = dlFileEntryPersistence.findByPrimaryKey(
				classPK);

			fileEntry.setTitle(title);
			fileEntry.setDescription(description);

			dlFileEntryPersistence.update(fileEntry);
		}
		else if (className.equals(JournalArticle.class.getName())) {
			JournalArticle article = journalArticlePersistence.findByPrimaryKey(
				classPK);

			article.setTitle(title);
			article.setDescription(description);

			journalArticlePersistence.update(article);
		}
		else if (className.equals(MBMessage.class.getName())) {
			MBMessage message = mbMessagePersistence.findByPrimaryKey(classPK);

			message.setSubject(title);

			mbMessagePersistence.update(message);
		}
		else if (className.equals(WikiPage.class.getName())) {
			WikiPage page = wikiPagePersistence.findByPrimaryKey(classPK);

			page.setTitle(title);

			wikiPagePersistence.update(page);
		}

		return asset;
	}

	public void validate(String className, String[] entryNames)
		throws PortalException {

		TagsAssetValidator validator = (TagsAssetValidator)InstancePool.get(
			PropsValues.TAGS_ASSET_VALIDATOR);

		validator.validate(className, entryNames);
	}

	protected TagsAsset getAsset(Document doc)
		throws PortalException, SystemException {

		String portletId = GetterUtil.getString(
			doc.get(LuceneFields.PORTLET_ID));

		if (portletId.equals(PortletKeys.BLOGS)) {
			long entryId = GetterUtil.getLong(doc.get("entryId"));

			long classNameId = PortalUtil.getClassNameId(
				BlogsEntry.class.getName());
			long classPK = entryId;

			return tagsAssetPersistence.findByC_C(classNameId, classPK);
		}
		else if (portletId.equals(PortletKeys.BOOKMARKS)) {
			long entryId = GetterUtil.getLong(doc.get("entryId"));

			long classNameId = PortalUtil.getClassNameId(
				BookmarksEntry.class.getName());
			long classPK = entryId;

			return tagsAssetPersistence.findByC_C(classNameId, classPK);
		}
		else if (portletId.equals(PortletKeys.DOCUMENT_LIBRARY)) {
			long folderId = GetterUtil.getLong(doc.get("repositoryId"));
			String name = doc.get("path");

			DLFileEntry fileEntry = dlFileEntryLocalService.getFileEntry(
				folderId, name);

			long classNameId = PortalUtil.getClassNameId(
				DLFileEntry.class.getName());
			long classPK = fileEntry.getFileEntryId();

			return tagsAssetPersistence.findByC_C(classNameId, classPK);
		}
		else if (portletId.equals(PortletKeys.IMAGE_GALLERY)) {
			long imageId = GetterUtil.getLong(doc.get("imageId"));

			long classNameId = PortalUtil.getClassNameId(
				IGImage.class.getName());
			long classPK = imageId;

			return tagsAssetPersistence.findByC_C(classNameId, classPK);
		}
		else if (portletId.equals(PortletKeys.JOURNAL)) {
			long groupId = GetterUtil.getLong(
				doc.get(LuceneFields.GROUP_ID));
			String articleId = doc.get("articleId");
			//double version = GetterUtil.getDouble(doc.get("version"));

			long articleResourcePrimKey =
				journalArticleResourceLocalService.getArticleResourcePrimKey(
					groupId, articleId);

			long classNameId = PortalUtil.getClassNameId(
				JournalArticle.class.getName());
			long classPK = articleResourcePrimKey;

			return tagsAssetPersistence.findByC_C(classNameId, classPK);
		}
		else if (portletId.equals(PortletKeys.MESSAGE_BOARDS)) {
			long messageId = GetterUtil.getLong(doc.get("messageId"));

			long classNameId = PortalUtil.getClassNameId(
				MBMessage.class.getName());
			long classPK = messageId;

			return tagsAssetPersistence.findByC_C(classNameId, classPK);
		}
		else if (portletId.equals(PortletKeys.WIKI)) {
			long nodeId = GetterUtil.getLong(doc.get("nodeId"));
			String title = doc.get(LuceneFields.TITLE);

			long pageResourcePrimKey =
				wikiPageResourceLocalService.getPageResourcePrimKey(
					nodeId, title);

			long classNameId = PortalUtil.getClassNameId(
				WikiPage.class.getName());
			long classPK = pageResourcePrimKey;

			return tagsAssetPersistence.findByC_C(classNameId, classPK);
		}

		return null;
	}

	protected TagsAssetDisplay[] getAssetDisplays(
			List assets, String languageId)
		throws PortalException, SystemException {

		TagsAssetDisplay[] assetDisplays = new TagsAssetDisplay[assets.size()];

		for (int i = 0; i < assets.size(); i++) {
			TagsAsset asset = (TagsAsset)assets.get(i);

			String className = PortalUtil.getClassName(asset.getClassNameId());
			String portletId = PortalUtil.getClassNamePortletId(className);
			String portletTitle = PortalUtil.getPortletTitle(
				portletId, asset.getCompanyId(), languageId);

			List tagsEntriesList = tagsAssetPersistence.getTagsEntries(
				asset.getAssetId());

			String tagsEntries = ListUtil.toString(
				tagsEntriesList, "name", ", ");

			TagsAssetDisplay assetDisplay = new TagsAssetDisplay();

			assetDisplay.setAssetId(asset.getAssetId());
			assetDisplay.setCompanyId(asset.getCompanyId());
			assetDisplay.setUserId(asset.getUserId());
			assetDisplay.setUserName(asset.getUserName());
			assetDisplay.setCreateDate(asset.getCreateDate());
			assetDisplay.setModifiedDate(asset.getModifiedDate());
			assetDisplay.setClassNameId(asset.getClassNameId());
			assetDisplay.setClassName(className);
			assetDisplay.setClassPK(asset.getClassPK());
			assetDisplay.setPortletId(portletId);
			assetDisplay.setPortletTitle(portletTitle);
			assetDisplay.setStartDate(asset.getStartDate());
			assetDisplay.setEndDate(asset.getEndDate());
			assetDisplay.setPublishDate(asset.getPublishDate());
			assetDisplay.setExpirationDate(asset.getExpirationDate());
			assetDisplay.setMimeType(asset.getMimeType());
			assetDisplay.setTitle(asset.getTitle());
			assetDisplay.setDescription(asset.getDescription());
			assetDisplay.setSummary(asset.getSummary());
			assetDisplay.setUrl(asset.getUrl());
			assetDisplay.setHeight(asset.getHeight());
			assetDisplay.setWidth(asset.getWidth());
			assetDisplay.setPriority(asset.getPriority());
			assetDisplay.setViewCount(asset.getViewCount());
			assetDisplay.setTagsEntries(tagsEntries);

			assetDisplays[i] = assetDisplay;
		}

		return assetDisplays;
	}

	protected TagsAssetType getAssetType(String className, String languageId) {
		long companyId = PortalInstances.getDefaultCompanyId();

		long classNameId = PortalUtil.getClassNameId(className);

		String portletId = PortalUtil.getClassNamePortletId(className);
		String portletTitle = PortalUtil.getPortletTitle(
			portletId, companyId, languageId);

		TagsAssetType assetType = new TagsAssetType();

		assetType.setClassNameId(classNameId);
		assetType.setClassName(className);
		assetType.setPortletId(portletId);
		assetType.setPortletTitle(portletTitle);

		return assetType;
	}

	private static Log _log =
		LogFactory.getLog(TagsAssetLocalServiceImpl.class);

}