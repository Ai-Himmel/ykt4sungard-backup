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

package com.liferay.portlet.project.service.http;

import com.liferay.portlet.project.service.spring.ProjTaskServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ProjTaskServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTaskServiceSoap {
	public static void addNote(java.lang.String taskId,
		java.lang.String noteContent) throws RemoteException {
		try {
			ProjTaskServiceUtil.addNote(taskId, noteContent);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTaskModel addTask(
		java.lang.String projectId, java.lang.String name,
		java.lang.String description, java.lang.String comments,
		int estimatedDuration, int estEndMonth, int estEndDay, int estEndYear,
		int estEndHour, int estEndMin, int actualDuration, int actualEndMonth,
		int actualEndDay, int actualEndYear, int actualEndHour,
		int actualEndMin, int status) throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjTask returnValue = ProjTaskServiceUtil.addTask(projectId,
					name, description, comments, estimatedDuration,
					estEndMonth, estEndDay, estEndYear, estEndHour, estEndMin,
					actualDuration, actualEndMonth, actualEndDay,
					actualEndYear, actualEndHour, actualEndMin, status);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteNote(java.lang.String taskId,
		java.lang.String noteId) throws RemoteException {
		try {
			ProjTaskServiceUtil.deleteNote(taskId, noteId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteTask(java.lang.String taskId)
		throws RemoteException {
		try {
			ProjTaskServiceUtil.deleteTask(taskId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTaskModel[] getNotes(
		java.lang.String taskId) throws RemoteException {
		try {
			java.util.List returnValue = ProjTaskServiceUtil.getNotes(taskId);

			return (com.liferay.portlet.project.model.ProjTask[])returnValue.toArray(new com.liferay.portlet.project.model.ProjTask[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTaskModel getTask(
		java.lang.String taskId) throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjTask returnValue = ProjTaskServiceUtil.getTask(taskId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTaskModel[] getTasks()
		throws RemoteException {
		try {
			java.util.List returnValue = ProjTaskServiceUtil.getTasks();

			return (com.liferay.portlet.project.model.ProjTask[])returnValue.toArray(new com.liferay.portlet.project.model.ProjTask[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTaskModel[] getTasks(
		int relationship, int status) throws RemoteException {
		try {
			java.util.List returnValue = ProjTaskServiceUtil.getTasks(relationship,
					status);

			return (com.liferay.portlet.project.model.ProjTask[])returnValue.toArray(new com.liferay.portlet.project.model.ProjTask[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTaskModel[] getUsers(
		java.lang.String taskId) throws RemoteException {
		try {
			java.util.List returnValue = ProjTaskServiceUtil.getUsers(taskId);

			return (com.liferay.portlet.project.model.ProjTask[])returnValue.toArray(new com.liferay.portlet.project.model.ProjTask[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setUsers(java.lang.String taskId,
		java.lang.String[] userIds) throws RemoteException {
		try {
			ProjTaskServiceUtil.setUsers(taskId, userIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjTaskModel updateTask(
		java.lang.String taskId, java.lang.String projectId,
		java.lang.String name, java.lang.String description,
		java.lang.String comments, int estimatedDuration, int estEndMonth,
		int estEndDay, int estEndYear, int estEndHour, int estEndMin,
		int actualDuration, int actualEndMonth, int actualEndDay,
		int actualEndYear, int actualEndHour, int actualEndMin, int status)
		throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjTask returnValue = ProjTaskServiceUtil.updateTask(taskId,
					projectId, name, description, comments, estimatedDuration,
					estEndMonth, estEndDay, estEndYear, estEndHour, estEndMin,
					actualDuration, actualEndMonth, actualEndDay,
					actualEndYear, actualEndHour, actualEndMin, status);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String taskId)
		throws RemoteException {
		try {
			boolean returnValue = ProjTaskServiceUtil.hasAdmin(taskId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}