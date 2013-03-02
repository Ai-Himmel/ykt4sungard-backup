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

package com.liferay.portlet.calendar.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.calendar.NoSuchTaskException;
import com.liferay.portlet.calendar.TaskDueDateException;
import com.liferay.portlet.calendar.TaskTitleException;
import com.liferay.portlet.calendar.model.CalTask;
import com.liferay.portlet.calendar.service.spring.CalTaskServiceUtil;
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
 * <a href="EditTaskAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class EditTaskAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			ActionUtil.getTask(req);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			setForward(req, Constants.COMMON_ERROR);
		}

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_updateTask(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof TaskDueDateException ||
					e instanceof TaskTitleException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.calendar.edit_task");
				}
				else if (e != null &&
						 e instanceof NoSuchTaskException ||
						 e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.calendar.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if ((cmd != null) && (cmd.equals(Constants.DELETE))) {
			try {
				_deleteTask(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchTaskException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.calendar.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.calendar.edit_task");
		}
	}

	private void _deleteTask(ActionRequest req, ActionResponse res)
		throws Exception {

		CalTask task = (CalTask)req.getAttribute(WebKeys.CALENDAR_TASK);

		if (task != null) {

			// Delete task

			CalTaskServiceUtil.deleteTask(task.getTaskId());
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _updateTask(ActionRequest req, ActionResponse res)
		throws Exception {

		String taskId = ParamUtil.getString(req, "task_id");

		String title = ParamUtil.getString(req, "task_title");
		String description = ParamUtil.getString(req, "task_desc");
		boolean noDueDate = ParamUtil.get(req, "task_no_dd_param", false);
		int ddMonth = ParamUtil.get(req, "task_dd_month", 0);
		int ddDay = ParamUtil.get(req, "task_dd_day", 0);
		int ddYear = ParamUtil.get(req, "task_dd_year", 0);
		int priority = ParamUtil.get(req, "task_priority", 1);
		int status = ParamUtil.get(req, "task_status", 0);

		if (Validator.isNull(taskId)) {

			// Add task

			CalTaskServiceUtil.addTask(
				title, description, noDueDate, ddMonth, ddDay, ddYear, priority,
				status);
		}
		else {

			// Update task

			CalTaskServiceUtil.updateTask(
				taskId, title, description, noDueDate, ddMonth, ddDay, ddYear,
				priority, status);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}