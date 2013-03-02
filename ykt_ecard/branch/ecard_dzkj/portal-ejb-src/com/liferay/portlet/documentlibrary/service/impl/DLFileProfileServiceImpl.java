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

import com.liferay.documentlibrary.util.DirectoryView;
import com.liferay.lock.DuplicateLockException;
import com.liferay.lock.ExpiredLockException;
import com.liferay.lock.NoSuchLockException;
import com.liferay.lock.model.Lock;
import com.liferay.lock.service.spring.LockServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portlet.documentlibrary.model.DLFileProfile;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileFinder;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileProfilePK;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLFileProfileLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLFileProfileService;
import com.liferay.portlet.documentlibrary.service.spring.DLRepositoryServiceUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.lucene.Hits;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="DLFileProfileServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class DLFileProfileServiceImpl
	extends PrincipalBean implements DLFileProfileService {

	// Business methods

	public void addDirectory(String repositoryId, String dirName)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasWrite(repositoryId)) {
			throw new PrincipalException();
		}

		DLFileProfileLocalServiceUtil.addDirectory(
			getUser().getCompanyId(), repositoryId, dirName);
	}

	public void addFile(
			String repositoryId, String fileName, String readRoles,
			String writeRoles, byte[] byteArray)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasWrite(repositoryId)) {
			throw new PrincipalException();
		}

		User user = getUser();

		DLFileProfileLocalServiceUtil.addFile(
			user.getCompanyId(), user.getUserId(), repositoryId, fileName,
			readRoles, writeRoles, byteArray);
	}

	public void deleteDirectory(String repositoryId, String dirName)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasWrite(repositoryId)) {
			throw new PrincipalException();
		}

		User user = getUser();

		Collection c = DLFileProfileFinder.findByFileName(
			getUser().getCompanyId(), repositoryId, dirName);

		Iterator itr = c.iterator();

		while (itr.hasNext()) {
			DLFileProfilePK pk = (DLFileProfilePK)itr.next();

			if (!hasAdmin(pk)) {
				throw new PrincipalException();
			}

			try {
				Lock lock = LockServiceUtil.getLock(
					DLFileProfile.class.getName(), pk);

				if (!lock.getUserId().equals(user.getUserId())) {
					throw new DuplicateLockException(lock);
				}
			}
			catch (ExpiredLockException ele) {
			}
			catch (NoSuchLockException nsle) {
			}
		}

		DLFileProfileLocalServiceUtil.deleteDirectory(
			user.getCompanyId(), repositoryId, dirName);
	}

	public void deleteFile(String repositoryId, String fileName)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasWrite(repositoryId)) {
			throw new PrincipalException();
		}

		User user = getUser();

		DLFileProfilePK pk = new DLFileProfilePK(
			user.getCompanyId(), repositoryId, fileName);

		if (!hasAdmin(pk)) {
			throw new PrincipalException();
		}

		boolean alreadyHasLock = LockServiceUtil.hasLock(
			DLFileProfile.class.getName(), pk, user.getUserId());

		if (!alreadyHasLock) {

			// Lock

			LockServiceUtil.lock(
				DLFileProfile.class.getName(), pk, pk.getCompanyId(),
				user.getUserId(), DLFileProfile.LOCK_EXPIRATION_TIME);
		}

		DLFileProfileLocalServiceUtil.deleteFile(
			pk.companyId, repositoryId, fileName);

		if (!alreadyHasLock) {

			// Unlock

			LockServiceUtil.unlock(DLFileProfile.class.getName(), pk);
		}
	}

	public void deleteFile(String repositoryId, String fileName, double version)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasWrite(repositoryId)) {
			throw new PrincipalException();
		}

		User user = getUser();

		DLFileProfilePK pk = new DLFileProfilePK(
			user.getCompanyId(), repositoryId, fileName);

		if (!hasAdmin(pk)) {
			throw new PrincipalException();
		}

		// Lock

		LockServiceUtil.lock(
			DLFileProfile.class.getName(), pk, pk.getCompanyId(),
			user.getUserId(), DLFileProfile.LOCK_EXPIRATION_TIME);

		DLFileProfileLocalServiceUtil.deleteFile(
			pk.companyId, repositoryId, fileName, version);

		// Unlock

		LockServiceUtil.unlock(DLFileProfile.class.getName(), pk);
	}

	public String[] getDirectoryNames(String repositoryId, String dirName)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasRead(repositoryId)) {
			throw new PrincipalException();
		}

		return DLFileProfileLocalServiceUtil.getDirectoryNames(
			getUser().getCompanyId(), repositoryId, dirName);
	}

	public DirectoryView getDirectoryView(String repositoryId)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasRead(repositoryId)) {
			throw new PrincipalException();
		}

		return DLFileProfileLocalServiceUtil.getDirectoryView(
			getUser().getCompanyId(), repositoryId);
	}

	public byte[] getFile(
			String companyId, String repositoryId, String fileName)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasRead(repositoryId)) {
			throw new PrincipalException();
		}

		DLFileProfilePK pk = new DLFileProfilePK(
			companyId, repositoryId, fileName);

		if (!hasRead(pk)) {
			throw new PrincipalException();
		}

		String userId = null;
		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
		}

		return DLFileProfileLocalServiceUtil.getFile(
			companyId, userId, repositoryId, fileName);
	}

	public byte[] getFile(
			String companyId, String repositoryId, String fileName,
			double version)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasRead(repositoryId)) {
			throw new PrincipalException();
		}

		DLFileProfilePK pk = new DLFileProfilePK(
			companyId, repositoryId, fileName);

		if (!hasRead(pk)) {
			throw new PrincipalException();
		}

		String userId = null;
		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
		}

		return DLFileProfileLocalServiceUtil.getFile(
			companyId, userId, repositoryId, fileName, version);
	}

	public DLFileProfile getFileProfile(String repositoryId, String fileName)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasRead(repositoryId)) {
			throw new PrincipalException();
		}

		User user = getUser();

		DLFileProfilePK pk = new DLFileProfilePK(
			user.getCompanyId(), repositoryId, fileName);

		if (!hasRead(pk)) {
			throw new PrincipalException();
		}

		return DLFileProfileLocalServiceUtil.getFileProfile(
			user.getCompanyId(), user.getUserId(), repositoryId, fileName);
	}

	public List getFileProfiles(String repositoryId, String dirName)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasRead(repositoryId)) {
			throw new PrincipalException();
		}

		User user = getUser();

		return DLFileProfileLocalServiceUtil.getFileProfiles(
			user.getCompanyId(), user.getUserId(), repositoryId, dirName);
	}

	public int getFileProfilesSize(String repositoryId)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasRead(repositoryId)) {
			throw new PrincipalException();
		}

		return DLFileProfileUtil.countByC_R(
			 getUser().getCompanyId(), repositoryId);
	}

	public void lockFile(String repositoryId, String fileName)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasWrite(repositoryId)) {
			throw new PrincipalException();
		}

		DLFileProfilePK pk = new DLFileProfilePK(
			getUser().getCompanyId(), repositoryId, fileName);

		if (!hasWrite(pk)) {
			throw new PrincipalException();
		}

		LockServiceUtil.lock(
			DLFileProfile.class.getName(), pk, pk.getCompanyId(), getUserId(),
			DLFileProfile.LOCK_EXPIRATION_TIME);
	}

	public Hits search(String repositoryId, String keywords)
		throws PortalException, SystemException {

		return search(new String[] {repositoryId}, keywords);
	}

	public Hits search(String[] repositoryIds, String keywords)
		throws PortalException, SystemException {

		return DLFileProfileLocalServiceUtil.search(
			getUser().getCompanyId(), repositoryIds, keywords);
	}

	public void unlockFile(String repositoryId, String fileName)
		throws PortalException, SystemException {

		DLFileProfilePK pk = new DLFileProfilePK(
			getUser().getCompanyId(), repositoryId, fileName);

		LockServiceUtil.unlock(DLFileProfile.class.getName(), pk);
	}

	public void updateFile(
			String repositoryId, String fileName, String sourceFileName,
			byte[] byteArray)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasWrite(repositoryId)) {
			throw new PrincipalException();
		}

		User user = getUser();

		DLFileProfilePK pk = new DLFileProfilePK(
			user.getCompanyId(), repositoryId, fileName);

		if (!hasWrite(pk)) {
			throw new PrincipalException();
		}

		boolean alreadyHasLock = LockServiceUtil.hasLock(
			DLFileProfile.class.getName(), pk, user.getUserId());

		if (!alreadyHasLock) {

			// Lock

			LockServiceUtil.lock(
				DLFileProfile.class.getName(), pk, pk.getCompanyId(),
				user.getUserId(), DLFileProfile.LOCK_EXPIRATION_TIME);
		}

		DLFileProfileLocalServiceUtil.updateFile(
			pk.companyId, user.getUserId(), repositoryId, fileName,
			sourceFileName, byteArray);

		if (!alreadyHasLock) {

			// Unlock

			LockServiceUtil.unlock(DLFileProfile.class.getName(), pk);
		}
	}

	public DLFileProfile updateFileProfile(
			String repositoryId, String fileName, String description,
			String readRoles, String writeRoles)
		throws PortalException, SystemException {

		if (!DLRepositoryServiceUtil.hasWrite(repositoryId)) {
			throw new PrincipalException();
		}

		User user = getUser();

		DLFileProfilePK pk = new DLFileProfilePK(
			user.getCompanyId(), repositoryId, fileName);

		if (!hasAdmin(pk)) {
			throw new PrincipalException();
		}

		boolean alreadyHasLock = LockServiceUtil.hasLock(
			DLFileProfile.class.getName(), pk, user.getUserId());

		if (!alreadyHasLock) {

			// Lock

			LockServiceUtil.lock(
				DLFileProfile.class.getName(), pk, pk.getCompanyId(),
				user.getUserId(), DLFileProfile.LOCK_EXPIRATION_TIME);
		}

		DLFileProfile fileProfile =
			DLFileProfileLocalServiceUtil.updateFileProfile(
				pk.companyId, repositoryId, fileName, description, readRoles,
				writeRoles);

		if (!alreadyHasLock) {

			// Unlock

			LockServiceUtil.unlock(DLFileProfile.class.getName(), pk);
		}

		return fileProfile;
	}

	// Permission methods

	public boolean hasAdmin(DLFileProfilePK pk)
		throws PortalException, SystemException {

		DLFileProfile fileProfile =
			DLFileProfileLocalServiceUtil.getFileProfile(
				pk.companyId, getUserId(), pk.repositoryId, pk.fileName);

		if ((fileProfile.getUserId().equals(getUserId())) ||
			(getUser().getCompanyId().equals(pk.companyId) &&
			 RoleServiceUtil.hasRole(
				getUserId(), Role.DOCUMENT_LIBRARY_ADMIN))) {

			return true;
		}
		else {
			return DLRepositoryServiceUtil.hasAdmin(pk.repositoryId);
		}
	}

	public boolean hasRead(DLFileProfilePK pk)
		throws PortalException, SystemException {

		User user = null;

		try {
			user = getUser();
		}
		catch (Exception e1) {
			try {
				DLFileProfile fileProfile =
					DLFileProfileLocalServiceUtil.getFileProfile(
						pk.companyId, null, pk.repositoryId, pk.fileName);

				String[] readRoles = StringUtil.split(
					fileProfile.getReadRoles());

				for (int i = 0; i < readRoles.length; i++) {
					if (readRoles[i].equals(Role.GUEST)) {
						return true;
					}
				}
			}
			catch (Exception e2) {
			}
		}

		if (user == null) {
			return false;
		}

		DLFileProfile fileProfile =
			DLFileProfileLocalServiceUtil.getFileProfile(
				pk.companyId, user.getUserId(), pk.repositoryId, pk.fileName);

		if (user.getCompanyId().equals(pk.companyId) &&
			RoleServiceUtil.hasRoles(
				user.getUserId(),
				StringUtil.split(fileProfile.getReadRoles()))) {

			return true;
		}
		else {
			return DLRepositoryServiceUtil.hasAdmin(pk.repositoryId);
		}
	}

	public boolean hasWrite(DLFileProfilePK pk)
		throws PortalException, SystemException {

		DLFileProfile fileProfile =
			DLFileProfileLocalServiceUtil.getFileProfile(
				pk.companyId, getUserId(), pk.repositoryId, pk.fileName);

		if (getUser().getCompanyId().equals(pk.companyId) &&
			RoleServiceUtil.hasRoles(
				getUserId(), StringUtil.split(fileProfile.getWriteRoles()))) {

			return true;
		}
		else {
			return DLRepositoryServiceUtil.hasAdmin(pk.repositoryId);
		}
	}

}