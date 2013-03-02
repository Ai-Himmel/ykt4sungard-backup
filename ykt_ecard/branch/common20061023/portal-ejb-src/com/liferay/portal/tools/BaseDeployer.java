/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

import com.liferay.util.FileUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.ant.CopyTask;
import com.liferay.util.ant.DeleteTask;
import com.liferay.util.ant.ExpandTask;
import com.liferay.util.ant.UpToDateTask;
import com.liferay.util.ant.WarTask;

import java.io.File;

import java.text.SimpleDateFormat;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="BaseDeployer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.38 $
 *
 */
public class BaseDeployer {

	public static void main(String[] args) {
		if (args.length >= 2) {
			List jars = new ArrayList();

			for (int i = 0; i < args.length; i++) {
				jars.add(args[i]);
			}

			new BaseDeployer(jars);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	protected BaseDeployer(List jars) {
		baseDir = System.getProperty("deployer.base.dir");
		destDir = System.getProperty("deployer.dest.dir");
		appServerType = System.getProperty("deployer.app.server.type");
		portletTaglibDTD = System.getProperty("deployer.portlet.taglib.dtd");
		themeTaglibDTD = System.getProperty("deployer.theme.taglib.dtd");
		utilTaglibDTD = System.getProperty("deployer.util.taglib.dtd");
		jbossPrefix = System.getProperty("deployer.jboss.prefix");
		tomcatLibDir = System.getProperty("deployer.tomcat.lib.dir");
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

		if (!appServerType.startsWith("jboss") &&
			!appServerType.startsWith("jetty") &&
			!appServerType.equals("oc4j") &&
			!appServerType.equals("orion") &&
			!appServerType.equals("resin") &&
			!appServerType.equals("tomcat") &&
			!appServerType.equals("weblogic") &&
			!appServerType.equals("websphere")) {

			throw new IllegalArgumentException(
				appServerType + " is not a valid application server type");
		}

		if (!Validator.isNumber(jbossPrefix)) {
			jbossPrefix = "1";
		}
	}

	protected void copyJars(File srcFile) throws Exception {
		for (int i = 0; i < jars.size(); i++) {
			String jarFullName = (String)jars.get(i);
			String jarName = jarFullName.substring(
				jarFullName.lastIndexOf("/") + 1, jarFullName.length());

			if ((!appServerType.equals("tomcat")) ||
				(appServerType.equals("tomcat") &&
					!jarFullName.equals("util-java.jar"))) {

				FileUtil.copyFileLazy(
					jarFullName, srcFile + "/WEB-INF/lib/" + jarName);
			}
		}
	}

	protected void copyTlds(File srcFile) throws Exception {
		if (Validator.isNotNull(portletTaglibDTD)) {
			FileUtil.copyFileLazy(
				portletTaglibDTD, srcFile + "/WEB-INF/tld/liferay-portlet.tld");
		}

		if (Validator.isNotNull(themeTaglibDTD)) {
			FileUtil.copyFileLazy(
				themeTaglibDTD, srcFile + "/WEB-INF/tld/liferay-theme.tld");
		}

		if (Validator.isNotNull(utilTaglibDTD)) {
			FileUtil.copyFileLazy(
				utilTaglibDTD, srcFile + "/WEB-INF/tld/liferay-util.tld");
		}
	}

	protected void deploy() throws Exception  {
		try {
			File[] files = FileUtil.sortFiles(new File(baseDir).listFiles());

			for (int i = 0; i < files.length; i++) {
				File srcFile = files[i];

				if (srcFile.getName().endsWith(".war")) {
					System.out.println("\nDeploying " + srcFile.getName());

					String deployDir = srcFile.getName();

					if (appServerType.startsWith("jboss")) {
						deployDir = jbossPrefix + deployDir;
					}
					else if (appServerType.equals("jetty") ||
							 appServerType.equals("oc4j") ||
							 appServerType.equals("orion") ||
							 appServerType.equals("resin") ||
							 appServerType.equals("tomcat")) {

						deployDir =
							deployDir.substring(0, deployDir.length() - 4);
					}

					deployDir = destDir + "/" + deployDir;

					if (srcFile.isDirectory()) {
						deployDirectory(
							srcFile, new File(deployDir),
							getDisplayName(srcFile));
					}
					else {
						deployFile(srcFile, new File(deployDir));
					}
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	protected void deployDirectory(
			File srcFile, File deployDir, String displayName)
		throws Exception {

		copyJars(srcFile);
		copyTlds(srcFile);

		File webXML = new File(srcFile + "/WEB-INF/web.xml");

		String content = FileUtil.read(webXML);

		int pos = content.indexOf("<web-app");
		pos = content.indexOf(">", pos) + 1;

		String extraContent = getExtraContent(srcFile, displayName);

		String newContent =
			content.substring(0, pos) + extraContent +
			content.substring(pos, content.length());

		newContent = WebXMLBuilder.organizeWebXML(newContent);

		FileUtil.write(webXML, newContent, true);

		System.out.println("  Modifying " + webXML);

		if (!baseDir.equals(destDir)) {
			String includes = StringPool.BLANK;
			String excludes = StringPool.BLANK;

			if (appServerType.equals("tomcat")) {
				String[] libs = FileUtil.listFiles(tomcatLibDir);

				for (int i = 0; i < libs.length; i++) {
					excludes += "**/WEB-INF/lib/" + libs[i] + ",";
				}
			}

			if (appServerType.equals("websphere")) {
				WarTask.war(srcFile, deployDir, "WEB-INF/web.xml", webXML);
			}
			else {
				CopyTask.copyDirectory(
					srcFile, deployDir, includes, excludes, true, false);
			}
		}
	}

	protected void deployFile(File srcFile, File deployDir) throws Exception {
		if (UpToDateTask.isUpToDate(srcFile, deployDir)) {
			return;
		}

		DeleteTask.deleteDirectory(deployDir);

		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddkkmmssSSS");

		File tempDir = new File(sdf.format(new Date()));

		ExpandTask.expand(srcFile, tempDir);

		deployDirectory(tempDir, deployDir, getDisplayName(srcFile));

		DeleteTask.deleteDirectory(tempDir);
	}

	protected String getDisplayName(File srcFile) {
		String displayName = srcFile.getName();
		displayName = displayName.substring(0, displayName.length() - 4);

		if (displayName.startsWith(jbossPrefix)) {
			displayName = displayName.substring(1, displayName.length());
		}

		return displayName;
	}

	protected String getExtraContent(File srcFile, String displayName)
		throws Exception {

		String extraContent =
			"<display-name>" + displayName + "</display-name>";

		if (Validator.isNotNull(portletTaglibDTD)) {
			extraContent +=
				"<taglib>" +
				"<taglib-uri>http://java.sun.com/portlet</taglib-uri>" +
				"<taglib-location>" +
				"/WEB-INF/tld/liferay-portlet.tld" +
				"</taglib-location>" +
				"</taglib>";
		}

		if (Validator.isNotNull(themeTaglibDTD)) {
			extraContent +=
				"<taglib>" +
				"<taglib-uri>http://liferay.com/tld/theme</taglib-uri>" +
				"<taglib-location>" +
				"/WEB-INF/tld/liferay-theme.tld" +
				"</taglib-location>" +
				"</taglib>";
		}

		if (Validator.isNotNull(utilTaglibDTD)) {
			extraContent +=
				"<taglib>" +
				"<taglib-uri>http://liferay.com/tld/util</taglib-uri>" +
				"<taglib-location>" +
				"/WEB-INF/tld/liferay-util.tld" +
				"</taglib-location>" +
				"</taglib>";
		}

		return extraContent;
	}

	protected String baseDir;
	protected String destDir;
	protected String appServerType;
	protected String portletTaglibDTD;
	protected String themeTaglibDTD;
	protected String utilTaglibDTD;
	protected String jbossPrefix;
	protected String tomcatLibDir;
	protected List jars;

}