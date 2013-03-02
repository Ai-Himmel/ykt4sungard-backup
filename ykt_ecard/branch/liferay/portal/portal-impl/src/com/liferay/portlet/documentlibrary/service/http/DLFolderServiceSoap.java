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

package com.liferay.portlet.documentlibrary.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;

import com.liferay.portlet.documentlibrary.service.DLFolderServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="DLFolderServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portlet.documentlibrary.service.DLFolderServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portlet.documentlibrary.model.DLFolderSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.documentlibrary.model.DLFolder</code>,
 * that is translated to a <code>com.liferay.portlet.documentlibrary.model.DLFolderSoap</code>.
 * Methods that SOAP cannot safely wire are skipped.
 * </p>
 *
 * <p>
 * The benefits of using the SOAP utility is that it is cross platform
 * compatible. SOAP allows different languages like Java, .NET, C++, PHP, and
 * even Perl, to call the generated services. One drawback of SOAP is that it is
 * slow because it needs to serialize all calls into a text format (XML).
 * </p>
 *
 * <p>
 * You can see a list of services at
 * http://localhost:8080/tunnel-web/secure/axis. Set the property
 * <code>tunnel.servlet.hosts.allowed</code> in portal.properties to configure
 * security.
 * </p>
 *
 * <p>
 * The SOAP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.documentlibrary.service.DLFolderServiceUtil
 * @see com.liferay.portlet.documentlibrary.service.http.DLFolderServiceHttp
 * @see com.liferay.portlet.documentlibrary.service.model.DLFolderSoap
 *
 */
public class DLFolderServiceSoap {
	public static com.liferay.portlet.documentlibrary.model.DLFolderSoap addFolder(
		long plid, long parentFolderId, java.lang.String name,
		java.lang.String description, boolean addCommunityPermissions,
		boolean addGuestPermissions) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFolder returnValue = DLFolderServiceUtil.addFolder(plid,
					parentFolderId, name, description, addCommunityPermissions,
					addGuestPermissions);

			return com.liferay.portlet.documentlibrary.model.DLFolderSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolderSoap addFolder(
		long plid, long parentFolderId, java.lang.String name,
		java.lang.String description, java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFolder returnValue = DLFolderServiceUtil.addFolder(plid,
					parentFolderId, name, description, communityPermissions,
					guestPermissions);

			return com.liferay.portlet.documentlibrary.model.DLFolderSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolderSoap copyFolder(
		long plid, long sourceFolderId, long parentFolderId,
		java.lang.String name, java.lang.String description,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFolder returnValue = DLFolderServiceUtil.copyFolder(plid,
					sourceFolderId, parentFolderId, name, description,
					addCommunityPermissions, addGuestPermissions);

			return com.liferay.portlet.documentlibrary.model.DLFolderSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFolder(long folderId) throws RemoteException {
		try {
			DLFolderServiceUtil.deleteFolder(folderId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFolder(long groupId, long parentFolderId,
		java.lang.String name) throws RemoteException {
		try {
			DLFolderServiceUtil.deleteFolder(groupId, parentFolderId, name);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolderSoap getFolder(
		long folderId) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFolder returnValue = DLFolderServiceUtil.getFolder(folderId);

			return com.liferay.portlet.documentlibrary.model.DLFolderSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolderSoap getFolder(
		long groupId, long parentFolderId, java.lang.String name)
		throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFolder returnValue = DLFolderServiceUtil.getFolder(groupId,
					parentFolderId, name);

			return com.liferay.portlet.documentlibrary.model.DLFolderSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static long getFolderId(long groupId, long parentFolderId,
		java.lang.String name) throws RemoteException {
		try {
			long returnValue = DLFolderServiceUtil.getFolderId(groupId,
					parentFolderId, name);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void reIndexSearch(long companyId) throws RemoteException {
		try {
			DLFolderServiceUtil.reIndexSearch(companyId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFolderSoap updateFolder(
		long folderId, long parentFolderId, java.lang.String name,
		java.lang.String description) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFolder returnValue = DLFolderServiceUtil.updateFolder(folderId,
					parentFolderId, name, description);

			return com.liferay.portlet.documentlibrary.model.DLFolderSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(DLFolderServiceSoap.class);
}