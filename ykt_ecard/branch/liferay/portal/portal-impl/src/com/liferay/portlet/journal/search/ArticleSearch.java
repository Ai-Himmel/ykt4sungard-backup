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

package com.liferay.portlet.journal.search;

import com.liferay.portal.kernel.dao.search.SearchContainer;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.PortalPreferences;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.CollectionFactory;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.portlet.PortletConfig;
import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ArticleSearch.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ArticleSearch extends SearchContainer {

	static List headerNames = new ArrayList();
	static Map orderableHeaders = CollectionFactory.getHashMap();

	static {
		headerNames.add("id");
		headerNames.add("name");
		headerNames.add("version");
		headerNames.add("modified-date");
		headerNames.add("display-date");
		headerNames.add("author");

		orderableHeaders.put("id", "id");
		orderableHeaders.put("name", "title");
		orderableHeaders.put("version", "version");
		orderableHeaders.put("modified-date", "modified-date");
		orderableHeaders.put("display-date", "display-date");
	}

	public static final String EMPTY_RESULTS_MESSAGE =
		"no-articles-were-found";

	public ArticleSearch(RenderRequest req, PortletURL iteratorURL) {
		super(
			req, new ArticleDisplayTerms(req), new ArticleSearchTerms(req),
			DEFAULT_CUR_PARAM, DEFAULT_DELTA, iteratorURL, headerNames,
			EMPTY_RESULTS_MESSAGE);

		PortletConfig portletConfig = (PortletConfig)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		ArticleDisplayTerms displayTerms =
			(ArticleDisplayTerms)getDisplayTerms();
		ArticleSearchTerms searchTerms = (ArticleSearchTerms)getSearchTerms();

		if (!portletConfig.getPortletName().equals(PortletKeys.JOURNAL)) {
			displayTerms.setStatus("approved");
			searchTerms.setStatus("approved");
		}

		iteratorURL.setParameter(
			ArticleDisplayTerms.GROUP_ID,
			String.valueOf(displayTerms.getGroupId()));
		iteratorURL.setParameter(
			ArticleDisplayTerms.ARTICLE_ID, displayTerms.getArticleId());
		iteratorURL.setParameter(
			ArticleDisplayTerms.VERSION,
			String.valueOf(displayTerms.getVersion()));
		iteratorURL.setParameter(
			ArticleDisplayTerms.TITLE, displayTerms.getTitle());
		iteratorURL.setParameter(
			ArticleDisplayTerms.DESCRIPTION, displayTerms.getDescription());
		iteratorURL.setParameter(
			ArticleDisplayTerms.CONTENT, displayTerms.getContent());
		iteratorURL.setParameter(
			ArticleDisplayTerms.TYPE, displayTerms.getType());
		iteratorURL.setParameter(
			ArticleDisplayTerms.STRUCTURE_ID, displayTerms.getStructureId());
		iteratorURL.setParameter(
			ArticleDisplayTerms.TEMPLATE_ID, displayTerms.getTemplateId());
		iteratorURL.setParameter(
			ArticleDisplayTerms.STATUS, displayTerms.getStatus());

		try {
			PortalPreferences prefs =
				PortletPreferencesFactoryUtil.getPortalPreferences(req);

			String orderByCol = ParamUtil.getString(req, "orderByCol");
			String orderByType = ParamUtil.getString(req, "orderByType");

			if (Validator.isNotNull(orderByCol) &&
				Validator.isNotNull(orderByType)) {

				prefs.setValue(
					PortletKeys.JOURNAL, "articles-order-by-col", orderByCol);
				prefs.setValue(
					PortletKeys.JOURNAL, "articles-order-by-type", orderByType);
			}
			else {
				orderByCol = prefs.getValue(
					PortletKeys.JOURNAL, "articles-order-by-col", "id");
				orderByType = prefs.getValue(
					PortletKeys.JOURNAL, "articles-order-by-type", "asc");
			}

			OrderByComparator orderByComparator =
				JournalUtil.getArticleOrderByComparator(
					orderByCol, orderByType);

			setOrderableHeaders(orderableHeaders);
			setOrderByCol(orderByCol);
			setOrderByType(orderByType);
			setOrderByComparator(orderByComparator);
		}
		catch (Exception e) {
			_log.error(e);
		}
	}

	private static Log _log = LogFactory.getLog(ArticleSearch.class);

}