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

package com.liferay.portlet.admin.action;

import com.liferay.portal.CompanyMxException;
import com.liferay.portal.CompanyVirtualHostException;
import com.liferay.portal.CompanyWebIdException;
import com.liferay.portal.NoSuchCompanyException;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.CompanyServiceUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditInstanceAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditInstanceAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			updateInstance(req);

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchCompanyException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.admin.error");
			}
			else if (e instanceof CompanyMxException ||
					 e instanceof CompanyVirtualHostException ||
					 e instanceof CompanyWebIdException) {

				SessionErrors.add(req, e.getClass().getName());
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
			ActionUtil.getInstance(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchCompanyException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.admin.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.admin.edit_instance"));
	}

	protected void updateInstance(ActionRequest req) throws Exception {
		long companyId = ParamUtil.getLong(req, "companyId");

		String webId = ParamUtil.getString(req, "webId");
		String virtualHost = ParamUtil.getString(req, "virtualHost");
		String mx = ParamUtil.getString(req, "mx");

		if (companyId <= 0) {

			// Add instance

			Company company = CompanyServiceUtil.addCompany(
				webId, virtualHost, mx);

			ServletContext ctx = (ServletContext)req.getAttribute(WebKeys.CTX);

			PortalInstances.initCompany(ctx, company.getWebId());
		}
		else {

			// Update instance

			CompanyServiceUtil.updateCompany(companyId, virtualHost, mx);
		}
	}

}