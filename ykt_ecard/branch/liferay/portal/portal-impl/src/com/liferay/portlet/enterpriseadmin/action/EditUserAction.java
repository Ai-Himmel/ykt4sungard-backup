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

import com.liferay.portal.ContactFirstNameException;
import com.liferay.portal.ContactLastNameException;
import com.liferay.portal.DuplicateUserEmailAddressException;
import com.liferay.portal.DuplicateUserScreenNameException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.RequiredUserException;
import com.liferay.portal.ReservedUserEmailAddressException;
import com.liferay.portal.ReservedUserScreenNameException;
import com.liferay.portal.UserEmailAddressException;
import com.liferay.portal.UserIdException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.UserScreenNameException;
import com.liferay.portal.UserSmsException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.CachePortlet;
import com.liferay.portlet.admin.util.AdminUtil;
import com.liferay.util.HttpUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletSession;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditUserAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditUserAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {
		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			User user = null;
			String oldScreenName = StringPool.BLANK;

			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				Object[] returnValue = updateUser(req);

				user = (User)returnValue[0];
				oldScreenName = ((String)returnValue[1]);
			}
			else if (cmd.equals(Constants.DEACTIVATE) ||
					 cmd.equals(Constants.DELETE) ||
					 cmd.equals(Constants.RESTORE)) {

				deleteUsers(req);
			}
			else if (cmd.equals("deleteRole")) {
				deleteRole(req);
			}
			else if (cmd.equals("unlock")) {
				user = updateLockout(req);
			}

			String redirect = ParamUtil.getString(req, "redirect");

			if (user != null) {
				if (Validator.isNotNull(oldScreenName)) {

					// This will fix the redirect if the user is on his personal
					// my account page and changes his screen name. A redirect
					// that references the old screen name no longer points to a
					// valid screen name and therefore needs to be updated.

					ThemeDisplay themeDisplay =
						(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

					Group group = user.getGroup();

					if (group.getGroupId() ==
							themeDisplay.getPortletGroupId()) {

						Layout layout = themeDisplay.getLayout();

						String friendlyURLPath = group.getPathFriendlyURL(
							layout.isPrivateLayout(), themeDisplay);

						String oldPath =
							friendlyURLPath + StringPool.SLASH + oldScreenName;
						String newPath =
							friendlyURLPath + StringPool.SLASH +
								user.getScreenName();

						redirect = StringUtil.replace(
							redirect, oldPath, newPath);

						redirect = StringUtil.replace(
							redirect, HttpUtil.encodeURL(oldPath),
							HttpUtil.encodeURL(newPath));
					}
				}

				redirect += user.getUserId();
			}

			sendRedirect(req, res, redirect);
		}
		catch (Exception e) {
			if (e instanceof NoSuchUserException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.enterprise_admin.error");
			}
			else if (e instanceof ContactFirstNameException ||
					 e instanceof ContactLastNameException ||
					 e instanceof DuplicateUserEmailAddressException ||
					 e instanceof DuplicateUserScreenNameException ||
					 e instanceof RequiredUserException ||
					 e instanceof ReservedUserEmailAddressException ||
					 e instanceof ReservedUserScreenNameException ||
					 e instanceof UserEmailAddressException ||
					 e instanceof UserIdException ||
					 e instanceof UserPasswordException ||
					 e instanceof UserScreenNameException ||
					 e instanceof UserSmsException) {

				SessionErrors.add(req, e.getClass().getName(), e);

				if (e instanceof RequiredUserException) {
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
			PortalUtil.getSelectedUser(req);
		}
		catch (Exception e) {
			if (e instanceof PrincipalException) {
				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.enterprise_admin.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.enterprise_admin.edit_user"));
	}

	protected void deleteRole(ActionRequest req) throws Exception {
		User user = PortalUtil.getSelectedUser(req);

		long roleId = ParamUtil.getLong(req, "roleId");

		UserServiceUtil.deleteRoleUser(roleId, user.getUserId());
	}

	protected void deleteUsers(ActionRequest req) throws Exception {
		String cmd = ParamUtil.getString(req, Constants.CMD);

		long[] deleteUserIds = StringUtil.split(
			ParamUtil.getString(req, "deleteUserIds"), 0L);

		for (int i = 0; i < deleteUserIds.length; i++) {
			if (cmd.equals(Constants.DEACTIVATE) ||
				cmd.equals(Constants.RESTORE)) {

				boolean active = !cmd.equals(Constants.DEACTIVATE);

				UserServiceUtil.updateActive(deleteUserIds[i], active);
			}
			else {
				UserServiceUtil.deleteUser(deleteUserIds[i]);
			}
		}
	}

	protected User updateLockout(ActionRequest req) throws Exception {
		User user = PortalUtil.getSelectedUser(req);

		UserServiceUtil.updateLockout(user.getUserId(), false);

		return user;
	}

	protected Object[] updateUser(ActionRequest req) throws Exception {
		String cmd = ParamUtil.getString(req, Constants.CMD);

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		boolean autoPassword = false;
		String password1 = "666666";
		String password2 = "666666";
		boolean autoScreenName = false;
		String screenName = ParamUtil.getString(req, "screenName");
		String emailAddress = ParamUtil.getString(req, "emailAddress");
		String languageId = ParamUtil.getString(req, "languageId");
		String timeZoneId = ParamUtil.getString(req, "timeZoneId");
		String greeting = ParamUtil.getString(req, "greeting");
		String firstName = ParamUtil.getString(req, "firstName");
		String middleName = ParamUtil.getString(req, "middleName");
		String lastName = ParamUtil.getString(req, "lastName");
		int prefixId = ParamUtil.getInteger(req, "prefixId");
		int suffixId = ParamUtil.getInteger(req, "suffixId");
		boolean male = ParamUtil.get(req, "male", true);
		int birthdayMonth = ParamUtil.getInteger(req, "birthdayMonth");
		int birthdayDay = ParamUtil.getInteger(req, "birthdayDay");
		int birthdayYear = ParamUtil.getInteger(req, "birthdayYear");
		String comments = ParamUtil.getString(req, "comments");
		String smsSn = ParamUtil.getString(req, "smsSn");
		String aimSn = ParamUtil.getString(req, "aimSn");
		String icqSn = ParamUtil.getString(req, "icqSn");
		String jabberSn = ParamUtil.getString(req, "jabberSn");
		String msnSn = ParamUtil.getString(req, "msnSn");
		String skypeSn = ParamUtil.getString(req, "skypeSn");
		String ymSn = ParamUtil.getString(req, "ymSn");
		String jobTitle = ParamUtil.getString(req, "jobTitle");
		long[] organizationIds = StringUtil.split(
			ParamUtil.getString(req, "organizationIds"),  0L);
		boolean sendEmail = false;

		User user = null;
		String oldScreenName = StringPool.BLANK;

		if (cmd.equals(Constants.ADD)) {

			// Add user

			user = UserServiceUtil.addUser(
				themeDisplay.getCompanyId(), autoPassword, password1, password2,
				autoScreenName, screenName, emailAddress,
				themeDisplay.getLocale(), firstName, middleName, lastName,
				prefixId, suffixId, male, birthdayMonth, birthdayDay,
				birthdayYear, jobTitle, organizationIds, sendEmail);
		}
		else {

			// Update user

			user = PortalUtil.getSelectedUser(req);

			String oldPassword = AdminUtil.getUpdateUserPassword(
				req, user.getUserId());
			String newPassword1 = ParamUtil.getString(req, "password1");
			String newPassword2 = ParamUtil.getString(req, "password2");
			boolean passwordReset = ParamUtil.getBoolean(req, "passwordReset");

			String tempOldScreenName = user.getScreenName();

			user = UserServiceUtil.updateUser(
				user.getUserId(), oldPassword, newPassword1, newPassword2,
				passwordReset, screenName, emailAddress, languageId, timeZoneId,
				greeting, comments, firstName, middleName, lastName, prefixId,
				suffixId, male, birthdayMonth, birthdayDay, birthdayYear, smsSn,
				aimSn, icqSn, jabberSn, msnSn, skypeSn, ymSn, jobTitle,
				organizationIds);

			if (!tempOldScreenName.equals(user.getScreenName())) {
				oldScreenName = tempOldScreenName;
			}

			if (user.getUserId() == themeDisplay.getUserId()) {

				// Reset the locale

				HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(
					req);
				HttpSession httpSes = httpReq.getSession();

				httpSes.removeAttribute(Globals.LOCALE_KEY);

				// Clear cached portlet responses

				PortletSession ses = req.getPortletSession();

				CachePortlet.clearResponses(ses);

				// Password

				if (Validator.isNotNull(newPassword1)) {
					ses.setAttribute(
						WebKeys.USER_PASSWORD, newPassword1,
						PortletSession.APPLICATION_SCOPE);
				}
			}

		}

		return new Object[] {user, oldScreenName};
	}

}