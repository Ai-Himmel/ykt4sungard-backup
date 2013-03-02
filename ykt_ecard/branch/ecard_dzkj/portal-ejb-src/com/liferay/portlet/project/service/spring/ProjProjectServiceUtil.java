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
 * <a href="ProjProjectServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjProjectServiceUtil {
	public static void addNote(java.lang.String projectId,
		java.lang.String noteContent)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();
			projProjectService.addNote(projectId, noteContent);
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

	public static com.liferay.portlet.project.model.ProjProject addProject(
		java.lang.String firmId, java.lang.String code, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();

			return projProjectService.addProject(firmId, code, name, description);
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

	public static void deleteNote(java.lang.String projectId,
		java.lang.String noteId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();
			projProjectService.deleteNote(projectId, noteId);
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

	public static void deleteProject(java.lang.String projectId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();
			projProjectService.deleteProject(projectId);
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

	public static java.util.List getNotes(java.lang.String projectId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();

			return projProjectService.getNotes(projectId);
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

	public static com.liferay.portlet.project.model.ProjProject getProject(
		java.lang.String projectId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();

			return projProjectService.getProject(projectId);
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

	public static java.util.List getProjects()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();

			return projProjectService.getProjects();
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

	public static java.util.List getUsers(java.lang.String projectId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();

			return projProjectService.getUsers(projectId);
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

	public static void setUsers(java.lang.String projectId,
		java.lang.String[] userIds)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();
			projProjectService.setUsers(projectId, userIds);
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

	public static com.liferay.portlet.project.model.ProjProject updateProject(
		java.lang.String projectId, java.lang.String firmId,
		java.lang.String code, java.lang.String name,
		java.lang.String description)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();

			return projProjectService.updateProject(projectId, firmId, code,
				name, description);
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

	public static boolean hasAdmin(java.lang.String projectId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ProjProjectService projProjectService = ProjProjectServiceFactory.getService();

			return projProjectService.hasAdmin(projectId);
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