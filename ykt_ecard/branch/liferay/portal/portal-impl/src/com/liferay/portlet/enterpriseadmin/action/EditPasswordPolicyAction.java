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
import com.liferay.portal.PasswordPolicyNameException;
import com.liferay.portal.RequiredPasswordPolicyException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.PasswordPolicyServiceUtil;
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
 * <a href="EditPasswordPolicyAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Scott Lee
 *
 */
public class EditPasswordPolicyAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updatePasswordPolicy(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deletePasswordPolicy(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof PrincipalException) {
				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.enterprise_admin.error");
			}
			else if (e instanceof PasswordPolicyNameException ||
					 e instanceof NoSuchPasswordPolicyException ||
					 e instanceof RequiredPasswordPolicyException) {

				SessionErrors.add(req, e.getClass().getName());

				if (cmd.equals(Constants.DELETE)) {
					res.sendRedirect(ParamUtil.getString(req, "redirect"));
				}
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

		return mapping.findForward(
			getForward(req, "portlet.enterprise_admin.edit_password_policy"));
	}

	protected void deletePasswordPolicy(ActionRequest req) throws Exception {
		long passwordPolicyId = ParamUtil.getLong(req, "passwordPolicyId");

		PasswordPolicyServiceUtil.deletePasswordPolicy(passwordPolicyId);
	}

	protected void updatePasswordPolicy(ActionRequest req) throws Exception {
		long passwordPolicyId = ParamUtil.getLong(req, "passwordPolicyId");

		String name = ParamUtil.getString(req, "name");
		String description = ParamUtil.getString(req, "description");
		boolean changeable = ParamUtil.getBoolean(req, "changeable");
		boolean changeRequired = ParamUtil.getBoolean(req, "changeRequired");
		long minAge = ParamUtil.getLong(req, "minAge");
		boolean checkSyntax = ParamUtil.getBoolean(req, "checkSyntax");
		boolean allowDictionaryWords = ParamUtil.getBoolean(
			req, "allowDictionaryWords");
		int minLength = ParamUtil.getInteger(req, "minLength");
		boolean history = ParamUtil.getBoolean(req, "history");
		int historyCount = ParamUtil.getInteger(req, "historyCount");
		boolean expireable = ParamUtil.getBoolean(req, "expireable");
		long maxAge = ParamUtil.getLong(req, "maxAge");
		long warningTime = ParamUtil.getLong(req, "warningTime");
		int graceLimit = ParamUtil.getInteger(req, "graceLimit");
		boolean lockout = ParamUtil.getBoolean(req, "lockout");
		int maxFailure = ParamUtil.getInteger(req, "maxFailure");
		long lockoutDuration = ParamUtil.getLong(req, "lockoutDuration");
		long resetFailureCount = ParamUtil.getLong(req, "resetFailureCount");

		if (passwordPolicyId <= 0) {

			// Add password policy

			PasswordPolicyServiceUtil.addPasswordPolicy(
				name, description, changeable, changeRequired, minAge,
				checkSyntax, allowDictionaryWords, minLength, history,
				historyCount, expireable, maxAge, warningTime, graceLimit,
				lockout, maxFailure, lockoutDuration, resetFailureCount);
		}
		else {

			// Update password policy

			PasswordPolicyServiceUtil.updatePasswordPolicy(
				passwordPolicyId, name, description, changeable, changeRequired,
				minAge, checkSyntax, allowDictionaryWords, minLength, history,
				historyCount, expireable, maxAge, warningTime, graceLimit,
				lockout, maxFailure, lockoutDuration, resetFailureCount);
		}
	}

}