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

package com.liferay.taglib.portletext;

import com.liferay.portal.kernel.servlet.StringServletResponse;
import com.liferay.taglib.util.IncludeTag;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.JspException;

/**
 * <a href="PreviewTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PreviewTag extends IncludeTag {

	public static void doTag(
			String portletName, String queryString, String width,
			ServletContext ctx, HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		doTag(_PAGE, portletName, queryString, width, ctx, req, res);
	}

	public static void doTag(
			String page, String portletName, String queryString, String width,
			ServletContext ctx, HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		req.setAttribute("liferay-portlet:preview:portletName", portletName);
		req.setAttribute("liferay-portlet:preview:queryString", queryString);
		req.setAttribute("liferay-portlet:preview:width", width);

		RequestDispatcher rd = ctx.getRequestDispatcher(page);

		rd.include(req, res);
	}

	public int doEndTag() throws JspException {
		try {
			ServletContext ctx = getServletContext();
			HttpServletRequest req = getServletRequest();
			StringServletResponse res = getServletResponse();

			doTag(_portletName, _queryString, _width, ctx, req, res);

			pageContext.getOut().print(res.getString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

	public void setPortletName(String portletName) {
		_portletName = portletName;
	}

	public void setQueryString(String queryString) {
		_queryString = queryString;
	}

	public void setWidth(String width) {
		_width = width;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE = "/html/taglib/portlet/preview/page.jsp";

	private String _portletName;
	private String _queryString;
	private String _width;

}