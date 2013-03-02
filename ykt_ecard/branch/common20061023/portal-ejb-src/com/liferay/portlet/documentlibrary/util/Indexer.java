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

package com.liferay.portlet.documentlibrary.util;

import com.liferay.documentlibrary.service.spring.DLServiceUtil;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.documentlibrary.model.DLRepository;
import com.liferay.portlet.documentlibrary.service.spring.DLRepositoryLocalServiceUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.lucene.DocumentSummary;
import com.liferay.util.lucene.IndexerException;

import java.util.List;

import javax.portlet.PortletURL;

import org.apache.lucene.document.Document;

/**
 * <a href="Indexer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.13 $
 *
 */
public class Indexer implements com.liferay.util.lucene.Indexer {

	public DocumentSummary getDocumentSummary(
		Document doc, PortletURL portletURL) {

		// Company ID

		String companyId = doc.get(LuceneFields.COMPANY_ID);

		// Content

		String content = doc.get(LuceneFields.CONTENT);
		content = StringUtil.shorten(content, 200);

		// URL

		String repositoryId = doc.get("repositoryId");
		String docPath = StringUtil.replace(
			doc.get("path"), StringPool.BACK_SLASH, StringPool.FORWARD_SLASH);

		String filePath = null;
		String fileName = null;

		String rootDir = PropsUtil.get(PropsUtil.DL_ROOT_DIR);
		String versionRootDir = PropsUtil.get(PropsUtil.DL_VERSION_ROOT_DIR);

		if (docPath.startsWith(rootDir)) {
			int x = (rootDir + companyId).length() + 1;
			int y = docPath.indexOf(StringPool.FORWARD_SLASH, x);

			docPath = docPath.substring(y, docPath.length());

			x = docPath.lastIndexOf(StringPool.FORWARD_SLASH);

			filePath = docPath.substring(0, x);
			fileName = docPath.substring(x + 1, docPath.length());
		}
		else if (docPath.startsWith(versionRootDir)) {
			int x = (versionRootDir + companyId).length() + 1;
			int y = docPath.indexOf(StringPool.FORWARD_SLASH, x);

			docPath = docPath.substring(y, docPath.length());

			x = docPath.lastIndexOf(StringPool.FORWARD_SLASH);
			y = docPath.lastIndexOf(StringPool.UNDERLINE);
			int z = docPath.lastIndexOf(StringPool.UNDERLINE, y - 1);

			filePath = docPath.substring(0, x);
			fileName = docPath.substring(x + 1, z);
		}

		portletURL.setParameter(
			"struts_action", "/document_library/get_file_profile");

		portletURL.setParameter("repository_id", repositoryId);
		portletURL.setParameter("file_path", filePath);
		portletURL.setParameter("file_name", fileName);

		// Title

		String title = filePath + "/" + fileName;

		return new DocumentSummary(title, content, portletURL);
	}

	public void reIndex(String[] ids) throws IndexerException {
		try {
			String companyId = ids[0];

			List repositories =
				DLRepositoryLocalServiceUtil.getRepositories(companyId);

			for (int i = 0; i < repositories.size(); i++) {
				DLRepository repository = (DLRepository)repositories.get(i);

				String portletId = PortletKeys.DOCUMENT_LIBRARY;
				String groupId = repository.getGroupId();
				String repositoryId = repository.getRepositoryId();

				String[] newIds = {companyId, portletId, groupId, repositoryId};

				DLServiceUtil.reIndex(newIds);
			}
		}
		catch (Exception e) {
			throw new IndexerException(e);
		}
	}

}