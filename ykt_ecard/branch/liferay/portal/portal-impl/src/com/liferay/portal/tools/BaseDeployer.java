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

import com.liferay.portal.deploy.DeployUtil;
import com.liferay.portal.kernel.deploy.auto.AutoDeployException;
import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.PropertiesUtil;
import com.liferay.portal.kernel.util.ServerDetector;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.plugin.PluginPackageUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.Http;
import com.liferay.util.License;
import com.liferay.util.SystemProperties;
import com.liferay.util.Time;
import com.liferay.util.ant.CopyTask;
import com.liferay.util.ant.DeleteTask;
import com.liferay.util.ant.ExpandTask;
import com.liferay.util.ant.UpToDateTask;
import com.liferay.util.ant.WarTask;
import com.liferay.util.xml.XMLFormatter;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Properties;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.oro.io.GlobFilenameFilter;

import org.dom4j.Document;
import org.dom4j.Element;

/**
 * <a href="BaseDeployer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BaseDeployer {

	public static final String DEPLOY_TO_PREFIX = "DEPLOY_TO__";

	public static void main(String[] args) {
		List wars = new ArrayList();
		List jars = new ArrayList();

		for (int i = 0; i < args.length; i++) {
			String fileName = args[i].toLowerCase();

			if (fileName.endsWith(".war")) {
				wars.add(args[i]);
			}
			else if (fileName.endsWith(".jar")) {
				jars.add(args[i]);
			}
		}

		new BaseDeployer(wars, jars);
	}

	protected BaseDeployer() {
	}

	protected BaseDeployer(List wars, List jars) {
		baseDir = System.getProperty("deployer.base.dir");
		destDir = System.getProperty("deployer.dest.dir");
		appServerType = System.getProperty("deployer.app.server.type");
		portletTaglibDTD = System.getProperty("deployer.portlet.taglib.dtd");
		portletExtTaglibDTD = System.getProperty(
			"deployer.portlet.ext.taglib.dtd");
		securityTaglibDTD = System.getProperty("deployer.security.taglib.dtd");
		themeTaglibDTD = System.getProperty("deployer.theme.taglib.dtd");
		uiTaglibDTD = System.getProperty("deployer.ui.taglib.dtd");
		utilTaglibDTD = System.getProperty("deployer.util.taglib.dtd");
		unpackWar = GetterUtil.getBoolean(
			System.getProperty("deployer.unpack.war"), true);
		jbossPrefix = GetterUtil.getString(
			System.getProperty("deployer.jboss.prefix"));
		tomcatLibDir = System.getProperty("deployer.tomcat.lib.dir");
		this.wars = wars;
		this.jars = jars;

		checkArguments();

		try {
			deploy();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	protected void checkArguments() {
		if (Validator.isNull(baseDir)) {
			throw new IllegalArgumentException(
				"The system property deployer.base.dir is not set");
		}

		if (Validator.isNull(destDir)) {
			throw new IllegalArgumentException(
				"The system property deployer.dest.dir is not set");
		}

		if (Validator.isNull(appServerType)) {
			throw new IllegalArgumentException(
				"The system property deployer.app.server.type is not set");
		}

		if (!appServerType.startsWith(ServerDetector.GERONIMO_ID) &&
			!appServerType.startsWith(ServerDetector.GLASSFISH_ID) &&
			!appServerType.startsWith(ServerDetector.JBOSS_ID) &&
			!appServerType.startsWith(ServerDetector.JONAS_ID) &&
			!appServerType.equals(ServerDetector.JETTY_ID) &&
			!appServerType.equals(ServerDetector.OC4J_ID) &&
			!appServerType.equals(ServerDetector.ORION_ID) &&
			!appServerType.equals(ServerDetector.PRAMATI_ID) &&
			!appServerType.equals(ServerDetector.RESIN_ID) &&
			!appServerType.equals(ServerDetector.TOMCAT_ID) &&
			!appServerType.equals(ServerDetector.WEBLOGIC_ID) &&
			!appServerType.equals(ServerDetector.WEBSPHERE_ID)) {

			throw new IllegalArgumentException(
				appServerType + " is not a valid application server type");
		}

		if (appServerType.startsWith(ServerDetector.GLASSFISH_ID) ||
			appServerType.equals(ServerDetector.PRAMATI_ID) ||
			appServerType.equals(ServerDetector.WEBLOGIC_ID)) {

			unpackWar = false;
		}

		if (Validator.isNotNull(jbossPrefix) &&
			!Validator.isNumber(jbossPrefix)) {

			jbossPrefix = "1";
		}
	}

	protected void copyDependencyXml(String fileName, String targetDir)
		throws Exception {

		copyDependencyXml(fileName, targetDir, null);
	}

	protected void copyDependencyXml(
			String fileName, String targetDir, Map filterMap)
		throws Exception {

		copyDependencyXml(fileName, targetDir, filterMap, false);
	}

	protected void copyDependencyXml(
			String fileName, String targetDir, Map filterMap, boolean overwrite)
		throws Exception {

		File file = new File(DeployUtil.getResourcePath(fileName));
		File targetFile = new File(targetDir + "/" + fileName);

		if (!targetFile.exists()) {
			CopyTask.copyFile(
				file, new File(targetDir), filterMap, overwrite, true);
		}
	}

	protected void copyJars(File srcFile, PluginPackage pluginPackage)
		throws Exception {

		for (int i = 0; i < jars.size(); i++) {
			String jarFullName = (String)jars.get(i);
			String jarName = jarFullName.substring(
				jarFullName.lastIndexOf("/") + 1, jarFullName.length());

			if ((!appServerType.equals(ServerDetector.TOMCAT_ID)) ||
				(appServerType.equals(ServerDetector.TOMCAT_ID) &&
					!jarFullName.equals("util-java.jar"))) {

				FileUtil.copyFile(
					jarFullName, srcFile + "/WEB-INF/lib/" + jarName, true);
			}
		}

		FileUtil.delete(srcFile + "/WEB-INF/lib/util-jsf.jar");
	}

	protected void copyPortalDependencies(File srcFile) throws Exception {
		Properties props = getPluginPackageProperties(srcFile);

		if (props == null) {
			return;
		}

		// jars

		String[] portalJars = StringUtil.split(
			props.getProperty("portal.dependency.jars"));

		for (int i = 0; i < portalJars.length; i++) {
			String portalJar = portalJars[i].trim();

			if (_log.isDebugEnabled()) {
				_log.debug("Copy portal JAR " + portalJar);
			}

			try {
				String portalJarPath = PortalUtil.getPortalLibDir() + portalJar;

				FileUtil.copyFile(
					portalJarPath, srcFile + "/WEB-INF/lib/" + portalJar, true);
			}
			catch (Exception e) {
				_log.error("Unable to copy portal JAR " + portalJar, e);
			}
		}

		// tlds

		String[] portalTlds = StringUtil.split(
			props.getProperty("portal.dependency.tlds"));

		for (int i = 0; i < portalTlds.length; i++) {
			String portalTld = portalTlds[i].trim();

			if (_log.isDebugEnabled()) {
				_log.debug("Copy portal TLD " + portalTld);
			}

			try {
				String portalTldPath = DeployUtil.getResourcePath(portalTld);

				FileUtil.copyFile(
					portalTldPath, srcFile + "/WEB-INF/tld/" + portalTld, true);
			}
			catch (Exception e) {
				_log.error("Unable to copy portal TLD " + portalTld, e);
			}
		}

		// commons-logging*.jar

		File pluginLibDir = new File(srcFile + "/WEB-INF/lib/");

		String[] commonsLoggingJars = pluginLibDir.list(
			new GlobFilenameFilter("commons-logging*.jar"));

		if ((commonsLoggingJars == null) || (commonsLoggingJars.length == 0)) {
			String portalJarPath =
				PortalUtil.getPortalLibDir() + "commons-logging.jar";

			FileUtil.copyFile(
				portalJarPath, srcFile + "/WEB-INF/lib/commons-logging.jar",
				true);
		}

		// log4j*.jar

		String[] log4jJars = pluginLibDir.list(
			new GlobFilenameFilter("log4j*.jar"));

		if ((log4jJars == null) || (log4jJars.length == 0)) {
			String portalJarPath = PortalUtil.getPortalLibDir() + "log4j.jar";

			FileUtil.copyFile(
				portalJarPath, srcFile + "/WEB-INF/lib/log4j.jar", true);
		}
	}

	protected void copyTlds(File srcFile, PluginPackage pluginPackage)
		throws Exception {

		if (Validator.isNotNull(portletTaglibDTD)) {
			FileUtil.copyFile(
				portletTaglibDTD, srcFile + "/WEB-INF/tld/liferay-portlet.tld",
				true);
		}

		if (Validator.isNotNull(themeTaglibDTD)) {
			FileUtil.copyFile(
				themeTaglibDTD, srcFile + "/WEB-INF/tld/liferay-theme.tld",
				true);
		}

		if (Validator.isNotNull(utilTaglibDTD)) {
			FileUtil.copyFile(
				utilTaglibDTD, srcFile + "/WEB-INF/tld/liferay-util.tld", true);
		}
	}

	protected void copyXmls(
			File srcFile, String displayName, PluginPackage pluginPackage)
		throws Exception {

		copyDependencyXml("geronimo-web.xml", srcFile + "/WEB-INF");
		copyDependencyXml("web.xml", srcFile + "/WEB-INF");
	}

	protected void deploy() throws Exception  {
		try {
			File baseDirFile = new File(baseDir);

			File[] files = baseDirFile.listFiles();

			if (files == null) {
				return;
			}

			files = FileUtil.sortFiles(files);

			for (int i = 0; i < files.length; i++) {
				File srcFile = files[i];

				String fileName = srcFile.getName().toLowerCase();

				boolean deploy = false;

				if (fileName.endsWith(".war") || fileName.endsWith(".zip")) {
					deploy = true;

					if ((wars.size() > 0) &&
						(!wars.contains(srcFile.getName()))) {

						deploy = false;
					}
				}

				if (deploy) {
					deployFile(srcFile);
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	protected void deployDirectory(
			File srcFile, String displayName, boolean override,
			PluginPackage pluginPackage)
		throws Exception {

		deployDirectory(
			srcFile, null, null, displayName, override, pluginPackage);
	}

	protected void deployDirectory(
			File srcFile, File mergeDir, File deployDir, String displayName,
			boolean overwrite, PluginPackage pluginPackage)
		throws Exception {

		rewriteFiles(srcFile);

		mergeDirectory(mergeDir, srcFile);

		processPluginPackageProperties(srcFile, displayName, pluginPackage);

		copyJars(srcFile, pluginPackage);
		copyTlds(srcFile, pluginPackage);
		copyXmls(srcFile, displayName, pluginPackage);
		copyPortalDependencies(srcFile);

		updateGeronimoWebXml(srcFile, displayName, pluginPackage);

		File webXml = new File(srcFile + "/WEB-INF/web.xml");

		updateWebXml(webXml, srcFile, displayName, pluginPackage);

		if ((deployDir != null) && !baseDir.equals(destDir)) {
			updateDeployDirectory(srcFile);

			String excludes = StringPool.BLANK;

			if (appServerType.startsWith("jboss")) {
				excludes += "**/WEB-INF/lib/log4j.jar,";
			}
			else if (appServerType.equals(ServerDetector.TOMCAT_ID)) {
				String[] libs = FileUtil.listFiles(tomcatLibDir);

				for (int i = 0; i < libs.length; i++) {
					excludes += "**/WEB-INF/lib/" + libs[i] + ",";
				}

				File contextXml = new File(srcFile + "/META-INF/context.xml");

				if (contextXml.exists()) {
					String content = FileUtil.read(contextXml);

					if (content.indexOf(_PORTAL_CLASS_LOADER) != -1) {
						excludes += "**/WEB-INF/lib/util-bridges.jar,";
						excludes += "**/WEB-INF/lib/util-java.jar,";
						excludes += "**/WEB-INF/lib/util-taglib.jar,";
					}
				}

				try {

					// LEP-2990

					Class.forName("javax.el.ELContext");

					excludes += "**/WEB-INF/lib/el-api.jar,";
				}
				catch (ClassNotFoundException cnfe) {
				}
			}

			if (!unpackWar || appServerType.equals("websphere")) {
				File tempDir = new File(
					SystemProperties.get(SystemProperties.TMP_DIR) +
						File.separator + Time.getTimestamp());

				WarTask.war(srcFile, tempDir, "WEB-INF/web.xml", webXml);

				if (!tempDir.renameTo(deployDir)) {
					WarTask.war(srcFile, deployDir, "WEB-INF/web.xml", webXml);
				}

				DeleteTask.deleteDirectory(tempDir);
			}
			else {

				// The deployer might only copy files that have been modified.
				// However, the deployer always copies and overwrites web.xml
				// after the other files have been copied because application
				// servers usually detect that a WAR has been modified based on
				// the web.xml time stamp.

				excludes += "**/WEB-INF/web.xml";

				CopyTask.copyDirectory(
					srcFile, deployDir, StringPool.BLANK, excludes, overwrite,
					true);

				CopyTask.copyDirectory(
					srcFile, deployDir, "**/WEB-INF/web.xml", StringPool.BLANK,
					true, false);

				if (appServerType.equals(ServerDetector.TOMCAT_ID)) {

					// See org.apache.catalina.startup.HostConfig to see how
					// Tomcat checks to make sure that web.xml was modified 5
					// seconds after WEB-INF

					File deployWebXml = new File(
						deployDir + "/WEB-INF/web.xml");

					deployWebXml.setLastModified(
						System.currentTimeMillis() + (Time.SECOND * 6));
				}
			}
		}
	}

	protected void deployFile(File srcFile) throws Exception {
		PluginPackage pluginPackage = readPluginPackage(srcFile);

		if (_log.isInfoEnabled()) {
			_log.info("Deploying " + srcFile.getName());
		}

		String deployDir = null;
		String displayName = null;
		boolean overwrite = false;
		String preliminaryContext = null;

		// File names starting with DEPLOY_TO_PREFIX should use the filename
		// after the prefix as the deployment context

		if (srcFile.getName().startsWith(DEPLOY_TO_PREFIX)) {
			displayName = srcFile.getName().substring(
				DEPLOY_TO_PREFIX.length(), srcFile.getName().length() - 4);

			overwrite = true;
			preliminaryContext = displayName;
		}

		if (preliminaryContext == null) {
			preliminaryContext = getDisplayName(srcFile);
		}

		if (pluginPackage != null) {
			if (!PluginPackageUtil.isCurrentVersionSupported(
					pluginPackage.getLiferayVersions())) {

				throw new AutoDeployException(
					srcFile.getName() +
						" does not support this version of Liferay");
			}

			if (displayName == null) {
				displayName = pluginPackage.getRecommendedDeploymentContext();
			}

			if (Validator.isNull(displayName)) {
				displayName = getDisplayName(srcFile);
			}

			pluginPackage.setContext(displayName);

			PluginPackageUtil.updateInstallingPluginPackage(
				preliminaryContext, pluginPackage);
		}

		if (Validator.isNotNull(displayName)) {
			deployDir = displayName + ".war";
		}
		else {
			deployDir = srcFile.getName();
			displayName = getDisplayName(srcFile);
		}

		if (appServerType.startsWith(ServerDetector.JBOSS_ID)) {
			deployDir = jbossPrefix + deployDir;
		}
		else if (appServerType.equals(ServerDetector.JETTY_ID) ||
				 appServerType.equals(ServerDetector.OC4J_ID) ||
				 appServerType.equals(ServerDetector.ORION_ID) ||
				 appServerType.equals(ServerDetector.RESIN_ID) ||
				 appServerType.equals(ServerDetector.TOMCAT_ID)) {

			if (unpackWar) {
				deployDir = deployDir.substring(0, deployDir.length() - 4);
			}
		}

		deployDir = destDir + "/" + deployDir;

		File deployDirFile = new File(deployDir);

		try {
			PluginPackage previousPluginPackage =
				readPluginPackage(deployDirFile);

			if ((pluginPackage != null) && (previousPluginPackage != null)) {
				if (_log.isInfoEnabled()) {
					String name = pluginPackage.getName();
					String previousVersion = previousPluginPackage.getVersion();
					String version = pluginPackage.getVersion();

					_log.info(
						"Updating " + name + " from version " +
							previousVersion + " to version " + version);
				}

				if (pluginPackage.isLaterVersionThan(
					previousPluginPackage)) {

					overwrite = true;
				}
			}

			File mergeDirFile = new File(
				srcFile.getParent() + "/merge/" + srcFile.getName());

			if (srcFile.isDirectory()) {
				deployDirectory(
					srcFile, mergeDirFile, deployDirFile, displayName,
					overwrite, pluginPackage);
			}
			else {
				boolean deployed = deployFile(
					srcFile, mergeDirFile, deployDirFile, displayName,
					overwrite, pluginPackage);

				if (!deployed) {
					String context = preliminaryContext;

					if (pluginPackage != null) {
						context = pluginPackage.getContext();
					}

					PluginPackageUtil.endPluginPackageInstallation(context);
				}
			}
		}
		catch (Exception e) {
			if (pluginPackage != null) {
				PluginPackageUtil.endPluginPackageInstallation(
					pluginPackage.getContext());
			}

			throw e;
		}
	}

	protected boolean deployFile(
			File srcFile, File mergeDir, File deployDir, String displayName,
			boolean overwrite, PluginPackage pluginPackage)
		throws Exception {

		if (!overwrite && UpToDateTask.isUpToDate(srcFile, deployDir)) {
			if (_log.isInfoEnabled()) {
				_log.info(deployDir + " is already up to date");
			}

			return false;
		}

		// Don't delete the deploy directory because it can cause problems in
		// certain application servers

		//DeleteTask.deleteDirectory(deployDir);

		File tempDir = new File(
			SystemProperties.get(SystemProperties.TMP_DIR) + File.separator +
				Time.getTimestamp());

		ExpandTask.expand(srcFile, tempDir);

		deployDirectory(
			tempDir, mergeDir, deployDir, displayName, overwrite,
			pluginPackage);

		DeleteTask.deleteDirectory(tempDir);

		return true;
	}

	protected String downloadJar(String jar) throws Exception {
		String tmpDir = SystemProperties.get(SystemProperties.TMP_DIR);

		File file = new File(
			tmpDir + "/liferay/com/liferay/portal/deploy/dependencies/" +
				jar);

		if (!file.exists()) {
			synchronized(this) {
				String url = PropsUtil.get(
					PropsUtil.LIBRARY_DOWNLOAD_URL + jar);

				if (_log.isInfoEnabled()) {
					_log.info("Downloading library from " + url);
				}

				byte[] bytes = Http.URLtoByteArray(url);

				FileUtil.write(file, bytes);
			}
		}

		return FileUtil.getAbsolutePath(file);
	}

	protected String getDisplayName(File srcFile) {
		String displayName = srcFile.getName();

		displayName = displayName.substring(0, displayName.length() - 4);

		if (appServerType.startsWith("jboss") &&
			Validator.isNotNull(jbossPrefix) &&
			displayName.startsWith(jbossPrefix)) {

			displayName = displayName.substring(1, displayName.length());
		}

		return displayName;
	}

	protected String getExtraContent(
			double webXmlVersion, File srcFile, String displayName)
		throws Exception {

		StringMaker sm = new StringMaker();

		sm.append("<display-name>");
		sm.append(displayName);
		sm.append("</display-name>");

		boolean hasTaglib = false;

		if (Validator.isNotNull(portletTaglibDTD) ||
			Validator.isNotNull(portletExtTaglibDTD) ||
			Validator.isNotNull(securityTaglibDTD) ||
			Validator.isNotNull(themeTaglibDTD) ||
			Validator.isNotNull(uiTaglibDTD) ||
			Validator.isNotNull(utilTaglibDTD)) {

			hasTaglib = true;
		}

		if (hasTaglib && (webXmlVersion > 2.3)) {
			sm.append("<jsp-config>");
		}

		if (Validator.isNotNull(portletTaglibDTD)) {
			sm.append("<taglib>");
			sm.append("<taglib-uri>http://java.sun.com/portlet</taglib-uri>");
			sm.append("<taglib-location>");
			sm.append("/WEB-INF/tld/liferay-portlet.tld");
			sm.append("</taglib-location>");
			sm.append("</taglib>");
		}

		if (Validator.isNotNull(portletExtTaglibDTD)) {
			sm.append("<taglib>");
			sm.append("<taglib-uri>");
			sm.append("http://liferay.com/tld/portlet");
			sm.append("</taglib-uri>");
			sm.append("<taglib-location>");
			sm.append("/WEB-INF/tld/liferay-portlet-ext.tld");
			sm.append("</taglib-location>");
			sm.append("</taglib>");
		}

		if (Validator.isNotNull(securityTaglibDTD)) {
			sm.append("<taglib>");
			sm.append("<taglib-uri>");
			sm.append("http://liferay.com/tld/security");
			sm.append("</taglib-uri>");
			sm.append("<taglib-location>");
			sm.append("/WEB-INF/tld/liferay-security.tld");
			sm.append("</taglib-location>");
			sm.append("</taglib>");
		}

		if (Validator.isNotNull(themeTaglibDTD)) {
			sm.append("<taglib>");
			sm.append("<taglib-uri>http://liferay.com/tld/theme</taglib-uri>");
			sm.append("<taglib-location>");
			sm.append("/WEB-INF/tld/liferay-theme.tld");
			sm.append("</taglib-location>");
			sm.append("</taglib>");
		}

		if (Validator.isNotNull(uiTaglibDTD)) {
			sm.append("<taglib>");
			sm.append("<taglib-uri>http://liferay.com/tld/ui</taglib-uri>");
			sm.append("<taglib-location>");
			sm.append("/WEB-INF/tld/liferay-ui.tld");
			sm.append("</taglib-location>");
			sm.append("</taglib>");
		}

		if (Validator.isNotNull(utilTaglibDTD)) {
			sm.append("<taglib>");
			sm.append("<taglib-uri>http://liferay.com/tld/util</taglib-uri>");
			sm.append("<taglib-location>");
			sm.append("/WEB-INF/tld/liferay-util.tld");
			sm.append("</taglib-location>");
			sm.append("</taglib>");
		}

		if (hasTaglib && (webXmlVersion > 2.3)) {
			sm.append("</jsp-config>");
		}

		return sm.toString();
	}

	protected String getPluginPackageLicensesXml(List licenses) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < licenses.size(); i++) {
			License license = (License)licenses.get(i);

			if (i == 0) {
				sm.append("\r\n");
			}

			sm.append("\t\t<license osi-approved=\"");
			sm.append(license.isOsiApproved());
			sm.append("\">");
			sm.append(license.getName());
			sm.append("</license>\r\n");

			if ((i + 1) == licenses.size()) {
				sm.append("\t");
			}
		}

		return sm.toString();
	}

	protected String getPluginPackageLiferayVersionsXml(List liferayVersions) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < liferayVersions.size(); i++) {
			String liferayVersion = (String)liferayVersions.get(i);

			if (i == 0) {
				sm.append("\r\n");
			}

			sm.append("\t\t<liferay-version>");
			sm.append(liferayVersion);
			sm.append("</liferay-version>\r\n");

			if ((i + 1) == liferayVersions.size()) {
				sm.append("\t");
			}
		}

		return sm.toString();
	}

	protected Properties getPluginPackageProperties(File srcFile)
		throws Exception {

		File propsFile = new File(
			srcFile + "/WEB-INF/liferay-plugin-package.properties");

		if (!propsFile.exists()) {
			return null;
		}

		String propsString = FileUtil.read(propsFile);

		return PropertiesUtil.load(propsString);
	}

	protected String getPluginPackageTagsXml(List tags) {
		StringMaker sm = new StringMaker();

		for (int i = 0; i < tags.size(); i++) {
			String tag = (String)tags.get(i);

			if (i == 0) {
				sm.append("\r\n");
			}

			sm.append("\t\t<tag>");
			sm.append(tag);
			sm.append("</tag>\r\n");

			if ((i + 1) == tags.size()) {
				sm.append("\t");
			}
		}

		return sm.toString();
	}

	protected void mergeDirectory(File mergeDir, File targetDir) {
		if ((mergeDir == null) || (!mergeDir.exists())) {
			return;
		}

		CopyTask.copyDirectory(mergeDir, targetDir, null, null, true, false);
	}

	protected void processPluginPackageProperties(
			File srcFile, String displayName, PluginPackage pluginPackage)
		throws Exception {
	}

	protected PluginPackage readPluginPackage(File file) {
		if (!file.exists()) {
			return null;
		}

		InputStream is = null;
		ZipFile zipFile = null;

		try {
			boolean parseProps = false;

			if (file.isDirectory()) {
				String path = file.getPath();

				File pluginPackageXmlFile = new File(
					file.getParent() + "/merge/" + file.getName() +
						"/WEB-INF/liferay-plugin-package.xml");

				if (pluginPackageXmlFile.exists()) {
					is = new FileInputStream(pluginPackageXmlFile);
				}
				else {
					pluginPackageXmlFile = new File(
						path + "/WEB-INF/liferay-plugin-package.xml");

					if (pluginPackageXmlFile.exists()) {
						is = new FileInputStream(pluginPackageXmlFile);
					}
				}

				File pluginPackagePropsFile = new File(
					file.getParent() + "/merge/" + file.getName() +
						"/WEB-INF/liferay-plugin-package.properties");

				if (pluginPackagePropsFile.exists()) {
					is = new FileInputStream(pluginPackagePropsFile);

					parseProps = true;
				}
				else {
					pluginPackagePropsFile = new File(
						path + "/WEB-INF/liferay-plugin-package.properties");

					if (pluginPackagePropsFile.exists()) {
						is = new FileInputStream(pluginPackagePropsFile);

						parseProps = true;
					}
				}
			}
			else {
				zipFile = new ZipFile(file);

				File pluginPackageXmlFile = new File(
					file.getParent() + "/merge/" + file.getName() +
						"/WEB-INF/liferay-plugin-package.xml");

				if (pluginPackageXmlFile.exists()) {
					is = new FileInputStream(pluginPackageXmlFile);
				}
				else {
					ZipEntry zipEntry = zipFile.getEntry(
						"WEB-INF/liferay-plugin-package.xml");

					if (zipEntry != null) {
						is = zipFile.getInputStream(zipEntry);
					}
				}

				File pluginPackagePropsFile = new File(
					file.getParent() + "/merge/" + file.getName() +
						"/WEB-INF/liferay-plugin-package.properties");

				if (pluginPackagePropsFile.exists()) {
					is = new FileInputStream(pluginPackagePropsFile);

					parseProps = true;
				}
				else {
					ZipEntry zipEntry = zipFile.getEntry(
						"WEB-INF/liferay-plugin-package.properties");

					if (zipEntry != null) {
						is = zipFile.getInputStream(zipEntry);

						parseProps = true;
					}
				}
			}

			if (is == null) {
				if (_log.isInfoEnabled()) {
					_log.info(
						file.getPath() + " does not have a " +
							"WEB-INF/liferay-plugin-package.xml or " +
								"WEB-INF/liferay-plugin-package.properties");
				}

				return null;
			}

			if (parseProps) {
				String displayName = getDisplayName(file);

				String propsString = StringUtil.read(is);

				Properties props = PropertiesUtil.load(propsString);

				return PluginPackageUtil.readPluginPackageProps(
					displayName, props);
			}
			else {
				String xml = StringUtil.read(is);

				xml = XMLFormatter.fixProlog(xml);

				return PluginPackageUtil.readPluginPackageXml(xml);
			}
		}
		catch (Exception e) {
			_log.error(file.getPath() + ": " + e.toString());
		}
		finally {
			if (is != null) {
				try {
					is.close();
				}
				catch (IOException ioe) {
				}
			}

			if (zipFile != null) {
				try {
					zipFile.close();
				}
				catch (IOException ioe) {
				}
			}
		}

		return null;
	}

	protected void rewriteFiles(File srcDir) throws Exception {
		String[] files = FileUtil.listFiles(srcDir + "/WEB-INF/");

		for (int i = 0; i < files.length; i++) {
			String ext = FileUtil.getExtension(files[i]);

			if (ext.equalsIgnoreCase("xml")) {

				// Make sure to rewrite any XML files to include external
				// entities into same file. See LEP-3142.

				File file = new File(srcDir + "/WEB-INF/" + files[i]);

				try {
					Document doc = PortalUtil.readDocumentFromFile(file);

					String content = XMLFormatter.toString(
						doc, XMLFormatter.INDENT, true);

					FileUtil.write(file, content);
				}
				catch (Exception e) {
					if (_log.isWarnEnabled()) {
						_log.warn(
							"Unable to format " + file + ": " + e.getMessage());
					}
				}
			}
		}
	}

	protected void updateDeployDirectory(File srcFile) throws Exception {
	}

	protected void updateGeronimoWebXml(
			File srcFile, String displayName, PluginPackage pluginPackage)
		throws Exception {

		if (!appServerType.startsWith(ServerDetector.GERONIMO_ID)) {
			return;
		}

		File geronimoWebXml = new File(srcFile + "/WEB-INF/geronimo-web.xml");

		Document doc = PortalUtil.readDocumentFromFile(geronimoWebXml);

		Element root = doc.getRootElement();

		Element environmentEl = root.element("environment");

		Element moduleIdEl = environmentEl.element("moduleId");

		Element artifactIdEl = moduleIdEl.element("artifactId");

		String artifactIdText = GetterUtil.getString(artifactIdEl.getText());

		if (!artifactIdText.equals(displayName)) {
			artifactIdEl.setText(displayName);

			String content = XMLFormatter.toString(doc);

			FileUtil.write(geronimoWebXml, content);

			if (_log.isInfoEnabled()) {
				_log.info("Modifying Geronimo " + geronimoWebXml);
			}
		}
	}

	protected void updateWebXml(
			File webXml, File srcFile, String displayName,
			PluginPackage pluginPackage)
		throws Exception {

		String content = FileUtil.read(webXml);

		int pos = content.indexOf("<web-app");
		pos = content.indexOf(">", pos) + 1;

		double webXmlVersion = 2.3;

		Document webXmlDoc = PortalUtil.readDocumentFromXML(content);

		Element webXmlRoot = webXmlDoc.getRootElement();

		webXmlVersion = GetterUtil.getDouble(
			webXmlRoot.attributeValue("version"), webXmlVersion);

		// Merge extra content

		String extraContent = getExtraContent(
			webXmlVersion, srcFile, displayName);

		String newContent =
			content.substring(0, pos) + extraContent +
			content.substring(pos, content.length());

		// Replace old package names

		newContent = StringUtil.replace(
			newContent, "com.liferay.portal.shared.",
			"com.liferay.portal.kernel.");

		newContent = WebXMLBuilder.organizeWebXML(newContent);

		FileUtil.write(webXml, newContent, true);

		if (_log.isInfoEnabled()) {
			_log.info("Modifying Servlet " + webXmlVersion + " " + webXml);
		}
	}

	protected String baseDir;
	protected String destDir;
	protected String appServerType;
	protected String portletTaglibDTD;
	protected String portletExtTaglibDTD;
	protected String securityTaglibDTD;
	protected String themeTaglibDTD;
	protected String uiTaglibDTD;
	protected String utilTaglibDTD;
	protected boolean unpackWar;
	protected String jbossPrefix;
	protected String tomcatLibDir;
	protected List wars;
	protected List jars;

	private static final String _PORTAL_CLASS_LOADER =
		"com.liferay.support.tomcat.loader.PortalClassLoader";

	private static Log _log = LogFactory.getLog(BaseDeployer.class);

}