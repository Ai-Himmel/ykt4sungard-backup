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

package com.liferay.documentlibrary.service.impl;

import com.liferay.documentlibrary.DirectoryNameException;
import com.liferay.documentlibrary.DuplicateDirectoryException;
import com.liferay.documentlibrary.DuplicateFileException;
import com.liferay.documentlibrary.FileNameException;
import com.liferay.documentlibrary.FileSizeException;
import com.liferay.documentlibrary.NoSuchDirectoryException;
import com.liferay.documentlibrary.NoSuchFileException;
import com.liferay.documentlibrary.SourceFileNameException;
import com.liferay.documentlibrary.service.spring.DLService;
import com.liferay.documentlibrary.util.DirectoryLister;
import com.liferay.documentlibrary.util.DirectoryView;
import com.liferay.documentlibrary.util.Indexer;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.FileUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.SimpleCachePool;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lucene.Hits;
import com.liferay.util.lucene.IndexerException;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.apache.lucene.analysis.WhitespaceAnalyzer;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.TermQuery;

/**
 * <a href="DLServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class DLServiceImpl implements DLService {

	public static final String VERSION = "_VERSION_";

	public void addDirectory(
			String companyId, String repositoryId, String dirName)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

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
			(dirName.indexOf("&") != -1)) {

			throw new DirectoryNameException(dirName);
		}

		File directory = new File(
			PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId + dirName);

		if (directory.exists()) {
			throw new DuplicateDirectoryException(dirName);
		}
		else {
			directory.mkdirs();
		}

		_getDirectoryViewsPool().remove(coRepoId);
	}

	public void addFile(
			String companyId, String portletId, String groupId,
			String repositoryId, String fileName, byte[] byteArray)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		if ((fileName.indexOf("\\\\") != -1) ||
			(fileName.indexOf("//") != -1) ||
			(fileName.indexOf(":") != -1) ||
			(fileName.indexOf("*") != -1) ||
			(fileName.indexOf("?") != -1) ||
			(fileName.indexOf("\"") != -1) ||
			(fileName.indexOf("<") != -1) ||
			(fileName.indexOf(">") != -1) ||
			(fileName.indexOf("|") != -1) ||
			(fileName.indexOf("&") != -1)) {

			throw new FileNameException(fileName);
		}

		boolean validFileExtension = false;

		String[] fileExtensions =
			PropsUtil.getArray(PropsUtil.DL_FILE_EXTENSIONS);

		for (int i = 0; i < fileExtensions.length; i++) {
			if (StringPool.STAR.equals(fileExtensions[i]) ||
				StringUtil.endsWith(fileName, fileExtensions[i])) {

				validFileExtension = true;

				break;
			}
		}

		if (!validFileExtension) {
			throw new FileNameException(fileName);
		}

		long fileMaxSize = GetterUtil.getLong(
			PropsUtil.get(PropsUtil.DL_FILE_MAX_SIZE));

		if ((fileMaxSize > 0) &&
			((byteArray == null) || (byteArray.length > fileMaxSize))) {

			throw new FileSizeException(fileName);
		}

		File file = new File(
			PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId + fileName);

		if (file.exists()) {
			throw new DuplicateFileException(fileName);
		}
		else {
			try {
				if (file.getParent() != null) {
					FileUtil.mkdirs(file.getParent());
				}

				OutputStream out = new FileOutputStream(file);
				out.write(byteArray);
				out.close();
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Update lucene

			try {
				Indexer.addFile(
					companyId, portletId, groupId, repositoryId, file);
			}
			catch (IOException ioe) {
				ioe.printStackTrace();
			}
		}

		_getDirectoryViewsPool().remove(coRepoId);
	}

	public void deleteAll(
		String companyId, String portletId, String repositoryId) {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		FileUtil.deltree(PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId);

		FileUtil.deltree(
			PropsUtil.get(PropsUtil.DL_VERSION_ROOT_DIR) + coRepoId);

		// Update lucene

		try {
			Indexer.deleteFiles(companyId, portletId, repositoryId);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		_getDirectoryViewsPool().remove(coRepoId);
	}

	public void deleteDirectory(
			String companyId, String portletId, String repositoryId,
			String dirName)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		File directory = new File(
			PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId + dirName);

		if (!directory.exists()) {
			throw new NoSuchDirectoryException(dirName);
		}

		_deleteDirectory(companyId, portletId, repositoryId, directory);

		File versionedDir = new File(
			PropsUtil.get(PropsUtil.DL_VERSION_ROOT_DIR) + coRepoId + dirName);

		_deleteDirectory(companyId, portletId, repositoryId, versionedDir);

		_getDirectoryViewsPool().remove(coRepoId);
	}

	public void deleteFile(
			String companyId, String portletId, String repositoryId,
			String fileName)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		File file = new File(
			PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId + fileName);

		if (!file.exists()) {
			throw new NoSuchFileException(fileName);
		}

		_deleteFile(companyId, portletId, repositoryId, file);

		String dirName = FileUtil.getPath(fileName);

		File directory = new File(
			PropsUtil.get(PropsUtil.DL_VERSION_ROOT_DIR) + coRepoId + dirName);

		String prefix = FileUtil.getShortFileName(fileName) + VERSION;

		if (directory.exists() && directory.isDirectory()) {
			File[] array = directory.listFiles();

			for (int i = 0; i < array.length; i++) {
				File temp = array[i];

				if (!temp.isDirectory() && temp.getName().startsWith(prefix)) {
					_deleteFile(companyId, portletId, repositoryId, temp);
				}
			}
		}

		_getDirectoryViewsPool().remove(coRepoId);
	}

	public void deleteFile(
			String companyId, String portletId, String repositoryId,
			String fileName, double version)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		File file = new File(
			PropsUtil.get(PropsUtil.DL_VERSION_ROOT_DIR) + coRepoId + fileName +
				VERSION + version);

		if (!file.exists()) {
			throw new NoSuchFileException(fileName + VERSION + version);
		}

		_deleteFile(companyId, portletId, repositoryId, file);

		_getDirectoryViewsPool().remove(coRepoId);
	}

	public String[] getDirectoryNames(
			String companyId, String repositoryId, String dirName)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		File directory = new File(
			PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId + dirName);

		if (!directory.exists()) {
			throw new NoSuchDirectoryException(dirName);
		}

		List directoryNames = new ArrayList();

		File[] array = directory.listFiles();

		for (int i = 0; i < array.length; i++) {
			if (array[i].isDirectory()) {
				directoryNames.add(dirName + "/" + array[i].getName());
			}
		}

		return (String[])directoryNames.toArray(new String[0]);
	}

	public DirectoryView getDirectoryView(
		String companyId, String repositoryId) {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		Map directoryViewsPool = _getDirectoryViewsPool();

		DirectoryView directoryView =
			(DirectoryView)directoryViewsPool.get(coRepoId);

		if (directoryView == null) {
			DirectoryLister dirNameLister = new DirectoryLister();

			directoryView = dirNameLister.getDirectoryView(
				PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId);

			if (_CACHE_DIRECTORY_VIEWS) {
				directoryViewsPool.put(coRepoId, directoryView);
			}
		}

		return directoryView;
	}

	public byte[] getFile(
			String companyId, String repositoryId, String fileName)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		File file = new File(
			PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId + fileName);

		byte[] bytes = null;

		try {
			bytes = FileUtil.getBytes(file);

			if (bytes == null || bytes.length == 0) {
				throw new IOException();
			}
		}
		catch (IOException ioe) {
			throw new NoSuchFileException(fileName);
		}

		return bytes;
	}

	public byte[] getFile(
			String companyId, String repositoryId, String fileName,
			double version)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		File file = new File(
			PropsUtil.get(PropsUtil.DL_VERSION_ROOT_DIR) + coRepoId + fileName +
				VERSION + version);

		byte[] bytes = null;

		try {
			bytes = FileUtil.getBytes(file);

			if (bytes == null || bytes.length == 0) {
				throw new IOException();
			}
		}
		catch (IOException ioe) {
			throw new NoSuchFileException(fileName + VERSION + version);
		}

		return bytes;
	}

	public String[] getFileNames(
			String companyId, String repositoryId, String dirName)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		File directory = new File(
			PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId + dirName);

		if (!directory.exists()) {
			throw new NoSuchDirectoryException(dirName);
		}

		List fileNames = new ArrayList();

		File[] array = directory.listFiles();

		for (int i = 0; i < array.length; i++) {
			if (array[i].isFile()) {
				fileNames.add(dirName + "/" + array[i].getName());
			}
		}

		return (String[])fileNames.toArray(new String[0]);
	}

	public int getFileSize(
			String companyId, String repositoryId, String fileName)
		throws PortalException {

		return getFile(companyId, repositoryId, fileName).length;
	}

	public boolean exists(
		String companyId, String repositoryId, String fileName) {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		File file = new File(
			PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId + fileName);

		return file.exists();
	}

	public void reIndex(String[] ids) throws SystemException {
		try {
			Indexer indexer = new Indexer();

			indexer.reIndex(ids);
		}
		catch (IndexerException ie) {
			throw new SystemException(ie);
		}
	}

	public Hits search(
			String companyId, String portletId, String groupId,
			String[] repositoryIds, String keywords)
		throws SystemException {

		try {
			Hits hits = new Hits();

			if (Validator.isNull(keywords)) {
				return hits;
			}

			BooleanQuery booleanQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.PORTLET_ID, portletId);
			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.GROUP_ID, groupId);

			LuceneUtil.addTerm(booleanQuery, LuceneFields.CONTENT, keywords);

			if ((repositoryIds != null) && (repositoryIds.length > 0)) {
				BooleanQuery repositoryIdsQuery = new BooleanQuery();

				for (int i = 0; i < repositoryIds.length; i++) {
					repositoryIdsQuery.add(new TermQuery(new Term(
						"repositoryId", repositoryIds[i])), false, false);
				}

				booleanQuery.add(repositoryIdsQuery, true, false);
			}

			Searcher searcher = LuceneUtil.getSearcher(companyId);

			Query query = QueryParser.parse(
				booleanQuery.toString(), LuceneFields.CONTENT,
				new WhitespaceAnalyzer());

			hits.recordHits(searcher.search(query));

			return hits;
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (ParseException pe) {
			throw new SystemException(pe);
		}
	}

	public void updateFile(
			String companyId, String portletId, String groupId,
			String repositoryId, String fileName, double version,
			String sourceFileName, byte[] byteArray)
		throws PortalException {

		String coRepoId = companyId + StringPool.PERIOD + repositoryId;

		File file = new File(
			PropsUtil.get(PropsUtil.DL_ROOT_DIR) + coRepoId + fileName);

		if (!file.exists()) {
			throw new NoSuchFileException(fileName);
		}

		int pos = fileName.lastIndexOf(StringPool.PERIOD);

		if (pos != -1) {
			String fileNameExtension =
				fileName.substring(pos, fileName.length());

			pos = sourceFileName.lastIndexOf(StringPool.PERIOD);

			if (pos == -1) {
				throw new SourceFileNameException(sourceFileName);
			}
			else {
				String sourceFileNameExtension =
					sourceFileName.substring(pos, sourceFileName.length());

				if (!fileNameExtension.equalsIgnoreCase(
						sourceFileNameExtension)) {

					throw new SourceFileNameException(sourceFileName);
				}
			}
		}

		long fileMaxSize = GetterUtil.getLong(
			PropsUtil.get(PropsUtil.DL_FILE_MAX_SIZE));

		if (byteArray == null || byteArray.length > fileMaxSize) {
			throw new FileSizeException(fileName);
		}

		File versionedFile = new File(
			PropsUtil.get(PropsUtil.DL_VERSION_ROOT_DIR) + coRepoId + fileName +
				VERSION + version);

		FileUtil.copyFile(file, versionedFile);

		try {
			if (file.getParent() != null) {
				FileUtil.mkdirs(file.getParent());
			}

			OutputStream out = new FileOutputStream(file);
			out.write(byteArray);
			out.close();
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Update lucene

		try {
			Indexer.deleteFile(companyId, portletId, repositoryId, file);

			Indexer.addFile(companyId, portletId, groupId, repositoryId, file);

			Indexer.addFile(
				companyId, portletId, groupId, repositoryId, versionedFile);
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	private void _deleteDirectory(
		String companyId, String portletId, String repositoryId,
		File directory) {

		if (directory.exists() && directory.isDirectory()) {
			File[] array = directory.listFiles();

			for (int i = 0; i < array.length; i++) {
				File temp = array[i];

				if (temp.isDirectory()) {
					_deleteDirectory(
						companyId, portletId, repositoryId, array[i]);
				}
				else {
					_deleteFile(companyId, portletId, repositoryId, temp);
				}
			}

			directory.delete();
		}
	}

	private void _deleteFile(
			String companyId, String portletId, String repositoryId,
			File file) {

		// Update lucene

		try {
			Indexer.deleteFile(companyId, portletId, repositoryId, file);
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		// Delete file

		file.delete();
	}

	private Map _getDirectoryViewsPool() {
		String scpId = DLServiceImpl.class.getName();

		Map directoryViewsPool = (Map)SimpleCachePool.get(scpId);

		if (directoryViewsPool == null) {
			directoryViewsPool = CollectionFactory.getSyncHashMap();

			SimpleCachePool.put(scpId, directoryViewsPool);
		}

		return directoryViewsPool;
	}

	public static final boolean _CACHE_DIRECTORY_VIEWS = GetterUtil.get(
		PropsUtil.get(PropsUtil.DL_VERSION_CACHE_DIRECTORY_VIEWS), true);

}