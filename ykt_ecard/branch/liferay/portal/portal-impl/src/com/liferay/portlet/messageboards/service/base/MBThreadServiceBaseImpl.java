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

package com.liferay.portlet.messageboards.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.documentlibrary.service.DLLocalService;
import com.liferay.documentlibrary.service.DLLocalServiceFactory;
import com.liferay.documentlibrary.service.DLService;
import com.liferay.documentlibrary.service.DLServiceFactory;

import com.liferay.portal.service.ActivityTrackerLocalService;
import com.liferay.portal.service.ActivityTrackerLocalServiceFactory;
import com.liferay.portal.service.ResourceLocalService;
import com.liferay.portal.service.ResourceLocalServiceFactory;
import com.liferay.portal.service.ResourceService;
import com.liferay.portal.service.ResourceServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.persistence.ActivityTrackerFinder;
import com.liferay.portal.service.persistence.ActivityTrackerFinderUtil;
import com.liferay.portal.service.persistence.ActivityTrackerPersistence;
import com.liferay.portal.service.persistence.ActivityTrackerUtil;
import com.liferay.portal.service.persistence.ResourceFinder;
import com.liferay.portal.service.persistence.ResourceFinderUtil;
import com.liferay.portal.service.persistence.ResourcePersistence;
import com.liferay.portal.service.persistence.ResourceUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserUtil;

import com.liferay.portlet.messageboards.service.MBBanLocalService;
import com.liferay.portlet.messageboards.service.MBBanLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBBanService;
import com.liferay.portlet.messageboards.service.MBBanServiceFactory;
import com.liferay.portlet.messageboards.service.MBCategoryLocalService;
import com.liferay.portlet.messageboards.service.MBCategoryLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBCategoryService;
import com.liferay.portlet.messageboards.service.MBCategoryServiceFactory;
import com.liferay.portlet.messageboards.service.MBMessageFlagLocalService;
import com.liferay.portlet.messageboards.service.MBMessageFlagLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBMessageLocalService;
import com.liferay.portlet.messageboards.service.MBMessageLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBMessageService;
import com.liferay.portlet.messageboards.service.MBMessageServiceFactory;
import com.liferay.portlet.messageboards.service.MBStatsUserLocalService;
import com.liferay.portlet.messageboards.service.MBStatsUserLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBThreadLocalService;
import com.liferay.portlet.messageboards.service.MBThreadLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBThreadService;
import com.liferay.portlet.messageboards.service.persistence.MBBanPersistence;
import com.liferay.portlet.messageboards.service.persistence.MBBanUtil;
import com.liferay.portlet.messageboards.service.persistence.MBCategoryFinder;
import com.liferay.portlet.messageboards.service.persistence.MBCategoryFinderUtil;
import com.liferay.portlet.messageboards.service.persistence.MBCategoryPersistence;
import com.liferay.portlet.messageboards.service.persistence.MBCategoryUtil;
import com.liferay.portlet.messageboards.service.persistence.MBDiscussionPersistence;
import com.liferay.portlet.messageboards.service.persistence.MBDiscussionUtil;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFinder;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFinderUtil;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinder;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagFinderUtil;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPersistence;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagUtil;
import com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence;
import com.liferay.portlet.messageboards.service.persistence.MBMessageUtil;
import com.liferay.portlet.messageboards.service.persistence.MBStatsUserPersistence;
import com.liferay.portlet.messageboards.service.persistence.MBStatsUserUtil;
import com.liferay.portlet.messageboards.service.persistence.MBThreadFinder;
import com.liferay.portlet.messageboards.service.persistence.MBThreadFinderUtil;
import com.liferay.portlet.messageboards.service.persistence.MBThreadPersistence;
import com.liferay.portlet.messageboards.service.persistence.MBThreadUtil;
import com.liferay.portlet.tags.service.TagsAssetLocalService;
import com.liferay.portlet.tags.service.TagsAssetLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsAssetService;
import com.liferay.portlet.tags.service.TagsAssetServiceFactory;
import com.liferay.portlet.tags.service.persistence.TagsAssetFinder;
import com.liferay.portlet.tags.service.persistence.TagsAssetFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsAssetPersistence;
import com.liferay.portlet.tags.service.persistence.TagsAssetUtil;

