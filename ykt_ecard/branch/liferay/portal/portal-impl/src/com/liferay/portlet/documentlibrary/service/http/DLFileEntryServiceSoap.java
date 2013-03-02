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

import com.liferay.portlet.documentlibrary.service.DLFileEntryServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="DLFileEntryServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portlet.documentlibrary.service.DLFileEntryServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portlet.documentlibrary.model.DLFileEntrySoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.documentlibrary.model.DLFileEntry</code>,
 * that is translated to a <code>com.liferay.portlet.documentlibrary.model.DLFileEntrySoap</code>.
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
 * @see com.liferay.portlet.documentlibrary.service.DLFileEntryServiceUtil
 * @see com.liferay.portlet.documentlibrary.service.http.DLFileEntryServiceHttp
 * @see com.liferay.portlet.documentlibrary.service.model.DLFileEntrySoap
 *
 */
public class DLFileEntryServiceSoap {
	public static com.liferay.portlet.documentlibrary.model.DLFileEntrySoap addFileEntry(
		long folderId, java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFileEntry returnValue = DLFileEntryServiceUtil.addFileEntry(folderId,
					name, title, description, tagsEntries, extraSettings,
					byteArray, addCommunityPermissions, addGuestPermissions);

			return com.liferay.portlet.documentlibrary.model.DLFileEntrySoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntrySoap addFileEntry(
		long folderId, java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFileEntry returnValue = DLFileEntryServiceUtil.addFileEntry(folderId,
					name, title, description, tagsEntries, extraSettings,
					byteArray, communityPermissions, guestPermissions);

			return com.liferay.portlet.documentlibrary.model.DLFileEntrySoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFileEntry(long folderId, java.lang.String name)
		throws RemoteException {
		try {
			DLFileEntryServiceUtil.deleteFileEntry(folderId, name);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFileEntry(long folderId, java.lang.String name,
		double version) throws RemoteException {
		try {
			DLFileEntryServiceUtil.deleteFileEntry(folderId, name, version);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteFileEntryByTitle(long folderId,
		java.lang.String titleWithExtension) throws RemoteException {
		try {
			DLFileEntryServiceUtil.deleteFileEntryByTitle(folderId,
				titleWithExtension);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntrySoap getFileEntry(
		long folderId, java.lang.String name) throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFileEntry returnValue = DLFileEntryServiceUtil.getFileEntry(folderId,
					name);

			return com.liferay.portlet.documentlibrary.model.DLFileEntrySoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntrySoap getFileEntryByTitle(
		long folderId, java.lang.String titleWithExtension)
		throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFileEntry returnValue = DLFileEntryServiceUtil.getFileEntryByTitle(folderId,
					titleWithExtension);

			return com.liferay.portlet.documentlibrary.model.DLFileEntrySoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void lockFileEntry(long folderId, java.lang.String name)
		throws RemoteException {
		try {
			DLFileEntryServiceUtil.lockFileEntry(folderId, name);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unlockFileEntry(long folderId, java.lang.String name)
		throws RemoteException {
		try {
			DLFileEntryServiceUtil.unlockFileEntry(folderId, name);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntrySoap updateFileEntry(
		long folderId, long newFolderId, java.lang.String name,
		java.lang.String sourceFileName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray)
		throws RemoteException {
		try {
			com.liferay.portlet.documentlibrary.model.DLFileEntry returnValue = DLFileEntryServiceUtil.updateFileEntry(folderId,
					newFolderId, name, sourceFileName, title, description,
					tagsEntries, extraSettings, byteArray);

			return com.liferay.portlet.documentlibrary.model.DLFileEntrySoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(DLFileEntryServiceSoap.class);
}