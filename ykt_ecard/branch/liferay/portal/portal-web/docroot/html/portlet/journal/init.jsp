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

<%@ page import="com.liferay.portlet.documentlibrary.util.DLUtil" %>
<%@ page import="com.liferay.portlet.journal.ArticleContentException" %>
<%@ page import="com.liferay.portlet.journal.ArticleDisplayDateException" %>
<%@ page import="com.liferay.portlet.journal.ArticleExpirationDateException" %>
<%@ page import="com.liferay.portlet.journal.ArticleIdException" %>
<%@ page import="com.liferay.portlet.journal.ArticleSmallImageNameException" %>
<%@ page import="com.liferay.portlet.journal.ArticleSmallImageSizeException" %>
<%@ page import="com.liferay.portlet.journal.ArticleTitleException" %>
<%@ page import="com.liferay.portlet.journal.ArticleTypeException" %>
<%@ page import="com.liferay.portlet.journal.DuplicateArticleIdException" %>
<%@ page import="com.liferay.portlet.journal.DuplicateFeedIdException" %>
<%@ page import="com.liferay.portlet.journal.DuplicateStructureIdException" %>
<%@ page import="com.liferay.portlet.journal.DuplicateTemplateIdException" %>
<%@ page import="com.liferay.portlet.journal.FeedContentFieldException" %>
<%@ page import="com.liferay.portlet.journal.FeedDescriptionException" %>
<%@ page import="com.liferay.portlet.journal.FeedIdException" %>
<%@ page import="com.liferay.portlet.journal.FeedNameException" %>
<%@ page import="com.liferay.portlet.journal.FeedTargetLayoutFriendlyUrlException" %>
<%@ page import="com.liferay.portlet.journal.FeedTargetPortletIdException" %>
<%@ page import="com.liferay.portlet.journal.NoSuchArticleException" %>
<%@ page import="com.liferay.portlet.journal.NoSuchStructureException" %>
<%@ page import="com.liferay.portlet.journal.NoSuchTemplateException" %>
<%@ page import="com.liferay.portlet.journal.RequiredStructureException" %>
<%@ page import="com.liferay.portlet.journal.RequiredTemplateException" %>
<%@ page import="com.liferay.portlet.journal.StructureDescriptionException" %>
<%@ page import="com.liferay.portlet.journal.StructureIdException" %>
<%@ page import="com.liferay.portlet.journal.StructureNameException" %>
<%@ page import="com.liferay.portlet.journal.StructureXsdException" %>
<%@ page import="com.liferay.portlet.journal.TemplateDescriptionException" %>
<%@ page import="com.liferay.portlet.journal.TemplateIdException" %>
<%@ page import="com.liferay.portlet.journal.TemplateNameException" %>
<%@ page import="com.liferay.portlet.journal.TemplateSmallImageNameException" %>
<%@ page import="com.liferay.portlet.journal.TemplateSmallImageSizeException" %>
<%@ page import="com.liferay.portlet.journal.TemplateXslException" %>
<%@ page import="com.liferay.portlet.journal.action.EditArticleAction" %>
<%@ page import="com.liferay.portlet.journal.model.JournalArticle" %>
<%@ page import="com.liferay.portlet.journal.model.JournalFeed" %>
<%@ page import="com.liferay.portlet.journal.model.JournalStructure" %>
<%@ page import="com.liferay.portlet.journal.model.JournalTemplate" %>
<%@ page import="com.liferay.portlet.journal.model.impl.JournalArticleImpl" %>
<%@ page import="com.liferay.portlet.journal.model.impl.JournalFeedImpl" %>
<%@ page import="com.liferay.portlet.journal.model.impl.JournalTemplateImpl" %>
<%@ page import="com.liferay.portlet.journal.search.ArticleDisplayTerms" %>
<%@ page import="com.liferay.portlet.journal.search.ArticleSearch" %>
<%@ page import="com.liferay.portlet.journal.search.ArticleSearchTerms" %>
<%@ page import="com.liferay.portlet.journal.search.FeedDisplayTerms" %>
<%@ page import="com.liferay.portlet.journal.search.FeedSearch" %>
<%@ page import="com.liferay.portlet.journal.search.FeedSearchTerms" %>
<%@ page import="com.liferay.portlet.journal.search.StructureDisplayTerms" %>
<%@ page import="com.liferay.portlet.journal.search.StructureSearch" %>
<%@ page import="com.liferay.portlet.journal.search.StructureSearchTerms" %>
<%@ page import="com.liferay.portlet.journal.search.TemplateDisplayTerms" %>
<%@ page import="com.liferay.portlet.journal.search.TemplateSearch" %>
<%@ page import="com.liferay.portlet.journal.search.TemplateSearchTerms" %>
<%@ page import="com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.journal.service.JournalFeedLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.journal.service.JournalStructureLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.journal.service.JournalTemplateLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.journal.service.permission.JournalArticlePermission" %>
<%@ page import="com.liferay.portlet.journal.service.permission.JournalFeedPermission" %>
<%@ page import="com.liferay.portlet.journal.service.permission.JournalStructurePermission" %>
<%@ page import="com.liferay.portlet.journal.service.permission.JournalTemplatePermission" %>
<%@ page import="com.liferay.portlet.journal.util.JournalUtil" %>

<%@ page import="com.liferay.util.RSSUtil" %>

<%@ page import="org.dom4j.Document" %>
<%@ page import="org.dom4j.DocumentFactory" %>
<%@ page import="org.dom4j.DocumentHelper" %>
<%@ page import="org.dom4j.Element" %>
<%@ page import="org.dom4j.XPath" %>
<%@ page import="org.dom4j.io.SAXReader" %>

<%
PortalPreferences portalPrefs = PortletPreferencesFactoryUtil.getPortalPreferences(request);

DateFormat dateFormatDate = DateFormats.getDate(locale, timeZone);
%>