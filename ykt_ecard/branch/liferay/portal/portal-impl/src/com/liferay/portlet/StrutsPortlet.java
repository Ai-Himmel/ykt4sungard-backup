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

package com.liferay.portlet;

import com.liferay.portal.kernel.portlet.LiferayPortlet;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.security.permission.PermissionCheckerImpl;
import com.liferay.portal.security.permission.PermissionThreadLocal;
import com.liferay.portal.struts.PortletRequestProcessor;
import com.liferay.portal.struts.StrutsUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;

import java.io.IOException;

import java.util.Map;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletException;
import javax.portlet.PortletRequest;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletException;

/**
 * <a href="StrutsPortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class StrutsPortlet extends LiferayPortlet {

	public void init(PortletConfig config) throws PortletException {
		super.init(config);

		aboutAction = getInitParameter("about-action");
		configAction = getInitParameter("config-action");
		editAction = getInitParameter("edit-action");
		editDefaultsAction = getInitParameter("edit-defaults-action");
		editGuestAction = getInitParameter("edit-guest-action");
		helpAction = getInitParameter("help-action");
		previewAction = getInitParameter("preview-action");
		printAction = getInitParameter("print-action");
		viewAction = getInitParameter("view-action");

		copyRequestParameters = GetterUtil.getBoolean(
			getInitParameter("copy-request-parameters"), true);

		_portletConfig = (PortletConfigImpl)config;
	}

	public void processAction(ActionRequest req, ActionResponse res)
		throws IOException, PortletException {

		String path = req.getParameter("struts_action");

		if (Validator.isNotNull(path)) {

			// Call processAction of com.liferay.portal.struts.PortletAction

			PermissionCheckerImpl permissionChecker = (PermissionCheckerImpl)
				PermissionThreadLocal.getPermissionChecker();

			try {
				permissionChecker.setValues(req);

				// Process action

				PortletRequestProcessor processor =
					_getPortletRequestProcessor(req);

				processor.process(req, res, path);
			}
			catch (ServletException se) {
				throw new PortletException(se);
			}
			finally {
				permissionChecker.resetValues();
			}
		}

		if (copyRequestParameters) {
			PortalUtil.copyRequestParameters(req, res);
		}
	}

	public void doAbout(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		req.setAttribute(WebKeys.PORTLET_STRUTS_ACTION, aboutAction);

		include(req, res);
	}

	public void doConfig(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		req.setAttribute(WebKeys.PORTLET_STRUTS_ACTION, configAction);

		include(req, res);
	}

	public void doEdit(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			req.setAttribute(WebKeys.PORTLET_STRUTS_ACTION, editAction);

			include(req, res);
		}
	}

	public void doEditDefaults(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			req.setAttribute(WebKeys.PORTLET_STRUTS_ACTION, editDefaultsAction);

			include(req, res);
		}
	}

	public void doEditGuest(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			req.setAttribute(WebKeys.PORTLET_STRUTS_ACTION, editGuestAction);

			include(req, res);
		}
	}

	public void doHelp(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		req.setAttribute(WebKeys.PORTLET_STRUTS_ACTION, helpAction);

		include(req, res);
	}

	public void doPreview(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		req.setAttribute(WebKeys.PORTLET_STRUTS_ACTION, previewAction);

		include(req, res);
	}

	public void doPrint(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		req.setAttribute(WebKeys.PORTLET_STRUTS_ACTION, printAction);

		include(req, res);
	}

	public void doView(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		req.setAttribute(WebKeys.PORTLET_STRUTS_ACTION, viewAction);

		include(req, res);
	}

	protected void include(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		// Call render of com.liferay.portal.struts.PortletAction

		Map strutsAttributes = null;

		if (_portletConfig.isWARFile()) {

			// Remove any Struts request attributes

			strutsAttributes =
				StrutsUtil.removeStrutsAttributes(getPortletContext(), req);
		}

		// Process render

		PermissionCheckerImpl permissionChecker =
			(PermissionCheckerImpl)PermissionThreadLocal.getPermissionChecker();

		try {
			permissionChecker.setValues(req);

			PortletRequestProcessor processor =
				_getPortletRequestProcessor(req);

			processor.process(req, res);
		}
		catch (IOException ioe) {
			throw ioe;
		}
		catch (ServletException se) {
			throw new PortletException(se);
		}
		finally {
			permissionChecker.resetValues();

			if (_portletConfig.isWARFile()) {

				// Set the Struts request attributes

				StrutsUtil.setStrutsAttributes(req, strutsAttributes);
			}
		}

		if (copyRequestParameters) {
			PortalUtil.clearRequestParameters(req);
		}
	}

	private PortletRequestProcessor _getPortletRequestProcessor(
		PortletRequest req) {

		return (PortletRequestProcessor)getPortletContext().getAttribute(
			WebKeys.PORTLET_STRUTS_PROCESSOR);
	}

	protected String aboutAction;
	protected String configAction;
	protected String editAction;
	protected String editDefaultsAction;
	protected String editGuestAction;
	protected String helpAction;
	protected String previewAction;
	protected String printAction;
	protected String viewAction;
	protected boolean copyRequestParameters;

	private PortletConfigImpl _portletConfig;

}