import org.springframework.beans.factory.InitializingBean;

/**
 * <a href="MBThreadServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class MBThreadServiceBaseImpl extends PrincipalBean
	implements MBThreadService, InitializingBean {
	public MBBanLocalService getMBBanLocalService() {
		return mbBanLocalService;
	}

	public void setMBBanLocalService(MBBanLocalService mbBanLocalService) {
		this.mbBanLocalService = mbBanLocalService;
	}

	public MBBanService getMBBanService() {
		return mbBanService;
	}

	public void setMBBanService(MBBanService mbBanService) {
		this.mbBanService = mbBanService;
	}

	public MBBanPersistence getMBBanPersistence() {
		return mbBanPersistence;
	}

	public void setMBBanPersistence(MBBanPersistence mbBanPersistence) {
		this.mbBanPersistence = mbBanPersistence;
	}

	public MBCategoryLocalService getMBCategoryLocalService() {
		return mbCategoryLocalService;
	}

	public void setMBCategoryLocalService(
		MBCategoryLocalService mbCategoryLocalService) {
		this.mbCategoryLocalService = mbCategoryLocalService;
	}

	public MBCategoryService getMBCategoryService() {
		return mbCategoryService;
	}

	public void setMBCategoryService(MBCategoryService mbCategoryService) {
		this.mbCategoryService = mbCategoryService;
	}

	public MBCategoryPersistence getMBCategoryPersistence() {
		return mbCategoryPersistence;
	}

	public void setMBCategoryPersistence(
		MBCategoryPersistence mbCategoryPersistence) {
		this.mbCategoryPersistence = mbCategoryPersistence;
	}

	public MBCategoryFinder getMBCategoryFinder() {
		return mbCategoryFinder;
	}

	public void setMBCategoryFinder(MBCategoryFinder mbCategoryFinder) {
		this.mbCategoryFinder = mbCategoryFinder;
	}

	public MBDiscussionPersistence getMBDiscussionPersistence() {
		return mbDiscussionPersistence;
	}

	public void setMBDiscussionPersistence(
		MBDiscussionPersistence mbDiscussionPersistence) {
		this.mbDiscussionPersistence = mbDiscussionPersistence;
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

	public MBMessageFlagLocalService getMBMessageFlagLocalService() {
		return mbMessageFlagLocalService;
	}

	public void setMBMessageFlagLocalService(
		MBMessageFlagLocalService mbMessageFlagLocalService) {
		this.mbMessageFlagLocalService = mbMessageFlagLocalService;
	}

	public MBMessageFlagPersistence getMBMessageFlagPersistence() {
		return mbMessageFlagPersistence;
	}

	public void setMBMessageFlagPersistence(
		MBMessageFlagPersistence mbMessageFlagPersistence) {
		this.mbMessageFlagPersistence = mbMessageFlagPersistence;
	}

	public MBMessageFlagFinder getMBMessageFlagFinder() {
		return mbMessageFlagFinder;
	}

	public void setMBMessageFlagFinder(MBMessageFlagFinder mbMessageFlagFinder) {
		this.mbMessageFlagFinder = mbMessageFlagFinder;
	}

	public MBStatsUserLocalService getMBStatsUserLocalService() {
		return mbStatsUserLocalService;
	}

	public void setMBStatsUserLocalService(
		MBStatsUserLocalService mbStatsUserLocalService) {
		this.mbStatsUserLocalService = mbStatsUserLocalService;
	}

	public MBStatsUserPersistence getMBStatsUserPersistence() {
		return mbStatsUserPersistence;
	}

	public void setMBStatsUserPersistence(
		MBStatsUserPersistence mbStatsUserPersistence) {
		this.mbStatsUserPersistence = mbStatsUserPersistence;
	}

	public MBThreadLocalService getMBThreadLocalService() {
		return mbThreadLocalService;
	}

	public void setMBThreadLocalService(
		MBThreadLocalService mbThreadLocalService) {
		this.mbThreadLocalService = mbThreadLocalService;
	}

	public MBThreadPersistence getMBThreadPersistence() {
		return mbThreadPersistence;
	}

	public void setMBThreadPersistence(MBThreadPersistence mbThreadPersistence) {
		this.mbThreadPersistence = mbThreadPersistence;
	}

	public MBThreadFinder getMBThreadFinder() {
		return mbThreadFinder;
	}

	public void setMBThreadFinder(MBThreadFinder mbThreadFinder) {
		this.mbThreadFinder = mbThreadFinder;
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

	public DLLocalService getDLLocalService() {
		return dlLocalService;
	}

	public void setDLLocalService(DLLocalService dlLocalService) {
		this.dlLocalService = dlLocalService;
	}

	public DLService getDLService() {
		return dlService;
	}

	public void setDLService(DLService dlService) {
		this.dlService = dlService;
	}

	public ActivityTrackerLocalService getActivityTrackerLocalService() {
		return activityTrackerLocalService;
	}

	public void setActivityTrackerLocalService(
		ActivityTrackerLocalService activityTrackerLocalService) {
		this.activityTrackerLocalService = activityTrackerLocalService;
	}

	public ActivityTrackerPersistence getActivityTrackerPersistence() {
		return activityTrackerPersistence;
	}

	public void setActivityTrackerPersistence(
		ActivityTrackerPersistence activityTrackerPersistence) {
		this.activityTrackerPersistence = activityTrackerPersistence;
	}

	public ActivityTrackerFinder getActivityTrackerFinder() {
		return activityTrackerFinder;
	}

	public void setActivityTrackerFinder(
		ActivityTrackerFinder activityTrackerFinder) {
		this.activityTrackerFinder = activityTrackerFinder;
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

	public TagsAssetLocalService getTagsAssetLocalService() {
		return tagsAssetLocalService;
	}

	public void setTagsAssetLocalService(
		TagsAssetLocalService tagsAssetLocalService) {
		this.tagsAssetLocalService = tagsAssetLocalService;
	}

	public TagsAssetService getTagsAssetService() {
		return tagsAssetService;
	}

	public void setTagsAssetService(TagsAssetService tagsAssetService) {
		this.tagsAssetService = tagsAssetService;
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

	public void afterPropertiesSet() {
		if (mbBanLocalService == null) {
			mbBanLocalService = MBBanLocalServiceFactory.getImpl();
		}

		if (mbBanService == null) {
			mbBanService = MBBanServiceFactory.getImpl();
		}

		if (mbBanPersistence == null) {
			mbBanPersistence = MBBanUtil.getPersistence();
		}

		if (mbCategoryLocalService == null) {
			mbCategoryLocalService = MBCategoryLocalServiceFactory.getImpl();
		}

		if (mbCategoryService == null) {
			mbCategoryService = MBCategoryServiceFactory.getImpl();
		}

		if (mbCategoryPersistence == null) {
			mbCategoryPersistence = MBCategoryUtil.getPersistence();
		}

		if (mbCategoryFinder == null) {
			mbCategoryFinder = MBCategoryFinderUtil.getFinder();
		}

		if (mbDiscussionPersistence == null) {
			mbDiscussionPersistence = MBDiscussionUtil.getPersistence();
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

		if (mbMessageFlagLocalService == null) {
			mbMessageFlagLocalService = MBMessageFlagLocalServiceFactory.getImpl();
		}

		if (mbMessageFlagPersistence == null) {
			mbMessageFlagPersistence = MBMessageFlagUtil.getPersistence();
		}

		if (mbMessageFlagFinder == null) {
			mbMessageFlagFinder = MBMessageFlagFinderUtil.getFinder();
		}

		if (mbStatsUserLocalService == null) {
			mbStatsUserLocalService = MBStatsUserLocalServiceFactory.getImpl();
		}

		if (mbStatsUserPersistence == null) {
			mbStatsUserPersistence = MBStatsUserUtil.getPersistence();
		}

		if (mbThreadLocalService == null) {
			mbThreadLocalService = MBThreadLocalServiceFactory.getImpl();
		}

		if (mbThreadPersistence == null) {
			mbThreadPersistence = MBThreadUtil.getPersistence();
		}

		if (mbThreadFinder == null) {
			mbThreadFinder = MBThreadFinderUtil.getFinder();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
		}

		if (dlLocalService == null) {
			dlLocalService = DLLocalServiceFactory.getImpl();
		}

		if (dlService == null) {
			dlService = DLServiceFactory.getImpl();
		}

		if (activityTrackerLocalService == null) {
			activityTrackerLocalService = ActivityTrackerLocalServiceFactory.getImpl();
		}

		if (activityTrackerPersistence == null) {
			activityTrackerPersistence = ActivityTrackerUtil.getPersistence();
		}

		if (activityTrackerFinder == null) {
			activityTrackerFinder = ActivityTrackerFinderUtil.getFinder();
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

		if (tagsAssetLocalService == null) {
			tagsAssetLocalService = TagsAssetLocalServiceFactory.getImpl();
		}

		if (tagsAssetService == null) {
			tagsAssetService = TagsAssetServiceFactory.getImpl();
		}

		if (tagsAssetPersistence == null) {
			tagsAssetPersistence = TagsAssetUtil.getPersistence();
		}

		if (tagsAssetFinder == null) {
			tagsAssetFinder = TagsAssetFinderUtil.getFinder();
		}
	}

	protected MBBanLocalService mbBanLocalService;
	protected MBBanService mbBanService;
	protected MBBanPersistence mbBanPersistence;
	protected MBCategoryLocalService mbCategoryLocalService;
	protected MBCategoryService mbCategoryService;
	protected MBCategoryPersistence mbCategoryPersistence;
	protected MBCategoryFinder mbCategoryFinder;
	protected MBDiscussionPersistence mbDiscussionPersistence;
	protected MBMessageLocalService mbMessageLocalService;
	protected MBMessageService mbMessageService;
	protected MBMessagePersistence mbMessagePersistence;
	protected MBMessageFinder mbMessageFinder;
	protected MBMessageFlagLocalService mbMessageFlagLocalService;
	protected MBMessageFlagPersistence mbMessageFlagPersistence;
	protected MBMessageFlagFinder mbMessageFlagFinder;
	protected MBStatsUserLocalService mbStatsUserLocalService;
	protected MBStatsUserPersistence mbStatsUserPersistence;
	protected MBThreadLocalService mbThreadLocalService;
	protected MBThreadPersistence mbThreadPersistence;
	protected MBThreadFinder mbThreadFinder;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
	protected DLLocalService dlLocalService;
	protected DLService dlService;
	protected ActivityTrackerLocalService activityTrackerLocalService;
	protected ActivityTrackerPersistence activityTrackerPersistence;
	protected ActivityTrackerFinder activityTrackerFinder;
	protected ResourceLocalService resourceLocalService;
	protected ResourceService resourceService;
	protected ResourcePersistence resourcePersistence;
	protected ResourceFinder resourceFinder;
	protected UserLocalService userLocalService;
	protected UserService userService;
	protected UserPersistence userPersistence;
	protected UserFinder userFinder;
	protected TagsAssetLocalService tagsAssetLocalService;
	protected TagsAssetService tagsAssetService;
	protected TagsAssetPersistence tagsAssetPersistence;
	protected TagsAssetFinder tagsAssetFinder;
}