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

package com.liferay.portlet.news.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portlet.news.model.Feed;
import com.liferay.portlet.news.util.NewsUtil;
import com.liferay.util.servlet.SessionMessages;

import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Set;
import java.util.StringTokenizer;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditPreferencesAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditPreferencesAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (!cmd.equals(Constants.UPDATE)) {
			return;
		}

		PortletPreferences prefs = req.getPreferences();

		String tabs1 = ParamUtil.getString(req, "tabs1");

		if (tabs1.equals("news-selections")) {
			String categoryName = req.getParameter("category_name");
			String list = req.getParameter("feeds");

			Set selFeeds = NewsUtil.getSelFeeds(prefs);

			Iterator itr = selFeeds.iterator();

			while (itr.hasNext()) {
				Feed feed = (Feed)itr.next();

				String feedURL = feed.getFeedURL();

				int pos = list.indexOf(feedURL);

				if ((pos == -1) &&
					(feed.getCategoryName().equals(categoryName))) {

					itr.remove();
				}
				else {
					list = StringUtil.replace(
						list, feedURL + StringPool.COMMA, StringPool.BLANK);
				}
			}

			Map feedMap = NewsUtil.getFeedMap();

			StringTokenizer st = new StringTokenizer(list, StringPool.COMMA);

			while (st.hasMoreTokens()) {
				Feed feed = (Feed)feedMap.get(st.nextToken());

				if (feed != null) {
					selFeeds.add(feed);
				}
			}

			prefs.setValues("sel-feeds", NewsUtil.getSelFeeds(selFeeds));
		}
		else if (tabs1.equals("display-settings")) {
			String list = req.getParameter("feeds");
			int articlesPerNews = ParamUtil.get(req, "apn", 4);

			prefs.setValue(
				"articles-per-news", Integer.toString(articlesPerNews));

			Set selFeeds = new LinkedHashSet();

			Map feedMap = NewsUtil.getFeedMap();

			StringTokenizer st = new StringTokenizer(list, StringPool.COMMA);

			while (st.hasMoreTokens()) {
				Feed feed = (Feed)feedMap.get(st.nextToken());

				if (feed != null) {
					selFeeds.add(feed);
				}
			}

			prefs.setValues("sel-feeds", NewsUtil.getSelFeeds(selFeeds));
		}

		prefs.store();

		SessionMessages.add(req, config.getPortletName() + ".doEdit");
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		return mapping.findForward("portlet.news.edit");
	}

}