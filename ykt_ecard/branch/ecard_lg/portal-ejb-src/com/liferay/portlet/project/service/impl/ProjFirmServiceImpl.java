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
import com.liferay.portlet.project.FirmNameException;
import com.liferay.portlet.project.FirmURLException;
import com.liferay.portlet.project.RequiredFirmException;
import com.liferay.portlet.project.model.ProjFirm;
import com.liferay.portlet.project.service.persistence.ProjFirmUtil;
import com.liferay.portlet.project.service.persistence.ProjProjectUtil;
import com.liferay.portlet.project.service.spring.ProjFirmService;
import com.liferay.util.Validator;

import java.net.MalformedURLException;
import java.net.URL;

import java.util.Date;
import java.util.List;

/**
 * <a href="ProjFirmServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.2 $
 *
 */
public class ProjFirmServiceImpl
	extends PrincipalBean implements ProjFirmService {

	// Business methods

	public ProjFirm addFirm(
			String name, String description, String url)
		throws PortalException, SystemException {

		_validate(name, url);

		if (!hasAdmin()) {
			throw new PrincipalException();
		}

		User user = getUser();

		String firmId = Long.toString(CounterServiceUtil.increment(
			ProjFirm.class.getName()));

		Date now = new Date();

		ProjFirm firm = ProjFirmUtil.create(firmId);

		firm.setCompanyId(user.getCompanyId());
		firm.setUserId(user.getUserId());
		firm.setUserName(user.getFullName());
		firm.setCreateDate(now);
		firm.setModifiedDate(now);
		firm.setName(name);
		firm.setDescription(description);
		firm.setUrl(url);

		ProjFirmUtil.update(firm);

		return firm;
	}

	public void addNote(String firmId, String noteContent)
		throws PortalException, SystemException {

		if (!hasAdmin(firmId)) {
			throw new PrincipalException();
		}

		NoteLocalServiceUtil.addNote(
			getUserId(), ProjFirm.class.getName(), firmId, noteContent);
	}

	public void deleteFirm(String firmId)
		throws PortalException, SystemException {

		ProjFirm firm = ProjFirmUtil.findByPrimaryKey(firmId);

		if (!hasAdmin(firmId)) {
			throw new PrincipalException();
		}

		if (ProjProjectUtil.countByFirmId(firmId) > 0) {
			throw new RequiredFirmException();
		}

		// Remove firm notes

		NoteLocalServiceUtil.deleteNotes(
			firm.getCompanyId(), ProjFirm.class.getName(), firmId);

		// Remove firm

		ProjFirmUtil.remove(firmId);
	}

	public void deleteNote(String firmId, String noteId)
		throws PortalException, SystemException {

		if (!hasAdmin(firmId)) {
			throw new PrincipalException();
		}

		Note note = NoteLocalServiceUtil.getNote(noteId);

		if (note.getClassPK().equals(firmId)) {
			NoteLocalServiceUtil.deleteNote(noteId);
		}
	}

	public ProjFirm getFirm(String firmId)
		throws PortalException, SystemException {

		return ProjFirmUtil.findByPrimaryKey(firmId);
	}

	public List getFirms() throws PortalException, SystemException {
		return ProjFirmUtil.findByCompanyId(getUser().getCompanyId());
	}

	public List getNotes(String firmId)
		throws PortalException, SystemException {

		if (!hasAdmin(firmId)) {
			throw new PrincipalException();
		}

		return NoteLocalServiceUtil.getNotes(
			getUser().getCompanyId(), ProjFirm.class.getName(), firmId);
	}

	public ProjFirm updateFirm(
			String firmId, String name, String description, String url)
		throws PortalException, SystemException {

		_validate(name, url);

		if (!hasAdmin(firmId)) {
			throw new PrincipalException();
		}

		ProjFirm firm = ProjFirmUtil.findByPrimaryKey(firmId);

		firm.setModifiedDate(new Date());

		firm.setName(name);
		firm.setDescription(description);
		firm.setUrl(url);

		ProjFirmUtil.update(firm);

		return firm;
	}

	// Permission methods

	public boolean hasAdmin() throws PortalException, SystemException {
		String userId = null;

		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if (RoleServiceUtil.hasRole(userId, Role.PROJECT_ADMIN)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasAdmin(String firmId)
		throws PortalException, SystemException {

		ProjFirm firm = ProjFirmUtil.findByPrimaryKey(firmId);

		if (getUser().getCompanyId().equals(firm.getCompanyId()) &&
			RoleServiceUtil.hasRole(getUserId(), Role.PROJECT_ADMIN)) {

			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private void _validate(String name, String url) throws PortalException {
		if (Validator.isNull(name)) {
			throw new FirmNameException();
		}

		if (Validator.isNull(url)) {
			throw new FirmURLException();
		}
		else {
			try {
				new URL(url);
			}
			catch (MalformedURLException murle) {
				throw new FirmURLException();
			}
		}
	}

}