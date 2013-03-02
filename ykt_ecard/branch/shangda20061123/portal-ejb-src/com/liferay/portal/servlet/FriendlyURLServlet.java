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

package com.liferay.portal.servlet;

import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.LayoutLocalServiceUtil;
import com.liferay.portal.struts.LastPath;
import com.liferay.portal.util.CompanyPropsUtil;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="FriendlyURLServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.16 $
 *
 */
public class FriendlyURLServlet extends HttpServlet {

	public void init(ServletConfig sc) throws ServletException {
		synchronized (FriendlyURLServlet.class) {
			super.init(sc);

			ServletContext ctx = getServletContext();

			_companyId = ctx.getInitParameter("company_id");
		}
	}

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {
		/*Support utf-8 encoding */
		String strutsCharEncoding =
			PropsUtil.get(PropsUtil.STRUTS_CHAR_ENCODING);
		req.setCharacterEncoding(strutsCharEncoding);
		/**/
		if (!PortalInstances.matches()) {
			return;
		}

		ServletContext ctx = getServletContext();
		
		String mainPath = (String)ctx.getAttribute(WebKeys.MAIN_PATH);
		String friendlyURLPath =
			(String)ctx.getAttribute(WebKeys.FRIENDLY_URL_PATH);

		String redirect = mainPath;

		try {
			redirect = _getRedirect(req.getPathInfo(), mainPath);

			LastPath lastPath = new LastPath(
				friendlyURLPath, req.getPathInfo(), req.getParameterMap());

			req.setAttribute(WebKeys.LAST_PATH, lastPath);
		}
		catch (Exception e) {
			_log.warn(e);
		}

		if (Validator.isNull(redirect)) {
			return;
		}

		//res.sendRedirect(redirect);
		
		if (redirect.startsWith(StringPool.SLASH)) {
			RequestDispatcher rd = ctx.getRequestDispatcher(redirect);

			if (rd != null) {
				rd.forward(req, res);
			}
		}
		else {
			res.sendRedirect(redirect);
		}
	}

	private String _getRedirect(String path, String mainPath) throws Exception {
		if (Validator.isNull(path)) {
			return mainPath;
		}

		if (!path.startsWith(StringPool.SLASH)) {
			return mainPath;
		}

		// Group path

		String groupFriendlyUrl = null;

		int pos = path.indexOf(StringPool.SLASH, 1);

		if (pos != -1) {
			groupFriendlyUrl = path.substring(0, pos);
		}
		else {
			if (path.length() > 1) {
				groupFriendlyUrl = path.substring(0, path.length());
			}
		}

		if (Validator.isNull(groupFriendlyUrl)) {
			return mainPath;
		}

		Group group = GroupLocalServiceUtil.getGroupByFriendlyURL(
			_companyId, groupFriendlyUrl);

		// Layout path

		String layoutFriendlyURL = null;

		if ((pos != -1) && ((pos + 1) != path.length())) {
			layoutFriendlyURL = path.substring(pos, path.length());
		}

		Layout layout = LayoutLocalServiceUtil.getLayoutByFriendlyURL(
			group.getGroupId(), layoutFriendlyURL);

		return PortalUtil.getLayoutActualURL(layout, mainPath);
	}

	private static final Log _log = LogFactory.getLog(FriendlyURLServlet.class);

	private String _companyId;

}