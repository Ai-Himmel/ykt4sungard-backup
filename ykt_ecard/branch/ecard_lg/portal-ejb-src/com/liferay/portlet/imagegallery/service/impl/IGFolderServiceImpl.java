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

package com.liferay.portlet.imagegallery.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.imagegallery.FolderNameException;
import com.liferay.portlet.imagegallery.NoSuchFolderException;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.service.persistence.IGFolderUtil;
import com.liferay.portlet.imagegallery.service.spring.IGFolderLocalServiceUtil;
import com.liferay.portlet.imagegallery.service.spring.IGFolderService;
import com.liferay.util.Validator;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.List;

/**
 * <a href="IGFolderServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class IGFolderServiceImpl
	extends PrincipalBean implements IGFolderService {

	// Business methods

	public IGFolder addFolder(
			String groupId, String parentFolderId, String name)
		throws PortalException, SystemException {

		parentFolderId = _getParentFolderId(parentFolderId);

		_validate(name);

		User user = getUser();

		String folderId = Long.toString(CounterServiceUtil.increment(
			IGFolder.class.getName()));

		IGFolder folder = IGFolderUtil.create(folderId);

		Date now = new Date();

		folder.setGroupId(groupId);
		folder.setCompanyId(user.getCompanyId());
		folder.setUserId(user.getUserId());
		folder.setCreateDate(now);
		folder.setModifiedDate(now);
		folder.setParentFolderId(parentFolderId);
		folder.setName(name);

		IGFolderUtil.update(folder);

		return folder;
	}

	public void deleteFolder(String folderId)
		throws PortalException, SystemException {

		IGFolderLocalServiceUtil.deleteFolder(folderId);
	}

	public void deleteFolder(IGFolder folder)
		throws PortalException, SystemException {

		IGFolderLocalServiceUtil.deleteFolder(folder);
	}

	public IGFolder getFolder(String folderId)
		throws PortalException, SystemException {

		return IGFolderUtil.findByPrimaryKey(folderId);
	}

	public List getFolders(String groupId, String companyId)
		throws SystemException {

		return IGFolderUtil.findByG_C(groupId, companyId);
	}

	public List getFolders(
			String groupId, String companyId, String parentFolderId)
		throws SystemException {

		return IGFolderUtil.findByG_C_P(groupId, companyId, parentFolderId);
	}

	public List getFolders(IGFolder folder) throws SystemException {
		return IGFolderUtil.findByG_C_P(
			folder.getGroupId(), folder.getCompanyId(), folder.getFolderId());
	}

	public int getFoldersSize(String groupId, String companyId)
		throws SystemException {

		return IGFolderUtil.countByG_C(groupId, companyId);
	}

	public int getFoldersSize(
			String groupId, String companyId, String parentFolderId)
		throws SystemException {

		return IGFolderUtil.countByG_C_P(groupId, companyId, parentFolderId);
	}

	public int getFoldersSize(IGFolder folder) throws SystemException {
		return IGFolderUtil.countByG_C_P(
			folder.getGroupId(), folder.getCompanyId(), folder.getFolderId());
	}

	public IGFolder getParentFolder(IGFolder folder)
		throws PortalException, SystemException {

		IGFolder parentFolder =
			IGFolderUtil.findByPrimaryKey(folder.getParentFolderId());

		return parentFolder;
	}

	public List getParentFolders(IGFolder folder)
		throws PortalException, SystemException {

		List parentFolders = new ArrayList();

		IGFolder tempFolder = folder;

		for (;;) {
			parentFolders.add(tempFolder);

			if (tempFolder.getParentFolderId().equals(
					IGFolder.DEFAULT_PARENT_FOLDER_ID)) {

				break;
			}

			tempFolder = IGFolderUtil.findByPrimaryKey(
				tempFolder.getParentFolderId());
		}

		Collections.reverse(parentFolders);

		return parentFolders;
	}

	public IGFolder updateFolder(
			String folderId, String parentFolderId, String name)
		throws PortalException, SystemException {

		parentFolderId = _getParentFolderId(parentFolderId);

		_validate(name);

		IGFolder folder = IGFolderUtil.findByPrimaryKey(folderId);

		folder.setModifiedDate(new Date());
		folder.setParentFolderId(parentFolderId);
		folder.setName(name);

		IGFolderUtil.update(folder);

		return folder;
	}

	// Private methods

	private String _getParentFolderId(String parentFolderId)
		throws PortalException, SystemException {

		if (!parentFolderId.equals(IGFolder.DEFAULT_PARENT_FOLDER_ID)) {

			// Ensure parent folder exists and belongs to the proper company

			try {
				IGFolder parentFolder =
					IGFolderUtil.findByPrimaryKey(parentFolderId);

				if (!parentFolder.getCompanyId().equals(
						getUser().getCompanyId())) {

					parentFolderId = IGFolder.DEFAULT_PARENT_FOLDER_ID;
				}
			}
			catch (NoSuchFolderException nsfe) {
				parentFolderId = IGFolder.DEFAULT_PARENT_FOLDER_ID;
			}
		}

		return parentFolderId;
	}

	private void _validate(String name) throws PortalException {
		if ((Validator.isNull(name)) || (name.indexOf("\\\\") != -1) ||
			(name.indexOf("//") != -1)) {

			throw new FolderNameException();
		}
	}

}