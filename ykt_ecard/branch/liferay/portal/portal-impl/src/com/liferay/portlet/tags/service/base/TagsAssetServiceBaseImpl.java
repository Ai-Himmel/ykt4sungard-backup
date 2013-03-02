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

package com.liferay.portlet.tags.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.portal.service.CompanyLocalService;
import com.liferay.portal.service.CompanyLocalServiceFactory;
import com.liferay.portal.service.CompanyService;
import com.liferay.portal.service.CompanyServiceFactory;
import com.liferay.portal.service.GroupLocalService;
import com.liferay.portal.service.GroupLocalServiceFactory;
import com.liferay.portal.service.GroupService;
import com.liferay.portal.service.GroupServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.persistence.CompanyPersistence;
import com.liferay.portal.service.persistence.CompanyUtil;
import com.liferay.portal.service.persistence.GroupFinder;
import com.liferay.portal.service.persistence.GroupFinderUtil;
import com.liferay.portal.service.persistence.GroupPersistence;
import com.liferay.portal.service.persistence.GroupUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserUtil;

import com.liferay.portlet.blogs.service.BlogsEntryLocalService;
import com.liferay.portlet.blogs.service.BlogsEntryLocalServiceFactory;
import com.liferay.portlet.blogs.service.BlogsEntryService;
import com.liferay.portlet.blogs.service.BlogsEntryServiceFactory;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryFinderUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryUtil;
import com.liferay.portlet.bookmarks.service.BookmarksEntryLocalService;
import com.liferay.portlet.bookmarks.service.BookmarksEntryLocalServiceFactory;
import com.liferay.portlet.bookmarks.service.BookmarksEntryService;
import com.liferay.portlet.bookmarks.service.BookmarksEntryServiceFactory;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinder;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinderUtil;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistence;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryUtil;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalService;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceFactory;
import com.liferay.portlet.documentlibrary.service.DLFileEntryService;
import com.liferay.portlet.documentlibrary.service.DLFileEntryServiceFactory;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinderUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryUtil;
import com.liferay.portlet.journal.service.JournalArticleLocalService;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalArticleResourceLocalService;
import com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalArticleService;
import com.liferay.portlet.journal.service.JournalArticleServiceFactory;
import com.liferay.portlet.journal.service.persistence.JournalArticleFinder;
import com.liferay.portlet.journal.service.persistence.JournalArticleFinderUtil;
import com.liferay.portlet.journal.service.persistence.JournalArticlePersistence;
import com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence;
import com.liferay.portlet.journal.service.persistence.JournalArticleResourceUtil;
import com.liferay.portlet.journal.service.persistence.JournalArticleUtil;
import com.liferay.portlet.messageboards.service.MBMessageLocalService;
import com.liferay.portlet.messageboards.service.MBMessageLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBMessageService;
import com.liferay.portlet.messageboards.service.MBMessageServiceFactory;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFinder;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFinderUtil;
import com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence;
import com.liferay.portlet.messageboards.service.persistence.MBMessageUtil;
import com.liferay.portlet.tags.service.TagsAssetLocalService;
import com.liferay.portlet.tags.service.TagsAssetLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsAssetService;
import com.liferay.portlet.tags.service.TagsEntryLocalService;
import com.liferay.portlet.tags.service.TagsEntryLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsEntryService;
import com.liferay.portlet.tags.service.TagsEntryServiceFactory;
import com.liferay.portlet.tags.service.TagsPropertyLocalService;
import com.liferay.portlet.tags.service.TagsPropertyLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsPropertyService;
import com.liferay.portlet.tags.service.TagsPropertyServiceFactory;
import com.liferay.portlet.tags.service.TagsSourceLocalService;
import com.liferay.portlet.tags.service.TagsSourceLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsSourceService;
import com.liferay.portlet.tags.service.TagsSourceServiceFactory;
import com.liferay.portlet.tags.service.persistence.TagsAssetFinder;
import com.liferay.portlet.tags.service.persistence.TagsAssetFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsAssetPersistence;
import com.liferay.portlet.tags.service.persistence.TagsAssetUtil;
import com.liferay.portlet.tags.service.persistence.TagsEntryFinder;
import com.liferay.portlet.tags.service.persistence.TagsEntryFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsEntryPersistence;
import com.liferay.portlet.tags.service.persistence.TagsEntryUtil;
import com.liferay.portlet.tags.service.persistence.TagsPropertyFinder;
import com.liferay.portlet.tags.service.persistence.TagsPropertyFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinder;
import com.liferay.portlet.tags.service.persistence.TagsPropertyKeyFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsPropertyPersistence;
import com.liferay.portlet.tags.service.persistence.TagsPropertyUtil;
import com.liferay.portlet.tags.service.persistence.TagsSourcePersistence;
import com.liferay.portlet.tags.service.persistence.TagsSourceUtil;
import com.liferay.portlet.wiki.service.WikiPageLocalService;
import com.liferay.portlet.wiki.service.WikiPageLocalServiceFactory;
import com.liferay.portlet.wiki.service.WikiPageResourceLocalService;
import com.liferay.portlet.wiki.service.WikiPageResourceLocalServiceFactory;
import com.liferay.portlet.wiki.service.WikiPageService;
import com.liferay.portlet.wiki.service.WikiPageServiceFactory;
import com.liferay.portlet.wiki.service.persistence.WikiPageFinder;
import com.liferay.portlet.wiki.service.persistence.WikiPageFinderUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPagePersistence;
import com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence;
import com.liferay.portlet.wiki.service.persistence.WikiPageResourceUtil;
import com.liferay.portlet.wiki.service.persistence.WikiPageUtil;

