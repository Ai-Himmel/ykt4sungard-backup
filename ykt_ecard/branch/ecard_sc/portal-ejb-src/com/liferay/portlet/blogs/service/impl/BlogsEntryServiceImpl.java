/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.blogs.EntryContentException;
import com.liferay.portlet.blogs.EntryDisplayDateException;
import com.liferay.portlet.blogs.EntryTitleException;
import com.liferay.portlet.blogs.NoSuchCategoryException;
import com.liferay.portlet.blogs.NoSuchEntryException;
import com.liferay.portlet.blogs.model.BlogsCategory;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.model.BlogsProps;
import com.liferay.portlet.blogs.service.persistence.BlogsCategoryUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsCommentsUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsPropsUtil;
import com.liferay.portlet.blogs.service.spring.BlogsEntryLocalServiceUtil;
import com.liferay.portlet.blogs.service.spring.BlogsEntryService;
import com.liferay.portlet.blogs.service.spring.BlogsUserLocalServiceUtil;
import com.liferay.portlet.blogs.util.Indexer;
import com.liferay.util.Html;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.cal.CalendarUtil;
import com.liferay.util.lucene.Hits;

import de.nava.informa.core.ChannelExporterIF;
import de.nava.informa.core.ChannelIF;
import de.nava.informa.core.ItemIF;
import de.nava.informa.exporters.RSS_0_91_Exporter;
import de.nava.informa.exporters.RSS_1_0_Exporter;
import de.nava.informa.exporters.RSS_2_0_Exporter;
import de.nava.informa.impl.basic.ChannelBuilder;

import java.io.IOException;
import java.io.StringWriter;

import java.net.URL;

import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.analysis.WhitespaceAnalyzer;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.TermQuery;

