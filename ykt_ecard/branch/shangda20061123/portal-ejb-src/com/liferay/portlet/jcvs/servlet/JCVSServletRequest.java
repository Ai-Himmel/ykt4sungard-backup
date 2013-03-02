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

package com.liferay.portlet.jcvs.servlet;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.StringPool;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletRequestWrapper;

/**
 * <a href="JCVSServletRequest.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class JCVSServletRequest extends HttpServletRequestWrapper {

	public JCVSServletRequest(HttpServletRequest req, String servletPath,
							  String pathInfo) {

		super(req);

		_servletPath = servletPath;
		_pathInfo = pathInfo;
	}

	public String getContextPath() {
		return StringPool.BLANK;
	}

	public String getParameter(String name) {
		if (name != null && name.equals("jcvs_license")) {
			return PropsUtil.get(PropsUtil.JCVS_LICENSE);
		}
		else {
			return super.getParameter(name);
		}
	}

	public String getPathInfo() {
		return _pathInfo;
	}

	public String getServletPath() {
		return _servletPath;
	}

	private String _servletPath;
	private String _pathInfo;

}