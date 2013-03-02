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
 * <a href="DLFileEntryLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.documentlibrary.service.impl.DLFileEntryLocalServiceImpl</code>.
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
 * @see com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceFactory
 * @see com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil
 *
 */
public interface DLFileEntryLocalService {
	public com.liferay.portlet.documentlibrary.model.DLFileEntry addDLFileEntry(
		com.liferay.portlet.documentlibrary.model.DLFileEntry model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry updateDLFileEntry(
		com.liferay.portlet.documentlibrary.model.DLFileEntry model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence getDLFileEntryPersistence();

	public void setDLFileEntryPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryPersistence dlFileEntryPersistence);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder getDLFileEntryFinder();

	public void setDLFileEntryFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryFinder dlFileEntryFinder);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder getDLFileEntryAndShortcutFinder();

	public void setDLFileEntryAndShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileEntryAndShortcutFinder dlFileEntryAndShortcutFinder);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence getDLFileRankPersistence();

	public void setDLFileRankPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence dlFileRankPersistence);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder getDLFileRankFinder();

	public void setDLFileRankFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder dlFileRankFinder);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence getDLFileShortcutPersistence();

	public void setDLFileShortcutPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutPersistence dlFileShortcutPersistence);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder getDLFileShortcutFinder();

	public void setDLFileShortcutFinder(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileShortcutFinder dlFileShortcutFinder);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence getDLFileVersionPersistence();

	public void setDLFileVersionPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPersistence dlFileVersionPersistence);

	public com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence getDLFolderPersistence();

	public void setDLFolderPersistence(
		com.liferay.portlet.documentlibrary.service.persistence.DLFolderPersistence dlFolderPersistence);

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

	public com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence getMBMessagePersistence();

	public void setMBMessagePersistence(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePersistence mbMessagePersistence);

	public com.liferay.portlet.messageboards.service.persistence.MBMessageFinder getMBMessageFinder();

	public void setMBMessageFinder(
		com.liferay.portlet.messageboards.service.persistence.MBMessageFinder mbMessageFinder);

	public com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence getRatingsStatsPersistence();

	public void setRatingsStatsPersistence(
		com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence ratingsStatsPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence();

	public void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder();

	public void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder);

	public void afterPropertiesSet();

	public com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		java.io.File file, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		byte[] byteArray, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		java.lang.String uuid, long userId, long folderId,
		java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		java.io.File file, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		byte[] byteArray, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String title, java.lang.String description,
		java.lang.String[] tagsEntries, java.lang.String extraSettings,
		java.io.File file, java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		java.lang.String uuid, long userId, long folderId,
		java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		java.lang.String uuid, long userId, long folderId,
		java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, java.io.InputStream is, long size,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFileEntryResources(long folderId, java.lang.String name,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFileEntryResources(
		com.liferay.portlet.documentlibrary.model.DLFolder folder,
		com.liferay.portlet.documentlibrary.model.DLFileEntry fileEntry,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFileEntryResources(long folderId, java.lang.String name,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFileEntryResources(
		com.liferay.portlet.documentlibrary.model.DLFolder folder,
		com.liferay.portlet.documentlibrary.model.DLFileEntry fileEntry,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry addOrOverwriteFileEntry(
		long userId, long folderId, java.lang.String name,
		java.lang.String sourceName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, java.io.File file,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFileEntries(long folderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFileEntry(long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFileEntry(long folderId, java.lang.String name,
		double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFileEntry(
		com.liferay.portlet.documentlibrary.model.DLFileEntry fileEntry)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getCompanyFileEntries(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException;

	public java.util.List getCompanyFileEntries(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int getCompanyFileEntriesCount(long companyId)
		throws com.liferay.portal.SystemException;

	public java.io.InputStream getFileAsStream(long companyId, long userId,
		long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.io.InputStream getFileAsStream(long companyId, long userId,
		long folderId, java.lang.String name, double version)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getFileEntries(long folderId)
		throws com.liferay.portal.SystemException;

	public java.util.List getFileEntries(long folderId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getFileEntries(long folderId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public java.util.List getFileEntriesAndShortcuts(long folderId, int begin,
		int end) throws com.liferay.portal.SystemException;

	public java.util.List getFileEntriesAndShortcuts(java.util.List folderIds,
		int begin, int end) throws com.liferay.portal.SystemException;

	public int getFileEntriesAndShortcutsCount(long folderId)
		throws com.liferay.portal.SystemException;

	public int getFileEntriesAndShortcutsCount(java.util.List folderIds)
		throws com.liferay.portal.SystemException;

	public int getFileEntriesCount(long folderId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntry(
		long fileEntryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntry(
		long folderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntryByUuidAndGroupId(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntryByTitle(
		long folderId, java.lang.String titleWithExtension)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public int getFoldersFileEntriesCount(java.util.List folderIds)
		throws com.liferay.portal.SystemException;

	public java.util.List getGroupFileEntries(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getGroupFileEntries(long groupId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public java.util.List getGroupFileEntries(long groupId, long userId,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List getGroupFileEntries(long groupId, long userId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int getGroupFileEntriesCount(long groupId)
		throws com.liferay.portal.SystemException;

	public int getGroupFileEntriesCount(long groupId, long userId)
		throws com.liferay.portal.SystemException;

	public java.util.List getNoAssetFileEntries()
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry updateFileEntry(
		long userId, long folderId, long newFolderId, java.lang.String name,
		java.lang.String sourceFileName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, java.io.File file)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry updateFileEntry(
		long userId, long folderId, long newFolderId, java.lang.String name,
		java.lang.String sourceFileName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFileEntry updateFileEntry(
		long userId, long folderId, long newFolderId, java.lang.String name,
		java.lang.String sourceFileName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, java.io.InputStream is, long size)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void updateTagsAsset(long userId,
		com.liferay.portlet.documentlibrary.model.DLFileEntry fileEntry,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}