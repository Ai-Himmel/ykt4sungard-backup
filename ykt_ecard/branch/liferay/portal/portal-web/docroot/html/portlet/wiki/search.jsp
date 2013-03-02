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

<%@ include file="/html/portlet/wiki/init.jsp" %>

<liferay-util:include page="/html/portlet/wiki/node_tabs.jsp" />

<%
String redirect = ParamUtil.getString(request, "redirect");

WikiNode node = (WikiNode)request.getAttribute(WebKeys.WIKI_NODE);
WikiPage wikiPage = null;

long nodeId = BeanParamUtil.getLong(node, request, "nodeId");

long[] nodeIds = null;

if (node != null) {
	nodeIds = new long[] {nodeId};
}

String keywords = ParamUtil.getString(request, "keywords");
%>

<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" varImpl="searchURL"><portlet:param name="struts_action" value="/wiki/search" /></liferay-portlet:renderURL>

<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="searchURL" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />nodeId" type="hidden" value="<%= nodeId %>" />

<liferay-ui:tabs
	names="search"
	backURL="<%= redirect %>"
/>

<%
PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/wiki/search");
portletURL.setParameter("nodeId", String.valueOf(nodeId));
portletURL.setParameter("keywords", keywords);

List headerNames = new ArrayList();

headerNames.add("#");
headerNames.add("node");
headerNames.add("page");
headerNames.add("score");

SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, LanguageUtil.format(pageContext, "no-pages-were-found-that-matched-the-keywords-x", "<b>" + Html.escape(keywords) + "</b>"));

Hits hits = null;

try {
	hits = WikiNodeLocalServiceUtil.search(company.getCompanyId(), portletGroupId.longValue(), nodeIds, keywords);

	Hits results = hits.subset(searchContainer.getStart(), searchContainer.getEnd());
	int total = hits.getLength();

	searchContainer.setTotal(total);

	List resultRows = searchContainer.getResultRows();

	for (int i = 0; i < results.getLength(); i++) {
		Document doc = results.doc(i);

		ResultRow row = new ResultRow(doc, i, i);

		// Position

		row.addText(searchContainer.getStart() + i + 1 + StringPool.PERIOD);

		// Node and page

		long curNodeId = GetterUtil.getLong(doc.get("nodeId"));
		String title = doc.get("title");

		WikiNode curNode = WikiNodeLocalServiceUtil.getNode(curNodeId);

		PortletURL rowURL = renderResponse.createRenderURL();

		rowURL.setWindowState(WindowState.MAXIMIZED);

		rowURL.setParameter("struts_action", "/wiki/view");
		rowURL.setParameter("nodeId", String.valueOf(curNodeId));
		rowURL.setParameter("title", title);

		row.addText(curNode.getName(), rowURL);

		row.addText(title, rowURL);

		// Score

		row.addScore(results.score(i));

		// Add result row

		resultRows.add(row);
	}
%>

	<input name="<portlet:namespace />keywords" size="30" type="text" value="<%= Html.escape(keywords) %>" />

	<input type="submit" value="<liferay-ui:message key="search-pages" />" />

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
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.wiki.search.jsp");
%>