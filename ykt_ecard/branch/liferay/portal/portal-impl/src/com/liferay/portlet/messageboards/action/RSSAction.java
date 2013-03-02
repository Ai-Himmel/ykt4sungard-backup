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

package com.liferay.portlet.messageboards.action;

import com.liferay.portal.kernel.dao.search.SearchContainer;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.messageboards.NoSuchCategoryException;
import com.liferay.portlet.messageboards.service.MBMessageServiceUtil;
import com.liferay.util.RSSUtil;
import com.liferay.util.servlet.ServletResponseUtil;

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

		String plid = ParamUtil.getString(req, "p_l_id");
		long companyId = ParamUtil.getLong(req, "companyId");
		long groupId = ParamUtil.getLong(req, "groupId");
		long userId = ParamUtil.getLong(req, "userId");
		long categoryId = ParamUtil.getLong(req, "categoryId");
		long threadId = ParamUtil.getLong(req, "threadId");
		int max = ParamUtil.getInteger(
			req, "max", SearchContainer.DEFAULT_DELTA);
		String type = ParamUtil.getString(req, "type", RSSUtil.DEFAULT_TYPE);
		double version = ParamUtil.getDouble(
			req, "version", RSSUtil.DEFAULT_VERSION);
		String displayStyle = ParamUtil.getString(
			req, "displayStyle", RSSUtil.DISPLAY_STYLE_FULL_CONTENT);

		String entryURL =
			themeDisplay.getURLPortal() + themeDisplay.getPathMain() +
				"/message_boards/find_message?p_l_id=" + plid;

		String rss = StringPool.BLANK;

		if (companyId > 0) {
			String feedURL = StringPool.BLANK;

			rss = MBMessageServiceUtil.getCompanyMessagesRSS(
				companyId, max, type, version, displayStyle, feedURL, entryURL);
		}
		else if (groupId > 0) {
			String feedURL =
				themeDisplay.getURLPortal() + themeDisplay.getPathMain() +
					"/message_boards/find_recent_posts?p_l_id=" + plid;

			if (userId > 0) {
				rss = MBMessageServiceUtil.getGroupMessagesRSS(
					groupId, userId, max, type, version, displayStyle, feedURL,
					entryURL);
			}
			else {
				rss = MBMessageServiceUtil.getGroupMessagesRSS(
					groupId, max, type, version, displayStyle, feedURL,
					entryURL);
			}
		}
		else if (categoryId > 0) {
			String feedURL =
				themeDisplay.getURLPortal() + themeDisplay.getPathMain() +
					"/message_boards/find_category?p_l_id=" + plid +
						"&categoryId=" + categoryId;

			try {
				rss = MBMessageServiceUtil.getCategoryMessagesRSS(
					categoryId, max, type, version, displayStyle, feedURL,
					entryURL);
			}
			catch (NoSuchCategoryException nsce) {
				if (_log.isWarnEnabled()) {
					_log.warn(nsce);
				}
			}
		}
		else if (threadId > 0) {
			String feedURL =
				themeDisplay.getURLPortal() + themeDisplay.getPathMain() +
					"/message_boards/find_thread?p_l_id=" + plid +
						"&threadId=" + threadId;

			rss = MBMessageServiceUtil.getThreadMessagesRSS(
				threadId, max, type, version, displayStyle, feedURL, entryURL);
		}

		return rss.getBytes(StringPool.UTF8);
	}

	private static Log _log = LogFactory.getLog(RSSAction.class);

}