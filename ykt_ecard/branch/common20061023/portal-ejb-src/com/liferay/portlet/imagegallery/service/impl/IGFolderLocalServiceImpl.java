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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.service.persistence.IGFolderUtil;
import com.liferay.portlet.imagegallery.service.persistence.IGImageUtil;
import com.liferay.portlet.imagegallery.service.spring.IGFolderLocalService;
import com.liferay.portlet.imagegallery.service.spring.IGImageServiceUtil;

import java.util.Iterator;

/**
 * <a href="IGFolderLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class IGFolderLocalServiceImpl implements IGFolderLocalService {

	// Business methods

	public void deleteAll(String groupId)
		throws PortalException, SystemException {

		Iterator itr1 = IGFolderUtil.findByGroupId(groupId).iterator();

		while (itr1.hasNext()) {
			IGFolder folder = (IGFolder)itr1.next();

			Iterator itr2 = IGImageUtil.findByC_F(
				folder.getCompanyId(), folder.getFolderId()).iterator();

			while (itr2.hasNext()) {
				IGImageServiceUtil.deleteImage((IGImage)itr2.next());
			}

			IGFolderUtil.remove(folder.getFolderId());
		}
	}

	public void deleteFolder(String folderId)
		throws PortalException, SystemException {

		IGFolder folder = IGFolderUtil.findByPrimaryKey(folderId);

		deleteFolder(folder);
	}

	public void deleteFolder(IGFolder folder)
		throws PortalException, SystemException {

		Iterator itr = IGFolderUtil.findByG_C_P(
			folder.getGroupId(), folder.getCompanyId(),
			folder.getFolderId()).iterator();

		while (itr.hasNext()) {
			deleteFolder((IGFolder)itr.next());
		}

		itr = IGImageUtil.findByC_F(
			folder.getCompanyId(), folder.getFolderId()).iterator();

		while (itr.hasNext()) {
			IGImageServiceUtil.deleteImage((IGImage)itr.next());
		}

		IGFolderUtil.remove(folder.getFolderId());
	}

}