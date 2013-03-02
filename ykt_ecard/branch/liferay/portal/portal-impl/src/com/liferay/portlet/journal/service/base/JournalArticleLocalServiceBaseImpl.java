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

import com.liferay.mail.service.MailService;
import com.liferay.mail.service.MailServiceFactory;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.service.CompanyLocalService;
import com.liferay.portal.service.CompanyLocalServiceFactory;
import com.liferay.portal.service.CompanyService;
import com.liferay.portal.service.CompanyServiceFactory;
import com.liferay.portal.service.PortletPreferencesLocalService;
import com.liferay.portal.service.PortletPreferencesLocalServiceFactory;
import com.liferay.portal.service.ResourceLocalService;
import com.liferay.portal.service.ResourceLocalServiceFactory;
import com.liferay.portal.service.ResourceService;
import com.liferay.portal.service.ResourceServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.persistence.CompanyPersistence;
import com.liferay.portal.service.persistence.CompanyUtil;
import com.liferay.portal.service.persistence.PortletPreferencesFinder;
import com.liferay.portal.service.persistence.PortletPreferencesFinderUtil;
import com.liferay.portal.service.persistence.PortletPreferencesPersistence;
import com.liferay.portal.service.persistence.PortletPreferencesUtil;
import com.liferay.portal.service.persistence.ResourceFinder;
import com.liferay.portal.service.persistence.ResourceFinderUtil;
import com.liferay.portal.service.persistence.ResourcePersistence;
import com.liferay.portal.service.persistence.ResourceUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserUtil;

import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.impl.JournalArticleImpl;
import com.liferay.portlet.journal.service.JournalArticleImageLocalService;
import com.liferay.portlet.journal.service.JournalArticleImageLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalArticleLocalService;
import com.liferay.portlet.journal.service.JournalArticleResourceLocalService;
import com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalContentSearchLocalService;
import com.liferay.portlet.journal.service.JournalContentSearchLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalFeedLocalService;
import com.liferay.portlet.journal.service.JournalFeedLocalServiceFactory;
import com.liferay.portlet.journal.service.JournalFeedService;
import com.liferay.portlet.journal.service.JournalFeedServiceFactory;
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
import com.liferay.portlet.messageboards.service.MBMessageLocalService;
import com.liferay.portlet.messageboards.service.MBMessageLocalServiceFactory;
import com.liferay.portlet.messageboards.service.MBMessageService;
import com.liferay.portlet.messageboards.service.MBMessageServiceFactory;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFinder;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFinderUtil;
import com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence;
import com.liferay.portlet.messageboards.service.persistence.MBMessageUtil;
import com.liferay.portlet.ratings.service.RatingsStatsLocalService;
import com.liferay.portlet.ratings.service.RatingsStatsLocalServiceFactory;
import com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence;
import com.liferay.portlet.ratings.service.persistence.RatingsStatsUtil;
import com.liferay.portlet.tags.service.TagsAssetLocalService;
import com.liferay.portlet.tags.service.TagsAssetLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsAssetService;
import com.liferay.portlet.tags.service.TagsAssetServiceFactory;
import com.liferay.portlet.tags.service.TagsEntryLocalService;
import com.liferay.portlet.tags.service.TagsEntryLocalServiceFactory;
import com.liferay.portlet.tags.service.TagsEntryService;
import com.liferay.portlet.tags.service.TagsEntryServiceFactory;
import com.liferay.portlet.tags.service.persistence.TagsAssetFinder;
import com.liferay.portlet.tags.service.persistence.TagsAssetFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsAssetPersistence;
import com.liferay.portlet.tags.service.persistence.TagsAssetUtil;
import com.liferay.portlet.tags.service.persistence.TagsEntryFinder;
import com.liferay.portlet.tags.service.persistence.TagsEntryFinderUtil;
import com.liferay.portlet.tags.service.persistence.TagsEntryPersistence;
import com.liferay.portlet.tags.service.persistence.TagsEntryUtil;

import org.springframework.beans.factory.InitializingBean;

import java.util.List;

