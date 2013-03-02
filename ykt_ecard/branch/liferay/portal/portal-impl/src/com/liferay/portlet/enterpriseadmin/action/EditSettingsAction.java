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

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.impl.RoleImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.security.ldap.PortalLDAPUtil;
import com.liferay.portal.service.CompanyServiceUtil;
import com.liferay.portal.service.RoleLocalServiceUtil;
import com.liferay.portal.servlet.filters.sso.cas.CASFilter;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.ldap.LDAPUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditSettingsAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Scott Lee
 *
 */
public class EditSettingsAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		long companyId = PortalUtil.getCompanyId(req);
		long userId = PortalUtil.getUserId(req);

		if (!RoleLocalServiceUtil.hasUserRole(
				userId, companyId, RoleImpl.ADMINISTRATOR, true)) {

			SessionErrors.add(req, PrincipalException.class.getName());

			setForward(req, "portlet.enterprise_admin.error");

			return;
		}

		PortletPreferences prefs = PrefsPropsUtil.getPreferences(companyId);

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (cmd.equals("updateCAS")) {
			updateCAS(req, companyId, prefs);
		}
		else if (cmd.equals("updateDefaultGroupsAndRoles")) {
			updateDefaultGroupsAndRoles(req, prefs);
		}
		else if (cmd.equals("updateEmails")) {
			updateEmails(req, prefs);
		}
		else if (cmd.equals("updateLdap")) {
			updateLdap(req, companyId, prefs);
		}
		else if (cmd.equals("updateMailHostNames")) {
			updateMailHostNames(req, prefs);
		}
		else if (cmd.equals("updateNtlm")) {
			updateNtlm(req, companyId, prefs);
		}
		else if (cmd.equals("updateOpenId")) {
			updateOpenId(req, prefs);
		}
		else if (cmd.equals("updateOpenSSO")) {
			updateOpenSSO(req, companyId, prefs);
		}
		else if (cmd.equals("updateReservedUsers")) {
			updateReservedUsers(req, prefs);
		}
		else if (cmd.equals("updateSecurity")) {
			updateSecurity(req);
		}

		if (SessionErrors.isEmpty(req)) {
			if (!cmd.equals("updateLdap") && !cmd.equals("updateSecurity")) {
				prefs.store();
			}

			sendRedirect(req, res);
		}
		else {
			setForward(req, "portlet.enterprise_admin.view");
		}
	}

	protected void updateCAS(
			ActionRequest req, long companyId, PortletPreferences prefs)
		throws Exception {

		boolean enabled = ParamUtil.getBoolean(req, "enabled");
		boolean importFromLdap = ParamUtil.getBoolean(req, "importFromLdap");
		String loginUrl = ParamUtil.getString(req, "loginUrl");
		String logoutUrl = ParamUtil.getString(req, "logoutUrl");
		String serverName = ParamUtil.getString(req, "serverName");
		String serviceUrl = ParamUtil.getString(req, "serviceUrl");
		String validateUrl = ParamUtil.getString(req, "validateUrl");

		prefs.setValue(
			PropsUtil.CAS_AUTH_ENABLED, String.valueOf(enabled));
		prefs.setValue(
			PropsUtil.CAS_IMPORT_FROM_LDAP, String.valueOf(importFromLdap));
		prefs.setValue(PropsUtil.CAS_LOGIN_URL, loginUrl);
		prefs.setValue(PropsUtil.CAS_LOGOUT_URL, logoutUrl);
		prefs.setValue(PropsUtil.CAS_SERVER_NAME, serverName);
		prefs.setValue(PropsUtil.CAS_SERVICE_URL, serviceUrl);
		prefs.setValue(PropsUtil.CAS_VALIDATE_URL, validateUrl);

		prefs.store();

		CASFilter.reload(companyId);
	}

	protected void updateDefaultGroupsAndRoles(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String defaultGroupNames = ParamUtil.getString(
			req, "defaultGroupNames");
		String defaultRoleNames = ParamUtil.getString(req, "defaultRoleNames");
		String defaultUserGroupNames = ParamUtil.getString(
			req, "defaultUserGroupNames");

		prefs.setValue(PropsUtil.ADMIN_DEFAULT_GROUP_NAMES, defaultGroupNames);
		prefs.setValue(PropsUtil.ADMIN_DEFAULT_ROLE_NAMES, defaultRoleNames);
		prefs.setValue(
			PropsUtil.ADMIN_DEFAULT_USER_GROUP_NAMES, defaultUserGroupNames);
	}

	protected void updateEmails(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String tabs3 = ParamUtil.getString(req, "tabs3");

		if (tabs3.equals("account-created-notification")) {
			String emailUserAddedEnabled = ParamUtil.getString(
				req, "emailUserAddedEnabled");
			String emailUserAddedSubject = ParamUtil.getString(
				req, "emailUserAddedSubject");
			String emailUserAddedBody = ParamUtil.getString(
				req, "emailUserAddedBody");

			if (Validator.isNull(emailUserAddedSubject)) {
				SessionErrors.add(req, "emailUserAddedSubject");
			}
			else if (Validator.isNull(emailUserAddedBody)) {
				SessionErrors.add(req, "emailUserAddedBody");
			}
			else {
				prefs.setValue(
					PropsUtil.ADMIN_EMAIL_USER_ADDED_ENABLED,
					emailUserAddedEnabled);
				prefs.setValue(
					PropsUtil.ADMIN_EMAIL_USER_ADDED_SUBJECT,
					emailUserAddedSubject);
				prefs.setValue(
					PropsUtil.ADMIN_EMAIL_USER_ADDED_BODY, emailUserAddedBody);
			}
		}
		else if (tabs3.equals("password-changed-notification")) {
			String emailPasswordSentEnabled = ParamUtil.getString(
				req, "emailPasswordSentEnabled");
			String emailPasswordSentSubject = ParamUtil.getString(
				req, "emailPasswordSentSubject");
			String emailPasswordSentBody = ParamUtil.getString(
				req, "emailPasswordSentBody");

			if (Validator.isNull(emailPasswordSentSubject)) {
				SessionErrors.add(req, "emailPasswordSentSubject");
			}
			else if (Validator.isNull(emailPasswordSentBody)) {
				SessionErrors.add(req, "emailPasswordSentBody");
			}
			else {
				prefs.setValue(
					PropsUtil.ADMIN_EMAIL_PASSWORD_SENT_ENABLED,
					emailPasswordSentEnabled);
				prefs.setValue(
					PropsUtil.ADMIN_EMAIL_PASSWORD_SENT_SUBJECT,
					emailPasswordSentSubject);
				prefs.setValue(
					PropsUtil.ADMIN_EMAIL_PASSWORD_SENT_BODY,
					emailPasswordSentBody);
			}
		}
		else {
			String emailFromName = ParamUtil.getString(req, "emailFromName");
			String emailFromAddress = ParamUtil.getString(
				req, "emailFromAddress");

			if (Validator.isNull(emailFromName)) {
				SessionErrors.add(req, "emailFromName");
			}
			else if (!Validator.isEmailAddress(emailFromAddress)) {
				SessionErrors.add(req, "emailFromAddress");
			}
			else {
				prefs.setValue(PropsUtil.ADMIN_EMAIL_FROM_NAME, emailFromName);
				prefs.setValue(
					PropsUtil.ADMIN_EMAIL_FROM_ADDRESS, emailFromAddress);
			}
		}
	}

	protected void updateLdap(
			ActionRequest req, long companyId, PortletPreferences prefs)
		throws Exception {

		boolean enabled = ParamUtil.getBoolean(req, "enabled");
		boolean required = ParamUtil.getBoolean(req, "required");
		String baseProviderURL = ParamUtil.getString(req, "baseProviderURL");
		String baseDN = ParamUtil.getString(req, "baseDN");
		String principal = ParamUtil.getString(req, "principal");
		String credentials = ParamUtil.getString(req, "credentials");
		String searchFilter = ParamUtil.getString(req, "searchFilter");
		String userDefaultObjectClasses = ParamUtil.getString(
			req, "userDefaultObjectClasses");

		String userMappings =
			"screenName=" + ParamUtil.getString(req, "userMappingScreenName") +
			"\npassword=" + ParamUtil.getString(req, "userMappingPassword") +
			"\nemailAddress=" +
				ParamUtil.getString(req, "userMappingEmailAddress") +
			"\nfullName=" + ParamUtil.getString(req, "userMappingFullName") +
			"\nfirstName=" + ParamUtil.getString(req, "userMappingFirstName") +
			"\nlastName=" + ParamUtil.getString(req, "userMappingLastName") +
			"\njobTitle=" + ParamUtil.getString(req, "userMappingJobTitle") +
			"\ngroup=" + ParamUtil.getString(req, "userMappingGroup");

		String groupMappings =
			"groupName=" + ParamUtil.getString(req, "groupMappingGroupName") +
			"\ndescription=" +
				ParamUtil.getString(req, "groupMappingDescription") +
			"\nuser=" + ParamUtil.getString(req, "groupMappingUser");

		boolean importEnabled = ParamUtil.getBoolean(req, "importEnabled");
		boolean importOnStartup = ParamUtil.getBoolean(req, "importOnStartup");
		long importInterval = ParamUtil.getLong(req, "importInterval");
		String importUserSearchFilter = ParamUtil.getString(
			req, "importUserSearchFilter");
		String importGroupSearchFilter = ParamUtil.getString(
			req, "importGroupSearchFilter");
		boolean exportEnabled = ParamUtil.getBoolean(req, "exportEnabled");
		String usersDN = ParamUtil.getString(req, "usersDN");
		String groupsDN = ParamUtil.getString(req, "groupsDN");
		boolean passwordPolicyEnabled = ParamUtil.getBoolean(
			req, "passwordPolicyEnabled");

		try {
			if (enabled) {
				String fullProviderURL = LDAPUtil.getFullProviderURL(
					baseProviderURL, baseDN);

				PortalLDAPUtil.getContext(
					companyId, fullProviderURL, principal, credentials);
			}
		}
		catch (Exception e) {
			SessionErrors.add(req, "ldapAuthentication");

			return;
		}

		prefs.setValue(PropsUtil.LDAP_AUTH_ENABLED, String.valueOf(enabled));
		prefs.setValue(PropsUtil.LDAP_AUTH_REQUIRED, String.valueOf(required));
		prefs.setValue(PropsUtil.LDAP_BASE_PROVIDER_URL, baseProviderURL);
		prefs.setValue(PropsUtil.LDAP_BASE_DN, baseDN);
		prefs.setValue(PropsUtil.LDAP_SECURITY_PRINCIPAL, principal);
		prefs.setValue(PropsUtil.LDAP_SECURITY_CREDENTIALS, credentials);
		prefs.setValue(PropsUtil.LDAP_AUTH_SEARCH_FILTER, searchFilter);
		prefs.setValue(
			PropsUtil.LDAP_USER_DEFAULT_OBJECT_CLASSES,
			userDefaultObjectClasses);
		prefs.setValue(PropsUtil.LDAP_USER_MAPPINGS, userMappings);
		prefs.setValue(PropsUtil.LDAP_GROUP_MAPPINGS, groupMappings);
		prefs.setValue(
			PropsUtil.LDAP_IMPORT_ENABLED, String.valueOf(importEnabled));
		prefs.setValue(
			PropsUtil.LDAP_IMPORT_ON_STARTUP, String.valueOf(importOnStartup));
		prefs.setValue(
			PropsUtil.LDAP_IMPORT_INTERVAL, String.valueOf(importInterval));
		prefs.setValue(
			PropsUtil.LDAP_IMPORT_USER_SEARCH_FILTER, importUserSearchFilter);
		prefs.setValue(
			PropsUtil.LDAP_IMPORT_GROUP_SEARCH_FILTER, importGroupSearchFilter);
		prefs.setValue(
			PropsUtil.LDAP_EXPORT_ENABLED, String.valueOf(exportEnabled));
		prefs.setValue(PropsUtil.LDAP_USERS_DN, usersDN);
		prefs.setValue(PropsUtil.LDAP_GROUPS_DN, groupsDN);
		prefs.setValue(
			PropsUtil.LDAP_PASSWORD_POLICY_ENABLED,
			String.valueOf(passwordPolicyEnabled));

		prefs.store();
	}

	protected void updateMailHostNames(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String mailHostNames = ParamUtil.getString(req, "mailHostNames");

		prefs.setValue(PropsUtil.ADMIN_MAIL_HOST_NAMES, mailHostNames);
	}

	protected void updateNtlm(
			ActionRequest req, long companyId, PortletPreferences prefs)
		throws Exception {

		boolean enabled = ParamUtil.getBoolean(req, "enabled");
		String domainController = ParamUtil.getString(req, "domainController");
		String domain = ParamUtil.getString(req, "domain");

		prefs.setValue(
			PropsUtil.NTLM_AUTH_ENABLED, String.valueOf(enabled));
		prefs.setValue(PropsUtil.NTLM_DOMAIN_CONTROLLER, domainController);
		prefs.setValue(PropsUtil.NTLM_DOMAIN, domain);

		prefs.store();
	}

	protected void updateOpenId(ActionRequest req, PortletPreferences prefs)
		throws Exception {

		boolean enabled = ParamUtil.getBoolean(req, "enabled");

		prefs.setValue(PropsUtil.OPEN_ID_AUTH_ENABLED, String.valueOf(enabled));

		prefs.store();
	}

	protected void updateOpenSSO(
			ActionRequest req, long companyId, PortletPreferences prefs)
		throws Exception {

		boolean enabled = ParamUtil.getBoolean(req, "enabled");
		String loginUrl = ParamUtil.getString(req, "loginUrl");
		String logoutUrl = ParamUtil.getString(req, "logoutUrl");
		String serviceUrl = ParamUtil.getString(req, "serviceUrl");
		String subjectCookieName = ParamUtil.getString(
			req, "subjectCookieName");

		prefs.setValue(
			PropsUtil.OPEN_SSO_AUTH_ENABLED, String.valueOf(enabled));
		prefs.setValue(PropsUtil.OPEN_SSO_LOGIN_URL, loginUrl);
		prefs.setValue(PropsUtil.OPEN_SSO_LOGOUT_URL, logoutUrl);
		prefs.setValue(PropsUtil.OPEN_SSO_SERVICE_URL, serviceUrl);
		prefs.setValue(
			PropsUtil.OPEN_SSO_SUBJECT_COOKIE_NAME, subjectCookieName);

		prefs.store();
	}

	protected void updateReservedUsers(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String reservedScreenNames = ParamUtil.getString(
			req, "reservedScreenNames");
		String reservedEmailAddresses = ParamUtil.getString(
			req, "reservedEmailAddresses");

		prefs.setValue(
			PropsUtil.ADMIN_RESERVED_SCREEN_NAMES, reservedScreenNames);
		prefs.setValue(
			PropsUtil.ADMIN_RESERVED_EMAIL_ADDRESSES, reservedEmailAddresses);
	}

	protected void updateSecurity(ActionRequest req) throws Exception {
		Company company = PortalUtil.getCompany(req);

		String authType = ParamUtil.getString(req, "authType");
		boolean autoLogin = ParamUtil.getBoolean(req, "autoLogin");
		boolean sendPassword = ParamUtil.getBoolean(req, "sendPassword");
		boolean strangers = ParamUtil.getBoolean(req, "strangers");
		boolean strangersWithMx = ParamUtil.getBoolean(req, "strangersWithMx");
		boolean strangersVerify = ParamUtil.getBoolean(req, "strangersVerify");

		CompanyServiceUtil.updateSecurity(
			company.getCompanyId(), authType, autoLogin, sendPassword,
			strangers, strangersWithMx, strangersVerify,
			company.isCommunityLogo());
	}

}