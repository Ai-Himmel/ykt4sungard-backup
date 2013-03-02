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
 * <a href="PluginSettingUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PluginSettingUtil {
	public static com.liferay.portal.model.PluginSetting create(
		long pluginSettingId) {
		return getPersistence().create(pluginSettingId);
	}

	public static com.liferay.portal.model.PluginSetting remove(
		long pluginSettingId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPluginSettingException {
		return getPersistence().remove(pluginSettingId);
	}

	public static com.liferay.portal.model.PluginSetting remove(
		com.liferay.portal.model.PluginSetting pluginSetting)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(pluginSetting);
	}

	public static com.liferay.portal.model.PluginSetting update(
		com.liferay.portal.model.PluginSetting pluginSetting)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(pluginSetting);
	}

	public static com.liferay.portal.model.PluginSetting update(
		com.liferay.portal.model.PluginSetting pluginSetting, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(pluginSetting, merge);
	}

	public static com.liferay.portal.model.PluginSetting updateImpl(
		com.liferay.portal.model.PluginSetting pluginSetting, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(pluginSetting, merge);
	}

	public static com.liferay.portal.model.PluginSetting findByPrimaryKey(
		long pluginSettingId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPluginSettingException {
		return getPersistence().findByPrimaryKey(pluginSettingId);
	}

	public static com.liferay.portal.model.PluginSetting fetchByPrimaryKey(
		long pluginSettingId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(pluginSettingId);
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

	public static com.liferay.portal.model.PluginSetting findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPluginSettingException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.PluginSetting findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPluginSettingException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.PluginSetting[] findByCompanyId_PrevAndNext(
		long pluginSettingId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPluginSettingException {
		return getPersistence().findByCompanyId_PrevAndNext(pluginSettingId,
			companyId, obc);
	}

	public static com.liferay.portal.model.PluginSetting findByC_I_T(
		long companyId, java.lang.String pluginId, java.lang.String pluginType)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPluginSettingException {
		return getPersistence().findByC_I_T(companyId, pluginId, pluginType);
	}

	public static com.liferay.portal.model.PluginSetting fetchByC_I_T(
		long companyId, java.lang.String pluginId, java.lang.String pluginType)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_I_T(companyId, pluginId, pluginType);
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

	public static void removeByC_I_T(long companyId, java.lang.String pluginId,
		java.lang.String pluginType)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPluginSettingException {
		getPersistence().removeByC_I_T(companyId, pluginId, pluginType);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByC_I_T(long companyId, java.lang.String pluginId,
		java.lang.String pluginType) throws com.liferay.portal.SystemException {
		return getPersistence().countByC_I_T(companyId, pluginId, pluginType);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static PluginSettingPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PluginSettingPersistence persistence) {
		_persistence = persistence;
	}

	private static PluginSettingUtil _getUtil() {
		if (_util == null) {
			_util = (PluginSettingUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PluginSettingUtil.class.getName();
	private static PluginSettingUtil _util;
	private PluginSettingPersistence _persistence;
}