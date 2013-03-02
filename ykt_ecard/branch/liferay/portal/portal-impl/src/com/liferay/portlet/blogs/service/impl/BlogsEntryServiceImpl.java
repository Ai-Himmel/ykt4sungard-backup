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
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Organization;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.service.base.BlogsEntryServiceBaseImpl;
import com.liferay.portlet.blogs.service.permission.BlogsEntryPermission;
import com.liferay.util.Html;
import com.liferay.util.RSSUtil;

import com.sun.syndication.feed.synd.SyndContent;
import com.sun.syndication.feed.synd.SyndContentImpl;
import com.sun.syndication.feed.synd.SyndEntry;
import com.sun.syndication.feed.synd.SyndEntryImpl;
import com.sun.syndication.feed.synd.SyndFeed;
import com.sun.syndication.feed.synd.SyndFeedImpl;
import com.sun.syndication.io.FeedException;

import java.io.IOException;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="BlogsEntryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BlogsEntryServiceImpl extends BlogsEntryServiceBaseImpl {

	public BlogsEntry addEntry(
			long plid, String title, String content, int displayDateMonth,
			int displayDateDay, int displayDateYear, int displayDateHour,
			int displayDateMinute, String[] tagsEntries,
			boolean addCommunityPermissions, boolean addGuestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.BLOGS,
			ActionKeys.ADD_ENTRY);

		return blogsEntryLocalService.addEntry(
			getUserId(), plid, title, content, displayDateMonth, displayDateDay,
			displayDateYear, displayDateHour, displayDateMinute, tagsEntries,
			addCommunityPermissions, addGuestPermissions, themeDisplay);
	}

	public BlogsEntry addEntry(
			long plid, String title, String content, int displayDateMonth,
			int displayDateDay, int displayDateYear, int displayDateHour,
			int displayDateMinute, String[] tagsEntries,
			String[] communityPermissions, String[] guestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.BLOGS,
			ActionKeys.ADD_ENTRY);

		return blogsEntryLocalService.addEntry(
			getUserId(), plid, title, content, displayDateMonth, displayDateDay,
			displayDateYear, displayDateHour, displayDateMinute, tagsEntries,
			communityPermissions, guestPermissions, themeDisplay);
	}

	public void deleteEntry(long entryId)
		throws PortalException, SystemException {

		BlogsEntryPermission.check(
			getPermissionChecker(), entryId, ActionKeys.DELETE);

		blogsEntryLocalService.deleteEntry(entryId);
	}

	public List getCompanyEntries(long companyId, int max)
		throws PortalException, SystemException {

		List entries = new ArrayList();

		Iterator itr = blogsEntryLocalService.getCompanyEntries(
			companyId, 0, _MAX_END).iterator();

		while (itr.hasNext() && (entries.size() < max)) {
			BlogsEntry entry = (BlogsEntry)itr.next();

			if (BlogsEntryPermission.contains(
					getPermissionChecker(), entry, ActionKeys.VIEW)) {

				entries.add(entry);
			}
		}

		return entries;
	}

	public String getCompanyEntriesRSS(
			long companyId, int max, String type, double version,
			String displayStyle, String feedURL, String entryURL)
		throws PortalException, SystemException {

		Company company = companyPersistence.findByPrimaryKey(companyId);

		String name = company.getName();

		List blogsEntries = getCompanyEntries(companyId, max);

		return exportToRSS(
			name, null, type, version, displayStyle, feedURL, entryURL,
			blogsEntries);
	}

	public BlogsEntry getEntry(long entryId)
		throws PortalException, SystemException {

		BlogsEntryPermission.check(
			getPermissionChecker(), entryId, ActionKeys.VIEW);

		return blogsEntryLocalService.getEntry(entryId);
	}

	public BlogsEntry getEntry(long groupId, String urlTitle)
		throws PortalException, SystemException {

		BlogsEntry entry = blogsEntryLocalService.getEntry(groupId, urlTitle);

		BlogsEntryPermission.check(
			getPermissionChecker(), entry.getEntryId(), ActionKeys.VIEW);

		return entry;
	}

	public List getGroupEntries(long groupId, int max)
		throws PortalException, SystemException {

		List entries = new ArrayList();

		Iterator itr = blogsEntryLocalService.getGroupEntries(
			groupId, 0, _MAX_END).iterator();

		while (itr.hasNext() && (entries.size() < max)) {
			BlogsEntry entry = (BlogsEntry)itr.next();

			if (BlogsEntryPermission.contains(
					getPermissionChecker(), entry, ActionKeys.VIEW)) {

				entries.add(entry);
			}
		}

		return entries;
	}

	public String getGroupEntriesRSS(
			long groupId, int max, String type, double version,
			String displayStyle, String feedURL, String entryURL)
		throws PortalException, SystemException {

		Group group = groupPersistence.findByPrimaryKey(groupId);

		String name = group.getDescriptiveName();

		List blogsEntries = getGroupEntries(groupId, max);

		return exportToRSS(
			name, null, type, version, displayStyle, feedURL, entryURL,
			blogsEntries);
	}

	public List getOrganizationEntries(long organizationId, int max)
		throws PortalException, SystemException {

		List entries = new ArrayList();

		Iterator itr = blogsEntryFinder.findByOrganizationId(
			organizationId, 0, _MAX_END).iterator();

		while (itr.hasNext() && (entries.size() < max)) {
			BlogsEntry entry = (BlogsEntry)itr.next();

			if (BlogsEntryPermission.contains(
					getPermissionChecker(), entry, ActionKeys.VIEW)) {

				entries.add(entry);
			}
		}

		return entries;
	}

	public String getOrganizationEntriesRSS(
			long organizationId, int max, String type, double version,
			String displayStyle, String feedURL, String entryURL)
		throws PortalException, SystemException {

		Organization organization = organizationPersistence.findByPrimaryKey(
			organizationId);

		String name = organization.getName();

		List blogsEntries = getOrganizationEntries(organizationId, max);

		return exportToRSS(
			name, null, type, version, displayStyle, feedURL, entryURL,
			blogsEntries);
	}

	public BlogsEntry updateEntry(
			long entryId, String title, String content, int displayDateMonth,
			int displayDateDay, int displayDateYear, int displayDateHour,
			int displayDateMinute, String[] tagsEntries,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		BlogsEntryPermission.check(
			getPermissionChecker(), entryId, ActionKeys.UPDATE);

		return blogsEntryLocalService.updateEntry(
			getUserId(), entryId, title, content, displayDateMonth,
			displayDateDay, displayDateYear, displayDateHour, displayDateMinute,
			tagsEntries, themeDisplay);
	}

	protected String exportToRSS(
			String name, String description, String type, double version,
			String displayStyle, String feedURL, String entryURL,
			List blogsEntries)
		throws SystemException {

		SyndFeed syndFeed = new SyndFeedImpl();

		syndFeed.setFeedType(type + "_" + version);
		syndFeed.setTitle(name);
		syndFeed.setLink(feedURL);
		syndFeed.setDescription(GetterUtil.getString(description, name));

		List entries = new ArrayList();

		syndFeed.setEntries(entries);

		Iterator itr = blogsEntries.iterator();

		while (itr.hasNext()) {
			BlogsEntry entry = (BlogsEntry)itr.next();

			String author = PortalUtil.getUserName(
				entry.getUserId(), entry.getUserName());

			String link = entryURL;

			if (link.endsWith("/blogs/rss")) {
				link =
					link.substring(0, link.length() - 3) + entry.getUrlTitle();
			}
			else {
				if (!link.endsWith("?")) {
					link += "&";
				}

				link += "entryId=" + entry.getEntryId();
			}

			String value = null;

			if (displayStyle.equals(RSSUtil.DISPLAY_STYLE_ABSTRACT)) {
				value = StringUtil.shorten(
					Html.stripHtml(entry.getContent()), _RSS_ABSTRACT_LENGTH,
					StringPool.BLANK);
			}
			else {
				value = entry.getContent();
			}

			SyndEntry syndEntry = new SyndEntryImpl();

			syndEntry.setAuthor(author);
			syndEntry.setTitle(entry.getTitle());
			syndEntry.setLink(link);
			syndEntry.setPublishedDate(entry.getCreateDate());

			SyndContent syndContent = new SyndContentImpl();

			syndContent.setType("html");
			syndContent.setValue(value);

			syndEntry.setDescription(syndContent);

			entries.add(syndEntry);
		}

		try {
			return RSSUtil.export(syndFeed);
		}
		catch (FeedException fe) {
			throw new SystemException(fe);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	private static final int _MAX_END = 200;

	private static final int _RSS_ABSTRACT_LENGTH = GetterUtil.getInteger(
		PropsUtil.get(PropsUtil.BLOGS_RSS_ABSTRACT_LENGTH));

}