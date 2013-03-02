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

package com.liferay.portlet.calendar.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.calendar.TaskDueDateException;
import com.liferay.portlet.calendar.TaskTitleException;
import com.liferay.portlet.calendar.model.CalTask;
import com.liferay.portlet.calendar.service.persistence.CalTaskUtil;
import com.liferay.portlet.calendar.service.spring.CalTaskLocalServiceUtil;
import com.liferay.portlet.calendar.service.spring.CalTaskService;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.GregorianCalendar;
import java.util.List;

/**
 * <a href="CalTaskServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class CalTaskServiceImpl
	extends PrincipalBean implements CalTaskService {

	// Business methods

	public CalTask addTask(
			String title, String description, boolean noDueDate, int dueMonth,
			int dueDay, int dueYear, int priority, int status)
		throws PortalException, SystemException {

		_validate(title, dueMonth, dueDay, dueYear);

		User user = getUser();

		String taskId = Long.toString(CounterServiceUtil.increment(
			CalTask.class.getName()));

		CalTask task = CalTaskUtil.create(taskId);

		Date now = new Date();

		task.setCompanyId(user.getCompanyId());
		task.setUserId(user.getUserId());
		task.setCreateDate(now);
		task.setModifiedDate(now);
		task.setTitle(title);
		task.setDescription(description);
		task.setNoDueDate(noDueDate);
		task.setDueDate(
			new GregorianCalendar(dueYear, dueMonth, dueDay).getTime());
		task.setPriority(priority);
		task.setStatus(status);

		CalTaskUtil.update(task);

		return task;
	}

	public void deleteTask(String taskId)
		throws PortalException, SystemException {

		CalTask task = CalTaskUtil.findByPrimaryKey(taskId);

		if (!task.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		CalTaskLocalServiceUtil.deleteTask(taskId);
	}

	public CalTask getTask(String taskId)
		throws PortalException, SystemException {

		return CalTaskUtil.findByPrimaryKey(taskId);
	}

	public List getTasks() throws PortalException, SystemException {
		return getTasks(CalTask.PRIORITY_ANY, CalTask.STATUS_ANY);
	}

	public List getTasks(int priority, int status)
		throws PortalException, SystemException {

		List list = null;

		if ((priority == CalTask.PRIORITY_ANY) &&
			(status == CalTask.STATUS_ANY)) {

			list = CalTaskUtil.findByUserId(getUserId());
		}
		else if ((priority != CalTask.PRIORITY_ANY) &&
				 (status == CalTask.STATUS_ANY)) {

			list = CalTaskUtil.findByU_P(getUserId(), priority);
		}
		else if ((priority == CalTask.PRIORITY_ANY) &&
				 (status != CalTask.STATUS_ANY)) {

			list = CalTaskUtil.findByU_S(getUserId(), status);
		}
		else {
			list = CalTaskUtil.findByU_P_S(getUserId(), priority, status);
		}

		return list;
	}

	public CalTask updateTask(
			String taskId, String title, String description, boolean noDueDate,
			int dueMonth, int dueDay, int dueYear, int priority, int status)
		throws PortalException, SystemException {

		_validate(title, dueMonth, dueDay, dueYear);

		CalTask task = CalTaskUtil.findByPrimaryKey(taskId);

		if (!task.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		task.setModifiedDate(new Date());
		task.setTitle(title);
		task.setDescription(description);
		task.setNoDueDate(noDueDate);
		task.setDueDate(
			new GregorianCalendar(dueYear, dueMonth, dueDay).getTime());
		task.setPriority(priority);
		task.setStatus(status);

		CalTaskUtil.update(task);

		return task;
	}

	// Private methods

	private void _validate(String title, int dueMonth, int dueDay, int dueYear)
		throws PortalException {

		if (Validator.isNull(title)) {
			throw new TaskTitleException();
		}
		else if (!Validator.isDate(dueMonth, dueDay, dueYear)) {
			throw new TaskDueDateException();
		}
	}

}