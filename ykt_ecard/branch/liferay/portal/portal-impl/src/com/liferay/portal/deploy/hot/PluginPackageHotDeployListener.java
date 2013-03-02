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

package com.liferay.portal.deploy.hot;

import com.liferay.portal.kernel.deploy.hot.HotDeployEvent;
import com.liferay.portal.kernel.deploy.hot.HotDeployException;
import com.liferay.portal.kernel.deploy.hot.HotDeployListener;
import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.plugin.PluginPackageImpl;
import com.liferay.portal.plugin.PluginPackageUtil;
import com.liferay.util.Http;
import com.liferay.util.Version;

import java.io.IOException;
import java.io.InputStream;

import java.util.jar.Attributes;
import java.util.jar.Manifest;

import javax.servlet.ServletContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.DocumentException;

/**
 * <a href="PluginPackageHotDeployListener.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Jorge Ferrer
 *
 */
public class PluginPackageHotDeployListener implements HotDeployListener {

	public static PluginPackage readPluginPackage(ServletContext ctx)
		throws DocumentException, IOException {

		PluginPackage pluginPackage = null;

		String servletContextName = ctx.getServletContextName();

		String xml = Http.URLtoString(
			ctx.getResource("/WEB-INF/liferay-plugin-package.xml"));

		if (_log.isInfoEnabled()) {
			if (servletContextName == null) {
				_log.info("Reading plugin package for the root context");
			}
			else {
				_log.info("Reading plugin package for " + servletContextName);
			}
		}

		if (xml == null) {
			if (_log.isDebugEnabled()) {
				_log.debug("Reading plugin package from MANIFEST.MF");
			}

			Attributes attributes = null;

			InputStream is = ctx.getResourceAsStream("/META-INF/MANIFEST.MF");

			if (is != null) {
				Manifest manifest = new Manifest(is);

				attributes = manifest.getMainAttributes();
			}
			else {
				attributes = new Attributes();
			}

			String artifactGroupId = attributes.getValue(
				"Implementation-Vendor-Id");

			if (Validator.isNull(artifactGroupId)) {
				artifactGroupId = attributes.getValue("Implementation-Vendor");
			}

			if (Validator.isNull(artifactGroupId)) {
				artifactGroupId = GetterUtil.getString(
					attributes.getValue("Bundle-Vendor"), servletContextName);
			}

			String artifactId = attributes.getValue("Implementation-Title");

			if (Validator.isNull(artifactId)) {
				artifactId = GetterUtil.getString(
					attributes.getValue("Bundle-Name"), servletContextName);
			}

			String version = attributes.getValue("Implementation-Version");

			if (Validator.isNull(version)) {
				version = GetterUtil.getString(
					attributes.getValue("Bundle-Version"), Version.UNKNOWN);
			}

			if ((version == Version.UNKNOWN) && _log.isWarnEnabled()) {
				_log.warn(
					"Plugin package on context " + servletContextName +
						" cannot be tracked because this WAR does not " +
							"contain a liferay-plugin-package.xml file");
			}

			pluginPackage =
				new PluginPackageImpl(
					artifactGroupId + StringPool.SLASH + artifactId +
						StringPool.SLASH + version + StringPool.SLASH +
							"war");

			pluginPackage.setName(artifactId);

			String shortDescription = attributes.getValue("Bundle-Description");

			if (Validator.isNotNull(shortDescription)) {
				pluginPackage.setShortDescription(shortDescription);
			}

			String pageURL = attributes.getValue("Bundle-DocURL");

			if (Validator.isNotNull(pageURL)) {
				pluginPackage.setPageURL(pageURL);
			}
		}
		else {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Reading plugin package from liferay-plugin-package.xml");
			}

			pluginPackage = PluginPackageUtil.readPluginPackageXml(xml);
		}

		return pluginPackage;
	}

	public void invokeDeploy(HotDeployEvent event) throws HotDeployException {
		String servletContextName = null;

		try {
			ServletContext ctx = event.getServletContext();

			servletContextName = ctx.getServletContextName();

			if (_log.isDebugEnabled()) {
				_log.debug("Invoking deploy for " + servletContextName);
			}

			if (ctx.getResource("/WEB-INF/liferay-theme-loader.xml") != null) {
				return;
			}

			PluginPackage pluginPackage = readPluginPackage(ctx);

			if (pluginPackage != null) {
				pluginPackage.setContext(servletContextName);

				event.setPluginPackage(pluginPackage);

				PluginPackageUtil.registerInstalledPluginPackage(pluginPackage);

				if (_log.isInfoEnabled()) {
					_log.info(
						"Plugin package " + pluginPackage.getModuleId() +
							" registered successfully");
				}
			}
		}
		catch (Exception e) {
			throw new HotDeployException(
				"Error registering plugins for " + servletContextName,
				e);
		}
	}

	public void invokeUndeploy(HotDeployEvent event) throws HotDeployException {
		String servletContextName = null;

		try {
			ServletContext ctx = event.getServletContext();

			servletContextName = ctx.getServletContextName();

			if (_log.isDebugEnabled()) {
				_log.debug("Invoking deploy for " + servletContextName);
			}

			PluginPackage pluginPackage = readPluginPackage(ctx);

			if (pluginPackage != null) {
				event.setPluginPackage(pluginPackage);

				PluginPackageUtil.unregisterInstalledPluginPackage(
					pluginPackage);

				if (_log.isInfoEnabled()) {
					_log.info(
						"Plugin package " + pluginPackage.getModuleId() +
							" unregistered successfully");
				}
			}
		}
		catch (Exception e) {
			throw new HotDeployException(
				"Error unregistering plugins for " + servletContextName,
				e);
		}
	}

	private static Log _log =
		LogFactory.getLog(PluginPackageHotDeployListener.class);

}