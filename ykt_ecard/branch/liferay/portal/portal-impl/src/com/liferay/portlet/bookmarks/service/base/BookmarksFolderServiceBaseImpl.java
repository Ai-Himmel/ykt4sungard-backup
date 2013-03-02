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

package com.liferay.portlet.bookmarks.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.portal.service.ResourceLocalService;
import com.liferay.portal.service.ResourceLocalServiceFactory;
import com.liferay.portal.service.ResourceService;
import com.liferay.portal.service.ResourceServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.persistence.ResourceFinder;
import com.liferay.portal.service.persistence.ResourceFinderUtil;
import com.liferay.portal.service.persistence.ResourcePersistence;
import com.liferay.portal.service.persistence.ResourceUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserUtil;

import com.liferay.portlet.bookmarks.service.BookmarksEntryLocalService;
import com.liferay.portlet.bookmarks.service.BookmarksEntryLocalServiceFactory;
import com.liferay.portlet.bookmarks.service.BookmarksEntryService;
import com.liferay.portlet.bookmarks.service.BookmarksEntryServiceFactory;
import com.liferay.portlet.bookmarks.service.BookmarksFolderLocalService;
import com.liferay.portlet.bookmarks.service.BookmarksFolderLocalServiceFactory;
import com.liferay.portlet.bookmarks.service.BookmarksFolderService;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinder;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinderUtil;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistence;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryUtil;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderPersistence;
import com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderUtil;
import com.liferay.portlet.tags.service.TagsEntryLocalService;
import com.liferay.portlet.tags.service.TagsEntryLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsEntryService;
import com.liferay.portlet.tags.service.TagsEntryServiceFactory;
import com.liferay.portlet.tags.service.persistence.TagsEntryFinder;
import com.liferay.portlet.tags.service.persistence.TagsEntryFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsEntryPersistence;
import com.liferay.portlet.tags.service.persistence.TagsEntryUtil;

import org.springframework.beans.factory.InitializingBean;

/**
 * <a href="BookmarksFolderServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class BookmarksFolderServiceBaseImpl extends PrincipalBean
	implements BookmarksFolderService, InitializingBean {
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

	public BookmarksFolderLocalService getBookmarksFolderLocalService() {
		return bookmarksFolderLocalService;
	}

	public void setBookmarksFolderLocalService(
		BookmarksFolderLocalService bookmarksFolderLocalService) {
		this.bookmarksFolderLocalService = bookmarksFolderLocalService;
	}

	public BookmarksFolderPersistence getBookmarksFolderPersistence() {
		return bookmarksFolderPersistence;
	}

	public void setBookmarksFolderPersistence(
		BookmarksFolderPersistence bookmarksFolderPersistence) {
		this.bookmarksFolderPersistence = bookmarksFolderPersistence;
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

	public ResourceLocalService getResourceLocalService() {
		return resourceLocalService;
	}

	public void setResourceLocalService(
		ResourceLocalService resourceLocalService) {
		this.resourceLocalService = resourceLocalService;
	}

	public ResourceService getResourceService() {
		return resourceService;
	}

	public void setResourceService(ResourceService resourceService) {
		this.resourceService = resourceService;
	}

	public ResourcePersistence getResourcePersistence() {
		return resourcePersistence;
	}

	public void setResourcePersistence(ResourcePersistence resourcePersistence) {
		this.resourcePersistence = resourcePersistence;
	}

	public ResourceFinder getResourceFinder() {
		return resourceFinder;
	}

	public void setResourceFinder(ResourceFinder resourceFinder) {
		this.resourceFinder = resourceFinder;
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

	public void afterPropertiesSet() {
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

		if (bookmarksFolderLocalService == null) {
			bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getImpl();
		}

		if (bookmarksFolderPersistence == null) {
			bookmarksFolderPersistence = BookmarksFolderUtil.getPersistence();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
		}

		if (resourceLocalService == null) {
			resourceLocalService = ResourceLocalServiceFactory.getImpl();
		}

		if (resourceService == null) {
			resourceService = ResourceServiceFactory.getImpl();
		}

		if (resourcePersistence == null) {
			resourcePersistence = ResourceUtil.getPersistence();
		}

		if (resourceFinder == null) {
			resourceFinder = ResourceFinderUtil.getFinder();
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
	}

	protected BookmarksEntryLocalService bookmarksEntryLocalService;
	protected BookmarksEntryService bookmarksEntryService;
	protected BookmarksEntryPersistence bookmarksEntryPersistence;
	protected BookmarksEntryFinder bookmarksEntryFinder;
	protected BookmarksFolderLocalService bookmarksFolderLocalService;
	protected BookmarksFolderPersistence bookmarksFolderPersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
	protected ResourceLocalService resourceLocalService;
	protected ResourceService resourceService;
	protected ResourcePersistence resourcePersistence;
	protected ResourceFinder resourceFinder;
	protected UserLocalService userLocalService;
	protected UserService userService;
	protected UserPersistence userPersistence;
	protected UserFinder userFinder;
	protected TagsEntryLocalService tagsEntryLocalService;
	protected TagsEntryService tagsEntryService;
	protected TagsEntryPersistence tagsEntryPersistence;
	protected TagsEntryFinder tagsEntryFinder;
}