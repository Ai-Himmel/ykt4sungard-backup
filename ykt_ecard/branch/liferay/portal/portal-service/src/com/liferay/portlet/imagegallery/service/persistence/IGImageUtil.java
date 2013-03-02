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
 * <a href="IGImageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class IGImageUtil {
	public static com.liferay.portlet.imagegallery.model.IGImage create(
		long imageId) {
		return getPersistence().create(imageId);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage remove(
		long imageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().remove(imageId);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage remove(
		com.liferay.portlet.imagegallery.model.IGImage igImage)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(igImage);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage update(
		com.liferay.portlet.imagegallery.model.IGImage igImage)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(igImage);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage update(
		com.liferay.portlet.imagegallery.model.IGImage igImage, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(igImage, merge);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage updateImpl(
		com.liferay.portlet.imagegallery.model.IGImage igImage, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(igImage, merge);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByPrimaryKey(
		long imageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().findByPrimaryKey(imageId);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage fetchByPrimaryKey(
		long imageId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(imageId);
	}

	public static java.util.List findByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end);
	}

	public static java.util.List findByUuid(java.lang.String uuid, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUuid(uuid, begin, end, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByUuid_First(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().findByUuid_First(uuid, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByUuid_Last(
		java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().findByUuid_Last(uuid, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage[] findByUuid_PrevAndNext(
		long imageId, java.lang.String uuid,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().findByUuid_PrevAndNext(imageId, uuid, obc);
	}

	public static java.util.List findByFolderId(long folderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByFolderId(folderId);
	}

	public static java.util.List findByFolderId(long folderId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByFolderId(folderId, begin, end);
	}

	public static java.util.List findByFolderId(long folderId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByFolderId(folderId, begin, end, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByFolderId_First(
		long folderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().findByFolderId_First(folderId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByFolderId_Last(
		long folderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().findByFolderId_Last(folderId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage[] findByFolderId_PrevAndNext(
		long imageId, long folderId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().findByFolderId_PrevAndNext(imageId, folderId,
			obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findBySmallImageId(
		long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().findBySmallImageId(smallImageId);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage fetchBySmallImageId(
		long smallImageId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchBySmallImageId(smallImageId);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByLargeImageId(
		long largeImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		return getPersistence().findByLargeImageId(largeImageId);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage fetchByLargeImageId(
		long largeImageId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByLargeImageId(largeImageId);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer, begin,
			end);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll();
	}

	public static java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end);
	}

	public static java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end, obc);
	}

	public static void removeByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUuid(uuid);
	}

	public static void removeByFolderId(long folderId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByFolderId(folderId);
	}

	public static void removeBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		getPersistence().removeBySmallImageId(smallImageId);
	}

	public static void removeByLargeImageId(long largeImageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.imagegallery.NoSuchImageException {
		getPersistence().removeByLargeImageId(largeImageId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUuid(java.lang.String uuid)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUuid(uuid);
	}

	public static int countByFolderId(long folderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByFolderId(folderId);
	}

	public static int countBySmallImageId(long smallImageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countBySmallImageId(smallImageId);
	}

	public static int countByLargeImageId(long largeImageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByLargeImageId(largeImageId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static IGImagePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(IGImagePersistence persistence) {
		_persistence = persistence;
	}

	private static IGImageUtil _getUtil() {
		if (_util == null) {
			_util = (IGImageUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = IGImageUtil.class.getName();
	private static IGImageUtil _util;
	private IGImagePersistence _persistence;
}