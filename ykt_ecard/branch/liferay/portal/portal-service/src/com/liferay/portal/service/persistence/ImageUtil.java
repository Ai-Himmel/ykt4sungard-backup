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

package com.liferay.portal.service.persistence;

/**
 * <a href="ImageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ImageUtil {
	public static com.liferay.portal.model.Image create(long imageId) {
		return getPersistence().create(imageId);
	}

	public static com.liferay.portal.model.Image remove(long imageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchImageException {
		return getPersistence().remove(imageId);
	}

	public static com.liferay.portal.model.Image remove(
		com.liferay.portal.model.Image image)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(image);
	}

	public static com.liferay.portal.model.Image update(
		com.liferay.portal.model.Image image)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(image);
	}

	public static com.liferay.portal.model.Image update(
		com.liferay.portal.model.Image image, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(image, merge);
	}

	public static com.liferay.portal.model.Image updateImpl(
		com.liferay.portal.model.Image image, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(image, merge);
	}

	public static com.liferay.portal.model.Image findByPrimaryKey(long imageId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchImageException {
		return getPersistence().findByPrimaryKey(imageId);
	}

	public static com.liferay.portal.model.Image fetchByPrimaryKey(long imageId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(imageId);
	}

	public static java.util.List findBySize(int size)
		throws com.liferay.portal.SystemException {
		return getPersistence().findBySize(size);
	}

	public static java.util.List findBySize(int size, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findBySize(size, begin, end);
	}

	public static java.util.List findBySize(int size, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findBySize(size, begin, end, obc);
	}

	public static com.liferay.portal.model.Image findBySize_First(int size,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchImageException {
		return getPersistence().findBySize_First(size, obc);
	}

	public static com.liferay.portal.model.Image findBySize_Last(int size,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchImageException {
		return getPersistence().findBySize_Last(size, obc);
	}

	public static com.liferay.portal.model.Image[] findBySize_PrevAndNext(
		long imageId, int size,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchImageException {
		return getPersistence().findBySize_PrevAndNext(imageId, size, obc);
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

	public static void removeBySize(int size)
		throws com.liferay.portal.SystemException {
		getPersistence().removeBySize(size);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countBySize(int size)
		throws com.liferay.portal.SystemException {
		return getPersistence().countBySize(size);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static ImagePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(ImagePersistence persistence) {
		_persistence = persistence;
	}

	private static ImageUtil _getUtil() {
		if (_util == null) {
			_util = (ImageUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ImageUtil.class.getName();
	private static ImageUtil _util;
	private ImagePersistence _persistence;
}