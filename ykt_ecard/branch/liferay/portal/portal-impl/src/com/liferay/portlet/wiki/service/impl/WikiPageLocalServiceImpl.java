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

package com.liferay.portlet.wiki.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portlet.wiki.NoSuchPageException;
import com.liferay.portlet.wiki.PageContentException;
import com.liferay.portlet.wiki.PageTitleException;
import com.liferay.portlet.wiki.model.WikiNode;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.portlet.wiki.model.impl.WikiPageImpl;
import com.liferay.portlet.wiki.service.base.WikiPageLocalServiceBaseImpl;
import com.liferay.portlet.wiki.util.Indexer;
import com.liferay.portlet.wiki.util.NodeFilter;
import com.liferay.portlet.wiki.util.WikiUtil;
import com.liferay.portlet.wiki.util.comparator.PageCreateDateComparator;
import com.liferay.util.MathUtil;

import java.io.IOException;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="WikiPageLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WikiPageLocalServiceImpl extends WikiPageLocalServiceBaseImpl {

	public WikiPage addPage(long userId, long nodeId, String title)
		throws PortalException, SystemException {

		double version = WikiPageImpl.DEFAULT_VERSION;
		String content = null;
		String format = WikiPageImpl.DEFAULT_FORMAT;
		boolean head = true;
		String[] tagsEntries = null;

		return addPage(
			null, userId, nodeId, title, version, content, format, head,
			tagsEntries);
	}

	public WikiPage addPage(
			long userId, long nodeId, String title, double version,
			String content, String format, boolean head, String[] tagsEntries)
		throws PortalException, SystemException {

		return addPage(
			null, userId, nodeId, title, version, content, format, head,
			tagsEntries);
	}

	public WikiPage addPage(
			String uuid, long userId, long nodeId, String title, double version,
			String content, String format, boolean head, String[] tagsEntries)
		throws PortalException, SystemException {

		// Page

		User user = userPersistence.findByPrimaryKey(userId);
		WikiNode node = wikiNodePersistence.findByPrimaryKey(nodeId);

		Date now = new Date();

		validate(title, nodeId, content, format);

		long pageId = counterLocalService.increment();

		long resourcePrimKey =
			wikiPageResourceLocalService.getPageResourcePrimKey(nodeId, title);

		WikiPage page = wikiPagePersistence.create(pageId);

		page.setUuid(uuid);
		page.setResourcePrimKey(resourcePrimKey);
		page.setCompanyId(user.getCompanyId());
		page.setUserId(user.getUserId());
		page.setUserName(user.getFullName());
		page.setCreateDate(now);
		page.setNodeId(nodeId);
		page.setTitle(title);
		page.setVersion(version);
		page.setContent(content);
		page.setFormat(format);
		page.setHead(head);

		wikiPagePersistence.update(page);

		// Resources

		addPageResources(page.getNode(), page, true, true);

		// Tags

		updateTagsAsset(userId, page, tagsEntries);

		// Lucene

		try {
			Indexer.addPage(
				page.getCompanyId(), node.getGroupId(), nodeId, title,
				content, tagsEntries);
		}
		catch (IOException ioe) {
			_log.error("Indexing " + pageId, ioe);
		}

		return page;
	}

	public void addPageResources(
			long nodeId, String title, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		WikiNode node = wikiNodePersistence.findByPrimaryKey(nodeId);
		WikiPage page = getPage(nodeId, title);

		addPageResources(
			node, page, addCommunityPermissions, addGuestPermissions);
	}

	public void addPageResources(
			WikiNode node, WikiPage page, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			page.getCompanyId(), node.getGroupId(),	page.getUserId(),
			WikiPage.class.getName(), page.getResourcePrimKey(), false,
			addCommunityPermissions, addGuestPermissions);
	}

	public void addPageResources(
			long nodeId, String title, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		WikiNode node = wikiNodePersistence.findByPrimaryKey(nodeId);
		WikiPage page = getPage(nodeId, title);

		addPageResources(node, page, communityPermissions, guestPermissions);
	}

	public void addPageResources(
			WikiNode node, WikiPage page, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			page.getCompanyId(), node.getGroupId(),	page.getUserId(),
			WikiPage.class.getName(), page.getResourcePrimKey(),
			communityPermissions, guestPermissions);
	}

	public void deletePage(long nodeId, String title)
		throws PortalException, SystemException {

		List pages = wikiPagePersistence.findByN_T_H(nodeId, title, true, 0, 1);

		if (pages.size() > 0) {
			WikiPage page = (WikiPage)pages.iterator().next();

			deletePage(page);
		}
	}

	public void deletePage(WikiPage page)
		throws PortalException, SystemException {

		// Lucene

		try {
			Indexer.deletePage(
				page.getCompanyId(), page.getNodeId(), page.getTitle());
		}
		catch (IOException ioe) {
			_log.error("Deleting index " + page.getPrimaryKey(), ioe);
		}

		// Tags

		tagsAssetLocalService.deleteAsset(
			WikiPage.class.getName(), page.getResourcePrimKey());

		// Message boards

		mbMessageLocalService.deleteDiscussionMessages(
			WikiPage.class.getName(), page.getResourcePrimKey());

		// Resources

		resourceLocalService.deleteResource(
			page.getCompanyId(), WikiPage.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, page.getResourcePrimKey());

		// Resource

		wikiPageResourceLocalService.deletePageResource(
			page.getNodeId(), page.getTitle());

		// All versions

		wikiPagePersistence.removeByN_T(page.getNodeId(), page.getTitle());
	}

	public void deletePages(long nodeId)
		throws PortalException, SystemException {

		Iterator itr = wikiPagePersistence.findByN_H(nodeId, true).iterator();

		while (itr.hasNext()) {
			WikiPage page = (WikiPage)itr.next();

			deletePage(page);
		}
	}

	public List getNoAssetPages() throws SystemException {
		return wikiPageFinder.findByNoAssets();
	}

	public List getLinks(long nodeId, String title) throws SystemException {
		List links = new ArrayList();

		List pages = wikiPagePersistence.findByN_H(nodeId, true);

		for (int i = 0; i < pages.size(); i++) {
			WikiPage page = (WikiPage)pages.get(i);

			if (page.getFormat().equals(WikiPageImpl.CLASSIC_WIKI_FORMAT)) {
				NodeFilter filter = WikiUtil.getFilter(nodeId);

				try {
					WikiUtil.convert(filter, page.getContent());

					if (filter.getTitles().get(title) != null) {
						links.add(page);
					}
				}
				catch (IOException ioe) {
					ioe.printStackTrace();
				}
			}
		}

		Collections.sort(links);

		return links;
	}

	public List getOrphans(long nodeId) throws SystemException {
		List pageTitles = new ArrayList();

		List pages = wikiPagePersistence.findByN_H(nodeId, true);

		for (int i = 0; i < pages.size(); i++) {
			WikiPage page = (WikiPage)pages.get(i);

			if (page.getFormat().equals(WikiPageImpl.CLASSIC_WIKI_FORMAT)) {
				NodeFilter filter = WikiUtil.getFilter(nodeId);

				try {
					WikiUtil.convert(filter, page.getContent());

					pageTitles.add(filter.getTitles());
				}
				catch (IOException ioe) {
					ioe.printStackTrace();
				}
			}
		}

		Set notOrphans = new HashSet();

		for (int i = 0; i < pages.size(); i++) {
			WikiPage page = (WikiPage)pages.get(i);

			for (int j = 0; j < pageTitles.size(); j++) {
				Map titles = (Map)pageTitles.get(j);

				if (titles.get(page.getTitle()) != null) {
					notOrphans.add(page);

					break;
				}
			}
		}

		List orphans = new ArrayList();

		for (int i = 0; i < pages.size(); i++) {
			WikiPage page = (WikiPage)pages.get(i);

			if (!notOrphans.contains(page)) {
				orphans.add(page);
			}
		}

		Collections.sort(orphans);

		return orphans;
	}

	public WikiPage getPage(long nodeId, String title)
		throws PortalException, SystemException {

		List pages = wikiPagePersistence.findByN_T_H(nodeId, title, true, 0, 1);

		if (pages.size() > 0) {
			return (WikiPage)pages.iterator().next();
		}
		else {
			throw new NoSuchPageException();
		}
	}

	public WikiPage getPage(long nodeId, String title, double version)
		throws PortalException, SystemException {

		WikiPage page = null;

		if (version == 0) {
			page = getPage(nodeId, title);
		}
		else {
			page = wikiPagePersistence.findByN_T_V(nodeId, title, version);
		}

		return page;
	}

	public List getPages(long nodeId, int begin, int end)
		throws SystemException {

		return wikiPagePersistence.findByNodeId(
			nodeId, begin, end, new PageCreateDateComparator(false));
	}

	public List getPages(long nodeId, String title, int begin, int end)
		throws SystemException {

		return wikiPagePersistence.findByN_T(
			nodeId, title, begin, end, new PageCreateDateComparator(false));
	}

	public List getPages(long nodeId, boolean head, int begin, int end)
		throws SystemException {

		return wikiPagePersistence.findByN_H(
			nodeId, head, begin, end, new PageCreateDateComparator(false));
	}

	public List getPages(
			long nodeId, String title, boolean head, int begin, int end)
		throws SystemException {

		return wikiPagePersistence.findByN_T_H(
			nodeId, title, head, begin, end,
			new PageCreateDateComparator(false));
	}

	public int getPagesCount(long nodeId) throws SystemException {
		return wikiPagePersistence.countByNodeId(nodeId);
	}

	public int getPagesCount(long nodeId, String title)
		throws SystemException {

		return wikiPagePersistence.countByN_T(nodeId, title);
	}

	public int getPagesCount(long nodeId, boolean head)
		throws SystemException {

		return wikiPagePersistence.countByN_H(nodeId, head);
	}

	public int getPagesCount(long nodeId, String title, boolean head)
		throws SystemException {

		return wikiPagePersistence.countByN_T_H(nodeId, title, head);
	}

	public List getRecentChanges(long nodeId, int begin, int end)
		throws SystemException {

		Calendar cal = CalendarFactoryUtil.getCalendar();

		cal.add(Calendar.WEEK_OF_YEAR, -1);

		return wikiPageFinder.findByCreateDate(
			nodeId, cal.getTime(), false, begin, end);
	}

	public int getRecentChangesCount(long nodeId) throws SystemException {
		Calendar cal = CalendarFactoryUtil.getCalendar();

		cal.add(Calendar.WEEK_OF_YEAR, -1);

		return wikiPageFinder.countByCreateDate(nodeId, cal.getTime(), false);
	}

	public WikiPage revertPage(
			long userId, long nodeId, String title, double version)
		throws PortalException, SystemException {

		WikiPage oldPage = getPage(nodeId, title, version);

		return updatePage(
			userId, nodeId, title, oldPage.getContent(), oldPage.getFormat(),
			null);
	}

	public WikiPage updatePage(
			long userId, long nodeId, String title, String content,
			String format, String[] tagsEntries)
		throws PortalException, SystemException {

		// Page

		User user = userPersistence.findByPrimaryKey(userId);
		Date now = new Date();

		validate(nodeId, content, format);

		WikiPage page = getPage(nodeId, title);

		long resourcePrimKey = page.getResourcePrimKey();

		page.setHead(false);

		wikiPagePersistence.update(page);

		double oldVersion = page.getVersion();
		double newVersion = MathUtil.format(oldVersion + 0.1, 1, 1);

		long pageId = counterLocalService.increment();

		page = wikiPagePersistence.create(pageId);

		page.setResourcePrimKey(resourcePrimKey);
		page.setCompanyId(user.getCompanyId());
		page.setUserId(user.getUserId());
		page.setUserName(user.getFullName());
		page.setCreateDate(now);
		page.setNodeId(nodeId);
		page.setTitle(title);
		page.setVersion(newVersion);
		page.setContent(content);
		page.setFormat(format);
		page.setHead(true);

		wikiPagePersistence.update(page);

		// Node

		WikiNode node = wikiNodePersistence.findByPrimaryKey(nodeId);

		node.setLastPostDate(now);

		wikiNodePersistence.update(node);

		// Tags

		updateTagsAsset(userId, page, tagsEntries);

		// Lucene

		try {
			Indexer.updatePage(
				node.getCompanyId(), node.getGroupId(), nodeId, title, content,
				tagsEntries);
		}
		catch (IOException ioe) {
			_log.error("Indexing " + page.getPrimaryKey(), ioe);
		}

		return page;
	}

	public void updateTagsAsset(
			long userId, WikiPage page, String[] tagsEntries)
		throws PortalException, SystemException {

		tagsAssetLocalService.updateAsset(
			userId, page.getNode().getGroupId(), WikiPage.class.getName(),
			page.getResourcePrimKey(), tagsEntries, null, null, null, null,
			ContentTypes.TEXT_HTML, page.getTitle(), null, null, null, 0, 0,
			null, false);
	}

	protected void validate(long nodeId, String content, String format)
		throws PortalException {

		if (format.equals(WikiPageImpl.CLASSIC_WIKI_FORMAT)) {
			try {
				NodeFilter filter = WikiUtil.getFilter(nodeId);

				WikiUtil.convert(filter, content);
			}
			catch (Exception e) {
				throw new PageContentException();
			}
		}
	}

	protected void validate(
			String title, long nodeId, String content, String format)
		throws PortalException {

		if (Validator.isNull(title)) {
			throw new PageTitleException();
		}

		Pattern pattern = Pattern.compile("(((\\p{Lu}\\p{Ll}+)_?)+)");
		Matcher matcher = pattern.matcher(title);

		if (!matcher.matches()) {
			throw new PageTitleException();
		}

		validate(nodeId, content, format);
	}

	private static Log _log = LogFactory.getLog(WikiPageLocalServiceImpl.class);

}