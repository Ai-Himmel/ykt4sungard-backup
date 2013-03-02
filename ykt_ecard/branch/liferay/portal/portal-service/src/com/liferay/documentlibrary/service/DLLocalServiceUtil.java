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

package com.liferay.documentlibrary.service;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.Hits;

import java.io.File;
import java.io.InputStream;

/**
 * <a href="DLLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLLocalServiceUtil {

	public static void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries,
			InputStream is)
		throws PortalException, SystemException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		dlLocalService.addFile(
			companyId, portletId, groupId, repositoryId, fileName, properties,
			tagsEntries, is);
	}

	public static void checkRoot(long companyId) throws SystemException {
		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		dlLocalService.checkRoot(companyId);
	}

	public static InputStream getFileAsStream(
			long companyId, long repositoryId, String fileName)
		throws PortalException, SystemException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		return dlLocalService.getFileAsStream(
			companyId, repositoryId, fileName);
	}

	public static InputStream getFileAsStream(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		return dlLocalService.getFileAsStream(
			companyId, repositoryId, fileName, versionNumber);
	}

	public static boolean hasFile(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		return dlLocalService.hasFile(
			companyId, repositoryId, fileName, versionNumber);
	}

	public static void move(String srcDir, String destDir)
		throws SystemException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		dlLocalService.move(srcDir, destDir);
	}

	public static Hits search(
			long companyId, String portletId, long groupId,
			long[] repositoryIds, String keywords)
		throws SystemException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		return dlLocalService.search(
			companyId, portletId, groupId, repositoryIds, keywords);
	}

	public static void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, double versionNumber, String sourceFileName,
			String properties, String[] tagsEntries, InputStream is)
		throws PortalException, SystemException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		dlLocalService.updateFile(
			companyId, portletId, groupId, repositoryId, fileName,
			versionNumber, sourceFileName, properties, tagsEntries, is);
	}

	public static void validate(String fileName, File file)
		throws PortalException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		dlLocalService.validate(fileName, file);
	}

	public static void validate(String fileName, byte[] byteArray)
		throws PortalException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		dlLocalService.validate(fileName, byteArray);
	}

	public static void validate(String fileName, InputStream is)
		throws PortalException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		dlLocalService.validate(fileName, is);
	}

	public static void validate(
			String fileName, String sourceFileName, InputStream is)
		throws PortalException {

		DLLocalService dlLocalService = DLLocalServiceFactory.getService();

		dlLocalService.validate(fileName, sourceFileName, is);
	}

}