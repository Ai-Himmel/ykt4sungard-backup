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

<%@ include file="/html/portlet/blogs/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

long groupId = ParamUtil.getLong(request, "groupId");

String keywords = ParamUtil.getString(request, "keywords");
%>

<liferay-portlet:renderURL varImpl="searchURL"><portlet:param name="struts_action" value="/blogs/search" /></liferay-portlet:renderURL>

<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="searchURL" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />

<liferay-ui:tabs
	names="search"
	backURL="<%= redirect %>"
/>

<%
PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setParameter("struts_action", "/blogs/search");
portletURL.setParameter("keywords", keywords);

List headerNames = new ArrayList();

headerNames.add("#");
headerNames.add("entry");
headerNames.add("score");

SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, LanguageUtil.format(pageContext, "no-entries-were-found-that-matched-the-keywords-x", "<b>" + Html.escape(keywords) + "</b>"));

Hits hits = null;

try {
	hits = BlogsEntryLocalServiceUtil.search(company.getCompanyId(), groupId, 0, keywords);

	Hits results = hits.subset(searchContainer.getStart(), searchContainer.getEnd());
	int total = hits.getLength();

	searchContainer.setTotal(total);

	List resultRows = searchContainer.getResultRows();

	for (int i = 0; i < results.getLength(); i++) {
		Document doc = results.doc(i);

		ResultRow row = new ResultRow(doc, i, i);

		// Position

		row.addText(searchContainer.getStart() + i + 1 + StringPool.PERIOD);

		// Entry

		long entryId = GetterUtil.getLong(doc.get("entryId"));

		BlogsEntry entry = BlogsEntryLocalServiceUtil.getEntry(entryId);

		PortletURL rowURL = renderResponse.createRenderURL();

		rowURL.setParameter("struts_action", "/blogs/view_entry");
		rowURL.setParameter("redirect", currentURL);
		rowURL.setParameter("urlTitle", entry.getUrlTitle());

		row.addText(entry.getTitle(), rowURL);

		// Score

		row.addScore(results.score(i));

		// Add result row

		resultRows.add(row);
	}
%>

	<input id="<portlet:namespace />keywords" name="<portlet:namespace />keywords" size="30" type="text" value="<%= Html.escape(keywords) %>" />

	<input type="submit" value="<liferay-ui:message key="search-entries" />" />

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
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.blogs.search.jsp");
%>