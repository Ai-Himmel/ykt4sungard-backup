/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.journal.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.admin.model.EmailConfig;
import com.liferay.portlet.admin.model.JournalConfig;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="UpdateJournalConfigAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class UpdateJournalConfigAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			String cmd = ParamUtil.get(req, Constants.CMD, "requested");

			boolean allowSimpleArticles = ParamUtil.get(
				req, "config_allow_simple_articles", true);

			boolean approvalRequestedEmailSend = ParamUtil.get(
				req, "config_requested_send", true);
			String approvalRequestedEmailSubject = ParamUtil.getString(
				req, "config_requested_subject");
			String approvalRequestedEmailBody = ParamUtil.getString(
				req, "config_requested_body");

			boolean approvalGrantedEmailSend = ParamUtil.get(
				req, "config_granted_send", true);
			String approvalGrantedEmailSubject = ParamUtil.getString(
				req, "config_granted_subject");
			String approvalGrantedEmailBody = ParamUtil.getString(
				req, "config_granted_body");

			boolean approvalDeniedEmailSend = ParamUtil.get(
				req, "config_denied_send", true);
			String approvalDeniedEmailSubject = ParamUtil.getString(
				req, "config_denied_subject");
			String approvalDeniedEmailBody = ParamUtil.getString(
				req, "config_denied_body");

			JournalConfig journalConfig =
				AdminConfigServiceUtil.getJournalConfig(
					PortalUtil.getCompanyId(req), config.getPortletName());

			if (cmd.equals("basic")) {
				journalConfig.setAllowSimpleArticles(allowSimpleArticles);
			}
			else if (cmd.equals("requested")) {
				journalConfig.setApprovalRequestedEmail(new EmailConfig(
					approvalRequestedEmailSend, approvalRequestedEmailSubject,
					approvalRequestedEmailBody));
			}
			else if (cmd.equals("granted")) {
				journalConfig.setApprovalGrantedEmail(new EmailConfig(
					approvalGrantedEmailSend, approvalGrantedEmailSubject,
					approvalGrantedEmailBody));
			}
			else if (cmd.equals("denied")) {
				journalConfig.setApprovalDeniedEmail(new EmailConfig(
					approvalDeniedEmailSend, approvalDeniedEmailSubject,
					approvalDeniedEmailBody));
			}

			// Update config

			AdminConfigServiceUtil.updateJournalConfig(
				journalConfig, config.getPortletName());

			// Session messages

			SessionMessages.add(req, UpdateJournalConfigAction.class.getName());

			// Send redirect

			res.sendRedirect(ParamUtil.getString(req, "redirect"));
		}
		catch (Exception e) {
			if (e != null &&
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.journal.error");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
	}

}