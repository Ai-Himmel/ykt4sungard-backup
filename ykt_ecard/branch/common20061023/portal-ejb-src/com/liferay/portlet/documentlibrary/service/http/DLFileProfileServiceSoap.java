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

package com.liferay.portlet.documentlibrary.service.http;

import com.liferay.portlet.documentlibrary.service.spring.DLFileProfileServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="DLFileProfileServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileProfileServiceSoap {
	public static void addDirectory(java.lang.String repositoryId,
		java.lang.String dirName) throws RemoteException {
		try {
			DLFileProfileServiceUtil.addDirectory(repositoryId, dirName);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void addFile(java.lang.String repositoryId,
		java.lang.String fileName, java.lang.String readRoles,
		java.lang.String writeRoles, byte[] byteArray)
		throws RemoteException {
		try {
			DLFileProfileServiceUtil.addFile(repositoryId, fileName, readRoles,
				writeRoles, byteArray);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteDirectory(java.lang.String repositoryId,
		java.lang.String dirName) throws RemoteException {
		try {
			DLFileProfileServiceUtil.deleteDirectory(repositoryId, dirName);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFile(java.lang.String repositoryId,
		java.lang.String fileName) throws RemoteException {
		try {
			DLFileProfileServiceUtil.deleteFile(repositoryId, fileName);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFile(java.lang.String repositoryId,
		java.lang.String fileName, double version) throws RemoteException {
		try {
			DLFileProfileServiceUtil.deleteFile(repositoryId, fileName, version);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String[] getDirectoryNames(
		java.lang.String repositoryId, java.lang.String dirName)
		throws RemoteException {
		try {
			java.lang.String[] returnValue = DLFileProfileServiceUtil.getDirectoryNames(repositoryId,
					dirName);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.documentlibrary.util.DirectoryView getDirectoryView(
		java.lang.String repositoryId) throws RemoteException {
		try {
			com.liferay.documentlibrary.util.DirectoryView returnValue = DLFileProfileServiceUtil.getDirectoryView(repositoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static byte[] getFile(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String fileName)
		throws RemoteException {
		try {
			byte[] returnValue = DLFileProfileServiceUtil.getFile(companyId,
					repositoryId, fileName);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static byte[] getFile(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String fileName, double version)
		throws RemoteException {
		try {
			byte[] returnValue = DLFileProfileServiceUtil.getFile(companyId,
					repositoryId, fileName, version);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileProfileModel getFileProfile(
		java.lang.String repositoryId, java.lang.String fileName)
		throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFileProfile returnValue = DLFileProfileServiceUtil.getFileProfile(repositoryId,
					fileName);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileProfileModel[] getFileProfiles(
		java.lang.String repositoryId, java.lang.String dirName)
		throws RemoteException {
		try {
			java.util.List returnValue = DLFileProfileServiceUtil.getFileProfiles(repositoryId,
					dirName);

			return (com.liferay.portlet.documentlibrary.model.DLFileProfile[])returnValue.toArray(new com.liferay.portlet.documentlibrary.model.DLFileProfile[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getFileProfilesSize(java.lang.String repositoryId)
		throws RemoteException {
		try {
			int returnValue = DLFileProfileServiceUtil.getFileProfilesSize(repositoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void lockFile(java.lang.String repositoryId,
		java.lang.String fileName) throws RemoteException {
		try {
			DLFileProfileServiceUtil.lockFile(repositoryId, fileName);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String repositoryId, java.lang.String keywords)
		throws RemoteException {
		try {
			com.liferay.util.lucene.Hits returnValue = DLFileProfileServiceUtil.search(repositoryId,
					keywords);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String[] repositoryIds, java.lang.String keywords)
		throws RemoteException {
		try {
			com.liferay.util.lucene.Hits returnValue = DLFileProfileServiceUtil.search(repositoryIds,
					keywords);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void unlockFile(java.lang.String repositoryId,
		java.lang.String fileName) throws RemoteException {
		try {
			DLFileProfileServiceUtil.unlockFile(repositoryId, fileName);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void updateFile(java.lang.String repositoryId,
		java.lang.String fileName, java.lang.String sourceFileName,
		byte[] byteArray) throws RemoteException {
		try {
			DLFileProfileServiceUtil.updateFile(repositoryId, fileName,
				sourceFileName, byteArray);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileProfileModel updateFileProfile(
		java.lang.String repositoryId, java.lang.String fileName,
		java.lang.String description, java.lang.String readRoles,
		java.lang.String writeRoles) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFileProfile returnValue = DLFileProfileServiceUtil.updateFileProfile(repositoryId,
					fileName, description, readRoles, writeRoles);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileProfilePK pk)
		throws RemoteException {
		try {
			boolean returnValue = DLFileProfileServiceUtil.hasAdmin(pk);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasRead(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileProfilePK pk)
		throws RemoteException {
		try {
			boolean returnValue = DLFileProfileServiceUtil.hasRead(pk);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasWrite(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileProfilePK pk)
		throws RemoteException {
		try {
			boolean returnValue = DLFileProfileServiceUtil.hasWrite(pk);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}