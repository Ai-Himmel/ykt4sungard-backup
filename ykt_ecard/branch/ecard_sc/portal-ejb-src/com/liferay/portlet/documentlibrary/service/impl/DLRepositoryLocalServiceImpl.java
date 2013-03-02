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

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.documentlibrary.service.spring.DLServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portlet.documentlibrary.RepositoryNameException;
import com.liferay.portlet.documentlibrary.RepositoryReadRolesException;
import com.liferay.portlet.documentlibrary.RepositoryWriteRolesException;
import com.liferay.portlet.documentlibrary.model.DLRepository;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLRepositoryLocalService;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="DLRepositoryLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class DLRepositoryLocalServiceImpl implements DLRepositoryLocalService {

	// Business methods

	public DLRepository addRepository(
			String userId, String groupId, String readRoles, String writeRoles,
			String name, String description)
		throws PortalException, SystemException {

		_validate(readRoles, writeRoles, name);

		User user = UserLocalServiceUtil.getUserById(userId);

		String repositoryId = Long.toString(CounterServiceUtil.increment(
			DLRepository.class.getName()));

		DLRepository repository = DLRepositoryUtil.create(repositoryId);

		Date now = new Date();

		repository.setGroupId(groupId);
		repository.setCompanyId(user.getCompanyId());
		repository.setUserId(user.getUserId());
		repository.setUserName(user.getFullName());
		repository.setCreateDate(now);
		repository.setModifiedDate(now);
		repository.setReadRoles(readRoles);
		repository.setWriteRoles(writeRoles);
		repository.setName(name);
		repository.setDescription(description);

		DLRepositoryUtil.update(repository);

		return repository;
	}

	public void deleteAll(String groupId)
		throws PortalException, SystemException {

		Iterator itr = DLRepositoryUtil.findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			DLRepository repository = (DLRepository)itr.next();

			deleteRepository(repository);
		}
	}

	public void deleteRepository(DLRepository repository)
		throws PortalException, SystemException {

		// Delete file profiles

		DLFileProfileUtil.removeByC_R(
			repository.getCompanyId(), repository.getRepositoryId());

		// Delete files

		DLServiceUtil.deleteAll(
			repository.getCompanyId(), repository.getPortletId(),
			repository.getRepositoryId());

		// Delete file versions

		DLFileVersionUtil.removeByC_R(
			repository.getCompanyId(), repository.getRepositoryId());

		// Delete repository

		DLRepositoryUtil.remove(repository.getRepositoryId());
	}

	public List getRepositories(String companyId)
		throws SystemException {

		return DLRepositoryUtil.findByCompanyId(companyId);
	}

	public List getRepositories(String groupId, String companyId)
		throws SystemException {

		return DLRepositoryUtil.findByG_C(groupId, companyId);
	}

	public DLRepository getRepository(String repositoryId)
		throws PortalException, SystemException {

		return DLRepositoryUtil.findByPrimaryKey(repositoryId);
	}

	public DLRepository updateRepository(
			String repositoryId, String readRoles, String writeRoles,
			String name, String description)
		throws PortalException, SystemException {

		_validate(readRoles, writeRoles, name);

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		repository.setModifiedDate(new Date());
		repository.setReadRoles(readRoles);
		repository.setWriteRoles(writeRoles);
		repository.setName(name);
		repository.setDescription(description);

		DLRepositoryUtil.update(repository);

		return repository;
	}

	// Private methods

	private void _validate(String readRoles, String writeRoles, String name)
		throws PortalException, SystemException {

		String[] readRolesArray = StringUtil.split(readRoles);

		if (readRolesArray.length == 0 ||
			!RoleServiceUtil.exists(readRolesArray)) {

			throw new RepositoryReadRolesException();
		}

		String[] writeRolesArray = StringUtil.split(writeRoles);

		if (writeRolesArray.length == 0 ||
			!RoleServiceUtil.exists(writeRolesArray)) {

			throw new RepositoryWriteRolesException();
		}

		if (Validator.isNull(name)) {
			throw new RepositoryNameException();
		}
	}

}