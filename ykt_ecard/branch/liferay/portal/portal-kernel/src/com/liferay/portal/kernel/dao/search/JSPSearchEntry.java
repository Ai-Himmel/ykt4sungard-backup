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

package com.liferay.portal.kernel.dao.search;

import com.liferay.portal.kernel.servlet.StringServletResponse;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

/**
 * <a href="JSPSearchEntry.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JSPSearchEntry extends SearchEntry {

	public JSPSearchEntry(String align, String valign, String path) {
		this(align, valign, DEFAULT_COLSPAN, path, null, null, null);
	}

	public JSPSearchEntry(
		String align, String valign, int colspan, String path) {

		this(align, valign, colspan, path, null, null, null);
	}

	public JSPSearchEntry(
		String align, String valign, int colspan, String path,
		ServletContext ctx, HttpServletRequest req, HttpServletResponse res) {

		super(align, valign, colspan);

		_path = path;
		_ctx = ctx;
		_req = req;
		_res = res;
	}

	public String getPath() {
		return _path;
	}

	public void setPath(String path) {
		_path = path;
	}

	public void print(PageContext pageContext) throws Exception {
		if (_ctx != null) {
			RequestDispatcher rd = _ctx.getRequestDispatcher(_path);

			StringServletResponse stringServletRes =
				new StringServletResponse(_res);

			rd.include(_req, stringServletRes);

			pageContext.getOut().print(stringServletRes.getString());
		}
		else {
			pageContext.include(_path);
		}
	}

	public Object clone() {
		return new JSPSearchEntry(
			getAlign(), getValign(), getColspan(), getPath());
	}

	private String _path;
	private ServletContext _ctx;
	private HttpServletRequest _req;
	private HttpServletResponse _res;

}