/**
 * <a href="JournalArticleLocalServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class JournalArticleLocalServiceBaseImpl
	implements JournalArticleLocalService, InitializingBean {
	public JournalArticle addJournalArticle(JournalArticle model)
		throws SystemException {
		JournalArticle journalArticle = new JournalArticleImpl();

		journalArticle.setNew(true);

		journalArticle.setUuid(model.getUuid());
		journalArticle.setId(model.getId());
		journalArticle.setResourcePrimKey(model.getResourcePrimKey());
		journalArticle.setGroupId(model.getGroupId());
		journalArticle.setCompanyId(model.getCompanyId());
		journalArticle.setUserId(model.getUserId());
		journalArticle.setUserName(model.getUserName());
		journalArticle.setCreateDate(model.getCreateDate());
		journalArticle.setModifiedDate(model.getModifiedDate());
		journalArticle.setArticleId(model.getArticleId());
		journalArticle.setVersion(model.getVersion());
		journalArticle.setTitle(model.getTitle());
		journalArticle.setDescription(model.getDescription());
		journalArticle.setContent(model.getContent());
		journalArticle.setType(model.getType());
		journalArticle.setStructureId(model.getStructureId());
		journalArticle.setTemplateId(model.getTemplateId());
		journalArticle.setDisplayDate(model.getDisplayDate());
		journalArticle.setApproved(model.getApproved());
		journalArticle.setApprovedByUserId(model.getApprovedByUserId());
		journalArticle.setApprovedByUserName(model.getApprovedByUserName());
		journalArticle.setApprovedDate(model.getApprovedDate());
		journalArticle.setExpired(model.getExpired());
		journalArticle.setExpirationDate(model.getExpirationDate());
		journalArticle.setReviewDate(model.getReviewDate());
		journalArticle.setIndexable(model.getIndexable());
		journalArticle.setSmallImage(model.getSmallImage());
		journalArticle.setSmallImageId(model.getSmallImageId());
		journalArticle.setSmallImageURL(model.getSmallImageURL());

		return journalArticlePersistence.update(journalArticle);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		return journalArticlePersistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		return journalArticlePersistence.findWithDynamicQuery(queryInitializer,
			begin, end);
	}

	public JournalArticle updateJournalArticle(JournalArticle model)
		throws SystemException {
		JournalArticle journalArticle = new JournalArticleImpl();

		journalArticle.setNew(false);

		journalArticle.setUuid(model.getUuid());
		journalArticle.setId(model.getId());
		journalArticle.setResourcePrimKey(model.getResourcePrimKey());
		journalArticle.setGroupId(model.getGroupId());
		journalArticle.setCompanyId(model.getCompanyId());
		journalArticle.setUserId(model.getUserId());
		journalArticle.setUserName(model.getUserName());
		journalArticle.setCreateDate(model.getCreateDate());
		journalArticle.setModifiedDate(model.getModifiedDate());
		journalArticle.setArticleId(model.getArticleId());
		journalArticle.setVersion(model.getVersion());
		journalArticle.setTitle(model.getTitle());
		journalArticle.setDescription(model.getDescription());
		journalArticle.setContent(model.getContent());
		journalArticle.setType(model.getType());
		journalArticle.setStructureId(model.getStructureId());
		journalArticle.setTemplateId(model.getTemplateId());
		journalArticle.setDisplayDate(model.getDisplayDate());
		journalArticle.setApproved(model.getApproved());
		journalArticle.setApprovedByUserId(model.getApprovedByUserId());
		journalArticle.setApprovedByUserName(model.getApprovedByUserName());
		journalArticle.setApprovedDate(model.getApprovedDate());
		journalArticle.setExpired(model.getExpired());
		journalArticle.setExpirationDate(model.getExpirationDate());
		journalArticle.setReviewDate(model.getReviewDate());
		journalArticle.setIndexable(model.getIndexable());
		journalArticle.setSmallImage(model.getSmallImage());
		journalArticle.setSmallImageId(model.getSmallImageId());
		journalArticle.setSmallImageURL(model.getSmallImageURL());

		return journalArticlePersistence.update(journalArticle);
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

	public JournalFeedLocalService getJournalFeedLocalService() {
		return journalFeedLocalService;
	}

	public void setJournalFeedLocalService(
		JournalFeedLocalService journalFeedLocalService) {
		this.journalFeedLocalService = journalFeedLocalService;
	}

	public JournalFeedService getJournalFeedService() {
		return journalFeedService;
	}

	public void setJournalFeedService(JournalFeedService journalFeedService) {
		this.journalFeedService = journalFeedService;
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

	public MailService getMailService() {
		return mailService;
	}

	public void setMailService(MailService mailService) {
		this.mailService = mailService;
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

	public PortletPreferencesLocalService getPortletPreferencesLocalService() {
		return portletPreferencesLocalService;
	}

	public void setPortletPreferencesLocalService(
		PortletPreferencesLocalService portletPreferencesLocalService) {
		this.portletPreferencesLocalService = portletPreferencesLocalService;
	}

	public PortletPreferencesPersistence getPortletPreferencesPersistence() {
		return portletPreferencesPersistence;
	}

	public void setPortletPreferencesPersistence(
		PortletPreferencesPersistence portletPreferencesPersistence) {
		this.portletPreferencesPersistence = portletPreferencesPersistence;
	}

	public PortletPreferencesFinder getPortletPreferencesFinder() {
		return portletPreferencesFinder;
	}

	public void setPortletPreferencesFinder(
		PortletPreferencesFinder portletPreferencesFinder) {
		this.portletPreferencesFinder = portletPreferencesFinder;
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

	public RatingsStatsLocalService getRatingsStatsLocalService() {
		return ratingsStatsLocalService;
	}

	public void setRatingsStatsLocalService(
		RatingsStatsLocalService ratingsStatsLocalService) {
		this.ratingsStatsLocalService = ratingsStatsLocalService;
	}

	public RatingsStatsPersistence getRatingsStatsPersistence() {
		return ratingsStatsPersistence;
	}

	public void setRatingsStatsPersistence(
		RatingsStatsPersistence ratingsStatsPersistence) {
		this.ratingsStatsPersistence = ratingsStatsPersistence;
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

		if (journalFeedLocalService == null) {
			journalFeedLocalService = JournalFeedLocalServiceFactory.getImpl();
		}

		if (journalFeedService == null) {
			journalFeedService = JournalFeedServiceFactory.getImpl();
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

		if (mailService == null) {
			mailService = MailServiceFactory.getImpl();
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

		if (portletPreferencesLocalService == null) {
			portletPreferencesLocalService = PortletPreferencesLocalServiceFactory.getImpl();
		}

		if (portletPreferencesPersistence == null) {
			portletPreferencesPersistence = PortletPreferencesUtil.getPersistence();
		}

		if (portletPreferencesFinder == null) {
			portletPreferencesFinder = PortletPreferencesFinderUtil.getFinder();
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

		if (ratingsStatsLocalService == null) {
			ratingsStatsLocalService = RatingsStatsLocalServiceFactory.getImpl();
		}

		if (ratingsStatsPersistence == null) {
			ratingsStatsPersistence = RatingsStatsUtil.getPersistence();
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

	protected JournalArticlePersistence journalArticlePersistence;
	protected JournalArticleFinder journalArticleFinder;
	protected JournalArticleImageLocalService journalArticleImageLocalService;
	protected JournalArticleImagePersistence journalArticleImagePersistence;
	protected JournalArticleResourceLocalService journalArticleResourceLocalService;
	protected JournalArticleResourcePersistence journalArticleResourcePersistence;
	protected JournalContentSearchLocalService journalContentSearchLocalService;
	protected JournalContentSearchPersistence journalContentSearchPersistence;
	protected JournalFeedLocalService journalFeedLocalService;
	protected JournalFeedService journalFeedService;
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
	protected MailService mailService;
	protected CompanyLocalService companyLocalService;
	protected CompanyService companyService;
	protected CompanyPersistence companyPersistence;
	protected PortletPreferencesLocalService portletPreferencesLocalService;
	protected PortletPreferencesPersistence portletPreferencesPersistence;
	protected PortletPreferencesFinder portletPreferencesFinder;
	protected ResourceLocalService resourceLocalService;
	protected ResourceService resourceService;
	protected ResourcePersistence resourcePersistence;
	protected ResourceFinder resourceFinder;
	protected UserLocalService userLocalService;
	protected UserService userService;
	protected UserPersistence userPersistence;
	protected UserFinder userFinder;
	protected MBMessageLocalService mbMessageLocalService;
	protected MBMessageService mbMessageService;
	protected MBMessagePersistence mbMessagePersistence;
	protected MBMessageFinder mbMessageFinder;
	protected RatingsStatsLocalService ratingsStatsLocalService;
	protected RatingsStatsPersistence ratingsStatsPersistence;
	protected TagsAssetLocalService tagsAssetLocalService;
	protected TagsAssetService tagsAssetService;
	protected TagsAssetPersistence tagsAssetPersistence;
	protected TagsAssetFinder tagsAssetFinder;
	protected TagsEntryLocalService tagsEntryLocalService;
	protected TagsEntryService tagsEntryService;
	protected TagsEntryPersistence tagsEntryPersistence;
	protected TagsEntryFinder tagsEntryFinder;
}