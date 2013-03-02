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
 * <a href="JournalStructureLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.journal.service.JournalStructureLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.journal.service.JournalStructureLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.JournalStructureLocalService
 * @see com.liferay.portlet.journal.service.JournalStructureLocalServiceFactory
 *
 */
public class JournalStructureLocalServiceUtil {
	public static com.liferay.portlet.journal.model.JournalStructure addJournalStructure(
		com.liferay.portlet.journal.model.JournalStructure model)
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.addJournalStructure(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.journal.model.JournalStructure updateJournalStructure(
		com.liferay.portlet.journal.model.JournalStructure model)
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.updateJournalStructure(model);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalArticlePersistence();
	}

	public static void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalArticlePersistence(journalArticlePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalArticleFinder();
	}

	public static void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalArticleFinder(journalArticleFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalArticleImagePersistence();
	}

	public static void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalArticleImagePersistence(journalArticleImagePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalArticleResourcePersistence();
	}

	public static void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalArticleResourcePersistence(journalArticleResourcePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalContentSearchPersistence();
	}

	public static void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalContentSearchPersistence(journalContentSearchPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalFeedPersistence();
	}

	public static void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalFeedPersistence(journalFeedPersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalFeedFinder();
	}

	public static void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalFeedFinder(journalFeedFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalStructurePersistence();
	}

	public static void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalStructurePersistence(journalStructurePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalStructureFinder();
	}

	public static void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalStructureFinder(journalStructureFinder);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalTemplatePersistence();
	}

	public static void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalTemplatePersistence(journalTemplatePersistence);
	}

	public static com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getJournalTemplateFinder();
	}

	public static void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setJournalTemplateFinder(journalTemplateFinder);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static void afterPropertiesSet() {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.journal.model.JournalStructure addStructure(
		long userId, java.lang.String structureId, boolean autoStructureId,
		long plid, java.lang.String name, java.lang.String description,
		java.lang.String xsd, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.addStructure(userId, structureId,
			autoStructureId, plid, name, description, xsd,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalStructure addStructure(
		java.lang.String uuid, long userId, java.lang.String structureId,
		boolean autoStructureId, long plid, java.lang.String name,
		java.lang.String description, java.lang.String xsd,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.addStructure(uuid, userId,
			structureId, autoStructureId, plid, name, description, xsd,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalStructure addStructure(
		long userId, java.lang.String structureId, boolean autoStructureId,
		long plid, java.lang.String name, java.lang.String description,
		java.lang.String xsd, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.addStructure(userId, structureId,
			autoStructureId, plid, name, description, xsd,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalStructure addStructure(
		java.lang.String uuid, long userId, java.lang.String structureId,
		boolean autoStructureId, long plid, java.lang.String name,
		java.lang.String description, java.lang.String xsd,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.addStructure(uuid, userId,
			structureId, autoStructureId, plid, name, description, xsd,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public static com.liferay.portlet.journal.model.JournalStructure addStructureToGroup(
		java.lang.String uuid, long userId, java.lang.String structureId,
		boolean autoStructureId, long groupId, java.lang.String name,
		java.lang.String description, java.lang.String xsd,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.addStructureToGroup(uuid, userId,
			structureId, autoStructureId, groupId, name, description, xsd,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public static void addStructureResources(long groupId,
		java.lang.String structureId, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.addStructureResources(groupId,
			structureId, addCommunityPermissions, addGuestPermissions);
	}

	public static void addStructureResources(
		com.liferay.portlet.journal.model.JournalStructure structure,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.addStructureResources(structure,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addStructureResources(long groupId,
		java.lang.String structureId, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.addStructureResources(groupId,
			structureId, communityPermissions, guestPermissions);
	}

	public static void addStructureResources(
		com.liferay.portlet.journal.model.JournalStructure structure,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.addStructureResources(structure,
			communityPermissions, guestPermissions);
	}

	public static void checkNewLine(long groupId, java.lang.String structureId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.checkNewLine(groupId, structureId);
	}

	public static void deleteStructure(long groupId,
		java.lang.String structureId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.deleteStructure(groupId, structureId);
	}

	public static void deleteStructure(
		com.liferay.portlet.journal.model.JournalStructure structure)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.deleteStructure(structure);
	}

	public static void deleteStructures(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		journalStructureLocalService.deleteStructures(groupId);
	}

	public static com.liferay.portlet.journal.model.JournalStructure getStructure(
		long id)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getStructure(id);
	}

	public static com.liferay.portlet.journal.model.JournalStructure getStructure(
		long groupId, java.lang.String structureId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getStructure(groupId, structureId);
	}

	public static java.util.List getStructures()
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getStructures();
	}

	public static java.util.List getStructures(long groupId)
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getStructures(groupId);
	}

	public static java.util.List getStructures(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getStructures(groupId, begin, end);
	}

	public static int getStructuresCount(long groupId)
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.getStructuresCount(groupId);
	}

	public static java.util.List search(long companyId, long groupId,
		java.lang.String keywords, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.search(companyId, groupId,
			keywords, begin, end, obc);
	}

	public static java.util.List search(long companyId, long groupId,
		java.lang.String structureId, java.lang.String name,
		java.lang.String description, boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.search(companyId, groupId,
			structureId, name, description, andOperator, begin, end, obc);
	}

	public static int searchCount(long companyId, long groupId,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.searchCount(companyId, groupId,
			keywords);
	}

	public static int searchCount(long companyId, long groupId,
		java.lang.String structureId, java.lang.String name,
		java.lang.String description, boolean andOperator)
		throws com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.searchCount(companyId, groupId,
			structureId, name, description, andOperator);
	}

	public static com.liferay.portlet.journal.model.JournalStructure updateStructure(
		long groupId, java.lang.String structureId, java.lang.String name,
		java.lang.String description, java.lang.String xsd)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		JournalStructureLocalService journalStructureLocalService = JournalStructureLocalServiceFactory.getService();

		return journalStructureLocalService.updateStructure(groupId,
			structureId, name, description, xsd);
	}
}