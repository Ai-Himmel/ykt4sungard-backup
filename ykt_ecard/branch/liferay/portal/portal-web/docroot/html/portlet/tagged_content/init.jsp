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

<%@ page import="com.liferay.portal.kernel.dao.search.ResultRow" %>
<%@ page import="com.liferay.portal.kernel.search.Hits" %>
<%@ page import="com.liferay.portlet.PortalPreferences" %>
<%@ page import="com.liferay.portlet.blogs.model.BlogsEntry" %>
<%@ page import="com.liferay.portlet.blogs.service.BlogsEntryLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.blogs.service.permission.BlogsEntryPermission" %>
<%@ page import="com.liferay.portlet.bookmarks.model.BookmarksEntry" %>
<%@ page import="com.liferay.portlet.bookmarks.model.BookmarksFolder" %>
<%@ page import="com.liferay.portlet.bookmarks.model.impl.BookmarksFolderImpl" %>
<%@ page import="com.liferay.portlet.bookmarks.service.BookmarksEntryLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.bookmarks.service.BookmarksFolderLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.bookmarks.service.permission.BookmarksEntryPermission" %>
<%@ page import="com.liferay.portlet.bookmarks.service.permission.BookmarksFolderPermission" %>
<%@ page import="com.liferay.portlet.bookmarks.util.BookmarksUtil" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.DLFileEntry" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.DLFolder" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.impl.DLFileEntryImpl" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl" %>
<%@ page import="com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.documentlibrary.service.permission.DLFileEntryPermission" %>
<%@ page import="com.liferay.portlet.documentlibrary.util.DLUtil" %>
<%@ page import="com.liferay.portlet.imagegallery.model.IGFolder" %>
<%@ page import="com.liferay.portlet.imagegallery.model.IGImage" %>
<%@ page import="com.liferay.portlet.imagegallery.model.impl.IGFolderImpl" %>
<%@ page import="com.liferay.portlet.imagegallery.service.IGFolderLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.imagegallery.service.IGImageLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.imagegallery.service.permission.IGImagePermission" %>
<%@ page import="com.liferay.portlet.journalcontent.util.JournalContentUtil"%>
<%@ page import="com.liferay.portlet.journal.NoSuchArticleException" %>
<%@ page import="com.liferay.portlet.journal.action.EditArticleAction" %>
<%@ page import="com.liferay.portlet.journal.model.JournalArticle" %>
<%@ page import="com.liferay.portlet.journal.model.JournalArticleDisplay" %>
<%@ page import="com.liferay.portlet.journal.model.JournalArticleResource" %>
<%@ page import="com.liferay.portlet.journal.model.impl.JournalArticleImpl" %>
<%@ page import="com.liferay.portlet.journal.search.ArticleDisplayTerms" %>
<%@ page import="com.liferay.portlet.journal.search.ArticleSearch" %>
<%@ page import="com.liferay.portlet.journal.search.ArticleSearchTerms" %>
<%@ page import="com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.journal.service.permission.JournalArticlePermission" %>
<%@ page import="com.liferay.portlet.messageboards.model.MBMessage" %>
<%@ page import="com.liferay.portlet.messageboards.service.MBMessageLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.taggedcontent.util.AssetPublisherUtil" %>
<%@ page import="com.liferay.portlet.tags.NoSuchEntryException" %>
<%@ page import="com.liferay.portlet.tags.NoSuchPropertyException" %>
<%@ page import="com.liferay.portlet.tags.model.TagsAsset" %>
<%@ page import="com.liferay.portlet.tags.model.TagsAssetType" %>
<%@ page import="com.liferay.portlet.tags.model.TagsEntry" %>
<%@ page import="com.liferay.portlet.tags.model.TagsProperty" %>
<%@ page import="com.liferay.portlet.tags.service.TagsAssetLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.tags.service.TagsAssetServiceUtil" %>
<%@ page import="com.liferay.portlet.tags.service.TagsEntryLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.tags.service.TagsPropertyLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.tags.util.TagsUtil" %>
<%@ page import="com.liferay.portlet.wiki.model.WikiNode" %>
<%@ page import="com.liferay.portlet.wiki.model.WikiPage" %>
<%@ page import="com.liferay.portlet.wiki.model.WikiPageResource" %>
<%@ page import="com.liferay.portlet.wiki.model.impl.WikiPageImpl" %>
<%@ page import="com.liferay.portlet.wiki.service.WikiPageLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.wiki.service.WikiPageResourceLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.wiki.service.permission.WikiPagePermission" %>
<%@ page import="com.liferay.portlet.wiki.util.WikiUtil" %>
<%@ page import="com.liferay.util.xml.DocUtil" %>

