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

package com.liferay.portlet.journal.service;


/**
 * <a href="JournalFeedLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.journal.service.JournalFeedLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.journal.service.JournalFeedLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.JournalFeedLocalService
 * @see com.liferay.portlet.journal.service.JournalFeedLocalServiceFactory
 *
 */
public class JournalFeedLocalServiceUtil {
	public static com.liferay.portlet.journal.model.JournalFeed addJournalFeed(
		com.liferay.portlet.journal.model.JournalFeed model)
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.addJournalFeed(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.journal.model.JournalFeed updateJournalFeed(
		com.liferay.portlet.journal.model.JournalFeed model)
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.updateJournalFeed(model);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalArticlePersistence();
	}

	public static void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalArticlePersistence(journalArticlePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalArticleFinder();
	}

	public static void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalArticleFinder(journalArticleFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalArticleImagePersistence();
	}

	public static void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalArticleImagePersistence(journalArticleImagePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalArticleResourcePersistence();
	}

	public static void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalArticleResourcePersistence(journalArticleResourcePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalContentSearchPersistence();
	}

	public static void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalContentSearchPersistence(journalContentSearchPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalFeedPersistence();
	}

	public static void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalFeedPersistence(journalFeedPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalFeedFinder();
	}

	public static void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalFeedFinder(journalFeedFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalStructurePersistence();
	}

	public static void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalStructurePersistence(journalStructurePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalStructureFinder();
	}

	public static void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalStructureFinder(journalStructureFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalTemplatePersistence();
	}

	public static void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalTemplatePersistence(journalTemplatePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getJournalTemplateFinder();
	}