import org.springframework.beans.factory.InitializingBean;

/**
 * <a href="TagsAssetServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class TagsAssetServiceBaseImpl extends PrincipalBean
	implements TagsAssetService, InitializingBean {
	public TagsAssetLocalService getTagsAssetLocalService() {
		return tagsAssetLocalService;
	}

	public void setTagsAssetLocalService(
		TagsAssetLocalService tagsAssetLocalService) {
		this.tagsAssetLocalService = tagsAssetLocalService;
	}

	public TagsAssetPersistence getTagsAssetPersistence() {
		return tagsAssetPersistence;
	}

	public void setTagsAssetPersistence(
		TagsAssetPersistence tagsAssetPersistence) {
		this.tagsAssetPersistence = tagsAssetPersistence;
	}

	public TagsAssetFinder getTagsAssetFinder() {
		return tagsAssetFinder;
	}

	public void setTagsAssetFinder(TagsAssetFinder tagsAssetFinder) {
		this.tagsAssetFinder = tagsAssetFinder;
	}

	public TagsEntryLocalService getTagsEntryLocalService() {
		return tagsEntryLocalService;
	}

	public void setTagsEntryLocalService(
		TagsEntryLocalService tagsEntryLocalService) {
		this.tagsEntryLocalService = tagsEntryLocalService;
	}

	public TagsEntryService getTagsEntryService() {
		return tagsEntryService;
	}

	public void setTagsEntryService(TagsEntryService tagsEntryService) {
		this.tagsEntryService = tagsEntryService;
	}

	public TagsEntryPersistence getTagsEntryPersistence() {
		return tagsEntryPersistence;
	}

	public void setTagsEntryPersistence(
		TagsEntryPersistence tagsEntryPersistence) {
		this.tagsEntryPersistence = tagsEntryPersistence;
	}

	public TagsEntryFinder getTagsEntryFinder() {
		return tagsEntryFinder;
	}

	public void setTagsEntryFinder(TagsEntryFinder tagsEntryFinder) {
		this.tagsEntryFinder = tagsEntryFinder;
	}

	public TagsPropertyLocalService getTagsPropertyLocalService() {
		return tagsPropertyLocalService;
	}

	public void setTagsPropertyLocalService(
		TagsPropertyLocalService tagsPropertyLocalService) {
		this.tagsPropertyLocalService = tagsPropertyLocalService;
	}

	public TagsPropertyService getTagsPropertyService() {
		return tagsPropertyService;
	}

	public void setTagsPropertyService(TagsPropertyService tagsPropertyService) {
		this.tagsPropertyService = tagsPropertyService;
	}

	public TagsPropertyPersistence getTagsPropertyPersistence() {
		return tagsPropertyPersistence;
	}

	public void setTagsPropertyPersistence(
		TagsPropertyPersistence tagsPropertyPersistence) {
		this.tagsPropertyPersistence = tagsPropertyPersistence;
	}

	public TagsPropertyFinder getTagsPropertyFinder() {
		return tagsPropertyFinder;
	}

	public void setTagsPropertyFinder(TagsPropertyFinder tagsPropertyFinder) {
		this.tagsPropertyFinder = tagsPropertyFinder;
	}

	public TagsPropertyKeyFinder getTagsPropertyKeyFinder() {
		return tagsPropertyKeyFinder;
	}

	public void setTagsPropertyKeyFinder(
		TagsPropertyKeyFinder tagsPropertyKeyFinder) {
		this.tagsPropertyKeyFinder = tagsPropertyKeyFinder;
	}

	public TagsSourceLocalService getTagsSourceLocalService() {
		return tagsSourceLocalService;
	}

	public void setTagsSourceLocalService(
		TagsSourceLocalService tagsSourceLocalService) {
		this.tagsSourceLocalService = tagsSourceLocalService;
	}

	public TagsSourceService getTagsSourceService() {
		return tagsSourceService;
	}

	public void setTagsSourceService(TagsSourceService tagsSourceService) {
		this.tagsSourceService = tagsSourceService;
	}

	public TagsSourcePersistence getTagsSourcePersistence() {
		return tagsSourcePersistence;
	}

	public void setTagsSourcePersistence(
		TagsSourcePersistence tagsSourcePersistence) {
		this.tagsSourcePersistence = tagsSourcePersistence;
	}

	public CounterLocalService getCounterLocalService() {
		return counterLocalService;
	}

	public void setCounterLocalService(CounterLocalService counterLocalService) {
		this.counterLocalService = counterLocalService;
	}

	public CounterService getCounterService() {
		return counterService;
	}

	public void setCounterService(CounterService counterService) {
		this.counterService = counterService;
	}

	public CompanyLocalService getCompanyLocalService() {
		return companyLocalService;
	}

	public void setCompanyLocalService(CompanyLocalService companyLocalService) {
		this.companyLocalService = companyLocalService;
	}

	public CompanyService getCompanyService() {
		return companyService;
	}

	public void setCompanyService(CompanyService companyService) {
		this.companyService = companyService;
	}

	public CompanyPersistence getCompanyPersistence() {
		return companyPersistence;
	}

	public void setCompanyPersistence(CompanyPersistence companyPersistence) {
		this.companyPersistence = companyPersistence;
	}

	public GroupLocalService getGroupLocalService() {
		return groupLocalService;
	}

	public void setGroupLocalService(GroupLocalService groupLocalService) {
		this.groupLocalService = groupLocalService;
	}

	public GroupService getGroupService() {
		return groupService;
	}

	public void setGroupService(GroupService groupService) {
		this.groupService = groupService;
	}

	public GroupPersistence getGroupPersistence() {
		return groupPersistence;
	}

	public void setGroupPersistence(GroupPersistence groupPersistence) {
		this.groupPersistence = groupPersistence;
	}

	public GroupFinder getGroupFinder() {
		return groupFinder;
	}

	public void setGroupFinder(GroupFinder groupFinder) {
		this.groupFinder = groupFinder;
	}

	public UserLocalService getUserLocalService() {
		return userLocalService;
	}

	public void setUserLocalService(UserLocalService userLocalService) {
		this.userLocalService = userLocalService;
	}

	public UserService getUserService() {
		return userService;
	}

	public void setUserService(UserService userService) {
		this.userService = userService;
	}

	public UserPersistence getUserPersistence() {
		return userPersistence;
	}

	public void setUserPersistence(UserPersistence userPersistence) {
		this.userPersistence = userPersistence;
	}

	public UserFinder getUserFinder() {
		return userFinder;
	}

	public void setUserFinder(UserFinder userFinder) {
		this.userFinder = userFinder;
	}

	public BlogsEntryLocalService getBlogsEntryLocalService() {
		return blogsEntryLocalService;
	}

	public void setBlogsEntryLocalService(
		BlogsEntryLocalService blogsEntryLocalService) {
		this.blogsEntryLocalService = blogsEntryLocalService;
	}

	public BlogsEntryService getBlogsEntryService() {
		return blogsEntryService;
	}

	public void setBlogsEntryService(BlogsEntryService blogsEntryService) {
		this.blogsEntryService = blogsEntryService;
	}

	public BlogsEntryPersistence getBlogsEntryPersistence() {
		return blogsEntryPersistence;
	}

	public void setBlogsEntryPersistence(
		BlogsEntryPersistence blogsEntryPersistence) {
		this.blogsEntryPersistence = blogsEntryPersistence;
	}

	public BlogsEntryFinder getBlogsEntryFinder() {
		return blogsEntryFinder;
	}

	public void setBlogsEntryFinder(BlogsEntryFinder blogsEntryFinder) {
		this.blogsEntryFinder = blogsEntryFinder;
	}

	public BookmarksEntryLocalService getBookmarksEntryLocalService() {
		return bookmarksEntryLocalService;
	}

	public void setBookmarksEntryLocalService(
		BookmarksEntryLocalService bookmarksEntryLocalService) {
		this.bookmarksEntryLocalService = bookmarksEntryLocalService;
	}

	public BookmarksEntryService getBookmarksEntryService() {
		return bookmarksEntryService;
	}

	public void setBookmarksEntryService(
		BookmarksEntryService bookmarksEntryService) {
		this.bookmarksEntryService = bookmarksEntryService;
	}

	public BookmarksEntryPersistence getBookmarksEntryPersistence() {
		return bookmarksEntryPersistence;
	}

	public void setBookmarksEntryPersistence(
		BookmarksEntryPersistence bookmarksEntryPersistence) {
		this.bookmarksEntryPersistence = bookmarksEntryPersistence;
	}

	public BookmarksEntryFinder getBookmarksEntryFinder() {
		return bookmarksEntryFinder;
	}

	public void setBookmarksEntryFinder(
		BookmarksEntryFinder bookmarksEntryFinder) {
		this.bookmarksEntryFinder = bookmarksEntryFinder;
	}

	public DLFileEntryLocalService getDLFileEntryLocalService() {
		return dlFileEntryLocalService;
	}

	public void setDLFileEntryLocalService(
		DLFileEntryLocalService dlFileEntryLocalService) {
		this.dlFileEntryLocalService = dlFileEntryLocalService;
	}

	public DLFileEntryService getDLFileEntryService() {
		return dlFileEntryService;
	}

	public void setDLFileEntryService(DLFileEntryService dlFileEntryService) {
		this.dlFileEntryService = dlFileEntryService;
	}

	public DLFileEntryPersistence getDLFileEntryPersistence() {
		return dlFileEntryPersistence;
	}

	public void setDLFileEntryPersistence(
		DLFileEntryPersistence dlFileEntryPersistence) {
		this.dlFileEntryPersistence = dlFileEntryPersistence;
	}

	public DLFileEntryFinder getDLFileEntryFinder() {
		return dlFileEntryFinder;
	}

	public void setDLFileEntryFinder(DLFileEntryFinder dlFileEntryFinder) {
		this.dlFileEntryFinder = dlFileEntryFinder;
	}

	public JournalArticleLocalService getJournalArticleLocalService() {
		return journalArticleLocalService;
	}

	public void setJournalArticleLocalService(
		JournalArticleLocalService journalArticleLocalService) {
		this.journalArticleLocalService = journalArticleLocalService;
	}

	public JournalArticleService getJournalArticleService() {
		return journalArticleService;
	}

	public void setJournalArticleService(
		JournalArticleService journalArticleService) {
		this.journalArticleService = journalArticleService;
	}

	public JournalArticlePersistence getJournalArticlePersistence() {
		return journalArticlePersistence;
	}

	public void setJournalArticlePersistence(
		JournalArticlePersistence journalArticlePersistence) {
		this.journalArticlePersistence = journalArticlePersistence;
	}

	public JournalArticleFinder getJournalArticleFinder() {
		return journalArticleFinder;
	}

	public void setJournalArticleFinder(
		JournalArticleFinder journalArticleFinder) {
		this.journalArticleFinder = journalArticleFinder;
	}

	public JournalArticleResourceLocalService getJournalArticleResourceLocalService() {
		return journalArticleResourceLocalService;
	}

	public void setJournalArticleResourceLocalService(
		JournalArticleResourceLocalService journalArticleResourceLocalService) {
		this.journalArticleResourceLocalService = journalArticleResourceLocalService;
	}

	public JournalArticleResourcePersistence getJournalArticleResourcePersistence() {
		return journalArticleResourcePersistence;
	}

	public void setJournalArticleResourcePersistence(
		JournalArticleResourcePersistence journalArticleResourcePersistence) {
		this.journalArticleResourcePersistence = journalArticleResourcePersistence;
	}

	public MBMessageLocalService getMBMessageLocalService() {
		return mbMessageLocalService;
	}

	public void setMBMessageLocalService(
		MBMessageLocalService mbMessageLocalService) {
		this.mbMessageLocalService = mbMessageLocalService;
	}

	public MBMessageService getMBMessageService() {
		return mbMessageService;
	}

	public void setMBMessageService(MBMessageService mbMessageService) {
		this.mbMessageService = mbMessageService;
	}

	public MBMessagePersistence getMBMessagePersistence() {
		return mbMessagePersistence;
	}

	public void setMBMessagePersistence(
		MBMessagePersistence mbMessagePersistence) {
		this.mbMessagePersistence = mbMessagePersistence;
	}

	public MBMessageFinder getMBMessageFinder() {
		return mbMessageFinder;
	}

	public void setMBMessageFinder(MBMessageFinder mbMessageFinder) {
		this.mbMessageFinder = mbMessageFinder;
	}

	public WikiPageLocalService getWikiPageLocalService() {
		return wikiPageLocalService;
	}

	public void setWikiPageLocalService(
		WikiPageLocalService wikiPageLocalService) {
		this.wikiPageLocalService = wikiPageLocalService;
	}

	public WikiPageService getWikiPageService() {
		return wikiPageService;
	}

	public void setWikiPageService(WikiPageService wikiPageService) {
		this.wikiPageService = wikiPageService;
	}

	public WikiPagePersistence getWikiPagePersistence() {
		return wikiPagePersistence;
	}

	public void setWikiPagePersistence(WikiPagePersistence wikiPagePersistence) {
		this.wikiPagePersistence = wikiPagePersistence;
	}

	public WikiPageFinder getWikiPageFinder() {
		return wikiPageFinder;
	}

	public void setWikiPageFinder(WikiPageFinder wikiPageFinder) {
		this.wikiPageFinder = wikiPageFinder;
	}

	public WikiPageResourceLocalService getWikiPageResourceLocalService() {
		return wikiPageResourceLocalService;
	}

	public void setWikiPageResourceLocalService(
		WikiPageResourceLocalService wikiPageResourceLocalService) {
		this.wikiPageResourceLocalService = wikiPageResourceLocalService;
	}

	public WikiPageResourcePersistence getWikiPageResourcePersistence() {
		return wikiPageResourcePersistence;
	}

	public void setWikiPageResourcePersistence(
		WikiPageResourcePersistence wikiPageResourcePersistence) {
		this.wikiPageResourcePersistence = wikiPageResourcePersistence;
	}

	public void afterPropertiesSet() {
		if (tagsAssetLocalService == null) {
			tagsAssetLocalService = TagsAssetLocalServiceFactory.getImpl();
		}

		if (tagsAssetPersistence == null) {
			tagsAssetPersistence = TagsAssetUtil.getPersistence();
		}

		if (tagsAssetFinder == null) {
			tagsAssetFinder = TagsAssetFinderUtil.getFinder();
		}

		if (tagsEntryLocalService == null) {
			tagsEntryLocalService = TagsEntryLocalServiceFactory.getImpl();
		}

		if (tagsEntryService == null) {
			tagsEntryService = TagsEntryServiceFactory.getImpl();
		}

		if (tagsEntryPersistence == null) {
			tagsEntryPersistence = TagsEntryUtil.getPersistence();
		}

		if (tagsEntryFinder == null) {
			tagsEntryFinder = TagsEntryFinderUtil.getFinder();
		}

		if (tagsPropertyLocalService == null) {
			tagsPropertyLocalService = TagsPropertyLocalServiceFactory.getImpl();
		}

		if (tagsPropertyService == null) {
			tagsPropertyService = TagsPropertyServiceFactory.getImpl();
		}

		if (tagsPropertyPersistence == null) {
			tagsPropertyPersistence = TagsPropertyUtil.getPersistence();
		}

		if (tagsPropertyFinder == null) {
			tagsPropertyFinder = TagsPropertyFinderUtil.getFinder();
		}

		if (tagsPropertyKeyFinder == null) {
			tagsPropertyKeyFinder = TagsPropertyKeyFinderUtil.getFinder();
		}

		if (tagsSourceLocalService == null) {
			tagsSourceLocalService = TagsSourceLocalServiceFactory.getImpl();
		}

		if (tagsSourceService == null) {
			tagsSourceService = TagsSourceServiceFactory.getImpl();
		}

		if (tagsSourcePersistence == null) {
			tagsSourcePersistence = TagsSourceUtil.getPersistence();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
		}

		if (companyLocalService == null) {
			companyLocalService = CompanyLocalServiceFactory.getImpl();
		}

		if (companyService == null) {
			companyService = CompanyServiceFactory.getImpl();
		}

		if (companyPersistence == null) {
			companyPersistence = CompanyUtil.getPersistence();
		}

		if (groupLocalService == null) {
			groupLocalService = GroupLocalServiceFactory.getImpl();
		}

		if (groupService == null) {
			groupService = GroupServiceFactory.getImpl();
		}

		if (groupPersistence == null) {
			groupPersistence = GroupUtil.getPersistence();
		}

		if (groupFinder == null) {
			groupFinder = GroupFinderUtil.getFinder();
		}

		if (userLocalService == null) {
			userLocalService = UserLocalServiceFactory.getImpl();
		}

		if (userService == null) {
			userService = UserServiceFactory.getImpl();
		}

		if (userPersistence == null) {
			userPersistence = UserUtil.getPersistence();
		}

		if (userFinder == null) {
			userFinder = UserFinderUtil.getFinder();
		}

		if (blogsEntryLocalService == null) {
			blogsEntryLocalService = BlogsEntryLocalServiceFactory.getImpl();
		}

		if (blogsEntryService == null) {
			blogsEntryService = BlogsEntryServiceFactory.getImpl();
		}

		if (blogsEntryPersistence == null) {
			blogsEntryPersistence = BlogsEntryUtil.getPersistence();
		}

		if (blogsEntryFinder == null) {
			blogsEntryFinder = BlogsEntryFinderUtil.getFinder();
		}

		if (bookmarksEntryLocalService == null) {
			bookmarksEntryLocalService = BookmarksEntryLocalServiceFactory.getImpl();
		}

		if (bookmarksEntryService == null) {
			bookmarksEntryService = BookmarksEntryServiceFactory.getImpl();
		}

		if (bookmarksEntryPersistence == null) {
			bookmarksEntryPersistence = BookmarksEntryUtil.getPersistence();
		}

		if (bookmarksEntryFinder == null) {
			bookmarksEntryFinder = BookmarksEntryFinderUtil.getFinder();
		}

		if (dlFileEntryLocalService == null) {
			dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getImpl();
		}

		if (dlFileEntryService == null) {
			dlFileEntryService = DLFileEntryServiceFactory.getImpl();
		}

		if (dlFileEntryPersistence == null) {
			dlFileEntryPersistence = DLFileEntryUtil.getPersistence();
		}

		if (dlFileEntryFinder == null) {
			dlFileEntryFinder = DLFileEntryFinderUtil.getFinder();
		}

		if (journalArticleLocalService == null) {
			journalArticleLocalService = JournalArticleLocalServiceFactory.getImpl();
		}

		if (journalArticleService == null) {
			journalArticleService = JournalArticleServiceFactory.getImpl();
		}

		if (journalArticlePersistence == null) {
			journalArticlePersistence = JournalArticleUtil.getPersistence();
		}

		if (journalArticleFinder == null) {
			journalArticleFinder = JournalArticleFinderUtil.getFinder();
		}

		if (journalArticleResourceLocalService == null) {
			journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getImpl();
		}

		if (journalArticleResourcePersistence == null) {
			journalArticleResourcePersistence = JournalArticleResourceUtil.getPersistence();
		}

		if (mbMessageLocalService == null) {
			mbMessageLocalService = MBMessageLocalServiceFactory.getImpl();
		}

		if (mbMessageService == null) {
			mbMessageService = MBMessageServiceFactory.getImpl();
		}

		if (mbMessagePersistence == null) {
			mbMessagePersistence = MBMessageUtil.getPersistence();
		}

		if (mbMessageFinder == null) {
			mbMessageFinder = MBMessageFinderUtil.getFinder();
		}

		if (wikiPageLocalService == null) {
			wikiPageLocalService = WikiPageLocalServiceFactory.getImpl();
		}

		if (wikiPageService == null) {
			wikiPageService = WikiPageServiceFactory.getImpl();
		}

		if (wikiPagePersistence == null) {
			wikiPagePersistence = WikiPageUtil.getPersistence();
		}

		if (wikiPageFinder == null) {
			wikiPageFinder = WikiPageFinderUtil.getFinder();
		}

		if (wikiPageResourceLocalService == null) {
			wikiPageResourceLocalService = WikiPageResourceLocalServiceFactory.getImpl();
		}

		if (wikiPageResourcePersistence == null) {
			wikiPageResourcePersistence = WikiPageResourceUtil.getPersistence();
		}
	}

	protected TagsAssetLocalService tagsAssetLocalService;
	protected TagsAssetPersistence tagsAssetPersistence;
	protected TagsAssetFinder tagsAssetFinder;
	protected TagsEntryLocalService tagsEntryLocalService;
	protected TagsEntryService tagsEntryService;
	protected TagsEntryPersistence tagsEntryPersistence;
	protected TagsEntryFinder tagsEntryFinder;
	protected TagsPropertyLocalService tagsPropertyLocalService;
	protected TagsPropertyService tagsPropertyService;
	protected TagsPropertyPersistence tagsPropertyPersistence;
	protected TagsPropertyFinder tagsPropertyFinder;
	protected TagsPropertyKeyFinder tagsPropertyKeyFinder;
	protected TagsSourceLocalService tagsSourceLocalService;
	protected TagsSourceService tagsSourceService;
	protected TagsSourcePersistence tagsSourcePersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
	protected CompanyLocalService companyLocalService;
	protected CompanyService companyService;
	protected CompanyPersistence companyPersistence;
	protected GroupLocalService groupLocalService;
	protected GroupService groupService;
	protected GroupPersistence groupPersistence;
	protected GroupFinder groupFinder;
	protected UserLocalService userLocalService;
	protected UserService userService;
	protected UserPersistence userPersistence;
	protected UserFinder userFinder;
	protected BlogsEntryLocalService blogsEntryLocalService;
	protected BlogsEntryService blogsEntryService;
	protected BlogsEntryPersistence blogsEntryPersistence;
	protected BlogsEntryFinder blogsEntryFinder;
	protected BookmarksEntryLocalService bookmarksEntryLocalService;
	protected BookmarksEntryService bookmarksEntryService;
	protected BookmarksEntryPersistence bookmarksEntryPersistence;
	protected BookmarksEntryFinder bookmarksEntryFinder;
	protected DLFileEntryLocalService dlFileEntryLocalService;
	protected DLFileEntryService dlFileEntryService;
	protected DLFileEntryPersistence dlFileEntryPersistence;
	protected DLFileEntryFinder dlFileEntryFinder;
	protected JournalArticleLocalService journalArticleLocalService;
	protected JournalArticleService journalArticleService;
	protected JournalArticlePersistence journalArticlePersistence;
	protected JournalArticleFinder journalArticleFinder;
	protected JournalArticleResourceLocalService journalArticleResourceLocalService;
	protected JournalArticleResourcePersistence journalArticleResourcePersistence;
	protected MBMessageLocalService mbMessageLocalService;
	protected MBMessageService mbMessageService;
	protected MBMessagePersistence mbMessagePersistence;
	protected MBMessageFinder mbMessageFinder;
	protected WikiPageLocalService wikiPageLocalService;
	protected WikiPageService wikiPageService;
	protected WikiPagePersistence wikiPagePersistence;
	protected WikiPageFinder wikiPageFinder;
	protected WikiPageResourceLocalService wikiPageResourceLocalService;
	protected WikiPageResourcePersistence wikiPageResourcePersistence;
}