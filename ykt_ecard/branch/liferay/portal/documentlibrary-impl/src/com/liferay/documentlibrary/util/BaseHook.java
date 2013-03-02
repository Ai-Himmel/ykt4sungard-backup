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

package com.liferay.documentlibrary.util;

import com.liferay.documentlibrary.NoSuchFileException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.util.FileUtil;

import java.io.BufferedInputStream;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**

 * <a href="BaseHook.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class BaseHook implements Hook {

	public abstract void addDirectory(
			long companyId, long repositoryId, String dirName)
		throws PortalException, SystemException;

	public void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries,
			File file)
		throws PortalException, SystemException {

		InputStream is = null;

		try {
			is = new BufferedInputStream(new FileInputStream(file));

			addFile(
				companyId, portletId, groupId, repositoryId, fileName,
				properties, tagsEntries, is);
		}
		catch (FileNotFoundException fnfe) {
			throw new NoSuchFileException(fileName);
		}
		finally {
			try {
				if (is != null) {
					is.close();
				}
			}
			catch (IOException ioe) {
				_log.error(ioe);
			}
		}
	}

	public void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries,
			byte[] byteArray)
		throws PortalException, SystemException {

		InputStream is = new ByteArrayInputStream(byteArray);

		try {
			addFile(
				companyId, portletId, groupId, repositoryId, fileName,
				properties, tagsEntries, is);
		}
		finally {
			try {
				is.close();
			}
			catch (IOException ioe) {
				_log.error(ioe);
			}
		}
	}

	public abstract void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries,
			InputStream is)
		throws PortalException, SystemException;

	public abstract void checkRoot(long companyId) throws SystemException;

	public abstract void deleteDirectory(
			long companyId, String portletId, long repositoryId, String dirName)
		throws PortalException, SystemException;

	public abstract void deleteFile(
			long companyId, String portletId, long repositoryId,
			String fileName)
		throws PortalException, SystemException;

	public abstract void deleteFile(
			long companyId, String portletId, long repositoryId,
			String fileName, double versionNumber)
		throws PortalException, SystemException;

	public byte[] getFile(long companyId, long repositoryId, String fileName)
		throws PortalException, SystemException {

		byte[] bytes = null;

		try {
			InputStream is = getFileAsStream(companyId, repositoryId, fileName);

			bytes = FileUtil.getBytes(is);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}

		return bytes;
	}

	public byte[] getFile(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException {

		byte[] bytes = null;

		try {
			InputStream is = getFileAsStream(
				companyId, repositoryId, fileName, versionNumber);

			bytes = FileUtil.getBytes(is);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}

		return bytes;
	}

	public InputStream getFileAsStream(
			long companyId, long repositoryId, String fileName)
		throws PortalException, SystemException {

		return getFileAsStream(companyId, repositoryId, fileName, 0);
	}

	public abstract InputStream getFileAsStream(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException;

	public abstract String[] getFileNames(
			long companyId, long repositoryId, String dirName)
		throws PortalException, SystemException;

	public abstract long getFileSize(
			long companyId, long repositoryId, String fileName)
		throws PortalException, SystemException;

	public abstract boolean hasFile(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException;

	public abstract void move(String srcDir, String destDir)
		throws SystemException;

	public abstract void reIndex(String[] ids) throws SearchException;

	public void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, double versionNumber, String sourceFileName,
			String properties, String[] tagsEntries, File file)
		throws PortalException, SystemException {

		InputStream is = null;

		try {
			is = new BufferedInputStream(new FileInputStream(file));

			updateFile(
				companyId, portletId, groupId, repositoryId, fileName,
				versionNumber, sourceFileName, properties, tagsEntries, is);
		}
		catch (FileNotFoundException fnfe) {
			throw new NoSuchFileException(fileName);
		}
		finally {
			try {
				if (is != null) {
					is.close();
				}
			}
			catch (IOException ioe) {
				_log.error(ioe);
			}
		}
	}

	public void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, double versionNumber, String sourceFileName,
			String properties, String[] tagsEntries, byte[] byteArray)
		throws PortalException, SystemException {

		InputStream is = new ByteArrayInputStream(byteArray);

		try {
			updateFile(
				companyId, portletId, groupId, repositoryId, fileName,
				versionNumber, sourceFileName, properties, tagsEntries, is);
		}
		finally {
			try {
				is.close();
			}
			catch (IOException ioe) {
				_log.error(ioe);
			}
		}
	}

	public abstract void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, double versionNumber, String sourceFileName,
			String properties, String[] tagsEntries, InputStream is)
		throws PortalException, SystemException;

	public abstract void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			long newRepositoryId, String fileName)
		throws PortalException, SystemException;

	private static Log _log = LogFactory.getLog(BaseHook.class);

}