	public static void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setJournalTemplateFinder(journalTemplateFinder);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.journal.model.JournalFeed addFeed(
		long userId, long plid, java.lang.String feedId, boolean autoFeedId,
		java.lang.String name, java.lang.String description,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, java.lang.String rendererTemplateId,
		int delta, java.lang.String orderByCol, java.lang.String orderByType,
		java.lang.String targetLayoutFriendlyUrl,
		java.lang.String targetPortletId, java.lang.String contentField,
		java.lang.String feedType, double feedVersion,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.addFeed(userId, plid, feedId,
			autoFeedId, name, description, type, structureId, templateId,
			rendererTemplateId, delta, orderByCol, orderByType,
			targetLayoutFriendlyUrl, targetPortletId, contentField, feedType,
			feedVersion, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalFeed addFeed(
		long userId, long plid, java.lang.String feedId, boolean autoFeedId,
		java.lang.String name, java.lang.String description,
		java.lang.String type, java.lang.String structureId,
		java.lang.String templateId, java.lang.String rendererTemplateId,
		int delta, java.lang.String orderByCol, java.lang.String orderByType,
		java.lang.String targetLayoutFriendlyUrl,
		java.lang.String targetPortletId, java.lang.String contentField,
		java.lang.String feedType, double feedVersion,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.addFeed(userId, plid, feedId,
			autoFeedId, name, description, type, structureId, templateId,
			rendererTemplateId, delta, orderByCol, orderByType,
			targetLayoutFriendlyUrl, targetPortletId, contentField, feedType,
			feedVersion, communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalFeed addFeed(
		java.lang.String uuid, long userId, long plid, java.lang.String feedId,
		boolean autoFeedId, java.lang.String name,
		java.lang.String description, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.lang.String rendererTemplateId, int delta,
		java.lang.String orderByCol, java.lang.String orderByType,
		java.lang.String targetLayoutFriendlyUrl,
		java.lang.String targetPortletId, java.lang.String contentField,
		java.lang.String feedType, double feedVersion,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.addFeed(uuid, userId, plid, feedId,
			autoFeedId, name, description, type, structureId, templateId,
			rendererTemplateId, delta, orderByCol, orderByType,
			targetLayoutFriendlyUrl, targetPortletId, contentField, feedType,
			feedVersion, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalFeed addFeed(
		java.lang.String uuid, long userId, long plid, java.lang.String feedId,
		boolean autoFeedId, java.lang.String name,
		java.lang.String description, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.lang.String rendererTemplateId, int delta,
		java.lang.String orderByCol, java.lang.String orderByType,
		java.lang.String targetLayoutFriendlyUrl,
		java.lang.String targetPortletId, java.lang.String contentField,
		java.lang.String feedType, double feedVersion,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.addFeed(uuid, userId, plid, feedId,
			autoFeedId, name, description, type, structureId, templateId,
			rendererTemplateId, delta, orderByCol, orderByType,
			targetLayoutFriendlyUrl, targetPortletId, contentField, feedType,
			feedVersion, communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalFeed addFeed(
		java.lang.String uuid, long userId, long plid, java.lang.String feedId,
		boolean autoFeedId, java.lang.String name,
		java.lang.String description, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.lang.String rendererTemplateId, int delta,
		java.lang.String orderByCol, java.lang.String orderByType,
		java.lang.String targetLayoutFriendlyUrl,
		java.lang.String targetPortletId, java.lang.String contentField,
		java.lang.String feedType, double feedVersion,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.addFeed(uuid, userId, plid, feedId,
			autoFeedId, name, description, type, structureId, templateId,
			rendererTemplateId, delta, orderByCol, orderByType,
			targetLayoutFriendlyUrl, targetPortletId, contentField, feedType,
			feedVersion, addCommunityPermissions, addGuestPermissions,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalFeed addFeedToGroup(
		java.lang.String uuid, long userId, long groupId,
		java.lang.String feedId, boolean autoFeedId, java.lang.String name,
		java.lang.String description, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.lang.String rendererTemplateId, int delta,
		java.lang.String orderByCol, java.lang.String orderByType,
		java.lang.String targetLayoutFriendlyUrl,
		java.lang.String targetPortletId, java.lang.String contentField,
		java.lang.String feedType, double feedVersion,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.addFeedToGroup(uuid, userId, groupId,
			feedId, autoFeedId, name, description, type, structureId,
			templateId, rendererTemplateId, delta, orderByCol, orderByType,
			targetLayoutFriendlyUrl, targetPortletId, contentField, feedType,
			feedVersion, addCommunityPermissions, addGuestPermissions,
			communityPermissions, guestPermissions);
	}

	public static void addFeedResources(long feedId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.addFeedResources(feedId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addFeedResources(
		com.liferay.portlet.journal.model.JournalFeed feed,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.addFeedResources(feed, addCommunityPermissions,
			addGuestPermissions);
	}

	public static void addFeedResources(long feedId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.addFeedResources(feedId, communityPermissions,
			guestPermissions);
	}

	public static void addFeedResources(
		com.liferay.portlet.journal.model.JournalFeed feed,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.addFeedResources(feed, communityPermissions,
			guestPermissions);
	}

	public static void deleteFeed(long feedId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.deleteFeed(feedId);
	}

	public static void deleteFeed(long groupId, java.lang.String feedId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.deleteFeed(groupId, feedId);
	}

	public static void deleteFeed(
		com.liferay.portlet.journal.model.JournalFeed feed)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		journalFeedLocalService.deleteFeed(feed);
	}

	public static com.liferay.portlet.journal.model.JournalFeed getFeed(
		long feedId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getFeed(feedId);
	}

	public static com.liferay.portlet.journal.model.JournalFeed getFeed(
		long groupId, java.lang.String feedId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getFeed(groupId, feedId);
	}

	public static java.util.List getFeeds()
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getFeeds();
	}

	public static java.util.List getFeeds(long groupId)
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getFeeds(groupId);
	}

	public static java.util.List getFeeds(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getFeeds(groupId, begin, end);
	}

	public static int getFeedsCount(long groupId)
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.getFeedsCount(groupId);
	}

	public static java.util.List search(long companyId, long groupId,
		java.lang.String keywords, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.search(companyId, groupId, keywords,
			begin, end, obc);
	}

	public static java.util.List search(long companyId, long groupId,
		java.lang.String feedId, java.lang.String name,
		java.lang.String description, boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.search(companyId, groupId, feedId, name,
			description, andOperator, begin, end, obc);
	}

	public static int searchCount(long companyId, long groupId,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.searchCount(companyId, groupId, keywords);
	}

	public static int searchCount(long companyId, long groupId,
		java.lang.String feedId, java.lang.String name,
		java.lang.String description, boolean andOperator)
		throws com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.searchCount(companyId, groupId, feedId,
			name, description, andOperator);
	}

	public static com.liferay.portlet.journal.model.JournalFeed updateFeed(
		long groupId, java.lang.String feedId, java.lang.String name,
		java.lang.String description, java.lang.String type,
		java.lang.String structureId, java.lang.String templateId,
		java.lang.String rendererTemplateId, int delta,
		java.lang.String orderByCol, java.lang.String orderByType,
		java.lang.String targetLayoutFriendlyUrl,
		java.lang.String targetPortletId, java.lang.String contentField,
		java.lang.String feedType, double feedVersion)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalFeedLocalService journalFeedLocalService = JournalFeedLocalServiceFactory.getService();

		return journalFeedLocalService.updateFeed(groupId, feedId, name,
			description, type, structureId, templateId, rendererTemplateId,
			delta, orderByCol, orderByType, targetLayoutFriendlyUrl,
			targetPortletId, contentField, feedType, feedVersion);
	}
}