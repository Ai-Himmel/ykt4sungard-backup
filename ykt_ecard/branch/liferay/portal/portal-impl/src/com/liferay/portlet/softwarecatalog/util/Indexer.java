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

package com.liferay.portlet.softwarecatalog.util;

import com.liferay.portal.kernel.search.DocumentSummary;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalServiceUtil;
import com.liferay.util.Html;

import java.io.IOException;

import java.util.Date;

import javax.portlet.PortletURL;

import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;

/**
 * <a href="Indexer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 * @author Brian Wing Shun Chan
 * @author Harry Mark
 *
 */
public class Indexer
	implements com.liferay.portal.kernel.search.Indexer {

	public static final String PORTLET_ID = PortletKeys.SOFTWARE_CATALOG;

	public static void addProductEntry(
			long companyId, long groupId, long userId, String userName,
			long productEntryId, String name, Date modifiedDate, String version,
			String type, String shortDescription, String longDescription,
			String pageURL, String repoGroupId, String repoArtifactId)
		throws IOException {

		Document doc = getAddProductEntryDocument(
			companyId, groupId, userId, userName, productEntryId, name,
			modifiedDate, version, type, shortDescription, longDescription,
			pageURL, repoGroupId, repoArtifactId);

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

	public static void deleteProductEntry(long companyId, long productEntryId)
		throws IOException {

		LuceneUtil.deleteDocuments(
			companyId,
			new Term(
				LuceneFields.UID,
				LuceneFields.getUID(PORTLET_ID, productEntryId)));
	}

	public static Document getAddProductEntryDocument(
		long companyId, long groupId, long userId, String userName,
		long productEntryId, String name, Date modifiedDate, String version,
		String type, String shortDescription, String longDescription,
		String pageURL, String repoGroupId, String repoArtifactId) {

		shortDescription = Html.stripHtml(shortDescription);
		longDescription = Html.stripHtml(longDescription);

		String content =
			userId + " " + userName + " " + type + " " + shortDescription +
				" " + longDescription + " " + pageURL + repoGroupId + " " +
					repoArtifactId;

		Document doc = new Document();

		doc.add(
			LuceneFields.getKeyword(
				LuceneFields.UID,
				LuceneFields.getUID(PORTLET_ID, productEntryId)));

		doc.add(LuceneFields.getKeyword(LuceneFields.COMPANY_ID, companyId));
		doc.add(LuceneFields.getKeyword(LuceneFields.PORTLET_ID, PORTLET_ID));
		doc.add(LuceneFields.getKeyword(LuceneFields.GROUP_ID, groupId));
		doc.add(LuceneFields.getKeyword(LuceneFields.USER_ID, userId));

		doc.add(LuceneFields.getText(LuceneFields.TITLE, name));
		doc.add(LuceneFields.getText(LuceneFields.CONTENT, content));

		doc.add(LuceneFields.getDate(LuceneFields.MODIFIED));

		doc.add(LuceneFields.getKeyword("productEntryId", productEntryId));
		doc.add(LuceneFields.getDate("modified-date", modifiedDate));
		doc.add(LuceneFields.getText("version", version));
		doc.add(LuceneFields.getKeyword("type", type));
		doc.add(LuceneFields.getKeyword("repoGroupId", repoGroupId));
		doc.add(LuceneFields.getKeyword("repoArtifactId", repoArtifactId));

		return doc;
	}

	public static void updateProductEntry(
			long companyId, long groupId, long userId, String userName,
			long productEntryId, String name, Date modifiedDate, String version,
			String type, String shortDescription, String longDescription,
			String pageURL, String repoGroupId, String repoArtifactId)
		throws IOException {

		try {
			deleteProductEntry(companyId, productEntryId);
		}
		catch (IOException ioe) {
		}

		addProductEntry(
			companyId, groupId, userId, userName, productEntryId, name,
			modifiedDate, version, type, shortDescription, longDescription,
			pageURL, repoGroupId, repoArtifactId);
	}

	public DocumentSummary getDocumentSummary(
		com.liferay.portal.kernel.search.Document doc, PortletURL portletURL) {

		// Title

		String title = doc.get(LuceneFields.TITLE);

		// Content

		String content = doc.get(LuceneFields.CONTENT);

		content = StringUtil.shorten(content, 200);

		// URL

		String productEntryId = doc.get("productEntryId");

		portletURL.setParameter(
			"struts_action", "/software_catalog/view_product_entry");
		portletURL.setParameter("productEntryId", productEntryId);

		return new DocumentSummary(title, content, portletURL);
	}

	public void reIndex(String[] ids) throws SearchException {
		try {
			SCProductEntryLocalServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new SearchException(e);
		}
	}

}