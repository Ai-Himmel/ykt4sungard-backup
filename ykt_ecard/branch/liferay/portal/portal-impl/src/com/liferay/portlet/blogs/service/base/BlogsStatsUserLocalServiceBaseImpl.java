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

package com.liferay.portlet.blogs.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.service.GroupLocalService;
import com.liferay.portal.service.GroupLocalServiceFactory;
import com.liferay.portal.service.GroupService;
import com.liferay.portal.service.GroupServiceFactory;
import com.liferay.portal.service.persistence.GroupFinder;
import com.liferay.portal.service.persistence.GroupFinderUtil;
import com.liferay.portal.service.persistence.GroupPersistence;
import com.liferay.portal.service.persistence.GroupUtil;

import com.liferay.portlet.blogs.model.BlogsStatsUser;
import com.liferay.portlet.blogs.model.impl.BlogsStatsUserImpl;
import com.liferay.portlet.blogs.service.BlogsEntryLocalService;
import com.liferay.portlet.blogs.service.BlogsEntryLocalServiceFactory;
import com.liferay.portlet.blogs.service.BlogsEntryService;
import com.liferay.portlet.blogs.service.BlogsEntryServiceFactory;
import com.liferay.portlet.blogs.service.BlogsStatsUserLocalService;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryFinder;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryFinderUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinder;
import com.liferay.portlet.blogs.service.persistence.BlogsStatsUserFinderUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsStatsUserPersistence;
import com.liferay.portlet.blogs.service.persistence.BlogsStatsUserUtil;

import org.springframework.beans.factory.InitializingBean;

import java.util.List;

/**
 * <a href="BlogsStatsUserLocalServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class BlogsStatsUserLocalServiceBaseImpl
	implements BlogsStatsUserLocalService, InitializingBean {
	public BlogsStatsUser addBlogsStatsUser(BlogsStatsUser model)
		throws SystemException {
		BlogsStatsUser blogsStatsUser = new BlogsStatsUserImpl();

		blogsStatsUser.setNew(true);

		blogsStatsUser.setStatsUserId(model.getStatsUserId());
		blogsStatsUser.setGroupId(model.getGroupId());
		blogsStatsUser.setCompanyId(model.getCompanyId());
		blogsStatsUser.setUserId(model.getUserId());
		blogsStatsUser.setEntryCount(model.getEntryCount());
		blogsStatsUser.setLastPostDate(model.getLastPostDate());
		blogsStatsUser.setRatingsTotalEntries(model.getRatingsTotalEntries());
		blogsStatsUser.setRatingsTotalScore(model.getRatingsTotalScore());
		blogsStatsUser.setRatingsAverageScore(model.getRatingsAverageScore());

		return blogsStatsUserPersistence.update(blogsStatsUser);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		return blogsStatsUserPersistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		return blogsStatsUserPersistence.findWithDynamicQuery(queryInitializer,
			begin, end);
	}

	public BlogsStatsUser updateBlogsStatsUser(BlogsStatsUser model)
		throws SystemException {
		BlogsStatsUser blogsStatsUser = new BlogsStatsUserImpl();

		blogsStatsUser.setNew(false);

		blogsStatsUser.setStatsUserId(model.getStatsUserId());
		blogsStatsUser.setGroupId(model.getGroupId());
		blogsStatsUser.setCompanyId(model.getCompanyId());
		blogsStatsUser.setUserId(model.getUserId());
		blogsStatsUser.setEntryCount(model.getEntryCount());
		blogsStatsUser.setLastPostDate(model.getLastPostDate());
		blogsStatsUser.setRatingsTotalEntries(model.getRatingsTotalEntries());
		blogsStatsUser.setRatingsTotalScore(model.getRatingsTotalScore());
		blogsStatsUser.setRatingsAverageScore(model.getRatingsAverageScore());

		return blogsStatsUserPersistence.update(blogsStatsUser);
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

	public BlogsStatsUserPersistence getBlogsStatsUserPersistence() {
		return blogsStatsUserPersistence;
	}

	public void setBlogsStatsUserPersistence(
		BlogsStatsUserPersistence blogsStatsUserPersistence) {
		this.blogsStatsUserPersistence = blogsStatsUserPersistence;
	}

	public BlogsStatsUserFinder getBlogsStatsUserFinder() {
		return blogsStatsUserFinder;
	}

	public void setBlogsStatsUserFinder(
		BlogsStatsUserFinder blogsStatsUserFinder) {
		this.blogsStatsUserFinder = blogsStatsUserFinder;
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

	public void afterPropertiesSet() {
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

		if (blogsStatsUserPersistence == null) {
			blogsStatsUserPersistence = BlogsStatsUserUtil.getPersistence();
		}

		if (blogsStatsUserFinder == null) {
			blogsStatsUserFinder = BlogsStatsUserFinderUtil.getFinder();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
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
	}

	protected BlogsEntryLocalService blogsEntryLocalService;
	protected BlogsEntryService blogsEntryService;
	protected BlogsEntryPersistence blogsEntryPersistence;
	protected BlogsEntryFinder blogsEntryFinder;
	protected BlogsStatsUserPersistence blogsStatsUserPersistence;
	protected BlogsStatsUserFinder blogsStatsUserFinder;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
	protected GroupLocalService groupLocalService;
	protected GroupService groupService;
	protected GroupPersistence groupPersistence;
	protected GroupFinder groupFinder;
}