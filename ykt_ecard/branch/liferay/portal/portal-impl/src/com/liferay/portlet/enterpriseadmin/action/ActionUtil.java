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

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.Address;
import com.liferay.portal.model.EmailAddress;
import com.liferay.portal.model.OrgLabor;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.model.Phone;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.Website;
import com.liferay.portal.service.AddressServiceUtil;
import com.liferay.portal.service.EmailAddressServiceUtil;
import com.liferay.portal.service.OrgLaborServiceUtil;
import com.liferay.portal.service.OrganizationServiceUtil;
import com.liferay.portal.service.PasswordPolicyLocalServiceUtil;
import com.liferay.portal.service.PhoneServiceUtil;
import com.liferay.portal.service.RoleServiceUtil;
import com.liferay.portal.service.UserGroupServiceUtil;
import com.liferay.portal.service.WebsiteServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class ActionUtil {

	public static void getAddress(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getAddress(httpReq);
	}

	public static void getAddress(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getAddress(httpReq);
	}

	public static void getAddress(HttpServletRequest req) throws Exception {
		long addressId = ParamUtil.getLong(req, "addressId");

		Address address = null;

		if (addressId > 0) {
			address = AddressServiceUtil.getAddress(addressId);
		}

		req.setAttribute(WebKeys.ADDRESS, address);
	}

	public static void getEmailAddress(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getEmailAddress(httpReq);
	}

	public static void getEmailAddress(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getEmailAddress(httpReq);
	}

	public static void getEmailAddress(
		HttpServletRequest req) throws Exception {

		long emailAddressId = ParamUtil.getLong(req, "emailAddressId");

		EmailAddress emailAddress = null;

		if (emailAddressId > 0) {
			emailAddress =
				EmailAddressServiceUtil.getEmailAddress(emailAddressId);
		}

		req.setAttribute(WebKeys.EMAIL_ADDRESS, emailAddress);
	}

	public static void getPhone(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getPhone(httpReq);
	}

	public static void getPhone(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getPhone(httpReq);
	}

	public static void getPhone(HttpServletRequest req) throws Exception {
		long phoneId = ParamUtil.getLong(req, "phoneId");

		Phone phone = null;

		if (phoneId > 0) {
			phone = PhoneServiceUtil.getPhone(phoneId);
		}

		req.setAttribute(WebKeys.PHONE, phone);
	}

	public static void getOrganization(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getOrganization(httpReq);
	}

	public static void getOrganization(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getOrganization(httpReq);
	}

	public static void getOrganization(HttpServletRequest req)
		throws Exception {

		long organizationId = ParamUtil.getLong(req, "organizationId");

		Organization organization = null;

		if (organizationId > 0) {
			organization =
				OrganizationServiceUtil.getOrganization(organizationId);
		}

		req.setAttribute(WebKeys.ORGANIZATION, organization);
	}

	public static void getOrgLabor(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getOrgLabor(httpReq);
	}

	public static void getOrgLabor(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getOrgLabor(httpReq);
	}

	public static void getOrgLabor(HttpServletRequest req) throws Exception {
		long orgLaborId = ParamUtil.getLong(req, "orgLaborId");

		OrgLabor orgLabor = null;

		if (orgLaborId > 0) {
			orgLabor = OrgLaborServiceUtil.getOrgLabor(orgLaborId);
		}

		req.setAttribute(WebKeys.ORG_LABOR, orgLabor);
	}

	public static void getPasswordPolicy(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getPasswordPolicy(httpReq);
	}

	public static void getPasswordPolicy(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getPasswordPolicy(httpReq);
	}

	public static void getPasswordPolicy(HttpServletRequest req)
		throws Exception {

		long passwordPolicyId = ParamUtil.getLong(req, "passwordPolicyId");

		PasswordPolicy passwordPolicy = null;

		if (passwordPolicyId > 0) {
			passwordPolicy = PasswordPolicyLocalServiceUtil.getPasswordPolicy(
				passwordPolicyId);
		}

		req.setAttribute(WebKeys.PASSWORD_POLICY, passwordPolicy);
	}

	public static void getRole(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getRole(httpReq);
	}

	public static void getRole(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getRole(httpReq);
	}

	public static void getRole(HttpServletRequest req)
		throws Exception {

		long roleId = ParamUtil.getLong(req, "roleId");

		Role role = null;

		if (roleId > 0) {
			role = RoleServiceUtil.getRole(roleId);
		}

		req.setAttribute(WebKeys.ROLE, role);
	}

	public static void getUserGroup(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getUserGroup(httpReq);
	}

	public static void getUserGroup(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getUserGroup(httpReq);
	}

	public static void getUserGroup(HttpServletRequest req)
		throws Exception {

		long userGroupId = ParamUtil.getLong(req, "userGroupId");

		UserGroup userGroup = null;

		if (userGroupId > 0) {
			userGroup = UserGroupServiceUtil.getUserGroup(userGroupId);
		}

		req.setAttribute(WebKeys.USER_GROUP, userGroup);
	}

	public static void getWebsite(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getWebsite(httpReq);
	}

	public static void getWebsite(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getWebsite(httpReq);
	}

	public static void getWebsite(HttpServletRequest req) throws Exception {
		long websiteId = ParamUtil.getLong(req, "websiteId");

		Website website = null;

		if (websiteId > 0) {
			website = WebsiteServiceUtil.getWebsite(websiteId);
		}

		req.setAttribute(WebKeys.WEBSITE, website);
	}

}