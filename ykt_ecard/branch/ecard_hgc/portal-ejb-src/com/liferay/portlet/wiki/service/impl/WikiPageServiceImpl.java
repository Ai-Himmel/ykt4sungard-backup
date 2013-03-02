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

package com.liferay.portlet.wiki.service.impl;

import com.liferay.lock.DuplicateLockException;
import com.liferay.lock.model.Lock;
import com.liferay.lock.service.spring.LockServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.wiki.PageContentException;
import com.liferay.portlet.wiki.PageTitleException;
import com.liferay.portlet.wiki.model.WikiNode;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.portlet.wiki.service.persistence.WikiNodeUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPageFinder;
import com.liferay.portlet.wiki.service.persistence.WikiPagePK;
import com.liferay.portlet.wiki.service.persistence.WikiPageUtil;
import com.liferay.portlet.wiki.service.spring.WikiNodeServiceUtil;
import com.liferay.portlet.wiki.service.spring.WikiPageService;
import com.liferay.portlet.wiki.util.Indexer;
import com.liferay.portlet.wiki.util.NodeFilter;
import com.liferay.portlet.wiki.util.WikiPageComparator;
import com.liferay.portlet.wiki.util.WikiUtil;
import com.liferay.util.MathUtil;
import com.liferay.util.Validator;

