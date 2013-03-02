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

package com.liferay.portlet.blogs.util;

import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portlet.blogs.service.spring.BlogsEntryServiceUtil;
import com.liferay.util.Html;
import com.liferay.util.StringUtil;
import com.liferay.util.lucene.DocumentSummary;
import com.liferay.util.lucene.IndexerException;

import java.io.IOException;

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
 * @version $Revision: 1.6 $
 *
 */
public class Indexer implements com.liferay.util.lucene.Indexer {

	public static void addEntry(
			String companyId, String portletId, String groupId,
			String blogsUserId, String entryId, String title, String content)
		throws IOException {

		content = Html.stripHtml(content);

		IndexWriter writer = LuceneUtil.getWriter(companyId);

		Document doc = new Document();

		doc.add(
			LuceneFields.getKeyword(
				LuceneFields.UID,
				LuceneFields.getUID(portletId, blogsUserId, entryId)));

		doc.add(LuceneFields.getKeyword(LuceneFields.COMPANY_ID, companyId));
		doc.add(LuceneFields.getKeyword(LuceneFields.PORTLET_ID, portletId));
		doc.add(LuceneFields.getKeyword(LuceneFields.GROUP_ID, groupId));

		doc.add(Field.Text(LuceneFields.TITLE, title));
		doc.add(Field.Text(LuceneFields.CONTENT, content));

		doc.add(LuceneFields.getDate(LuceneFields.MODIFIED));

		doc.add(LuceneFields.getKeyword("blogsUserId", blogsUserId));
		doc.add(LuceneFields.getKeyword("entryId", entryId));

		writer.addDocument(doc);

		writer.close();
	}

	public static void deleteEntry(
			String companyId, String portletId, String blogsUserId,
			String entryId)
		throws IOException {

		IndexReader reader = LuceneUtil.getReader(companyId);

		reader.delete(
			new Term(
				LuceneFields.UID,
				LuceneFields.getUID(portletId, blogsUserId, entryId)));

		reader.close();
	}

	public static void updateEntry(
			String companyId, String portletId, String groupId,
			String blogsUserId, String entryId, String title, String content)
		throws IOException {

		try {
			deleteEntry(companyId, portletId, blogsUserId, entryId);
		}
		catch (IOException ioe) {
		}

		addEntry(
			companyId, portletId, groupId, blogsUserId, entryId, title,
			content);
	}

	public DocumentSummary getDocumentSummary(
		Document doc, PortletURL portletURL) {

		// Title

		String title = doc.get(LuceneFields.TITLE);

		// Content

		String content = doc.get(LuceneFields.CONTENT);
		content = StringUtil.shorten(content, 200);

		// URL

		String blogsUserId = doc.get("blogsUserId");
		String entryId = doc.get("entryId");

		portletURL.setParameter("struts_action", "/blogs/view_entries");

		portletURL.setParameter("blogs_user_id", blogsUserId);
		portletURL.setParameter("entry_id", entryId);

		return new DocumentSummary(title, content, portletURL);
	}

	public void reIndex(String[] ids) throws IndexerException {
		try {
			BlogsEntryServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new IndexerException(e);
		}
	}

}