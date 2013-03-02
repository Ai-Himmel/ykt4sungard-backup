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

import com.liferay.documentlibrary.NoSuchFileException;
import com.liferay.documentlibrary.service.spring.DLServiceUtil;
import com.liferay.documentlibrary.util.DirectoryView;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.RoleLocalServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portlet.documentlibrary.FileProfileReadRolesException;
import com.liferay.portlet.documentlibrary.FileProfileWriteRolesException;
import com.liferay.portlet.documentlibrary.NoSuchFileProfileException;
import com.liferay.portlet.documentlibrary.model.DLFileProfile;
import com.liferay.portlet.documentlibrary.model.DLFileRank;
import com.liferay.portlet.documentlibrary.model.DLFileVersion;
import com.liferay.portlet.documentlibrary.model.DLRepository;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileFinder;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileProfilePK;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileRankFinder;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPK;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileRankUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionFinder;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionPK;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionUtil;
import com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLFileProfileLocalService;
import com.liferay.portlet.documentlibrary.service.spring.DLFileRankLocalServiceUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.MathUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lucene.Hits;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;

/**
 * <a href="DLFileProfileLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class DLFileProfileLocalServiceImpl
	implements DLFileProfileLocalService {

	// Business methods

	public void addDirectory(
			String companyId, String repositoryId, String dirName)
		throws PortalException, SystemException {

		DLServiceUtil.addDirectory(companyId, repositoryId, dirName);
	}

	public void addFile(
			String companyId, String userId, String repositoryId,
			String fileName, String readRoles, String writeRoles,
			byte[] byteArray)
		throws PortalException, SystemException {

		validate(companyId, readRoles, writeRoles);

		User user = UserLocalServiceUtil.getUserById(userId);

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		DLFileProfilePK pk = new DLFileProfilePK(
			companyId, repositoryId, fileName);

		DLFileProfile fileProfile = DLFileProfileUtil.create(pk);

		Date now = new Date();

		fileProfile.setUserId(user.getUserId());
		fileProfile.setUserName(user.getFullName());
		fileProfile.setVersionUserId(user.getUserId());
		fileProfile.setVersionUserName(user.getFullName());
		fileProfile.setCreateDate(now);
		fileProfile.setModifiedDate(now);
		fileProfile.setReadRoles(readRoles);
		fileProfile.setWriteRoles(writeRoles);
		fileProfile.setDescription(fileName);
		fileProfile.setVersion(DLFileProfile.DEFAULT_VERSION);
		fileProfile.setSize(byteArray.length);

		DLServiceUtil.addFile(
			companyId, repository.getPortletId(), repository.getGroupId(),
			repositoryId, fileName, byteArray);

		try {
			DLFileProfileUtil.update(fileProfile);
		}

		// Stale file profile that points to a nonexistent file

		catch (SystemException se) {
			if (se.getCause() instanceof HibernateException) {

				// Delete file profile

				try {
					DLFileProfileUtil.remove(pk);
				}
				catch (Exception e) {
				}

				// Delete file versions

				Iterator itr = DLFileVersionUtil.findByC_R_FN(
					pk.companyId, repositoryId, fileName).iterator();

				while (itr.hasNext()) {
					DLFileVersion fileVersion = (DLFileVersion)itr.next();

					try {
						DLFileVersionUtil.remove(fileVersion.getPrimaryKey());
					}
					catch (Exception e) {
					}
				}

				DLFileProfileUtil.update(fileProfile);
			}
		}

		// Update repository

		repository.setLastPostDate(now);

		DLRepositoryUtil.update(repository);
	}

	public void deleteDirectory(
			String companyId, String repositoryId, String dirName)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		Collection c = DLFileProfileFinder.findByFileName(
			companyId, repositoryId, dirName);

		Iterator itr = c.iterator();

		while (itr.hasNext()) {
			DLFileProfilePK pk = (DLFileProfilePK)itr.next();
		}

		// Delete directory

		DLServiceUtil.deleteDirectory(
			companyId, repository.getPortletId(), repositoryId, dirName);

		// Delete file profiles

		itr = c.iterator();

		while (itr.hasNext()) {
			DLFileProfilePK pk = (DLFileProfilePK)itr.next();

			DLFileProfileUtil.remove(pk);
		}

		// Delete file versions

		itr = DLFileVersionFinder.findByFileName(
			companyId, repositoryId, dirName).iterator();

		while (itr.hasNext()) {
			DLFileVersionPK pk = (DLFileVersionPK)itr.next();

			DLFileVersionUtil.remove(pk);
		}

		// Delete file ranks

		itr = DLFileRankFinder.findByFileName(
			companyId, repositoryId, dirName).iterator();

		while (itr.hasNext()) {
			DLFileRankPK pk = (DLFileRankPK)itr.next();

			DLFileRankUtil.remove(pk);
		}
	}

	public void deleteFile(
			String companyId, String repositoryId, String fileName)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		DLFileProfilePK pk = new DLFileProfilePK(
			companyId, repositoryId, fileName);

		// Delete file profile

		DLFileProfileUtil.remove(pk);

		// Delete file

		DLServiceUtil.deleteFile(
			pk.companyId, repository.getPortletId(), repositoryId, fileName);

		// Delete file versions

		Iterator itr = DLFileVersionUtil.findByC_R_FN(
			pk.companyId, repositoryId, fileName).iterator();

		while (itr.hasNext()) {
			DLFileVersion fileVersion = (DLFileVersion)itr.next();

			DLFileVersionUtil.remove(fileVersion.getPrimaryKey());
		}

		// Delete file ranks

		itr = DLFileRankUtil.findByC_R_FN(
			pk.companyId, repositoryId, fileName).iterator();

		while (itr.hasNext()) {
			DLFileRank fileRank = (DLFileRank)itr.next();

			DLFileRankUtil.remove(fileRank.getPrimaryKey());
		}
	}

	public void deleteFile(
			String companyId, String repositoryId, String fileName,
			double version)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		// Delete file

		DLServiceUtil.deleteFile(
			companyId, repository.getPortletId(), repositoryId, fileName,
			version);

		// Delete file version

		DLFileVersionUtil.remove(
			new DLFileVersionPK(companyId, repositoryId, fileName, version));
	}

	public String[] getDirectoryNames(
			String companyId, String repositoryId, String dirName)
		throws PortalException, SystemException {

		return DLServiceUtil.getDirectoryNames(
			companyId, repositoryId, dirName);
	}

	public DirectoryView getDirectoryView(String companyId, String repositoryId)
		throws PortalException, SystemException {

		return DLServiceUtil.getDirectoryView(companyId, repositoryId);
	}

	public byte[] getFile(
			String companyId, String userId, String repositoryId,
			String fileName)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		if (Validator.isNotNull(userId)) {
			DLFileRankLocalServiceUtil.updateRank(
				repository.getGroupId(), companyId, userId, repositoryId,
				fileName);
		}

		return DLServiceUtil.getFile(companyId, repositoryId, fileName);
	}

	public byte[] getFile(
			String companyId, String userId, String repositoryId,
			String fileName, double version)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		if (Validator.isNotNull(userId)) {
			DLFileRankLocalServiceUtil.updateRank(
				repository.getGroupId(), companyId, userId, repositoryId,
				fileName);
		}

		return DLServiceUtil.getFile(
			companyId, repositoryId, fileName, version);
	}

	public DLFileProfile getFileProfile(
			String companyId, String userId, String repositoryId,
			String fileName)
		throws PortalException, SystemException {

		DLFileProfilePK pk = new DLFileProfilePK(
			companyId, repositoryId, fileName);

		DLFileProfile fileProfile = null;

		try {
			fileProfile = DLFileProfileUtil.findByPrimaryKey(pk);
		}
		catch (NoSuchFileProfileException nsfpe) {
			if (DLServiceUtil.exists(pk.companyId, repositoryId, pk.fileName)) {
				fileProfile = DLFileProfileUtil.create(pk);

				User user = UserLocalServiceUtil.getUserById(userId);
				Date now = new Date();

				fileProfile.setUserId(user.getUserId());
				fileProfile.setUserName(user.getFullName());
				fileProfile.setVersionUserId(user.getUserId());
				fileProfile.setVersionUserName(user.getFullName());
				fileProfile.setCreateDate(now);
				fileProfile.setModifiedDate(now);
				fileProfile.setReadRoles(DLFileProfile.READ_ROLES);
				fileProfile.setWriteRoles(DLFileProfile.WRITE_ROLES);
				fileProfile.setDescription(pk.fileName);
				fileProfile.setVersion(DLFileProfile.DEFAULT_VERSION);
				fileProfile.setSize(DLServiceUtil.getFileSize(
					pk.companyId, repositoryId, pk.fileName));

				DLFileProfileUtil.update(fileProfile);
			}
			else {
				throw new NoSuchFileException();
			}
		}

		return fileProfile;
	}

	public List getFileProfiles(
			String companyId, String userId, String repositoryId,
			String dirName)
		throws PortalException, SystemException {

		List fileProfiles = new ArrayList();

		String[] fileNames = DLServiceUtil.getFileNames(
			companyId, repositoryId, dirName);

		for (int i = 0; i < fileNames.length; i++) {
			fileProfiles.add(getFileProfile(
				companyId, userId, repositoryId, fileNames[i]));
		}

		return fileProfiles;
	}

	public Hits search(String companyId, String repositoryId, String keywords)
		throws PortalException, SystemException {

		return search(companyId, new String[] {repositoryId}, keywords);
	}

	public Hits search(
			String companyId, String[] repositoryIds, String keywords)
		throws PortalException, SystemException {

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryIds[0]);

		String portletId = repository.getPortletId();
		String groupId = repository.getGroupId();

		return DLServiceUtil.search(
			companyId, portletId, groupId, repositoryIds, keywords);
	}

	public void updateFile(
			String companyId, String userId, String repositoryId,
			String fileName, String sourceFileName, byte[] byteArray)
		throws PortalException, SystemException {

		User user = UserLocalServiceUtil.getUserById(userId);

		DLRepository repository =
			DLRepositoryUtil.findByPrimaryKey(repositoryId);

		DLFileProfilePK pk = new DLFileProfilePK(
			companyId, repositoryId, fileName);

		DLFileProfile fileProfile = DLFileProfileUtil.findByPrimaryKey(pk);

		double oldVersion = fileProfile.getVersion();
		double newVersion = MathUtil.format(oldVersion + 0.1, 1, 1);

		// Update file

		DLServiceUtil.updateFile(
			companyId, repository.getPortletId(), repository.getGroupId(),
			repositoryId, fileName, oldVersion, sourceFileName, byteArray);

		// Add file version

		DLFileVersion fileVersion = DLFileVersionUtil.create(
			new DLFileVersionPK(companyId, repositoryId, fileName, oldVersion));

		String versionUserId = GetterUtil.get(
			fileProfile.getVersionUserId(), fileProfile.getUserId());

		String versionUserName = GetterUtil.getString(
			fileProfile.getVersionUserName(), fileProfile.getUserName());

		fileVersion.setUserId(versionUserId);
		fileVersion.setUserName(versionUserName);
		fileVersion.setCreateDate(fileProfile.getModifiedDate());
		fileVersion.setSize(fileProfile.getSize());

		DLFileVersionUtil.update(fileVersion);

		// Update file profile

		fileProfile.setVersionUserId(user.getUserId());
		fileProfile.setVersionUserName(user.getFullName());
		fileProfile.setModifiedDate(new Date());
		fileProfile.setVersion(newVersion);
		fileProfile.setSize(byteArray.length);

		DLFileProfileUtil.update(fileProfile);

		// Update repository

		repository.setLastPostDate(fileProfile.getModifiedDate());

		DLRepositoryUtil.update(repository);
	}

	public DLFileProfile updateFileProfile(
			String companyId, String repositoryId, String fileName,
			String description, String readRoles, String writeRoles)
		throws PortalException, SystemException {

		validate(companyId, readRoles, writeRoles);

		DLFileProfilePK pk = new DLFileProfilePK(
			companyId, repositoryId, fileName);

		DLFileProfile fileProfile = DLFileProfileUtil.findByPrimaryKey(pk);

		fileProfile.setDescription(description);
		fileProfile.setReadRoles(readRoles);
		fileProfile.setWriteRoles(writeRoles);

		DLFileProfileUtil.update(fileProfile);

		return fileProfile;
	}

	public void validate(String companyId, String readRoles, String writeRoles)
		throws PortalException, SystemException {

		String[] readRolesArray = StringUtil.split(readRoles);

		if (readRolesArray.length == 0 ||
			!RoleLocalServiceUtil.exists(companyId, readRolesArray)) {

			throw new FileProfileReadRolesException();
		}

		String[] writeRolesArray = StringUtil.split(writeRoles);

		if (writeRolesArray.length == 0 ||
			!RoleLocalServiceUtil.exists(companyId, writeRolesArray)) {

			throw new FileProfileWriteRolesException();
		}
	}

}