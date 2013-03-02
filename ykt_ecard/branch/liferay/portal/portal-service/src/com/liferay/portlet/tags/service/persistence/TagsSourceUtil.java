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

package com.liferay.portlet.tags.service.persistence;

/**
 * <a href="TagsSourceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsSourceUtil {
	public static com.liferay.portlet.tags.model.TagsSource create(
		long sourceId) {
		return getPersistence().create(sourceId);
	}

	public static com.liferay.portlet.tags.model.TagsSource remove(
		long sourceId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchSourceException {
		return getPersistence().remove(sourceId);
	}

	public static com.liferay.portlet.tags.model.TagsSource remove(
		com.liferay.portlet.tags.model.TagsSource tagsSource)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(tagsSource);
	}

	public static com.liferay.portlet.tags.model.TagsSource update(
		com.liferay.portlet.tags.model.TagsSource tagsSource)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(tagsSource);
	}

	public static com.liferay.portlet.tags.model.TagsSource update(
		com.liferay.portlet.tags.model.TagsSource tagsSource, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(tagsSource, merge);
	}

	public static com.liferay.portlet.tags.model.TagsSource updateImpl(
		com.liferay.portlet.tags.model.TagsSource tagsSource, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(tagsSource, merge);
	}

	public static com.liferay.portlet.tags.model.TagsSource findByPrimaryKey(
		long sourceId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.tags.NoSuchSourceException {
		return getPersistence().findByPrimaryKey(sourceId);
	}

	public static com.liferay.portlet.tags.model.TagsSource fetchByPrimaryKey(
		long sourceId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(sourceId);
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

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static TagsSourcePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(TagsSourcePersistence persistence) {
		_persistence = persistence;
	}

	private static TagsSourceUtil _getUtil() {
		if (_util == null) {
			_util = (TagsSourceUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = TagsSourceUtil.class.getName();
	private static TagsSourceUtil _util;
	private TagsSourcePersistence _persistence;
}