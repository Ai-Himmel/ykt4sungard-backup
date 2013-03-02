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

package com.liferay.portlet.bookmarks.util;

import com.liferay.portal.kernel.search.DocumentSummary;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.bookmarks.service.BookmarksFolderLocalServiceUtil;

import java.io.IOException;

import javax.portlet.PortletURL;

import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;

/**
 * <a href="Indexer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Indexer implements com.liferay.portal.kernel.search.Indexer {

	public static final String PORTLET_ID = PortletKeys.BOOKMARKS;

	public static void addEntry(
			long companyId, long groupId, long folderId, long entryId,
			String title, String content, String description,
			String[] tagsEntries)
		throws IOException {

		Document doc = getAddEntryDocument(
			companyId, groupId, folderId, entryId, title, content, description,
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

	public static void deleteEntry(long companyId, long entryId)
		throws IOException {

		LuceneUtil.deleteDocuments(
			companyId,
			new Term(
				LuceneFields.UID, LuceneFields.getUID(PORTLET_ID, entryId)));
	}

	public static Document getAddEntryDocument(
		long companyId, long groupId, long folderId, long entryId, String title,
		String content, String description, String[] tagsEntries) {

		Document doc = new Document();

		LuceneUtil.addKeyword(
			doc, LuceneFields.UID, LuceneFields.getUID(PORTLET_ID, entryId));

		LuceneUtil.addKeyword(doc, LuceneFields.COMPANY_ID, companyId);
		LuceneUtil.addKeyword(doc, LuceneFields.PORTLET_ID, PORTLET_ID);
		LuceneUtil.addKeyword(doc, LuceneFields.GROUP_ID, groupId);

		LuceneUtil.addText(doc, LuceneFields.TITLE, title);
		LuceneUtil.addText(doc, LuceneFields.CONTENT, content);
		LuceneUtil.addText(doc, LuceneFields.DESCRIPTION, description);

		LuceneUtil.addModifiedDate(doc);

		LuceneUtil.addKeyword(doc, "folderId", folderId);
		LuceneUtil.addKeyword(doc, "entryId", entryId);

		LuceneUtil.addKeyword(doc, LuceneFields.TAG_ENTRY, tagsEntries);

		return doc;
	}

	public static void updateEntry(
			long companyId, long groupId, long folderId, long entryId,
			String title, String content, String description,
			String[] tagsEntries)
		throws IOException {

		try {
			deleteEntry(companyId, entryId);
		}
		catch (IOException ioe) {
		}

		addEntry(
			companyId, groupId, folderId, entryId, title, content, description,
			tagsEntries);
	}

	public DocumentSummary getDocumentSummary(
		com.liferay.portal.kernel.search.Document doc, PortletURL portletURL) {

		// Title

		String title = doc.get(LuceneFields.TITLE);

		// Content

		String content = doc.get(LuceneFields.CONTENT);

		content = StringUtil.shorten(content, 200);

		// URL

		String entryId = doc.get("entryId");

		portletURL.setParameter("struts_action", "/bookmarks/edit_entry");
		portletURL.setParameter("entryId", entryId);

		return new DocumentSummary(title, content, portletURL);
	}

	public void reIndex(String[] ids) throws SearchException {
		try {
			BookmarksFolderLocalServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new SearchException(e);
		}
	}

}