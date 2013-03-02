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

package com.liferay.portlet.login.action;

import com.liferay.portal.CookieNotSupportedException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PasswordExpiredException;
import com.liferay.portal.UserEmailAddressException;
import com.liferay.portal.UserIdException;
import com.liferay.portal.UserLockoutException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.UserScreenNameException;
import com.liferay.portal.action.LoginAction;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.security.auth.AuthException;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

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

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		if (req.getRemoteUser() != null) {
			res.sendRedirect(themeDisplay.getPathMain());
		}
		else if (Validator.isNotNull(cmd)) {
			try {
				login(themeDisplay, req, res);
			}
			catch (Exception e) {
				if (e instanceof AuthException) {
					Throwable cause = e.getCause();

					if (cause instanceof PasswordExpiredException ||
						cause instanceof UserLockoutException) {

						SessionErrors.add(req, cause.getClass().getName());
					}
					else {
						SessionErrors.add(req, e.getClass().getName());
					}
				}
				else if (e instanceof CookieNotSupportedException ||
						 e instanceof NoSuchUserException ||
						 e instanceof PasswordExpiredException ||
						 e instanceof UserEmailAddressException ||
						 e instanceof UserIdException ||
						 e instanceof UserLockoutException ||
						 e instanceof UserPasswordException ||
						 e instanceof UserScreenNameException) {

					SessionErrors.add(req, e.getClass().getName());
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, ActionConstants.COMMON_ERROR);
				}
			}
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		return mapping.findForward("portlet.login.view");
	}

	protected void login(
			ThemeDisplay themeDisplay, ActionRequest req, ActionResponse res)
		throws Exception {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(res);

		String login = ParamUtil.getString(req, "login");
		String password = ParamUtil.getString(req, "password");
		boolean rememberMe = ParamUtil.getBoolean(req, "rememberMe");

		LoginAction.login(httpReq, httpRes, login, password, rememberMe);

		if (PropsValues.PORTAL_JAAS_ENABLE) {
			res.sendRedirect(themeDisplay.getPathMain() + "/portal/protected");
		}
		else {
			res.sendRedirect(themeDisplay.getPathMain());
		}
	}

}