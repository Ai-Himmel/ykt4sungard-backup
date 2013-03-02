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

package com.liferay.filters.strip;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.servlet.BaseFilter;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.util.Http;
import com.liferay.util.SystemProperties;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.IOException;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="StripFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class StripFilter extends BaseFilter {

	public static final boolean USE_FILTER = GetterUtil.getBoolean(
		SystemProperties.get(StripFilter.class.getName()), true);

	public static final String ENCODING = GetterUtil.getString(
		SystemProperties.get("file.encoding"), "UTF-8");

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		if (_log.isDebugEnabled()) {
			if (USE_FILTER) {
				_log.debug("Strip is enabled");
			}
			else {
				_log.debug("Strip is disabled");
			}
		}

		HttpServletRequest httpReq = (HttpServletRequest)req;
		HttpServletResponse httpRes = (HttpServletResponse)res;

		String completeURL = Http.getCompleteURL(httpReq);

		if (USE_FILTER && isStrip(httpReq) && !isInclude(httpReq) &&
			!isAlreadyFiltered(httpReq)) {

			if (_log.isDebugEnabled()) {
				_log.debug("Stripping " + completeURL);
			}

			httpReq.setAttribute(_ALREADY_FILTERED, Boolean.TRUE);

			StripResponse stripResponse = new StripResponse(httpRes);

			doFilter(StripFilter.class, req, stripResponse, chain);

			String contentType = GetterUtil.getString(
				stripResponse.getContentType());

			byte[] oldByteArray = stripResponse.getData();

			if ((oldByteArray != null) && (oldByteArray.length > 0)) {
				byte[] newByteArray = new byte[oldByteArray.length];
				int newByteArrayPos = 0;

				if (_log.isDebugEnabled()) {
					_log.debug("Stripping content of type " + contentType);
				}

				if (contentType.toLowerCase().indexOf("text/") != -1) {
					boolean ignore = false;
					char prevChar = '\n';

					for (int i = 0; i < oldByteArray.length; i++) {
						byte b = oldByteArray[i];
						char c = (char)b;

						if (c == '<') {

							// Ignore text inside certain HTML tags.

							if (!ignore) {

								// Check for <pre>

								if ((i + 4) < oldByteArray.length) {
									char c1 = (char)oldByteArray[i + 1];
									char c2 = (char)oldByteArray[i + 2];
									char c3 = (char)oldByteArray[i + 3];
									char c4 = (char)oldByteArray[i + 4];

									if (((c1 == 'p') || (c1 == 'P')) &&
										((c2 == 'r') || (c2 == 'R')) &&
										((c3 == 'e') || (c3 == 'E')) &&
										((c4 == '>'))) {

										ignore = true;
									}
								}

								// Check for <textarea

								if (!ignore &&
									((i + 9) < oldByteArray.length)) {

									char c1 = (char)oldByteArray[i + 1];
									char c2 = (char)oldByteArray[i + 2];
									char c3 = (char)oldByteArray[i + 3];
									char c4 = (char)oldByteArray[i + 4];
									char c5 = (char)oldByteArray[i + 5];
									char c6 = (char)oldByteArray[i + 6];
									char c7 = (char)oldByteArray[i + 7];
									char c8 = (char)oldByteArray[i + 8];
									char c9 = (char)oldByteArray[i + 9];

									if (((c1 == 't') || (c1 == 'T')) &&
										((c2 == 'e') || (c2 == 'E')) &&
										((c3 == 'x') || (c3 == 'X')) &&
										((c4 == 't') || (c4 == 'T')) &&
										((c5 == 'a') || (c5 == 'A')) &&
										((c6 == 'r') || (c6 == 'R')) &&
										((c7 == 'e') || (c7 == 'E')) &&
										((c8 == 'a') || (c8 == 'A')) &&
										((c9 == ' '))) {

										ignore = true;
									}
								}
							}
							else if (ignore) {

								// Check for </pre>

								if ((i + 5) < oldByteArray.length) {
									char c1 = (char)oldByteArray[i + 1];
									char c2 = (char)oldByteArray[i + 2];
									char c3 = (char)oldByteArray[i + 3];
									char c4 = (char)oldByteArray[i + 4];
									char c5 = (char)oldByteArray[i + 5];

									if (((c1 == '/')) &&
										((c2 == 'p') || (c2 == 'P')) &&
										((c3 == 'r') || (c3 == 'R')) &&
										((c4 == 'e') || (c4 == 'E')) &&
										((c5 == '>'))) {

										ignore = false;
									}
								}

								// Check for </textarea>

								if (ignore &&
									((i + 10) < oldByteArray.length)) {

									char c1 = (char)oldByteArray[i + 1];
									char c2 = (char)oldByteArray[i + 2];
									char c3 = (char)oldByteArray[i + 3];
									char c4 = (char)oldByteArray[i + 4];
									char c5 = (char)oldByteArray[i + 5];
									char c6 = (char)oldByteArray[i + 6];
									char c7 = (char)oldByteArray[i + 7];
									char c8 = (char)oldByteArray[i + 8];
									char c9 = (char)oldByteArray[i + 9];
									char c10 = (char)oldByteArray[i + 10];

									if (((c1 == '/')) &&
										((c2 == 't') || (c2 == 'T')) &&
										((c3 == 'e') || (c3 == 'E')) &&
										((c4 == 'x') || (c4 == 'X')) &&
										((c5 == 't') || (c5 == 'T')) &&
										((c6 == 'a') || (c6 == 'A')) &&
										((c7 == 'r') || (c7 == 'R')) &&
										((c8 == 'e') || (c8 == 'E')) &&
										((c9 == 'a') || (c9 == 'A')) &&
										((c10 == '>'))) {

										ignore = false;
									}
								}
							}
						}

						if ((!ignore) &&
							((c == '\n') || (c == '\r') || (c == '\t'))) {

							if ((i + 1) == oldByteArray.length) {
							}

							if ((prevChar == '\n') || (prevChar == '\r')) {
							}
							else {
								if (c != '\t') {
									prevChar = c;
								}

								newByteArray[newByteArrayPos++] = b;
							}
						}
						else {
							prevChar = c;

							newByteArray[newByteArrayPos++] = b;
						}
					}
				}
				else {
					newByteArray = oldByteArray;
					newByteArrayPos = oldByteArray.length;
				}

				ServletResponseUtil.write(
					httpRes, newByteArray, newByteArrayPos);
			}
		}
		else {
			if (_log.isDebugEnabled()) {
				_log.debug("Not stripping " + completeURL);
			}

			doFilter(StripFilter.class, req, res, chain);
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

	protected boolean isStrip(HttpServletRequest req) {
		if (!ParamUtil.get(req, _STRIP, true)) {
			return false;
		}
		else {

			// The exclusive state is used to stream binary content.
			// Compressing binary content through a servlet filter is bad on
			// performance because the user will not start downloading the
			// content until the entire content is compressed.

			boolean action = ParamUtil.getBoolean(req, "p_p_action");
			String windowState = ParamUtil.getString(req, "p_p_state");

			if (action && windowState.equals("exclusive")) {
				return false;
			}
			else {
				return true;
			}
		}
	}

	private static final String _ALREADY_FILTERED =
		StripFilter.class.getName() + "_ALREADY_FILTERED";

	private static final String _STRIP = "strip";

	private static Log _log = LogFactoryUtil.getLog(StripFilter.class);

}