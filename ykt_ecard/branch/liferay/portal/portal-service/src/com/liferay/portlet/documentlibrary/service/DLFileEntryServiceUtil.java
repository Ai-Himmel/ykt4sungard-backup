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

package com.liferay.portlet.documentlibrary.service;


/**
 * <a href="DLFileEntryServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.documentlibrary.service.DLFileEntryService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.documentlibrary.service.DLFileEntryServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.documentlibrary.service.DLFileEntryService
 * @see com.liferay.portlet.documentlibrary.service.DLFileEntryServiceFactory
 *
 */
public class DLFileEntryServiceUtil {
	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long folderId, java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		return dlFileEntryService.addFileEntry(folderId, name, title,
			description, tagsEntries, extraSettings, byteArray,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry addFileEntry(
		long folderId, java.lang.String name, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		return dlFileEntryService.addFileEntry(folderId, name, title,
			description, tagsEntries, extraSettings, byteArray,
			communityPermissions, guestPermissions);
	}

	public static void deleteFileEntry(long folderId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		dlFileEntryService.deleteFileEntry(folderId, name);
	}

	public static void deleteFileEntry(long folderId, java.lang.String name,
		double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		dlFileEntryService.deleteFileEntry(folderId, name, version);
	}

	public static void deleteFileEntryByTitle(long folderId,
		java.lang.String titleWithExtension)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		dlFileEntryService.deleteFileEntryByTitle(folderId, titleWithExtension);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntry(
		long folderId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		return dlFileEntryService.getFileEntry(folderId, name);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry getFileEntryByTitle(
		long folderId, java.lang.String titleWithExtension)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		return dlFileEntryService.getFileEntryByTitle(folderId,
			titleWithExtension);
	}

	public static void lockFileEntry(long folderId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		dlFileEntryService.lockFileEntry(folderId, name);
	}

	public static void unlockFileEntry(long folderId, java.lang.String name)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		dlFileEntryService.unlockFileEntry(folderId, name);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileEntry updateFileEntry(
		long folderId, long newFolderId, java.lang.String name,
		java.lang.String sourceFileName, java.lang.String title,
		java.lang.String description, java.lang.String[] tagsEntries,
		java.lang.String extraSettings, byte[] byteArray)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		DLFileEntryService dlFileEntryService = DLFileEntryServiceFactory.getService();

		return dlFileEntryService.updateFileEntry(folderId, newFolderId, name,
			sourceFileName, title, description, tagsEntries, extraSettings,
			byteArray);
	}
}