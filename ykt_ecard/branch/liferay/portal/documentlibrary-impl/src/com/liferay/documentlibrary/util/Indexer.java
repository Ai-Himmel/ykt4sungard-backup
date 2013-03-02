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

import com.liferay.documentlibrary.service.impl.DLServiceImpl;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.search.DocumentSummary;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portlet.documentlibrary.NoSuchFileEntryException;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil;
import com.liferay.portlet.tags.service.TagsEntryLocalServiceUtil;

import java.io.IOException;
import java.io.InputStream;

import java.util.Iterator;
import java.util.Map;
import java.util.Properties;

import javax.portlet.PortletURL;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;

/**
 * <a href="Indexer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Harry Mark
 *
 */
public class Indexer implements com.liferay.portal.kernel.search.Indexer {

	public static void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName)
		throws IOException {

		Document doc = getAddFileDocument(
			companyId, portletId, groupId, repositoryId, fileName);

		IndexWriter writer = null;

		try {
			writer = LuceneUtil.getWriter(companyId);

			writer.addDocument(doc);
		}
		finally {
			if (writer != null) {
				LuceneUtil.write(companyId);
			}
		}
	}

	public static void addFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries)
		throws IOException {

		Document doc = getAddFileDocument(
			companyId, portletId, groupId, repositoryId, fileName, properties,
			tagsEntries);

		IndexWriter writer = null;

		try {
			writer = LuceneUtil.getWriter(companyId);

			writer.addDocument(doc);
		}
		finally {
			if (writer != null) {
				LuceneUtil.write(companyId);
			}
		}
	}

	public static void deleteFile(
			long companyId, String portletId, long repositoryId,
			String fileName)
		throws IOException {

		LuceneUtil.deleteDocuments(
			companyId,
			new Term(
				LuceneFields.UID,
				LuceneFields.getUID(portletId, repositoryId, fileName)));
	}

	public static Document getAddFileDocument(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName)
		throws IOException {

		try {
			DLFileEntry fileEntry = null;

			try {
				fileEntry = DLFileEntryLocalServiceUtil.getFileEntry(
					repositoryId, fileName);
			}
			catch (NoSuchFileEntryException nsfe) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"File " + fileName + " in repository " +
							repositoryId + " exists in the JCR but does " +
								"not exist in the database");
				}

				return null;
			}

			StringMaker sm = new StringMaker();

			sm.append(fileEntry.getTitle());
			sm.append(StringPool.SPACE);
			sm.append(fileEntry.getDescription());
			sm.append(StringPool.SPACE);

			Properties extraSettingsProps =
				fileEntry.getExtraSettingsProperties();

			Iterator itr =
				(Iterator)extraSettingsProps.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				String value = GetterUtil.getString(
					(String)entry.getValue());

				sm.append(value);
			}

			String properties = sm.toString();

			String[] tagsEntries = TagsEntryLocalServiceUtil.getEntryNames(
				DLFileEntry.class.getName(), fileEntry.getFileEntryId());

			return getAddFileDocument(
				companyId, portletId, groupId, repositoryId, fileName,
				properties, tagsEntries);
		}
		catch (PortalException pe) {
			throw new IOException(pe.getMessage());
		}
		catch (SystemException se) {
			throw new IOException(se.getMessage());
		}
	}

	public static Document getAddFileDocument(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries)
		throws IOException {

		if (_log.isDebugEnabled()) {
			_log.debug(
				"Indexing document " + companyId + " " + portletId + " " +
					groupId + " " + repositoryId + " " + fileName);
		}

		String fileExt = StringPool.BLANK;

		int fileExtVersionPos = fileName.indexOf(DLServiceImpl.VERSION);

		if (fileExtVersionPos != -1) {
			int fileExtPos = fileName.lastIndexOf(
				StringPool.PERIOD, fileExtVersionPos);

			if (fileExtPos != -1) {
				fileExt = fileName.substring(fileExtPos, fileExtVersionPos);
			}
		}
		else {
			int fileExtPos = fileName.lastIndexOf(StringPool.PERIOD);

			if (fileExtPos != -1) {
				fileExt = fileName.substring(fileExtPos, fileName.length());
			}
		}

		InputStream is = null;

		try {
			Hook hook = HookFactory.getInstance();

			is = hook.getFileAsStream(companyId, repositoryId, fileName);
		}
		catch (Exception e) {
		}

		if (is == null) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Document " + companyId + " " + portletId + " " + groupId +
						" " + repositoryId + " " + fileName +
							" does not have any content");
			}

			return null;
		}

		Document doc = new Document();

		LuceneUtil.addKeyword(
			doc, LuceneFields.UID,
			LuceneFields.getUID(portletId, repositoryId, fileName));

		LuceneUtil.addKeyword(doc, LuceneFields.COMPANY_ID, companyId);
		LuceneUtil.addKeyword(doc, LuceneFields.PORTLET_ID, portletId);
		LuceneUtil.addKeyword(doc, LuceneFields.GROUP_ID, groupId);

		doc.add(LuceneFields.getFile(LuceneFields.CONTENT, is, fileExt));

		if (Validator.isNotNull(properties)) {
			LuceneUtil.addText(doc, LuceneFields.PROPERTIES, properties);
		}

		LuceneUtil.addModifiedDate(doc);

		LuceneUtil.addKeyword(doc, "repositoryId", repositoryId);
		LuceneUtil.addKeyword(doc, "path", fileName);

		LuceneUtil.addKeyword(doc, LuceneFields.TAG_ENTRY, tagsEntries);

		if (_log.isDebugEnabled()) {
			_log.debug(
				"Document " + companyId + " " + portletId + " " + groupId +
					" " + repositoryId + " " + fileName +
						" indexed successfully");
		}

		return doc;
	}

	public static void updateFile(
			long companyId, String portletId, long groupId, long repositoryId,
			String fileName, String properties, String[] tagsEntries)
		throws IOException {

		try {
			deleteFile(companyId, portletId, repositoryId, fileName);
		}
		catch (IOException ioe) {
		}

		addFile(
			companyId, portletId, groupId, repositoryId, fileName, properties,
			tagsEntries);
	}

	public DocumentSummary getDocumentSummary(
		com.liferay.portal.kernel.search.Document doc, PortletURL portletURL) {

		return null;
	}

	public void reIndex(String[] ids) throws SearchException {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		Hook hook = HookFactory.getInstance();

		hook.reIndex(ids);
	}

	private static Log _log = LogFactory.getLog(Indexer.class);

}