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

package com.liferay.portlet.bookmarks.service;


/**
 * <a href="BookmarksFolderLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.bookmarks.service.BookmarksFolderLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.bookmarks.service.BookmarksFolderLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.bookmarks.service.BookmarksFolderLocalService
 * @see com.liferay.portlet.bookmarks.service.BookmarksFolderLocalServiceFactory
 *
 */
public class BookmarksFolderLocalServiceUtil {
	public static com.liferay.portlet.bookmarks.model.BookmarksFolder addBookmarksFolder(
		com.liferay.portlet.bookmarks.model.BookmarksFolder model)
		throws com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.addBookmarksFolder(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.dynamicQuery(queryInitializer,
			begin, end);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder updateBookmarksFolder(
		com.liferay.portlet.bookmarks.model.BookmarksFolder model)
		throws com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.updateBookmarksFolder(model);
	}

	public static com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistence getBookmarksEntryPersistence() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getBookmarksEntryPersistence();
	}

	public static void setBookmarksEntryPersistence(
		com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryPersistence bookmarksEntryPersistence) {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.setBookmarksEntryPersistence(bookmarksEntryPersistence);
	}

	public static com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinder getBookmarksEntryFinder() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getBookmarksEntryFinder();
	}

	public static void setBookmarksEntryFinder(
		com.liferay.portlet.bookmarks.service.persistence.BookmarksEntryFinder bookmarksEntryFinder) {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.setBookmarksEntryFinder(bookmarksEntryFinder);
	}

	public static com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderPersistence getBookmarksFolderPersistence() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getBookmarksFolderPersistence();
	}

	public static void setBookmarksFolderPersistence(
		com.liferay.portlet.bookmarks.service.persistence.BookmarksFolderPersistence bookmarksFolderPersistence) {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.setBookmarksFolderPersistence(bookmarksFolderPersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryPersistence getTagsEntryPersistence() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getTagsEntryPersistence();
	}

	public static void setTagsEntryPersistence(
		com.liferay.portlet.tags.service.persistence.TagsEntryPersistence tagsEntryPersistence) {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.setTagsEntryPersistence(tagsEntryPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsEntryFinder getTagsEntryFinder() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getTagsEntryFinder();
	}

	public static void setTagsEntryFinder(
		com.liferay.portlet.tags.service.persistence.TagsEntryFinder tagsEntryFinder) {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.setTagsEntryFinder(tagsEntryFinder);
	}

	public static void afterPropertiesSet() {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder addFolder(
		long userId, long plid, long parentFolderId, java.lang.String name,
		java.lang.String description, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.addFolder(userId, plid,
			parentFolderId, name, description, addCommunityPermissions,
			addGuestPermissions);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder addFolder(
		java.lang.String uuid, long userId, long plid, long parentFolderId,
		java.lang.String name, java.lang.String description,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.addFolder(uuid, userId, plid,
			parentFolderId, name, description, addCommunityPermissions,
			addGuestPermissions);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder addFolder(
		long userId, long plid, long parentFolderId, java.lang.String name,
		java.lang.String description, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.addFolder(userId, plid,
			parentFolderId, name, description, communityPermissions,
			guestPermissions);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder addFolder(
		java.lang.String uuid, long userId, long plid, long parentFolderId,
		java.lang.String name, java.lang.String description,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.addFolder(uuid, userId, plid,
			parentFolderId, name, description, addCommunityPermissions,
			addGuestPermissions, communityPermissions, guestPermissions);
	}

	public static void addFolderResources(long folderId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.addFolderResources(folderId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addFolderResources(
		com.liferay.portlet.bookmarks.model.BookmarksFolder folder,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.addFolderResources(folder,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addFolderResources(long folderId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.addFolderResources(folderId,
			communityPermissions, guestPermissions);
	}

	public static void addFolderResources(
		com.liferay.portlet.bookmarks.model.BookmarksFolder folder,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.addFolderResources(folder,
			communityPermissions, guestPermissions);
	}

	public static void deleteFolder(long folderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.deleteFolder(folderId);
	}

	public static void deleteFolder(
		com.liferay.portlet.bookmarks.model.BookmarksFolder folder)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.deleteFolder(folder);
	}

	public static void deleteFolders(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.deleteFolders(groupId);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder getFolder(
		long folderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getFolder(folderId);
	}

	public static java.util.List getFolders(long groupId, long parentFolderId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getFolders(groupId, parentFolderId,
			begin, end);
	}

	public static int getFoldersCount(long groupId, long parentFolderId)
		throws com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.getFoldersCount(groupId,
			parentFolderId);
	}

	public static void getSubfolderIds(java.util.List folderIds, long groupId,
		long folderId) throws com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.getSubfolderIds(folderIds, groupId, folderId);
	}

	public static void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		bookmarksFolderLocalService.reIndex(ids);
	}

	public static com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, long[] folderIds, java.lang.String keywords)
		throws com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.search(companyId, groupId,
			folderIds, keywords);
	}

	public static com.liferay.portlet.bookmarks.model.BookmarksFolder updateFolder(
		long folderId, long parentFolderId, java.lang.String name,
		java.lang.String description, boolean mergeWithParentFolder)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		BookmarksFolderLocalService bookmarksFolderLocalService = BookmarksFolderLocalServiceFactory.getService();

		return bookmarksFolderLocalService.updateFolder(folderId,
			parentFolderId, name, description, mergeWithParentFolder);
	}
}