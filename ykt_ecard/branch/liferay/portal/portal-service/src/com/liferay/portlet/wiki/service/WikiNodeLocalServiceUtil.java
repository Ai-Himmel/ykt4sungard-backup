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
 * <a href="WikiNodeLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.wiki.service.WikiNodeLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.wiki.service.WikiNodeLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.wiki.service.WikiNodeLocalService
 * @see com.liferay.portlet.wiki.service.WikiNodeLocalServiceFactory
 *
 */
public class WikiNodeLocalServiceUtil {
	public static com.liferay.portlet.wiki.model.WikiNode addWikiNode(
		com.liferay.portlet.wiki.model.WikiNode model)
		throws com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.addWikiNode(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.wiki.model.WikiNode updateWikiNode(
		com.liferay.portlet.wiki.model.WikiNode model)
		throws com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.updateWikiNode(model);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiNodePersistence getWikiNodePersistence() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getWikiNodePersistence();
	}

	public static void setWikiNodePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiNodePersistence wikiNodePersistence) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setWikiNodePersistence(wikiNodePersistence);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPagePersistence getWikiPagePersistence() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getWikiPagePersistence();
	}

	public static void setWikiPagePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPagePersistence wikiPagePersistence) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setWikiPagePersistence(wikiPagePersistence);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPageFinder getWikiPageFinder() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getWikiPageFinder();
	}

	public static void setWikiPageFinder(
		com.liferay.portlet.wiki.service.persistence.WikiPageFinder wikiPageFinder) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setWikiPageFinder(wikiPageFinder);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence getWikiPageResourcePersistence() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getWikiPageResourcePersistence();
	}

	public static void setWikiPageResourcePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence wikiPageResourcePersistence) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setWikiPageResourcePersistence(wikiPageResourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getTagsEntryPersistence();
	}

	public static void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setTagsEntryPersistence(tagsEntryPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getTagsEntryFinder();
	}

	public static void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder) {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.setTagsEntryFinder(tagsEntryFinder);
	}

	public static void afterPropertiesSet() {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.wiki.model.WikiNode addNode(long userId,
		long plid, java.lang.String name, java.lang.String description,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.addNode(userId, plid, name, description,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.wiki.model.WikiNode addNode(
		java.lang.String uuid, long userId, long plid, java.lang.String name,
		java.lang.String description, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.addNode(uuid, userId, plid, name,
			description, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.wiki.model.WikiNode addNode(long userId,
		long plid, java.lang.String name, java.lang.String description,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.addNode(userId, plid, name, description,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.wiki.model.WikiNode addNode(
		java.lang.String uuid, long userId, long plid, java.lang.String name,
		java.lang.String description,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.addNode(uuid, userId, plid, name,
			description, addCommunityPermissions, addGuestPermissions,
			communityPermissions, guestPermissions);
	}

	public static void addNodeResources(long nodeId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.addNodeResources(nodeId, addCommunityPermissions,
			addGuestPermissions);
	}

	public static void addNodeResources(
		com.liferay.portlet.wiki.model.WikiNode node,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.addNodeResources(node, addCommunityPermissions,
			addGuestPermissions);
	}

	public static void addNodeResources(long nodeId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.addNodeResources(nodeId, communityPermissions,
			guestPermissions);
	}

	public static void addNodeResources(
		com.liferay.portlet.wiki.model.WikiNode node,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.addNodeResources(node, communityPermissions,
			guestPermissions);
	}

	public static void deleteNode(long nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.deleteNode(nodeId);
	}

	public static void deleteNode(com.liferay.portlet.wiki.model.WikiNode node)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.deleteNode(node);
	}

	public static void deleteNodes(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.deleteNodes(groupId);
	}

	public static com.liferay.portlet.wiki.model.WikiNode getNode(long nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getNode(nodeId);
	}

	public static java.util.List getNodes(long groupId)
		throws com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getNodes(groupId);
	}

	public static java.util.List getNodes(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getNodes(groupId, begin, end);
	}

	public static int getNodesCount(long groupId)
		throws com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.getNodesCount(groupId);
	}

	public static void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		wikiNodeLocalService.reIndex(ids);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, long[] nodeIds, java.lang.String keywords)
		throws com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.search(companyId, groupId, nodeIds, keywords);
	}

	public static com.liferay.portlet.wiki.model.WikiNode updateNode(
		long nodeId, java.lang.String name, java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiNodeLocalService wikiNodeLocalService = WikiNodeLocalServiceFactory.getService();

		return wikiNodeLocalService.updateNode(nodeId, name, description);
	}
}