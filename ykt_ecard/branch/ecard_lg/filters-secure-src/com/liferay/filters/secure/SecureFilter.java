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

package com.liferay.filters.secure;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.GetterUtil;
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;

import java.io.IOException;

import java.util.Set;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="SecureFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class SecureFilter implements Filter {

	public void init(FilterConfig filterConfig) {
		String propertyPrefix =
			filterConfig.getInitParameter("portal_property_prefix");

		String[] hostsAllowedArray = null;

		if (Validator.isNull(propertyPrefix)) {
			hostsAllowedArray = StringUtil.split(
				filterConfig.getInitParameter("hosts.allowed"));
			_httpsRequired = GetterUtil.getBoolean(
				filterConfig.getInitParameter("https.required"));
		}
		else {
			hostsAllowedArray = PropsUtil.getArray(
				propertyPrefix + "hosts.allowed");
			_httpsRequired = GetterUtil.getBoolean(
				PropsUtil.get(propertyPrefix + "https.required"));
		}

		for (int i = 0; i < hostsAllowedArray.length; i++) {
			_hostsAllowed.add(hostsAllowedArray[i]);
		}
	}

	public void destroy() {
	}

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		String remoteAddr = req.getRemoteAddr();

		if (isAccessAllowed(req)) {
			_log.debug("Access allowed for " + remoteAddr);
		}
		else {
			_log.error("Access denied for " + remoteAddr);

			return;
		}

		if (_httpsRequired) {
			_log.debug("https is required");
		}
		else {
			_log.debug("https is not required");
		}

		HttpServletRequest request = (HttpServletRequest)req;
		HttpServletResponse response = (HttpServletResponse)res;

		String completeURL = Http.getCompleteURL(request);

		if (_httpsRequired && !request.isSecure()) {
			_log.debug("Securing " + completeURL);

			FastStringBuffer redirectURL = new FastStringBuffer();

			redirectURL.append(Http.HTTPS_WITH_SLASH);
			redirectURL.append(request.getServerName());
			redirectURL.append(request.getServletPath());

			String queryString = request.getQueryString();

			if (Validator.isNotNull(queryString)) {
				redirectURL.append(StringPool.QUESTION);
				redirectURL.append(request.getQueryString());
			}

			_log.debug("Redirect to " + redirectURL);

			response.sendRedirect(redirectURL.toString());
		}
		else {
			_log.debug("Not securing " + completeURL);

			chain.doFilter(req, res);
		}
	}

	protected boolean isAccessAllowed(ServletRequest req) {
		String remoteAddr = req.getRemoteAddr();
		String serverIp = req.getServerName();

		if ((_hostsAllowed.size() > 0) &&
			(!_hostsAllowed.contains(remoteAddr))) {

			if ((serverIp.equals(remoteAddr)) &&
				(_hostsAllowed.contains(_SERVER_IP))) {

				return true;
			}

			return false;
		}
		else {
			return true;
		}
	}

	private static final Log _log = LogFactory.getLog(SecureFilter.class);

	private static final String _SERVER_IP = "SERVER_IP";

	private Set _hostsAllowed = CollectionFactory.getHashSet();
	private boolean _httpsRequired;

}