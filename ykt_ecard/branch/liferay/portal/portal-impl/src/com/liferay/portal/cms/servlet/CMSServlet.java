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

package com.liferay.portal.cms.servlet;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.service.CompanyLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.theme.ThemeDisplayFactory;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.ExtPropertiesLoader;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.IOException;

import java.util.Properties;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="CMSServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 * @author Raymond Augé
 *
 */
public class CMSServlet extends HttpServlet {

	public void init(ServletConfig config) throws ServletException {
		super.init(config);

		_groupId = GetterUtil.getLong(config.getInitParameter("group_id"));

		String redirectsConf = config.getInitParameter("redirects_conf");

		if (redirectsConf != null) {
			_redirectProperties = ExtPropertiesLoader.getInstance(
				redirectsConf).getProperties();
		}

		_redirectsEnabled = GetterUtil.getBoolean(
			config.getInitParameter("redirects_enabled"));
	}

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		long groupId = _groupId;

		if (groupId <= 0) {
			groupId = ParamUtil.getLong(req, "groupId");
		}

		String path = GetterUtil.getString(req.getPathInfo());

		if (path.endsWith(StringPool.SLASH)) {
			path = path.substring(0, path.length() - 1);
		}

		if (path.startsWith(StringPool.SLASH)) {
			path = path.substring(1, path.length());
		}

		if ((_redirectProperties != null) && _redirectsEnabled) {
			String redirect = _redirectProperties.getProperty(path);

			if (Validator.isNotNull(redirect)) {
				res.sendRedirect(redirect);

				return;
			}
		}

		String languageId = LanguageUtil.getLanguageId(req);

		ThemeDisplay themeDisplay = null;

		try {
			themeDisplay = ThemeDisplayFactory.create();

			long companyId = PortalInstances.getCompanyId(req);

			Company company = CompanyLocalServiceUtil.getCompanyById(companyId);

			String contextPath = PortalUtil.getPathContext();

			themeDisplay.setCompany(company);
			themeDisplay.setPortletGroupId(groupId);
			themeDisplay.setPathContext(contextPath);
			themeDisplay.setPathFriendlyURLPrivateGroup(
				PortalUtil.getPathFriendlyURLPrivateGroup());
			themeDisplay.setPathFriendlyURLPrivateUser(
				PortalUtil.getPathFriendlyURLPrivateUser());
			themeDisplay.setPathFriendlyURLPublic(
				PortalUtil.getPathFriendlyURLPublic());
			themeDisplay.setPathImage(PortalUtil.getPathImage());
			themeDisplay.setPathMain(PortalUtil.getPathMain());

			String content = getContent(
				groupId, path, languageId, themeDisplay);

			if (Validator.isNotNull(content)) {
				if (_log.isDebugEnabled()) {
					_log.debug("Content found for " + path);
				}

				String mimeType = ParamUtil.getString(
					req, "mimeType", ContentTypes.TEXT_HTML_UTF8);

				res.setContentType(mimeType);

				try {
					ServletResponseUtil.write(res, content);
				}
				catch (Exception e) {
					if (_log.isWarnEnabled()) {
						_log.warn(e, e);
					}
				}
			}
			else {
				if (_log.isDebugEnabled()) {
					_log.debug("Content NOT found for " + path);
				}
			}
		}
		catch (Exception e) {
		}
		finally {
			try {
				ThemeDisplayFactory.recycle(themeDisplay);
			}
			catch (Exception e) {
			}
		}
	}

	protected String getContent(
		long groupId, String articleId, String languageId,
		ThemeDisplay themeDisplay) {

		return CMSServletUtil.getContent(
			groupId, articleId, languageId, themeDisplay);
	}

	private static Log _log = LogFactory.getLog(CMSServlet.class);

	private long _groupId;
	private Properties _redirectProperties;
	private boolean _redirectsEnabled;

}