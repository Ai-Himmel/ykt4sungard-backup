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

package com.liferay.portal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Plugin;
import com.liferay.portal.model.PluginSetting;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.LayoutTemplateImpl;
import com.liferay.portal.model.impl.PluginSettingImpl;
import com.liferay.portal.model.impl.ThemeImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.base.PluginSettingLocalServiceBaseImpl;
import com.liferay.portal.util.PortalUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PluginSettingLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Jorge Ferrer
 *
 */
public class PluginSettingLocalServiceImpl
	extends PluginSettingLocalServiceBaseImpl {

	public void checkPermission(
			long userId, String pluginId, String pluginType)
		throws PortalException {

		if (!hasPermission(userId, pluginId, pluginType)) {
			throw new PrincipalException();
		}
	}

	public PluginSetting getDefaultPluginSetting() {
		PluginSettingImpl pluginSetting = new PluginSettingImpl();

		pluginSetting.setRoles(StringPool.BLANK);
		pluginSetting.setActive(true);

		return pluginSetting;
	}

	public PluginSetting getPluginSetting(
			long companyId, String pluginId, String pluginType)
		throws PortalException, SystemException {

		PluginSetting pluginSetting = pluginSettingPersistence.fetchByC_I_T(
			companyId, pluginId, pluginType);

		if (pluginSetting == null) {
			Plugin plugin = null;

			if (pluginType.equals(LayoutTemplateImpl.PLUGIN_TYPE)) {
				plugin = LayoutTemplateLocalUtil.getLayoutTemplate(
					pluginId, false, null);
			}
			else if (pluginType.equals(ThemeImpl.PLUGIN_TYPE)) {
				boolean wapTheme = true;

				plugin = ThemeLocalUtil.getTheme(companyId, pluginId, wapTheme);
			}

			if ((plugin == null) ||
				(plugin.getDefaultPluginSetting() == null)) {

				pluginSetting = getDefaultPluginSetting();

				pluginSetting.setCompanyId(companyId);
			}
			else {
				pluginSetting = plugin.getDefaultPluginSetting(companyId);
			}
		}

		return pluginSetting;
	}

	public boolean hasPermission(
		long userId, String pluginId, String pluginType) {

		try {
			User user = userPersistence.findByPrimaryKey(userId);

			PluginSetting pluginSetting = getPluginSetting(
				user.getCompanyId(), pluginId, pluginType);

			if (!pluginSetting.hasPermission(userId)) {
				return false;
			}
			else {
				return true;
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Could not check permissions for " + pluginId, e);
			}

			return false;
		}
	}

	public PluginSetting updatePluginSetting(
			long companyId, String pluginId, String pluginType, String roles,
			boolean active)
		throws PortalException, SystemException {

		pluginId = PortalUtil.getJsSafePortletId(pluginId);

		PluginSetting pluginSetting = pluginSettingPersistence.fetchByC_I_T(
			companyId, pluginId, pluginType);

		if (pluginSetting == null) {
			long pluginSettingId = counterLocalService.increment();

			pluginSetting = pluginSettingPersistence.create(pluginSettingId);

			pluginSetting.setCompanyId(companyId);
			pluginSetting.setPluginId(pluginId);
			pluginSetting.setPluginType(pluginType);
		}

		pluginSetting.setRoles(roles);
		pluginSetting.setActive(active);

		pluginSettingPersistence.update(pluginSetting);

		return pluginSetting;
	}

	private static Log _log =
		LogFactory.getLog(PluginSettingLocalServiceImpl.class);

}