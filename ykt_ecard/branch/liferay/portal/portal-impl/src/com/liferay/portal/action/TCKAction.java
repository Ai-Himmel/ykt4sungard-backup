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

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="TCKAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TCKAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			if (!PropsValues.TCK_URL) {
				throw new PrincipalException();
			}

			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			String[] portletIds = req.getParameterValues("portletId");

			if (portletIds == null) {
				portletIds = req.getParameterValues("portletName");
			}

			for (int i = 0; i < portletIds.length; i++) {
				String[] nameAndWar = StringUtil.split(portletIds[i], "/");

				portletIds[i] = PortalUtil.getJsSafePortletId(
					nameAndWar[1] + PortletImpl.WAR_SEPARATOR + nameAndWar[0]);
			}

			// Default admin

			long userId = 2;

			// Guest group

			long groupId = 14;

			Layout layout = LayoutLocalServiceUtil.addLayout(
				userId, groupId, false, LayoutImpl.DEFAULT_PARENT_LAYOUT_ID,
				"TCKAction", StringPool.BLANK, StringPool.BLANK,
				LayoutImpl.TYPE_PORTLET, false, StringPool.BLANK);

			LayoutTypePortlet layoutType =
				(LayoutTypePortlet)layout.getLayoutType();

			for (int i = 0; i < portletIds.length; i++) {
				layoutType.addPortletId(userId, portletIds[i]);
			}

			LayoutLocalServiceUtil.updateLayout(
				layout.getGroupId(), layout.isPrivateLayout(),
				layout.getLayoutId(), layout.getTypeSettings());

			req.setAttribute(
				WebKeys.FORWARD_URL,
				themeDisplay.getPathMain() + "/portal/layout?p_l_id=" +
					layout.getPlid());

			return mapping.findForward(ActionConstants.COMMON_FORWARD_JSP);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

}