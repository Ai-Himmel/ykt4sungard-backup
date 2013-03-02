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

package com.liferay.portal.search;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.search.SearchContainer;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.search.OpenSearch;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.uuid.PortalUUIDUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletURLImpl;
import com.liferay.util.Http;

import java.util.Date;

import javax.portlet.PortletMode;
import javax.portlet.PortletModeException;
import javax.portlet.PortletURL;
import javax.portlet.WindowState;
import javax.portlet.WindowStateException;

import javax.servlet.http.HttpServletRequest;

import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="BaseOpenSearchImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 * @author Brian Wing Shun Chan
 *
 */
public abstract class BaseOpenSearchImpl implements OpenSearch {

	public boolean isEnabled() {
		return true;
	}

	public String search(HttpServletRequest req, String url)
		throws SearchException {

		String keywords = GetterUtil.getString(
			Http.getParameter(url, "keywords", false));
		int startPage = GetterUtil.getInteger(
			Http.getParameter(url, "p", false), 1);
		int itemsPerPage = GetterUtil.getInteger(
			Http.getParameter(url, "c", false), SearchContainer.DEFAULT_DELTA);

		return search(req, keywords, startPage, itemsPerPage);
	}

	public abstract String search(
			HttpServletRequest req, String keywords, int startPage,
			int itemsPerPage)
		throws SearchException;

	protected void addSearchResult(
		Element root, String title, String link, Date updated, String summary,
		double score) {

		// entry

		Element entry = OpenSearchUtil.addElement(
			root, "entry", OpenSearchUtil.DEFAULT_NAMESPACE);

		// title

		OpenSearchUtil.addElement(
			entry, "title", OpenSearchUtil.DEFAULT_NAMESPACE, title);

		// link

		Element entryLink = OpenSearchUtil.addElement(
			entry, "link", OpenSearchUtil.DEFAULT_NAMESPACE);

		entryLink.addAttribute("href", link);

		// id

		OpenSearchUtil.addElement(
			entry, "id", OpenSearchUtil.DEFAULT_NAMESPACE,
			"urn:uuid:" + PortalUUIDUtil.generate());

		// updated

		OpenSearchUtil.addElement(
			entry, "updated", OpenSearchUtil.DEFAULT_NAMESPACE, updated);

		// summary

		OpenSearchUtil.addElement(
			entry, "summary", OpenSearchUtil.DEFAULT_NAMESPACE, summary);

		// relevance:score

		OpenSearchUtil.addElement(
			entry, "score", OpenSearchUtil.RELEVANCE_NAMESPACE, score);
	}

	protected Object[] addSearchResults(
		String keywords, int startPage, int itemsPerPage, int total,
		String title, String searchPath, ThemeDisplay themeDisplay) {

		return addSearchResults(
			keywords, startPage, itemsPerPage, null, title, searchPath,
			themeDisplay);
	}

	protected Object[] addSearchResults(
		String keywords, int startPage, int itemsPerPage, Hits hits,
		String title, String searchPath, ThemeDisplay themeDisplay) {

		return addSearchResults(
			keywords, startPage, itemsPerPage, 0, hits, title, searchPath,
			themeDisplay);
	}

