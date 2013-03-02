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

package com.liferay.taglib.ui;

import com.liferay.portal.kernel.servlet.StringServletResponse;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Theme;
import com.liferay.portal.util.WebKeys;
import com.liferay.taglib.util.ParamAncestorTagImpl;
import com.liferay.taglib.util.ThemeUtil;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspException;

/**
 * <a href="BoxTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BoxTag extends ParamAncestorTagImpl {

	public int doStartTag() {
		return EVAL_BODY_BUFFERED;
	}

	public int doAfterBody() {
		_bodyContentString = getBodyContent().getString();

		return SKIP_BODY;
	}

	public int doEndTag() throws JspException {
		try {
			ServletContext ctx = getServletContext();
			HttpServletRequest req = getServletRequest();
			StringServletResponse res = getServletResponse();

			Theme theme = (Theme)req.getAttribute(WebKeys.THEME);

			// Top

			if (isTheme()) {
				ThemeUtil.include(ctx, req, res, pageContext, getTop(), theme);
			}
			else {
				RequestDispatcher rd = ctx.getRequestDispatcher(getTop());

				rd.include(req, res);
			}

			pageContext.getOut().print(res.getString());

			// Body

			pageContext.getOut().print(_bodyContentString);

			// Bottom

			//res = getServletResponse();
			res.recycle();

			if (isTheme()) {
				ThemeUtil.include(
					ctx, req, res, pageContext, getBottom(), theme);
			}
			else {
				RequestDispatcher rd = ctx.getRequestDispatcher(getBottom());

				rd.include(req, res);
			}

			pageContext.getOut().print(res.getString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspException(e);
		}
		finally {
			clearParams();
		}
	}

	public boolean isTheme() {
		return false;
	}

	public String getTop() {
		return _top;
	}

	public void setTop(String top) {
		_top = top;
	}

	public String getBottom() {
		return _bottom;
	}

	public void setBottom(String bottom) {
		_bottom = bottom;
	}

	private String _top;
	private String _bottom;
	private String _bodyContentString = StringPool.BLANK;

}