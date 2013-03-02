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

package com.liferay.portal.struts;

import com.liferay.portal.util.CompanyPropsUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.BrowserSniffer;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="StrutsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.11 $
 *
 */
public class StrutsUtil {

	public static void forward(
			String uri, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res)
		throws ServletException {

		if (!res.isCommitted()) {
			String path = Constants.TEXT_HTML_DIR + uri;
			if (BrowserSniffer.is_wml(req)) {
				path = Constants.TEXT_WML_DIR + uri;
			}

			ServletContext portalCtx = _getPortalCtx(ctx, req);

			RequestDispatcher rd = portalCtx.getRequestDispatcher(path);

			try {
				rd.forward(req, res);
			}
			catch (IOException ioe1) {
				ioe1.printStackTrace();
			}
			catch (ServletException se1) {
				req.setAttribute(PageContext.EXCEPTION, se1.getRootCause());

				String errorPath =
					Constants.TEXT_HTML_DIR + Constants.COMMON_ERROR;
				if (BrowserSniffer.is_wml(req)) {
					path = Constants.TEXT_WML_DIR + Constants.COMMON_ERROR;
				}

				rd = portalCtx.getRequestDispatcher(errorPath);

				try {
					rd.forward(req, res);
				}
				catch (IOException ioe2) {
					ioe2.printStackTrace();
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

		String path = Constants.TEXT_HTML_DIR + uri;
		if (BrowserSniffer.is_wml(req)) {
			path = Constants.TEXT_WML_DIR + uri;
		}

		ServletContext portalCtx = _getPortalCtx(ctx, req);

		RequestDispatcher rd = portalCtx.getRequestDispatcher(path);

		try {
			rd.include(req, res);
		}
		catch (IOException ioe) {
		}
	}

	private static ServletContext _getPortalCtx(
			ServletContext ctx, HttpServletRequest req) {
        String companyId = PortalUtil.getCompanyId(req);

		ServletContext portalCtx = ctx.getContext(
			CompanyPropsUtil.get(companyId, PropsUtil.PORTAL_CTX));
		if (portalCtx == null) {
			portalCtx = ctx;
		}

		return portalCtx;
	}

	private static final Log _log = LogFactory.getLog(StrutsUtil.class);

}