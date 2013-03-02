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

package com.liferay.portlet.messageboards.util;

import com.liferay.portal.kernel.search.DocumentSummary;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.messageboards.service.MBCategoryLocalServiceUtil;
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

	public static final String PORTLET_ID = PortletKeys.MESSAGE_BOARDS;

	public static void addMessage(
			long companyId, long groupId, String userName, long categoryId,
			long threadId, long messageId, String title, String content,
			String[] tagsEntries)
		throws IOException {

		Document doc = getAddMessageDocument(
			companyId, groupId, userName, categoryId, threadId, messageId,
			title, content, tagsEntries);

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

	public static void deleteMessage(long companyId, long messageId)
		throws IOException {

		LuceneUtil.deleteDocuments(
			companyId,
			new Term(
				LuceneFields.UID, LuceneFields.getUID(PORTLET_ID, messageId)));
	}

	public static void deleteMessages(long companyId, long threadId)
		throws IOException, ParseException {

		BooleanQuery booleanQuery = new BooleanQuery();

		LuceneUtil.addRequiredTerm(
			booleanQuery, LuceneFields.PORTLET_ID, PORTLET_ID);

		LuceneUtil.addRequiredTerm(booleanQuery, "threadId", threadId);

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

	public static Document getAddMessageDocument(
		long companyId, long groupId, String userName, long categoryId,
		long threadId, long messageId, String title, String content,
		String[] tagsEntries) {

		content = Html.stripHtml(content);

		Document doc = new Document();

		LuceneUtil.addKeyword(
			doc, LuceneFields.UID, LuceneFields.getUID(PORTLET_ID, messageId));

		LuceneUtil.addKeyword(doc, LuceneFields.COMPANY_ID, companyId);
		LuceneUtil.addKeyword(doc, LuceneFields.PORTLET_ID, PORTLET_ID);
		LuceneUtil.addKeyword(doc, LuceneFields.GROUP_ID, groupId);

		LuceneUtil.addText(doc, LuceneFields.USER_NAME, userName);
		LuceneUtil.addText(doc, LuceneFields.TITLE, title);
		LuceneUtil.addText(doc, LuceneFields.CONTENT, content);

		LuceneUtil.addModifiedDate(doc);

		LuceneUtil.addKeyword(doc, "categoryId", categoryId);
		LuceneUtil.addKeyword(doc, "threadId", threadId);
		LuceneUtil.addKeyword(doc, "messageId", messageId);

		LuceneUtil.addKeyword(doc, LuceneFields.TAG_ENTRY, tagsEntries);

		return doc;
	}

	public static void updateMessage(
			long companyId, long groupId, String userName, long categoryId,
			long threadId, long messageId, String title, String content,
			String[] tagsEntries)
		throws IOException {

		try {
			deleteMessage(companyId, messageId);
		}
		catch (IOException ioe) {
		}

		addMessage(
			companyId, groupId, userName, categoryId, threadId, messageId,
			title, content, tagsEntries);
	}

	public DocumentSummary getDocumentSummary(
		com.liferay.portal.kernel.search.Document doc, PortletURL portletURL) {

		// Title

		String title = doc.get(LuceneFields.TITLE);

		// Content

		String content = doc.get(LuceneFields.CONTENT);

		content = StringUtil.shorten(content, 200);

		// URL

		long messageId = GetterUtil.getLong(doc.get("messageId"));

		portletURL.setParameter(
			"struts_action", "/message_boards/view_message");
		portletURL.setParameter("messageId", String.valueOf(messageId));

		return new DocumentSummary(title, content, portletURL);
	}

	public void reIndex(String[] ids) throws SearchException {
		try {
			MBCategoryLocalServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new SearchException(e);
		}
	}

}