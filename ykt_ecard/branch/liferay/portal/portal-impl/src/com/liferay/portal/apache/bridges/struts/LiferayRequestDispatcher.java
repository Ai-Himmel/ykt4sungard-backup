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

package com.liferay.portal.apache.bridges.struts;

import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portlet.PortletServletRequest;
import com.liferay.portlet.PortletServletResponse;
import com.liferay.portlet.RenderRequestImpl;

import java.io.IOException;

import java.util.Iterator;
import java.util.List;

import javax.portlet.PortletResponse;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="LiferayRequestDispatcher.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 * @author Brian Myunghun Kim
 *
 */
public class LiferayRequestDispatcher implements RequestDispatcher {

	public LiferayRequestDispatcher(RequestDispatcher rd, String path) {
		_rd = rd;
		_path = path;
	}

	public void forward(ServletRequest req, ServletResponse res)
		throws IOException, ServletException {

		if (req.getAttribute(JavaConstants.JAVAX_PORTLET_REQUEST) != null) {
			invoke(req, res, false);
		}
		else {
			_rd.forward(req, res);
		}
	}

	public void include(ServletRequest req, ServletResponse res)
		throws IOException, ServletException {

		if (req.getAttribute(JavaConstants.JAVAX_PORTLET_REQUEST) != null) {
			invoke(req, res, true);
		}
		else {
			_rd.include(req, res);
		}
	}

	public void invoke(ServletRequest req, ServletResponse res, boolean include)
		throws IOException, ServletException {

		String pathInfo = null;
		String queryString = null;
		String requestURI = null;
		String servletPath = null;

		RenderRequestImpl renderReq = (RenderRequestImpl)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_REQUEST);

		PortletResponse portletRes = (PortletResponse)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_RESPONSE);

		if (_path != null) {
			String pathNoQueryString = _path;

			int pos = _path.indexOf(StringPool.QUESTION);

			if (pos != -1) {
				pathNoQueryString = _path.substring(0, pos);
				queryString = _path.substring(pos + 1, _path.length());
			}

			List servletURLPatterns =
				renderReq.getPortlet().getServletURLPatterns();

			Iterator itr = servletURLPatterns.iterator();

			while (itr.hasNext()) {
				String urlPattern = (String)itr.next();

				if (urlPattern.endsWith("/*")) {
					pos = urlPattern.indexOf("/*");

					urlPattern = urlPattern.substring(0, pos);

					if (pathNoQueryString.startsWith(urlPattern)) {
						pathInfo = pathNoQueryString.substring(
							urlPattern.length());
						servletPath = urlPattern;

						break;
					}
				}
			}

			if ((pathInfo == null) && (servletPath == null)) {
				pathInfo = StringPool.BLANK;
				servletPath = pathNoQueryString;
			}

			requestURI = renderReq.getContextPath() + pathNoQueryString;
		}

		PortletServletRequest portletServletReq = new PortletServletRequest(
			(HttpServletRequest)req, renderReq, pathInfo, queryString,
			requestURI, servletPath);

		PortletServletResponse portletServletRes =
			new PortletServletResponse((HttpServletResponse)res, portletRes);

		if (include) {
			_rd.include(portletServletReq, portletServletRes);
		}
		else {
			_rd.forward(portletServletReq, portletServletRes);
		}
	}

	private RequestDispatcher _rd;
	private String _path;

}