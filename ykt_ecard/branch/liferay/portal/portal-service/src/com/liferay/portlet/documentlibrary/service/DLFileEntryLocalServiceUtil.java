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
 * <a href="DLFileEntryLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.documentlibrary.service.DLFileEntryLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.documentlibrary.service.DLFileEntryLocalService
 * @see com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceFactory
 *
 */
public class DLFileEntryLocalServiceUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addDLFileEntry(
		com.liferay.portlet.documentlibrary.model.DLFileEntry model)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addDLFileEntry(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry updateDLFileEntry(
		com.liferay.portlet.documentlibrary.model.DLFileEntry model)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.updateDLFileEntry(model);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence getDLFileEntryPersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getDLFileEntryPersistence();
	}

	public static void setDLFileEntryPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence dlFileEntryPersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setDLFileEntryPersistence(dlFileEntryPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder getDLFileEntryFinder() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getDLFileEntryFinder();
	}

	public static void setDLFileEntryFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder dlFileEntryFinder) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setDLFileEntryFinder(dlFileEntryFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder getDLFileEntryAndShortcutFinder() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getDLFileEntryAndShortcutFinder();
	}

	public static void setDLFileEntryAndShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder dlFileEntryAndShortcutFinder) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setDLFileEntryAndShortcutFinder(dlFileEntryAndShortcutFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence getDLFileRankPersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getDLFileRankPersistence();
	}

	public static void setDLFileRankPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence dlFileRankPersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setDLFileRankPersistence(dlFileRankPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder getDLFileRankFinder() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getDLFileRankFinder();
	}

	public static void setDLFileRankFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder dlFileRankFinder) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setDLFileRankFinder(dlFileRankFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence getDLFileShortcutPersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getDLFileShortcutPersistence();
	}

	public static void setDLFileShortcutPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence dlFileShortcutPersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setDLFileShortcutPersistence(dlFileShortcutPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder getDLFileShortcutFinder() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getDLFileShortcutFinder();
	}

	public static void setDLFileShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder dlFileShortcutFinder) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setDLFileShortcutFinder(dlFileShortcutFinder);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence getDLFileVersionPersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getDLFileVersionPersistence();
	}

	public static void setDLFileVersionPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence dlFileVersionPersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setDLFileVersionPersistence(dlFileVersionPersistence);
	}

	public static com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence getDLFolderPersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getDLFolderPersistence();
	}

	public static void setDLFolderPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence dlFolderPersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setDLFolderPersistence(dlFolderPersistence);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setUserFinder(userFinder);
	}

	public static com.liferay.portal.service.persistence.WebDAVPropsPersistence getWebDAVPropsPersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getWebDAVPropsPersistence();
	}

	public static void setWebDAVPropsPersistence(
		com.liferay.portal.service.persistence.WebDAVPropsPersistence webDAVPropsPersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setWebDAVPropsPersistence(webDAVPropsPersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getMBMessagePersistence();
	}

	public static void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setMBMessagePersistence(mbMessagePersistence);
	}

	public static com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getMBMessageFinder();
	}

	public static void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setMBMessageFinder(mbMessageFinder);
	}

	public static com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence getRatingsStatsPersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getRatingsStatsPersistence();
	}

	public static void setRatingsStatsPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence ratingsStatsPersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setRatingsStatsPersistence(ratingsStatsPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getTagsAssetPersistence();
	}

	public static void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setTagsAssetPersistence(tagsAssetPersistence);
	}

	public static com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getTagsAssetFinder();
	}

	public static void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder) {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.setTagsAssetFinder(tagsAssetFinder);
	}

	public static void afterPropertiesSet() {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		java.io.File file, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addFileEntry(userId, folderId, name,
			title, description, tagsEntries, extraSettings, file,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		byte[] byteArray, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addFileEntry(userId, folderId, name,
			title, description, tagsEntries, extraSettings, byteArray,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		java.lang.String uuid, long userId, long folderId,
		java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addFileEntry(uuid, userId, folderId,
			name, title, description, tagsEntries, extraSettings, byteArray,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		java.io.File file, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addFileEntry(userId, folderId, name,
			title, description, tagsEntries, extraSettings, file,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		byte[] byteArray, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addFileEntry(userId, folderId, name,
			title, description, tagsEntries, extraSettings, byteArray,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		java.io.File file, java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addFileEntry(userId, folderId, name,
			title, description, tagsEntries, extraSettings, file,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		java.lang.String uuid, long userId, long folderId,
		java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addFileEntry(uuid, userId, folderId,
			name, title, description, tagsEntries, extraSettings, byteArray,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		java.lang.String uuid, long userId, long folderId,
		java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, java.io.InputStream is, long size,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addFileEntry(uuid, userId, folderId,
			name, title, description, tagsEntries, extraSettings, is, size,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public static void addFileEntryResources(long folderId,
		java.lang.String name, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.addFileEntryResources(folderId, name,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addFileEntryResources(
		com.liferay.portlet.documentlibrary.model.DLFolder folder,
		com.liferay.portlet.documentlibrary.model.DLFileEntry fileEntry,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.addFileEntryResources(folder, fileEntry,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addFileEntryResources(long folderId,
		java.lang.String name, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.addFileEntryResources(folderId, name,
			communityPermissions, guestPermissions);
	}

	public static void addFileEntryResources(
		com.liferay.portlet.documentlibrary.model.DLFolder folder,
		com.liferay.portlet.documentlibrary.model.DLFileEntry fileEntry,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.addFileEntryResources(folder, fileEntry,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addOrOverwriteFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String sourceName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, java.io.File file,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.addOrOverwriteFileEntry(userId,
			folderId, name, sourceName, title, description, tagsEntries,
			extraSettings, file, addCommunityPermissions, addGuestPermissions);
	}

	public static void deleteFileEntries(long folderId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.deleteFileEntries(folderId);
	}

	public static void deleteFileEntry(long folderId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.deleteFileEntry(folderId, name);
	}

	public static void deleteFileEntry(long folderId, java.lang.String name,
		double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.deleteFileEntry(folderId, name, version);
	}

	public static void deleteFileEntry(
		com.liferay.portlet.documentlibrary.model.DLFileEntry fileEntry)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.deleteFileEntry(fileEntry);
	}

	public static java.util.List getCompanyFileEntries(long companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getCompanyFileEntries(companyId, begin,
			end);
	}

	public static java.util.List getCompanyFileEntries(long companyId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getCompanyFileEntries(companyId, begin,
			end, obc);
	}

	public static int getCompanyFileEntriesCount(long companyId)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getCompanyFileEntriesCount(companyId);
	}

	public static java.io.InputStream getFileAsStream(long companyId,
		long userId, long folderId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileAsStream(companyId, userId,
			folderId, name);
	}

	public static java.io.InputStream getFileAsStream(long companyId,
		long userId, long folderId, java.lang.String name, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileAsStream(companyId, userId,
			folderId, name, version);
	}

	public static java.util.List getFileEntries(long folderId)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntries(folderId);
	}

	public static java.util.List getFileEntries(long folderId, int begin,
		int end) throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntries(folderId, begin, end);
	}

	public static java.util.List getFileEntries(long folderId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntries(folderId, begin, end, obc);
	}

	public static java.util.List getFileEntriesAndShortcuts(long folderId,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntriesAndShortcuts(folderId,
			begin, end);
	}

	public static java.util.List getFileEntriesAndShortcuts(
		java.util.List folderIds, int begin, int end)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntriesAndShortcuts(folderIds,
			begin, end);
	}

	public static int getFileEntriesAndShortcutsCount(long folderId)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntriesAndShortcutsCount(folderId);
	}

	public static int getFileEntriesAndShortcutsCount(java.util.List folderIds)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntriesAndShortcutsCount(folderIds);
	}

	public static int getFileEntriesCount(long folderId)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntriesCount(folderId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntry(
		long fileEntryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntry(fileEntryId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntry(
		long folderId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntry(folderId, name);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntryByUuidAndGroupId(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntryByUuidAndGroupId(uuid,
			groupId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntryByTitle(
		long folderId, java.lang.String titleWithExtension)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFileEntryByTitle(folderId,
			titleWithExtension);
	}

	public static int getFoldersFileEntriesCount(java.util.List folderIds)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getFoldersFileEntriesCount(folderIds);
	}

	public static java.util.List getGroupFileEntries(long groupId, int begin,
		int end) throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getGroupFileEntries(groupId, begin, end);
	}

	public static java.util.List getGroupFileEntries(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getGroupFileEntries(groupId, begin, end,
			obc);
	}

	public static java.util.List getGroupFileEntries(long groupId, long userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getGroupFileEntries(groupId, userId,
			begin, end);
	}

	public static java.util.List getGroupFileEntries(long groupId, long userId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getGroupFileEntries(groupId, userId,
			begin, end, obc);
	}

	public static int getGroupFileEntriesCount(long groupId)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getGroupFileEntriesCount(groupId);
	}

	public static int getGroupFileEntriesCount(long groupId, long userId)
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getGroupFileEntriesCount(groupId, userId);
	}

	public static java.util.List getNoAssetFileEntries()
		throws com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.getNoAssetFileEntries();
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry updateFileEntry(
		long userId, long folderId, long newFolderId, java.lang.String name,
		java.lang.String sourceFileName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, java.io.File file)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.updateFileEntry(userId, folderId,
			newFolderId, name, sourceFileName, title, description, tagsEntries,
			extraSettings, file);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry updateFileEntry(
		long userId, long folderId, long newFolderId, java.lang.String name,
		java.lang.String sourceFileName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.updateFileEntry(userId, folderId,
			newFolderId, name, sourceFileName, title, description, tagsEntries,
			extraSettings, byteArray);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry updateFileEntry(
		long userId, long folderId, long newFolderId, java.lang.String name,
		java.lang.String sourceFileName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, java.io.InputStream is, long size)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		return dlFileEntryLocalService.updateFileEntry(userId, folderId,
			newFolderId, name, sourceFileName, title, description, tagsEntries,
			extraSettings, is, size);
	}

	public static void updateTagsAsset(long userId,
		com.liferay.portlet.documentlibrary.model.DLFileEntry fileEntry,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		DLFileEntryLocalService dlFileEntryLocalService = DLFileEntryLocalServiceFactory.getService();

		dlFileEntryLocalService.updateTagsAsset(userId, fileEntry, tagsEntries);
	}
}