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

package com.liferay.portlet.directory.util;

import com.liferay.portal.kernel.search.SearchException;
import com.liferay.portal.model.User;
import com.liferay.portal.search.BaseOpenSearchImpl;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebKeys;
import com.liferay.portal.util.comparator.ContactLastNameComparator;

import java.util.Date;
import java.util.List;

import javax.portlet.PortletURL;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Element;

/**
 * <a href="DirectoryOpenSearchImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DirectoryOpenSearchImpl extends BaseOpenSearchImpl {

	public static final String SEARCH_PATH = "/c/directory/open_search";

	public String search(
			HttpServletRequest req, String keywords, int startPage,
			int itemsPerPage)
		throws SearchException {

		try {
			return _search(req, keywords, startPage, itemsPerPage);
		}
		catch (Exception e) {
			throw new SearchException(e);
		}
	}

	private String _search(
			HttpServletRequest req, String keywords, int startPage,
			int itemsPerPage)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		int begin = (startPage * itemsPerPage) - itemsPerPage;
		int end = startPage * itemsPerPage;

		List results = UserLocalServiceUtil.search(
			themeDisplay.getCompanyId(), keywords, Boolean.TRUE, null, begin,
			end, new ContactLastNameComparator(true));

		int total = UserLocalServiceUtil.searchCount(
			themeDisplay.getCompanyId(), keywords, Boolean.TRUE, null);

		Object[] values = addSearchResults(
			keywords, startPage, itemsPerPage, total, null,
			"Liferay Directory Search: " + keywords, SEARCH_PATH, themeDisplay);

		org.dom4j.Document doc = (org.dom4j.Document)values[1];
		Element root = (Element)values[2];

		for (int i = 0; i < results.size(); i++) {
			User user = (User)results.get(i);

			String portletId = PortletKeys.DIRECTORY;

			//String portletTitle = PortalUtil.getPortletTitle(
			//	portletId, themeDisplay.getUser());

			PortletURL portletURL = getPortletURL(req, portletId);

			String title = user.getFullName();
			String url = portletURL.toString();
			Date modifedDate = user.getModifiedDate();
			String content =
				user.getFullName() + " &lt;" + user.getEmailAddress() + "&gt;";
			double score = 1.0;

			addSearchResult(root, title, url, modifedDate, content, score);
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Return\n" + doc.asXML());
		}

		return doc.asXML();
	}

	private static Log _log = LogFactory.getLog(DirectoryOpenSearchImpl.class);

}