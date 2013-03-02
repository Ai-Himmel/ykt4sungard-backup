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

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.LayoutServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.PortletURLImpl;

import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletMode;
import javax.portlet.PortletURL;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditPagesAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditPagesAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		long groupId = ParamUtil.getLong(req, "groupId");
		boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");

		Layout layout = null;

		List layouts = LayoutLocalServiceUtil.getLayouts(
			groupId, privateLayout, LayoutImpl.DEFAULT_PARENT_LAYOUT_ID, 0, 1);

		if (layouts.size() > 0) {
			layout = (Layout)layouts.get(0);
		}
		else {
			long parentLayoutId = LayoutImpl.DEFAULT_PARENT_LAYOUT_ID;
			String name = "New Page";
			String title = StringPool.BLANK;
			String description = StringPool.BLANK;
			String type = LayoutImpl.TYPE_PORTLET;
			boolean hidden = false;
			String friendlyURL = StringPool.BLANK;

			layout = LayoutServiceUtil.addLayout(
				groupId, privateLayout, parentLayoutId, name, title,
				description, type, hidden, friendlyURL);
		}

		if (layout != null) {
			String tabs2 = "public";

			if (privateLayout) {
				tabs2 = "private";
			}

			HttpServletRequest httReq = PortalUtil.getHttpServletRequest(req);

			PortletURL portletURL = new PortletURLImpl(
				httReq, PortletKeys.LAYOUT_MANAGEMENT, layout.getPlid(), false);

			portletURL.setWindowState(WindowState.MAXIMIZED);
			portletURL.setPortletMode(PortletMode.VIEW);

			portletURL.setParameter(
				"struts_action", "/layout_management/edit_pages");
			portletURL.setParameter("tabs2", tabs2);
			portletURL.setParameter("groupId", String.valueOf(groupId));

			res.sendRedirect(portletURL.toString());
		}
	}

}