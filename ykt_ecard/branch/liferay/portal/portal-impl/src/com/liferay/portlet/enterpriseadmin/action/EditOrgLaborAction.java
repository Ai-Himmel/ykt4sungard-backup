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

import com.liferay.portal.NoSuchListTypeException;
import com.liferay.portal.NoSuchOrgLaborException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.OrgLaborServiceUtil;
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
 * <a href="EditOrgLaborAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditOrgLaborAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateOrgLabor(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteOrgLabor(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchOrgLaborException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.enterprise_admin.error");
			}
			else if (e instanceof NoSuchListTypeException) {
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
			ActionUtil.getOrgLabor(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchOrgLaborException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.enterprise_admin.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.enterprise_admin.edit_org_labor"));
	}

	protected void deleteOrgLabor(ActionRequest req) throws Exception {
		long orgLaborId = ParamUtil.getLong(req, "orgLaborId");

		OrgLaborServiceUtil.deleteOrgLabor(orgLaborId);
	}

	protected void updateOrgLabor(ActionRequest req) throws Exception {
		long orgLaborId = ParamUtil.getLong(req, "orgLaborId");

		long organizationId = ParamUtil.getLong(req, "organizationId");
		int typeId = ParamUtil.getInteger(req, "typeId");

		int sunOpen = ParamUtil.getInteger(req, "sunOpen");
		int sunClose = ParamUtil.getInteger(req, "sunClose");

		int monOpen = ParamUtil.getInteger(req, "monOpen");
		int monClose = ParamUtil.getInteger(req, "monClose");

		int tueOpen = ParamUtil.getInteger(req, "tueOpen");
		int tueClose = ParamUtil.getInteger(req, "tueClose");

		int wedOpen = ParamUtil.getInteger(req, "wedOpen");
		int wedClose = ParamUtil.getInteger(req, "wedClose");

		int thuOpen = ParamUtil.getInteger(req, "thuOpen");
		int thuClose = ParamUtil.getInteger(req, "thuClose");

		int friOpen = ParamUtil.getInteger(req, "friOpen");
		int friClose = ParamUtil.getInteger(req, "friClose");

		int satOpen = ParamUtil.getInteger(req, "satOpen");
		int satClose = ParamUtil.getInteger(req, "satClose");

		if (orgLaborId <= 0) {

			// Add organization labor

			OrgLaborServiceUtil.addOrgLabor(
				organizationId, typeId, sunOpen, sunClose, monOpen, monClose,
				tueOpen, tueClose, wedOpen, wedClose, thuOpen, thuClose,
				friOpen, friClose, satOpen, satClose);
		}
		else {

			// Update organization labor

			OrgLaborServiceUtil.updateOrgLabor(
				orgLaborId, sunOpen, sunClose, monOpen, monClose, tueOpen,
				tueClose, wedOpen, wedClose, thuOpen, thuClose, friOpen,
				friClose, satOpen, satClose);
		}
	}

}