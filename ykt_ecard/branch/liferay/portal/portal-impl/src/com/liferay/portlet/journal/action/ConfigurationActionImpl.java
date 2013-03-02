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

package com.liferay.portlet.journal.action;

import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

/**
 * <a href="ConfigurationActionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ConfigurationActionImpl implements ConfigurationAction {

	public void processAction(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (!cmd.equals(Constants.UPDATE)) {
			return;
		}

		String portletResource = ParamUtil.getString(
			req, "portletResource");

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				req, portletResource, false, true);

		String tabs2 = ParamUtil.getString(req, "tabs2");

		if (tabs2.equals("email-from")) {
			updateEmailFrom(req, prefs);
		}
		else if (tabs2.equals("article-approval-denied-email")) {
			updateEmailArticleApprovalDenied(req, prefs);
		}
		else if (tabs2.equals("article-approval-granted-email")) {
			updateEmailArticleApprovalGranted(req, prefs);
		}
		else if (tabs2.equals("article-approval-requested-email")) {
			updateEmailArticleApprovalRequested(req, prefs);
		}
		else if (tabs2.equals("article-review-email")) {
			updateEmailArticleReview(req, prefs);
		}

		if (SessionErrors.isEmpty(req)) {
			prefs.store();

			SessionMessages.add(req, config.getPortletName() + ".doConfigure");
		}
	}

	public String render(
			PortletConfig config, RenderRequest req, RenderResponse res)
		throws Exception {

		return "/html/portlet/journal/configuration.jsp";
	}

	protected void updateEmailFrom(ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String emailFromName = ParamUtil.getString(req, "emailFromName");
		String emailFromAddress = ParamUtil.getString(req, "emailFromAddress");

		if (Validator.isNull(emailFromName)) {
			SessionErrors.add(req, "emailFromName");
		}
		else if (!Validator.isEmailAddress(emailFromAddress)) {
			SessionErrors.add(req, "emailFromAddress");
		}
		else {
			prefs.setValue("email-from-name", emailFromName);
			prefs.setValue("email-from-address", emailFromAddress);
		}
	}

	protected void updateEmailArticleApprovalDenied(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String emailArticleApprovalDeniedEnabled = ParamUtil.getString(
			req, "emailArticleApprovalDeniedEnabled");
		String emailArticleApprovalDeniedSubject = ParamUtil.getString(
			req, "emailArticleApprovalDeniedSubject");
		String emailArticleApprovalDeniedBody = ParamUtil.getString(
			req, "emailArticleApprovalDeniedBody");

		if (Validator.isNull(emailArticleApprovalDeniedSubject)) {
			SessionErrors.add(req, "emailArticleApprovalDeniedSubject");
		}
		else if (Validator.isNull(emailArticleApprovalDeniedBody)) {
			SessionErrors.add(req, "emailArticleApprovalDeniedBody");
		}
		else {
			prefs.setValue(
				"email-article-approval-denied-enabled",
				emailArticleApprovalDeniedEnabled);
			prefs.setValue(
				"email-article-approval-denied-subject",
				emailArticleApprovalDeniedSubject);
			prefs.setValue(
				"email-article-approval-denied-body",
				emailArticleApprovalDeniedBody);
		}
	}

	protected void updateEmailArticleApprovalGranted(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String emailArticleApprovalGrantedEnabled = ParamUtil.getString(
			req, "emailArticleApprovalGrantedEnabled");
		String emailArticleApprovalGrantedSubject = ParamUtil.getString(
			req, "emailArticleApprovalGrantedSubject");
		String emailArticleApprovalGrantedBody = ParamUtil.getString(
			req, "emailArticleApprovalGrantedBody");

		if (Validator.isNull(emailArticleApprovalGrantedSubject)) {
			SessionErrors.add(req, "emailArticleApprovalGrantedSubject");
		}
		else if (Validator.isNull(emailArticleApprovalGrantedBody)) {
			SessionErrors.add(req, "emailArticleApprovalGrantedBody");
		}
		else {
			prefs.setValue(
				"email-article-approval-granted-enabled",
				emailArticleApprovalGrantedEnabled);
			prefs.setValue(
				"email-article-approval-granted-subject",
				emailArticleApprovalGrantedSubject);
			prefs.setValue(
				"email-article-approval-granted-body",
				emailArticleApprovalGrantedBody);
		}
	}

	protected void updateEmailArticleApprovalRequested(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String emailArticleApprovalRequestedEnabled = ParamUtil.getString(
			req, "emailArticleApprovalRequestedEnabled");
		String emailArticleApprovalRequestedSubject = ParamUtil.getString(
			req, "emailArticleApprovalRequestedSubject");
		String emailArticleApprovalRequestedBody = ParamUtil.getString(
			req, "emailArticleApprovalRequestedBody");

		if (Validator.isNull(emailArticleApprovalRequestedSubject)) {
			SessionErrors.add(req, "emailArticleApprovalRequestedSubject");
		}
		else if (Validator.isNull(emailArticleApprovalRequestedBody)) {
			SessionErrors.add(req, "emailArticleApprovalRequestedBody");
		}
		else {
			prefs.setValue(
				"email-article-approval-requested-enabled",
				emailArticleApprovalRequestedEnabled);
			prefs.setValue(
				"email-article-approval-requested-subject",
				emailArticleApprovalRequestedSubject);
			prefs.setValue(
				"email-article-approval-requested-body",
				emailArticleApprovalRequestedBody);
		}
	}

	protected void updateEmailArticleReview(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String emailArticleReviewEnabled = ParamUtil.getString(
			req, "emailArticleReviewEnabled");
		String emailArticleReviewSubject = ParamUtil.getString(
			req, "emailArticleReviewSubject");
		String emailArticleReviewBody = ParamUtil.getString(
			req, "emailArticleReviewBody");

		if (Validator.isNull(emailArticleReviewSubject)) {
			SessionErrors.add(req, "emailArticleReviewSubject");
		}
		else if (Validator.isNull(emailArticleReviewBody)) {
			SessionErrors.add(req, "emailArticleReviewBody");
		}
		else {
			prefs.setValue(
				"email-article-review-enabled", emailArticleReviewEnabled);
			prefs.setValue(
				"email-article-review-subject", emailArticleReviewSubject);
			prefs.setValue("email-article-review-body", emailArticleReviewBody);
		}
	}

}