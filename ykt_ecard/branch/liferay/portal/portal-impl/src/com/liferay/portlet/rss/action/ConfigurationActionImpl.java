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

package com.liferay.portlet.rss.action;

import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.ValidatorException;

/**
 * <a href="ConfigurationActionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ConfigurationActionImpl implements ConfigurationAction {

	public void processAction(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		String portletResource = ParamUtil.getString(
			req, "portletResource");

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				req, portletResource, true, true);

		if (cmd.equals("remove-footer-article")) {
			removeFooterArticle(req, prefs);
		}
		else if (cmd.equals("remove-header-article")) {
			removeHeaderArticle(req, prefs);
		}
		else if (cmd.equals("set-footer-article")) {
			setFooterArticle(req, prefs);
		}
		else if (cmd.equals("set-header-article")) {
			setHeaderArticle(req, prefs);
		}
		else if (cmd.equals(Constants.UPDATE)) {
			updateConfiguration(req, prefs);
		}

		if (SessionErrors.isEmpty(req)) {
			try {
				prefs.store();
			}
			catch (ValidatorException ve) {
				SessionErrors.add(req, ValidatorException.class.getName(), ve);

				return;
			}

			SessionMessages.add(req, config.getPortletName() + ".doConfigure");
		}
	}

	public String render(
			PortletConfig config, RenderRequest req, RenderResponse res)
		throws Exception {

		return "/html/portlet/rss/configuration.jsp";
	}

	protected void removeFooterArticle(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		prefs.setValues(
			"footer-article-resouce-values", new String[] {"0", ""});
	}

	protected void removeHeaderArticle(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		prefs.setValues(
			"header-article-resouce-values", new String[] {"0", ""});
	}

	protected void setFooterArticle(ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String footerArticleResouceId = ParamUtil.getString(req, "resourceId");
		String footerArticleResouceTitle = ParamUtil.getString(
			req, "resourceTitle");

		prefs.setValues(
			"footer-article-resouce-values",
			new String[] {footerArticleResouceId, footerArticleResouceTitle});
	}

	protected void setHeaderArticle(ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String headerArticleResouceId = ParamUtil.getString(req, "resourceId");
		String headerArticleResouceTitle = ParamUtil.getString(
			req, "resourceTitle");

		prefs.setValues(
			"header-article-resouce-values",
		new String[] {headerArticleResouceId, headerArticleResouceTitle});
	}

	protected void updateConfiguration(
			ActionRequest req, PortletPreferences prefs)
		throws Exception {

		String[] urls = req.getParameterValues("url");
		String[] titles = req.getParameterValues("title");
		int entriesPerFeed = ParamUtil.getInteger(req, "entriesPerFeed", 4);
		boolean showFeedTitle = ParamUtil.getBoolean(req, "showFeedTitle");
		boolean showFeedPublishedDate = ParamUtil.getBoolean(
			req, "showFeedPublishedDate");
		boolean showFeedDescription = ParamUtil.getBoolean(
			req, "showFeedDescription");
		boolean showFeedImage = ParamUtil.getBoolean(req, "showFeedImage");
		String feedImageAlignment = ParamUtil.getString(
			req, "feedImageAlignment");
		long headerArticleResouceId = ParamUtil.getLong(
			req, "headerArticleResouceId");
		long footerArticleResouceId = ParamUtil.getLong(
			req, "footerArticleResouceId");

		if (urls != null && titles != null) {
			prefs.setValues("urls", urls);
			prefs.setValues("titles", titles);
		}
		else {
			prefs.setValues("urls", new String[0]);
			prefs.setValues("titles", new String[0]);
		}

		prefs.setValue("items-per-channel", String.valueOf(entriesPerFeed));
		prefs.setValue("show-feed-title", String.valueOf(showFeedTitle));
		prefs.setValue(
			"show-feed-published-date", String.valueOf(showFeedPublishedDate));
		prefs.setValue(
			"show-feed-description", String.valueOf(showFeedDescription));
		prefs.setValue("show-feed-image", String.valueOf(showFeedImage));
		prefs.setValue(
			"feed-image-alignment", String.valueOf(feedImageAlignment));
		prefs.setValue(
			"header-article-resouce-id",
			String.valueOf(headerArticleResouceId));
		prefs.setValue(
			"footer-article-resouce-id",
			String.valueOf(footerArticleResouceId));
	}

}