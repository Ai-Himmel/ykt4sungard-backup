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

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

/**
 * <a href="PortalDelegateServlet.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * See http://support.liferay.com/browse/LEP-2297.
 * </p>
 *
 * @author Olaf Fricke
 * @author Brian Wing Shun Chan
 *
 */
public class PortalDelegateServlet extends HttpServlet {

	public void init(ServletConfig config) throws ServletException {
        String servletClass = config.getInitParameter("servlet-class");

		_subContext = config.getInitParameter("sub-context");

		if (_subContext == null) {
            _subContext = getServletName();
        }

		try {
            ClassLoader contextClassLoader =
				Thread.currentThread().getContextClassLoader();

			HttpServlet servlet = (HttpServlet)contextClassLoader.loadClass(
				servletClass).newInstance();

			servlet.init(config);

			PortalDelegatorServlet.addDelegate(_subContext, servlet);
        }
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public void destroy() {
		PortalDelegatorServlet.removeDelegate(_subContext);
	}

	private static Log _log =
		LogFactoryUtil.getLog(PortalDelegateServlet.class);

	private String _subContext;

}