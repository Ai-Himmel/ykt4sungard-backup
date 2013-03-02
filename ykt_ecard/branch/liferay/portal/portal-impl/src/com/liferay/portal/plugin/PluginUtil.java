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

package com.liferay.portal.plugin;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Plugin;
import com.liferay.portal.model.PluginSetting;
import com.liferay.portal.model.User;
import com.liferay.portal.service.PluginSettingLocalServiceUtil;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="PluginUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PluginUtil {

	public static List restrictPlugins(List plugins, User user)
		throws PortalException, SystemException {

		return restrictPlugins(plugins, user.getCompanyId(), user.getUserId());
	}

	public static List restrictPlugins(
			List plugins, long companyId, long userId)
		throws PortalException, SystemException {

		List visiblePlugins = new ArrayList(plugins.size());

		for (int i = 0; i < plugins.size(); i++) {
			Plugin plugin = (Plugin)plugins.get(i);

			PluginSetting pluginSetting =
				PluginSettingLocalServiceUtil.getPluginSetting(
					companyId, plugin.getPluginId(), plugin.getPluginType());

			if (pluginSetting.isActive() &&
				pluginSetting.hasPermission(userId)) {

				visiblePlugins.add(plugin);
			}
		}

		return visiblePlugins;
	}

}