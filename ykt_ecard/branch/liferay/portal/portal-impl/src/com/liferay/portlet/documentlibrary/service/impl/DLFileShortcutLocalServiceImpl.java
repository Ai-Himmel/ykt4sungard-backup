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
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portlet.documentlibrary.NoSuchFileEntryException;
import com.liferay.portlet.documentlibrary.NoSuchFolderException;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.DLFileShortcut;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl;
import com.liferay.portlet.documentlibrary.service.base.DLFileShortcutLocalServiceBaseImpl;

import java.util.Date;
import java.util.Iterator;

/**
 * <a href="DLFileShortcutLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileShortcutLocalServiceImpl
	extends DLFileShortcutLocalServiceBaseImpl {

	public DLFileShortcut addFileShortcut(
			long userId, long folderId, long toFolderId, String toName,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addFileShortcut(
			null, userId, folderId, toFolderId, toName,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public DLFileShortcut addFileShortcut(
			String uuid, long userId, long folderId, long toFolderId,
			String toName, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addFileShortcut(
			uuid, userId, folderId, toFolderId, toName,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public DLFileShortcut addFileShortcut(
			long userId, long folderId, long toFolderId, String toName,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		return addFileShortcut(
			null, userId, folderId, toFolderId, toName, null, null,
			communityPermissions, guestPermissions);
	}

	public DLFileShortcut addFileShortcut(
			String uuid, long userId, long folderId, long toFolderId,
			String toName, Boolean addCommunityPermissions,
			Boolean addGuestPermissions, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		// File shortcut

		User user = userPersistence.findByPrimaryKey(userId);
		folderId = getFolderId(user.getCompanyId(), folderId);
		DLFolder folder = dlFolderPersistence.findByPrimaryKey(folderId);
		Date now = new Date();

		validate(user, toFolderId, toName);

		long fileShortcutId = counterLocalService.increment();

		DLFileShortcut fileShortcut = dlFileShortcutPersistence.create(
			fileShortcutId);

		fileShortcut.setUuid(uuid);
		fileShortcut.setCompanyId(user.getCompanyId());
		fileShortcut.setUserId(user.getUserId());
		fileShortcut.setUserName(user.getFullName());
		fileShortcut.setCreateDate(now);
		fileShortcut.setModifiedDate(now);
		fileShortcut.setFolderId(folderId);
		fileShortcut.setToFolderId(toFolderId);
		fileShortcut.setToName(toName);

		dlFileShortcutPersistence.update(fileShortcut);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addFileShortcutResources(
				folder, fileShortcut, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addFileShortcutResources(
				folder, fileShortcut, communityPermissions, guestPermissions);
		}

		// Folder

		folder.setLastPostDate(fileShortcut.getModifiedDate());

		dlFolderPersistence.update(folder);

		return fileShortcut;
	}

	public void addFileShortcutResources(
			long fileShortcutId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		DLFileShortcut fileShortcut =
			dlFileShortcutPersistence.findByPrimaryKey(fileShortcutId);
		DLFolder folder = fileShortcut.getFolder();

		addFileShortcutResources(
			folder, fileShortcut, addCommunityPermissions, addGuestPermissions);
	}

	public void addFileShortcutResources(
			DLFolder folder, DLFileShortcut fileShortcut,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			fileShortcut.getCompanyId(), folder.getGroupId(),
			fileShortcut.getUserId(), DLFileShortcut.class.getName(),
			fileShortcut.getFileShortcutId(), false, addCommunityPermissions,
			addGuestPermissions);
	}

	public void addFileShortcutResources(
			long fileShortcutId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		DLFileShortcut fileShortcut =
			dlFileShortcutPersistence.findByPrimaryKey(fileShortcutId);
		DLFolder folder = fileShortcut.getFolder();

		addFileShortcutResources(
			folder, fileShortcut, communityPermissions, guestPermissions);
	}

	public void addFileShortcutResources(
			DLFolder folder, DLFileShortcut fileShortcut,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			fileShortcut.getCompanyId(), folder.getGroupId(),
			fileShortcut.getUserId(), DLFileShortcut.class.getName(),
			fileShortcut.getFileShortcutId(), communityPermissions,
			guestPermissions);
	}

	public void deleteFileShortcut(long fileShortcutId)
		throws PortalException, SystemException {

		dlFileShortcutPersistence.remove(fileShortcutId);
	}

	public void deleteFileShortcut(DLFileShortcut fileShortcut)
		throws PortalException, SystemException {

		// Resources

		resourceLocalService.deleteResource(
			fileShortcut.getCompanyId(), DLFileShortcut.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, fileShortcut.getFileShortcutId());

		// File shortcut

		dlFileShortcutPersistence.remove(fileShortcut.getFileShortcutId());
	}

	public void deleteFileShortcuts(long toFolderId, String toName)
		throws PortalException, SystemException {

		Iterator itr = dlFileShortcutPersistence.findByTF_TN(
			toFolderId, toName).iterator();

		while (itr.hasNext()) {
			DLFileShortcut fileShortcut = (DLFileShortcut)itr.next();

			deleteFileShortcut(fileShortcut);
		}
	}

	public DLFileShortcut getFileShortcut(long fileShortcutId)
		throws PortalException, SystemException {

		return dlFileShortcutPersistence.findByPrimaryKey(fileShortcutId);
	}

	public DLFileShortcut updateFileShortcut(
			long userId, long fileShortcutId, long folderId,
			long toFolderId, String toName)
		throws PortalException, SystemException {

		// File shortcut

		User user = userPersistence.findByPrimaryKey(userId);
		DLFolder folder = dlFolderPersistence.findByPrimaryKey(folderId);

		validate(user, toFolderId, toName);

		DLFileShortcut fileShortcut =
			dlFileShortcutPersistence.findByPrimaryKey(fileShortcutId);

		fileShortcut.setModifiedDate(new Date());
		fileShortcut.setFolderId(folderId);
		fileShortcut.setToFolderId(toFolderId);
		fileShortcut.setToName(toName);

		dlFileShortcutPersistence.update(fileShortcut);

		// Folder

		folder.setLastPostDate(fileShortcut.getModifiedDate());

		dlFolderPersistence.update(folder);

		return fileShortcut;
	}

	public void updateFileShortcuts(
			long oldToFolderId, String oldToName, long newToFolderId,
			String newToName)
		throws PortalException, SystemException {

		Iterator itr = dlFileShortcutPersistence.findByTF_TN(
			oldToFolderId, oldToName).iterator();

		while (itr.hasNext()) {
			DLFileShortcut fileShortcut = (DLFileShortcut)itr.next();

			fileShortcut.setToFolderId(newToFolderId);
			fileShortcut.setToName(newToName);

			dlFileShortcutPersistence.update(fileShortcut);
		}
	}

	protected long getFolderId(long companyId, long folderId)
		throws PortalException, SystemException {

		if (folderId != DLFolderImpl.DEFAULT_PARENT_FOLDER_ID) {

			// Ensure folder exists and belongs to the proper company

			try {
				DLFolder folder = dlFolderPersistence.findByPrimaryKey(
					folderId);

				if (companyId != folder.getCompanyId()) {
					folderId = DLFolderImpl.DEFAULT_PARENT_FOLDER_ID;
				}
			}
			catch (NoSuchFolderException nsfe) {
				folderId = DLFolderImpl.DEFAULT_PARENT_FOLDER_ID;
			}
		}

		return folderId;
	}

	protected void validate(User user, long toFolderId, String toName)
		throws PortalException, SystemException {

		DLFileEntry fileEntry = dlFileEntryLocalService.getFileEntry(
			toFolderId, toName);

		if (user.getCompanyId() != fileEntry.getCompanyId()) {
			throw new NoSuchFileEntryException();
		}
	}

}