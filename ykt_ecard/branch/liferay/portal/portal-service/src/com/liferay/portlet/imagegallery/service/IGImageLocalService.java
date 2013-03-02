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

package com.liferay.portlet.imagegallery.service;


/**
 * <a href="IGImageLocalService.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface defines the service. The default implementation is
 * <code>com.liferay.portlet.imagegallery.service.impl.IGImageLocalServiceImpl</code>.
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
 * @see com.liferay.portlet.imagegallery.service.IGImageLocalServiceFactory
 * @see com.liferay.portlet.imagegallery.service.IGImageLocalServiceUtil
 *
 */
public interface IGImageLocalService {
	public com.liferay.portlet.imagegallery.model.IGImage addIGImage(
		com.liferay.portlet.imagegallery.model.IGImage model)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage updateIGImage(
		com.liferay.portlet.imagegallery.model.IGImage model)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.service.persistence.IGFolderPersistence getIGFolderPersistence();

	public void setIGFolderPersistence(
		com.liferay.portlet.imagegallery.service.persistence.IGFolderPersistence igFolderPersistence);

	public com.liferay.portlet.imagegallery.service.persistence.IGImagePersistence getIGImagePersistence();

	public void setIGImagePersistence(
		com.liferay.portlet.imagegallery.service.persistence.IGImagePersistence igImagePersistence);

	public com.liferay.portlet.imagegallery.service.persistence.IGImageFinder getIGImageFinder();

	public void setIGImageFinder(
		com.liferay.portlet.imagegallery.service.persistence.IGImageFinder igImageFinder);

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

	public com.liferay.portlet.tags.service.persistence.TagsAssetPersistence getTagsAssetPersistence();

	public void setTagsAssetPersistence(
		com.liferay.portlet.tags.service.persistence.TagsAssetPersistence tagsAssetPersistence);

	public com.liferay.portlet.tags.service.persistence.TagsAssetFinder getTagsAssetFinder();

	public void setTagsAssetFinder(
		com.liferay.portlet.tags.service.persistence.TagsAssetFinder tagsAssetFinder);

	public void afterPropertiesSet();

	public com.liferay.portlet.imagegallery.model.IGImage addImage(
		long userId, long folderId, java.lang.String description,
		java.io.File file, java.lang.String contentType,
		java.lang.String[] tagsEntries, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.imagegallery.model.IGImage addImage(
		java.lang.String uuid, long userId, long folderId,
		java.lang.String description, java.io.File file,
		java.lang.String contentType, java.lang.String[] tagsEntries,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.imagegallery.model.IGImage addImage(
		long userId, long folderId, java.lang.String description,
		java.io.File file, java.lang.String contentType,
		java.lang.String[] tagsEntries,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.imagegallery.model.IGImage addImage(
		java.lang.String uuid, long userId, long folderId,
		java.lang.String description, java.io.File file,
		java.lang.String contentType, java.lang.String[] tagsEntries,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addImageResources(long folderId, long imageId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addImageResources(
		com.liferay.portlet.imagegallery.model.IGFolder folder,
		com.liferay.portlet.imagegallery.model.IGImage image,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addImageResources(long folderId, long imageId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void addImageResources(
		com.liferay.portlet.imagegallery.model.IGFolder folder,
		com.liferay.portlet.imagegallery.model.IGImage image,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteImage(long imageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteImage(
		com.liferay.portlet.imagegallery.model.IGImage image)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void deleteImages(long folderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public int getFoldersImagesCount(java.util.List folderIds)
		throws com.liferay.portal.SystemException;

	public java.util.List getGroupImages(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getGroupImages(long groupId, long userId, int begin,
		int end) throws com.liferay.portal.SystemException;

	public int getGroupImagesCount(long groupId)
		throws com.liferay.portal.SystemException;

	public int getGroupImagesCount(long groupId, long userId)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage getImage(long imageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.imagegallery.model.IGImage getImageByLargeImageId(
		long largeImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.imagegallery.model.IGImage getImageBySmallImageId(
		long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portlet.imagegallery.model.IGImage getImageByUuidAndGroupId(
		java.lang.String uuid, long groupId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.util.List getImages(long folderId)
		throws com.liferay.portal.SystemException;

	public java.util.List getImages(long folderId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List getImages(long folderId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public int getImagesCount(long folderId)
		throws com.liferay.portal.SystemException;

	public java.util.List getNoAssetImages()
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage updateImage(
		long userId, long imageId, long folderId, java.lang.String description,
		java.io.File file, java.lang.String contentType,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public void updateTagsAsset(long userId,
		com.liferay.portlet.imagegallery.model.IGImage image,
		java.lang.String[] tagsEntries)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;
}