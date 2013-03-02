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

package com.liferay.portlet.plugininstaller.action;

import com.liferay.portal.events.GlobalStartupAction;
import com.liferay.portal.kernel.deploy.auto.AutoDeployDir;
import com.liferay.portal.kernel.deploy.auto.AutoDeployUtil;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.plugin.PluginPackageUtil;
import com.liferay.portal.plugin.RepositoryReport;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.tools.BaseDeployer;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.FileUtil;
import com.liferay.util.Http;
import com.liferay.util.servlet.ProgressInputStream;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;
import com.liferay.util.servlet.UploadException;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import java.net.MalformedURLException;
import java.net.URL;

import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;

import javax.servlet.http.HttpServletResponse;

import org.apache.commons.httpclient.HostConfiguration;
import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.methods.GetMethod;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="InstallPluginAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 * @author Brian Wing Shun Chan
 * @author Minhchau Dang
 *
 */
public class InstallPluginAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		PermissionChecker permissionChecker =
			themeDisplay.getPermissionChecker();

		if (!permissionChecker.isOmniadmin()) {
			SessionErrors.add(req, PrincipalException.class.getName());

			setForward(req, "portlet.plugin_installer.error");

			return;
		}

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (cmd.equals("deployConfiguration")) {
			deployConfiguration(req);
		}
		else if (cmd.equals("ignorePackages")) {
			ignorePackages(req);
		}
		else if (cmd.equals("localDeploy")) {
			localDeploy(req);
		}
		else if (cmd.equals("reloadRepositories")) {
			reloadRepositories(req);
		}
		else if (cmd.equals("remoteDeploy")) {
			remoteDeploy(req);
		}
		else if (cmd.equals("unignorePackages")) {
			unignorePackages(req);
		}

		sendRedirect(req, res);
	}

	protected void deployConfiguration(ActionRequest req) throws Exception {
		boolean enabled = ParamUtil.getBoolean(req, "enabled");
		String deployDir = ParamUtil.getString(req, "deployDir");
		String destDir = ParamUtil.getString(req, "destDir");
		long interval = ParamUtil.getLong(req, "interval");
		int blacklistThreshold = ParamUtil.getInteger(
			req, "blacklistThreshold");
		boolean unpackWar = ParamUtil.getBoolean(req, "unpackWar");
		boolean customPortletXml = ParamUtil.getBoolean(
			req, "customPortletXml");
		String jbossPrefix = ParamUtil.getString(req, "jbossPrefix");
		String tomcatConfDir = ParamUtil.getString(req, "tomcatConfDir");
		String tomcatLibDir = ParamUtil.getString(req, "tomcatLibDir");
		String pluginRepositoriesTrusted = ParamUtil.getString(
			req, "pluginRepositoriesTrusted");
		String pluginRepositoriesUntrusted = ParamUtil.getString(
			req, "pluginRepositoriesUntrusted");
		boolean pluginNotificationsEnabled = ParamUtil.getBoolean(
			req, "pluginNotificationsEnabled");
		String pluginPackagesIgnored = ParamUtil.getString(
			req, "pluginPackagesIgnored");

		PortletPreferences prefs = PrefsPropsUtil.getPreferences();

		prefs.setValue(PropsUtil.AUTO_DEPLOY_ENABLED, String.valueOf(enabled));
		prefs.setValue(PropsUtil.AUTO_DEPLOY_DEPLOY_DIR, deployDir);
		prefs.setValue(PropsUtil.AUTO_DEPLOY_DEST_DIR, destDir);
		prefs.setValue(
			PropsUtil.AUTO_DEPLOY_INTERVAL, String.valueOf(interval));
		prefs.setValue(
			PropsUtil.AUTO_DEPLOY_BLACKLIST_THRESHOLD,
			String.valueOf(blacklistThreshold));
		prefs.setValue(
			PropsUtil.AUTO_DEPLOY_UNPACK_WAR, String.valueOf(unpackWar));
		prefs.setValue(
			PropsUtil.AUTO_DEPLOY_CUSTOM_PORTLET_XML,
			String.valueOf(customPortletXml));
		prefs.setValue(PropsUtil.AUTO_DEPLOY_JBOSS_PREFIX, jbossPrefix);
		prefs.setValue(PropsUtil.AUTO_DEPLOY_TOMCAT_CONF_DIR, tomcatConfDir);
		prefs.setValue(PropsUtil.AUTO_DEPLOY_TOMCAT_LIB_DIR, tomcatLibDir);
		prefs.setValue(
			PropsUtil.PLUGIN_REPOSITORIES_TRUSTED, pluginRepositoriesTrusted);
		prefs.setValue(
			PropsUtil.PLUGIN_REPOSITORIES_UNTRUSTED,
			pluginRepositoriesUntrusted);
		prefs.setValue(
			PropsUtil.PLUGIN_NOTIFICATIONS_ENABLED,
			String.valueOf(pluginNotificationsEnabled));
		prefs.setValue(
			PropsUtil.PLUGIN_NOTIFICATIONS_PACKAGES_IGNORED,
			pluginPackagesIgnored);

		prefs.store();

		reloadRepositories(req);

		if (_log.isInfoEnabled()) {
			_log.info("Unregistering auto deploy directories");
		}

		AutoDeployUtil.unregisterDir("defaultAutoDeployDir");

		if (enabled) {
			if (_log.isInfoEnabled()) {
				_log.info("Registering auto deploy directories");
			}

			List autoDeployListeners =
				GlobalStartupAction.getAutoDeployListeners();

			AutoDeployDir autoDeployDir = new AutoDeployDir(
				"defaultAutoDeployDir", new File(deployDir), new File(destDir),
				interval, blacklistThreshold, autoDeployListeners);

			AutoDeployUtil.registerDir(autoDeployDir);
		}
		else {
			if (_log.isInfoEnabled()) {
				_log.info("Not registering auto deploy directories");
			}
		}
	}

	protected String[] getSourceForgeMirrors() {
		return PropsUtil.getArray(PropsUtil.SOURCE_FORGE_MIRRORS);
	}

	protected void ignorePackages(ActionRequest req) throws Exception {
		String pluginPackagesIgnored = ParamUtil.getString(
			req, "pluginPackagesIgnored");

		String oldPluginPackagesIgnored= PrefsPropsUtil.getString(
			PropsUtil.PLUGIN_NOTIFICATIONS_PACKAGES_IGNORED);

		StringMaker sm = new StringMaker();

		sm.append(oldPluginPackagesIgnored);
		sm.append(StringPool.NEW_LINE);
		sm.append(pluginPackagesIgnored);

		PortletPreferences prefs = PrefsPropsUtil.getPreferences();

		prefs.setValue(
			PropsUtil.PLUGIN_NOTIFICATIONS_PACKAGES_IGNORED, sm.toString());

		prefs.store();

		PluginPackageUtil.refreshUpdatesAvailableCache();
	}

	protected void localDeploy(ActionRequest req) throws Exception {
		UploadPortletRequest uploadReq =
			PortalUtil.getUploadPortletRequest(req);

		String fileName = null;

		String deploymentContext = ParamUtil.getString(
			req, "deploymentContext");

		if (Validator.isNotNull(deploymentContext)) {
			fileName =
				BaseDeployer.DEPLOY_TO_PREFIX + deploymentContext + ".war";
		}
		else {
			fileName = GetterUtil.getString(uploadReq.getFileName("file"));

			int pos = fileName.lastIndexOf(StringPool.PERIOD);

			if (pos != -1) {
				deploymentContext = fileName.substring(0, pos);
			}
		}

		File file = uploadReq.getFile("file");

		byte[] bytes = FileUtil.getBytes(file);

		if ((bytes == null) || (bytes.length == 0)) {
			SessionErrors.add(req, UploadException.class.getName());

			return;
		}

		try {
			PluginPackageUtil.registerPluginPackageInstallation(
				deploymentContext);

			String source = file.toString();

			String deployDir = PrefsPropsUtil.getString(
				PropsUtil.AUTO_DEPLOY_DEPLOY_DIR,
				PropsValues.AUTO_DEPLOY_DEPLOY_DIR);

			String destination = deployDir + StringPool.SLASH + fileName;

			FileUtil.copyFile(source, destination);

			SessionMessages.add(req, "pluginUploaded");
		}
		finally {
			PluginPackageUtil.endPluginPackageInstallation(deploymentContext);
		}
	}

	protected void reloadRepositories(ActionRequest req) throws Exception {
		RepositoryReport report = PluginPackageUtil.reloadRepositories();

		SessionMessages.add(req, WebKeys.PLUGIN_REPOSITORY_REPORT, report);
	}

	protected void remoteDeploy(ActionRequest req) throws Exception {
		try {
			String url = ParamUtil.getString(req, "url");

			URL urlObj = new URL(url);

			String host = urlObj.getHost();

			if (host.endsWith(".sf.net") || host.endsWith(".sourceforge.net")) {
				remoteDeploySourceForge(urlObj.getPath(), req);
			}
			else {
				remoteDeploy(url, urlObj, req, true);
			}
		}
		catch (MalformedURLException murle) {
			SessionErrors.add(req, "invalidUrl", murle);
		}
	}

	protected int remoteDeploy(
			String url, URL urlObj, ActionRequest req, boolean failOnError)
		throws Exception {

		int responseCode = HttpServletResponse.SC_OK;

		GetMethod getMethod = null;

		String deploymentContext = ParamUtil.getString(
			req, "deploymentContext");

		try {
			HostConfiguration hostConfig = Http.getHostConfig(url);

			HttpClient client = Http.getClient(hostConfig);

			getMethod = new GetMethod(url);

			String fileName = null;

			if (Validator.isNotNull(deploymentContext)) {
				fileName =
					BaseDeployer.DEPLOY_TO_PREFIX + deploymentContext + ".war";
			}
			else {
				fileName = url.substring(url.lastIndexOf(StringPool.SLASH) + 1);

				int pos = fileName.lastIndexOf(StringPool.PERIOD);

				if (pos != -1) {
					deploymentContext = fileName.substring(0, pos);
				}
			}

			PluginPackageUtil.registerPluginPackageInstallation(
				deploymentContext);

			responseCode = client.executeMethod(hostConfig, getMethod);

			if (responseCode != HttpServletResponse.SC_OK) {
				if (failOnError) {
					SessionErrors.add(
						req, "errorConnectingToUrl",
						new Object[] {String.valueOf(responseCode)});
				}

				return responseCode;
			}

			long contentLength = getMethod.getResponseContentLength();

			String progressId = ParamUtil.getString(req, Constants.PROGRESS_ID);

			ProgressInputStream pis = new ProgressInputStream(
				req, getMethod.getResponseBodyAsStream(), contentLength,
				progressId);

			String deployDir = PrefsPropsUtil.getString(
				PropsUtil.AUTO_DEPLOY_DEPLOY_DIR,
				PropsValues.AUTO_DEPLOY_DEPLOY_DIR);

			String tmpFilePath =
				deployDir + StringPool.SLASH + _DOWNLOAD_DIR +
					StringPool.SLASH + fileName;

			File tmpFile = new File(tmpFilePath);

			if (!tmpFile.getParentFile().exists()) {
				tmpFile.getParentFile().mkdirs();
			}

			FileOutputStream fos = new FileOutputStream(tmpFile);

			try {
				pis.readAll(fos);

				if (_log.isInfoEnabled()) {
					_log.info(
						"Downloaded plugin from " + urlObj + " has " +
							pis.getTotalRead() + " bytes");
				}
			}
			finally {
				pis.clearProgress();
			}

			getMethod.releaseConnection();

			if (pis.getTotalRead() > 0) {
				String destination = deployDir + StringPool.SLASH + fileName;

				File destinationFile = new File(destination);

				boolean moved = FileUtil.move(tmpFile, destinationFile);

				if (!moved) {
					FileUtil.copyFile(tmpFile, destinationFile);
					FileUtil.delete(tmpFile);
				}

				SessionMessages.add(req, "pluginDownloaded");
			}
			else {
				if (failOnError) {
					SessionErrors.add(req, UploadException.class.getName());
				}

				responseCode = HttpServletResponse.SC_INTERNAL_SERVER_ERROR;
			}
		}
		catch (MalformedURLException murle) {
			SessionErrors.add(req, "invalidUrl", murle);
		}
		catch (IOException ioe) {
			SessionErrors.add(req, "errorConnectingToUrl", ioe);
		}
		finally {
			if (getMethod != null) {
				getMethod.releaseConnection();
			}

			PluginPackageUtil.endPluginPackageInstallation(deploymentContext);
		}

		return responseCode;
	}

	protected void remoteDeploySourceForge(String path, ActionRequest req)
		throws Exception {

		String[] sourceForgeMirrors = getSourceForgeMirrors();

		for (int i = 0; i < sourceForgeMirrors.length; i++) {
			try {
				String url = sourceForgeMirrors[i] + path;

				if (_log.isDebugEnabled()) {
					_log.debug("Downloading from SourceForge mirror " + url);
				}

				URL urlObj = new URL(url);

				boolean failOnError = false;

				if ((i + 1) == sourceForgeMirrors.length) {
					failOnError = true;
				}

				int responseCode = remoteDeploy(url, urlObj, req, failOnError);

				if (responseCode == HttpServletResponse.SC_OK) {
					return;
				}
			}
			catch (MalformedURLException murle) {
				SessionErrors.add(req, "invalidUrl", murle);
			}
		}
	}

	protected void unignorePackages(ActionRequest req) throws Exception {
		String[] pluginPackagesUnignored = StringUtil.split(
			ParamUtil.getString(req, "pluginPackagesUnignored"),
			StringPool.NEW_LINE);

		String[] pluginPackagesIgnored = PrefsPropsUtil.getStringArray(
			PropsUtil.PLUGIN_NOTIFICATIONS_PACKAGES_IGNORED,
			StringPool.NEW_LINE,
			PropsValues.PLUGIN_NOTIFICATIONS_PACKAGES_IGNORED);

		StringMaker sm = new StringMaker();

		for (int i = 0; i < pluginPackagesIgnored.length; i++) {
			String packageId = pluginPackagesIgnored[i];

			if (!ArrayUtil.contains(pluginPackagesUnignored, packageId)) {
				sm.append(packageId);
				sm.append(StringPool.NEW_LINE);
			}
		}

		PortletPreferences prefs = PrefsPropsUtil.getPreferences();

		prefs.setValue(
			PropsUtil.PLUGIN_NOTIFICATIONS_PACKAGES_IGNORED, sm.toString());

		prefs.store();

		PluginPackageUtil.refreshUpdatesAvailableCache();
	}

	private static final String _DOWNLOAD_DIR = "download";

	private static Log _log = LogFactory.getLog(InstallPluginAction.class);

}