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

package com.liferay.portlet.wiki.service;


/**
 * <a href="WikiPageLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.wiki.service.impl.WikiPageLocalServiceImpl</code>.
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
 * @see com.liferay.portlet.wiki.service.WikiPageLocalServiceFactory
 * @see com.liferay.portlet.wiki.service.WikiPageLocalServiceUtil
 *
 */
public interface WikiPageLocalService {
	public com.liferay.portlet.wiki.model.WikiPage addWikiPage(
		com.liferay.portlet.wiki.model.WikiPage model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.wiki.model.WikiPage updateWikiPage(
		com.liferay.portlet.wiki.model.WikiPage model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.wiki.service.persistence.WikiNodePersistence getWikiNodePersistence();

	public void setWikiNodePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiNodePersistence wikiNodePersistence);

	public com.liferay.portlet.wiki.service.persistence.WikiPagePersistence getWikiPagePersistence();

	public void setWikiPagePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPagePersistence wikiPagePersistence);

	public com.liferay.portlet.wiki.service.persistence.WikiPageFinder getWikiPageFinder();

	public void setWikiPageFinder(
		com.liferay.portlet.wiki.service.persistence.WikiPageFinder wikiPageFinder);

	public com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence getWikiPageResourcePersistence();

	public void setWikiPageResourcePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence wikiPageResourcePersistence);

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

	public com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence();

	public void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence);

	public com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder();

	public void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder);

	public com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence();

	public void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder();

	public void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder);

	public void afterPropertiesSet();

	public com.liferay.portlet.wiki.model.WikiPage addPage(long userId,
		long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.wiki.model.WikiPage addPage(long userId,
		long nodeId, java.lang.String title, double version,
		java.lang.String content, java.lang.String format, boolean head,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.wiki.model.WikiPage addPage(
		java.lang.String uuid, long userId, long nodeId,
		java.lang.String title, double version, java.lang.String content,
		java.lang.String format, boolean head, java.lang.String[] tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addPageResources(long nodeId, java.lang.String title,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addPageResources(com.liferay.portlet.wiki.model.WikiNode node,
		com.liferay.portlet.wiki.model.WikiPage page,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addPageResources(long nodeId, java.lang.String title,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addPageResources(com.liferay.portlet.wiki.model.WikiNode node,
		com.liferay.portlet.wiki.model.WikiPage page,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deletePage(long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deletePage(com.liferay.portlet.wiki.model.WikiPage page)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deletePages(long nodeId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getNoAssetPages()
		throws com.liferay.portal.SystemException;

	public java.util.List getLinks(long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException;

	public java.util.List getOrphans(long nodeId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.wiki.model.WikiPage getPage(long nodeId,
		java.lang.String title)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.wiki.model.WikiPage getPage(long nodeId,
		java.lang.String title, double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getPages(long nodeId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getPages(long nodeId, java.lang.String title,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List getPages(long nodeId, boolean head, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getPages(long nodeId, java.lang.String title,
		boolean head, int begin, int end)
		throws com.liferay.portal.SystemException;

	public int getPagesCount(long nodeId)
		throws com.liferay.portal.SystemException;

	public int getPagesCount(long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException;

	public int getPagesCount(long nodeId, boolean head)
		throws com.liferay.portal.SystemException;

	public int getPagesCount(long nodeId, java.lang.String title, boolean head)
		throws com.liferay.portal.SystemException;

	public java.util.List getRecentChanges(long nodeId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public int getRecentChangesCount(long nodeId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.wiki.model.WikiPage revertPage(long userId,
		long nodeId, java.lang.String title, double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.wiki.model.WikiPage updatePage(long userId,
		long nodeId, java.lang.String title, java.lang.String content,
		java.lang.String format, java.lang.String[] tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void updateTagsAsset(long userId,
		com.liferay.portlet.wiki.model.WikiPage page,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}