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

package com.liferay.portlet.project.service.spring;

/**
 * <a href="ProjTaskServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTaskServiceUtil {
	public static void addNote(java.lang.String taskId,
		java.lang.String noteContent)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();
			projTaskService.addNote(taskId, noteContent);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.project.model.ProjTask addTask(
		java.lang.String projectId, java.lang.String name,
		java.lang.String description, java.lang.String comments,
		int estimatedDuration, int estEndMonth, int estEndDay, int estEndYear,
		int estEndHour, int estEndMin, int actualDuration, int actualEndMonth,
		int actualEndDay, int actualEndYear, int actualEndHour,
		int actualEndMin, int status)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();

			return projTaskService.addTask(projectId, name, description,
				comments, estimatedDuration, estEndMonth, estEndDay,
				estEndYear, estEndHour, estEndMin, actualDuration,
				actualEndMonth, actualEndDay, actualEndYear, actualEndHour,
				actualEndMin, status);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteNote(java.lang.String taskId,
		java.lang.String noteId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();
			projTaskService.deleteNote(taskId, noteId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteTask(java.lang.String taskId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();
			projTaskService.deleteTask(taskId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getNotes(java.lang.String taskId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();

			return projTaskService.getNotes(taskId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.project.model.ProjTask getTask(
		java.lang.String taskId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();

			return projTaskService.getTask(taskId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getTasks()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();

			return projTaskService.getTasks();
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getTasks(int relationship, int status)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();

			return projTaskService.getTasks(relationship, status);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getUsers(java.lang.String taskId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();

			return projTaskService.getUsers(taskId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void setUsers(java.lang.String taskId,
		java.lang.String[] userIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();
			projTaskService.setUsers(taskId, userIds);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.project.model.ProjTask updateTask(
		java.lang.String taskId, java.lang.String projectId,
		java.lang.String name, java.lang.String description,
		java.lang.String comments, int estimatedDuration, int estEndMonth,
		int estEndDay, int estEndYear, int estEndHour, int estEndMin,
		int actualDuration, int actualEndMonth, int actualEndDay,
		int actualEndYear, int actualEndHour, int actualEndMin, int status)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();

			return projTaskService.updateTask(taskId, projectId, name,
				description, comments, estimatedDuration, estEndMonth,
				estEndDay, estEndYear, estEndHour, estEndMin, actualDuration,
				actualEndMonth, actualEndDay, actualEndYear, actualEndHour,
				actualEndMin, status);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static boolean hasAdmin(java.lang.String taskId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjTaskService projTaskService = ProjTaskServiceFactory.getService();

			return projTaskService.hasAdmin(taskId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}