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

package com.liferay.filters.compression;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.servlet.BaseFilter;
import com.liferay.portal.kernel.servlet.BrowserSniffer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.ServerDetector;
import com.liferay.util.Http;
import com.liferay.util.SystemProperties;

import java.io.IOException;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="CompressionFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class CompressionFilter extends BaseFilter {

	static boolean useFilter = GetterUtil.getBoolean(
		SystemProperties.get(CompressionFilter.class.getName()), true);

	public static final String ENCODING = GetterUtil.getString(
		SystemProperties.get("file.encoding"), "UTF-8");

	static {

		// The compression filter will work on JBoss, Jetty, JOnAS, OC4J, Orion,
		// and Tomcat, but may break on other servers

		if (useFilter) {
			if (ServerDetector.isJBoss() || ServerDetector.isJetty() ||
				ServerDetector.isJOnAS() || ServerDetector.isOC4J() ||
				ServerDetector.isOrion() || ServerDetector.isTomcat()) {

				useFilter = true;
			}
			else {
				useFilter = false;
			}
		}
	}

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		if (_log.isDebugEnabled()) {
			if (useFilter) {
				_log.debug("Compression is enabled");
			}
			else {
				_log.debug("Compression is disabled");
			}
		}

		HttpServletRequest httpReq = (HttpServletRequest)req;
		HttpServletResponse httpRes = (HttpServletResponse)res;

		String completeURL = Http.getCompleteURL(httpReq);

		if (useFilter && isCompress(httpReq) && !isInclude(httpReq) &&
			BrowserSniffer.acceptsGzip(httpReq) &&
			!isAlreadyFiltered(httpReq)) {

			if (_log.isDebugEnabled()) {
				_log.debug("Compressing " + completeURL);
			}

			httpReq.setAttribute(_ALREADY_FILTERED, Boolean.TRUE);

			CompressionResponse compressionResponse =
				new CompressionResponse(httpRes);

			doFilter(CompressionFilter.class, req, compressionResponse, chain);

			compressionResponse.finishResponse();
		}
		else {
			if (_log.isDebugEnabled()) {
				_log.debug("Not compressing " + completeURL);
			}

			doFilter(CompressionFilter.class, req, res, chain);
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

	protected boolean isCompress(HttpServletRequest req) {
		if (!ParamUtil.get(req, _COMPRESS, true)) {
			return false;
		}
		else {

			// The exclusive state is used to stream binary content.
			// Compressing binary content through a servlet filter is bad on
			// performance because the user will not start downloading the
			// content until the entire content is compressed.

			String windowState = ParamUtil.getString(req, "p_p_state");

			if (windowState.equals("exclusive")) {
				return false;
			}
			else {
				return true;
			}
		}
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

	private static final String _ALREADY_FILTERED =
		CompressionFilter.class.getName() + "_ALREADY_FILTERED";

	private static final String _COMPRESS = "compress";

	private static Log _log = LogFactoryUtil.getLog(CompressionFilter.class);

}