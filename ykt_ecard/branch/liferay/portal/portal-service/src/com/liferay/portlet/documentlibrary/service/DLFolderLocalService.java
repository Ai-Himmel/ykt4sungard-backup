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
 * <a href="DLFolderLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.documentlibrary.service.impl.DLFolderLocalServiceImpl</code>.
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
 * @see com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceFactory
 * @see com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceUtil
 *
 */
public interface DLFolderLocalService {
	public com.liferay.portlet.documentlibrary.model.DLFolder addDLFolder(
		com.liferay.portlet.documentlibrary.model.DLFolder model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.documentlibrary.model.DLFolder updateDLFolder(
		com.liferay.portlet.documentlibrary.model.DLFolder model)
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

	public com.liferay.portal.service.persistence.LayoutPersistence getLayoutPersistence();

	public void setLayoutPersistence(
		com.liferay.portal.service.persistence.LayoutPersistence layoutPersistence);

	public com.liferay.portal.service.persistence.LayoutFinder getLayoutFinder();

	public void setLayoutFinder(
		com.liferay.portal.service.persistence.LayoutFinder layoutFinder);

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

	public com.liferay.portlet.documentlibrary.model.DLFolder addFolder(
		long userId, long plid, long parentFolderId, java.lang.String name,
		java.lang.String description, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFolder addFolder(
		java.lang.String uuid, long userId, long plid, long parentFolderId,
		java.lang.String name, java.lang.String description,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFolder addFolder(
		long userId, long plid, long parentFolderId, java.lang.String name,
		java.lang.String description, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFolder addFolder(
		java.lang.String uuid, long userId, long plid, long parentFolderId,
		java.lang.String name, java.lang.String description,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFolder addFolderToGroup(
		java.lang.String uuid, long userId, long groupId, long parentFolderId,
		java.lang.String name, java.lang.String description,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFolderResources(long folderId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFolderResources(
		com.liferay.portlet.documentlibrary.model.DLFolder folder,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFolderResources(long folderId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addFolderResources(
		com.liferay.portlet.documentlibrary.model.DLFolder folder,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFolder(long folderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFolder(
		com.liferay.portlet.documentlibrary.model.DLFolder folder)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteFolders(long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFolder getFolder(
		long folderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFolder getFolder(
		long groupId, long parentFolderId, java.lang.String name)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getFolders(long companyId)
		throws com.liferay.portal.SystemException;

	public java.util.List getFolders(long groupId, long parentFolderId)
		throws com.liferay.portal.SystemException;

	public java.util.List getFolders(long groupId, long parentFolderId,
		int begin, int end) throws com.liferay.portal.SystemException;

	public int getFoldersCount(long groupId, long parentFolderId)
		throws com.liferay.portal.SystemException;

	public void getSubfolderIds(java.util.List folderIds, long groupId,
		long folderId) throws com.liferay.portal.SystemException;

	public void reIndex(java.lang.String[] ids)
		throws com.liferay.portal.SystemException;

	public com.liferay.portal.kernel.search.Hits search(long companyId,
		long groupId, long[] folderIds, java.lang.String keywords)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.documentlibrary.model.DLFolder updateFolder(
		long folderId, long parentFolderId, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}