import java.io.IOException;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * <a href="WikiPageServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class WikiPageServiceImpl
	extends PrincipalBean implements WikiPageService {

	// Business methods

	public void deletePage(String nodeId, String title)
		throws PortalException, SystemException {

		if (!WikiNodeServiceUtil.hasAdmin(nodeId)) {
			throw new PrincipalException();
		}

		// Lock page

		User user = getUser();

		WikiPagePK pk = new WikiPagePK(nodeId, title, 0.0);

		if (!LockServiceUtil.isLocked(WikiPage.class.getName(), pk)) {
			LockServiceUtil.lock(
				WikiPage.class.getName(), pk, user.getCompanyId(),
				user.getUserId(), WikiPage.LOCK_EXPIRATION_TIME);
		}
		else if (!LockServiceUtil.hasLock(
			WikiPage.class.getName(), pk, user.getUserId())) {

			Lock lock = LockServiceUtil.getLock(WikiPage.class.getName(), pk);

			throw new DuplicateLockException(lock);
		}

		// Delete all versions of this page

		WikiPageUtil.removeByN_T(nodeId, title);

		// Update lucene

		WikiNode node = WikiNodeUtil.findByPrimaryKey(nodeId);

		try {
			Indexer.deletePage(
				node.getCompanyId(), node.getPortletId(), nodeId, title);
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		// Unlock page

		LockServiceUtil.unlock(WikiPage.class.getName(), pk);
	}

	public boolean exists(String nodeId, String title) throws SystemException {
		List pages = WikiPageUtil.findByN_T_H(nodeId, title, true);

		if (pages.size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public WikiPage getHeadPage(String nodeId, String title)
		throws PortalException, SystemException {

		if (!WikiNodeServiceUtil.hasRead(nodeId)) {
			throw new PrincipalException();
		}

		WikiPage page = null;

		List pages = WikiPageUtil.findByN_T_H(nodeId, title, true);

		if (pages.size() > 0) {
			page = (WikiPage)pages.iterator().next();
		}
		else {
			_validate(title);

			User user = getUser();

			WikiPagePK pk = new WikiPagePK(
				nodeId, title, WikiPage.DEFAULT_VERSION);

			page = WikiPageUtil.create(pk);

			page.setCompanyId(user.getCompanyId());
			page.setUserId(user.getUserId());
			page.setUserName(user.getFullName());
			page.setCreateDate(new Date());
			page.setFormat(WikiPage.DEFAULT_FORMAT);
			page.setHead(true);
		}

		return page;
	}

	public List getHeadPagesByNode(String nodeId)
		throws PortalException, SystemException {

		if (!WikiNodeServiceUtil.hasRead(nodeId)) {
			throw new PrincipalException();
		}

		return WikiPageUtil.findByN_H(nodeId, true);
	}

	public List getLinks(String nodeId, String title)
		throws PortalException, SystemException {

		if (!WikiNodeServiceUtil.hasRead(nodeId)) {
			throw new PrincipalException();
		}

		List links = new ArrayList();

		List pages = WikiPageUtil.findByN_H(nodeId, true);

		for (int i = 0; i < pages.size(); i++) {
			WikiPage page = (WikiPage)pages.get(i);

			if (page.getFormat().equals(WikiPage.CLASSIC_WIKI_FORMAT)) {
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

	public List getOrphans(String nodeId)
		throws PortalException, SystemException {

		if (!WikiNodeServiceUtil.hasRead(nodeId)) {
			throw new PrincipalException();
		}

		List pageTitles = new ArrayList();

		List pages = WikiPageUtil.findByN_H(nodeId, true);

		for (int i = 0; i < pages.size(); i++) {
			WikiPage page = (WikiPage)pages.get(i);

			if (page.getFormat().equals(WikiPage.CLASSIC_WIKI_FORMAT)) {
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

	public WikiPage getPage(String nodeId, String title, double version)
		throws PortalException, SystemException {

		WikiPage page = null;

		if (version == 0.0) {
			page = getHeadPage(nodeId, title);
		}
		else {
			if (!WikiNodeServiceUtil.hasRead(nodeId)) {
				throw new PrincipalException();
			}

			page = WikiPageUtil.findByPrimaryKey(
				new WikiPagePK(nodeId, title, version));
		}

		return page;
	}

	public List getPages(String nodeId, String title, boolean head)
		throws PortalException, SystemException {

		if (!WikiNodeServiceUtil.hasRead(nodeId)) {
			throw new PrincipalException();
		}

		List pages = WikiPageUtil.findByN_T_H(nodeId, title, head);

		Collections.sort(pages, new WikiPageComparator());

		return pages;
	}

	public List getPagesByNode(String nodeId, boolean head)
		throws PortalException, SystemException {

		if (!WikiNodeServiceUtil.hasRead(nodeId)) {
			throw new PrincipalException();
		}

		return WikiPageUtil.findByN_H(nodeId, head);
	}

	public int getPagesSizeByNode(String nodeId, boolean head)
		throws SystemException {

		return WikiPageUtil.countByN_H(nodeId, head);
	}

	public List getRecentChanges(String nodeId)
		throws PortalException, SystemException {

		if (!WikiNodeServiceUtil.hasRead(nodeId)) {
			throw new PrincipalException();
		}

		Calendar cal = new GregorianCalendar();
		cal.add(Calendar.WEEK_OF_YEAR, -1);

		List recentChanges =
			WikiPageFinder.findByCreateDate(nodeId, cal.getTime(), false);

		Collections.sort(recentChanges, new WikiPageComparator());

		return recentChanges;
	}

	public WikiPage lockPage(String nodeId, String title, double version)
		throws PortalException, SystemException {

		if (!WikiNodeServiceUtil.hasWrite(nodeId)) {
			throw new PrincipalException();
		}

		WikiPage page = getPage(nodeId, title, version);

		WikiPagePK pk = new WikiPagePK(nodeId, title, 0.0);

		LockServiceUtil.lock(
			WikiPage.class.getName(), pk, page.getCompanyId(), getUserId(),
			WikiPage.LOCK_EXPIRATION_TIME);

		return page;
	}

	public WikiPage revertPage(String nodeId, String title, double version)
		throws PortalException, SystemException {

		WikiPage oldPage = getPage(nodeId, title, version);

		return updatePage(
			nodeId, title, oldPage.getContent(), oldPage.getFormat());
	}

	public void unlockPage(String nodeId, String title)
		throws PortalException, SystemException {

		WikiPagePK pk = new WikiPagePK(nodeId, title, 0.0);

		LockServiceUtil.unlock(WikiPage.class.getName(), pk);
	}

	public WikiPage updatePage(
			String nodeId, String title, String content, String format)
		throws PortalException, SystemException {

		_validate(nodeId, content, format);

		WikiPage page = getHeadPage(nodeId, title);

		Date now = new Date();

		if (page.isNew()) {
			if (!WikiNodeServiceUtil.hasWrite(nodeId)) {
				throw new PrincipalException();
			}

			page.setContent(content);
			page.setFormat(format);

			WikiPageUtil.update(page);
		}
		else {
			lockPage(nodeId, title, page.getVersion());

			page.setHead(false);

			WikiPageUtil.update(page);

			User user = getUser();

			double oldVersion = page.getVersion();
			double newVersion = MathUtil.format(oldVersion + 0.1, 1, 1);

			WikiPagePK pk = new WikiPagePK(nodeId, title, newVersion);

			page = WikiPageUtil.create(pk);

			page.setCompanyId(user.getCompanyId());
			page.setUserId(user.getUserId());
			page.setUserName(user.getFullName());
			page.setCreateDate(now);
			page.setContent(content);
			page.setFormat(format);
			page.setHead(true);

			WikiPageUtil.update(page);

			unlockPage(nodeId, title);
		}

		// Update node last post date

		WikiNode node = WikiNodeUtil.findByPrimaryKey(nodeId);

		node.setLastPostDate(now);

		WikiNodeUtil.update(node);

		// Update lucene

		try {
			Indexer.addPage(
				node.getCompanyId(), node.getPortletId(), node.getGroupId(),
				nodeId, title, content);
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		return page;
	}

	// Private methods

	private void _validate(String title) throws PortalException {
		if (Validator.isNull(title)) {
			throw new PageTitleException();
		}

		Pattern pattern = Pattern.compile("(([A-Z][a-z]+){2,})");
		Matcher matcher = pattern.matcher(title);

		if (!matcher.matches()) {
			throw new PageTitleException();
		}
	}

	private void _validate(String nodeId, String content, String format)
		throws PortalException {

		if (format.equals(WikiPage.CLASSIC_WIKI_FORMAT)) {
			try {
				NodeFilter filter = WikiUtil.getFilter(nodeId);

				WikiUtil.convert(filter, content);
			}
			catch (Exception e) {
				throw new PageContentException();
			}
		}
	}

}