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

package com.liferay.portlet.documentlibrary.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portlet.documentlibrary.NoSuchRepositoryException;
import com.liferay.portlet.documentlibrary.model.DLRepository;
import com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLRepositoryLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLRepositoryService;
import com.liferay.util.StringUtil;

import java.util.Iterator;
import java.util.List;

/**
 * <a href="DLRepositoryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class DLRepositoryServiceImpl
	extends PrincipalBean implements DLRepositoryService {

	// Business methods

	public DLRepository addRepository(
			String groupId, String readRoles, String writeRoles, String name,
			String description)
		throws PortalException, SystemException {

		return DLRepositoryLocalServiceUtil.addRepository(
			getUserId(), groupId, readRoles, writeRoles, name, description);
	}

	public void deleteRepository(String repositoryId)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		deleteRepository(repository);
	}

	public void deleteRepository(DLRepository repository)
		throws PortalException, SystemException {

		if (!hasAdmin(repository.getRepositoryId())) {
			throw new PrincipalException();
		}

		DLRepositoryLocalServiceUtil.deleteRepository(repository);
	}

	public List getRepositories(String groupId)
		throws PortalException, SystemException {

		List list = DLRepositoryUtil.findByG_C(
			groupId, getUser().getCompanyId());

		Iterator itr = list.iterator();

		while (itr.hasNext()) {
			DLRepository repository = (DLRepository)itr.next();

			try {
				if (!hasRead(repository.getRepositoryId())) {
					itr.remove();
				}
			}
			catch (NoSuchRepositoryException nsre) {
			}
		}

		return list;
	}

	public DLRepository getRepository(String repositoryId)
		throws PortalException, SystemException {

		if (!hasRead(repositoryId)) {
			throw new PrincipalException();
		}

		return DLRepositoryLocalServiceUtil.getRepository(repositoryId);
	}

	public DLRepository updateRepository(
			String repositoryId, String readRoles, String writeRoles,
			String name, String description)
		throws PortalException, SystemException {

		if (!hasAdmin(repositoryId)) {
			throw new PrincipalException();
		}

		return DLRepositoryLocalServiceUtil.updateRepository(
			repositoryId, readRoles, writeRoles, name, description);
	}

	// Permission methods

	public boolean hasAdmin(String repositoryId)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		if ((repository.getUserId().equals(getUserId())) ||
			(getUser().getCompanyId().equals(repository.getCompanyId()) &&
			 RoleServiceUtil.hasRole(
				getUserId(), Role.DOCUMENT_LIBRARY_ADMIN))) {

			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasRead(String repositoryId)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		User user = null;

		try {
			user = getUser();
		}
		catch (Exception e) {
			String[] readRoles = StringUtil.split(repository.getReadRoles());

			for (int i = 0; i < readRoles.length; i++) {
				if (readRoles[i].equals(Role.GUEST)) {
					return true;
				}
			}
		}

		if (user == null) {
			return false;
		}

		if (user.getCompanyId().equals(repository.getCompanyId()) &&
			RoleServiceUtil.hasRoles(
				user.getUserId(),
				StringUtil.split(repository.getReadRoles()))) {

			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasWrite(String repositoryId)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		if (getUser().getCompanyId().equals(repository.getCompanyId()) &&
			RoleServiceUtil.hasRoles(
				getUserId(), StringUtil.split(repository.getWriteRoles()))) {

			return true;
		}
		else {
			return false;
		}
	}

}