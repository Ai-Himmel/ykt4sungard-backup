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

package com.liferay.portlet.wsrp.action;

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletSession;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditLocalPreferencesAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class EditLocalPreferencesAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		PortletPreferences prefs = req.getPreferences();

		String wsrpServiceUrl = ParamUtil.getString(req, "wsrp_service_url");
		String markupEndpoint = ParamUtil.getString(req, "markup_endpoint");
		String serviceDescriptionEndpoint = ParamUtil.getString(req,
				"service_description_endpoint");
		String registrationEndpoint = ParamUtil.getString(req,
				"registration_endpoint");
		String portletManagementEndpoint = ParamUtil.getString(req,
				"portlet_management_endpoint");
		String portletHandle = ParamUtil.getString(req, "portlet_handle");

		prefs.setValue("wsrp-service-url", wsrpServiceUrl);
		prefs.setValue("markup-endpoint", markupEndpoint);
		prefs.setValue("service-description-endpoint",
				serviceDescriptionEndpoint);
		prefs.setValue("registration-endpoint", registrationEndpoint);
		prefs.setValue("portlet-management-endpoint",
						portletManagementEndpoint);

		String oldPortletHandle = prefs.getValue("portlet-handle", "");
		if (!portletHandle.equals(oldPortletHandle)) {
			prefs.reset("parent-handle");
		}
		prefs.setValue("portlet-handle", portletHandle);

		// start a new wsrp session on next render
		PortletSession ses = req.getPortletSession();
		ses.setAttribute(WebKeys.WSRP_NEW_SESSION, "true");

		prefs.store();

		SessionMessages.add(req, config.getPortletName() + ".doEdit");

		setForward(req, "portlet.wsrp.edit");
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		return mapping.findForward(
			getForward(req, "portlet.wsrp.edit_local_preferences"));
	}

}