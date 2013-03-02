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
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.service.base.DLFolderServiceBaseImpl;
import com.liferay.portlet.documentlibrary.service.permission.DLFileEntryPermission;
import com.liferay.portlet.documentlibrary.service.permission.DLFolderPermission;
import com.liferay.util.FileUtil;
import com.liferay.util.PwdGenerator;
import com.liferay.util.SystemProperties;
import com.liferay.util.Time;

import java.io.File;
import java.io.InputStream;

import java.util.Iterator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="DLFolderServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFolderServiceImpl extends DLFolderServiceBaseImpl {

	public DLFolder addFolder(
			long plid, long parentFolderId, String name, String description,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		DLFolderPermission.check(
			getPermissionChecker(), plid, parentFolderId,
			ActionKeys.ADD_FOLDER);

		return dlFolderLocalService.addFolder(
			getUserId(), plid, parentFolderId, name, description,
			addCommunityPermissions, addGuestPermissions);
	}

	public DLFolder addFolder(
			long plid, long parentFolderId, String name, String description,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		DLFolderPermission.check(
			getPermissionChecker(), plid, parentFolderId,
			ActionKeys.ADD_FOLDER);

		return dlFolderLocalService.addFolder(
			getUserId(), plid, parentFolderId, name, description,
			communityPermissions, guestPermissions);
	}

	public DLFolder copyFolder(
			long plid, long sourceFolderId, long parentFolderId, String name,
			String description, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		DLFolderPermission.check(
			getPermissionChecker(), sourceFolderId, ActionKeys.VIEW);

		DLFolder srcFolder = getFolder(sourceFolderId);

		DLFolderPermission.check(
			getPermissionChecker(), plid, parentFolderId,
			ActionKeys.ADD_FOLDER);

		DLFolder destFolder = addFolder(
			plid, parentFolderId, name, description, addCommunityPermissions,
			addGuestPermissions);

		copyFolder(
			srcFolder, destFolder, addCommunityPermissions,
			addGuestPermissions);

		return destFolder;
	}

	public void deleteFolder(long folderId)
		throws PortalException, SystemException {

		DLFolderPermission.check(
			getPermissionChecker(), folderId, ActionKeys.DELETE);

		dlFolderLocalService.deleteFolder(folderId);
	}

	public void deleteFolder(long groupId, long parentFolderId, String name)
		throws PortalException, SystemException {

		DLFolder folder = getFolder(groupId, parentFolderId, name);

		deleteFolder(folder.getFolderId());
	}

	public DLFolder getFolder(long folderId)
		throws PortalException, SystemException {

		DLFolderPermission.check(
			getPermissionChecker(), folderId, ActionKeys.VIEW);

		return dlFolderLocalService.getFolder(folderId);
	}

	public DLFolder getFolder(long groupId, long parentFolderId, String name)
		throws PortalException, SystemException {

		DLFolder folder = dlFolderLocalService.getFolder(
			groupId, parentFolderId, name);

		DLFolderPermission.check(
			getPermissionChecker(), folder, ActionKeys.VIEW);

		return folder;
	}

	public long getFolderId(long groupId, long parentFolderId, String name)
		throws PortalException, SystemException {

		DLFolder folder = getFolder(groupId, parentFolderId, name);

		return folder.getFolderId();
	}

	public void reIndexSearch(long companyId)
		throws PortalException, SystemException {

		if (!getPermissionChecker().isOmniadmin()) {
			throw new PrincipalException();
		}

		String[] ids = new String[] {String.valueOf(companyId)};

		dlFolderLocalService.reIndex(ids);
	}

	public DLFolder updateFolder(
			long folderId, long parentFolderId, String name, String description)
		throws PortalException, SystemException {

		DLFolderPermission.check(
			getPermissionChecker(), folderId, ActionKeys.UPDATE);

		return dlFolderLocalService.updateFolder(
			folderId, parentFolderId, name, description);
	}

	protected void copyFolder(
			DLFolder srcFolder, DLFolder destFolder,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		long companyId = srcFolder.getCompanyId();
		long userId = getUserId();
		long srcFolderId = srcFolder.getFolderId();
		long destFolderId = destFolder.getFolderId();

		// Copy all viewable files

		Iterator itr = dlFileEntryLocalService.getFileEntries(
			srcFolderId).iterator();

		while (itr.hasNext()) {
			DLFileEntry fileEntry = (DLFileEntry)itr.next();

			if (DLFileEntryPermission.contains(
				getPermissionChecker(), fileEntry, ActionKeys.VIEW)) {

				String name = fileEntry.getTitleWithExtension();
				String title = fileEntry.getTitleWithExtension();
				String description = fileEntry.getDescription();
				String[] tagsEntries = null;
				String extraSettings = fileEntry.getExtraSettings();

				File file = null;

				try {
					InputStream is = dlFileEntryLocalService.getFileAsStream(
						companyId, userId, srcFolderId, fileEntry.getName());

					String fileName =
						SystemProperties.get(SystemProperties.TMP_DIR) +
							StringPool.SLASH + Time.getTimestamp() +
								PwdGenerator.getPassword(PwdGenerator.KEY2, 8);

					file = new File(fileName);

					FileUtil.write(file, is);
				}
				catch (Exception e) {
					_log.error(e, e);

					continue;
				}

				dlFileEntryLocalService.addFileEntry(
					userId, destFolderId, name, title, description, tagsEntries,
					extraSettings, file, addCommunityPermissions,
					addGuestPermissions);
			}
		}

		String uuid = StringPool.BLANK;
		long groupId = destFolder.getGroupId();
		Boolean addCommunityPermissionsObj = Boolean.valueOf(
			addCommunityPermissions);
		Boolean addGuestPermissionsObj = Boolean.valueOf(addGuestPermissions);
		String[] communityPermissions = null;
		String[] guestPermissions = null;

		// Copy all viewable folders

		itr = dlFolderLocalService.getFolders(
			srcFolder.getGroupId(), srcFolderId).iterator();

		while (itr.hasNext()) {
			DLFolder folder = (DLFolder)itr.next();

			if (DLFolderPermission.contains(
					getPermissionChecker(), folder, ActionKeys.VIEW)) {

				String name = folder.getName();
				String description = folder.getDescription();

				DLFolder subfolder = dlFolderLocalService.addFolderToGroup(
					uuid, userId, groupId, destFolderId, name, description,
					addCommunityPermissionsObj, addGuestPermissionsObj,
					communityPermissions, guestPermissions);

				// Recursively copy all subfolders

				copyFolder(
					folder, subfolder, addCommunityPermissions,
					addGuestPermissions);
			}
		}
	}

	private static Log _log = LogFactory.getLog(DLFolderServiceImpl.class);

}