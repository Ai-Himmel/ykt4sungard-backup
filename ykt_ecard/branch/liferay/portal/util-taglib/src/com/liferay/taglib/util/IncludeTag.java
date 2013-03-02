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

package com.liferay.taglib.util;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.log.LogUtil;
import com.liferay.portal.kernel.servlet.StringServletResponse;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Theme;
import com.liferay.portal.util.WebKeys;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspException;

/**
 * <a href="IncludeTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class IncludeTag extends ParamAncestorTagImpl {

	public int doEndTag() throws JspException {
		HttpServletRequest req = null;

		try {
			ServletContext ctx = getServletContext();
			req = getServletRequest();
			StringServletResponse res = getServletResponse();

			Theme theme = (Theme)req.getAttribute(WebKeys.THEME);

			String page = getPage();

			if (isTheme()) {
				ThemeUtil.include(ctx, req, res, pageContext, page, theme);
			}
			else {
				RequestDispatcher rd = ctx.getRequestDispatcher(page);

				rd.include(req, res);
			}

			pageContext.getOut().print(res.getString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			if (req != null) {
				String currentURL = (String)req.getAttribute(
					WebKeys.CURRENT_URL);

				_log.error(
					"Current URL " + currentURL + " generates exception: " +
						e.getMessage());
			}

			LogUtil.log(_log, e);

			return EVAL_PAGE;
		}
		finally {
			clearParams();
		}
	}

	public boolean isTheme() {
		return false;
	}

	public String getPage() {
		if (Validator.isNull(_page)) {
			return getDefaultPage();
		}
		else {
			return _page;
		}
	}

	public void setPage(String page) {
		_page = page;
	}

	protected String getDefaultPage() {
		return null;
	}

	private static Log _log = LogFactoryUtil.getLog(IncludeTag.class);

	private String _page;

}