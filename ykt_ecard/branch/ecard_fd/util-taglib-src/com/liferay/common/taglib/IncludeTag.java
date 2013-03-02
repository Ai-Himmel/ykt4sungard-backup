/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.common.taglib;

import com.liferay.common.taglib.util.ThemeUtil;
import com.liferay.portal.model.Theme;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.StringServletResponse;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspTagException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="IncludeTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class IncludeTag extends ParamAncestorTagImpl {

	public int doEndTag() throws JspTagException {
		try {
			ServletContext ctx = getServletContext();
			ServletRequest req = getServletRequest();
			StringServletResponse res = getServletResponse();

			Theme theme = (Theme)req.getAttribute(WebKeys.THEME);

			if (isTheme()) {
				ThemeUtil.include(ctx, req, res, pageContext, _page, theme);
			}
			else {
				RequestDispatcher rd = ctx.getRequestDispatcher(_page);

				rd.include(req, res);
			}

			pageContext.getOut().print(res.getString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			e.printStackTrace();

			throw new JspTagException(e.getMessage());
		}
		finally {
			clearParams();
		}
    }

	public boolean isTheme() {
		return false;
	}

	public void setPage(String page) {
		_page = page;
	}

	public void setFlush(boolean flush) {
		_flush = flush;
	}

	private static final Log _log = LogFactory.getLog(IncludeTag.class);

	private String _page;
	private boolean _flush;

}