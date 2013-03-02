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

package com.liferay.portlet.blogs.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.blogs.EntryContentException;
import com.liferay.portlet.blogs.EntryDisplayDateException;
import com.liferay.portlet.blogs.EntryTitleException;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.model.BlogsStatsUser;
import com.liferay.portlet.blogs.service.base.BlogsEntryLocalServiceBaseImpl;
import com.liferay.portlet.blogs.util.Indexer;
import com.liferay.util.Http;
import com.liferay.util.HttpUtil;
import com.liferay.util.Normalizer;
import com.liferay.util.lucene.HitsImpl;

import java.io.IOException;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Searcher;

/**
 * <a href="BlogsEntryLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 * @author Wilson S. Man
 *
 */
public class BlogsEntryLocalServiceImpl extends BlogsEntryLocalServiceBaseImpl {

	public BlogsEntry addEntry(
			long userId, long plid, String title, String content,
			int displayDateMonth, int displayDateDay, int displayDateYear,
			int displayDateHour, int displayDateMinute, String[] tagsEntries,
			boolean addCommunityPermissions, boolean addGuestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		return addEntry(
			null, userId, plid, title, content, displayDateMonth,
			displayDateDay, displayDateYear, displayDateHour, displayDateMinute,
			tagsEntries, Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null, themeDisplay);
	}

	public BlogsEntry addEntry(
			String uuid, long userId, long plid, String title, String content,
			int displayDateMonth, int displayDateDay, int displayDateYear,
			int displayDateHour, int displayDateMinute, String[] tagsEntries,
			boolean addCommunityPermissions, boolean addGuestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		return addEntry(
			uuid, userId, plid, title, content, displayDateMonth,
			displayDateDay, displayDateYear, displayDateHour, displayDateMinute,
			tagsEntries, Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null, themeDisplay);
	}

	public BlogsEntry addEntry(
			long userId, long plid, String title, String content,
			int displayDateMonth, int displayDateDay, int displayDateYear,
			int displayDateHour, int displayDateMinute, String[] tagsEntries,
			String[] communityPermissions, String[] guestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		return addEntry(
			null, userId, plid, title, content, displayDateMonth,
			displayDateDay, displayDateYear, displayDateHour, displayDateMinute,
			tagsEntries, null, null, communityPermissions, guestPermissions,
			themeDisplay);
	}

	public BlogsEntry addEntry(
			String uuid, long userId, long plid, String title, String content,
			int displayDateMonth, int displayDateDay, int displayDateYear,
			int displayDateHour, int displayDateMinute, String[] tagsEntries,
			Boolean addCommunityPermissions, Boolean addGuestPermissions,
			String[] communityPermissions, String[] guestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		// Entry

		User user = userPersistence.findByPrimaryKey(userId);
		long groupId = PortalUtil.getPortletGroupId(plid);
		Date now = new Date();

		Date displayDate = PortalUtil.getDate(
			displayDateMonth, displayDateDay, displayDateYear, displayDateHour,
			displayDateMinute, user.getTimeZone(),
			new EntryDisplayDateException());

		validate(title, content);

		long entryId = counterLocalService.increment();

		BlogsEntry entry = blogsEntryPersistence.create(entryId);

		entry.setUuid(uuid);
		entry.setGroupId(groupId);
		entry.setCompanyId(user.getCompanyId());
		entry.setUserId(user.getUserId());
		entry.setUserName(user.getFullName());
		entry.setCreateDate(now);
		entry.setModifiedDate(now);
		entry.setTitle(title);
		entry.setUrlTitle(getUniqueUrlTitle(entryId, groupId, title));
		entry.setContent(content);
		entry.setDisplayDate(displayDate);

		blogsEntryPersistence.update(entry);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addEntryResources(
				entry, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addEntryResources(entry, communityPermissions, guestPermissions);
		}

		// Statistics

		blogsStatsUserLocalService.updateStatsUser(
			entry.getGroupId(), userId, now);

		// Tags

		updateTagsAsset(userId, entry, tagsEntries);

		// Lucene

		try {
			Indexer.addEntry(
				entry.getCompanyId(), entry.getGroupId(), userId, entryId,
				title, content, tagsEntries);
		}
		catch (IOException ioe) {
			_log.error("Indexing " + entryId, ioe);
		}

		// Google

		pingGoogle(entry, themeDisplay);

		return entry;
	}

