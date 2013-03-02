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

package com.liferay.portlet.imagegallery.service.http;

import com.liferay.portlet.imagegallery.service.spring.IGFolderServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="IGFolderServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class IGFolderServiceSoap {
	public static com.liferay.portlet.imagegallery.model.IGFolderModel addFolder(
		java.lang.String groupId, java.lang.String parentFolderId,
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portlet.imagegallery.model.IGFolder returnValue = IGFolderServiceUtil.addFolder(groupId,
					parentFolderId, name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFolder(java.lang.String folderId)
		throws RemoteException {
		try {
			IGFolderServiceUtil.deleteFolder(folderId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFolder(
		com.liferay.portlet.imagegallery.model.IGFolder folder)
		throws RemoteException {
		try {
			IGFolderServiceUtil.deleteFolder(folder);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGFolderModel getFolder(
		java.lang.String folderId) throws RemoteException {
		try {
			com.liferay.portlet.imagegallery.model.IGFolder returnValue = IGFolderServiceUtil.getFolder(folderId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGFolderModel[] getFolders(
		java.lang.String groupId, java.lang.String companyId)
		throws RemoteException {
		try {
			java.util.List returnValue = IGFolderServiceUtil.getFolders(groupId,
					companyId);

			return (com.liferay.portlet.imagegallery.model.IGFolder[])returnValue.toArray(new com.liferay.portlet.imagegallery.model.IGFolder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGFolderModel[] getFolders(
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String parentFolderId) throws RemoteException {
		try {
			java.util.List returnValue = IGFolderServiceUtil.getFolders(groupId,
					companyId, parentFolderId);

			return (com.liferay.portlet.imagegallery.model.IGFolder[])returnValue.toArray(new com.liferay.portlet.imagegallery.model.IGFolder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGFolderModel[] getFolders(
		com.liferay.portlet.imagegallery.model.IGFolder folder)
		throws RemoteException {
		try {
			java.util.List returnValue = IGFolderServiceUtil.getFolders(folder);

			return (com.liferay.portlet.imagegallery.model.IGFolder[])returnValue.toArray(new com.liferay.portlet.imagegallery.model.IGFolder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getFoldersSize(java.lang.String groupId,
		java.lang.String companyId) throws RemoteException {
		try {
			int returnValue = IGFolderServiceUtil.getFoldersSize(groupId,
					companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getFoldersSize(java.lang.String groupId,
		java.lang.String companyId, java.lang.String parentFolderId)
		throws RemoteException {
		try {
			int returnValue = IGFolderServiceUtil.getFoldersSize(groupId,
					companyId, parentFolderId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getFoldersSize(
		com.liferay.portlet.imagegallery.model.IGFolder folder)
		throws RemoteException {
		try {
			int returnValue = IGFolderServiceUtil.getFoldersSize(folder);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGFolderModel getParentFolder(
		com.liferay.portlet.imagegallery.model.IGFolder folder)
		throws RemoteException {
		try {
			com.liferay.portlet.imagegallery.model.IGFolder returnValue = IGFolderServiceUtil.getParentFolder(folder);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGFolderModel[] getParentFolders(
		com.liferay.portlet.imagegallery.model.IGFolder folder)
		throws RemoteException {
		try {
			java.util.List returnValue = IGFolderServiceUtil.getParentFolders(folder);

			return (com.liferay.portlet.imagegallery.model.IGFolder[])returnValue.toArray(new com.liferay.portlet.imagegallery.model.IGFolder[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGFolderModel updateFolder(
		java.lang.String folderId, java.lang.String parentFolderId,
		java.lang.String name) throws RemoteException {
		try {
			com.liferay.portlet.imagegallery.model.IGFolder returnValue = IGFolderServiceUtil.updateFolder(folderId,
					parentFolderId, name);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}