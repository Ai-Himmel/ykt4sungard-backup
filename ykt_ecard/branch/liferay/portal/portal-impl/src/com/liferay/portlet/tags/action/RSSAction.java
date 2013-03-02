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

package com.liferay.portlet.tags.action;

import com.liferay.portal.NoSuchCompanyException;
import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.kernel.dao.search.SearchContainer;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Group;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.tags.service.TagsAssetServiceUtil;
import com.liferay.portlet.tags.service.TagsEntryLocalServiceUtil;
import com.liferay.util.RSSUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import java.util.Date;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="RSSAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RSSAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			ServletResponseUtil.sendFile(
				res, null, getRSS(req), ContentTypes.TEXT_XML_UTF8);

			return null;
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

	protected byte[] getRSS(HttpServletRequest req) throws Exception {
		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long companyId = ParamUtil.getLong(req, "companyId");
		long groupId = ParamUtil.getLong(req, "groupId");
		int max = ParamUtil.getInteger(
			req, "max", SearchContainer.DEFAULT_DELTA);
		String type = ParamUtil.getString(req, "type", RSSUtil.DEFAULT_TYPE);
		double version = ParamUtil.getDouble(
			req, "version", RSSUtil.DEFAULT_VERSION);
		String displayStyle = ParamUtil.getString(
			req, "displayStyle", RSSUtil.DISPLAY_STYLE_FULL_CONTENT);

		String feedURL = StringPool.BLANK;

		String entryURL =
			themeDisplay.getURLPortal() + themeDisplay.getPathMain() +
				"/tags/find_asset?";

		String rss = StringPool.BLANK;

		if (companyId > 0) {
			try {
				rss = TagsAssetServiceUtil.getCompanyAssetsRSS(
					companyId, max, type, version, displayStyle, feedURL,
					entryURL);
			}
			catch (NoSuchCompanyException nsce) {
				if (_log.isWarnEnabled()) {
					_log.warn(nsce);
				}
			}
		}
		else if (groupId > 0) {
			try {
				Group group = GroupLocalServiceUtil.getGroup(groupId);

				companyId = group.getCompanyId();

				long[] classNameIds = new long[0];

				String[] allEntries = StringUtil.split(
					ParamUtil.getString(req, "tags"));

				long[] entryIds = TagsEntryLocalServiceUtil.getEntryIds(
					companyId, allEntries);

				String[] notEntries = StringUtil.split(
					ParamUtil.getString(req, "noTags"));

				long[] notEntryIds = TagsEntryLocalServiceUtil.getEntryIds(
					companyId, notEntries);

				boolean andOperator = false;
				String orderByCol1 = null;
				String orderByCol2 = null;
				String orderByType1 = null;
				String orderByType2 = null;
				boolean excludeZeroViewCount = false;
				Date publishDate = null;
				Date expirationDate = null;

				rss = TagsAssetServiceUtil.getAssetsRSS(
					groupId, classNameIds, entryIds, notEntryIds, andOperator,
					orderByCol1, orderByCol2, orderByType1, orderByType2,
					excludeZeroViewCount, publishDate, expirationDate,
					max, type, version, displayStyle, feedURL, entryURL);
			}
			catch (NoSuchGroupException nsge) {
				if (_log.isWarnEnabled()) {
					_log.warn(nsge);
				}
			}
		}

		return rss.getBytes(StringPool.UTF8);
	}

	private static Log _log = LogFactory.getLog(RSSAction.class);

}