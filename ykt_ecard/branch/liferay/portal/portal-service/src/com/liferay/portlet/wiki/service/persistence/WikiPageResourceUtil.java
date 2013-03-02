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

package com.liferay.portlet.wiki.service.persistence;

/**
 * <a href="WikiPageResourceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WikiPageResourceUtil {
	public static com.liferay.portlet.wiki.model.WikiPageResource create(
		long resourcePrimKey) {
		return getPersistence().create(resourcePrimKey);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource remove(
		long resourcePrimKey)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.wiki.NoSuchPageResourceException {
		return getPersistence().remove(resourcePrimKey);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource remove(
		com.liferay.portlet.wiki.model.WikiPageResource wikiPageResource)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(wikiPageResource);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource update(
		com.liferay.portlet.wiki.model.WikiPageResource wikiPageResource)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(wikiPageResource);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource update(
		com.liferay.portlet.wiki.model.WikiPageResource wikiPageResource,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(wikiPageResource, merge);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource updateImpl(
		com.liferay.portlet.wiki.model.WikiPageResource wikiPageResource,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(wikiPageResource, merge);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource findByPrimaryKey(
		long resourcePrimKey)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.wiki.NoSuchPageResourceException {
		return getPersistence().findByPrimaryKey(resourcePrimKey);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource fetchByPrimaryKey(
		long resourcePrimKey) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(resourcePrimKey);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource findByN_T(
		long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.wiki.NoSuchPageResourceException {
		return getPersistence().findByN_T(nodeId, title);
	}

	public static com.liferay.portlet.wiki.model.WikiPageResource fetchByN_T(
		long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByN_T(nodeId, title);
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

	public static void removeByN_T(long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.wiki.NoSuchPageResourceException {
		getPersistence().removeByN_T(nodeId, title);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByN_T(long nodeId, java.lang.String title)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByN_T(nodeId, title);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static WikiPageResourcePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(WikiPageResourcePersistence persistence) {
		_persistence = persistence;
	}

	private static WikiPageResourceUtil _getUtil() {
		if (_util == null) {
			_util = (WikiPageResourceUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = WikiPageResourceUtil.class.getName();
	private static WikiPageResourceUtil _util;
	private WikiPageResourcePersistence _persistence;
}