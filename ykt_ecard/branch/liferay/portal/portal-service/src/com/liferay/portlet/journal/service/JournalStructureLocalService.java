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
 * <a href="JournalStructureLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.journal.service.impl.JournalStructureLocalServiceImpl</code>.
 * Modify methods in that class and rerun ServiceBuilder to populate this class
 * and all other generated classes.
 * </p>
 *
 * <p>
 * This is a local service. Methods of this service will not have security checks based on the propagated JAAS credentials because this service can only be accessed from within the same VM.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.JournalStructureLocalServiceFactory
 * @see com.liferay.portlet.journal.service.JournalStructureLocalServiceUtil
 *
 */
public interface JournalStructureLocalService {
	public com.liferay.portlet.journal.model.JournalStructure addJournalStructure(
		com.liferay.portlet.journal.model.JournalStructure model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalStructure updateJournalStructure(
		com.liferay.portlet.journal.model.JournalStructure model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.service.persistence.JournalArticlePersistence getJournalArticlePersistence();

	public void setJournalArticlePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticlePersistence journalArticlePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalArticleFinder getJournalArticleFinder();

	public void setJournalArticleFinder(
		com.liferay.portlet.journal.service.persistence.JournalArticleFinder journalArticleFinder);

	public com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence getJournalArticleImagePersistence();

	public void setJournalArticleImagePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleImagePersistence journalArticleImagePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence getJournalArticleResourcePersistence();

	public void setJournalArticleResourcePersistence(
		com.liferay.portlet.journal.service.persistence.JournalArticleResourcePersistence journalArticleResourcePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence getJournalContentSearchPersistence();

	public void setJournalContentSearchPersistence(
		com.liferay.portlet.journal.service.persistence.JournalContentSearchPersistence journalContentSearchPersistence);

	public com.liferay.portlet.journal.service.persistence.JournalFeedPersistence getJournalFeedPersistence();

	public void setJournalFeedPersistence(
		com.liferay.portlet.journal.service.persistence.JournalFeedPersistence journalFeedPersistence);

	public com.liferay.portlet.journal.service.persistence.JournalFeedFinder getJournalFeedFinder();

	public void setJournalFeedFinder(
		com.liferay.portlet.journal.service.persistence.JournalFeedFinder journalFeedFinder);

	public com.liferay.portlet.journal.service.persistence.JournalStructurePersistence getJournalStructurePersistence();

	public void setJournalStructurePersistence(
		com.liferay.portlet.journal.service.persistence.JournalStructurePersistence journalStructurePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalStructureFinder getJournalStructureFinder();

	public void setJournalStructureFinder(
		com.liferay.portlet.journal.service.persistence.JournalStructureFinder journalStructureFinder);

	public com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence getJournalTemplatePersistence();

	public void setJournalTemplatePersistence(
		com.liferay.portlet.journal.service.persistence.JournalTemplatePersistence journalTemplatePersistence);

	public com.liferay.portlet.journal.service.persistence.JournalTemplateFinder getJournalTemplateFinder();

	public void setJournalTemplateFinder(
		com.liferay.portlet.journal.service.persistence.JournalTemplateFinder journalTemplateFinder);

	public com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence();

	public void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence);

	public com.liferay.portal.service.persistence.ResourceFinder getResourceFinder();

	public void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder);

	public com.liferay.portal.service.persistence.UserPersistence getUserPersistence();

	public void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence);

	public com.liferay.portal.service.persistence.UserFinder getUserFinder();

	public void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder);

	public com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence();

	public void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence);

	public void afterPropertiesSet();

	public com.liferay.portlet.journal.model.JournalStructure addStructure(
		long userId, java.lang.String structureId, boolean autoStructureId,
		long plid, java.lang.String name, java.lang.String description,
		java.lang.String xsd, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalStructure addStructure(
		java.lang.String uuid, long userId, java.lang.String structureId,
		boolean autoStructureId, long plid, java.lang.String name,
		java.lang.String description, java.lang.String xsd,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalStructure addStructure(
		long userId, java.lang.String structureId, boolean autoStructureId,
		long plid, java.lang.String name, java.lang.String description,
		java.lang.String xsd, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalStructure addStructure(
		java.lang.String uuid, long userId, java.lang.String structureId,
		boolean autoStructureId, long plid, java.lang.String name,
		java.lang.String description, java.lang.String xsd,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalStructure addStructureToGroup(
		java.lang.String uuid, long userId, java.lang.String structureId,
		boolean autoStructureId, long groupId, java.lang.String name,
		java.lang.String description, java.lang.String xsd,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addStructureResources(long groupId,
		java.lang.String structureId, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addStructureResources(
		com.liferay.portlet.journal.model.JournalStructure structure,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addStructureResources(long groupId,
		java.lang.String structureId, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addStructureResources(
		com.liferay.portlet.journal.model.JournalStructure structure,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void checkNewLine(long groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteStructure(long groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteStructure(
		com.liferay.portlet.journal.model.JournalStructure structure)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteStructures(long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalStructure getStructure(
		long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.journal.model.JournalStructure getStructure(
		long groupId, java.lang.String structureId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getStructures()
		throws com.liferay.portal.SystemException;

	public java.util.List getStructures(long groupId)
		throws com.liferay.portal.SystemException;

	public java.util.List getStructures(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public int getStructuresCount(long groupId)
		throws com.liferay.portal.SystemException;

	public java.util.List search(long companyId, long groupId,
		java.lang.String keywords, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public java.util.List search(long companyId, long groupId,
		java.lang.String structureId, java.lang.String name,
		java.lang.String description, boolean andOperator, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int searchCount(long companyId, long groupId,
		java.lang.String keywords) throws com.liferay.portal.SystemException;

	public int searchCount(long companyId, long groupId,
		java.lang.String structureId, java.lang.String name,
		java.lang.String description, boolean andOperator)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.journal.model.JournalStructure updateStructure(
		long groupId, java.lang.String structureId, java.lang.String name,
		java.lang.String description, java.lang.String xsd)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}