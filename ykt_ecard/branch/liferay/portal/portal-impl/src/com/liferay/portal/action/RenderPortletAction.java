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

package com.liferay.portal.action;

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;

import javax.portlet.WindowState;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="RenderPortletAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RenderPortletAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		ServletContext ctx = (ServletContext)req.getAttribute(WebKeys.CTX);

		String ajaxId = req.getParameter("ajax_id");

		long companyId = PortalUtil.getCompanyId(req);
		User user = PortalUtil.getUser(req);
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);
		String portletId = ParamUtil.getString(req, "p_p_id");

		Portlet portlet = PortletLocalServiceUtil.getPortletById(
			companyId, portletId);

		String queryString = null;
		String columnId = ParamUtil.getString(req, "p_p_col_id");
		int columnPos = ParamUtil.getInteger(req, "p_p_col_pos");
		int columnCount = ParamUtil.getInteger(req, "p_p_col_count");
		boolean staticPortlet = ParamUtil.getBoolean(req, "p_p_static");
		boolean staticStartPortlet = ParamUtil.getBoolean(
			req, "p_p_static_start");

		if (staticPortlet) {
			portlet = (Portlet)portlet.clone();

			portlet.setStatic(true);
			portlet.setStaticStart(staticStartPortlet);
		}

		if (ajaxId != null) {
			res.setHeader("Ajax-ID", ajaxId);
		}

		WindowState windowState = new WindowState(
			ParamUtil.getString(req, "p_p_state"));

		PortalUtil.updateWindowState(
			portletId, user, layout, windowState, req);

		PortalUtil.renderPortlet(
			null, ctx, req, res, portlet, queryString, columnId,
			new Integer(columnPos), new Integer(columnCount));

		return null;
	}

}