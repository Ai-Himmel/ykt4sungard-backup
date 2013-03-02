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
 * <a href="JournalTemplateLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.journal.service.JournalTemplateLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.journal.service.JournalTemplateLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.JournalTemplateLocalService
 * @see com.liferay.portlet.journal.service.JournalTemplateLocalServiceFactory
 *
 */
public class JournalTemplateLocalServiceUtil {
	public static com.liferay.portlet.journal.model.JournalTemplate addJournalTemplate(
		com.liferay.portlet.journal.model.JournalTemplate model)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.addJournalTemplate(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate updateJournalTemplate(
		com.liferay.portlet.journal.model.JournalTemplate model)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.updateJournalTemplate(model);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalArticlePersistence();
	}

	public static void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalArticlePersistence(journalArticlePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalArticleFinder();
	}

	public static void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalArticleFinder(journalArticleFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalArticleImagePersistence();
	}

	public static void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalArticleImagePersistence(journalArticleImagePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalArticleResourcePersistence();
	}

	public static void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalArticleResourcePersistence(journalArticleResourcePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalContentSearchPersistence();
	}

	public static void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalContentSearchPersistence(journalContentSearchPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalFeedPersistence();
	}

	public static void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalFeedPersistence(journalFeedPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalFeedFinder();
	}

	public static void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalFeedFinder(journalFeedFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalStructurePersistence();
	}

	public static void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalStructurePersistence(journalStructurePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalStructureFinder();
	}

	public static void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalStructureFinder(journalStructureFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalTemplatePersistence();
	}

	public static void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalTemplatePersistence(journalTemplatePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getJournalTemplateFinder();
	}

