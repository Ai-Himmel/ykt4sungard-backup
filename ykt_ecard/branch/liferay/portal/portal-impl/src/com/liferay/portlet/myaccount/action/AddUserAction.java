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

package com.liferay.portlet.myaccount.action;

import com.liferay.portal.ContactFirstNameException;
import com.liferay.portal.ContactLastNameException;
import com.liferay.portal.DuplicateUserEmailAddressException;
import com.liferay.portal.DuplicateUserScreenNameException;
import com.liferay.portal.NoSuchOrganizationException;
import com.liferay.portal.OrganizationParentException;
import com.liferay.portal.RequiredUserException;
import com.liferay.portal.ReservedUserEmailAddressException;
import com.liferay.portal.UserEmailAddressException;
import com.liferay.portal.UserIdException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.UserScreenNameException;
import com.liferay.portal.UserSmsException;
import com.liferay.portal.captcha.CaptchaTextException;
import com.liferay.portal.captcha.CaptchaUtil;
import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="AddUserAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class AddUserAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD)) {
				addUser(req, res);
			}
		}
		catch (Exception e) {
			if (e instanceof CaptchaTextException ||
				e instanceof ContactFirstNameException ||
				e instanceof ContactLastNameException ||
				e instanceof DuplicateUserEmailAddressException ||
				e instanceof DuplicateUserScreenNameException ||
				e instanceof NoSuchOrganizationException ||
				e instanceof OrganizationParentException ||
				e instanceof RequiredUserException ||
				e instanceof ReservedUserEmailAddressException ||
				e instanceof UserEmailAddressException ||
				e instanceof UserIdException ||
				e instanceof UserPasswordException ||
				e instanceof UserScreenNameException ||
				e instanceof UserSmsException) {

				SessionErrors.add(req, e.getClass().getName(), e);
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

		Company company = PortalUtil.getCompany(req);

		if (!company.isStrangers()) {
			throw new PrincipalException();
		}

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		res.setTitle(
			LanguageUtil.get(
				themeDisplay.getCompanyId(), themeDisplay.getLocale(),
				"create-account"));

		return mapping.findForward("portlet.my_account.create_account");
	}

	protected void addUser(ActionRequest req, ActionResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		Company company = themeDisplay.getCompany();

		boolean autoPassword = true;
		String password1 = null;
		String password2 = null;
		boolean autoScreenName = false;
		String screenName = ParamUtil.getString(req, "screenName");
		String emailAddress = ParamUtil.getString(req, "emailAddress");
		String firstName = ParamUtil.getString(req, "firstName");
		String middleName = ParamUtil.getString(req, "middleName");
		String lastName = ParamUtil.getString(req, "lastName");
		int prefixId = ParamUtil.getInteger(req, "prefixId");
		int suffixId = ParamUtil.getInteger(req, "suffixId");
		boolean male = ParamUtil.get(req, "male", true);
		int birthdayMonth = ParamUtil.getInteger(req, "birthdayMonth");
		int birthdayDay = ParamUtil.getInteger(req, "birthdayDay");
		int birthdayYear = ParamUtil.getInteger(req, "birthdayYear");
		String jobTitle = ParamUtil.getString(req, "jobTitle");
		long[] organizationIds = StringUtil.split(
			ParamUtil.getString(req, "organizationIds"),  0L);
		boolean sendEmail = true;

		CaptchaUtil.check(req);

		User user = UserServiceUtil.addUser(
			company.getCompanyId(), autoPassword, password1, password2,
			autoScreenName, screenName, emailAddress, themeDisplay.getLocale(),
			firstName, middleName, lastName, prefixId, suffixId, male,
			birthdayMonth, birthdayDay, birthdayYear, jobTitle, organizationIds,
			sendEmail);

		// Session messages

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		SessionMessages.add(httpReq, "user_added", user.getEmailAddress());
		SessionMessages.add(
			httpReq, "user_added_password", user.getPasswordUnencrypted());

		// Send redirect

		String redirect = themeDisplay.getPathMain() + "/portal/login?login=";

		if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_ID)) {
			redirect += user.getUserId();
		}
		else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_SN)) {
			redirect += user.getScreenName();
		}
		else {
			redirect += user.getEmailAddress();
		}

		res.sendRedirect(redirect);
	}

	protected boolean isCheckMethodOnProcessAction() {
		return _CHECK_METHOD_ON_PROCESS_ACTION;
	}

	private static final boolean _CHECK_METHOD_ON_PROCESS_ACTION = false;

}