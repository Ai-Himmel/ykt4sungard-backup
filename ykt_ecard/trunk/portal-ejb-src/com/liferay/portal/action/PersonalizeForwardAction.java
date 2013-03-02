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

package com.liferay.portal.action;

import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.spring.GroupServiceUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletURLImpl;
import com.liferay.util.ParamUtil;

import java.util.List;

import javax.portlet.PortletMode;
import javax.portlet.PortletURL;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="PersonalizeForwardAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.21 $
 *
 */
public class PersonalizeForwardAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			String groupId = ParamUtil.getString(req, "group_id");

			String forwardURL = null;

			if (groupId.equals(Group.DEFAULT_PARENT_GROUP_ID)) {
				String mainPath = (String)req.getAttribute(WebKeys.MAIN_PATH);

				forwardURL = mainPath + "/portal/personalize";
			}
			else {
				String layoutId = Layout.DEFAULT_LAYOUT_ID;

				List layouts = GroupServiceUtil.getLayouts(
					groupId, Layout.DEFAULT_PARENT_LAYOUT_ID);

				if (layouts.size() > 0) {
					Layout layout = (Layout)layouts.get(0);

					layoutId = layout.getLayoutId();
				}

				PortletURL portlerURL = new PortletURLImpl(
					req, PortletKeys.ADMIN, layoutId, true);

				portlerURL.setWindowState(WindowState.MAXIMIZED);
				portlerURL.setPortletMode(PortletMode.VIEW);

				portlerURL.setParameter(
					"struts_action", "/admin/edit_group_pages");

				forwardURL = portlerURL.toString() + "&group_id=" + groupId;
			}

			req.setAttribute(WebKeys.FORWARD_URL, forwardURL);

			return mapping.findForward(Constants.COMMON_FORWARD);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}