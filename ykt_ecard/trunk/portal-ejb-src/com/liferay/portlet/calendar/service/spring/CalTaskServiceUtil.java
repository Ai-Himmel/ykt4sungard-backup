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

package com.liferay.portlet.calendar.service.spring;

/**
 * <a href="CalTaskServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalTaskServiceUtil {
	public static final String PORTLET_ID = "8";

	public static com.liferay.portlet.calendar.model.CalTask addTask(
		java.lang.String title, java.lang.String description,
		boolean noDueDate, int dueMonth, int dueDay, int dueYear, int priority,
		int status)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalTaskService calTaskService = CalTaskServiceFactory.getService();

			return calTaskService.addTask(title, description, noDueDate,
				dueMonth, dueDay, dueYear, priority, status);
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
			CalTaskService calTaskService = CalTaskServiceFactory.getService();
			calTaskService.deleteTask(taskId);
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

	public static com.liferay.portlet.calendar.model.CalTask getTask(
		java.lang.String taskId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalTaskService calTaskService = CalTaskServiceFactory.getService();

			return calTaskService.getTask(taskId);
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
			CalTaskService calTaskService = CalTaskServiceFactory.getService();

			return calTaskService.getTasks();
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

	public static java.util.List getTasks(int priority, int status)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalTaskService calTaskService = CalTaskServiceFactory.getService();

			return calTaskService.getTasks(priority, status);
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

	public static com.liferay.portlet.calendar.model.CalTask updateTask(
		java.lang.String taskId, java.lang.String title,
		java.lang.String description, boolean noDueDate, int dueMonth,
		int dueDay, int dueYear, int priority, int status)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			CalTaskService calTaskService = CalTaskServiceFactory.getService();

			return calTaskService.updateTask(taskId, title, description,
				noDueDate, dueMonth, dueDay, dueYear, priority, status);
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