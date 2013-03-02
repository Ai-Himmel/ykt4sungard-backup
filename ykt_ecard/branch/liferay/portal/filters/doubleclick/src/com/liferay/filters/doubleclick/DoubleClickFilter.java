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

package com.liferay.filters.doubleclick;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.servlet.BaseFilter;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.util.Http;
import com.liferay.util.SystemProperties;

import java.io.IOException;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.lang.time.StopWatch;

/**
 * <a href="DoubleClickFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Olaf Fricke
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class DoubleClickFilter extends BaseFilter {

	public static final boolean USE_FILTER = GetterUtil.getBoolean(
		SystemProperties.get(DoubleClickFilter.class.getName()), true);

	public static final String ENCODING = GetterUtil.getString(
		SystemProperties.get("file.encoding"), "UTF-8");

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		if (_log.isDebugEnabled()) {
			if (USE_FILTER) {
				_log.debug("Double click prevention is enabled");
			}
			else {
				_log.debug("Double click prevention is disabled");
			}
		}

		if (USE_FILTER) {
			HttpServletRequest httpReq = (HttpServletRequest)req;
			HttpServletResponse httpRes = (HttpServletResponse)res;

			StopWatch stopWatch = null;

			if (_log.isDebugEnabled()) {
				stopWatch = new StopWatch();

				stopWatch.start();
			}

			HttpSession ses = httpReq.getSession(false);

			if (ses == null) {
				doFilter(DoubleClickFilter.class, req, res, chain);
			}
			else {
				DoubleClickController controller = null;

				synchronized (ses) {
					controller = (DoubleClickController)ses.getAttribute(
						_CONTROLLER_KEY);

					if (controller == null) {
						controller = new DoubleClickController();

						ses.setAttribute(_CONTROLLER_KEY, controller);
					}
				}

				boolean ok = false;

				try {
					controller.control(httpReq, httpRes, chain);

					ok = true;
				}
				finally {
					if (_log.isDebugEnabled()) {
						String completeURL = Http.getCompleteURL(httpReq);

						if (ok) {
							_log.debug(
								"Double click prevention succeded in " +
									stopWatch.getTime() + " ms for " +
										completeURL);
						}
						else {
							_log.debug(
								"Double click prevention failed in " +
									stopWatch.getTime() + " ms for " +
										completeURL);
						}
					}
				}
			}
		}
		else {
			doFilter(DoubleClickFilter.class, req, res, chain);
		}
	}

	private static final String _CONTROLLER_KEY =
		DoubleClickFilter.class.getName();

	private static Log _log = LogFactoryUtil.getLog(DoubleClickFilter.class);

}