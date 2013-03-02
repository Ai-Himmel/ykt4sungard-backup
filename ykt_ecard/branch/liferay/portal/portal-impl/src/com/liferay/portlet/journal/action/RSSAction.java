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

package com.liferay.portlet.journal.action;

import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalArticleDisplay;
import com.liferay.portlet.journal.model.JournalFeed;
import com.liferay.portlet.journal.model.impl.JournalFeedImpl;
import com.liferay.portlet.journal.service.JournalContentSearchLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalFeedLocalServiceUtil;
import com.liferay.portlet.journal.util.JournalRSSUtil;
import com.liferay.portlet.journalcontent.util.JournalContentUtil;
import com.liferay.util.RSSUtil;

import com.sun.syndication.feed.synd.SyndContent;
import com.sun.syndication.feed.synd.SyndContentImpl;
import com.sun.syndication.feed.synd.SyndEntry;
import com.sun.syndication.feed.synd.SyndEntryImpl;
import com.sun.syndication.feed.synd.SyndFeed;
import com.sun.syndication.feed.synd.SyndFeedImpl;
import com.sun.syndication.io.FeedException;

import java.io.IOException;
import java.io.OutputStream;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;
import org.dom4j.XPath;

/**
 * <a href="RSSAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class RSSAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		if (req.getWindowState() == LiferayWindowState.EXCLUSIVE) {
			res.setContentType(ContentTypes.TEXT_XML_UTF8);

			OutputStream out = res.getPortletOutputStream();

			try {
				out.write(getRSS(req));
			}
			finally {
				out.close();
			}
		}

		return mapping.findForward(ActionConstants.COMMON_NULL);
	}

	protected String exportToRSS(
			JournalFeed feed, String languageId, Layout layout,
			ThemeDisplay themeDisplay)
		throws Exception {

		String feedURL =
			themeDisplay.getURLPortal() +
				PortalUtil.getLayoutFriendlyURL(layout, themeDisplay) +
					"/journal/rss/" + feed.getId();

		SyndFeed syndFeed = new SyndFeedImpl();

		syndFeed.setFeedType(feed.getFeedType() + "_" + feed.getFeedVersion());
		syndFeed.setTitle(feed.getName());
		syndFeed.setLink(feedURL);
		syndFeed.setDescription(feed.getDescription());

		List entries = new ArrayList();

		syndFeed.setEntries(entries);

		List articles = JournalRSSUtil.getArticles(feed);

		if (_log.isDebugEnabled()) {
			_log.debug("Syndicating " + articles.size() + " articles");
		}

		Iterator itr = articles.iterator();

		while (itr.hasNext()) {
			JournalArticle article = (JournalArticle)itr.next();

			String author = PortalUtil.getUserName(
				article.getUserId(), article.getUserName());
			String link = getEntryURL(feed, article, layout, themeDisplay);

			SyndEntry syndEntry = new SyndEntryImpl();

			syndEntry.setAuthor(author);
			syndEntry.setTitle(article.getTitle());
			syndEntry.setLink(link);
			syndEntry.setPublishedDate(article.getDisplayDate());

			SyndContent syndContent = new SyndContentImpl();

			String value = article.getDescription();

			try {
				value = processContent(
					feed, article, languageId, themeDisplay, syndEntry,
					syndContent);
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(e, e);
				}
			}

			syndContent.setType("html");
			syndContent.setValue(value);

			syndEntry.setDescription(syndContent);

			entries.add(syndEntry);
		}

		try {
			return RSSUtil.export(syndFeed);
		}
		catch (FeedException fe) {
			throw new SystemException(fe);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	protected String getEntryURL(
			JournalFeed feed, JournalArticle article, Layout layout,
			ThemeDisplay themeDisplay)
		throws Exception {

		StringMaker sm = new StringMaker();

		List hitLayoutIds = JournalContentSearchLocalServiceUtil.getLayoutIds(
			layout.getGroupId(), layout.isPrivateLayout(),
			article.getArticleId());

		if (hitLayoutIds.size() > 0) {
			Long hitLayoutId = (Long)hitLayoutIds.get(0);

			Layout hitLayout = LayoutLocalServiceUtil.getLayout(
				layout.getGroupId(), layout.isPrivateLayout(),
				hitLayoutId.longValue());

			return themeDisplay.getURLPortal() +
				PortalUtil.getLayoutURL(hitLayout, themeDisplay);
		}
		else if (Validator.isNotNull(feed.getTargetLayoutFriendlyUrl())) {
			sm.append(themeDisplay.getURLPortal());
			sm.append(feed.getTargetLayoutFriendlyUrl());
		}
		else {
			sm.append(themeDisplay.getURLPortal());
			sm.append(PortalUtil.getLayoutFriendlyURL(layout, themeDisplay));
		}

		sm.append("/journal_content/");

		if (Validator.isNotNull(feed.getTargetPortletId())) {
			sm.append(feed.getTargetPortletId());
		}
		else {
			sm.append(PortletKeys.JOURNAL_CONTENT);
		}

		sm.append(StringPool.SLASH);
		sm.append(article.getGroupId());
		sm.append(StringPool.SLASH);
		sm.append(article.getArticleId());

		return sm.toString();
	}

	protected byte[] getRSS(RenderRequest req) throws Exception {
		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		JournalFeed feed = null;

		long id = ParamUtil.getLong(req, "id");

		long groupId = ParamUtil.getLong(req, "groupId");
		String feedId = ParamUtil.getString(req, "feedId");

		if (id > 0) {
			feed = JournalFeedLocalServiceUtil.getFeed(id);
		}
		else {
			feed = JournalFeedLocalServiceUtil.getFeed(groupId, feedId);
		}

		String languageId = LanguageUtil.getLanguageId(req);

		long plid = PortalUtil.getPlidIdFromFriendlyURL(
			themeDisplay.getCompanyId(), feed.getTargetLayoutFriendlyUrl());

		Layout layout = themeDisplay.getLayout();

		if (plid > 0) {
			try {
				layout = LayoutLocalServiceUtil.getLayout(plid);
			}
			catch (NoSuchLayoutException nsle) {
			}
		}

		String rss = exportToRSS(feed, languageId, layout, themeDisplay);

		return rss.getBytes(StringPool.UTF8);
	}

	protected String processContent(
			JournalFeed feed, JournalArticle article, String languageId,
			ThemeDisplay themeDisplay, SyndEntry syndEntry,
			SyndContent syndContent)
		throws Exception {

		String content = article.getDescription();

		String contentField = feed.getContentField();

		if (contentField.equals(JournalFeedImpl.RENDERED_ARTICLE)) {
			String rendererTemplateId = article.getTemplateId();

			if (Validator.isNotNull(feed.getRendererTemplateId())) {
				rendererTemplateId = feed.getRendererTemplateId();
			}

			JournalArticleDisplay articleDisplay =
				JournalContentUtil.getDisplay(
					feed.getGroupId(), article.getArticleId(),
					rendererTemplateId, languageId, themeDisplay, 1,
					_XML_REQUUEST);

			if (articleDisplay != null) {
				content = articleDisplay.getContent();
			}
		}
		else if (!contentField.equals(JournalFeedImpl.ARTICLE_DESCRIPTION)) {
			Document doc = PortalUtil.readDocumentFromXML(article.getContent());

			XPath xpathSelector = DocumentHelper.createXPath(
				"//dynamic-element[@name='" + contentField + "']");

			List results = xpathSelector.selectNodes(doc);

			if (results.size() == 0) {
				return content;
			}

			Element el = (Element)results.get(0);

			String elType = el.attributeValue("type");

			if (elType.equals("document_library")) {
				String url = el.elementText("dynamic-content");

				url = processURL(feed, url, themeDisplay, syndEntry);
			}
			else if (elType.equals("image") || elType.equals("image_gallery")) {
				String url = el.elementText("dynamic-content");

				url = processURL(feed, url, themeDisplay, syndEntry);

				content =
					content + "<br /><br /><img src='" +
						themeDisplay.getURLPortal() + url + "' />";
			}
			else if (elType.equals("text_box")) {
				syndContent.setType("text");

				content = el.elementText("dynamic-content");
			}
			else {
				content = el.elementText("dynamic-content");
			}
		}

		return content;
	}

	protected String processURL(
		JournalFeed feed, String url, ThemeDisplay themeDisplay,
		SyndEntry syndEntry) {

		url = StringUtil.replace(
			url,
			new String[] {
				"@group_id@",
				"@image_path@",
				"@main_path@"
			},
			new String[] {
				String.valueOf(feed.getGroupId()),
				themeDisplay.getPathImage(),
				themeDisplay.getPathMain()
			}
		);

		List links = JournalRSSUtil.getDLLinks(
			themeDisplay.getURLPortal(), url);
		List enclosures = JournalRSSUtil.getDLEnclosures(
			themeDisplay.getURLPortal(), url);

		syndEntry.setLinks(links);
		syndEntry.setEnclosures(enclosures);

		return url;
	}

	private static final String _XML_REQUUEST =
		"<request><parameters><parameter><name>rss</name><value>true</value>" +
			"</parameter></parameters></request>";

	private static Log _log = LogFactory.getLog(RSSAction.class);

}