	public static void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setJournalTemplateFinder(journalTemplateFinder);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static void afterPropertiesSet() {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.journal.model.JournalTemplate addTemplate(
		long userId, java.lang.String templateId, boolean autoTemplateId,
		long plid, java.lang.String structureId, java.lang.String name,
		java.lang.String description, java.lang.String xsl, boolean formatXsl,
		java.lang.String langType, boolean cacheable, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.addTemplate(userId, templateId,
			autoTemplateId, plid, structureId, name, description, xsl,
			formatXsl, langType, cacheable, smallImage, smallImageURL,
			smallFile, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate addTemplate(
		java.lang.String uuid, long userId, java.lang.String templateId,
		boolean autoTemplateId, long plid, java.lang.String structureId,
		java.lang.String name, java.lang.String description,
		java.lang.String xsl, boolean formatXsl, java.lang.String langType,
		boolean cacheable, boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.addTemplate(uuid, userId,
			templateId, autoTemplateId, plid, structureId, name, description,
			xsl, formatXsl, langType, cacheable, smallImage, smallImageURL,
			smallFile, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate addTemplate(
		long userId, java.lang.String templateId, boolean autoTemplateId,
		long plid, java.lang.String structureId, java.lang.String name,
		java.lang.String description, java.lang.String xsl, boolean formatXsl,
		java.lang.String langType, boolean cacheable, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.addTemplate(userId, templateId,
			autoTemplateId, plid, structureId, name, description, xsl,
			formatXsl, langType, cacheable, smallImage, smallImageURL,
			smallFile, communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate addTemplate(
		java.lang.String uuid, long userId, java.lang.String templateId,
		boolean autoTemplateId, long plid, java.lang.String structureId,
		java.lang.String name, java.lang.String description,
		java.lang.String xsl, boolean formatXsl, java.lang.String langType,
		boolean cacheable, boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.addTemplate(uuid, userId,
			templateId, autoTemplateId, plid, structureId, name, description,
			xsl, formatXsl, langType, cacheable, smallImage, smallImageURL,
			smallFile, addCommunityPermissions, addGuestPermissions,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate addTemplateToGroup(
		java.lang.String uuid, long userId, java.lang.String templateId,
		boolean autoTemplateId, long groupId, java.lang.String structureId,
		java.lang.String name, java.lang.String description,
		java.lang.String xsl, boolean formatXsl, java.lang.String langType,
		boolean cacheable, boolean smallImage, java.lang.String smallImageURL,
		java.io.File smallFile, java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.addTemplateToGroup(uuid, userId,
			templateId, autoTemplateId, groupId, structureId, name,
			description, xsl, formatXsl, langType, cacheable, smallImage,
			smallImageURL, smallFile, addCommunityPermissions,
			addGuestPermissions, communityPermissions, guestPermissions);
	}

	public static void addTemplateResources(long groupId,
		java.lang.String templateId, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.addTemplateResources(groupId, templateId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addTemplateResources(
		com.liferay.portlet.journal.model.JournalTemplate template,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.addTemplateResources(template,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addTemplateResources(long groupId,
		java.lang.String templateId, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.addTemplateResources(groupId, templateId,
			communityPermissions, guestPermissions);
	}

	public static void addTemplateResources(
		com.liferay.portlet.journal.model.JournalTemplate template,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.addTemplateResources(template,
			communityPermissions, guestPermissions);
	}

	public static void checkNewLine(long groupId, java.lang.String templateId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.checkNewLine(groupId, templateId);
	}

	public static void deleteTemplate(long groupId, java.lang.String templateId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.deleteTemplate(groupId, templateId);
	}

	public static void deleteTemplate(
		com.liferay.portlet.journal.model.JournalTemplate template)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.deleteTemplate(template);
	}

	public static void deleteTemplates(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		journalTemplateLocalService.deleteTemplates(groupId);
	}

	public static java.util.List getStructureTemplates(long groupId,
		java.lang.String structureId) throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getStructureTemplates(groupId,
			structureId);
	}

	public static java.util.List getStructureTemplates(long groupId,
		java.lang.String structureId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getStructureTemplates(groupId,
			structureId, begin, end);
	}

	public static int getStructureTemplatesCount(long groupId,
		java.lang.String structureId) throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getStructureTemplatesCount(groupId,
			structureId);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate getTemplate(
		long id)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getTemplate(id);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate getTemplate(
		long groupId, java.lang.String templateId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getTemplate(groupId, templateId);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate getTemplateBySmallImageId(
		long smallImageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getTemplateBySmallImageId(smallImageId);
	}

	public static java.util.List getTemplates()
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getTemplates();
	}

	public static java.util.List getTemplates(long groupId)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getTemplates(groupId);
	}

	public static java.util.List getTemplates(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getTemplates(groupId, begin, end);
	}

	public static int getTemplatesCount(long groupId)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.getTemplatesCount(groupId);
	}

	public static boolean hasTemplate(long groupId, java.lang.String templateId)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.hasTemplate(groupId, templateId);
	}

	public static java.util.List search(long companyId, long groupId,
		java.lang.String keywords, java.lang.String structureId,
		java.lang.String structureIdComparator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.search(companyId, groupId, keywords,
			structureId, structureIdComparator, begin, end, obc);
	}

	public static java.util.List search(long companyId, long groupId,
		java.lang.String templateId, java.lang.String structureId,
		java.lang.String structureIdComparator, java.lang.String name,
		java.lang.String description, boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.search(companyId, groupId,
			templateId, structureId, structureIdComparator, name, description,
			andOperator, begin, end, obc);
	}

	public static int searchCount(long companyId, long groupId,
		java.lang.String keywords, java.lang.String structureId,
		java.lang.String structureIdComparator)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.searchCount(companyId, groupId,
			keywords, structureId, structureIdComparator);
	}

	public static int searchCount(long companyId, long groupId,
		java.lang.String templateId, java.lang.String structureId,
		java.lang.String structureIdComparator, java.lang.String name,
		java.lang.String description, boolean andOperator)
		throws com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.searchCount(companyId, groupId,
			templateId, structureId, structureIdComparator, name, description,
			andOperator);
	}

	public static com.liferay.portlet.journal.model.JournalTemplate updateTemplate(
		long groupId, java.lang.String templateId,
		java.lang.String structureId, java.lang.String name,
		java.lang.String description, java.lang.String xsl, boolean formatXsl,
		java.lang.String langType, boolean cacheable, boolean smallImage,
		java.lang.String smallImageURL, java.io.File smallFile)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalTemplateLocalService journalTemplateLocalService = JournalTemplateLocalServiceFactory.getService();

		return journalTemplateLocalService.updateTemplate(groupId, templateId,
			structureId, name, description, xsl, formatXsl, langType,
			cacheable, smallImage, smallImageURL, smallFile);
	}
}