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

import com.liferay.portlet.documentlibrary.service.spring.DLRepositoryServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="DLRepositoryServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLRepositoryServiceSoap {
	public static com.liferay.portlet.documentlibrary.model.DLRepositoryModel addRepository(
		java.lang.String groupId, java.lang.String readRoles,
		java.lang.String writeRoles, java.lang.String name,
		java.lang.String description) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLRepository returnValue = DLRepositoryServiceUtil.addRepository(groupId,
					readRoles, writeRoles, name, description);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteRepository(java.lang.String repositoryId)
		throws RemoteException {
		try {
			DLRepositoryServiceUtil.deleteRepository(repositoryId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteRepository(
		com.liferay.portlet.documentlibrary.model.DLRepository repository)
		throws RemoteException {
		try {
			DLRepositoryServiceUtil.deleteRepository(repository);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepositoryModel[] getRepositories(
		java.lang.String groupId) throws RemoteException {
		try {
			java.util.List returnValue = DLRepositoryServiceUtil.getRepositories(groupId);

			return (com.liferay.portlet.documentlibrary.model.DLRepository[])returnValue.toArray(new com.liferay.portlet.documentlibrary.model.DLRepository[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepositoryModel getRepository(
		java.lang.String repositoryId) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLRepository returnValue = DLRepositoryServiceUtil.getRepository(repositoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepositoryModel updateRepository(
		java.lang.String repositoryId, java.lang.String readRoles,
		java.lang.String writeRoles, java.lang.String name,
		java.lang.String description) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLRepository returnValue = DLRepositoryServiceUtil.updateRepository(repositoryId,
					readRoles, writeRoles, name, description);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String repositoryId)
		throws RemoteException {
		try {
			boolean returnValue = DLRepositoryServiceUtil.hasAdmin(repositoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasRead(java.lang.String repositoryId)
		throws RemoteException {
		try {
			boolean returnValue = DLRepositoryServiceUtil.hasRead(repositoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasWrite(java.lang.String repositoryId)
		throws RemoteException {
		try {
			boolean returnValue = DLRepositoryServiceUtil.hasWrite(repositoryId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}