<%@ page import="org.dom4j.io.SAXReader" %>
<%@ page import="org.dom4j.Document" %>
<%@ page import="org.dom4j.Element" %>

<%@ page import="java.io.StringReader" %>

<%
PortletPreferences prefs = renderRequest.getPreferences();

String portletResource = ParamUtil.getString(request, "portletResource");

if (Validator.isNotNull(portletResource)) {
	prefs = PortletPreferencesFactoryUtil.getPortletSetup(request, portletResource, true, true);
}

String selectionStyle = prefs.getValue("selection-style", null);

if (Validator.isNull(selectionStyle)) {
	selectionStyle = "dynamic";
}

long classNameId = GetterUtil.getLong(prefs.getValue("class-name-id", StringPool.BLANK));
long[] classNameIds = null;

if (classNameId > 0) {
	classNameIds = new long[] {classNameId};
}
else {
	classNameIds = new long[0];
}

String category = GetterUtil.getString(prefs.getValue("category", StringPool.BLANK));
String[] entries = prefs.getValues("entries", new String[0]);
String[] notEntries = prefs.getValues("not-entries", new String[0]);
boolean mergeUrlTags = GetterUtil.getBoolean(prefs.getValue("merge-url-tags", null), true);
boolean andOperator = GetterUtil.getBoolean(prefs.getValue("and-operator", null), false);

String displayStyle = GetterUtil.getString(prefs.getValue("display-style", "abstracts"));

if (Validator.isNull(displayStyle)) {
	displayStyle = "abstracts";
}

String orderByColumn1 = GetterUtil.getString(prefs.getValue("order-by-column-1", "modifiedDate"));
String orderByColumn2 = GetterUtil.getString(prefs.getValue("order-by-column-2", "title"));
String orderByType1 = GetterUtil.getString(prefs.getValue("order-by-type-1", "DESC"));
String orderByType2 = GetterUtil.getString(prefs.getValue("order-by-type-2", "ASC"));
boolean excludeZeroViewCount = GetterUtil.getBoolean(prefs.getValue("exclude-zero-view-count", "0"));
int delta = GetterUtil.getInteger(prefs.getValue("delta", StringPool.BLANK), SearchContainer.DEFAULT_DELTA);
String paginationType = GetterUtil.getString(prefs.getValue("pagination-type", "none"));
boolean showQueryLogic = GetterUtil.getBoolean(prefs.getValue("show-query-logic", StringPool.BLANK));
boolean showAvailableLocales = GetterUtil.getBoolean(prefs.getValue("show-available-locales", StringPool.BLANK));
boolean enableRatings = GetterUtil.getBoolean(prefs.getValue("enable-ratings", null));
boolean enableComments = GetterUtil.getBoolean(prefs.getValue("enable-comments", null));

String defaultMetadataFields = "";
String allMetadataFields = "create-date,modified-date,publish-date,expiration-date,priority,author,view-count";

String[] metadataFields = StringUtil.split(PrefsParamUtil.getString(prefs, request, "metadata-fields", defaultMetadataFields));

Arrays.sort(entries);

String[] manualEntries = prefs.getValues("manual-entries", new String[0]);

DateFormat dateFormatDate = DateFormats.getDate(locale, timeZone);
%>