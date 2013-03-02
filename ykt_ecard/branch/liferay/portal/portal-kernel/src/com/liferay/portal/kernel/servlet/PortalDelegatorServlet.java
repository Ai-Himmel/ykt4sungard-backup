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

import com.liferay.portal.kernel.util.StringPool;

import java.io.IOException;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="PortalDelegatorServlet.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * See http://support.liferay.com/browse/LEP-2297.
 * </p>
 *
 * @author Olaf Fricke
 * @author Brian Wing Shun Chan
 *
 */
public class PortalDelegatorServlet extends HttpServlet {

	public static void addDelegate(String subContext, HttpServlet delegate) {
		if (subContext == null) {
			throw new IllegalArgumentException();
		}

		if (delegate == null) {
			throw new IllegalArgumentException();
		}

		_delegates.put(subContext, delegate);
	}

	public static void removeDelegate(String subContext) {
		if (subContext == null) {
			throw new IllegalArgumentException();
		}

		_delegates.remove(subContext);
	}

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		String uri = req.getPathInfo();

		if ((uri == null) || (uri.length() == 0)) {
			throw new ServletException("Path information is not specified");
		}

		String[] paths = uri.split(StringPool.SLASH);

		if (paths.length < 2) {
			throw new ServletException("Path " + uri + " is invalid");
		}

		HttpServlet delegate = (HttpServlet)_delegates.get(paths[1]);

		if (delegate == null) {
			throw new ServletException(
				"No servlet registred for context " + paths[1]);
		}

		ClassLoader contextClassLoader =
			Thread.currentThread().getContextClassLoader();

		try {
			ClassLoader delegateClassLoader =
				delegate.getClass().getClassLoader();

			Thread.currentThread().setContextClassLoader(delegateClassLoader);

			delegate.service(req, res);
		}
		finally {
			Thread.currentThread().setContextClassLoader(contextClassLoader);
		}
	}

	private static Map _delegates = new HashMap();

}