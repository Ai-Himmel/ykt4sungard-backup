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

package com.liferay.portal.deploy.auto;

import com.liferay.portal.deploy.DeployUtil;
import com.liferay.portal.kernel.deploy.auto.AutoDeployException;
import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.util.Validator;

import java.io.File;

import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

/**
 * <a href="WAIAutoDeployer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class WAIAutoDeployer extends PortletAutoDeployer {

	protected WAIAutoDeployer() throws AutoDeployException {
		try {
			jars.add(DeployUtil.getResourcePath("portals-bridges.jar"));
		}
		catch (Exception e) {
			throw new AutoDeployException(e);
		}
	}

	protected void copyXmls(
			File srcFile, String displayName, PluginPackage pluginPackage)
		throws Exception {

		super.copyXmls(srcFile, displayName, pluginPackage);

		String portletName = displayName;

		if (pluginPackage != null) {
			portletName = pluginPackage.getName();
		}

		Map filterMap = new HashMap();

		filterMap.put("portlet_name", displayName);
		filterMap.put("portlet_title", portletName);
		filterMap.put("restore_current_view", "false");

		if (pluginPackage != null) {
			Properties settings = pluginPackage.getDeploymentSettings();

			filterMap.put(
				"portlet_class",
				settings.getProperty(
					"wai.portlet", "com.liferay.util.bridges.wai.WAIPortlet"));

			filterMap.put(
				"friendly_url_mapper_class",
				settings.getProperty(
					"wai.friendly.url.mapper",
					"com.liferay.portlet.WAIFriendlyURLMapper"));
		}
		else {
			filterMap.put(
				"portlet_class", "com.liferay.util.bridges.wai.WAIPortlet");

			filterMap.put(
				"friendly_url_mapper_class",
				"com.liferay.portlet.WAIFriendlyURLMapper");
		}

		_setInitParams(filterMap, pluginPackage);

		copyDependencyXml(
			"liferay-display.xml", srcFile + "/WEB-INF", filterMap);
		copyDependencyXml(
			"liferay-portlet.xml", srcFile + "/WEB-INF", filterMap);
		copyDependencyXml(
			"portlet.xml", srcFile + "/WEB-INF", filterMap);
		copyDependencyXml(
			"normal_window_state.jsp", srcFile + "/WEB-INF/jsp/liferay/wai");
		copyDependencyXml("iframe.jsp", srcFile + "/WEB-INF/jsp/liferay/wai");

	}

	private void _setInitParams(Map filterMap, PluginPackage pluginPackage) {
		for (int i = 0; i < _INIT_PARAM_NAMES.length; i++) {
			String name = _INIT_PARAM_NAMES[i];

			String value = null;

			if (pluginPackage != null) {
				pluginPackage.getDeploymentSettings().getProperty(name);
			}

			if (Validator.isNull(value)) {
				value = _INIT_PARAM_DEFAULT_VALUES[i];
			}

			filterMap.put("init_param_name_" + i, name);
			filterMap.put("init_param_value_" + i, value);
		}
	}

	private static String[] _INIT_PARAM_NAMES = new String[] {
		"wai.connector", "wai.connector.iframe.height.extra"
	};

	private static String[] _INIT_PARAM_DEFAULT_VALUES = new String[] {
		"iframe", "40"
	};

}