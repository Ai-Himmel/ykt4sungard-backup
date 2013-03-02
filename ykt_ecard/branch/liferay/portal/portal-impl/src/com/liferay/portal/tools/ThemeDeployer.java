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

package com.liferay.portal.tools;

import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.TextFormatter;

import java.io.File;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Properties;

/**
 * <a href="ThemeDeployer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ThemeDeployer extends BaseDeployer {

	public static void main(String[] args) {
		List wars = new ArrayList();
		List jars = new ArrayList();

		for (int i = 0; i < args.length; i++) {
			if (args[i].endsWith(".war")) {
				wars.add(args[i]);
			}
			else if (args[i].endsWith(".jar")) {
				jars.add(args[i]);
			}
		}

		new ThemeDeployer(wars, jars);
	}

	protected ThemeDeployer() {
	}

	protected ThemeDeployer(List wars, List jars) {
		super(wars, jars);
	}

	protected void checkArguments() {
		super.checkArguments();

		if (Validator.isNull(themeTaglibDTD)) {
			throw new IllegalArgumentException(
				"The system property deployer.theme.taglib.dtd is not set");
		}

		if (Validator.isNull(utilTaglibDTD)) {
			throw new IllegalArgumentException(
				"The system property deployer.util.taglib.dtd is not set");
		}
	}

	protected String getExtraContent(
			double webXmlVersion, File srcFile, String displayName)
		throws Exception {

		StringMaker sm = new StringMaker();

		String extraContent = super.getExtraContent(
			webXmlVersion, srcFile, displayName);

		sm.append(extraContent);

		// HeaderFilter

		sm.append("<filter>");
		sm.append("<filter-name>Header Filter</filter-name>");
		sm.append("<filter-class>");
		sm.append("com.liferay.portal.kernel.servlet.PortalClassLoaderFilter");
		sm.append("</filter-class>");
		sm.append("<init-param>");
		sm.append("<param-name>filter-class</param-name>");
		sm.append("<param-value>");
		sm.append("com.liferay.filters.header.HeaderFilter");
		sm.append("</param-value>");
		sm.append("</init-param>");
		sm.append("<init-param>");
		sm.append("<param-name>Cache-Control</param-name>");
		sm.append("<param-value>max-age=172801, public</param-value>");
		sm.append("</init-param>");
		sm.append("<init-param>");
		sm.append("<param-name>Expires</param-name>");
		sm.append("<param-value>172801</param-value>");
		sm.append("</init-param>");
		sm.append("</filter>");

		sm.append("<filter-mapping>");
		sm.append("<filter-name>Header Filter</filter-name>");
		sm.append("<url-pattern>*.css</url-pattern>");
		sm.append("</filter-mapping>");
		sm.append("<filter-mapping>");
		sm.append("<filter-name>Header Filter</filter-name>");
		sm.append("<url-pattern>*.gif</url-pattern>");
		sm.append("</filter-mapping>");
		sm.append("<filter-mapping>");
		sm.append("<filter-name>Header Filter</filter-name>");
		sm.append("<url-pattern>*.html</url-pattern>");
		sm.append("</filter-mapping>");
		sm.append("<filter-mapping>");
		sm.append("<filter-name>Header Filter</filter-name>");
		sm.append("<url-pattern>*.jpg</url-pattern>");
		sm.append("</filter-mapping>");
		sm.append("<filter-mapping>");
		sm.append("<filter-name>Header Filter</filter-name>");
		sm.append("<url-pattern>*.js</url-pattern>");
		sm.append("</filter-mapping>");
		sm.append("<filter-mapping>");
		sm.append("<filter-name>Header Filter</filter-name>");
		sm.append("<url-pattern>*.png</url-pattern>");
		sm.append("</filter-mapping>");

		// CompressionFilter

		sm.append("<filter>");
		sm.append("<filter-name>Compression Filter</filter-name>");
		sm.append("<filter-class>");
		sm.append("com.liferay.portal.kernel.servlet.PortalClassLoaderFilter");
		sm.append("</filter-class>");
		sm.append("<init-param>");
		sm.append("<param-name>filter-class</param-name>");
		sm.append("<param-value>");
		sm.append("com.liferay.filters.compression.CompressionFilter");
		sm.append("</param-value>");
		sm.append("</init-param>");
		sm.append("</filter>");

		sm.append("<filter-mapping>");
		sm.append("<filter-name>Compression Filter</filter-name>");
		sm.append("<url-pattern>*.css</url-pattern>");
		sm.append("</filter-mapping>");
		sm.append("<filter-mapping>");
		sm.append("<filter-name>Compression Filter</filter-name>");
		sm.append("<url-pattern>*.js</url-pattern>");
		sm.append("</filter-mapping>");

		// VelocityFilter

		sm.append("<filter>");
		sm.append("<filter-name>Velocity Filter</filter-name>");
		sm.append("<filter-class>");
		sm.append("com.liferay.portal.kernel.servlet.PortalClassLoaderFilter");
		sm.append("</filter-class>");
		sm.append("<init-param>");
		sm.append("<param-name>filter-class</param-name>");
		sm.append("<param-value>");
		sm.append("com.liferay.portal.servlet.filters.velocity.VelocityFilter");
		sm.append("</param-value>");
		sm.append("</init-param>");
		sm.append("<init-param>");
		sm.append("<param-name>pattern</param-name>");
		sm.append("<param-value>(.+)/css/main.css(.+)</param-value>");
		sm.append("</init-param>");
		sm.append("</filter>");

		/*sm.append("<filter-mapping>");
		sm.append("<filter-name>Velocity Filter</filter-name>");
		sm.append("<url-pattern>*.css</url-pattern>");

		if (webXmlVersion > 2.3) {
			sm.append("<dispatcher>FORWARD</dispatcher>");
			sm.append("<dispatcher>INCLUDE</dispatcher>");
			sm.append("<dispatcher>REQUEST</dispatcher>");
		}

		sm.append("</filter-mapping>");*/

		// ThemeContextListener

		sm.append("<listener>");
		sm.append("<listener-class>");
		sm.append("com.liferay.portal.kernel.servlet.ThemeContextListener");
		sm.append("</listener-class>");
		sm.append("</listener>");

		return sm.toString();
	}

	protected void processPluginPackageProperties(
			File srcFile, String displayName, PluginPackage pluginPackage)
		throws Exception {

		if (pluginPackage == null) {
			return;
		}

		Properties props = getPluginPackageProperties(srcFile);

		if ((props == null) || (props.size() == 0)) {
			return;
		}

		String moduleGroupId = pluginPackage.getGroupId();
		String moduleArtifactId = pluginPackage.getArtifactId();
		String moduleVersion = pluginPackage.getVersion();

		String pluginName = pluginPackage.getName();
		String pluginType = (String)pluginPackage.getTypes().get(0);
		String pluginTypeName = TextFormatter.format(
			pluginType, TextFormatter.J);

		if (!pluginType.equals("theme")) {
			return;
		}

		String tags = getPluginPackageTagsXml(pluginPackage.getTags());
		String shortDescription = pluginPackage.getShortDescription();
		String longDescription = pluginPackage.getLongDescription();
		String changeLog = pluginPackage.getChangeLog();
		String pageURL = pluginPackage.getPageURL();
		String author = pluginPackage.getAuthor();
		String licenses = getPluginPackageLicensesXml(
			pluginPackage.getLicenses());
		String liferayVersions = getPluginPackageLiferayVersionsXml(
			pluginPackage.getLiferayVersions());

		int pos = moduleArtifactId.indexOf("-theme");

		String themeId = moduleArtifactId.substring(0, pos);
		String themeName = pluginName;

		Map filterMap = new HashMap();

		filterMap.put("module_group_id", moduleGroupId);
		filterMap.put("module_artifact_id", moduleArtifactId);
		filterMap.put("module_version", moduleVersion);

		filterMap.put("plugin_name", pluginName);
		filterMap.put("plugin_type", pluginType);
		filterMap.put("plugin_type_name", pluginTypeName);

		filterMap.put("tags", tags);
		filterMap.put("short_description", shortDescription);
		filterMap.put("long_description", longDescription);
		filterMap.put("change_log", changeLog);
		filterMap.put("page_url", pageURL);
		filterMap.put("author", author);
		filterMap.put("licenses", licenses);
		filterMap.put("liferay_versions", liferayVersions);

		filterMap.put("theme_id", themeId);
		filterMap.put("theme_name", themeName);
		filterMap.put(
			"theme_versions",
			StringUtil.replace(liferayVersions, "liferay-version", "version"));

		copyDependencyXml(
			"liferay-look-and-feel.xml", srcFile + "/WEB-INF", filterMap, true);
		copyDependencyXml(
			"liferay-plugin-package.xml", srcFile + "/WEB-INF", filterMap,
			true);
	}

}