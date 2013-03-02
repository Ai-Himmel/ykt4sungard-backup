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

package com.liferay.portal.servlet;

import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.plugin.PluginPackageUtil;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalServiceUtil;
import com.liferay.util.Http;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.IOException;

import java.text.SimpleDateFormat;

import java.util.Calendar;
import java.util.Date;
import java.util.Enumeration;
import java.util.Properties;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="SoftwareCatalogServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class SoftwareCatalogServlet extends HttpServlet {

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		try {
			long groupId = getGroupId(req);
			String version = getVersion(req);
			String baseImageURL = getBaseImageURL(req);
			Date oldestDate = getOldestDate(req);
			int maxNumOfVersions = ParamUtil.getInteger(
				req, "maxNumOfVersions");
			Properties repoSettings = getRepoSettings(req);

			if (_log.isDebugEnabled()) {
				_log.debug("Group ID " + groupId);
				_log.debug("Base image URL " + baseImageURL);
				_log.debug("Oldtest date " + oldestDate);
				_log.debug("Maximum number of versions " + maxNumOfVersions);
			}

			String repositoryXML =
				SCProductEntryLocalServiceUtil.getRepositoryXML(
					groupId, version, baseImageURL, oldestDate,
					maxNumOfVersions, repoSettings);

			String fileName = null;
			byte[] byteArray = repositoryXML.getBytes("UTF-8");

			ServletResponseUtil.sendFile(
				res, fileName, byteArray, ContentTypes.TEXT_XML_UTF8);
		}
		catch (NoSuchGroupException nsge) {
			PortalUtil.sendError(
				HttpServletResponse.SC_NOT_FOUND, nsge, req, res);
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e, e);
			}

			PortalUtil.sendError(
				HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e, req, res);
		}
	}

	protected String getBaseImageURL(HttpServletRequest req) {
		String host = PortalUtil.getHost(req);

		String portalURL = PortalUtil.getPortalURL(
			host, req.getServerPort(), req.isSecure());

		String pathImage = PortalUtil.getPathImage();

		if (pathImage.startsWith(Http.HTTP_WITH_SLASH) ||
			pathImage.startsWith(Http.HTTPS_WITH_SLASH)) {

			return pathImage + "/software_catalog";
		}
		else {
			return portalURL + pathImage + "/software_catalog";
		}
	}

	protected long getGroupId(HttpServletRequest req)
		throws SystemException, PortalException {

		long groupId = ParamUtil.getLong(req, "groupId");

		if (groupId <= 0) {
			String path = GetterUtil.getString(req.getPathInfo());

			path = StringUtil.replace(
				path, StringPool.DOUBLE_SLASH, StringPool.SLASH);

			if (Validator.isNotNull(path)) {
				int pos = path.indexOf(StringPool.SLASH, 1);

				if (pos == -1) {
					pos = path.length();
				}

				groupId = GetterUtil.getLong(path.substring(1, pos));
			}
		}

		if (groupId <= 0) {
			long companyId = PortalInstances.getCompanyId(req);

			Group guestGroup = GroupLocalServiceUtil.getGroup(
				companyId, GroupImpl.GUEST);

			groupId = guestGroup.getGroupId();
		}

		return groupId;
	}

	protected Date getOldestDate(HttpServletRequest req) {
		Date oldestDate = null;

		oldestDate = ParamUtil.getDate(
			req, "oldestDate", new SimpleDateFormat("yyyy.MM.dd"), null);

		if (oldestDate == null) {
			int daysOld = ParamUtil.getInteger(req, "maxAge", -1);

			if (daysOld != -1) {
				Calendar cal = Calendar.getInstance();

				cal.add(Calendar.DATE, (0 - daysOld));

				oldestDate = cal.getTime();
			}
		}

		return oldestDate;
	}

	protected Properties getRepoSettings(HttpServletRequest req) {
		Properties repoSettings = new Properties();

		String prefix = "setting_";

		Enumeration enu = req.getParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (name.startsWith(prefix)) {
				String settingName = name.substring(
					prefix.length(), name.length());

				String value = ParamUtil.getString(req, name);

				if (Validator.isNotNull(value)) {
					repoSettings.setProperty(settingName , value);
				}
			}
		}

		return repoSettings;
	}

	protected String getVersion(HttpServletRequest req)
		throws PortalException, SystemException {

		String version = ParamUtil.getString(req, "version");

		String prefix =
			PluginPackageUtil.REPOSITORY_XML_FILENAME_PREFIX + StringPool.DASH;
		String extension =
			StringPool.PERIOD +
				PluginPackageUtil.REPOSITORY_XML_FILENAME_EXTENSION;

		if (Validator.isNull(version)) {
			String path = GetterUtil.getString(req.getPathInfo());

			if (Validator.isNotNull(path)) {
				int x = path.indexOf(prefix);

				if (x != -1) {
					version = path.substring(
						x + prefix.length(), path.indexOf(extension, x));
				}
			}
		}

		if (_log.isDebugEnabled()) {
			if (Validator.isNull(version)) {
				_log.debug("Serving repository for all versions");
			}
			else {
				_log.debug("Serving repository for version " + version);
			}
		}

		return version;
	}

	private static Log _log = LogFactory.getLog(SoftwareCatalogServlet.class);

}