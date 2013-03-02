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

import com.liferay.portlet.project.service.spring.ProjProjectServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ProjProjectServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjProjectServiceSoap {
	public static void addNote(java.lang.String projectId,
		java.lang.String noteContent) throws RemoteException {
		try {
			ProjProjectServiceUtil.addNote(projectId, noteContent);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjProjectModel addProject(
		java.lang.String firmId, java.lang.String code, java.lang.String name,
		java.lang.String description) throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjProject returnValue = ProjProjectServiceUtil.addProject(firmId,
					code, name, description);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteNote(java.lang.String projectId,
		java.lang.String noteId) throws RemoteException {
		try {
			ProjProjectServiceUtil.deleteNote(projectId, noteId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteProject(java.lang.String projectId)
		throws RemoteException {
		try {
			ProjProjectServiceUtil.deleteProject(projectId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjProjectModel[] getNotes(
		java.lang.String projectId) throws RemoteException {
		try {
			java.util.List returnValue = ProjProjectServiceUtil.getNotes(projectId);

			return (com.liferay.portlet.project.model.ProjProject[])returnValue.toArray(new com.liferay.portlet.project.model.ProjProject[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjProjectModel getProject(
		java.lang.String projectId) throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjProject returnValue = ProjProjectServiceUtil.getProject(projectId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjProjectModel[] getProjects()
		throws RemoteException {
		try {
			java.util.List returnValue = ProjProjectServiceUtil.getProjects();

			return (com.liferay.portlet.project.model.ProjProject[])returnValue.toArray(new com.liferay.portlet.project.model.ProjProject[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjProjectModel[] getUsers(
		java.lang.String projectId) throws RemoteException {
		try {
			java.util.List returnValue = ProjProjectServiceUtil.getUsers(projectId);

			return (com.liferay.portlet.project.model.ProjProject[])returnValue.toArray(new com.liferay.portlet.project.model.ProjProject[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void setUsers(java.lang.String projectId,
		java.lang.String[] userIds) throws RemoteException {
		try {
			ProjProjectServiceUtil.setUsers(projectId, userIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.project.model.ProjProjectModel updateProject(
		java.lang.String projectId, java.lang.String firmId,
		java.lang.String code, java.lang.String name,
		java.lang.String description) throws RemoteException {
		try {
			com.liferay.portlet.project.model.ProjProject returnValue = ProjProjectServiceUtil.updateProject(projectId,
					firmId, code, name, description);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String projectId)
		throws RemoteException {
		try {
			boolean returnValue = ProjProjectServiceUtil.hasAdmin(projectId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}