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

<%@ include file="/html/portlet/message_boards/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

long breadcrumbsCategoryId = ParamUtil.getLong(request, "breadcrumbsCategoryId");
long breadcrumbsMessageId = ParamUtil.getLong(request, "breadcrumbsMessageId");

long searchCategoryId = ParamUtil.getLong(request, "searchCategoryId");
long searchCategoryIds = ParamUtil.getLong(request, "searchCategoryIds");

long[] categoryIdsArray = null;

if (searchCategoryId > 0) {
	categoryIdsArray = new long[] {searchCategoryId};
}
else {
	List categoryIds = new ArrayList();

	categoryIds.add(new Long(searchCategoryIds));

	MBCategoryLocalServiceUtil.getSubcategoryIds(categoryIds, portletGroupId.longValue(), searchCategoryIds);

	categoryIdsArray = StringUtil.split(StringUtil.merge(categoryIds), 0L);
}

long threadId = ParamUtil.getLong(request, "threadId");
String keywords = ParamUtil.getString(request, "keywords");
%>

<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" varImpl="searchURL"><portlet:param name="struts_action" value="/message_boards/search" /></liferay-portlet:renderURL>

<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="searchURL" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />breadcrumbsCategoryId" type="hidden" value="<%= breadcrumbsCategoryId %>" />
<input name="<portlet:namespace />breadcrumbsMessageId" type="hidden" value="<%= breadcrumbsMessageId %>" />
<input name="<portlet:namespace />searchCategoryId" type="hidden" value="<%= searchCategoryId %>" />
<input name="<portlet:namespace />searchCategoryIds" type="hidden" value="<%= searchCategoryIds %>" />
<input name="<portlet:namespace />threadId" type="hidden" value="<%= threadId %>" />

<liferay-ui:tabs
	names="search"
	backURL="<%= redirect %>"
/>

<%
PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/message_boards/search");
portletURL.setParameter("breadcrumbsCategoryId", String.valueOf(breadcrumbsCategoryId));
portletURL.setParameter("breadcrumbsMessageId", String.valueOf(breadcrumbsMessageId));
portletURL.setParameter("searchCategoryId", String.valueOf(searchCategoryId));
portletURL.setParameter("searchCategoryIds", String.valueOf(searchCategoryIds));
portletURL.setParameter("threadId", String.valueOf(threadId));
portletURL.setParameter("keywords", keywords);

List headerNames = new ArrayList();

headerNames.add("#");
headerNames.add("category");
headerNames.add("message");
headerNames.add("thread-posts");
headerNames.add("thread-views");
headerNames.add("score");

SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, LanguageUtil.format(pageContext, "no-messages-were-found-that-matched-the-keywords-x", "<b>" + Html.escape(keywords) + "</b>"));

Hits hits = null;

try {
	hits = MBCategoryLocalServiceUtil.search(company.getCompanyId(), portletGroupId.longValue(), categoryIdsArray, threadId, keywords);

	ThreadHits threadHits = new ThreadHits();

	threadHits.recordHits(hits);

	hits = threadHits;

	Hits results = hits.subset(searchContainer.getStart(), searchContainer.getEnd());
	int total = hits.getLength();

	searchContainer.setTotal(total);

	List resultRows = searchContainer.getResultRows();

	for (int i = 0; i < results.getLength(); i++) {
		Document doc = results.doc(i);

		ResultRow row = new ResultRow(doc, i, i);

		// Position

		row.addText(searchContainer.getStart() + i + 1 + StringPool.PERIOD);

		// Category, thread, and message

		long categoryId = GetterUtil.getLong(doc.get("categoryId"));
		long curThreadId = GetterUtil.getLong(doc.get("threadId"));
		long messageId = GetterUtil.getLong(doc.get("messageId"));

		MBCategory category = MBCategoryLocalServiceUtil.getCategory(categoryId);
		MBThread thread = MBThreadLocalServiceUtil.getThread(curThreadId);
		MBMessage message = MBMessageLocalServiceUtil.getMessage(messageId);

		PortletURL rowURL = renderResponse.createRenderURL();

		rowURL.setWindowState(WindowState.MAXIMIZED);

		rowURL.setParameter("struts_action", "/message_boards/view_message");
		rowURL.setParameter("redirect", currentURL);
		rowURL.setParameter("messageId", String.valueOf(messageId));

		row.addText(category.getName(), rowURL);
		row.addText(message.getSubject(), rowURL);
		row.addText(String.valueOf(thread.getMessageCount()), rowURL);
		row.addText(String.valueOf(thread.getViewCount()), rowURL);

		// Score

		row.addScore(results.score(i));

		// Add result row

		resultRows.add(row);
	}
%>

	<input name="<portlet:namespace />keywords" size="30" type="text" value="<%= Html.escape(keywords) %>" />

	<input type="submit" value="<liferay-ui:message key="search-messages" />" />

	<br /><br />

	<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

<%
}
catch (Exception e) {
	_log.error(e.getMessage());
}
finally {
	if (hits != null) {
		hits.closeSearcher();
	}
}
%>


</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />keywords);
	</script>
</c:if>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.message_boards.search.jsp");
%>