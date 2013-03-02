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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.model.Plugin;
import com.liferay.portal.model.PluginSetting;
import com.liferay.util.CollectionFactory;

import java.util.Map;

/**
 * <a href="PluginBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public abstract class PluginBaseImpl implements Plugin {

	public PluginPackage getPluginPackage() {
		return _pluginPackage;
	}

	public void setPluginPackage(PluginPackage pluginPackage) {
		_pluginPackage = pluginPackage;
	}

	public PluginSetting getDefaultPluginSetting() {
		return _defaultPluginSetting;
	}

	public PluginSetting getDefaultPluginSetting(long companyId) {
		Long companyIdObj = new Long(companyId);

		PluginSetting setting = (PluginSetting)_defaultPluginSettings.get(
			companyIdObj);

		if (setting == null) {
			setting = new PluginSettingImpl(_defaultPluginSetting);

			setting.setCompanyId(companyId);

			_defaultPluginSettings.put(companyIdObj, setting);
		}

		return setting;
	}

	public void setDefaultPluginSetting(PluginSetting pluginSetting) {
		_defaultPluginSetting = pluginSetting;
	}

	private PluginPackage _pluginPackage;
	private PluginSetting _defaultPluginSetting;
	private Map _defaultPluginSettings = CollectionFactory.getHashMap();

}