	protected Object[] addSearchResults(
		String keywords, int startPage, int itemsPerPage, int total, Hits hits,
		String title, String searchPath, ThemeDisplay themeDisplay) {

		int begin = (startPage * itemsPerPage) - itemsPerPage;

		if (hits != null) {
			int end = startPage * itemsPerPage;

			total = hits.getLength();

			if (end > total) {
				end = total;
			}

			hits = hits.subset(begin, end);
		}

		int totalPages = 0;

		if (total % itemsPerPage == 0) {
			totalPages = total / itemsPerPage;
		}
		else {
			totalPages = (total / itemsPerPage) + 1;
		}

		int previousPage = startPage - 1;
		int nextPage = startPage + 1;

		// Create document

		org.dom4j.Document doc = DocumentHelper.createDocument();

		// feed

		Element root = doc.addElement("feed");

		root.add(OpenSearchUtil.getNamespace(OpenSearchUtil.DEFAULT_NAMESPACE));
		root.add(OpenSearchUtil.getNamespace(OpenSearchUtil.OS_NAMESPACE));
		root.add(
			OpenSearchUtil.getNamespace(OpenSearchUtil.RELEVANCE_NAMESPACE));

		// title

		OpenSearchUtil.addElement(
			root, "title", OpenSearchUtil.DEFAULT_NAMESPACE, title);

		// updated

		OpenSearchUtil.addElement(
			root, "updated", OpenSearchUtil.DEFAULT_NAMESPACE, new Date());

		// author

		Element author = OpenSearchUtil.addElement(
			root, "author", OpenSearchUtil.DEFAULT_NAMESPACE);

		// name

		OpenSearchUtil.addElement(
			author, "name", OpenSearchUtil.DEFAULT_NAMESPACE,
			themeDisplay.getUserId());

		// id

		OpenSearchUtil.addElement(
			root, "id", OpenSearchUtil.DEFAULT_NAMESPACE,
			"urn:uuid:" + PortalUUIDUtil.generate());

		// opensearch:totalResults

		OpenSearchUtil.addElement(
			root, "totalResults", OpenSearchUtil.OS_NAMESPACE, total);

		// opensearch:startIndex

		OpenSearchUtil.addElement(
			root, "startIndex", OpenSearchUtil.OS_NAMESPACE, begin + 1);

		// opensearch:itemsPerPage

		OpenSearchUtil.addElement(
			root, "itemsPerPage", OpenSearchUtil.OS_NAMESPACE, itemsPerPage);

		// opensearch:Query

		Element query = OpenSearchUtil.addElement(
			root, "Query", OpenSearchUtil.OS_NAMESPACE);

		query.addAttribute("role", "request");
		query.addAttribute("searchTerms", keywords);
		query.addAttribute("startPage", String.valueOf(startPage));

		// links

		String searchURL = themeDisplay.getURLPortal() + searchPath;

		OpenSearchUtil.addLink(
			root, searchURL, "self", keywords, startPage, itemsPerPage);
		OpenSearchUtil.addLink(
			root, searchURL, "first", keywords, 1, itemsPerPage);

		if (previousPage > 0) {
			OpenSearchUtil.addLink(
				root, searchURL, "previous", keywords, previousPage,
				itemsPerPage);
		}

		if (nextPage <= totalPages) {
			OpenSearchUtil.addLink(
				root, searchURL, "next", keywords, nextPage, itemsPerPage);
		}

		OpenSearchUtil.addLink(
			root, searchURL, "last", keywords, totalPages, itemsPerPage);

		Element link = OpenSearchUtil.addElement(
			root, "link", OpenSearchUtil.DEFAULT_NAMESPACE);

		link.addAttribute("rel", "search");
		link.addAttribute("href", searchPath + "_description.xml");
		link.addAttribute("type", "application/opensearchdescription+xml");

		return new Object[] {hits, doc, root};
	}

	protected PortletURL getPortletURL(HttpServletRequest req, String portletId)
		throws PortalException, PortletModeException, SystemException,
			   WindowStateException {

		return getPortletURL(req, portletId, 0);
	}

	protected PortletURL getPortletURL(
			HttpServletRequest req, String portletId, long groupId)
		throws PortalException, PortletModeException, SystemException,
			   WindowStateException {

		long plid = LayoutLocalServiceUtil.getDefaultPlid(groupId, true);

		if (plid == 0) {
			plid = LayoutLocalServiceUtil.getDefaultPlid(groupId, false);
		}

		if (plid == 0) {
			Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

			if (layout != null) {
				plid = layout.getPlid();
			}
		}

		PortletURL portletURL = new PortletURLImpl(req, portletId, plid, false);

		portletURL.setWindowState(WindowState.MAXIMIZED);
		portletURL.setPortletMode(PortletMode.VIEW);

		return portletURL;
	}

}