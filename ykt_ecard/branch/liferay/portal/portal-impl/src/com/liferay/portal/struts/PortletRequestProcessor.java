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

import com.liferay.portal.kernel.portlet.LiferayPortletURL;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.PortletConfigImpl;
import com.liferay.portlet.PortletRequestDispatcherImpl;

import java.io.IOException;

import java.lang.reflect.Constructor;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletException;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionServlet;
import org.apache.struts.config.ForwardConfig;
import org.apache.struts.config.ModuleConfig;
import org.apache.struts.tiles.TilesRequestProcessor;

/**
 * <a href="PortletRequestProcessor.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletRequestProcessor extends TilesRequestProcessor {

	public static PortletRequestProcessor getInstance(
			ActionServlet servlet, ModuleConfig config)
		throws ServletException {

		try {
			String className = PropsValues.STRUTS_PORTLET_REQUEST_PROCESSOR;

			Class clazz = Class.forName(className);

			Constructor constructor = clazz.getConstructor(
				new Class[] {
					ActionServlet.class, ModuleConfig.class
				}
			);

			PortletRequestProcessor portletReqProcessor =
				(PortletRequestProcessor)constructor.newInstance(
					new Object[] {
						servlet, config
					}
				);

			return portletReqProcessor;
		}
		catch (Exception e) {
			_log.error(e);

			return new PortletRequestProcessor(servlet, config);
		}
	}

	public PortletRequestProcessor(ActionServlet servlet, ModuleConfig config)
		throws ServletException {

		init(servlet, config);
	}

	public void process(RenderRequest req, RenderResponse res)
		throws IOException, ServletException {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(res);

		process(httpReq, httpRes);
	}

	public void process(ActionRequest req, ActionResponse res, String path)
		throws IOException, ServletException {

		ActionResponseImpl resImpl = (ActionResponseImpl)res;

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(res);

		ActionMapping mapping = processMapping(httpReq, httpRes, path);

		if (mapping == null) {
			return;
		}

		if (!processRoles(httpReq, httpRes, mapping, true)) {
			return;
		}

		ActionForm form = processActionForm(httpReq, httpRes, mapping);

		processPopulate(httpReq, httpRes, form, mapping);

		if (!processValidateAction(httpReq, httpRes, form, mapping)) {
			return;
		}

		PortletAction action =
			(PortletAction)processActionCreate(httpReq, httpRes, mapping);

		if (action == null) {
			return;
		}

		PortletConfigImpl portletConfig = (PortletConfigImpl)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		try {
			if (action.isCheckMethodOnProcessAction()) {
				if (!PortalUtil.isMethodPost(req)) {
					String currentURL = PortalUtil.getCurrentURL(req);

					if (_log.isWarnEnabled()) {
						_log.warn(
							"This URL can only be invoked using POST: " +
								currentURL);
					}

					throw new PrincipalException(currentURL);
				}
			}

			action.processAction(mapping, form, portletConfig, req, res);
		}
		catch (Exception e) {
			String exceptionId =
				WebKeys.PORTLET_STRUTS_EXCEPTION + StringPool.PERIOD +
					portletConfig.getPortletId();

			req.setAttribute(exceptionId, e);
		}

		String forward =
			(String)req.getAttribute(PortletAction.getForwardKey(req));

		if (forward != null) {
			String queryString = StringPool.BLANK;

			int pos = forward.indexOf("?");

			if (pos != -1) {
				queryString = forward.substring(pos + 1, forward.length());
				forward = forward.substring(0, pos);
			}

			ActionForward actionForward = mapping.findForward(forward);

			if ((actionForward != null) && (actionForward.getRedirect())) {
				String forwardPath = actionForward.getPath();

				if (forwardPath.startsWith("/")) {
					LiferayPortletURL forwardURL =
						(LiferayPortletURL)resImpl.createRenderURL();

					forwardURL.setParameter("struts_action", forwardPath);

					StrutsURLEncoder.setParameters(forwardURL, queryString);

					forwardPath = forwardURL.toString();
				}

				res.sendRedirect(forwardPath);
			}
		}
	}

	protected ActionForm processActionForm(
		HttpServletRequest req, HttpServletResponse res,
		ActionMapping mapping) {

		ActionForm form = super.processActionForm(req, res, mapping);

		if (form instanceof InitializableActionForm) {
			InitializableActionForm initForm = (InitializableActionForm)form;

			initForm.init(req, res, mapping);
		}

		return form;
	}

	protected ActionForward processActionPerform(
			HttpServletRequest req, HttpServletResponse res, Action action,
			ActionForm form, ActionMapping mapping)
		throws IOException, ServletException {

		PortletConfigImpl portletConfig = (PortletConfigImpl)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		String exceptionId =
			WebKeys.PORTLET_STRUTS_EXCEPTION + StringPool.PERIOD +
				portletConfig.getPortletId();

		Exception e = (Exception)req.getAttribute(exceptionId);

		if (e != null) {
			return processException(req, res, e, form, mapping);
		}
		else {
			return super.processActionPerform(req, res, action, form, mapping);
		}
	}

	protected void processForwardConfig(
			HttpServletRequest req, HttpServletResponse res,
			ForwardConfig forward)
		throws IOException, ServletException {

		if (forward == null) {
			_log.error("Forward does not exist");
		}
		else {

			// Don't render a null path. This is useful if you're sending a file
			// in an exclusive window state.

			if (forward.getPath().equals(ActionConstants.COMMON_NULL)) {
				return;
			}
		}

		super.processForwardConfig(req, res, forward);
	}

	public ActionMapping processMapping(
			HttpServletRequest req, HttpServletResponse res, String path)
		throws IOException {

		if (path == null) {
			return null;
		}

		return super.processMapping(req, res, path);
	}

	protected boolean processRoles(
			HttpServletRequest req, HttpServletResponse res,
			ActionMapping mapping)
		throws IOException, ServletException {

		return processRoles(req, res, mapping, false);
	}

	protected boolean processRoles(
			HttpServletRequest req, HttpServletResponse res,
			ActionMapping mapping, boolean action)
		throws IOException, ServletException {

		User user = null;

		try {
			user = PortalUtil.getUser(req);
		}
		catch (Exception e) {
		}

		if (user == null) {
			return true;
		}

		String path = mapping.getPath();

		try {
			PortletConfigImpl portletConfig =
				(PortletConfigImpl)req.getAttribute(
					JavaConstants.JAVAX_PORTLET_CONFIG);

			Portlet portlet = PortletLocalServiceUtil.getPortletById(
				user.getCompanyId(), portletConfig.getPortletId());

			if (portlet == null) {
				return false;
			}

			String strutsPath = path.substring(
				1, path.lastIndexOf(StringPool.SLASH));

			if (!strutsPath.equals(portlet.getStrutsPath())) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"The struts path " + strutsPath + " does not belong " +
							"to portlet " + portlet.getPortletId() + ". " +
								"Check the definition in liferay-portlet.xml");
				}

				throw new PrincipalException();
			}
			else if (portlet.isActive()) {
				ThemeDisplay themeDisplay =
					(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

				Layout layout = themeDisplay.getLayout();
				PermissionChecker permissionChecker =
					themeDisplay.getPermissionChecker();

				if (!PortletPermissionUtil.contains(
						permissionChecker, layout.getPlid(), portlet,
						ActionKeys.VIEW)) {

					throw new PrincipalException();
				}
			}
			else if (!portlet.isActive()) {
				ForwardConfig forwardConfig =
					mapping.findForward(_PATH_PORTAL_PORTLET_INACTIVE);

				if (!action) {
					processForwardConfig(req, res, forwardConfig);
				}

				return false;
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e.getMessage());
			}

			ForwardConfig forwardConfig =
				mapping.findForward(_PATH_PORTAL_PORTLET_ACCESS_DENIED);

			if (!action) {
				processForwardConfig(req, res, forwardConfig);
			}

			return false;
		}

		return true;
	}

	protected boolean processValidateAction(
			HttpServletRequest req, HttpServletResponse res, ActionForm form,
			ActionMapping mapping)
		throws IOException, ServletException {

		if (form == null) {
			return true;
		}

		if (req.getAttribute(Globals.CANCEL_KEY) != null) {
			return true;
		}

		if (!mapping.getValidate()) {
			return true;
		}

		ActionErrors errors = form.validate(mapping, req);

		if ((errors == null) || errors.isEmpty()) {
			return true;
		}

		if (form.getMultipartRequestHandler() != null) {
			form.getMultipartRequestHandler().rollback();
		}

		String input = mapping.getInput();

		if (input == null) {
			_log.error("Validation failed but no input form is available");

			return false;
		}

		req.setAttribute(Globals.ERROR_KEY, errors);

		// Struts normally calls internalModuleRelativeForward which breaks
		// if called inside processAction

		req.setAttribute(PortletAction.getForwardKey(req), input);

		return false;
	}

	protected void doForward(
			String uri, HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		doInclude(uri, req, res);
	}

	protected void doInclude(
			String uri, HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		PortletConfigImpl portletConfig = (PortletConfigImpl)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		RenderRequest renderRequest = (RenderRequest)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_REQUEST);

		RenderResponse renderResponse = (RenderResponse)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_RESPONSE);

		PortletRequestDispatcherImpl prd = (PortletRequestDispatcherImpl)
			portletConfig.getPortletContext().getRequestDispatcher(
				StrutsUtil.TEXT_HTML_DIR + uri);

		try {
			if (prd == null) {
				_log.error(uri + " is not a valid include");
			}
			else {
				prd.include(renderRequest, renderResponse, true);
			}
		}
		catch (PortletException pe) {
			Throwable cause = pe.getCause();

			if (cause instanceof ServletException) {
				throw (ServletException)cause;
			}
			else {
				_log.error(cause, cause);
			}
		}
	}

	protected HttpServletRequest processMultipart(HttpServletRequest req) {

		// Disable Struts from automatically wrapping a multipart request

		return req;
	}

	protected String processPath(
			HttpServletRequest req, HttpServletResponse res)
		throws IOException {

		String path = req.getParameter("struts_action");

		if (_log.isDebugEnabled()) {
			_log.debug("Getting request parameter path " + path);
		}

		if (Validator.isNull(path)) {
			if (_log.isDebugEnabled()) {
				_log.debug("Getting request attribute path " + path);
			}

			path = (String)req.getAttribute(WebKeys.PORTLET_STRUTS_ACTION);
		}

		if (path == null) {
			PortletConfigImpl portletConfig =
				(PortletConfigImpl)req.getAttribute(
					JavaConstants.JAVAX_PORTLET_CONFIG);

			_log.error(
				portletConfig.getPortletName() +
					" does not have any paths specified");
		}
		else {
			if (_log.isDebugEnabled()) {
				_log.debug("Processing path " + path);
			}
		}

		return path;
	}

	private static final String _PATH_PORTAL_PORTLET_ACCESS_DENIED =
		"/portal/portlet_access_denied";

	private static final String _PATH_PORTAL_PORTLET_INACTIVE =
		"/portal/portlet_inactive";

	private static Log _log = LogFactory.getLog(PortletRequestProcessor.class);

}