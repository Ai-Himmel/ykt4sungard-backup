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

package com.liferay.portlet.project.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.project.FirmNameException;
import com.liferay.portlet.project.FirmURLException;
import com.liferay.portlet.project.NoSuchFirmException;
import com.liferay.portlet.project.RequiredFirmException;
import com.liferay.portlet.project.model.ProjFirm;
import com.liferay.portlet.project.service.spring.ProjFirmServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditFirmAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.4 $
 *
 */
public class EditFirmAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editFirm(req);

				_updateFirm(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof FirmNameException ||
					e instanceof FirmURLException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.project.edit_firm");
				}
				else if (e != null &&
						 e instanceof NoSuchFirmException ||
						 e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.project.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteFirm(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchFirmException ||
					e instanceof PrincipalException ||
					e instanceof RequiredFirmException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.project.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.EDIT)) {
			try {
				_editFirm(req);

				setForward(req, "portlet.project.edit_firm");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchFirmException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.project.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals("add_note")) {
			try {
				_addFirmNote(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchFirmException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.project.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals("delete_note")) {
			try {
				_deleteFirmNote(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchFirmException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.project.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.project.edit_firm");
		}
	}

	private void _addFirmNote(ActionRequest req, ActionResponse res)
		throws Exception {

		String firmId = ParamUtil.getString(req, "firm_id");

		String noteContent = ParamUtil.getString(req, "note_content");

		// Add note

		ProjFirmServiceUtil.addNote(firmId, noteContent);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _deleteFirm(ActionRequest req, ActionResponse res)
		throws Exception {

		String firmId = ParamUtil.getString(req, "firm_id");

		ProjFirmServiceUtil.deleteFirm(firmId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _deleteFirmNote(ActionRequest req, ActionResponse res)
		throws Exception {

		String firmId = ParamUtil.getString(req, "firm_id");

		String noteId = ParamUtil.getString(req, "note_id");

		// Delete note

		ProjFirmServiceUtil.deleteNote(firmId, noteId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editFirm(ActionRequest req) throws Exception {
		String firmId = req.getParameter("firm_id");

		ProjFirm firm = null;

		if (Validator.isNotNull(firmId)) {
			firm = ProjFirmServiceUtil.getFirm(firmId);
		}

		req.setAttribute(WebKeys.PROJ_FIRM, firm);
	}

	private void _updateFirm(ActionRequest req, ActionResponse res)
		throws Exception {

		String firmId = ParamUtil.getString(req, "firm_id");

		String name = ParamUtil.getString(req, "firm_name");
		String description = ParamUtil.getString(req, "firm_desc");
		String url = ParamUtil.getString(req, "firm_url");

		if (Validator.isNull(firmId)) {

			// Add firm

			ProjFirmServiceUtil.addFirm(name, description, url);
		}
		else {

			// Update firm

			ProjFirmServiceUtil.updateFirm(firmId, name, description, url);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}