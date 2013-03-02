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
 * <a href="ResourceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ResourceUtil {
	public static com.liferay.portal.model.Resource create(long resourceId) {
		return getPersistence().create(resourceId);
	}

	public static com.liferay.portal.model.Resource remove(long resourceId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceException {
		return getPersistence().remove(resourceId);
	}

	public static com.liferay.portal.model.Resource remove(
		com.liferay.portal.model.Resource resource)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(resource);
	}

	public static com.liferay.portal.model.Resource update(
		com.liferay.portal.model.Resource resource)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(resource);
	}

	public static com.liferay.portal.model.Resource update(
		com.liferay.portal.model.Resource resource, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(resource, merge);
	}

	public static com.liferay.portal.model.Resource updateImpl(
		com.liferay.portal.model.Resource resource, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(resource, merge);
	}

	public static com.liferay.portal.model.Resource findByPrimaryKey(
		long resourceId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceException {
		return getPersistence().findByPrimaryKey(resourceId);
	}

	public static com.liferay.portal.model.Resource fetchByPrimaryKey(
		long resourceId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(resourceId);
	}

	public static java.util.List findByCodeId(long codeId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCodeId(codeId);
	}

	public static java.util.List findByCodeId(long codeId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCodeId(codeId, begin, end);
	}

	public static java.util.List findByCodeId(long codeId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCodeId(codeId, begin, end, obc);
	}

	public static com.liferay.portal.model.Resource findByCodeId_First(
		long codeId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceException {
		return getPersistence().findByCodeId_First(codeId, obc);
	}

	public static com.liferay.portal.model.Resource findByCodeId_Last(
		long codeId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceException {
		return getPersistence().findByCodeId_Last(codeId, obc);
	}

	public static com.liferay.portal.model.Resource[] findByCodeId_PrevAndNext(
		long resourceId, long codeId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceException {
		return getPersistence().findByCodeId_PrevAndNext(resourceId, codeId, obc);
	}

	public static com.liferay.portal.model.Resource findByC_P(long codeId,
		java.lang.String primKey)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceException {
		return getPersistence().findByC_P(codeId, primKey);
	}

	public static com.liferay.portal.model.Resource fetchByC_P(long codeId,
		java.lang.String primKey) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_P(codeId, primKey);
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

	public static void removeByCodeId(long codeId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCodeId(codeId);
	}

	public static void removeByC_P(long codeId, java.lang.String primKey)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchResourceException {
		getPersistence().removeByC_P(codeId, primKey);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCodeId(long codeId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCodeId(codeId);
	}

	public static int countByC_P(long codeId, java.lang.String primKey)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_P(codeId, primKey);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static ResourcePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(ResourcePersistence persistence) {
		_persistence = persistence;
	}

	private static ResourceUtil _getUtil() {
		if (_util == null) {
			_util = (ResourceUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ResourceUtil.class.getName();
	private static ResourceUtil _util;
	private ResourcePersistence _persistence;
}