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

package com.liferay.portlet.imagegallery.service.persistence;

/**
 * <a href="IGImagePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface IGImagePersistence {
	public com.liferay.portlet.imagegallery.model.IGImage create(long imageId);

	public com.liferay.portlet.imagegallery.model.IGImage remove(long imageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public com.liferay.portlet.imagegallery.model.IGImage remove(
		com.liferay.portlet.imagegallery.model.IGImage igImage)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage update(
		com.liferay.portlet.imagegallery.model.IGImage igImage)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage update(
		com.liferay.portlet.imagegallery.model.IGImage igImage, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage updateImpl(
		com.liferay.portlet.imagegallery.model.IGImage igImage, boolean merge)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage findByPrimaryKey(
		long imageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public com.liferay.portlet.imagegallery.model.IGImage fetchByPrimaryKey(
		long imageId) throws com.liferay.portal.SystemException;

	public java.util.List findByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUuid(java.lang.String uuid, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByUuid(java.lang.String uuid, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public com.liferay.portlet.imagegallery.model.IGImage findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public com.liferay.portlet.imagegallery.model.IGImage[] findByUuid_PrevAndNext(
		long imageId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public java.util.List findByFolderId(long folderId)
		throws com.liferay.portal.SystemException;

	public java.util.List findByFolderId(long folderId, int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findByFolderId(long folderId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage findByFolderId_First(
		long folderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public com.liferay.portlet.imagegallery.model.IGImage findByFolderId_Last(
		long folderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public com.liferay.portlet.imagegallery.model.IGImage[] findByFolderId_PrevAndNext(
		long imageId, long folderId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public com.liferay.portlet.imagegallery.model.IGImage findBySmallImageId(
		long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public com.liferay.portlet.imagegallery.model.IGImage fetchBySmallImageId(
		long smallImageId) throws com.liferay.portal.SystemException;

	public com.liferay.portlet.imagegallery.model.IGImage findByLargeImageId(
		long largeImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public com.liferay.portlet.imagegallery.model.IGImage fetchByLargeImageId(
		long largeImageId) throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException;

	public java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException;

	public java.util.List findAll() throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException;

	public java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException;

	public void removeByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException;

	public void removeByFolderId(long folderId)
		throws com.liferay.portal.SystemException;

	public void removeBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public void removeByLargeImageId(long largeImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException;

	public void removeAll() throws com.liferay.portal.SystemException;

	public int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException;

	public int countByFolderId(long folderId)
		throws com.liferay.portal.SystemException;

	public int countBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException;

	public int countByLargeImageId(long largeImageId)
		throws com.liferay.portal.SystemException;

	public int countAll() throws com.liferay.portal.SystemException;
}