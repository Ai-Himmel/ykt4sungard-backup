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

package com.liferay.portlet.enterpriseadmin.action;

import com.liferay.portal.NoSuchPasswordPolicyException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.OrganizationServiceUtil;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditPasswordPolicyAssignmentsAction.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Scott Lee
 *
 */
public class EditPasswordPolicyAssignmentsAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals("password_policy_organizations")) {
				updatePasswordPolicyOrganizations(req);
			}
			else if (cmd.equals("password_policy_users")) {
				updatePasswordPolicyUsers(req);
			}

			if (Validator.isNotNull(cmd)) {
				String redirect = ParamUtil.getString(
					req, "assignmentsRedirect");

				sendRedirect(req, res, redirect);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchPasswordPolicyException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.enterprise_admin.error");
			}
			else {
				throw e;
			}
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		try {
			ActionUtil.getPasswordPolicy(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchPasswordPolicyException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.enterprise_admin.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(getForward(
			req, "portlet.enterprise_admin.edit_password_policy_assignments"));
	}

	protected void updatePasswordPolicyOrganizations(ActionRequest req)
		throws Exception {

		long passwordPolicyId = ParamUtil.getLong(req, "passwordPolicyId");

		long[] addOrganizationIds = StringUtil.split(
			ParamUtil.getString(req, "addOrganizationIds"), 0L);
		long[] removeOrganizationIds = StringUtil.split(
			ParamUtil.getString(req, "removeOrganizationIds"), 0L);

		OrganizationServiceUtil.addPasswordPolicyOrganizations(
			passwordPolicyId, addOrganizationIds);
		OrganizationServiceUtil.unsetPasswordPolicyOrganizations(
			passwordPolicyId, removeOrganizationIds);
	}

	protected void updatePasswordPolicyUsers(ActionRequest req)
		throws Exception {

		long passwordPolicyId = ParamUtil.getLong(req, "passwordPolicyId");

		long[] addUserIds = StringUtil.split(
			ParamUtil.getString(req, "addUserIds"), 0L);
		long[] removeUserIds = StringUtil.split(
			ParamUtil.getString(req, "removeUserIds"), 0L);

		UserServiceUtil.addPasswordPolicyUsers(passwordPolicyId, addUserIds);
		UserServiceUtil.unsetPasswordPolicyUsers(
			passwordPolicyId, removeUserIds);
	}

}