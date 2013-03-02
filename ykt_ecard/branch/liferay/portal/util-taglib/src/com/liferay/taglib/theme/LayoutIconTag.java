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

package com.liferay.taglib.theme;

import com.liferay.portal.model.Layout;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="LayoutIconTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutIconTag extends com.liferay.taglib.util.IncludeTag {

	public static void doTag(
			Layout layout, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res)
		throws IOException, ServletException {

		doTag(_PAGE, layout, ctx, req, res);
	}

	public static void doTag(
			String page, Layout layout, ServletContext ctx,
			HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		setRequestAttributes(req, layout);

		RequestDispatcher rd = ctx.getRequestDispatcher(page);

		rd.include(req, res);
	}

	public static void setRequestAttributes(ServletRequest req, Layout layout) {
		req.setAttribute("liferay-theme:layout-icon:layout", layout);
	}

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		setRequestAttributes(req, _layout);

		return EVAL_BODY_BUFFERED;
	}

	public void setLayout(Layout layout) {
		_layout = layout;
	}

	public String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE =
		"/html/taglib/theme/layout_icon/page.jsp";

	private Layout _layout;

}