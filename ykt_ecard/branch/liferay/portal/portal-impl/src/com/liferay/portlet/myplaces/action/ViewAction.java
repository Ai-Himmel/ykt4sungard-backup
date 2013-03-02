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

package com.liferay.portlet.myplaces.action;

import com.liferay.portal.NoSuchLayoutSetException;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;

import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ViewAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ViewAction extends PortletAction {

	public ActionForward strutsExecute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long groupId = ParamUtil.getLong(req, "groupId");
		boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");

		List layouts = LayoutLocalServiceUtil.getLayouts(
			groupId, privateLayout, LayoutImpl.DEFAULT_PARENT_LAYOUT_ID, 0, 1);

		String redirect = themeDisplay.getPathMain();

		if (layouts.size() > 0) {
			Layout layout = (Layout)layouts.get(0);

			redirect = PortalUtil.getLayoutURL(layout, themeDisplay);
		}
		else {
			redirect = ParamUtil.getString(req, "redirect");

			SessionErrors.add(
				req, NoSuchLayoutSetException.class.getName(),
				new NoSuchLayoutSetException(
					"{groupId=" + groupId + ",privateLayout=" + privateLayout +
						"}"));
		}

		// Send redirect

		res.sendRedirect(redirect);

		return null;
	}

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long groupId = ParamUtil.getLong(req, "groupId");
		boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");

		List layouts = LayoutLocalServiceUtil.getLayouts(
			groupId, privateLayout, LayoutImpl.DEFAULT_PARENT_LAYOUT_ID, 0, 1);

		String redirect = themeDisplay.getPathMain();

		if (layouts.size() > 0) {
			Layout layout = (Layout)layouts.get(0);

			redirect = PortalUtil.getLayoutURL(layout, themeDisplay);
		}
		else {
			redirect = ParamUtil.getString(req, "redirect");

			SessionErrors.add(
				req, NoSuchLayoutSetException.class.getName(),
				new NoSuchLayoutSetException(
					"{groupId=" + groupId + ",privateLayout=" + privateLayout +
						"}"));
		}

		// Send redirect

		res.sendRedirect(redirect);
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		return mapping.findForward("portlet.my_places.view");
	}

	protected boolean isCheckMethodOnProcessAction() {
		return _CHECK_METHOD_ON_PROCESS_ACTION;
	}

	private static final boolean _CHECK_METHOD_ON_PROCESS_ACTION = false;

}