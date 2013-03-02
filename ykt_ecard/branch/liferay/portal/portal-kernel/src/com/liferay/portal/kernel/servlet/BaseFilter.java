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

package com.liferay.portal.kernel.servlet;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.StringPool;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;

/**
 * <a href="BaseFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public abstract class BaseFilter implements Filter {

	public void init(FilterConfig config) throws ServletException {
		_config = config;
	}

	public abstract void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException;

	public FilterConfig getFilterConfig() {
		return _config;
	}

	public void destroy() {
	}

	protected void doFilter(
			Class filterClass, ServletRequest req, ServletResponse res,
			FilterChain chain)
		throws IOException, ServletException {

		long startTime = 0;

		String threadName = null;
		String depther = null;
		String path = null;

		if (_log.isDebugEnabled()) {
			HttpServletRequest httpReq = (HttpServletRequest)req;

			startTime = System.currentTimeMillis();

			threadName = Thread.currentThread().getName();

			depther = (String)req.getAttribute(_DEPTHER);

			if (depther == null) {
				depther = StringPool.BLANK;
			}
			else {
				depther += StringPool.EQUAL;
			}

			req.setAttribute(_DEPTHER, depther);

			path = httpReq.getRequestURI();

			_log.debug(
				"[" + threadName + "]" + depther + "> " +
					filterClass.getName() + " " + path);
		}

		chain.doFilter(req, res);

		if (_log.isDebugEnabled()) {
			long endTime = System.currentTimeMillis();

			depther = (String)req.getAttribute(_DEPTHER);

			_log.debug(
				"[" + threadName + "]" + depther + "< " +
					filterClass.getName() + " " + path + " " +
						(endTime - startTime) + " ms");

			if (depther.length() > 0) {
				depther = depther.substring(1);
			}

			req.setAttribute(_DEPTHER, depther);
		}
	}

	private static final String _DEPTHER = "DEPTHER";

	private static Log _log = LogFactoryUtil.getLog(BaseFilter.class);

	private FilterConfig _config;

}