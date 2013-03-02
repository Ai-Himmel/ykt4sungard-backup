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

package com.liferay.portlet.documentlibrary.service.spring;

/**
 * <a href="DLFileProfileRemoteServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileProfileRemoteServiceUtil {
	public static final String PORTLET_ID = "20";

	public static void addDirectory(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String dirName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();
			dlFileProfileRemoteService.addDirectory(companyId, repositoryId,
				dirName);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void addFile(java.lang.String companyId,
		java.lang.String userId, java.lang.String repositoryId,
		java.lang.String fileName, java.lang.String readRoles,
		java.lang.String writeRoles, byte[] byteArray)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();
			dlFileProfileRemoteService.addFile(companyId, userId, repositoryId,
				fileName, readRoles, writeRoles, byteArray);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteDirectory(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String dirName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();
			dlFileProfileRemoteService.deleteDirectory(companyId, repositoryId,
				dirName);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteFile(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String fileName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();
			dlFileProfileRemoteService.deleteFile(companyId, repositoryId,
				fileName);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteFile(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String fileName, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();
			dlFileProfileRemoteService.deleteFile(companyId, repositoryId,
				fileName, version);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.lang.String[] getDirectoryNames(
		java.lang.String companyId, java.lang.String repositoryId,
		java.lang.String dirName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();

			return dlFileProfileRemoteService.getDirectoryNames(companyId,
				repositoryId, dirName);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.documentlibrary.util.DirectoryView getDirectoryView(
		java.lang.String companyId, java.lang.String repositoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();

			return dlFileProfileRemoteService.getDirectoryView(companyId,
				repositoryId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static byte[] getFile(java.lang.String companyId,
		java.lang.String userId, java.lang.String repositoryId,
		java.lang.String fileName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();

			return dlFileProfileRemoteService.getFile(companyId, userId,
				repositoryId, fileName);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static byte[] getFile(java.lang.String companyId,
		java.lang.String userId, java.lang.String repositoryId,
		java.lang.String fileName, double version)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();

			return dlFileProfileRemoteService.getFile(companyId, userId,
				repositoryId, fileName, version);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileProfile getFileProfile(
		java.lang.String companyId, java.lang.String userId,
		java.lang.String repositoryId, java.lang.String fileName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();

			return dlFileProfileRemoteService.getFileProfile(companyId, userId,
				repositoryId, fileName);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getFileProfiles(java.lang.String companyId,
		java.lang.String userId, java.lang.String repositoryId,
		java.lang.String dirName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();

			return dlFileProfileRemoteService.getFileProfiles(companyId,
				userId, repositoryId, dirName);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String repositoryId,
		java.lang.String keywords)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();

			return dlFileProfileRemoteService.search(companyId, repositoryId,
				keywords);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String[] repositoryIds,
		java.lang.String keywords)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();

			return dlFileProfileRemoteService.search(companyId, repositoryIds,
				keywords);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void updateFile(java.lang.String companyId,
		java.lang.String userId, java.lang.String repositoryId,
		java.lang.String fileName, java.lang.String sourceFileName,
		byte[] byteArray)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();
			dlFileProfileRemoteService.updateFile(companyId, userId,
				repositoryId, fileName, sourceFileName, byteArray);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileProfile updateFileProfile(
		java.lang.String companyId, java.lang.String repositoryId,
		java.lang.String fileName, java.lang.String description,
		java.lang.String readRoles, java.lang.String writeRoles)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();

			return dlFileProfileRemoteService.updateFileProfile(companyId,
				repositoryId, fileName, description, readRoles, writeRoles);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void validate(java.lang.String companyId,
		java.lang.String readRoles, java.lang.String writeRoles)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			DLFileProfileRemoteService dlFileProfileRemoteService = DLFileProfileRemoteServiceFactory.getService();
			dlFileProfileRemoteService.validate(companyId, readRoles, writeRoles);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}