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

package com.liferay.portlet.wiki.util;

import com.liferay.portal.kernel.search.DocumentSummary;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.wiki.service.WikiNodeLocalServiceUtil;
import com.liferay.util.Html;

import java.io.IOException;

import javax.portlet.PortletURL;

import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Hits;
import org.apache.lucene.search.Searcher;

/**
 * <a href="Indexer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Harry Mark
 *
 */
public class Indexer implements com.liferay.portal.kernel.search.Indexer {

	public static final String PORTLET_ID = PortletKeys.WIKI;

	public static void addPage(
			long companyId, long groupId, long nodeId, String title,
			String content, String[] tagsEntries)
		throws IOException {

		try {
			deletePage(companyId, nodeId, title);
		}
		catch (IOException ioe) {
		}

		Document doc = getAddPageDocument(
			companyId, groupId, nodeId, title, content, tagsEntries);

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

	public static void deletePage(long companyId, long nodeId, String title)
		throws IOException {

		LuceneUtil.deleteDocuments(
			companyId,
			new Term(
				LuceneFields.UID,
				LuceneFields.getUID(PORTLET_ID, nodeId, title)));
	}

	public static void deletePages(long companyId, long nodeId)
		throws IOException, ParseException {

		BooleanQuery booleanQuery = new BooleanQuery();

		LuceneUtil.addRequiredTerm(
			booleanQuery, LuceneFields.PORTLET_ID, PORTLET_ID);

		LuceneUtil.addRequiredTerm(booleanQuery, "nodeId", nodeId);

		Searcher searcher = LuceneUtil.getSearcher(companyId);

		try {
			Hits hits = searcher.search(booleanQuery);

			if (hits.length() > 0) {
				IndexReader reader = null;

				try {
					LuceneUtil.acquireLock(companyId);

					reader = LuceneUtil.getReader(companyId);

					for (int i = 0; i < hits.length(); i++) {
						Document doc = hits.doc(i);

						Field field = doc.getField(LuceneFields.UID);

						reader.deleteDocuments(
							new Term(LuceneFields.UID, field.stringValue()));
					}
				}
				finally {
					if (reader != null) {
						reader.close();
					}

					LuceneUtil.releaseLock(companyId);
				}
			}
		}
		finally {
			LuceneUtil.closeSearcher(searcher);
		}
	}

	public static Document getAddPageDocument(
		long companyId, long groupId, long nodeId, String title,
		String content, String[] tagsEntries) {

		content = Html.stripHtml(content);

		Document doc = new Document();

		LuceneUtil.addKeyword(
			doc, LuceneFields.UID,
			LuceneFields.getUID(PORTLET_ID, nodeId, title));

		LuceneUtil.addKeyword(doc, LuceneFields.COMPANY_ID, companyId);
		LuceneUtil.addKeyword(doc, LuceneFields.PORTLET_ID, PORTLET_ID);
		LuceneUtil.addKeyword(doc, LuceneFields.GROUP_ID, groupId);

		LuceneUtil.addText(doc, LuceneFields.TITLE, title);
		LuceneUtil.addText(doc, LuceneFields.CONTENT, content);

		LuceneUtil.addModifiedDate(doc);

		LuceneUtil.addKeyword(doc, "nodeId", nodeId);

		LuceneUtil.addKeyword(doc, LuceneFields.TAG_ENTRY, tagsEntries);

		return doc;
	}

	public static void updatePage(
			long companyId, long groupId, long nodeId, String title,
			String content, String[] tagsEntries)
		throws IOException {

		try {
			deletePage(companyId, nodeId, title);
		}
		catch (IOException ioe) {
		}

		addPage(companyId, groupId, nodeId, title, content, tagsEntries);
	}

	public DocumentSummary getDocumentSummary(
		com.liferay.portal.kernel.search.Document doc, PortletURL portletURL) {

		// Title

		String title = doc.get(LuceneFields.TITLE);

		// Content

		String content = doc.get(LuceneFields.CONTENT);

		content = StringUtil.shorten(content, 200);

		// URL

		long nodeId = GetterUtil.getLong(doc.get("nodeId"));

		portletURL.setParameter("struts_action", "/wiki/view");
		portletURL.setParameter("nodeId", String.valueOf(nodeId));
		portletURL.setParameter("title", title);

		return new DocumentSummary(title, content, portletURL);
	}

	public void reIndex(String[] ids) throws SearchException {
		try {
			WikiNodeLocalServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new SearchException(e);
		}
	}

}