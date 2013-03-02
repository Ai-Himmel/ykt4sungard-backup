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
 * <a href="WebDAVPropsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WebDAVPropsUtil {
	public static com.liferay.portal.model.WebDAVProps create(
		long webDavPropsId) {
		return getPersistence().create(webDavPropsId);
	}

	public static com.liferay.portal.model.WebDAVProps remove(
		long webDavPropsId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchWebDAVPropsException {
		return getPersistence().remove(webDavPropsId);
	}

	public static com.liferay.portal.model.WebDAVProps remove(
		com.liferay.portal.model.WebDAVProps webDAVProps)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(webDAVProps);
	}

	public static com.liferay.portal.model.WebDAVProps update(
		com.liferay.portal.model.WebDAVProps webDAVProps)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(webDAVProps);
	}

	public static com.liferay.portal.model.WebDAVProps update(
		com.liferay.portal.model.WebDAVProps webDAVProps, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(webDAVProps, merge);
	}

	public static com.liferay.portal.model.WebDAVProps updateImpl(
		com.liferay.portal.model.WebDAVProps webDAVProps, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(webDAVProps, merge);
	}

	public static com.liferay.portal.model.WebDAVProps findByPrimaryKey(
		long webDavPropsId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchWebDAVPropsException {
		return getPersistence().findByPrimaryKey(webDavPropsId);
	}

	public static com.liferay.portal.model.WebDAVProps fetchByPrimaryKey(
		long webDavPropsId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(webDavPropsId);
	}

	public static com.liferay.portal.model.WebDAVProps findByC_C(
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchWebDAVPropsException {
		return getPersistence().findByC_C(classNameId, classPK);
	}

	public static com.liferay.portal.model.WebDAVProps fetchByC_C(
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_C(classNameId, classPK);
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

	public static void removeByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchWebDAVPropsException {
		getPersistence().removeByC_C(classNameId, classPK);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C(classNameId, classPK);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static WebDAVPropsPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(WebDAVPropsPersistence persistence) {
		_persistence = persistence;
	}

	private static WebDAVPropsUtil _getUtil() {
		if (_util == null) {
			_util = (WebDAVPropsUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = WebDAVPropsUtil.class.getName();
	private static WebDAVPropsUtil _util;
	private WebDAVPropsPersistence _persistence;
}