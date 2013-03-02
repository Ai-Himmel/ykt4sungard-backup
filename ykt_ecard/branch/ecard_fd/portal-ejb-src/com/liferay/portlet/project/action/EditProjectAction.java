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
import com.liferay.portlet.project.DuplicateProjectException;
import com.liferay.portlet.project.NoSuchFirmException;
import com.liferay.portlet.project.NoSuchProjectException;
import com.liferay.portlet.project.ProjectCodeException;
import com.liferay.portlet.project.ProjectNameException;
import com.liferay.portlet.project.RequiredProjectException;
import com.liferay.portlet.project.model.ProjFirm;
import com.liferay.portlet.project.model.ProjProject;
import com.liferay.portlet.project.service.spring.ProjFirmServiceUtil;
import com.liferay.portlet.project.service.spring.ProjProjectServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditProjectAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.4 $
 *
 */
public class EditProjectAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editProject(req);

				_updateProject(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof DuplicateProjectException ||
					e instanceof ProjectCodeException ||
					e instanceof ProjectNameException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.project.edit_project");
				}
				else if (e != null &&
						 e instanceof NoSuchFirmException ||
						 e instanceof NoSuchProjectException ||
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
				_deleteProject(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchProjectException ||
					e instanceof PrincipalException ||
					e instanceof RequiredProjectException) {

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
				_editProject(req);

				setForward(req, "portlet.project.edit_project");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchFirmException ||
					e instanceof NoSuchProjectException ||
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
				_addProjectNote(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchProjectException ||
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
				_deleteProjectNote(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchProjectException ||
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
			setForward(req, "portlet.project.edit_project");
		}
	}

	private void _addProjectNote(ActionRequest req, ActionResponse res)
		throws Exception {

		String projectId = ParamUtil.getString(req, "project_id");

		String noteContent = ParamUtil.getString(req, "note_content");

		// Add note

		ProjProjectServiceUtil.addNote(projectId, noteContent);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _deleteProject(ActionRequest req, ActionResponse res)
		throws Exception {

		String projectId = ParamUtil.getString(req, "project_id");

		ProjProjectServiceUtil.deleteProject(projectId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _deleteProjectNote(ActionRequest req, ActionResponse res)
		throws Exception {

		String projectId = ParamUtil.getString(req, "project_id");

		String noteId = ParamUtil.getString(req, "note_id");

		// Delete note

		ProjProjectServiceUtil.deleteNote(projectId, noteId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editProject(ActionRequest req) throws Exception {
		String projectId = req.getParameter("project_id");

		ProjProject project = null;

		if (Validator.isNotNull(projectId)) {
			project = ProjProjectServiceUtil.getProject(projectId);
		}

		String firmId = ParamUtil.getString(req, "firm_id");
		if (project != null) {
			firmId = project.getFirmId();
		}

		ProjFirm firm = ProjFirmServiceUtil.getFirm(firmId);

		req.setAttribute(WebKeys.PROJ_PROJECT, project);
		req.setAttribute(WebKeys.PROJ_FIRM, firm);
	}

	private void _updateProject(ActionRequest req, ActionResponse res)
		throws Exception {

		String projectId = ParamUtil.getString(req, "project_id");

		String firmId = ParamUtil.getString(req, "firm_id");
		String code = ParamUtil.getString(req, "project_code");
		String name = ParamUtil.getString(req, "project_name");
		String description = ParamUtil.getString(req, "project_desc");

		ProjProject project = null;

		if (Validator.isNull(projectId)) {

			// Add project

			project = ProjProjectServiceUtil.addProject(
				firmId, code, name, description);
		}
		else {

			// Update project

			project = ProjProjectServiceUtil.updateProject(
				projectId, firmId, code, name, description);
		}

		String[] userIds = StringUtil.split(
			ParamUtil.getString(req, "project_users"));

		ProjProjectServiceUtil.setUsers(project.getPrimaryKey(), userIds);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}