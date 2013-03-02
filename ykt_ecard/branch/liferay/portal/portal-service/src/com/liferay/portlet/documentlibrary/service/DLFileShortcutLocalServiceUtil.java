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

package com.liferay.portlet.documentlibrary.service;


/**
 * <a href="DLFileShortcutLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.documentlibrary.service.DLFileShortcutLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.documentlibrary.service.DLFileShortcutLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.documentlibrary.service.DLFileShortcutLocalService
 * @see com.liferay.portlet.documentlibrary.service.DLFileShortcutLocalServiceFactory
 *
 */
public class DLFileShortcutLocalServiceUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut addDLFileShortcut(
		com.liferay.portlet.documentlibrary.model.DLFileShortcut model)
		throws com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.addDLFileShortcut(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.dynamicQuery(queryInitializer, begin,
			end);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut updateDLFileShortcut(
		com.liferay.portlet.documentlibrary.model.DLFileShortcut model)
		throws com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.updateDLFileShortcut(model);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence getDLFileEntryPersistence() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getDLFileEntryPersistence();
	}

	public static void setDLFileEntryPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence dlFileEntryPersistence) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setDLFileEntryPersistence(dlFileEntryPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder getDLFileEntryFinder() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getDLFileEntryFinder();
	}

	public static void setDLFileEntryFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder dlFileEntryFinder) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setDLFileEntryFinder(dlFileEntryFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder getDLFileEntryAndShortcutFinder() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getDLFileEntryAndShortcutFinder();
	}

	public static void setDLFileEntryAndShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder dlFileEntryAndShortcutFinder) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setDLFileEntryAndShortcutFinder(dlFileEntryAndShortcutFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence getDLFileRankPersistence() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getDLFileRankPersistence();
	}

	public static void setDLFileRankPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence dlFileRankPersistence) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setDLFileRankPersistence(dlFileRankPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder getDLFileRankFinder() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getDLFileRankFinder();
	}

	public static void setDLFileRankFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder dlFileRankFinder) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setDLFileRankFinder(dlFileRankFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence getDLFileShortcutPersistence() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getDLFileShortcutPersistence();
	}

	public static void setDLFileShortcutPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence dlFileShortcutPersistence) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setDLFileShortcutPersistence(dlFileShortcutPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder getDLFileShortcutFinder() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getDLFileShortcutFinder();
	}

	public static void setDLFileShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder dlFileShortcutFinder) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setDLFileShortcutFinder(dlFileShortcutFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence getDLFileVersionPersistence() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getDLFileVersionPersistence();
	}

	public static void setDLFileVersionPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence dlFileVersionPersistence) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setDLFileVersionPersistence(dlFileVersionPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence getDLFolderPersistence() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getDLFolderPersistence();
	}

	public static void setDLFolderPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence dlFolderPersistence) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setDLFolderPersistence(dlFolderPersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut addFileShortcut(
		long userId, long folderId, long toFolderId, java.lang.String toName,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.addFileShortcut(userId, folderId,
			toFolderId, toName, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut addFileShortcut(
		java.lang.String uuid, long userId, long folderId, long toFolderId,
		java.lang.String toName, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.addFileShortcut(uuid, userId,
			folderId, toFolderId, toName, addCommunityPermissions,
			addGuestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut addFileShortcut(
		long userId, long folderId, long toFolderId, java.lang.String toName,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.addFileShortcut(userId, folderId,
			toFolderId, toName, communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut addFileShortcut(
		java.lang.String uuid, long userId, long folderId, long toFolderId,
		java.lang.String toName, java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.addFileShortcut(uuid, userId,
			folderId, toFolderId, toName, addCommunityPermissions,
			addGuestPermissions, communityPermissions, guestPermissions);
	}

	public static void addFileShortcutResources(long fileShortcutId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.addFileShortcutResources(fileShortcutId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addFileShortcutResources(
		com.liferay.portlet.documentlibrary.model.DLFolder folder,
		com.liferay.portlet.documentlibrary.model.DLFileShortcut fileShortcut,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.addFileShortcutResources(folder,
			fileShortcut, addCommunityPermissions, addGuestPermissions);
	}

	public static void addFileShortcutResources(long fileShortcutId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.addFileShortcutResources(fileShortcutId,
			communityPermissions, guestPermissions);
	}

	public static void addFileShortcutResources(
		com.liferay.portlet.documentlibrary.model.DLFolder folder,
		com.liferay.portlet.documentlibrary.model.DLFileShortcut fileShortcut,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.addFileShortcutResources(folder,
			fileShortcut, communityPermissions, guestPermissions);
	}

	public static void deleteFileShortcut(long fileShortcutId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.deleteFileShortcut(fileShortcutId);
	}

	public static void deleteFileShortcut(
		com.liferay.portlet.documentlibrary.model.DLFileShortcut fileShortcut)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.deleteFileShortcut(fileShortcut);
	}

	public static void deleteFileShortcuts(long toFolderId,
		java.lang.String toName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.deleteFileShortcuts(toFolderId, toName);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut getFileShortcut(
		long fileShortcutId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.getFileShortcut(fileShortcutId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileShortcut updateFileShortcut(
		long userId, long fileShortcutId, long folderId, long toFolderId,
		java.lang.String toName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		return dlFileShortcutLocalService.updateFileShortcut(userId,
			fileShortcutId, folderId, toFolderId, toName);
	}

	public static void updateFileShortcuts(long oldToFolderId,
		java.lang.String oldToName, long newToFolderId,
		java.lang.String newToName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileShortcutLocalService dlFileShortcutLocalService = DLFileShortcutLocalServiceFactory.getService();

		dlFileShortcutLocalService.updateFileShortcuts(oldToFolderId,
			oldToName, newToFolderId, newToName);
	}
}