/**
 * <a href="BlogsEntryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class BlogsEntryServiceImpl
	extends PrincipalBean implements BlogsEntryService {

	// Business methods

	public BlogsEntry addEntry(
			String categoryId, String title, String content, int displayMonth,
			int displayDay, int displayYear, int displayHour, int displayMinute,
			boolean sharing, boolean commentable)
		throws PortalException, SystemException {

		categoryId = _getCategoryId(categoryId);

		_validate(title, content);

		User user = getUser();

		String entryId = Long.toString(CounterServiceUtil.increment(
			BlogsEntry.class.getName()));

		BlogsEntry entry = BlogsEntryUtil.create(entryId);

		Date now = new Date();

		Date displayDate = PortalUtil.getDate(
			displayMonth, displayDay, displayYear, displayHour, displayMinute,
			user.getTimeZone(), new EntryDisplayDateException());

		entry.setCompanyId(user.getCompanyId());
		entry.setUserId(user.getUserId());
		entry.setCreateDate(now);
		entry.setModifiedDate(now);
		entry.setCategoryId(categoryId);
		entry.setTitle(title);
		entry.setContent(content);
		entry.setDisplayDate(displayDate);
		entry.setSharing(sharing);
		entry.setCommentable(commentable);

		BlogsEntryUtil.update(entry);

		// Update blogs user

		BlogsUserLocalServiceUtil.updateUser(
			user.getUserId(), user.getCompanyId(), entry.getEntryId());

		// Update lucene

		try {
			Indexer.addEntry(
				entry.getCompanyId(), entry.getPortletId(), entry.getGroupId(),
				entry.getUserId(), entry.getEntryId(), entry.getTitle(),
				entry.getContent());
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		return entry;
	}

	public void deleteEntry(String entryId)
		throws PortalException, SystemException {

		BlogsEntry entry = BlogsEntryUtil.findByPrimaryKey(entryId);

		deleteEntry(entry);
	}

	public void deleteEntry(BlogsEntry entry)
		throws PortalException, SystemException {

		if (!entry.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		BlogsEntryLocalServiceUtil.deleteEntry(entry.getEntryId());
	}

	public BlogsEntry getEntry(String entryId)
		throws PortalException, SystemException {

		BlogsEntry entry = BlogsEntryUtil.findByPrimaryKey(entryId);

		if (!entry.isSharing() && !entry.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		return entry;
	}

	public List getEntries(String userId, int begin, int end)
		throws SystemException {

		return getEntries(userId, null, begin, end);
	}

	public List getEntries(String userId, String categoryId, int begin, int end)
		throws SystemException {

		if (Validator.isNull(categoryId)) {
			return BlogsEntryUtil.findByU_S(userId, true, begin, end);
		}
		else {
			return BlogsEntryUtil.findByU_C_S(
				userId, categoryId, true, begin, end);
		}
	}

	public List getEntries(String userId, Calendar cal) throws SystemException {
		return getEntries(userId, null, cal);
	}

	public List getEntries(String userId, String categoryId, Calendar cal)
		throws SystemException {

		Boolean sharing = _getSharing(userId);
		Date gtDate = CalendarUtil.getGTDate(cal);
		Date ltDate = CalendarUtil.getLTDate(cal);

		if (Validator.isNull(categoryId)) {
			return BlogsEntryFinder.findByU_S_DD(
				userId, sharing, gtDate, ltDate);
		}
		else {
			return BlogsEntryFinder.findByU_C_S_DD(
				userId, categoryId, sharing, gtDate, ltDate);
		}
	}

	public int getEntriesSize(String userId, Calendar cal)
		throws SystemException {

		return getEntriesSize(userId, null, cal);
	}

	public int getEntriesSize(String userId, String categoryId, Calendar cal)
		throws SystemException {

		Boolean sharing = _getSharing(userId);
		Date gtDate = CalendarUtil.getGTDate(cal);
		Date ltDate = CalendarUtil.getLTDate(cal);

		if (Validator.isNull(categoryId)) {
			return BlogsEntryFinder.countByU_S_DD(
				userId, sharing, gtDate, ltDate);
		}
		else {
			return BlogsEntryFinder.countByU_C_S_DD(
				userId, categoryId, sharing, gtDate, ltDate);
		}
	}

	public String getEntriesXML(
			String userId, String categoryId, String type, int begin, int end,
			String findEntryUrl)
		throws PortalException, SystemException {

		User user = UserLocalServiceUtil.getUserById(userId);

		ChannelBuilder builder = new ChannelBuilder();

		ChannelIF channel = builder.createChannel(user.getFullName());

		channel.setDescription(user.getFullName());

		Iterator itr = getEntries(userId, categoryId, begin, end).iterator();

		while (itr.hasNext()) {
			BlogsEntry entry = (BlogsEntry)itr.next();

			try {
				String firstLine =
					StringUtil.shorten(
						Html.stripHtml(entry.getContent()), 80,
						StringPool.BLANK);

				URL url = new URL(
					findEntryUrl + "&blogs_user_id=" + userId + "&entry_id=" +
						entry.getEntryId());

				ItemIF item = builder.createItem(
					channel, entry.getTitle(), firstLine, url);
			}
			catch (IOException ioe) {
				throw new SystemException(ioe);
			}
		}

		StringWriter writer = new StringWriter();

		try {
			ChannelExporterIF exporter = null;

			String charEncoding = "UTF-8";

			if ((type != null) && (type.equals("rss1.0"))) {
				exporter = new RSS_1_0_Exporter(writer, charEncoding);
			}
			else if ((type != null) && (type.equals("rss0.91"))) {
				exporter = new RSS_0_91_Exporter(writer, charEncoding);
			}
			else {
				exporter = new RSS_2_0_Exporter(writer, charEncoding);
			}

			exporter.write(channel);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}

		return writer.getBuffer().toString();
	}

	public BlogsEntry getLatestEntry(String userId)
		throws PortalException, SystemException {

		List entries = null;

		Boolean sharing = _getSharing(userId);

		if (sharing == null) {
			entries = BlogsEntryUtil.findByUserId(userId, 0, 1);
		}
		else {
			entries = BlogsEntryUtil.findByU_S(
				userId, sharing.booleanValue(), 0, 1);
		}

		if (entries.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (BlogsEntry)entries.get(0);
		}
	}

	public BlogsEntry getLatestEntry(String userId, String categoryId)
		throws PortalException, SystemException {

		List entries = null;

		Boolean sharing = _getSharing(userId);

		if (sharing == null) {
			entries = BlogsEntryUtil.findByU_C(userId, categoryId, 0, 1);
		}
		else {
			entries = BlogsEntryUtil.findByU_C_S(
				userId, categoryId, sharing.booleanValue(), 0, 1);
		}

		if (entries.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (BlogsEntry)entries.get(0);
		}
	}

	public boolean hasEntries(String userId, Calendar cal)
		throws SystemException {

		return hasEntries(userId, null, cal);
	}

	public boolean hasEntries(String userId, String categoryId, Calendar cal)
		throws SystemException {

		int entriesSize = getEntriesSize(userId, categoryId, cal);

		if (entriesSize > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void reIndex(String[] ids) throws SystemException {
		try {
			String companyId = ids[0];

			Iterator itr = BlogsEntryUtil.findByCompanyId(companyId).iterator();

			while (itr.hasNext()) {
				BlogsEntry entry = (BlogsEntry)itr.next();

				String portletId = entry.getPortletId();
				String groupId = entry.getGroupId();
				String blogsUserId = entry.getUserId();
				String entryId = entry.getEntryId();
				String title = entry.getTitle();
				String content = entry.getContent();

				try {
					Indexer.addEntry(
						companyId, portletId, groupId, blogsUserId, entryId,
						title, content);
				}
				catch (Exception e1) {

					// Continue indexing even if one entry fails

					_log.error(e1.getMessage());
				}
			}
		}
		catch (SystemException se) {
			throw se;
		}
		catch (Exception e2) {
			throw new SystemException(e2);
		}
	}

	public Hits search(
			String companyId, String portletId, String groupId,
			String[] blogsUserIds, String keywords)
		throws SystemException {

		try {
			Hits hits = new Hits();

			if (Validator.isNull(keywords)) {
				return hits;
			}

			BooleanQuery booleanQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.PORTLET_ID, portletId);
			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.GROUP_ID, groupId);

			LuceneUtil.addTerm(booleanQuery, LuceneFields.TITLE, keywords);
			LuceneUtil.addTerm(booleanQuery, LuceneFields.CONTENT, keywords);

			if ((blogsUserIds != null) && (blogsUserIds.length > 0)) {
				BooleanQuery blogsUserIdsQuery = new BooleanQuery();

				for (int i = 0; i < blogsUserIds.length; i++) {
					blogsUserIdsQuery.add(new TermQuery(new Term(
						"blogsUserId", blogsUserIds[i])), false, false);
				}

				booleanQuery.add(blogsUserIdsQuery, true, false);
			}

			Searcher searcher = LuceneUtil.getSearcher(companyId);

			Query query = QueryParser.parse(
				booleanQuery.toString(), LuceneFields.CONTENT,
				new WhitespaceAnalyzer());

			hits.recordHits(searcher.search(query));

			return hits;
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (ParseException pe) {
			throw new SystemException(pe);
		}
	}

	public BlogsEntry updateEntry(
			String entryId, String categoryId, String title, String content,
			int displayMonth, int displayDay, int displayYear, int displayHour,
			int displayMinute, boolean sharing, boolean commentable)
		throws PortalException, SystemException {

		categoryId = _getCategoryId(categoryId);

		_validate(title, content);

		User user = getUser();

		BlogsEntry entry = BlogsEntryUtil.findByPrimaryKey(entryId);

		if (!entry.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		Date displayDate = PortalUtil.getDate(
			displayMonth, displayDay, displayYear, displayHour, displayMinute,
			user.getTimeZone(), new EntryDisplayDateException());

		entry.setModifiedDate(new Date());
		entry.setCategoryId(categoryId);
		entry.setTitle(title);
		entry.setContent(content);
		entry.setDisplayDate(displayDate);
		entry.setSharing(sharing);
		entry.setCommentable(commentable);

		BlogsEntryUtil.update(entry);

		// Update blogs user

		BlogsUserLocalServiceUtil.updateUser(
			user.getUserId(), user.getCompanyId(), entry.getEntryId());

		// Update lucene

		try {
			Indexer.updateEntry(
				entry.getCompanyId(), entry.getPortletId(), entry.getGroupId(),
				entry.getUserId(), entry.getEntryId(), entry.getTitle(),
				entry.getContent());
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		return entry;
	}

	public BlogsEntry updateSharing(String entryId)
		throws PortalException, SystemException {

		BlogsEntry entry = BlogsEntryUtil.findByPrimaryKey(entryId);

		if (!entry.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		entry.setSharing(!entry.isSharing());

		BlogsEntryUtil.update(entry);

		return entry;
	}

	public BlogsEntry updatePropsCount(String entryId)
		throws PortalException, SystemException {

		BlogsEntry entry = BlogsEntryUtil.findByPrimaryKey(entryId);

		entry.setPropsCount(_getPropsCount(entryId));

		BlogsEntryUtil.update(entry);

		return entry;
	}

	public BlogsEntry updateCommentsCount(String entryId)
		throws PortalException, SystemException {

		BlogsEntry entry = BlogsEntryUtil.findByPrimaryKey(entryId);

		entry.setCommentsCount(BlogsCommentsUtil.countByEntryId(entryId));

		BlogsEntryUtil.update(entry);

		return entry;
	}

	// Private methods

	private String _getCategoryId(String categoryId)
		throws PortalException, SystemException {

		if (!categoryId.equals(BlogsCategory.DEFAULT_PARENT_CATEGORY_ID)) {

			// Ensure category exists and belongs to the proper user

			try {
				BlogsCategory category =
					BlogsCategoryUtil.findByPrimaryKey(categoryId);

				if (!category.getUserId().equals(getUserId())) {
					categoryId = BlogsCategory.DEFAULT_PARENT_CATEGORY_ID;
				}
			}
			catch (NoSuchCategoryException nsfe) {
				categoryId = BlogsCategory.DEFAULT_PARENT_CATEGORY_ID;
			}
		}

		return categoryId;
	}

	private int _getPropsCount(String entryId) throws SystemException {
		int propsCount = 0;

		Iterator itr = BlogsPropsUtil.findByEntryId(entryId).iterator();

		while (itr.hasNext()) {
			BlogsProps blogsProps = (BlogsProps)itr.next();

			propsCount += blogsProps.getQuantity();
		}

		return propsCount;
	}

	private Boolean _getSharing(String userId) {
		Boolean sharing = Boolean.TRUE;

		try {
			if (getUserId().equals(userId)) {
				sharing = null;
			}
		}
		catch (PrincipalException pe) {
		}

		return sharing;
	}

	private void _validate(String title, String content)
		throws PortalException {

		if (Validator.isNull(title)) {
			throw new EntryTitleException();
		}
		else if (Validator.isNull(content)) {
			throw new EntryContentException();
		}
	}

	private static final Log _log =
		LogFactory.getLog(BlogsEntryServiceImpl.class);

}