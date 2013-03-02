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

import com.ice.jcvslet.JCVSlet;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.ParamUtil;

import java.io.IOException;

import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="JCVSServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class JCVSServlet extends JCVSlet {

	public static final boolean JCVS_AVAILABLE = GetterUtil.getBoolean(
		PropsUtil.get(PropsUtil.JCVS_AVAILABLE));

	public void init(ServletConfig sc) throws ServletException {
		if (JCVS_AVAILABLE) {
			super.init(sc);
		}
	}

	public void doGet(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		String jcvsLicense = ParamUtil.getString(req, "jcvs_license");

		if (jcvsLicense.equals(PropsUtil.get(PropsUtil.JCVS_LICENSE))) {
			super.doGet(req, res);
		}
	}

	public void doPost(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		String jcvsLicense = ParamUtil.getString(req, "jcvs_license");

		if (jcvsLicense.equals(PropsUtil.get(PropsUtil.JCVS_LICENSE))) {
			super.doPost(req, res);
		}
	}

	public ServletContext getContext() {
		if (_ctx == null) {
			_ctx = new JCVSServletContext(super.getContext());
		}

		return _ctx;
	}

	public void log(String msg) {
		_log.info(msg);
	}

	public void log(String msg, Throwable throwable) {
		_log.info(msg, throwable);
	}

	public void destroy() {
		if (JCVS_AVAILABLE) {
			super.destroy();
		}
	}

	private static final Log _log = LogFactory.getLog(JCVSServlet.class);

	private ServletContext _ctx;

}