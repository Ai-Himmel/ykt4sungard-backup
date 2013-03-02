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

package com.liferay.portal.struts;

import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletConfigImpl;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import java.io.IOException;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletRequest;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.config.ModuleConfig;
import org.apache.struts.util.MessageResources;

/**
 * <a href="PortletAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletAction extends Action {

	public static String getForwardKey(HttpServletRequest req) {
		PortletConfigImpl portletConfig = (PortletConfigImpl)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		return PortalUtil.getPortletNamespace(portletConfig.getPortletId()) +
			WebKeys.PORTLET_STRUTS_FORWARD;
	}

	public static String getForwardKey(PortletRequest req) {
		PortletConfigImpl portletConfig = (PortletConfigImpl)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		return PortalUtil.getPortletNamespace(portletConfig.getPortletId()) +
			WebKeys.PORTLET_STRUTS_FORWARD;
	}

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		PortletConfig portletConfig = (PortletConfig)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		RenderRequest renderRequest = (RenderRequest)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_REQUEST);

		RenderResponse renderResponse = (RenderResponse)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_RESPONSE);

		Boolean strutsExecute = (Boolean)req.getAttribute(
			WebKeys.PORTLET_STRUTS_EXECUTE);

		if ((strutsExecute != null) && strutsExecute.booleanValue()) {
			return strutsExecute(mapping, form, req, res);
		}
		else {
			return render(
				mapping, form, portletConfig, renderRequest, renderResponse);
		}
	}

	public ActionForward strutsExecute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		return super.execute(mapping, form, req, res);
	}

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		if (_log.isDebugEnabled()) {
			_log.debug("Forward to " + getForward(req));
		}

		return mapping.findForward(getForward(req));
	}

	protected String getForward(PortletRequest req) {
		return getForward(req, null);
	}

	protected String getForward(PortletRequest req, String defaultValue) {
		String forward = (String)req.getAttribute(getForwardKey(req));

		if (forward == null) {
			return defaultValue;
		}
		else {
			return forward;
		}
	}

	protected void setForward(PortletRequest req, String forward) {
		req.setAttribute(getForwardKey(req), forward);
	}

	protected ModuleConfig getModuleConfig(PortletRequest req) {
		return (ModuleConfig)req.getAttribute(Globals.MODULE_KEY);
	}

	protected MessageResources getResources() {
		ServletContext ctx = getServlet().getServletContext();

		return (MessageResources)ctx.getAttribute(Globals.MESSAGES_KEY);
	}

	protected MessageResources getResources(HttpServletRequest req) {
		return getResources();
	}

	protected MessageResources getResources(PortletRequest req) {
		return getResources();
	}

	protected boolean isCheckMethodOnProcessAction() {
		return _CHECK_METHOD_ON_PROCESS_ACTION;
	}

	protected void sendRedirect(ActionRequest req, ActionResponse res)
		throws IOException {

		sendRedirect(req, res, null);
	}

	protected void sendRedirect(
			ActionRequest req, ActionResponse res, String redirect)
		throws IOException {

		if (SessionErrors.isEmpty(req)) {
			SessionMessages.add(req, "request_processed");
		}

		if (redirect == null) {
			redirect = ParamUtil.getString(req, "redirect");
		}

		if (Validator.isNotNull(redirect)) {
			res.sendRedirect(redirect);
		}
	}

	protected boolean redirectToLogin(ActionRequest req, ActionResponse res)
		throws IOException {

		if (req.getRemoteUser() == null) {
			HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

			SessionErrors.add(httpReq, PrincipalException.class.getName());

			ThemeDisplay themeDisplay =
				(ThemeDisplay)httpReq.getAttribute(WebKeys.THEME_DISPLAY);

			res.sendRedirect(themeDisplay.getPathMain() + "/portal/login");

			return true;
		}
		else {
			return false;
		}
	}

	private static final boolean _CHECK_METHOD_ON_PROCESS_ACTION = true;

	private static Log _log = LogFactory.getLog(PortletAction.class);

}