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

import com.liferay.portal.AccountNameException;
import com.liferay.portal.CompanyMxException;
import com.liferay.portal.CompanyVirtualHostException;
import com.liferay.portal.CompanyWebIdException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.CompanyServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditCompanyAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditCompanyAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateCompany(req);
				updateDisplay(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof PrincipalException) {
				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.enterprise_admin.error");
			}
			else if (e instanceof AccountNameException ||
					 e instanceof CompanyMxException ||
					 e instanceof CompanyVirtualHostException ||
					 e instanceof CompanyWebIdException) {

				SessionErrors.add(req, e.getClass().getName(), e);

				setForward(req, "portlet.enterprise_admin.view");
			}
			else {
				throw e;
			}
		}
	}

	protected void updateCompany(ActionRequest req) throws Exception {
		long companyId = PortalUtil.getCompanyId(req);

		String virtualHost = ParamUtil.getString(req, "virtualHost");
		String mx = ParamUtil.getString(req, "mx");
		String name = ParamUtil.getString(req, "name");
		String legalName = ParamUtil.getString(req, "legalName");
		String legalId = ParamUtil.getString(req, "legalId");
		String legalType = ParamUtil.getString(req, "legalType");
		String sicCode = ParamUtil.getString(req, "sicCode");
		String tickerSymbol = ParamUtil.getString(req, "tickerSymbol");
		String industry = ParamUtil.getString(req, "industry");
		String type = ParamUtil.getString(req, "type");
		String size = ParamUtil.getString(req, "size");

		CompanyServiceUtil.updateCompany(
			companyId, virtualHost, mx, name, legalName, legalId, legalType,
			sicCode, tickerSymbol, industry, type, size);
	}

	protected void updateDisplay(ActionRequest req) throws Exception {
		Company company = PortalUtil.getCompany(req);

		String languageId = ParamUtil.getString(req, "languageId");
		String timeZoneId = ParamUtil.getString(req, "timeZoneId");
		boolean communityLogo = ParamUtil.getBoolean(req, "communityLogo");

		CompanyServiceUtil.updateDisplay(
			company.getCompanyId(), languageId, timeZoneId);

		CompanyServiceUtil.updateSecurity(
			company.getCompanyId(), company.getAuthType(),
			company.isAutoLogin(), company.isSendPassword(),
			company.isStrangers(), company.isStrangersWithMx(),
			company.isStrangersVerify(), communityLogo);
	}

}