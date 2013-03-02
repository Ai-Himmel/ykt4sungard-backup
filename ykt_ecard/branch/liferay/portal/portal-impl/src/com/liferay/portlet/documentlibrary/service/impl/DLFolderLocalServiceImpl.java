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

import com.liferay.documentlibrary.DuplicateFileException;
import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portlet.documentlibrary.DuplicateFolderNameException;
import com.liferay.portlet.documentlibrary.FolderNameException;
import com.liferay.portlet.documentlibrary.NoSuchFileEntryException;
import com.liferay.portlet.documentlibrary.NoSuchFolderException;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl;
import com.liferay.portlet.documentlibrary.service.base.DLFolderLocalServiceBaseImpl;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="DLFolderLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFolderLocalServiceImpl extends DLFolderLocalServiceBaseImpl {

	public DLFolder addFolder(
			long userId, long plid, long parentFolderId, String name,
			String description, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addFolder(
			null, userId, plid, parentFolderId, name, description,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public DLFolder addFolder(
			String uuid, long userId, long plid, long parentFolderId,
			String name, String description, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addFolder(
			uuid, userId, plid, parentFolderId, name, description,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public DLFolder addFolder(
			long userId, long plid, long parentFolderId, String name,
			String description, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		return addFolder(
			null, userId, plid, parentFolderId, name, description, null, null,
			communityPermissions, guestPermissions);
	}

	public DLFolder addFolder(
			String uuid, long userId, long plid, long parentFolderId,
			String name, String description, Boolean addCommunityPermissions,
			Boolean addGuestPermissions, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		long groupId = PortalUtil.getPortletGroupId(plid);

		return addFolderToGroup(
			uuid, userId, groupId, parentFolderId, name, description,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions);
	}

	public DLFolder addFolderToGroup(
			String uuid, long userId, long groupId, long parentFolderId,
			String name, String description, Boolean addCommunityPermissions,
			Boolean addGuestPermissions, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		// Folder

		User user = userPersistence.findByPrimaryKey(userId);
		parentFolderId = getParentFolderId(groupId, parentFolderId);
		Date now = new Date();

		validate(groupId, parentFolderId, name);

		long folderId = counterLocalService.increment();

		DLFolder folder = dlFolderPersistence.create(folderId);

		folder.setUuid(uuid);
		folder.setGroupId(groupId);
		folder.setCompanyId(user.getCompanyId());
		folder.setUserId(user.getUserId());
		folder.setCreateDate(now);
		folder.setModifiedDate(now);
		folder.setParentFolderId(parentFolderId);
		folder.setName(name);
		folder.setDescription(description);

		dlFolderPersistence.update(folder);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addFolderResources(
				folder, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addFolderResources(folder, communityPermissions, guestPermissions);
		}

		// Layout

		String[] pathArray = folder.getPathArray();

		if (PropsValues.DL_LAYOUTS_SYNC_ENABLED &&
			(parentFolderId != DLFolderImpl.DEFAULT_PARENT_FOLDER_ID)) {

			String layoutsSyncPrivateFolder = GetterUtil.getString(
				PropsUtil.get(PropsUtil.DL_LAYOUTS_SYNC_PRIVATE_FOLDER));
			String layoutsSyncPublicFolder = GetterUtil.getString(
				PropsUtil.get(PropsUtil.DL_LAYOUTS_SYNC_PUBLIC_FOLDER));

			if (pathArray[0].equals(layoutsSyncPrivateFolder) ||
				pathArray[0].equals(layoutsSyncPublicFolder)) {

				boolean privateLayout = true;

				if (pathArray[0].equals(layoutsSyncPublicFolder)) {
					privateLayout = false;
				}

				long parentLayoutId = LayoutImpl.DEFAULT_PARENT_LAYOUT_ID;
				String title = StringPool.BLANK;
				String layoutDescription = StringPool.BLANK;
				String type = LayoutImpl.TYPE_PORTLET;
				boolean hidden = false;
				String friendlyURL = StringPool.BLANK;

				Layout dlFolderLayout = null;

				try {
					dlFolderLayout = layoutLocalService.getDLFolderLayout(
						folder.getParentFolderId());

					parentLayoutId = dlFolderLayout.getLayoutId();
				}
				catch (NoSuchLayoutException nsle) {
				}

				layoutLocalService.addLayout(
					userId, groupId, privateLayout, parentLayoutId, name, title,
					layoutDescription, type, hidden, friendlyURL,
					folder.getFolderId());
			}
		}

		return folder;
	}

	public void addFolderResources(
			long folderId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		DLFolder folder = dlFolderPersistence.findByPrimaryKey(folderId);

		addFolderResources(
			folder, addCommunityPermissions, addGuestPermissions);
	}

	public void addFolderResources(
			DLFolder folder, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			folder.getCompanyId(), folder.getGroupId(), folder.getUserId(),
			DLFolder.class.getName(), folder.getFolderId(), false,
			addCommunityPermissions, addGuestPermissions);
	}

	public void addFolderResources(
			long folderId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		DLFolder folder = dlFolderPersistence.findByPrimaryKey(folderId);

		addFolderResources(folder, communityPermissions, guestPermissions);
	}

	public void addFolderResources(
			DLFolder folder, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			folder.getCompanyId(), folder.getGroupId(), folder.getUserId(),
			DLFolder.class.getName(), folder.getFolderId(),
			communityPermissions, guestPermissions);
	}

	public void deleteFolder(long folderId)
		throws PortalException, SystemException {

		DLFolder folder = dlFolderPersistence.findByPrimaryKey(folderId);

		deleteFolder(folder);
	}

	public void deleteFolder(DLFolder folder)
		throws PortalException, SystemException {

		// Folders

		Iterator itr = dlFolderPersistence.findByG_P(
			folder.getGroupId(), folder.getFolderId()).iterator();

		while (itr.hasNext()) {
			DLFolder curFolder = (DLFolder)itr.next();

			deleteFolder(curFolder);
		}

		// File entries

		dlFileEntryLocalService.deleteFileEntries(folder.getFolderId());

		// Resources

		resourceLocalService.deleteResource(
			folder.getCompanyId(), DLFolder.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL, folder.getFolderId());

		// WebDAVProps

		webDAVPropsLocalService.deleteWebDAVProps(
			DLFolder.class.getName(), folder.getPrimaryKey());

		// Folder

		dlFolderPersistence.remove(folder.getFolderId());
	}

	public void deleteFolders(long groupId)
		throws PortalException, SystemException {

		Iterator itr = dlFolderPersistence.findByG_P(
			groupId, DLFolderImpl.DEFAULT_PARENT_FOLDER_ID).iterator();

		while (itr.hasNext()) {
			DLFolder folder = (DLFolder)itr.next();

			deleteFolder(folder);
		}
	}

	public DLFolder getFolder(long folderId)
		throws PortalException, SystemException {

		return dlFolderPersistence.findByPrimaryKey(folderId);
	}

	public DLFolder getFolder(long groupId, long parentFolderId, String name)
		throws PortalException, SystemException {

		return dlFolderPersistence.findByG_P_N(groupId, parentFolderId, name);
	}

	public List getFolders(long companyId) throws SystemException {
		return dlFolderPersistence.findByCompanyId(companyId);
	}

	public List getFolders(long groupId, long parentFolderId)
		throws SystemException {

		return dlFolderPersistence.findByG_P(groupId, parentFolderId);
	}

	public List getFolders(
			long groupId, long parentFolderId, int begin, int end)
		throws SystemException {

		return dlFolderPersistence.findByG_P(
			groupId, parentFolderId, begin, end);
	}

	public int getFoldersCount(long groupId, long parentFolderId)
		throws SystemException {

		return dlFolderPersistence.countByG_P(groupId, parentFolderId);
	}

	public void getSubfolderIds(List folderIds, long groupId, long folderId)
		throws SystemException {

		Iterator itr = dlFolderPersistence.findByG_P(
			groupId, folderId).iterator();

		while (itr.hasNext()) {
			DLFolder folder = (DLFolder)itr.next();

			folderIds.add(new Long(folder.getFolderId()));

			getSubfolderIds(
				folderIds, folder.getGroupId(), folder.getFolderId());
		}
	}

	public void reIndex(String[] ids) throws SystemException {
		long companyId = GetterUtil.getLong(ids[0]);

		try {
			List folders = getFolders(companyId);

			for (int i = 0; i < folders.size(); i++) {
				DLFolder folder = (DLFolder)folders.get(i);

				String portletId = PortletKeys.DOCUMENT_LIBRARY;
				long groupId = folder.getGroupId();
				long folderId = folder.getFolderId();

				String[] newIds = {
					String.valueOf(companyId), portletId,
					String.valueOf(groupId), String.valueOf(folderId)
				};

				dlService.reIndex(newIds);
			}
		}
		catch (SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public Hits search(
			long companyId, long groupId, long[] folderIds, String keywords)
		throws PortalException, SystemException {

		return dlLocalService.search(
			companyId, PortletKeys.DOCUMENT_LIBRARY, groupId, folderIds,
			keywords);
	}

	public DLFolder updateFolder(
			long folderId, long parentFolderId, String name,
			String description)
		throws PortalException, SystemException {

		DLFolder folder = dlFolderPersistence.findByPrimaryKey(folderId);

		parentFolderId = getParentFolderId(folder, parentFolderId);

		validate(folder.getGroupId(), parentFolderId, name);

		folder.setModifiedDate(new Date());
		folder.setParentFolderId(parentFolderId);
		folder.setName(name);
		folder.setDescription(description);

		dlFolderPersistence.update(folder);

		if (PropsValues.DL_LAYOUTS_SYNC_ENABLED) {
			String privateFolder = GetterUtil.getString(PropsUtil.get(
				PropsUtil.DL_LAYOUTS_SYNC_PRIVATE_FOLDER));

			boolean privateLayout = false;

			String[] path = folder.getPathArray();

			if (path[0].equals(privateFolder)) {
				privateLayout = true;
			}

			Layout layout = layoutLocalService.getDLFolderLayout(
				folder.getFolderId());

			layout.setName(folder.getName());

			layoutLocalService.updateName(
				folder.getGroupId(), privateLayout, layout.getLayoutId(),
				folder.getName(),
				LocaleUtil.toLanguageId(LocaleUtil.getDefault()));
		}

		return folder;
	}

	protected long getParentFolderId(long groupId, long parentFolderId)
		throws SystemException {

		if (parentFolderId != DLFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
			DLFolder parentFolder = dlFolderPersistence.fetchByPrimaryKey(
				parentFolderId);

			if ((parentFolder == null) ||
				(groupId != parentFolder.getGroupId())) {

				parentFolderId = DLFolderImpl.DEFAULT_PARENT_FOLDER_ID;
			}
		}

		return parentFolderId;
	}

	protected long getParentFolderId(DLFolder folder, long parentFolderId)
		throws SystemException {

		if (parentFolderId == DLFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
			return parentFolderId;
		}

		if (folder.getFolderId() == parentFolderId) {
			return folder.getParentFolderId();
		}
		else {
			DLFolder parentFolder = dlFolderPersistence.fetchByPrimaryKey(
				parentFolderId);

			if ((parentFolder == null) ||
				(folder.getGroupId() != parentFolder.getGroupId())) {

				return folder.getParentFolderId();
			}

			List subfolderIds = new ArrayList();

			getSubfolderIds(
				subfolderIds, folder.getGroupId(), folder.getFolderId());

			if (subfolderIds.contains(new Long(parentFolderId))) {
				return folder.getParentFolderId();
			}

			return parentFolderId;
		}
	}

	protected void validate(long groupId, long parentFolderId, String name)
		throws PortalException, SystemException {

		if ((Validator.isNull(name)) || (name.indexOf("\\\\") != -1) ||
			(name.indexOf("//") != -1)) {

			throw new FolderNameException();
		}

		try {
			dlFileEntryLocalService.getFileEntryByTitle(parentFolderId, name);

			throw new DuplicateFileException();
		}
		catch (NoSuchFileEntryException nsfee) {
		}

		try {
			dlFolderPersistence.findByG_P_N(groupId, parentFolderId, name);

			throw new DuplicateFolderNameException();
		}
		catch (NoSuchFolderException nsfe) {
		}
	}

}