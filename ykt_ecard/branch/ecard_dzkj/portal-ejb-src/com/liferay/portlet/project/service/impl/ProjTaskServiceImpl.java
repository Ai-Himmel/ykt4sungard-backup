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

package com.liferay.portlet.project.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Note;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.NoteLocalServiceUtil;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.project.TaskActualEndDateException;
import com.liferay.portlet.project.TaskDescriptionException;
import com.liferay.portlet.project.TaskEstEndDateException;
import com.liferay.portlet.project.TaskNameException;
import com.liferay.portlet.project.model.ProjTask;
import com.liferay.portlet.project.service.persistence.ProjTaskFinder;
import com.liferay.portlet.project.service.persistence.ProjTaskUtil;
import com.liferay.portlet.project.service.spring.ProjFirmServiceUtil;
import com.liferay.portlet.project.service.spring.ProjTaskService;
import com.liferay.util.Validator;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * <a href="ProjTaskServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.2 $
 *
 */
public class ProjTaskServiceImpl
	extends PrincipalBean implements ProjTaskService {

	// Business methods

	public void addNote(String taskId, String noteContent)
		throws PortalException, SystemException {

		if (!hasAdmin(taskId)) {
			throw new PrincipalException();
		}

		NoteLocalServiceUtil.addNote(
			getUserId(), ProjTask.class.getName(), taskId, noteContent);
	}

	public ProjTask addTask(
			String projectId, String name, String description, String comments,
			int estimatedDuration, int estEndMonth, int estEndDay,
			int estEndYear, int estEndHour, int estEndMin, int actualDuration,
			int actualEndMonth, int actualEndDay, int actualEndYear,
			int actualEndHour, int actualEndMin, int status)
		throws PortalException, SystemException {

		_validate(name, description);

		User user = getUser();

		String taskId = Long.toString(CounterServiceUtil.increment(
			ProjTask.class.getName()));

		ProjTask task = ProjTaskUtil.create(taskId);

		Date now = new Date();

		Date estEndDate = PortalUtil.getDate(
			estEndMonth, estEndDay, estEndYear, estEndHour, estEndMin,
			user.getTimeZone(), new TaskEstEndDateException());

		Date actualEndDate = null;
		if ((actualEndMonth != 0) || (actualEndDay != 0) ||
			(actualEndYear != 0)) {

			actualEndDate = PortalUtil.getDate(
				actualEndMonth, actualEndDay, actualEndYear, actualEndHour,
				actualEndMin, user.getTimeZone(),
				new TaskActualEndDateException());
		}

		task.setCompanyId(user.getCompanyId());
		task.setUserId(user.getUserId());
		task.setUserName(user.getFullName());
		task.setCreateDate(now);
		task.setModifiedDate(now);
		task.setProjectId(projectId);
		task.setName(name);
		task.setDescription(description);
		task.setComments(comments);
		task.setEstimatedDuration(estimatedDuration);
		task.setEstimatedEndDate(estEndDate);
		task.setActualDuration(actualDuration);
		task.setActualEndDate(actualEndDate);
		task.setStatus(status);

		ProjTaskUtil.update(task);

		return task;
	}

	public void deleteNote(String taskId, String noteId)
		throws PortalException, SystemException {

		if (!hasAdmin(taskId)) {
			throw new PrincipalException();
		}

		Note note = NoteLocalServiceUtil.getNote(noteId);

		if (note.getClassPK().equals(taskId)) {
			NoteLocalServiceUtil.deleteNote(noteId);
		}
	}

	public void deleteTask(String taskId)
		throws PortalException, SystemException {

		ProjTask task = ProjTaskUtil.findByPrimaryKey(taskId);

		if (!hasAdmin(taskId)) {
			throw new PrincipalException();
		}

		// Remove task notes

		NoteLocalServiceUtil.deleteNotes(
			task.getCompanyId(), ProjTask.class.getName(), taskId);

		// Remove task

		ProjTaskUtil.remove(taskId);
	}

	public List getNotes(String taskId)
		throws PortalException, SystemException {

		if (!hasAdmin(taskId)) {
			throw new PrincipalException();
		}

		return NoteLocalServiceUtil.getNotes(
			getUser().getCompanyId(), ProjTask.class.getName(), taskId);
	}

	public ProjTask getTask(String taskId)
		throws PortalException, SystemException {

		return ProjTaskUtil.findByPrimaryKey(taskId);
	}

	public List getTasks() throws PortalException, SystemException {
		return getTasks(ProjTask.RELATIONSHIP_ANY, ProjTask.STATUS_ANY);
	}

	public List getTasks(int relationship, int status)
		throws PortalException, SystemException {

		List list = null;

		User user = getUser();

		if ((relationship == ProjTask.RELATIONSHIP_ANY) &&
			(status == ProjTask.STATUS_ANY)) {

			if (ProjFirmServiceUtil.hasAdmin()) {
				list = ProjTaskUtil.findByCompanyId(user.getCompanyId());
			}
			else {
				Set set = new HashSet();

				set.addAll(ProjTaskUtil.findByUserId(user.getUserId()));
				set.addAll(UserServiceUtil.getProjTasks(user.getUserId()));

				list = new ArrayList(set);

				Collections.sort(list);
			}
		}
		else if ((relationship == ProjTask.RELATIONSHIP_ANY) &&
				 (status != ProjTask.STATUS_ANY)) {

			if (ProjFirmServiceUtil.hasAdmin()) {
				list = ProjTaskUtil.findByC_S(user.getCompanyId(), status);
			}
			else {
				Set set = new HashSet();

				set.addAll(ProjTaskUtil.findByU_S(user.getUserId(), status));
				set.addAll(ProjTaskFinder.findByA_S(user.getUserId(), status));

				list = new ArrayList(set);

				Collections.sort(list);
			}
		}
		else if (relationship == ProjTask.RELATIONSHIP_ASSOCIATED) {
			Set set = new HashSet();

			set.addAll(getTasks(ProjTask.RELATIONSHIP_ASSIGNED, status));
			set.addAll(getTasks(ProjTask.RELATIONSHIP_CREATED, status));

			list = new ArrayList(set);

			Collections.sort(list);
		}
		else if (relationship == ProjTask.RELATIONSHIP_ASSIGNED) {
			if (status == ProjTask.STATUS_ANY) {
				list = UserServiceUtil.getProjTasks(user.getUserId());
			}
			else {
				list = ProjTaskFinder.findByA_S(user.getUserId(), status);
			}
		}
		else if (relationship == ProjTask.RELATIONSHIP_CREATED) {
			if (status == ProjTask.STATUS_ANY) {
				list = ProjTaskUtil.findByUserId(user.getUserId());
			}
			else {
				list = ProjTaskUtil.findByU_S(user.getUserId(), status);
			}
		}

		return list;
	}

	public List getUsers(String taskId)
		throws PortalException, SystemException {

		ProjTask task = ProjTaskUtil.findByPrimaryKey(taskId);

		if (hasAdministrator(task.getCompanyId())) {
			return ProjTaskUtil.getUsers(taskId);
		}
		else if (getUser().getCompanyId().equals(task.getCompanyId())) {
			List users = new ArrayList();

			Iterator itr = ProjTaskUtil.getUsers(taskId).iterator();

			while (itr.hasNext()) {
				users.add((User)((User)itr.next()).getProtected());
			}

			return users;
		}
		else {
			throw new PrincipalException();
		}
	}

	public void setUsers(String taskId, String[] userIds)
		throws PortalException, SystemException {

		if (!hasAdmin(taskId)) {
			throw new PrincipalException();
		}

		ProjTaskUtil.setUsers(taskId, userIds);
	}

	public ProjTask updateTask(
			String taskId, String projectId, String name, String description,
			String comments, int estimatedDuration, int estEndMonth,
			int estEndDay, int estEndYear, int estEndHour, int estEndMin,
			int actualDuration, int actualEndMonth, int actualEndDay,
			int actualEndYear, int actualEndHour, int actualEndMin, int status)
		throws PortalException, SystemException {

		_validate(name, description);

		User user = getUser();

		ProjTask task = ProjTaskUtil.findByPrimaryKey(taskId);

		Date estEndDate = PortalUtil.getDate(
			estEndMonth, estEndDay, estEndYear, estEndHour, estEndMin,
			user.getTimeZone(), new TaskEstEndDateException());

		Date actualEndDate = null;
		if ((actualEndMonth != 0) || (actualEndDay != 0) ||
			(actualEndYear != 0)) {

			actualEndDate = PortalUtil.getDate(
				actualEndMonth, actualEndDay, actualEndYear, actualEndHour,
				actualEndMin, user.getTimeZone(),
				new TaskActualEndDateException());
		}

		task.setModifiedDate(new Date());
		task.setName(name);
		task.setDescription(description);
		task.setComments(comments);
		task.setEstimatedDuration(estimatedDuration);
		task.setEstimatedEndDate(estEndDate);
		task.setActualDuration(actualDuration);
		task.setActualEndDate(actualEndDate);
		task.setStatus(status);

		ProjTaskUtil.update(task);

		return task;
	}

	// Permission methods

	public boolean hasAdmin(String taskId)
		throws PortalException, SystemException {

		ProjTask task = ProjTaskUtil.findByPrimaryKey(taskId);

		if (getUser().getCompanyId().equals(task.getCompanyId()) &&
			RoleServiceUtil.hasRole(getUserId(), Role.PROJECT_ADMIN)) {

			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private void _validate(String name, String description)
		throws PortalException {

		if (Validator.isNull(name)) {
			throw new TaskNameException();
		}
		else if (Validator.isNull(description)) {
			throw new TaskDescriptionException();
		}
	}

}