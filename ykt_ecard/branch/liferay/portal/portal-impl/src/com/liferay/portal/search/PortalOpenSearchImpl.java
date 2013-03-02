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

import com.liferay.portal.kernel.search.Document;
import com.liferay.portal.kernel.search.DocumentSummary;
import com.liferay.portal.kernel.search.Hits;
import com.liferay.portal.kernel.search.Indexer;
import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.CompanyLocalServiceUtil;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.service.JournalContentSearchLocalServiceUtil;

import java.util.Date;
import java.util.List;

import javax.portlet.PortletURL;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.document.DateTools;

import org.dom4j.Element;

/**
 * <a href="PortalOpenSearchImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 * @author Brian Wing Shun Chan
 *
 */
public class PortalOpenSearchImpl extends BaseOpenSearchImpl {

	public static final String SEARCH_PATH = "/c/search/open_search";

	public String search(
			HttpServletRequest req, String keywords, int startPage,
			int itemsPerPage)
		throws SearchException {

		Hits hits = null;

		try {
			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			hits = CompanyLocalServiceUtil.search(
				themeDisplay.getCompanyId(), keywords);

			Object[] values = addSearchResults(
				keywords, startPage, itemsPerPage, hits,
				"Liferay Portal Search: " + keywords, SEARCH_PATH,
				themeDisplay);

			Hits results = (Hits)values[0];
			org.dom4j.Document doc = (org.dom4j.Document)values[1];
			Element root = (Element)values[2];

			for (int i = 0; i < results.getLength(); i++) {
				Document result = results.doc(i);

				String portletId = (String)result.get(LuceneFields.PORTLET_ID);

				Portlet portlet = PortletLocalServiceUtil.getPortletById(
					themeDisplay.getCompanyId(), portletId);

				if (portlet == null) {
					continue;
				}

				String portletTitle = PortalUtil.getPortletTitle(
					portletId, themeDisplay.getUser());

				long groupId = GetterUtil.getLong(
					(String)result.get(LuceneFields.GROUP_ID));

				String title = StringPool.BLANK;

				PortletURL portletURL = getPortletURL(req, portletId, groupId);

				String url = portletURL.toString();

				Date modifedDate = DateTools.stringToDate(
					(String)result.get(LuceneFields.MODIFIED));

				String content = StringPool.BLANK;

				if (Validator.isNotNull(portlet.getIndexerClass())) {
					Indexer indexer = (Indexer)InstancePool.get(
						portlet.getIndexerClass());

					DocumentSummary docSummary = indexer.getDocumentSummary(
						result, portletURL);

					title = docSummary.getTitle();
					url = portletURL.toString();
					content = docSummary.getContent();

					if (portlet.getPortletId().equals(PortletKeys.JOURNAL)) {
						url = getJournalURL(themeDisplay, groupId, result);
					}
				}

				double score = hits.score(i);

				addSearchResult(
					root, portletTitle + " &raquo; " + title, url, modifedDate,
					content, score);
			}

			if (_log.isDebugEnabled()) {
				_log.debug("Return\n" + doc.asXML());
			}

			return doc.asXML();

		}
		catch (Exception e) {
			throw new SearchException(e);
		}
		finally {
			if (hits != null) {
				hits.closeSearcher();
			}
		}
	}

	protected String getJournalURL(
			ThemeDisplay themeDisplay, long groupId, Document result)
		throws Exception {

		Layout layout = themeDisplay.getLayout();

		String articleId = result.get("articleId");
		String version = result.get("version");

		List hitLayoutIds =
			JournalContentSearchLocalServiceUtil.getLayoutIds(
				layout.getGroupId(), layout.isPrivateLayout(), articleId);

		if (hitLayoutIds.size() > 0) {
			Long hitLayoutId = (Long)hitLayoutIds.get(0);

			Layout hitLayout = LayoutLocalServiceUtil.getLayout(
				layout.getGroupId(), layout.isPrivateLayout(),
				hitLayoutId.longValue());

			return PortalUtil.getLayoutURL(hitLayout, themeDisplay);
		}
		else {
			StringMaker sm = new StringMaker();

			sm.append(themeDisplay.getPathMain());
			sm.append("/journal/view_article_content?groupId=");
			sm.append(groupId);
			sm.append("&articleId=");
			sm.append(articleId);
			sm.append("&version=");
			sm.append(version);

			return sm.toString();
		}
	}

	private static Log _log = LogFactory.getLog(PortalOpenSearchImpl.class);

}