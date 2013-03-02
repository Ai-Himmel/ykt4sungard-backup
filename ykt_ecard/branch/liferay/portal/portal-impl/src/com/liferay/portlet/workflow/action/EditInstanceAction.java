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

package com.liferay.portlet.workflow.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portlet.workflow.model.WorkflowInstance;
import com.liferay.portlet.workflow.service.WorkflowInstanceServiceUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditInstanceAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditInstanceAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD)) {
				addInstance(req, res);
			}
			else if (cmd.equals(Constants.SIGNAL)) {
				signalInstance(req, res);
			}
		}
		catch (Exception e) {
			if (e instanceof PrincipalException) {
				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.workflow.error");
			}
			else {
				throw e;
			}
		}
	}

	protected void addInstance(ActionRequest req, ActionResponse res)
		throws Exception {

		long definitionId = ParamUtil.getLong(req, "definitionId");

		WorkflowInstance instance =
			WorkflowInstanceServiceUtil.addInstance(definitionId);

		String redirect = ParamUtil.getString(req, "redirect");

		redirect += "&instanceId=" + instance.getInstanceId();

		sendRedirect(req, res, redirect);
	}

	protected void signalInstance(ActionRequest req, ActionResponse res)
		throws Exception {

		long instanceId = ParamUtil.getLong(req, "instanceId");
		long tokenId = ParamUtil.getLong(req, "tokenId");

		if (tokenId <= 0) {
			WorkflowInstanceServiceUtil.signalInstance(instanceId);
		}
		else {
			WorkflowInstanceServiceUtil.signalToken(instanceId, tokenId);
		}

		sendRedirect(req, res);
	}

}