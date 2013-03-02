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

package com.liferay.portlet.messageboards.util;

import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portlet.messageboards.service.spring.MBTopicServiceUtil;
import com.liferay.util.Html;
import com.liferay.util.StringUtil;
import com.liferay.util.lucene.DocumentSummary;
import com.liferay.util.lucene.IndexerException;

import java.io.IOException;

import javax.portlet.PortletURL;

import org.apache.lucene.analysis.WhitespaceAnalyzer;
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
 * @version $Revision: 1.17 $
 *
 */
public class Indexer implements com.liferay.util.lucene.Indexer {

	public static void addMessage(
			String companyId, String portletId, String groupId,
			String topicId, String messageId, String title, String content)
		throws IOException {

		content = Html.stripHtml(content);

		IndexWriter writer = LuceneUtil.getWriter(companyId);

		Document doc = new Document();

		doc.add(
			LuceneFields.getKeyword(
				LuceneFields.UID,
				LuceneFields.getUID(portletId, topicId, messageId)));

		doc.add(LuceneFields.getKeyword(LuceneFields.COMPANY_ID, companyId));
		doc.add(LuceneFields.getKeyword(LuceneFields.PORTLET_ID, portletId));
		doc.add(LuceneFields.getKeyword(LuceneFields.GROUP_ID, groupId));

		doc.add(Field.Text(LuceneFields.TITLE, title));
		doc.add(Field.Text(LuceneFields.CONTENT, content));

		doc.add(LuceneFields.getDate(LuceneFields.MODIFIED));

		doc.add(LuceneFields.getKeyword("topicId", topicId));
		doc.add(LuceneFields.getKeyword("messageId", messageId));

		writer.addDocument(doc);

		writer.close();
	}

	public static void deleteMessage(
			String companyId, String portletId, String topicId,
			String messageId)
		throws IOException {

		IndexReader reader = LuceneUtil.getReader(companyId);

		reader.delete(
			new Term(
				LuceneFields.UID,
				LuceneFields.getUID(portletId, topicId, messageId)));

		reader.close();
	}

	public static void deleteMessages(
			String companyId, String portletId, String topicId)
		throws IOException, ParseException {

		BooleanQuery booleanQuery = new BooleanQuery();

		LuceneUtil.addRequiredTerm(
			booleanQuery, LuceneFields.PORTLET_ID, portletId);

		LuceneUtil.addRequiredTerm(booleanQuery, "topicId", topicId);

		Searcher searcher = LuceneUtil.getSearcher(companyId);

		Query query = QueryParser.parse(
			booleanQuery.toString(), LuceneFields.CONTENT,
			new WhitespaceAnalyzer());

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

		// Title

		String title = doc.get(LuceneFields.TITLE);

		// Content

		String content = doc.get(LuceneFields.CONTENT);
		content = StringUtil.shorten(content, 200);

		// URL

		String topicId = doc.get("topicId");
		String messageId = doc.get("messageId");

		portletURL.setParameter(
			"struts_action", "/message_boards/view_message");

		portletURL.setParameter("topic_id", topicId);
		portletURL.setParameter("msg_id", messageId);

		return new DocumentSummary(title, content, portletURL);
	}

	public void reIndex(String[] ids) throws IndexerException {
		try {
			MBTopicServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new IndexerException(e);
		}
	}

}