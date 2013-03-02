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

package com.liferay.portlet.journal.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.service.ResourceLocalService;
import com.liferay.portal.service.ResourceLocalServiceFactory;
import com.liferay.portal.service.ResourceService;
import com.liferay.portal.service.ResourceServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.persistence.ResourceFinder;
import com.liferay.portal.service.persistence.ResourceFinderUtil;
import com.liferay.portal.service.persistence.ResourcePersistence;
import com.liferay.portal.service.persistence.ResourceUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserUtil;

import com.liferay.portlet.journal.model.JournalFeed;
import com.liferay.portlet.journal.model.impl.JournalFeedImpl;
import com.liferay.portlet.journal.service.JournalArticleImageLocalService;
import com.liferay.portlet.journal.service.JournalArticleImageLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalArticleLocalService;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalArticleResourceLocalService;
import com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalArticleService;
import com.liferay.portlet.journal.service.JournalArticleServiceFactory;
import com.liferay.portlet.journal.service.JournalContentSearchLocalService;
import com.liferay.portlet.journal.service.JournalContentSearchLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalFeedLocalService;
import com.liferay.portlet.journal.service.JournalStructureLocalService;
import com.liferay.portlet.journal.service.JournalStructureLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalStructureService;
import com.liferay.portlet.journal.service.JournalStructureServiceFactory;
import com.liferay.portlet.journal.service.JournalTemplateLocalService;
import com.liferay.portlet.journal.service.JournalTemplateLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalTemplateService;
import com.liferay.portlet.journal.service.JournalTemplateServiceFactory;
import com.liferay.portlet.journal.service.persistence.JournalArticleFinder;
import com.liferay.portlet.journal.service.persistence.JournalArticleFinderUtil;
import com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence;
import com.liferay.portlet.journal.service.persistence.JournalArticleImageUtil;
import com.liferay.portlet.journal.service.persistence.JournalArticlePersistence;
import com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence;
import com.liferay.portlet.journal.service.persistence.JournalArticleResourceUtil;
import com.liferay.portlet.journal.service.persistence.JournalArticleUtil;
import com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence;
import com.liferay.portlet.journal.service.persistence.JournalContentSearchUtil;
import com.liferay.portlet.journal.service.persistence.JournalFeedFinder;
import com.liferay.portlet.journal.service.persistence.JournalFeedFinderUtil;
import com.liferay.portlet.journal.service.persistence.JournalFeedPersistence;
import com.liferay.portlet.journal.service.persistence.JournalFeedUtil;
import com.liferay.portlet.journal.service.persistence.JournalStructureFinder;
import com.liferay.portlet.journal.service.persistence.JournalStructureFinderUtil;
import com.liferay.portlet.journal.service.persistence.JournalStructurePersistence;
import com.liferay.portlet.journal.service.persistence.JournalStructureUtil;
import com.liferay.portlet.journal.service.persistence.JournalTemplateFinder;
import com.liferay.portlet.journal.service.persistence.JournalTemplateFinderUtil;
import com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence;
import com.liferay.portlet.journal.service.persistence.JournalTemplateUtil;

import org.springframework.beans.factory.InitializingBean;

import java.util.List;

