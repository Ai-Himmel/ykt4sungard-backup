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

import com.liferay.documentlibrary.FileNameException;
import com.liferay.documentlibrary.FileSizeException;
import com.liferay.documentlibrary.SourceFileNameException;
import com.liferay.documentlibrary.service.DLLocalService;
import com.liferay.documentlibrary.util.Hook;
import com.liferay.documentlibrary.util.HookFactory;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.FileUtil;
import com.liferay.util.lucene.HitsImpl;

import java.io.File;
import java.io.InputStream;

import org.apache.lucene.index.Term;
import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.TermQuery;

/**
 * <a href="DLLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLLocalServiceImpl implements DLLocalService {

	public void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries,
			InputStream is)
		throws PortalException, SystemException {

		validate(fileName, is);

		Hook hook = HookFactory.getInstance();

		hook.addFile(
			companyId, portletId, groupId, repositoryId, fileName, properties,
			tagsEntries, is);
	}

	public void checkRoot(long companyId) throws SystemException {
		Hook hook = HookFactory.getInstance();

		hook.checkRoot(companyId);
	}

	public InputStream getFileAsStream(
			long companyId, long repositoryId, String fileName)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		return hook.getFileAsStream(companyId, repositoryId, fileName);
	}

	public InputStream getFileAsStream(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		return hook.getFileAsStream(
			companyId, repositoryId, fileName, versionNumber);
	}

	public boolean hasFile(
			long companyId, long repositoryId, String fileName,
			double versionNumber)
		throws PortalException, SystemException {

		Hook hook = HookFactory.getInstance();

		return hook.hasFile(companyId, repositoryId, fileName, versionNumber);
	}

	public void move(String srcDir, String destDir) throws SystemException {
		Hook hook = HookFactory.getInstance();

		hook.move(srcDir, destDir);
	}

	public Hits search(
			long companyId, String portletId, long groupId,
			long[] repositoryIds, String keywords)
		throws SystemException {

		Searcher searcher = null;

		try {
			HitsImpl hits = new HitsImpl();

			BooleanQuery contextQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				contextQuery, LuceneFields.PORTLET_ID, portletId);

			if (groupId > 0) {
				LuceneUtil.addRequiredTerm(
					contextQuery, LuceneFields.GROUP_ID, groupId);
			}

			if ((repositoryIds != null) && (repositoryIds.length > 0)) {
				BooleanQuery repositoryIdsQuery = new BooleanQuery();

				for (int i = 0; i < repositoryIds.length; i++) {
					Term term = new Term(
						"repositoryId", String.valueOf(repositoryIds[i]));
					TermQuery termQuery = new TermQuery(term);

					repositoryIdsQuery.add(
						termQuery, BooleanClause.Occur.SHOULD);
				}

				contextQuery.add(repositoryIdsQuery, BooleanClause.Occur.MUST);
			}

			BooleanQuery searchQuery = new BooleanQuery();

			if (Validator.isNotNull(keywords)) {
				LuceneUtil.addTerm(searchQuery, LuceneFields.CONTENT, keywords);
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.PROPERTIES, keywords);
				LuceneUtil.addTerm(
					searchQuery, LuceneFields.TAG_ENTRY, keywords);
			}

			BooleanQuery fullQuery = new BooleanQuery();

			fullQuery.add(contextQuery, BooleanClause.Occur.MUST);

			if (searchQuery.clauses().size() > 0) {
				fullQuery.add(searchQuery, BooleanClause.Occur.MUST);
			}

			searcher = LuceneUtil.getSearcher(companyId);

			hits.recordHits(searcher.search(fullQuery), searcher);

			return hits;
		}
		catch (Exception e) {
			return LuceneUtil.closeSearcher(searcher, keywords, e);
		}
	}

	public void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, double versionNumber, String sourceFileName,
			String properties, String[] tagsEntries, InputStream is)
		throws PortalException, SystemException {

		validate(fileName, sourceFileName, is);

		Hook hook = HookFactory.getInstance();

		hook.updateFile(
			companyId, portletId, groupId, repositoryId, fileName,
			versionNumber, sourceFileName, properties, tagsEntries, is);
	}

	public void validate(String fileName, File file) throws PortalException {
		validate(fileName);

		if ((PropsValues.DL_FILE_MAX_SIZE > 0) &&
			((file == null) ||
			 (file.length() > PropsValues.DL_FILE_MAX_SIZE))) {

			throw new FileSizeException(fileName);
		}
	}

	public void validate(String fileName, byte[] byteArray)
		throws PortalException {

		validate(fileName);

		if ((PropsValues.DL_FILE_MAX_SIZE > 0) &&
			((byteArray == null) ||
			 (byteArray.length > PropsValues.DL_FILE_MAX_SIZE))) {

			throw new FileSizeException(fileName);
		}
	}

	public void validate(String fileName, InputStream is)
		throws PortalException {

		validate(fileName);

		if (is == null) {
			throw new FileSizeException(fileName);
		}
	}

	public void validate(String fileName) throws PortalException {
		if ((fileName.indexOf("\\\\") != -1) ||
			(fileName.indexOf("//") != -1) ||
			(fileName.indexOf(":") != -1) ||
			(fileName.indexOf("*") != -1) ||
			(fileName.indexOf("?") != -1) ||
			(fileName.indexOf("\"") != -1) ||
			(fileName.indexOf("<") != -1) ||
			(fileName.indexOf(">") != -1) ||
			(fileName.indexOf("|") != -1) ||
			(fileName.indexOf("&") != -1) ||
			(fileName.indexOf("[") != -1) ||
			(fileName.indexOf("]") != -1) ||
			(fileName.indexOf("'") != -1)) {

			throw new FileNameException(fileName);
		}

		boolean validFileExtension = false;

		String[] fileExtensions = PropsValues.DL_FILE_EXTENSIONS;

		if (!PropsValues.WEBDAV_LITMUS) {
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
		}
	}

	public void validate(String fileName, String sourceFileName, InputStream is)
		throws PortalException {

		String fileNameExtension = FileUtil.getExtension(fileName);
		String sourceFileNameExtension = FileUtil.getExtension(sourceFileName);

		if (!PropsValues.WEBDAV_LITMUS) {
			if (Validator.isNull(fileNameExtension) ||
				!fileNameExtension.equalsIgnoreCase(sourceFileNameExtension)) {

				throw new SourceFileNameException(sourceFileName);
			}
		}

		if (is == null) {
			throw new FileSizeException(fileName);
		}
	}

}