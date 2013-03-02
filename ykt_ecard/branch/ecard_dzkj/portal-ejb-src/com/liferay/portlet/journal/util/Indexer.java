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

package com.liferay.portlet.journal.util;

import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;
import com.liferay.util.Html;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.lucene.DocumentSummary;
import com.liferay.util.lucene.IndexerException;

import java.io.IOException;

import java.util.Date;

import javax.portlet.PortletURL;

import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;

/**
 * <a href="Indexer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class Indexer implements com.liferay.util.lucene.Indexer {

	public static void addArticle(
			String companyId, String portletId, String groupId,
			String articleId, double version, String title, String content,
			String type, Date displayDate)
		throws IOException {

		if ((content != null) && (content.indexOf("<root>") != -1) &&
			(content.indexOf("<dynamic-content>") != -1)) {

			content = StringUtil.replace(
				content, "<![CDATA[", StringPool.BLANK);
			content = StringUtil.replace(content, "]]>", StringPool.BLANK);
		}

		content = Html.stripHtml(content);

		IndexWriter writer = LuceneUtil.getWriter(companyId);

		Document doc = new Document();

		doc.add(
			LuceneFields.getKeyword(
				LuceneFields.UID, LuceneFields.getUID(portletId, articleId)));

		doc.add(LuceneFields.getKeyword(LuceneFields.COMPANY_ID, companyId));
		doc.add(LuceneFields.getKeyword(LuceneFields.PORTLET_ID, portletId));
		doc.add(LuceneFields.getKeyword(LuceneFields.GROUP_ID, groupId));

		doc.add(Field.Text(LuceneFields.TITLE, title));
		doc.add(Field.Text(LuceneFields.CONTENT, content));

		doc.add(LuceneFields.getDate(LuceneFields.MODIFIED));

		doc.add(LuceneFields.getKeyword("articleId", articleId));
		doc.add(LuceneFields.getKeyword("version", Double.toString(version)));
		doc.add(LuceneFields.getKeyword("type", type));
		doc.add(LuceneFields.getDate("displayDate", displayDate));

		writer.addDocument(doc);

		writer.close();
	}

	public static void deleteArticle(
			String companyId, String portletId, String articleId)
		throws IOException {

		IndexReader reader = LuceneUtil.getReader(companyId);

		reader.delete(
			new Term(
				LuceneFields.UID, LuceneFields.getUID(portletId, articleId)));

		reader.close();
	}

	public static void updateArticle(
			String companyId, String portletId, String groupId,
			String articleId, double version, String title, String content,
			String type, Date displayDate)
		throws IOException {

		try {
			deleteArticle(companyId, portletId, articleId);
		}
		catch (IOException ioe) {
		}

		addArticle(
			companyId, portletId, groupId, articleId, version, title, content,
			type, displayDate);
	}

	public DocumentSummary getDocumentSummary(
		Document doc, PortletURL portletURL) {

		// Title

		String title = doc.get(LuceneFields.TITLE);

		// Content

		String content = doc.get(LuceneFields.CONTENT);
		content = StringUtil.shorten(content, 200);

		// URL

		String articleId = doc.get("articleId");
		String version = doc.get("version");

		portletURL.setParameter("struts_action", "/journal/view_article");

		portletURL.setParameter("article_id", articleId);
		portletURL.setParameter("article_version", version);

		return new DocumentSummary(title, content, portletURL);
	}

	public void reIndex(String[] ids) throws IndexerException {
		try {
			JournalArticleServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new IndexerException(e);
		}
	}

}