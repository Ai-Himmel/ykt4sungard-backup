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

package com.liferay.portal.servlet.filters.layoutcache;

import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.servlet.BaseFilter;
import com.liferay.portal.kernel.servlet.BrowserSniffer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.PortalInitable;
import com.liferay.portal.kernel.util.PortalInitableUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.struts.LastPath;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.Http;
import com.liferay.util.SystemProperties;
import com.liferay.util.servlet.filters.CacheResponse;
import com.liferay.util.servlet.filters.CacheResponseData;
import com.liferay.util.servlet.filters.CacheResponseUtil;

import java.io.IOException;

import java.util.Properties;

import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * <a href="LayoutCacheFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 * @author Javier de Ros
 * @author Raymond Augé
 *
 */
public class LayoutCacheFilter extends BaseFilter implements PortalInitable {

	public static final boolean USE_FILTER = GetterUtil.getBoolean(
		SystemProperties.get(LayoutCacheFilter.class.getName()), true);

	public static final String ENCODING = GetterUtil.getString(
		SystemProperties.get("file.encoding"), "UTF-8");

	public void portalInit() {
		_pattern = GetterUtil.getInteger(
			_config.getInitParameter("pattern"));

		if ((_pattern != _PATTERN_FRIENDLY) &&
			(_pattern != _PATTERN_LAYOUT) &&
			(_pattern != _PATTERN_RESOURCE)) {

			_log.error("Layout cache pattern is invalid");
		}
	}

	public void init(FilterConfig config) throws ServletException {
		super.init(config);

		_config = config;

		PortalInitableUtil.init(this);
	}

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		if (_log.isDebugEnabled()) {
			if (USE_FILTER) {
				_log.debug("Layout cache is enabled");
			}
			else {
				_log.debug("Layout cache is disabled");
			}
		}

		HttpServletRequest httpReq = (HttpServletRequest)req;
		HttpServletResponse httpRes = (HttpServletResponse)res;

