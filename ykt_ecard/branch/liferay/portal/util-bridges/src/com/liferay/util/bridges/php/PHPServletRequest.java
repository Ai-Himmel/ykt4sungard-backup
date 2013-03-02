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

package com.liferay.util.bridges.php;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletConfig;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletRequestWrapper;

/**
 * <a href="PHPServletRequest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 */
public class PHPServletRequest extends HttpServletRequestWrapper {

	public PHPServletRequest(HttpServletRequest req, ServletConfig config,
							 RenderRequest renderReq, RenderResponse renderRes,
							 PortletConfig portletConfig, String phpURI) {

		super(req);

		_config = config;
		_renderReq = renderReq;
		_renderRes = renderRes;
		_portletConfig = portletConfig;

		StringBuffer sb = new StringBuffer();

		int pos = phpURI.indexOf(StringPool.QUESTION);

		if (pos != -1) {
			_path = phpURI.substring(0, pos);

			sb.append(phpURI.substring(pos + 1));
		}
		else {
			_path = phpURI;
		}

		if (GetterUtil.getBoolean(
				portletConfig.getInitParameter("add-portlet-params"), true)) {

			sb.append(StringPool.AMPERSAND);
			sb.append("portlet_namespace");
			sb.append(StringPool.EQUAL);
			sb.append(_renderRes.getNamespace());
			sb.append(StringPool.AMPERSAND);
			sb.append("portlet_name");
			sb.append(StringPool.EQUAL);
			sb.append(_portletConfig.getPortletName());
		}

		_queryString = sb.toString();

		req.setAttribute(
			JavaConstants.JAVAX_SERVLET_INCLUDE_QUERY_STRING, getQueryString());
		req.setAttribute(
			JavaConstants.JAVAX_SERVLET_INCLUDE_PATH_INFO, getPathInfo());
		req.setAttribute(
			JavaConstants.JAVAX_SERVLET_INCLUDE_REQUEST_URI, getRequestURI());
		req.setAttribute(
			JavaConstants.JAVAX_SERVLET_INCLUDE_SERVLET_PATH, _path);
	}

	public String getContextPath() {
		return StringPool.SLASH;
	}

	public String getParameter(String name) {
		return _renderReq.getParameter(name);
	}

	public Map getParameterMap() {
		return _renderReq.getParameterMap();
	}

	public Enumeration getParameterNames() {
		return _renderReq.getParameterNames();
	}

	public String[] getParameterValues(String name) {
		return _renderReq.getParameterValues(name);
	}

	public String getPathInfo() {
		return StringPool.BLANK;
	}

	public String getPathTranslated() {
		return StringPool.BLANK;
	}

	public String getQueryString() {
		return _queryString;
	}

	public String getRealPath(String path) {
		return _config.getServletContext().getRealPath(path);
	}

	public String getRequestURI() {
		return _path + StringPool.QUESTION + _queryString;
	}

	public StringBuffer getRequestURL() {
		StringBuffer sb = new StringBuffer();

		sb.append(getRequest().getProtocol());
		sb.append("://");
		sb.append(getRequest().getRemoteHost());
		sb.append(StringPool.COLON);
		sb.append(getRequest().getServerPort());
		sb.append(StringPool.SLASH);
		sb.append(getRequestURI());

		return sb;
	}

	public String getServletPath() {
		return _path;
	}

	protected Map parseQueryString(String queryString) {
		Map params = new HashMap();

		if (Validator.isNull(queryString)) {
			return params;
		}

		int ampersandIndex;

		do {
			ampersandIndex = queryString.indexOf(StringPool.AMPERSAND);

			String nameValuePair;

			if (ampersandIndex == -1) {
				nameValuePair = queryString;
			}
			else {
				nameValuePair = queryString.substring(0, ampersandIndex);
				queryString = queryString.substring(ampersandIndex + 1);
			}

			int equalIndex = nameValuePair.indexOf(StringPool.EQUAL);

			String key = nameValuePair;
			String value = StringPool.BLANK;

			if (equalIndex != -1) {
				key = nameValuePair.substring(0, equalIndex);
				value = nameValuePair.substring(equalIndex + 1);
			}

			params.put(key, value);

		}
		while (ampersandIndex != -1);

		return params;
	}

	private ServletConfig _config;
	private PortletConfig _portletConfig;
	private RenderRequest _renderReq;
	private RenderResponse _renderRes;
	private String _queryString;
	private String _path;

}