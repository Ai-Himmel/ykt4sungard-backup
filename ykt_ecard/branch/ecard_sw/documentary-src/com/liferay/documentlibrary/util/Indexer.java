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

package com.liferay.documentlibrary.util;

import com.liferay.documentlibrary.service.impl.DLServiceImpl;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.StringPool;
import com.liferay.util.lucene.DocumentSummary;
import com.liferay.util.lucene.IndexerException;

import java.io.File;
import java.io.IOException;

import javax.portlet.PortletURL;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Hits;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.Searcher;

/**
 * <a href="Indexer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.18 $
 *
 */
public class Indexer implements com.liferay.util.lucene.Indexer {

	public static void addFile(
			String companyId, String portletId, String groupId,
			String repositoryId, File file)
		throws IOException {

		String fileExt = file.getName();

		int fileExtPos = fileExt.indexOf(DLServiceImpl.VERSION);

		if (fileExtPos != -1) {
			fileExt = fileExt.substring(
				fileExt.lastIndexOf(StringPool.PERIOD, fileExtPos), fileExtPos);
		}
		else {
			fileExt = fileExt.substring(
				fileExt.lastIndexOf(StringPool.PERIOD), fileExt.length());
		}

		IndexWriter writer = LuceneUtil.getWriter(companyId);

		Document doc = new Document();

		doc.add(
			LuceneFields.getKeyword(
				LuceneFields.UID,
				LuceneFields.getUID(portletId, repositoryId, file.getPath())));

		doc.add(LuceneFields.getKeyword(LuceneFields.COMPANY_ID, companyId));
		doc.add(LuceneFields.getKeyword(LuceneFields.PORTLET_ID, portletId));
		doc.add(LuceneFields.getKeyword(LuceneFields.GROUP_ID, groupId));

		doc.add(LuceneFields.getFile(LuceneFields.CONTENT, file, fileExt));

		doc.add(LuceneFields.getDate(LuceneFields.MODIFIED));

		doc.add(LuceneFields.getKeyword("repositoryId", repositoryId));
		doc.add(LuceneFields.getKeyword("path", file.getPath()));

		writer.addDocument(doc);

		writer.close();
	}

	public static void deleteFile(
			String companyId, String portletId, String repositoryId, File file)
		throws IOException {

		IndexReader reader = LuceneUtil.getReader(companyId);

		reader.delete(
			new Term(
				LuceneFields.UID,
				LuceneFields.getUID(portletId, repositoryId, file.getPath())));

		reader.close();
	}

	public static void deleteFiles(
			String companyId, String portletId, String repositoryId)
		throws IOException, ParseException {

		BooleanQuery booleanQuery = new BooleanQuery();

		LuceneUtil.addRequiredTerm(
			booleanQuery, LuceneFields.PORTLET_ID, portletId);

		LuceneUtil.addRequiredTerm(booleanQuery, "repositoryId", repositoryId);

		Searcher searcher = LuceneUtil.getSearcher(companyId);

		Query query = QueryParser.parse(
			booleanQuery.toString(), LuceneFields.CONTENT,
			new StandardAnalyzer());

		Hits hits = searcher.search(query);

		if (hits.length() > 0) {
			IndexReader reader = LuceneUtil.getReader(companyId);

			for (int i = 0; i < hits.length(); i++) {
				Document doc = hits.doc(i);

				Field field = doc.getField(LuceneFields.UID);

				reader.delete(new Term(LuceneFields.UID, field.stringValue()));
			}

			reader.close();
		}
	}

	public DocumentSummary getDocumentSummary(
		Document doc, PortletURL portletURL) {

		return null;
	}

	public void reIndex(String[] ids) throws IndexerException {
		try {
			String companyId = ids[0];
			String portletId = ids[1];
			String groupId = ids[2];
			String repositoryId = ids[3];

			_addFiles(
				companyId, portletId, groupId, repositoryId,
				new File(
					PropsUtil.get(PropsUtil.DL_ROOT_DIR) +
					companyId + StringPool.PERIOD + repositoryId));

			_addFiles(
				companyId, portletId, groupId, repositoryId,
				new File(
					PropsUtil.get(PropsUtil.DL_VERSION_ROOT_DIR) +
					companyId + StringPool.PERIOD + repositoryId));
		}
		catch (Exception e) {
			throw new IndexerException(e);
		}
	}

	private void _addFiles(
			String companyId, String portletId, String groupId,
			String repositoryId, File folder)
		throws IOException {

		if (folder.exists() && folder.isDirectory()) {
			File[] array = folder.listFiles();

			for (int i = 0; i < array.length; i++) {
				File temp = array[i];

				if (temp.isDirectory()) {
					_addFiles(
						companyId, portletId, groupId, repositoryId, array[i]);
				}
				else {
					try {
						addFile(
							companyId, portletId, groupId, repositoryId, temp);
					}
					catch (Exception e) {

						// Continue indexing even if one file fails

						_log.error(e.getMessage());
					}
				}
			}
		}
	}

	private static final Log _log = LogFactory.getLog(Indexer.class);

}