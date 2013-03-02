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

package com.liferay.portal.servlet.taglib.security;

import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.theme.PortletDisplay;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletURLImpl;

import javax.portlet.PortletURL;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.PageContext;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="PermissionsURLTagUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionsURLTagUtil extends TagSupport {

	public static String doEndTag(
			String redirect, String modelResource,
			String modelResourceDescription, String resourcePrimKey, String var,
			boolean writeOutput, PageContext pageContext)
		throws JspException {

		try {
			HttpServletRequest req =
				(HttpServletRequest)pageContext.getRequest();

			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			PortletDisplay portletDisplay = themeDisplay.getPortletDisplay();

			Layout layout = themeDisplay.getLayout();

			if (Validator.isNull(redirect)) {
				redirect = PortalUtil.getCurrentURL(req);
			}

			PortletURL portletURL = new PortletURLImpl(
				req, PortletKeys.PORTLET_CONFIGURATION, layout.getPlid(),
				false);

			if (themeDisplay.isStatePopUp()) {
				portletURL.setWindowState(LiferayWindowState.POP_UP);
			}
			else {
				portletURL.setWindowState(WindowState.MAXIMIZED);
			}

			portletURL.setParameter(
				"struts_action", "/portlet_configuration/edit_permissions");
			portletURL.setParameter("redirect", redirect);

			if (!themeDisplay.isStateMaximized()) {
				portletURL.setParameter("returnToFullPageURL", redirect);
			}

			portletURL.setParameter("portletResource", portletDisplay.getId());
			portletURL.setParameter("modelResource", modelResource);
			portletURL.setParameter(
				"modelResourceDescription", modelResourceDescription);
			portletURL.setParameter("resourcePrimKey", resourcePrimKey);

			String portletURLToString = portletURL.toString();

			if (Validator.isNotNull(var)) {
				pageContext.setAttribute(var, portletURLToString);
			}
			else if (writeOutput) {
				pageContext.getOut().print(portletURLToString);
			}

			return portletURL.toString();
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

}