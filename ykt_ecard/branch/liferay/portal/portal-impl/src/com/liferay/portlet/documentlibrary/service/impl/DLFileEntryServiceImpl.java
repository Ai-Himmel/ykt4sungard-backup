/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.model.User;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.impl.DLFileEntryImpl;
import com.liferay.portlet.documentlibrary.service.base.DLFileEntryServiceBaseImpl;
import com.liferay.portlet.documentlibrary.service.permission.DLFileEntryPermission;
import com.liferay.portlet.documentlibrary.service.permission.DLFolderPermission;
import com.liferay.portlet.documentlibrary.util.DLUtil;

import java.rmi.RemoteException;

/**
 * <a href="DLFileEntryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileEntryServiceImpl extends DLFileEntryServiceBaseImpl {

	public DLFileEntry addFileEntry(
			long folderId, String name, String title, String description,
			String[] tagsEntries, String extraSettings, byte[] byteArray,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		DLFolderPermission.check(
			getPermissionChecker(), folderId, ActionKeys.ADD_DOCUMENT);

		return dlFileEntryLocalService.addFileEntry(
			getUserId(), folderId, name, title, description, tagsEntries,
			extraSettings, byteArray, addCommunityPermissions,
			addGuestPermissions);
	}

	public DLFileEntry addFileEntry(
			long folderId, String name, String title, String description,
			String[] tagsEntries, String extraSettings, byte[] byteArray,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		DLFolderPermission.check(
			getPermissionChecker(), folderId, ActionKeys.ADD_DOCUMENT);

		return dlFileEntryLocalService.addFileEntry(
			getUserId(), folderId, name, title, description, tagsEntries,
			extraSettings, byteArray, communityPermissions, guestPermissions);
	}

	public void deleteFileEntry(long folderId, String name)
		throws PortalException, RemoteException, SystemException {

		User user = getUser();

		DLFileEntryPermission.check(
			getPermissionChecker(), folderId, name, ActionKeys.DELETE);

		String lockId = DLUtil.getLockId(folderId, name);

		boolean alreadyHasLock = lockService.hasLock(
			DLFileEntry.class.getName(), lockId, user.getUserId());

		if (!alreadyHasLock) {

			// Lock

			lockService.lock(
				DLFileEntry.class.getName(), lockId, user.getCompanyId(),
				user.getUserId(), DLFileEntryImpl.LOCK_EXPIRATION_TIME);
		}

		dlFileEntryLocalService.deleteFileEntry(folderId, name);

		if (!alreadyHasLock) {

			// Unlock

			lockService.unlock(DLFileEntry.class.getName(), lockId);
		}
	}

	public void deleteFileEntry(long folderId, String name, double version)
		throws PortalException, RemoteException, SystemException {

		User user = getUser();

		DLFileEntryPermission.check(
			getPermissionChecker(), folderId, name, ActionKeys.DELETE);

		String lockId = DLUtil.getLockId(folderId, name);

		boolean alreadyHasLock = lockService.hasLock(
			DLFileEntry.class.getName(), lockId, user.getUserId());

		if (!alreadyHasLock) {

			// Lock

			lockService.lock(
				DLFileEntry.class.getName(), lockId, user.getCompanyId(),
				user.getUserId(), DLFileEntryImpl.LOCK_EXPIRATION_TIME);
		}

		dlFileEntryLocalService.deleteFileEntry(folderId, name, version);

		if (!alreadyHasLock) {

			// Unlock

			lockService.unlock(DLFileEntry.class.getName(), lockId);
		}
	}

	public void deleteFileEntryByTitle(long folderId, String titleWithExtension)
		throws PortalException, RemoteException, SystemException {

		DLFileEntry fileEntry = getFileEntryByTitle(
			folderId, titleWithExtension);

		deleteFileEntry(folderId, fileEntry.getName());
	}

	public DLFileEntry getFileEntry(long folderId, String name)
		throws PortalException, SystemException {

		DLFileEntryPermission.check(
			getPermissionChecker(), folderId, name, ActionKeys.VIEW);

		return dlFileEntryLocalService.getFileEntry(folderId, name);
	}

	public DLFileEntry getFileEntryByTitle(
			long folderId, String titleWithExtension)
		throws PortalException, SystemException {

		DLFileEntry fileEntry = dlFileEntryLocalService.getFileEntryByTitle(
			folderId, titleWithExtension);

		DLFileEntryPermission.check(
			getPermissionChecker(), fileEntry, ActionKeys.VIEW);

		return fileEntry;
	}

	public void lockFileEntry(long folderId, String name)
		throws PortalException, RemoteException, SystemException {

		User user = getUser();

		String lockId = DLUtil.getLockId(folderId, name);

		lockService.lock(
			DLFileEntry.class.getName(), lockId, user.getCompanyId(),
			user.getUserId(), DLFileEntryImpl.LOCK_EXPIRATION_TIME);
	}

	public void unlockFileEntry(long folderId, String name)
		throws PortalException, RemoteException, SystemException {

		String lockId = DLUtil.getLockId(folderId, name);

		lockService.unlock(DLFileEntry.class.getName(), lockId);
	}

	public DLFileEntry updateFileEntry(
			long folderId, long newFolderId, String name, String sourceFileName,
			String title, String description, String[] tagsEntries,
			String extraSettings, byte[] byteArray)
		throws PortalException, RemoteException, SystemException {

		User user = getUser();

		DLFileEntryPermission.check(
			getPermissionChecker(), folderId, name, ActionKeys.UPDATE);

		String lockId = DLUtil.getLockId(folderId, name);

		boolean alreadyHasLock = lockService.hasLock(
			DLFileEntry.class.getName(), lockId, user.getUserId());

		if (!alreadyHasLock) {

			// Lock

			lockService.lock(
				DLFileEntry.class.getName(), lockId, user.getCompanyId(),
				user.getUserId(), DLFileEntryImpl.LOCK_EXPIRATION_TIME);
		}

		DLFileEntry fileEntry = dlFileEntryLocalService.updateFileEntry(
			getUserId(), folderId, newFolderId, name, sourceFileName, title,
			description, tagsEntries, extraSettings, byteArray);

		if (!alreadyHasLock) {

			// Unlock

			lockService.unlock(DLFileEntry.class.getName(), lockId);
		}

		return fileEntry;
	}

}