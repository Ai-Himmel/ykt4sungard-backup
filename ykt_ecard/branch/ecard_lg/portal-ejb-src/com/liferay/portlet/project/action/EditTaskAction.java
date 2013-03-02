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
import com.liferay.portal.model.User;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.project.NoSuchProjectException;
import com.liferay.portlet.project.NoSuchTaskException;
import com.liferay.portlet.project.TaskActualEndDateException;
import com.liferay.portlet.project.TaskDescriptionException;
import com.liferay.portlet.project.TaskEstEndDateException;
import com.liferay.portlet.project.TaskNameException;
import com.liferay.portlet.project.model.ProjProject;
import com.liferay.portlet.project.model.ProjTask;
import com.liferay.portlet.project.service.spring.ProjProjectServiceUtil;
import com.liferay.portlet.project.service.spring.ProjTaskServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.TimeZone;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditTaskAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.5 $
 *
 */
public class EditTaskAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editTask(req);

				_updateTask(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof TaskDescriptionException ||
					e instanceof TaskActualEndDateException ||
					e instanceof TaskEstEndDateException ||
					e instanceof TaskNameException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.project.edit_task");
				}
				else if (e != null &&
						 e instanceof NoSuchProjectException ||
						 e instanceof NoSuchTaskException ||
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
				_deleteTask(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchTaskException ||
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
		else if (cmd != null && cmd.equals(Constants.EDIT)) {
			try {
				_editTask(req);

				setForward(req, "portlet.project.edit_task");
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchProjectException ||
					e instanceof NoSuchTaskException ||
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
				_addTaskNote(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchTaskException ||
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
				_deleteTaskNote(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchTaskException ||
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
			setForward(req, "portlet.project.edit_task");
		}
	}

	private void _addTaskNote(ActionRequest req, ActionResponse res)
		throws Exception {

		String taskId = ParamUtil.getString(req, "task_id");

		String noteContent = ParamUtil.getString(req, "note_content");

		// Add note

		ProjTaskServiceUtil.addNote(taskId, noteContent);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _deleteTask(ActionRequest req, ActionResponse res)
		throws Exception {

		String taskId = ParamUtil.getString(req, "task_id");

		ProjTaskServiceUtil.deleteTask(taskId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _deleteTaskNote(ActionRequest req, ActionResponse res)
		throws Exception {

		String taskId = ParamUtil.getString(req, "task_id");

		String noteId = ParamUtil.getString(req, "note_id");

		// Delete note

		ProjTaskServiceUtil.deleteNote(taskId, noteId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editTask(ActionRequest req) throws Exception {
		String taskId = req.getParameter("task_id");

		ProjTask task = null;

		if (Validator.isNotNull(taskId)) {
			task = ProjTaskServiceUtil.getTask(taskId);
		}

		String projectId = ParamUtil.getString(req, "project_id");
		if (task != null) {
			projectId = task.getProjectId();
		}

		ProjProject project = ProjProjectServiceUtil.getProject(projectId);

		req.setAttribute(WebKeys.PROJ_TASK, task);
		req.setAttribute(WebKeys.PROJ_PROJECT, project);
	}

	private void _updateTask(ActionRequest req, ActionResponse res)
		throws Exception {

		String taskId = ParamUtil.getString(req, "task_id");

		String projectId = ParamUtil.getString(req, "project_id");
		String name = ParamUtil.getString(req, "task_name");
		String description = ParamUtil.getString(req, "task_desc");
		String comments = ParamUtil.getString(req, "task_comments");

		User user = PortalUtil.getUser(req);

		TimeZone timeZone = user.getTimeZone();
		if (timeZone == null) {
			timeZone = PortalUtil.getCompany(req).getTimeZone();
		}

		Calendar cal = new GregorianCalendar(timeZone);
		cal.setTime(new Date());

		int estimatedDuration = ParamUtil.getInteger(
			req, "task_estimated_duration");

		int estEndMonth = ParamUtil.getInteger(req, "task_est_end_month");
		estEndMonth--;

		int estEndDay = ParamUtil.getInteger(req, "task_est_end_day");
		int estEndYear = ParamUtil.getInteger(req, "task_est_end_year");
		int estEndHour = ParamUtil.getInteger(req, "task_est_end_hour");
		int estEndMin = ParamUtil.getInteger(req, "task_est_end_min");

		int actualDuration = ParamUtil.getInteger(req, "task_actual_duration");

		int actualEndMonth = ParamUtil.getInteger(req, "task_actual_end_month");
		if (actualEndMonth > 0) {
			actualEndMonth--;
		}

		int actualEndDay = ParamUtil.getInteger(req, "task_actual_end_day");
		int actualEndYear = ParamUtil.getInteger(req, "task_actual_end_year");
		int actualEndHour = ParamUtil.getInteger(req, "task_actual_end_hour");
		int actualEndMin = ParamUtil.getInteger(req, "task_actual_end_min");

		int status = ParamUtil.getInteger(req, "task_status");

		ProjTask task = null;

		if (Validator.isNull(taskId)) {

			// Add task

			task = ProjTaskServiceUtil.addTask(
				projectId, name, description, comments, estimatedDuration,
				estEndMonth, estEndDay, estEndYear, estEndHour, estEndMin,
				actualDuration, actualEndMonth, actualEndDay, actualEndYear,
				actualEndHour, actualEndMin,  status);
		}
		else {

			// Update task

			task = ProjTaskServiceUtil.updateTask(
				taskId, projectId, name, description, comments,
				estimatedDuration, estEndMonth, estEndDay, estEndYear,
				estEndHour, estEndMin, actualDuration, actualEndMonth,
				actualEndDay, actualEndYear, actualEndHour, actualEndMin,
				status);
		}

		String[] userIds = StringUtil.split(
			ParamUtil.getString(req, "task_users"));

		ProjTaskServiceUtil.setUsers(task.getPrimaryKey(), userIds);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}