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
 * <a href="PortletUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletUtil {
	public static com.liferay.portal.model.Portlet create(long id) {
		return getPersistence().create(id);
	}

	public static com.liferay.portal.model.Portlet remove(long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPortletException {
		return getPersistence().remove(id);
	}

	public static com.liferay.portal.model.Portlet remove(
		com.liferay.portal.model.Portlet portlet)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(portlet);
	}

	public static com.liferay.portal.model.Portlet update(
		com.liferay.portal.model.Portlet portlet)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(portlet);
	}

	public static com.liferay.portal.model.Portlet update(
		com.liferay.portal.model.Portlet portlet, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(portlet, merge);
	}

	public static com.liferay.portal.model.Portlet updateImpl(
		com.liferay.portal.model.Portlet portlet, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(portlet, merge);
	}

	public static com.liferay.portal.model.Portlet findByPrimaryKey(long id)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPortletException {
		return getPersistence().findByPrimaryKey(id);
	}

	public static com.liferay.portal.model.Portlet fetchByPrimaryKey(long id)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(id);
	}

	public static java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portal.model.Portlet findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPortletException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Portlet findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPortletException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Portlet[] findByCompanyId_PrevAndNext(
		long id, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPortletException {
		return getPersistence().findByCompanyId_PrevAndNext(id, companyId, obc);
	}

	public static com.liferay.portal.model.Portlet findByC_P(long companyId,
		java.lang.String portletId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPortletException {
		return getPersistence().findByC_P(companyId, portletId);
	}

	public static com.liferay.portal.model.Portlet fetchByC_P(long companyId,
		java.lang.String portletId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_P(companyId, portletId);
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

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByC_P(long companyId, java.lang.String portletId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPortletException {
		getPersistence().removeByC_P(companyId, portletId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByC_P(long companyId, java.lang.String portletId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_P(companyId, portletId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static PortletPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PortletPersistence persistence) {
		_persistence = persistence;
	}

	private static PortletUtil _getUtil() {
		if (_util == null) {
			_util = (PortletUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PortletUtil.class.getName();
	private static PortletUtil _util;
	private PortletPersistence _persistence;
}