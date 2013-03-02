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

package com.liferay.portlet.journal.util;

import com.liferay.portal.kernel.search.DocumentSummary;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil;
import com.liferay.util.Html;

import java.io.IOException;
import java.io.StringReader;

import java.util.Date;
import java.util.Iterator;

import javax.portlet.PortletURL;

import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;

import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="Indexer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Harry Mark
 *
 */
public class Indexer implements com.liferay.portal.kernel.search.Indexer {

	public static final String PORTLET_ID = PortletKeys.JOURNAL;

	public static void addArticle(
			long companyId, long groupId, String articleId, double version,
			String title, String description, String content, String type,
			Date displayDate, String[] tagsEntries)
		throws IOException {

		Document doc = getAddArticleDocument(
			companyId, groupId, articleId, version, title, description, content,
			type, displayDate, tagsEntries);

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

	public static void deleteArticle(long companyId, String articleId)
		throws IOException {

		LuceneUtil.deleteDocuments(
			companyId,
			new Term(
				LuceneFields.UID, LuceneFields.getUID(PORTLET_ID, articleId)));
	}

	public static Document getAddArticleDocument(
		long companyId, long groupId, String articleId, double version,
		String title, String description, String content, String type,
		Date displayDate, String[] tagsEntries) {

		if ((content != null) &&
			((content.indexOf("<dynamic-content>") != -1) ||
			 (content.indexOf("<static-content") != -1))) {

			content = _getIndexableContent(content);

			content = StringUtil.replace(
				content, "<![CDATA[", StringPool.BLANK);
			content = StringUtil.replace(content, "]]>", StringPool.BLANK);
		}

		content = StringUtil.replace(content, "&amp;", "&");
		content = StringUtil.replace(content, "&lt;", "<");
		content = StringUtil.replace(content, "&gt;", ">");

		content = Html.stripHtml(content);

		Document doc = new Document();

		LuceneUtil.addKeyword(
			doc, LuceneFields.UID, LuceneFields.getUID(PORTLET_ID, articleId));

		LuceneUtil.addKeyword(doc, LuceneFields.COMPANY_ID, companyId);
		LuceneUtil.addKeyword(doc, LuceneFields.PORTLET_ID, PORTLET_ID);
		LuceneUtil.addKeyword(doc, LuceneFields.GROUP_ID, groupId);

		LuceneUtil.addText(doc, LuceneFields.TITLE, title);
		LuceneUtil.addText(doc, LuceneFields.CONTENT, content);
		LuceneUtil.addText(doc, LuceneFields.DESCRIPTION, description);

		LuceneUtil.addModifiedDate(doc);

		LuceneUtil.addKeyword(doc, "articleId", articleId);
		LuceneUtil.addKeyword(doc, "version", version);
		LuceneUtil.addKeyword(doc, "type", type);
		LuceneUtil.addDate(doc, "displayDate", displayDate);

		LuceneUtil.addKeyword(doc, LuceneFields.TAG_ENTRY, tagsEntries);

		return doc;
	}

	public static void updateArticle(
			long companyId, long groupId, String articleId, double version,
			String title, String description, String content, String type,
			Date displayDate, String[] tagsEntries)
		throws IOException {

		try {
			deleteArticle(companyId, articleId);
		}
		catch (IOException ioe) {
		}

		addArticle(
			companyId, groupId, articleId, version, title, description, content,
			type, displayDate, tagsEntries);
	}

	public DocumentSummary getDocumentSummary(
		com.liferay.portal.kernel.search.Document doc, PortletURL portletURL) {

		// Title

		String title = doc.get(LuceneFields.TITLE);

		// Content

		String content = doc.get(LuceneFields.CONTENT);

		content = StringUtil.shorten(content, 200);

		// URL

		String groupId = doc.get("groupId");
		String articleId = doc.get("articleId");
		String version = doc.get("version");

		portletURL.setParameter("struts_action", "/journal/edit_article");
		portletURL.setParameter("groupId", groupId);
		portletURL.setParameter("articleId", articleId);
		portletURL.setParameter("version", version);

		return new DocumentSummary(title, content, portletURL);
	}

	public void reIndex(String[] ids) throws SearchException {
		try {
			JournalArticleLocalServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new SearchException(e);
		}
	}

	private static String _getIndexableContent(String content) {
		try {
			StringMaker sm = new StringMaker();

			SAXReader reader = new SAXReader();

			org.dom4j.Document doc = reader.read(new StringReader(content));

			Element root = doc.getRootElement();

			_getIndexableContent(sm, root);

			return sm.toString();
		}
		catch (Exception e) {
			e.printStackTrace();

			return content;
		}
	}

	private static void _getIndexableContent(StringMaker sm, Element root)
		throws Exception {

		Iterator itr = root.elements().iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			String elType = el.attributeValue("type", StringPool.BLANK);

			if (elType.equals("text") || elType.equals("text_box") ||
				elType.equals("text_area")) {

				Element dynamicContent = el.element("dynamic-content");

				String text = dynamicContent.getText();

				sm.append(text);
				sm.append(StringPool.BLANK);
			}
			else if (el.getName().equals("static-content")) {
				String text = el.getText();

				sm.append(text);
				sm.append(StringPool.BLANK);
			}

			_getIndexableContent(sm, el);
		}
	}

}