		if (USE_FILTER && !isPortletRequest(httpReq) && isLayout(httpReq) &&
			!isSignedIn(httpReq) && !isInclude(httpReq) &&
			!isAlreadyFiltered(httpReq)) {

			httpReq.setAttribute(_ALREADY_FILTERED, Boolean.TRUE);

			String key = getCacheKey(httpReq);

			long companyId = PortalInstances.getCompanyId(httpReq);

			CacheResponseData data = LayoutCacheUtil.getCacheResponseData(
				companyId, key);

			if (data == null) {
				if (!isCacheable(companyId, httpReq)) {
					if (_log.isDebugEnabled()) {
						_log.debug("Layout is not cacheable " + key);
					}

					doFilter(LayoutCacheFilter.class, req, res, chain);

					return;
				}

				if (_log.isInfoEnabled()) {
					_log.info("Caching layout " + key);
				}

				CacheResponse cacheResponse = new CacheResponse(
					httpRes, ENCODING);

				doFilter(LayoutCacheFilter.class, req, cacheResponse, chain);

				data = new CacheResponseData(
					cacheResponse.getData(), cacheResponse.getContentType(),
					cacheResponse.getHeaders());

				LastPath lastPath = (LastPath)httpReq.getAttribute(
					WebKeys.LAST_PATH);

				if (lastPath != null) {
					data.setAttribute(WebKeys.LAST_PATH, lastPath);
				}

				if (data.getData().length > 0) {
					LayoutCacheUtil.putCacheResponseData(companyId, key, data);
				}
			}
			else {
				LastPath lastPath = (LastPath)data.getAttribute(
					WebKeys.LAST_PATH);

				if (lastPath != null) {
					HttpSession ses = httpReq.getSession();

					ses.setAttribute(WebKeys.LAST_PATH, lastPath);
				}
			}

			CacheResponseUtil.write(httpRes, data);
		}
		else {
			if (_log.isDebugEnabled()) {
				_log.debug("Did not request a layout");
			}

			doFilter(LayoutCacheFilter.class, req, res, chain);
		}
	}

	protected String getBrowserType(HttpServletRequest req) {
		if (BrowserSniffer.is_ie_7(req)) {
			return _BROWSER_TYPE_IE_7;
		}
		else if (BrowserSniffer.is_ie(req)) {
			return _BROWSER_TYPE_IE;
		}
		else {
			return _BROWSER_TYPE_OTHER;
		}
	}

	protected String getCacheKey(HttpServletRequest req) {
		StringMaker sm = new StringMaker();

		// Url

		sm.append(Http.getProtocol(req));
		sm.append("://");
		sm.append(req.getServletPath());
		sm.append(req.getPathInfo());
		sm.append(StringPool.QUESTION);
		sm.append(req.getQueryString());

		// Language

		sm.append(StringPool.POUND);
		sm.append(LanguageUtil.getLanguageId(req));

		// Browser type

		sm.append(StringPool.POUND);
		sm.append(getBrowserType(req));

		// Gzip compression

		sm.append(StringPool.POUND);
		sm.append(BrowserSniffer.acceptsGzip(req));

		return sm.toString().trim().toUpperCase();
	}

	protected long getPlid(
		long companyId, String pathInfo, String servletPath, long defaultPlid) {

		if (_pattern == _PATTERN_LAYOUT) {
			return defaultPlid;
		}

		if (Validator.isNull(pathInfo) ||
			!pathInfo.startsWith(StringPool.SLASH)) {

			return 0;
		}

		// Group friendly URL

		String friendlyURL = null;

		int pos = pathInfo.indexOf(StringPool.SLASH, 1);

		if (pos != -1) {
			friendlyURL = pathInfo.substring(0, pos);
		}
		else {
			if (pathInfo.length() > 1) {
				friendlyURL = pathInfo.substring(0, pathInfo.length());
			}
		}

		if (Validator.isNull(friendlyURL)) {
			return 0;
		}

		long groupId = 0;
		boolean privateLayout = false;

		try {
			Group group = GroupLocalServiceUtil.getFriendlyURLGroup(
				companyId, friendlyURL);

			groupId = group.getGroupId();

			if (servletPath.startsWith(
					PropsValues.
						LAYOUT_FRIENDLY_URL_PRIVATE_GROUP_SERVLET_MAPPING) ||
				servletPath.startsWith(
					PropsValues.
						LAYOUT_FRIENDLY_URL_PRIVATE_USER_SERVLET_MAPPING)) {

				privateLayout = true;
			}
			else if (servletPath.startsWith(
						PropsValues.
							LAYOUT_FRIENDLY_URL_PUBLIC_SERVLET_MAPPING)) {

				privateLayout = false;
			}
		}
		catch (NoSuchLayoutException nsle) {
			if (_log.isWarnEnabled()) {
				_log.warn(nsle);
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.error(e);
			}

			return 0;
		}

		// Layout friendly URL

		friendlyURL = null;

		if ((pos != -1) && ((pos + 1) != pathInfo.length())) {
			friendlyURL = pathInfo.substring(pos, pathInfo.length());
		}

		if (Validator.isNull(friendlyURL)) {
			return 0;
		}

		// If there is no layout path take the first from the group or user

		try {
			Layout layout = LayoutLocalServiceUtil.getFriendlyURLLayout(
				groupId, privateLayout, friendlyURL);

			return layout.getPlid();
		}
		catch (NoSuchLayoutException nsle) {
			_log.warn(nsle);

			return 0;
		}
		catch (Exception e) {
			_log.error(e);

			return 0;
		}
	}

	protected boolean isAlreadyFiltered(HttpServletRequest req) {
		if (req.getAttribute(_ALREADY_FILTERED) != null) {
			return true;
		}
		else {
			return false;
		}
	}

	protected boolean isCacheable(long companyId, HttpServletRequest req) {
		if (_pattern == _PATTERN_RESOURCE) {
			return true;
		}

		try {
			long plid = getPlid(
				companyId, req.getPathInfo(), req.getServletPath(),
				ParamUtil.getLong(req, "p_l_id"));

			if (plid <= 0) {
				return false;
			}

			Layout layout = LayoutLocalServiceUtil.getLayout(plid);

			if (!layout.getType().equals(LayoutImpl.TYPE_PORTLET)) {
				return false;
			}

			Properties props = layout.getTypeSettingsProperties();

			for (int i = 0; i < 10; i++) {
				String columnId = "column-" + i;

				String settings = props.getProperty(columnId, StringPool.BLANK);

				String[] portlets = StringUtil.split(settings);

				for (int j = 0; j < portlets.length; j++) {
					String portletId = StringUtil.extractFirst(
						portlets[j], PortletImpl.INSTANCE_SEPARATOR);

					Portlet portlet = PortletLocalServiceUtil.getPortletById(
						companyId, portletId);

					if (!portlet.isLayoutCacheable()) {
						return false;
					}
				}
			}
		}
		catch(Exception e) {
			return false;
		}

		return true;
	}

	protected boolean isInclude(HttpServletRequest req) {
		String uri = (String)req.getAttribute(
			JavaConstants.JAVAX_SERVLET_INCLUDE_REQUEST_URI);

		if (uri == null) {
			return false;
		}
		else {
			return true;
		}
	}

	protected boolean isLayout(HttpServletRequest req) {
		if ((_pattern == _PATTERN_FRIENDLY) ||
			(_pattern == _PATTERN_RESOURCE)) {

			return true;
		}
		else {
			String plid = ParamUtil.getString(req, "p_l_id");

			if (Validator.isNotNull(plid)) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	protected boolean isPortletRequest(HttpServletRequest req) {
		String portletId = ParamUtil.getString(req, "p_p_id");

		if (Validator.isNull(portletId)) {
			return false;
		}
		else {
			return true;
		}
	}

	protected boolean isSignedIn(HttpServletRequest req) {
		long userId = PortalUtil.getUserId(req);
		String remoteUser = req.getRemoteUser();

		if ((userId <= 0) && (remoteUser == null)) {
			return false;
		}
		else {
			return true;
		}
	}

	private static final String _ALREADY_FILTERED =
		LayoutCacheFilter.class + "_ALREADY_FILTERED";

	private static final int _PATTERN_FRIENDLY = 0;

	private static final int _PATTERN_LAYOUT = 1;

	private static final int _PATTERN_RESOURCE = 2;

	private static final String _BROWSER_TYPE_IE_7 = "ie_7";

	private static final String _BROWSER_TYPE_IE = "ie";

	private static final String _BROWSER_TYPE_OTHER = "other";

	private static Log _log = LogFactoryUtil.getLog(LayoutCacheFilter.class);

	private FilterConfig _config;
	private int _pattern;

}