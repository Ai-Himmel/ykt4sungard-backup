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

package com.liferay.documentlibrary.service.impl;

import com.liferay.documentlibrary.DirectoryNameException;
import com.liferay.documentlibrary.service.DLLocalServiceUtil;
import com.liferay.documentlibrary.service.DLService;
import com.liferay.documentlibrary.util.Hook;
import com.liferay.documentlibrary.util.HookFactory;
import com.liferay.documentlibrary.util.Indexer;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.SearchException;

import java.io.File;

/**
 * <a href="DLServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Michael Young
 *
 */
public class DLServiceImpl implements DLService {

	public static final String GROUP_NAME = DLServiceImpl.class.getName();

	public static final String[] GROUP_NAME_ARRAY = new String[] { GROUP_NAME };

	public static final String VERSION = "_VERSION_";

	public void addDirectory(long companyId, long repositoryId, String dirName)
		throws PortalException, SystemException {

		if ((dirName == null || dirName.equals("/")) ||
			(dirName.indexOf("\\\\") != -1) ||
			(dirName.indexOf("//") != -1) ||
			(dirName.indexOf(":") != -1) ||
			(dirName.indexOf("*") != -1) ||
			(dirName.indexOf("?") != -1) ||
			(dirName.indexOf("\"") != -1) ||
			(dirName.indexOf("<") != -1) ||
			(dirName.indexOf(">") != -1) ||
			(dirName.indexOf("|") != -1) ||
			(dirName.indexOf("&") != -1) ||
			(dirName.indexOf("[") != -1) ||
			(dirName.indexOf("]") != -1) ||
			(dirName.indexOf("'") != -1)) {

			throw new DirectoryNameException(dirName);
		}

		Hook hook = HookFactory.getInstance();

		hook.addDirectory(companyId, repositoryId, dirName);
	}

	public void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries, File file)
		throws PortalException, SystemException {

		DLLocalServiceUtil.validate(fileName, file);

		Hook hook = HookFactory.getInstance();

		hook.addFile(
			companyId, portletId, groupId, repositoryId, fileName, properties,
			tagsEntries, file);
	}

	public void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries,
			byte[] byteArray)
		throws PortalException, SystemException {

		DLLocalServiceUtil.validate(fileName, byteArray);

		Hook hook = HookFactory.getInstance();

		hook.addFile(
			companyId, portletId, groupId, repositoryId, fileName, properties,
			tagsEntries, byteArray);
	}

	public void deleteDirectory(
			long companyId, String portletId, long repositoryId, String dirName)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		hook.deleteDirectory(companyId, portletId, repositoryId, dirName);
	}

	public void deleteFile(
			long companyId, String portletId, long repositoryId,
			String fileName)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		hook.deleteFile(companyId, portletId, repositoryId, fileName);
	}

	public void deleteFile(
			long companyId, String portletId, long repositoryId,
			String fileName, double versionNumber)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		hook.deleteFile(
			companyId, portletId, repositoryId, fileName, versionNumber);
	}

	public byte[] getFile(long companyId, long repositoryId, String fileName)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		return hook.getFile(companyId, repositoryId, fileName);
	}

	public byte[] getFile(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		return hook.getFile(companyId, repositoryId, fileName, versionNumber);
	}

	public String[] getFileNames(
			long companyId, long repositoryId, String dirName)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		return hook.getFileNames(companyId, repositoryId, dirName);
	}

	public long getFileSize(
			long companyId, long repositoryId, String fileName)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		return hook.getFileSize(companyId, repositoryId, fileName);
	}

	public void reIndex(String[] ids) throws SystemException {
		try {
			Indexer indexer = new Indexer();

			indexer.reIndex(ids);
		}
		catch (SearchException se) {
			throw new SystemException(se);
		}
	}

	public void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, double versionNumber, String sourceFileName,
			String properties, String[] tagsEntries, File file)
		throws PortalException, SystemException {

		DLLocalServiceUtil.validate(fileName, file);

		Hook hook = HookFactory.getInstance();

		hook.updateFile(
			companyId, portletId, groupId, repositoryId, fileName,
			versionNumber, sourceFileName, properties, tagsEntries, file);
	}

	public void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, double versionNumber, String sourceFileName,
			String properties, String[] tagsEntries, byte[] byteArray)
		throws PortalException, SystemException {

		DLLocalServiceUtil.validate(fileName, byteArray);

		Hook hook = HookFactory.getInstance();

		hook.updateFile(
			companyId, portletId, groupId, repositoryId, fileName,
			versionNumber, sourceFileName, properties, tagsEntries, byteArray);
	}

	public void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			long newRepositoryId, String fileName)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		hook.updateFile(
			companyId, portletId, groupId, repositoryId, newRepositoryId,
			fileName);
	}

}