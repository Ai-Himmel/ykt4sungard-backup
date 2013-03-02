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
 * <a href="WikiPageLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.wiki.service.WikiPageLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.wiki.service.WikiPageLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.wiki.service.WikiPageLocalService
 * @see com.liferay.portlet.wiki.service.WikiPageLocalServiceFactory
 *
 */
public class WikiPageLocalServiceUtil {
	public static com.liferay.portlet.wiki.model.WikiPage addWikiPage(
		com.liferay.portlet.wiki.model.WikiPage model)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.addWikiPage(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.wiki.model.WikiPage updateWikiPage(
		com.liferay.portlet.wiki.model.WikiPage model)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.updateWikiPage(model);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiNodePersistence getWikiNodePersistence() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getWikiNodePersistence();
	}

	public static void setWikiNodePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiNodePersistence wikiNodePersistence) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setWikiNodePersistence(wikiNodePersistence);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPagePersistence getWikiPagePersistence() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getWikiPagePersistence();
	}

	public static void setWikiPagePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPagePersistence wikiPagePersistence) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setWikiPagePersistence(wikiPagePersistence);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPageFinder getWikiPageFinder() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getWikiPageFinder();
	}

	public static void setWikiPageFinder(
		com.liferay.portlet.wiki.service.persistence.WikiPageFinder wikiPageFinder) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setWikiPageFinder(wikiPageFinder);
	}

	public static com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence getWikiPageResourcePersistence() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getWikiPageResourcePersistence();
	}

	public static void setWikiPageResourcePersistence(
		com.liferay.portlet.wiki.service.persistence.WikiPageResourcePersistence wikiPageResourcePersistence) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setWikiPageResourcePersistence(wikiPageResourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getTagsAssetPersistence();
	}

	public static void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setTagsAssetPersistence(tagsAssetPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getTagsAssetFinder();
	}

	public static void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder) {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.setTagsAssetFinder(tagsAssetFinder);
	}

	public static void afterPropertiesSet() {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.wiki.model.WikiPage addPage(long userId,
		long nodeId, java.lang.String title)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.addPage(userId, nodeId, title);
	}

	public static com.liferay.portlet.wiki.model.WikiPage addPage(long userId,
		long nodeId, java.lang.String title, double version,
		java.lang.String content, java.lang.String format, boolean head,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.addPage(userId, nodeId, title, version,
			content, format, head, tagsEntries);
	}

	public static com.liferay.portlet.wiki.model.WikiPage addPage(
		java.lang.String uuid, long userId, long nodeId,
		java.lang.String title, double version, java.lang.String content,
		java.lang.String format, boolean head, java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.addPage(uuid, userId, nodeId, title,
			version, content, format, head, tagsEntries);
	}

	public static void addPageResources(long nodeId, java.lang.String title,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.addPageResources(nodeId, title,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addPageResources(
		com.liferay.portlet.wiki.model.WikiNode node,
		com.liferay.portlet.wiki.model.WikiPage page,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.addPageResources(node, page,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addPageResources(long nodeId, java.lang.String title,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.addPageResources(nodeId, title,
			communityPermissions, guestPermissions);
	}

	public static void addPageResources(
		com.liferay.portlet.wiki.model.WikiNode node,
		com.liferay.portlet.wiki.model.WikiPage page,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.addPageResources(node, page, communityPermissions,
			guestPermissions);
	}

	public static void deletePage(long nodeId, java.lang.String title)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.deletePage(nodeId, title);
	}

	public static void deletePage(com.liferay.portlet.wiki.model.WikiPage page)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.deletePage(page);
	}

	public static void deletePages(long nodeId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.deletePages(nodeId);
	}

	public static java.util.List getNoAssetPages()
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getNoAssetPages();
	}

	public static java.util.List getLinks(long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getLinks(nodeId, title);
	}

	public static java.util.List getOrphans(long nodeId)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getOrphans(nodeId);
	}

	public static com.liferay.portlet.wiki.model.WikiPage getPage(long nodeId,
		java.lang.String title)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPage(nodeId, title);
	}

	public static com.liferay.portlet.wiki.model.WikiPage getPage(long nodeId,
		java.lang.String title, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPage(nodeId, title, version);
	}

	public static java.util.List getPages(long nodeId, int begin, int end)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPages(nodeId, begin, end);
	}

	public static java.util.List getPages(long nodeId, java.lang.String title,
		int begin, int end) throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPages(nodeId, title, begin, end);
	}

	public static java.util.List getPages(long nodeId, boolean head, int begin,
		int end) throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPages(nodeId, head, begin, end);
	}

	public static java.util.List getPages(long nodeId, java.lang.String title,
		boolean head, int begin, int end)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPages(nodeId, title, head, begin, end);
	}

	public static int getPagesCount(long nodeId)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPagesCount(nodeId);
	}

	public static int getPagesCount(long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPagesCount(nodeId, title);
	}

	public static int getPagesCount(long nodeId, boolean head)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPagesCount(nodeId, head);
	}

	public static int getPagesCount(long nodeId, java.lang.String title,
		boolean head) throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getPagesCount(nodeId, title, head);
	}

	public static java.util.List getRecentChanges(long nodeId, int begin,
		int end) throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getRecentChanges(nodeId, begin, end);
	}

	public static int getRecentChangesCount(long nodeId)
		throws com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.getRecentChangesCount(nodeId);
	}

	public static com.liferay.portlet.wiki.model.WikiPage revertPage(
		long userId, long nodeId, java.lang.String title, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.revertPage(userId, nodeId, title, version);
	}

	public static com.liferay.portlet.wiki.model.WikiPage updatePage(
		long userId, long nodeId, java.lang.String title,
		java.lang.String content, java.lang.String format,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		return wikiPageLocalService.updatePage(userId, nodeId, title, content,
			format, tagsEntries);
	}

	public static void updateTagsAsset(long userId,
		com.liferay.portlet.wiki.model.WikiPage page,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		WikiPageLocalService wikiPageLocalService = WikiPageLocalServiceFactory.getService();

		wikiPageLocalService.updateTagsAsset(userId, page, tagsEntries);
	}
}