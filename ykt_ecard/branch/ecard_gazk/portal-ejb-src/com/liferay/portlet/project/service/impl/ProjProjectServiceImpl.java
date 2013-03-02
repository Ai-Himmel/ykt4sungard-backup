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
import com.liferay.portlet.project.DuplicateProjectException;
import com.liferay.portlet.project.NoSuchFirmException;
import com.liferay.portlet.project.NoSuchProjectException;
import com.liferay.portlet.project.ProjectCodeException;
import com.liferay.portlet.project.ProjectNameException;
import com.liferay.portlet.project.RequiredProjectException;
import com.liferay.portlet.project.model.ProjFirm;
import com.liferay.portlet.project.model.ProjProject;
import com.liferay.portlet.project.service.persistence.ProjFirmUtil;
import com.liferay.portlet.project.service.persistence.ProjProjectUtil;
import com.liferay.portlet.project.service.persistence.ProjTaskUtil;
import com.liferay.portlet.project.service.spring.ProjFirmServiceUtil;
import com.liferay.portlet.project.service.spring.ProjProjectService;
import com.liferay.util.Validator;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ProjProjectServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.2 $
 *
 */
public class ProjProjectServiceImpl
	extends PrincipalBean implements ProjProjectService {

	// Business methods

	public void addNote(String projectId, String noteContent)
		throws PortalException, SystemException {

		if (!hasAdmin(projectId)) {
			throw new PrincipalException();
		}

		NoteLocalServiceUtil.addNote(
			getUserId(), ProjProject.class.getName(), projectId, noteContent);
	}

	public ProjProject addProject(
			String firmId, String code, String name, String description)
		throws PortalException, SystemException {

		code = code.trim().toUpperCase();

		_validate(null, firmId, code, name);

		if (!ProjFirmServiceUtil.hasAdmin()) {
			throw new PrincipalException();
		}

		User user = getUser();

		String projectId = Long.toString(CounterServiceUtil.increment(
			ProjProject.class.getName()));

		Date now = new Date();

		ProjProject project = ProjProjectUtil.create(projectId);

		project.setCompanyId(user.getCompanyId());
		project.setUserId(user.getUserId());
		project.setCreateDate(now);
		project.setModifiedDate(now);
		project.setFirmId(firmId);
		project.setCode(code);
		project.setName(name);
		project.setDescription(description);

		ProjProjectUtil.update(project);

		return project;
	}

	public void deleteNote(String projectId, String noteId)
		throws PortalException, SystemException {

		if (!hasAdmin(projectId)) {
			throw new PrincipalException();
		}

		Note note = NoteLocalServiceUtil.getNote(noteId);

		if (note.getClassPK().equals(projectId)) {
			NoteLocalServiceUtil.deleteNote(noteId);
		}
	}

	public void deleteProject(String projectId)
		throws PortalException, SystemException {

		ProjProject project = ProjProjectUtil.findByPrimaryKey(projectId);

		if (!hasAdmin(projectId)) {
			throw new PrincipalException();
		}

		if (ProjTaskUtil.countByProjectId(projectId) > 0) {
			throw new RequiredProjectException();
		}

		// Remove project notes

		NoteLocalServiceUtil.deleteNotes(
			project.getCompanyId(), ProjProject.class.getName(), projectId);

		// Remove project

		ProjProjectUtil.remove(projectId);
	}

	public List getNotes(String projectId)
		throws PortalException, SystemException {

		if (!hasAdmin(projectId)) {
			throw new PrincipalException();
		}

		return NoteLocalServiceUtil.getNotes(
			getUser().getCompanyId(), ProjProject.class.getName(), projectId);
	}

	public ProjProject getProject(String projectId)
		throws PortalException, SystemException {

		return ProjProjectUtil.findByPrimaryKey(projectId);
	}

	public List getProjects() throws PortalException, SystemException {
		if (!ProjFirmServiceUtil.hasAdmin()) {
			throw new PrincipalException();
		}

		return ProjProjectUtil.findByCompanyId(getUser().getCompanyId());
	}

	public List getUsers(String projectId)
		throws PortalException, SystemException {

		ProjProject project = ProjProjectUtil.findByPrimaryKey(projectId);

		if (hasAdministrator(project.getCompanyId())) {
			return ProjProjectUtil.getUsers(projectId);
		}
		else if (getUser().getCompanyId().equals(project.getCompanyId())) {
			List users = new ArrayList();

			Iterator itr = ProjProjectUtil.getUsers(projectId).iterator();

			while (itr.hasNext()) {
				users.add((User)((User)itr.next()).getProtected());
			}

			return users;
		}
		else {
			throw new PrincipalException();
		}
	}

	public void setUsers(String projectId, String[] userIds)
		throws PortalException, SystemException {

		if (!hasAdmin(projectId)) {
			throw new PrincipalException();
		}

		ProjProjectUtil.setUsers(projectId, userIds);
	}

	public ProjProject updateProject(
			String projectId, String firmId, String code, String name,
			String description)
		throws PortalException, SystemException {

		code = code.trim().toUpperCase();

		_validate(projectId, firmId, code, name);

		if (!hasAdmin(projectId)) {
			throw new PrincipalException();
		}

		ProjProject project = ProjProjectUtil.findByPrimaryKey(projectId);

		project.setModifiedDate(new Date());
		project.setFirmId(firmId);
		project.setCode(code);
		project.setName(name);
		project.setDescription(description);

		ProjProjectUtil.update(project);

		return project;
	}

	// Permission methods

	public boolean hasAdmin(String projectId)
		throws PortalException, SystemException {

		ProjProject project = ProjProjectUtil.findByPrimaryKey(projectId);

		if (getUser().getCompanyId().equals(project.getCompanyId()) &&
			RoleServiceUtil.hasRole(getUserId(), Role.PROJECT_ADMIN)) {

			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private void _validate(
			String projectId, String firmId, String code, String name)
		throws PortalException, SystemException {

		String companyId = getUser().getCompanyId();

		ProjFirm firm = ProjFirmUtil.findByPrimaryKey(firmId);
		if (!firm.getCompanyId().equals(companyId)) {
			throw new NoSuchFirmException();
		}

		if (Validator.isNull(code)) {
			throw new ProjectCodeException();
		}
		else {
			if (projectId != null) {
				try {
					ProjProject project =
						ProjProjectUtil.findByC_C(companyId, code);

					if (!project.getProjectId().equals(projectId)) {
						throw new DuplicateProjectException();
					}
				}
				catch (NoSuchProjectException nspe) {
				}
			}
		}

		if (Validator.isNull(name)) {
			throw new ProjectNameException();
		}
	}

}