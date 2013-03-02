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

package com.liferay.portal.servlet.filters.virtualhost;

import com.liferay.portal.LayoutFriendlyURLException;
import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.servlet.BaseFilter;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.LayoutSet;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.servlet.AbsoluteRedirectsResponse;
import com.liferay.portal.struts.LastPath;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.SystemProperties;

import java.io.IOException;

import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * <a href="VirtualHostFilter.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This filter is used to provide virtual host functionality. However, this
 * filter is still required even if you do not use virtual hosting because it
 * sets the company id in the request so that subsequent calls in the thread
 * have the company id properly set. This filter must also always be the first
 * filter in the list of filters.
 * </p>
 *
 * @author Joel Kozikowski
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class VirtualHostFilter extends BaseFilter {

	public static final boolean USE_FILTER = GetterUtil.getBoolean(
		SystemProperties.get(VirtualHostFilter.class.getName()), true);

	public static final String ENCODING = GetterUtil.getString(
		SystemProperties.get("file.encoding"), "UTF-8");

	public void init(FilterConfig config) throws ServletException {
		super.init(config);

		_ctx = config.getServletContext();
	}

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		if (_log.isDebugEnabled()) {
			if (USE_FILTER) {
				_log.debug("Virtual host is enabled");
			}
			else {
				_log.debug("Virtual host is disabled");
			}
		}

		HttpServletRequest httpReq = (HttpServletRequest)req;
		HttpServletResponse httpRes = (HttpServletResponse)res;

		httpReq.setCharacterEncoding(ENCODING);
		//httpRes.setContentType(ContentTypes.TEXT_HTML_UTF8);

		// Make sure all redirects issued by the portal are absolute

		httpRes = new AbsoluteRedirectsResponse(httpReq, httpRes);

		// Company id needs to always be called here so that it's properly set
		// in subsequent calls

		long companyId = PortalInstances.getCompanyId(httpReq);

		if (_log.isDebugEnabled()) {
			_log.debug("Company id " + companyId);
		}

		PortalUtil.getCurrentURL(httpReq);

		HttpSession ses = httpReq.getSession();

		Boolean httpsInitial = (Boolean)ses.getAttribute(WebKeys.HTTPS_INITIAL);

		if (httpsInitial == null) {
			httpsInitial = Boolean.valueOf(httpReq.isSecure());

			ses.setAttribute(WebKeys.HTTPS_INITIAL, httpsInitial);

			if (_log.isDebugEnabled()) {
				_log.debug("Setting httpsInitial to " + httpsInitial);
			}
		}

		if (!USE_FILTER) {
			doFilter(VirtualHostFilter.class, req, httpRes, chain);

			return;
		}

		StringBuffer requestURL = httpReq.getRequestURL();

		if (_log.isDebugEnabled()) {
			_log.debug("Received " + requestURL);
		}

		if (!isValidRequestURL(requestURL)) {
			doFilter(VirtualHostFilter.class, req, httpRes, chain);

			return;
		}

		String contextPath = PortalUtil.getPathContext();

		String friendlyURL = httpReq.getRequestURI().toLowerCase();

		if ((!contextPath.equals(StringPool.SLASH)) &&
			(friendlyURL.indexOf(contextPath) != -1)) {

			friendlyURL = friendlyURL.substring(
				contextPath.length(), friendlyURL.length());
		}

		friendlyURL = StringUtil.replace(
			friendlyURL, StringPool.DOUBLE_SLASH, StringPool.SLASH);

		if (_log.isDebugEnabled()) {
			_log.debug("Friendly URL " + friendlyURL);
		}

		if (!isValidFriendlyURL(friendlyURL)) {
			doFilter(VirtualHostFilter.class, req, httpRes, chain);

			return;
		}

		LayoutSet layoutSet = (LayoutSet)req.getAttribute(
			WebKeys.VIRTUAL_HOST_LAYOUT_SET);

		if (_log.isDebugEnabled()) {
			_log.debug("Layout set " + layoutSet);
		}

		if (layoutSet != null) {
			try {
				LastPath lastPath = new LastPath(
					StringPool.BLANK, friendlyURL, req.getParameterMap());

				req.setAttribute(WebKeys.LAST_PATH, lastPath);

				StringMaker prefix = new StringMaker();

				if (layoutSet.isPrivateLayout()) {
					prefix.append(PortalUtil.getPathFriendlyURLPrivateGroup());
				}
				else {
					prefix.append(PortalUtil.getPathFriendlyURLPublic());
				}

				Group group = GroupLocalServiceUtil.getGroup(
					layoutSet.getGroupId());

				if (Validator.isNotNull(group.getFriendlyURL())) {
					prefix.append(group.getFriendlyURL());
				}
				else {
					prefix.append(
						group.getDefaultFriendlyURL(
							layoutSet.isPrivateLayout()));
				}

				StringMaker redirect = new StringMaker();

				redirect.append(prefix);
				redirect.append(friendlyURL);

				String query = httpReq.getQueryString();

				if (query != null) {
					redirect.append(StringPool.QUESTION);
					redirect.append(query);
				}

				if (_log.isDebugEnabled()) {
					_log.debug("Redirect to " + redirect);
				}

				RequestDispatcher rd =
					_ctx.getRequestDispatcher(redirect.toString());

				rd.forward(req, httpRes);

				return;
			}
			catch (Exception e) {
				_log.error(e, e);
			}
		}

		doFilter(VirtualHostFilter.class, req, httpRes, chain);
	}

	protected boolean isValidFriendlyURL(String friendlyURL) {
		if (PortalInstances.isIgnorePath(friendlyURL) ||
			friendlyURL.startsWith(
				PortalUtil.getPathFriendlyURLPrivateGroup()) ||
			friendlyURL.startsWith(PortalUtil.getPathFriendlyURLPublic()) ||
			friendlyURL.startsWith(
				PortalUtil.getPathFriendlyURLPrivateUser()) ||
			friendlyURL.startsWith(_PATH_C) ||
			friendlyURL.startsWith(_PATH_DELEGATE) ||
			friendlyURL.startsWith(_PATH_HTML) ||
			friendlyURL.startsWith(_PATH_IMAGE) ||
			friendlyURL.startsWith(_PATH_LANGUAGE) ||
			friendlyURL.startsWith(_PATH_SITEMAP_XML) ||
			friendlyURL.startsWith(_PATH_SOFTWARE_CATALOG) ||
			friendlyURL.startsWith(_PATH_WAP) ||
			friendlyURL.startsWith(_PATH_WSRP)) {

			return false;
		}

		int code = LayoutImpl.validateFriendlyURL(friendlyURL);

		if ((code > -1) &&
			(code != LayoutFriendlyURLException.ENDS_WITH_SLASH)) {

			return false;
		}

		return true;
	}

	protected boolean isValidRequestURL(StringBuffer requestURL) {
		if (requestURL == null) {
			return false;
		}

		String url = requestURL.toString();

		if (url.endsWith(_EXT_C) || url.endsWith(_EXT_CSS) ||
			url.endsWith(_EXT_GIF) || url.endsWith(_EXT_IMAGE_COMPANY_LOGO) ||
			url.endsWith(_EXT_ICO) || url.endsWith(_EXT_JS) ||
			url.endsWith(_EXT_JPEG) || url.endsWith(_EXT_PORTAL_CSS_CACHED) ||
			url.endsWith(_EXT_PORTAL_JAVASCRIPT_CACHED) ||
			url.endsWith(_EXT_PORTAL_LAYOUT) ||
			url.endsWith(_EXT_PORTAL_LOGIN) ||
			url.endsWith(_EXT_PORTAL_LOGOUT) || url.endsWith(_EXT_PNG)) {

			return false;
		}
		else {
			return true;
		}
	}

	private static Log _log = LogFactoryUtil.getLog(VirtualHostFilter.class);

	private static String _EXT_C = "/c";

	private static String _EXT_CSS = ".css";

	private static String _EXT_GIF = ".gif";

	private static String _EXT_IMAGE_COMPANY_LOGO = "/image/company_logo";

	private static String _EXT_ICO = ".ico";

	private static String _EXT_JS = ".js";

	private static String _EXT_JPEG = ".jpeg";

	private static String _EXT_PORTAL_CSS_CACHED = "/portal/css_cached";

	private static String _EXT_PORTAL_JAVASCRIPT_CACHED =
		"/portal/javascript_cached";

	private static String _EXT_PORTAL_LAYOUT = "/portal/layout";

	private static String _EXT_PORTAL_LOGIN = "/portal/login";

	private static String _EXT_PORTAL_LOGOUT = "/portal/logout";

	private static String _EXT_PNG = ".png";

	private static String _PATH_C = "/c/";

	private static String _PATH_DELEGATE = "/delegate/";

	private static String _PATH_HTML = "/html/";

	private static String _PATH_IMAGE = "/image/";

	private static String _PATH_LANGUAGE = "/language/";

	private static String _PATH_SITEMAP_XML = "/sitemap.xml";

	private static String _PATH_SOFTWARE_CATALOG = "/software_catalog/";

	private static String _PATH_WAP = "/wap/";

	private static String _PATH_WSRP = "/wsrp/";

	private ServletContext _ctx;

}