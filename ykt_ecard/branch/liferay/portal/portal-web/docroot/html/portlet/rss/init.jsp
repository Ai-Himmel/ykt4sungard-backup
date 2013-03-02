<%
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
%>

<%@ include file="/html/portlet/init.jsp" %>


<%@ page import="com.liferay.portlet.journal.action.EditArticleAction" %>
<%@ page import="com.liferay.portlet.journal.model.JournalArticle" %>
<%@ page import="com.liferay.portlet.journal.search.ArticleSearch" %>
<%@ page import="com.liferay.portlet.journal.search.ArticleSearchTerms" %>
<%@ page import="com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.rss.util.RSSUtil" %>

<%@ page import="com.sun.syndication.feed.synd.SyndContent" %>
<%@ page import="com.sun.syndication.feed.synd.SyndEntry" %>
<%@ page import="com.sun.syndication.feed.synd.SyndFeed" %>
<%@ page import="com.sun.syndication.feed.synd.SyndImage"%>

<%
PortletPreferences prefs = renderRequest.getPreferences();

String portletResource = ParamUtil.getString(request, "portletResource");

if (Validator.isNotNull(portletResource)) {
	prefs = PortletPreferencesFactoryUtil.getPortletSetup(request, portletResource, true, true);
}

String[] urls = prefs.getValues("urls", new String[0]);
String[] titles = prefs.getValues("titles", new String[0]);
int entriesPerFeed = GetterUtil.getInteger(prefs.getValue("items-per-channel", "8"));
boolean showFeedTitle = GetterUtil.getBoolean(prefs.getValue("show-feed-title", Boolean.TRUE.toString()));
boolean showFeedPublishedDate = GetterUtil.getBoolean(prefs.getValue("show-feed-published-date", Boolean.TRUE.toString()));
boolean showFeedDescription = GetterUtil.getBoolean(prefs.getValue("show-feed-description", Boolean.TRUE.toString()));
boolean showFeedImage = GetterUtil.getBoolean(prefs.getValue("show-feed-image", Boolean.TRUE.toString()));
String feedImageAlignment = prefs.getValue("feed-image-alignment", "right");

String[] headerArticleResouceValues = prefs.getValues("header-article-resouce-values", new String[] {"0", ""});

long headerArticleResouceId = GetterUtil.getLong(headerArticleResouceValues[0]);
String headerArticleResouceTitle = headerArticleResouceValues[1];

String[] footerArticleResouceValues = prefs.getValues("footer-article-resouce-values", new String[] {"0", ""});

long footerArticleResouceId = GetterUtil.getLong(footerArticleResouceValues[0]);
String footerArticleResouceTitle = footerArticleResouceValues[1];

DateFormat dateFormatDateTime = DateFormats.getDateTime(locale, timeZone);
DateFormat dateFormatDate = DateFormats.getDate(locale, timeZone);
%>