/**
 * <a href="JournalFeedLocalServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class JournalFeedLocalServiceBaseImpl
	implements JournalFeedLocalService, InitializingBean {
	public JournalFeed addJournalFeed(JournalFeed model)
		throws SystemException {
		JournalFeed journalFeed = new JournalFeedImpl();

		journalFeed.setNew(true);

		journalFeed.setUuid(model.getUuid());
		journalFeed.setId(model.getId());
		journalFeed.setGroupId(model.getGroupId());
		journalFeed.setCompanyId(model.getCompanyId());
		journalFeed.setUserId(model.getUserId());
		journalFeed.setUserName(model.getUserName());
		journalFeed.setCreateDate(model.getCreateDate());
		journalFeed.setModifiedDate(model.getModifiedDate());
		journalFeed.setFeedId(model.getFeedId());
		journalFeed.setName(model.getName());
		journalFeed.setDescription(model.getDescription());
		journalFeed.setType(model.getType());
		journalFeed.setStructureId(model.getStructureId());
		journalFeed.setTemplateId(model.getTemplateId());
		journalFeed.setRendererTemplateId(model.getRendererTemplateId());
		journalFeed.setDelta(model.getDelta());
		journalFeed.setOrderByCol(model.getOrderByCol());
		journalFeed.setOrderByType(model.getOrderByType());
		journalFeed.setTargetLayoutFriendlyUrl(model.getTargetLayoutFriendlyUrl());
		journalFeed.setTargetPortletId(model.getTargetPortletId());
		journalFeed.setContentField(model.getContentField());
		journalFeed.setFeedType(model.getFeedType());
		journalFeed.setFeedVersion(model.getFeedVersion());

		return journalFeedPersistence.update(journalFeed);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		return journalFeedPersistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		return journalFeedPersistence.findWithDynamicQuery(queryInitializer,
			begin, end);
	}

	public JournalFeed updateJournalFeed(JournalFeed model)
		throws SystemException {
		JournalFeed journalFeed = new JournalFeedImpl();

		journalFeed.setNew(false);

		journalFeed.setUuid(model.getUuid());
		journalFeed.setId(model.getId());
		journalFeed.setGroupId(model.getGroupId());
		journalFeed.setCompanyId(model.getCompanyId());
		journalFeed.setUserId(model.getUserId());
		journalFeed.setUserName(model.getUserName());
		journalFeed.setCreateDate(model.getCreateDate());
		journalFeed.setModifiedDate(model.getModifiedDate());
		journalFeed.setFeedId(model.getFeedId());
		journalFeed.setName(model.getName());
		journalFeed.setDescription(model.getDescription());
		journalFeed.setType(model.getType());
		journalFeed.setStructureId(model.getStructureId());
		journalFeed.setTemplateId(model.getTemplateId());
		journalFeed.setRendererTemplateId(model.getRendererTemplateId());
		journalFeed.setDelta(model.getDelta());
		journalFeed.setOrderByCol(model.getOrderByCol());
		journalFeed.setOrderByType(model.getOrderByType());
		journalFeed.setTargetLayoutFriendlyUrl(model.getTargetLayoutFriendlyUrl());
		journalFeed.setTargetPortletId(model.getTargetPortletId());
		journalFeed.setContentField(model.getContentField());
		journalFeed.setFeedType(model.getFeedType());
		journalFeed.setFeedVersion(model.getFeedVersion());

		return journalFeedPersistence.update(journalFeed);
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

	public JournalArticleImageLocalService getJournalArticleImageLocalService() {
		return journalArticleImageLocalService;
	}

	public void setJournalArticleImageLocalService(
		JournalArticleImageLocalService journalArticleImageLocalService) {
		this.journalArticleImageLocalService = journalArticleImageLocalService;
	}

	public JournalArticleImagePersistence getJournalArticleImagePersistence() {
		return journalArticleImagePersistence;
	}

	public void setJournalArticleImagePersistence(
		JournalArticleImagePersistence journalArticleImagePersistence) {
		this.journalArticleImagePersistence = journalArticleImagePersistence;
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

	public JournalContentSearchLocalService getJournalContentSearchLocalService() {
		return journalContentSearchLocalService;
	}

	public void setJournalContentSearchLocalService(
		JournalContentSearchLocalService journalContentSearchLocalService) {
		this.journalContentSearchLocalService = journalContentSearchLocalService;
	}

	public JournalContentSearchPersistence getJournalContentSearchPersistence() {
		return journalContentSearchPersistence;
	}

	public void setJournalContentSearchPersistence(
		JournalContentSearchPersistence journalContentSearchPersistence) {
		this.journalContentSearchPersistence = journalContentSearchPersistence;
	}

	public JournalFeedPersistence getJournalFeedPersistence() {
		return journalFeedPersistence;
	}

	public void setJournalFeedPersistence(
		JournalFeedPersistence journalFeedPersistence) {
		this.journalFeedPersistence = journalFeedPersistence;
	}

	public JournalFeedFinder getJournalFeedFinder() {
		return journalFeedFinder;
	}

	public void setJournalFeedFinder(JournalFeedFinder journalFeedFinder) {
		this.journalFeedFinder = journalFeedFinder;
	}

	public JournalStructureLocalService getJournalStructureLocalService() {
		return journalStructureLocalService;
	}

	public void setJournalStructureLocalService(
		JournalStructureLocalService journalStructureLocalService) {
		this.journalStructureLocalService = journalStructureLocalService;
	}

	public JournalStructureService getJournalStructureService() {
		return journalStructureService;
	}

	public void setJournalStructureService(
		JournalStructureService journalStructureService) {
		this.journalStructureService = journalStructureService;
	}

	public JournalStructurePersistence getJournalStructurePersistence() {
		return journalStructurePersistence;
	}

	public void setJournalStructurePersistence(
		JournalStructurePersistence journalStructurePersistence) {
		this.journalStructurePersistence = journalStructurePersistence;
	}

	public JournalStructureFinder getJournalStructureFinder() {
		return journalStructureFinder;
	}

	public void setJournalStructureFinder(
		JournalStructureFinder journalStructureFinder) {
		this.journalStructureFinder = journalStructureFinder;
	}

	public JournalTemplateLocalService getJournalTemplateLocalService() {
		return journalTemplateLocalService;
	}

	public void setJournalTemplateLocalService(
		JournalTemplateLocalService journalTemplateLocalService) {
		this.journalTemplateLocalService = journalTemplateLocalService;
	}

	public JournalTemplateService getJournalTemplateService() {
		return journalTemplateService;
	}

	public void setJournalTemplateService(
		JournalTemplateService journalTemplateService) {
		this.journalTemplateService = journalTemplateService;
	}

	public JournalTemplatePersistence getJournalTemplatePersistence() {
		return journalTemplatePersistence;
	}

	public void setJournalTemplatePersistence(
		JournalTemplatePersistence journalTemplatePersistence) {
		this.journalTemplatePersistence = journalTemplatePersistence;
	}

	public JournalTemplateFinder getJournalTemplateFinder() {
		return journalTemplateFinder;
	}

	public void setJournalTemplateFinder(
		JournalTemplateFinder journalTemplateFinder) {
		this.journalTemplateFinder = journalTemplateFinder;
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

	public void afterPropertiesSet() {
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

		if (journalArticleImageLocalService == null) {
			journalArticleImageLocalService = JournalArticleImageLocalServiceFactory.getImpl();
		}

		if (journalArticleImagePersistence == null) {
			journalArticleImagePersistence = JournalArticleImageUtil.getPersistence();
		}

		if (journalArticleResourceLocalService == null) {
			journalArticleResourceLocalService = JournalArticleResourceLocalServiceFactory.getImpl();
		}

		if (journalArticleResourcePersistence == null) {
			journalArticleResourcePersistence = JournalArticleResourceUtil.getPersistence();
		}

		if (journalContentSearchLocalService == null) {
			journalContentSearchLocalService = JournalContentSearchLocalServiceFactory.getImpl();
		}

		if (journalContentSearchPersistence == null) {
			journalContentSearchPersistence = JournalContentSearchUtil.getPersistence();
		}

		if (journalFeedPersistence == null) {
			journalFeedPersistence = JournalFeedUtil.getPersistence();
		}

		if (journalFeedFinder == null) {
			journalFeedFinder = JournalFeedFinderUtil.getFinder();
		}

		if (journalStructureLocalService == null) {
			journalStructureLocalService = JournalStructureLocalServiceFactory.getImpl();
		}

		if (journalStructureService == null) {
			journalStructureService = JournalStructureServiceFactory.getImpl();
		}

		if (journalStructurePersistence == null) {
			journalStructurePersistence = JournalStructureUtil.getPersistence();
		}

		if (journalStructureFinder == null) {
			journalStructureFinder = JournalStructureFinderUtil.getFinder();
		}

		if (journalTemplateLocalService == null) {
			journalTemplateLocalService = JournalTemplateLocalServiceFactory.getImpl();
		}

		if (journalTemplateService == null) {
			journalTemplateService = JournalTemplateServiceFactory.getImpl();
		}

		if (journalTemplatePersistence == null) {
			journalTemplatePersistence = JournalTemplateUtil.getPersistence();
		}

		if (journalTemplateFinder == null) {
			journalTemplateFinder = JournalTemplateFinderUtil.getFinder();
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
	}

	protected JournalArticleLocalService journalArticleLocalService;
	protected JournalArticleService journalArticleService;
	protected JournalArticlePersistence journalArticlePersistence;
	protected JournalArticleFinder journalArticleFinder;
	protected JournalArticleImageLocalService journalArticleImageLocalService;
	protected JournalArticleImagePersistence journalArticleImagePersistence;
	protected JournalArticleResourceLocalService journalArticleResourceLocalService;
	protected JournalArticleResourcePersistence journalArticleResourcePersistence;
	protected JournalContentSearchLocalService journalContentSearchLocalService;
	protected JournalContentSearchPersistence journalContentSearchPersistence;
	protected JournalFeedPersistence journalFeedPersistence;
	protected JournalFeedFinder journalFeedFinder;
	protected JournalStructureLocalService journalStructureLocalService;
	protected JournalStructureService journalStructureService;
	protected JournalStructurePersistence journalStructurePersistence;
	protected JournalStructureFinder journalStructureFinder;
	protected JournalTemplateLocalService journalTemplateLocalService;
	protected JournalTemplateService journalTemplateService;
	protected JournalTemplatePersistence journalTemplatePersistence;
	protected JournalTemplateFinder journalTemplateFinder;
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
}