	public void addEntryResources(
			long entryId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		BlogsEntry entry = blogsEntryPersistence.findByPrimaryKey(entryId);

		addEntryResources(entry, addCommunityPermissions, addGuestPermissions);
	}

	public void addEntryResources(
			BlogsEntry entry, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			entry.getCompanyId(), entry.getGroupId(), entry.getUserId(),
			BlogsEntry.class.getName(), entry.getEntryId(), false,
			addCommunityPermissions, addGuestPermissions);
	}

	public void addEntryResources(
			long entryId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		BlogsEntry entry = blogsEntryPersistence.findByPrimaryKey(entryId);

		addEntryResources(entry, communityPermissions, guestPermissions);
	}

	public void addEntryResources(
			BlogsEntry entry, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			entry.getCompanyId(), entry.getGroupId(), entry.getUserId(),
			BlogsEntry.class.getName(), entry.getEntryId(),
			communityPermissions, guestPermissions);
	}

	public void deleteEntries(long groupId)
		throws PortalException, SystemException {

		Iterator itr = blogsEntryPersistence.findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			BlogsEntry entry = (BlogsEntry)itr.next();

			deleteEntry(entry);
		}
	}

	public void deleteEntry(long entryId)
		throws PortalException, SystemException {

		BlogsEntry entry = blogsEntryPersistence.findByPrimaryKey(entryId);

		deleteEntry(entry);
	}

	public void deleteEntry(BlogsEntry entry)
		throws PortalException, SystemException {

		// Lucene

		try {
			Indexer.deleteEntry(entry.getCompanyId(), entry.getEntryId());
		}
		catch (IOException ioe) {
			_log.error("Deleting index " + entry.getEntryId(), ioe);
		}

		// Tags

		tagsAssetLocalService.deleteAsset(
			BlogsEntry.class.getName(), entry.getEntryId());

		// Ratings

		ratingsStatsLocalService.deleteStats(
			BlogsEntry.class.getName(), entry.getEntryId());

		// Message boards

		mbMessageLocalService.deleteDiscussionMessages(
			BlogsEntry.class.getName(), entry.getEntryId());

		// Resources

		resourceLocalService.deleteResource(
			entry.getCompanyId(), BlogsEntry.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, entry.getEntryId());

		// Entry

		blogsEntryPersistence.remove(entry.getEntryId());
	}

	public List getCompanyEntries(long companyId, int begin, int end)
		throws SystemException {

		return blogsEntryPersistence.findByCompanyId(companyId, begin, end);
	}

	public List getCompanyEntries(
			long companyId, int begin, int end, OrderByComparator obc)
		throws SystemException {

		return blogsEntryPersistence.findByCompanyId(
			companyId, begin, end, obc);
	}

	public int getCompanyEntriesCount(long companyId) throws SystemException {
		return blogsEntryPersistence.countByCompanyId(companyId);
	}

	public BlogsEntry getEntry(long entryId)
		throws PortalException, SystemException {

		return blogsEntryPersistence.findByPrimaryKey(entryId);
	}

	public BlogsEntry getEntry(long groupId, String urlTitle)
		throws PortalException, SystemException {

		return blogsEntryPersistence.findByG_UT(groupId, urlTitle);
	}

	public List getGroupEntries(long groupId, int begin, int end)
		throws SystemException {

		return blogsEntryPersistence.findByGroupId(groupId, begin, end);
	}

	public List getGroupEntries(
			long groupId, int begin, int end, OrderByComparator obc)
		throws SystemException {

		return blogsEntryPersistence.findByGroupId(groupId, begin, end, obc);
	}

	public int getGroupEntriesCount(long groupId) throws SystemException {
		return blogsEntryPersistence.countByGroupId(groupId);
	}

	public List getGroupUserEntries(
			long groupId, long userId, int begin, int end)
		throws SystemException {

		return blogsEntryPersistence.findByG_U(groupId, userId, begin, end);
	}

	public int getGroupUserEntriesCount(long groupId, long userId)
		throws SystemException {

		return blogsEntryPersistence.countByG_U(groupId, userId);
	}

	public List getNoAssetEntries() throws SystemException {
		return blogsEntryFinder.findByNoAssets();
	}

	public List getOrganizationEntries(long organizationId, int begin, int end)
		throws SystemException {

		return blogsEntryFinder.findByOrganizationId(
			organizationId, begin, end);
	}

	public int getOrganizationEntriesCount(long organizationId)
		throws SystemException {

		return blogsEntryFinder.countByOrganizationId(
			organizationId);
	}

	public String getUrlTitle(long entryId, String title) {
		String urlTitle = String.valueOf(entryId);

		title = title.trim().toLowerCase();

		if (Validator.isNull(title) || Validator.isNumber(title) ||
			title.equals("rss")) {

			return urlTitle;
		}

		title = Normalizer.normalizeToAscii(title);

		char[] urlTitleCharArray = title.toCharArray();

		for (int i = 0; i < urlTitleCharArray.length; i++) {
			char oldChar = urlTitleCharArray[i];

			char newChar = oldChar;

			if ((oldChar == '_') || (Validator.isChar(oldChar)) ||
				(Validator.isDigit(oldChar))) {

			}
			else if (ArrayUtil.contains(_URL_TITLE_REPLACE_CHARS, oldChar)) {
				newChar = '_';
			}
			else {
				return urlTitle;
			}

			if (oldChar != newChar) {
				urlTitleCharArray[i] = newChar;
			}
		}

		urlTitle = new String(urlTitleCharArray);

		return urlTitle;
	}

	public void reIndex(String[] ids) throws SystemException {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		long companyId = GetterUtil.getLong(ids[0]);

		IndexWriter writer = null;

		try {
			writer = LuceneUtil.getWriter(companyId);

			Iterator itr = blogsEntryPersistence.findByCompanyId(
				companyId).iterator();

			while (itr.hasNext()) {
				BlogsEntry entry = (BlogsEntry)itr.next();

				long groupId = entry.getGroupId();
				long userId = entry.getUserId();
				long entryId = entry.getEntryId();
				String title = entry.getTitle();
				String content = entry.getContent();

				String[] tagsEntries = tagsEntryLocalService.getEntryNames(
					BlogsEntry.class.getName(), entryId);

				try {
					Document doc = Indexer.getAddEntryDocument(
						companyId, groupId, userId, entryId, title, content,
						tagsEntries);

					writer.addDocument(doc);
				}
				catch (Exception e1) {
					_log.error("Reindexing " + entryId, e1);
				}
			}
		}
		catch (SystemException se) {
			throw se;
		}
		catch (Exception e2) {
			throw new SystemException(e2);
		}
		finally {
			try {
				if (writer != null) {
					LuceneUtil.write(companyId);
				}
			}
			catch (Exception e) {
				_log.error(e);
			}
		}
	}

	public Hits search(
			long companyId, long groupId, long userId, String keywords)
		throws SystemException {

		Searcher searcher = null;

		try {
			HitsImpl hits = new HitsImpl();

			BooleanQuery contextQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				contextQuery, LuceneFields.PORTLET_ID, Indexer.PORTLET_ID);

			if (groupId > 0) {
				LuceneUtil.addRequiredTerm(
					contextQuery, LuceneFields.GROUP_ID, groupId);
			}

			if (userId > 0) {
				LuceneUtil.addRequiredTerm(
					contextQuery, LuceneFields.USER_ID, userId);
			}

			BooleanQuery searchQuery = new BooleanQuery();

			if (Validator.isNotNull(keywords)) {
				LuceneUtil.addTerm(searchQuery, LuceneFields.TITLE, keywords);
				LuceneUtil.addTerm(searchQuery, LuceneFields.CONTENT, keywords);
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

	public BlogsEntry updateEntry(
			long userId, long entryId, String title, String content,
			int displayDateMonth, int displayDateDay, int displayDateYear,
			int displayDateHour, int displayDateMinute, String[] tagsEntries,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		// Entry

		User user = userPersistence.findByPrimaryKey(userId);
		Date now = new Date();

		Date displayDate = PortalUtil.getDate(
			displayDateMonth, displayDateDay, displayDateYear, displayDateHour,
			displayDateMinute, user.getTimeZone(),
			new EntryDisplayDateException());

		validate(title, content);

		BlogsEntry entry = blogsEntryPersistence.findByPrimaryKey(entryId);

		entry.setModifiedDate(now);
		entry.setTitle(title);
		entry.setUrlTitle(
			getUniqueUrlTitle(entryId, entry.getGroupId(), title));
		entry.setContent(content);
		entry.setDisplayDate(displayDate);

		blogsEntryPersistence.update(entry);

		// Statistics

		BlogsStatsUser statsUser = blogsStatsUserPersistence.fetchByG_U(
			entry.getGroupId(), entry.getUserId());

		if (statsUser != null) {
			statsUser.setLastPostDate(now);

			blogsStatsUserPersistence.update(statsUser);
		}

		// Tags

		updateTagsAsset(userId, entry, tagsEntries);

		// Lucene

		try {
			Indexer.updateEntry(
				entry.getCompanyId(), entry.getGroupId(), userId, entryId,
				title, content, tagsEntries);
		}
		catch (IOException ioe) {
			_log.error("Indexing " + entryId, ioe);
		}

		// Google

		pingGoogle(entry, themeDisplay);

		return entry;
	}

	public void updateTagsAsset(
			long userId, BlogsEntry entry, String[] tagsEntries)
		throws PortalException, SystemException {

		tagsAssetLocalService.updateAsset(
			userId, entry.getGroupId(), BlogsEntry.class.getName(),
			entry.getEntryId(), tagsEntries, null, null, null, null,
			ContentTypes.TEXT_HTML, entry.getTitle(), null, null, null, 0, 0,
			null, false);
	}

	protected String getUniqueUrlTitle(
			long entryId, long groupId, String title)
		throws SystemException {

		String urlTitle = getUrlTitle(entryId, title);

		String newUrlTitle = new String(urlTitle);

		for (int i = 1;; i++) {
			BlogsEntry entry = blogsEntryPersistence.fetchByG_UT(
				groupId, newUrlTitle);

			if ((entry == null) || (entry.getEntryId() == entryId)) {
				break;
			}
			else {
				newUrlTitle = urlTitle + "_" + i;
			}
		}

		return newUrlTitle;
	}

	protected void pingGoogle(BlogsEntry entry, ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		if (themeDisplay == null) {
			return;
		}

		Group group = groupPersistence.findByPrimaryKey(entry.getGroupId());

		String portalURL = PortalUtil.getPortalURL(themeDisplay);

		if ((portalURL.indexOf("://localhost") != -1) ||
			(portalURL.indexOf("://127.0.0.1") != -1)) {

			return;
		}

		String layoutURL = PortalUtil.getLayoutURL(themeDisplay);

		StringMaker sm = new StringMaker();

		String name = group.getDescriptiveName();
		//String url = portalURL + layoutURL + "/blogs/" + entry.getUrlTitle();
		String url = portalURL + layoutURL + "/blogs";
		String changesURL = portalURL + layoutURL + "/blogs/rss";

		sm.append("http://blogsearch.google.com/ping?name=");
		sm.append(HttpUtil.encodeURL(name));
		sm.append("&url=");
		sm.append(HttpUtil.encodeURL(url));
		sm.append("&changesURL=");
		sm.append(HttpUtil.encodeURL(changesURL));

		String location = sm.toString();

		if (_log.isInfoEnabled()) {
			_log.info("Pinging Google at " + location);
		}

		try {
			String response = Http.URLtoString(sm.toString());

			if (_log.isInfoEnabled()) {
				_log.info("Google ping response: " + response);
			}
		}
		catch (IOException ioe) {
			_log.error("Unable to ping Google at " + location, ioe);
		}
	}

	protected void validate(String title, String content)
		throws PortalException {

		if (Validator.isNull(title)) {
			throw new EntryTitleException();
		}
		else if (Validator.isNull(content)) {
			throw new EntryContentException();
		}
	}

	private static final char[] _URL_TITLE_REPLACE_CHARS = new char[] {
		' ',  '.',  '-',  ',',  '/',  '\\',  '\'',  '\"'
	};

	private static Log _log =
		LogFactory.getLog(BlogsEntryLocalServiceImpl.class);

}