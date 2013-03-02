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

package com.liferay.portlet.admin.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Company;
import com.liferay.portal.service.spring.CompanyServiceUtil;
import com.liferay.portal.service.spring.PropertiesServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import java.util.Properties;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="UpdateCompanyAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class UpdateCompanyAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			_updateCompany(req, res);
		}
		catch (Exception e) {
			if (e != null &&
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.admin.error");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
	}

	private void _updateCompany(ActionRequest req, ActionResponse res)
		throws Exception {

		String portalURL = ParamUtil.getString(req, "company_portal_url");
		String homeURL = ParamUtil.getString(req, "company_home_url");
		String mx = ParamUtil.getString(req, "company_mx");

		String name = ParamUtil.getString(req, "company_name");
		String shortName = ParamUtil.getString(req, "company_short_name");

		String type = ParamUtil.getString(req, "company_type");
		String size = ParamUtil.getString(req, "company_size");

		String street = ParamUtil.getString(req, "company_street");
		String city = ParamUtil.getString(req, "company_city");
		String state = ParamUtil.getString(req, "company_state");
		String zip = ParamUtil.getString(req, "company_zip");
		String phone = ParamUtil.getString(req, "company_phone");
		String fax = ParamUtil.getString(req, "company_fax");
		String emailAddress = ParamUtil.getString(req, "company_email_address");

		String authType = ParamUtil.getString(
			req, "company_auth_type", Company.AUTH_TYPE_EA);
		boolean autoLogin = ParamUtil.get(req, "company_auto_login", true);
		boolean strangers = ParamUtil.get(req, "company_strangers", false);

		String languageId = ParamUtil.getString(req, "company_language_id");
		String timeZoneId = ParamUtil.getString(req, "company_tz_id");
		String themeId = ParamUtil.getString(req, "company_theme_id");
		String colorSchemeId = ParamUtil.getString(
			req, "company_color_scheme_id");
		String resolution = ParamUtil.getString(req, "company_resolution");

		Company company = CompanyServiceUtil.updateCompany(
			portalURL, homeURL, mx, name, shortName, type, size, street, city,
			state, zip, phone, fax, emailAddress);

		CompanyServiceUtil.updateDefaultUser(
			languageId, timeZoneId, themeId, colorSchemeId, resolution);

		Properties propertiesObj =
			PropertiesServiceUtil.getPortalProperties(company.getCompanyId());

		propertiesObj.setProperty(
			PropsUtil.COMPANY_SECURITY_AUTH_TYPE, authType);
		propertiesObj.setProperty(
			PropsUtil.COMPANY_SECURITY_AUTO_LOGIN, Boolean.toString(autoLogin));
		propertiesObj.setProperty(
			PropsUtil.COMPANY_SECURITY_STRANGERS, Boolean.toString(strangers));

		PropertiesServiceUtil.updatePortalProperties(
			company.getCompanyId(), propertiesObj);

		// Session messages

		SessionMessages.add(req, UpdateCompanyAction.class.getName());

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}