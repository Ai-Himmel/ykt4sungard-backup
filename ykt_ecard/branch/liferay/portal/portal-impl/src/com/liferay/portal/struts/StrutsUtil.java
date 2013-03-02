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

package com.liferay.portal.struts;

import com.liferay.portal.kernel.servlet.BrowserSniffer;

import java.io.IOException;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import javax.portlet.PortletContext;
import javax.portlet.PortletRequest;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;

/**
 * <a href="StrutsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class StrutsUtil {

	public static final String STRUTS_PACKAGE = "org.apache.struts.";

	public static final String TEXT_HTML_DIR = "/html";

	public static final String TEXT_WAP_DIR = "/wap";

	public static void forward(
			String uri, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res)
		throws ServletException {

		if (_log.isDebugEnabled()) {
			_log.debug("Forward URI " + uri);
		}

		if (uri.equals(ActionConstants.COMMON_NULL)) {
			return;
		}

		if (!res.isCommitted()) {
			String path = TEXT_HTML_DIR + uri;

			if (BrowserSniffer.is_wap_xhtml(req)) {
				path = TEXT_WAP_DIR + uri;
			}

			if (_log.isDebugEnabled()) {
				_log.debug("Forward path " + path);
			}

			RequestDispatcher rd = ctx.getRequestDispatcher(path);

			try {
				rd.forward(req, res);
			}
			catch (IOException ioe1) {
				_log.warn(ioe1, ioe1);
			}
			catch (ServletException se1) {
				req.setAttribute(PageContext.EXCEPTION, se1.getRootCause());

				String errorPath = TEXT_HTML_DIR + ActionConstants.COMMON_ERROR;

				if (BrowserSniffer.is_wap_xhtml(req)) {
					path = TEXT_WAP_DIR + ActionConstants.COMMON_ERROR;
				}

				rd = ctx.getRequestDispatcher(errorPath);

				try {
					rd.forward(req, res);
				}
				catch (IOException ioe2) {
					_log.warn(ioe2, ioe2);
				}
				catch (ServletException se2) {
					throw se2;
				}
			}
		}
		else {
			_log.warn(uri + " is already committed");
		}
	}

	public static void include(
			String uri, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res)
		throws ServletException {

		if (_log.isDebugEnabled()) {
			_log.debug("Include URI " + uri);
		}

		String path = TEXT_HTML_DIR + uri;

		if (BrowserSniffer.is_wap_xhtml(req)) {
			path = TEXT_WAP_DIR + uri;
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Include path " + path);
		}

		RequestDispatcher rd = ctx.getRequestDispatcher(path);

		try {
			rd.include(req, res);
		}
		catch (IOException ioe) {
			_log.warn(ioe, ioe);
		}
	}

	public static Map removeStrutsAttributes(
		PortletContext portletContext, PortletRequest req) {

		Map strutsAttributes = new HashMap();

		Enumeration enu = req.getAttributeNames();

		while (enu.hasMoreElements()) {
			String attributeName = (String)enu.nextElement();

			if (attributeName.startsWith(STRUTS_PACKAGE)) {
				strutsAttributes.put(
					attributeName, req.getAttribute(attributeName));
			}
		}

		Iterator itr = strutsAttributes.keySet().iterator();

		while (itr.hasNext()) {
			String attributeName = (String)itr.next();

			req.setAttribute(attributeName, null);
		}

		Object moduleConfig = portletContext.getAttribute(Globals.MODULE_KEY);

		req.setAttribute(Globals.MODULE_KEY, moduleConfig);

		return strutsAttributes;
	}

	public static void setStrutsAttributes(
		PortletRequest req, Map strutsAttributes) {

		Iterator itr = strutsAttributes.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			Object value = entry.getValue();

			req.setAttribute(key, value);
		}
	}

	private static Log _log = LogFactory.getLog(StrutsUtil.class);

}