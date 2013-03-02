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

import com.liferay.portal.kernel.servlet.StringServletResponse;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Theme;
import com.liferay.portal.theme.PortletDisplay;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.taglib.util.ParamAncestorTagImpl;
import com.liferay.taglib.util.ThemeUtil;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.PageContext;

/**
 * <a href="WrapPortletTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WrapPortletTag extends ParamAncestorTagImpl {

	public static String doTag(
			String wrapPage, String portletPage, ServletContext ctx,
			HttpServletRequest req, StringServletResponse res,
			PageContext pageContext)
		throws Exception {

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		Theme theme = themeDisplay.getTheme();
		PortletDisplay portletDisplay = themeDisplay.getPortletDisplay();

		// Portlet content

		RequestDispatcher rd = ctx.getRequestDispatcher(portletPage);

		rd.include(req, res);

		portletDisplay.setContent(res.getString());

		// Page

		res.recycle();

		return ThemeUtil.includeVM(
			ctx, req, pageContext, wrapPage, theme, false);
	}

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

			ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
				WebKeys.THEME_DISPLAY);

			Theme theme = themeDisplay.getTheme();
			PortletDisplay portletDisplay = themeDisplay.getPortletDisplay();

			// Portlet content

			portletDisplay.setContent(_bodyContentString);

			// Page

			ThemeUtil.include(ctx, req, res, pageContext, getPage(), theme);

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

	public String getPage() {
		return _page;
	}

	public void setPage(String page) {
		_page = page;
	}

	private String _page;
	private String _bodyContentString = StringPool.BLANK;

}