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

import com.liferay.portal.DuplicateOrganizationException;
import com.liferay.portal.NoSuchCountryException;
import com.liferay.portal.NoSuchListTypeException;
import com.liferay.portal.NoSuchOrganizationException;
import com.liferay.portal.OrganizationNameException;
import com.liferay.portal.OrganizationParentException;
import com.liferay.portal.RequiredOrganizationException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.impl.OrganizationImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.OrganizationServiceUtil;
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
 * <a href="EditOrganizationAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditOrganizationAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			Organization organization = null;

			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				organization = updateOrganization(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteOrganizations(req);
			}

			String redirect = ParamUtil.getString(req, "redirect");

			if (organization != null) {
				redirect += organization.getOrganizationId();
			}

			sendRedirect(req, res, redirect);
		}
		catch (Exception e) {
			if (e instanceof NoSuchOrganizationException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.enterprise_admin.error");
			}
			else if (e instanceof DuplicateOrganizationException ||
					 e instanceof NoSuchCountryException ||
					 e instanceof NoSuchListTypeException ||
					 e instanceof OrganizationNameException ||
					 e instanceof OrganizationParentException ||
					 e instanceof RequiredOrganizationException) {

				SessionErrors.add(req, e.getClass().getName());

				if (e instanceof RequiredOrganizationException) {
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
			ActionUtil.getOrganization(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchOrganizationException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.enterprise_admin.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.enterprise_admin.edit_organization"));
	}

	protected void deleteOrganizations(ActionRequest req) throws Exception {
		long[] deleteOrganizationIds = StringUtil.split(
			ParamUtil.getString(req, "deleteOrganizationIds"), 0L);

		for (int i = 0; i < deleteOrganizationIds.length; i++) {
			OrganizationServiceUtil.deleteOrganization(
				deleteOrganizationIds[i]);
		}
	}

	protected Organization updateOrganization(ActionRequest req)
		throws Exception {

		long organizationId = ParamUtil.getLong(req, "organizationId");

		long parentOrganizationId = ParamUtil.getLong(
			req, "parentOrganizationId",
			OrganizationImpl.DEFAULT_PARENT_ORGANIZATION_ID);
		String name = ParamUtil.getString(req, "name");
		boolean recursable = ParamUtil.getBoolean(req, "recursable");
		int statusId = ParamUtil.getInteger(req, "statusId");
		int type = ParamUtil.getInteger(req, "type");
		long regionId = ParamUtil.getLong(req, "regionId");
		long countryId = ParamUtil.getLong(req, "countryId");
		String comments = ParamUtil.getString(req, "comments");

		Organization organization = null;

		if (organizationId <= 0) {

			// Add organization

			organization = OrganizationServiceUtil.addOrganization(
				parentOrganizationId, name, type, recursable, regionId,
				countryId, statusId, comments);
		}
		else {

			// Update organization

			organization = OrganizationServiceUtil.updateOrganization(
				organizationId, parentOrganizationId, name, type,
				recursable, regionId, countryId, statusId, comments);
		}

		return organization;
	}

}