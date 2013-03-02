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

<%@ include file="/html/portlet/search/init.jsp" %>

<%
String defaultKeywords = LanguageUtil.get(pageContext, "search") + "...";
String unicodeDefaultKeywords = UnicodeFormatter.toString(defaultKeywords);

String keywords = ParamUtil.getString(request, "keywords", defaultKeywords);

String primarySearch = ParamUtil.getString(request, "primarySearch");

if (Validator.isNotNull(primarySearch)) {
	portalPrefs.setValue(PortletKeys.SEARCH, "primary-search", primarySearch);
}
else {
	primarySearch = portalPrefs.getValue(PortletKeys.SEARCH, "primary-search", StringPool.BLANK);
}
%>

<form action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/search/search" /></portlet:renderURL>" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">

<input name="<portlet:namespace />keywords" size="30" type="text" value="<%= Html.escape(keywords) %>" onBlur="if (this.value == '') { this.value = '<%= unicodeDefaultKeywords %>'; }" onFocus="if (this.value == '<%= unicodeDefaultKeywords %>') { this.value = ''; }" />

<input align="absmiddle" border="0" src="<%= themeDisplay.getPathThemeImages() %>/common/search.png" title="<liferay-ui:message key="search" />" type="image" />

<br /><br />

<%
List portlets = PortletLocalServiceUtil.getPortlets(company.getCompanyId(), false, false);

Iterator itr = portlets.iterator();

while (itr.hasNext()) {
	Portlet portlet = (Portlet)itr.next();

	if (Validator.isNull(portlet.getOpenSearchClass())) {
		itr.remove();
	}
	else {
		OpenSearch openSearch = (OpenSearch)InstancePool.get(portlet.getOpenSearchClass());

		if (!openSearch.isEnabled()) {
			itr.remove();
		}
	}
}

Collections.sort(portlets, new PortletTitleComparator(application, locale));

if (Validator.isNotNull(primarySearch)) {
	for (int i = 0; i < portlets.size(); i++) {
		Portlet portlet = (Portlet)portlets.get(i);

		if (portlet.getOpenSearchClass().equals(primarySearch)) {
			if (i != 0) {
				portlets.remove(i);
				portlets.add(0, portlet);
			}

			break;
		}
	}
}
%>

<input type="button" value="<liferay-ui:message key="add-liferay-as-a-search-provider" />" onClick='window.external.AddSearchProvider("http://localhost:8080/c/search/open_search_description.xml");' />

<br /><br />

<table class="lfr-table" width="100%">

<%
for (int i = 0; i < portlets.size(); i++) {
	Portlet portlet = (Portlet)portlets.get(i);

	OpenSearch openSearch = (OpenSearch)InstancePool.get(portlet.getOpenSearchClass());

	PortletURL portletURL = renderResponse.createRenderURL();

	portletURL.setWindowState(WindowState.MAXIMIZED);

	portletURL.setParameter("struts_action", "/search/search");
	portletURL.setParameter("keywords", keywords);

	List headerNames = new ArrayList();

	headerNames.add("#");
	headerNames.add("summary");
	//headerNames.add("score");

	SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM + i, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, LanguageUtil.format(pageContext, "no-results-were-found-that-matched-the-keywords-x", "<b>" + Html.escape(keywords) + "</b>"));

	if (i > 0) {
		searchContainer.setDelta(5);
	}

	String portletTitle = PortalUtil.getPortletTitle(portlet, application, locale);

	List resultRows = new ArrayList();

	try {
		String xml = openSearch.search(request, keywords, searchContainer.getCurValue(), searchContainer.getDelta());

		SAXReader reader = SAXReaderFactory.getInstance();

		Document doc = reader.read(new StringReader(xml));

		Element root = doc.getRootElement();

		//portletTitle = root.elementText("title");

		List entries = root.elements("entry");

		int total = GetterUtil.getInteger(root.elementText(OpenSearchUtil.getQName("totalResults", OpenSearchUtil.OS_NAMESPACE)));

		searchContainer.setTotal(total);

		resultRows = searchContainer.getResultRows();

		for (int j = 0; j < entries.size(); j++) {
			Element el = (Element)entries.get(j);

			ResultRow row = new ResultRow(doc, String.valueOf(j), j);

			// Position

			row.addText(searchContainer.getStart() + j + 1 + StringPool.PERIOD);

			// Summary

			String entryTitle = el.elementText("title");
			String entryHref = el.element("link").attributeValue("href");
			String summary = el.elementText("summary");

			if (portlet.getPortletId().equals(PortletKeys.DOCUMENT_LIBRARY)) {
				long folderId = GetterUtil.getLong(Http.getParameter(entryHref, "_20_folderId", false));
				String name = GetterUtil.getString(Http.getParameter(entryHref, "_20_name", false));

				DLFileEntry fileEntry = DLFileEntryLocalServiceUtil.getFileEntry(folderId, name);

				entryTitle = fileEntry.getTitle();
			}

			StringMaker sm = new StringMaker();

			sm.append("<a href=\"");
			sm.append(entryHref);
			sm.append("\"");

			if (portlet.getPortletId().equals(PortletKeys.JOURNAL)) {
				sm.append(" target=\"_blank\"");
			}

			sm.append(">");
			sm.append("<span style=\"font-size: x-small; font-style: italic;\">");
			sm.append(entryTitle);
			sm.append("</span><br />");
			sm.append(summary);
			sm.append("</a>");

			row.addText(StringUtil.highlight(sm.toString(), keywords));

			// Score

			String score = el.elementText(OpenSearchUtil.getQName("score", OpenSearchUtil.RELEVANCE_NAMESPACE));

			//row.addText(score);

			// Add result row

			resultRows.add(row);
		}
	}
	catch (Exception e) {
		_log.error(portlet.getOpenSearchClass() + " " + e.getMessage());
	}
%>

	<c:choose>
		<c:when test="<%= (i == 0) && (portlets.size() == 1) %>">
			<tr>
				<td valign="top" width="100%">
		</c:when>
		<c:when test="<%= (i == 0) && (portlets.size() > 1) %>">
			<tr>
				<td valign="top" width="70%">
		</c:when>
		<c:when test="<%= i == 1 %>">
			<td valign="top" width="30%">
		</c:when>
	</c:choose>

	<c:if test="<%= i > 1 %>">
		<br />
	</c:if>

	<div style="padding-bottom: 5px;">
		<b><%= portletTitle %></b>
	</div>

	<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" paginate="<%= false %>" />

	<c:choose>
		<c:when test="<%= i == 0 %>">
			<div class="taglib-search-iterator-page-iterator-bottom">
				<liferay-ui:search-paginator searchContainer="<%= searchContainer %>" />
			</div>
		</c:when>
		<c:otherwise>
			<div style="padding-top: 5px;">
				<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/search/search" /><portlet:param name="primarySearch" value="<%= portlet.getOpenSearchClass() %>" /><portlet:param name="keywords" value="<%= Html.escape(keywords) %>" /></portlet:renderURL>"><liferay-ui:message key="more" /> &raquo;</a>
			</div>
		</c:otherwise>
	</c:choose>

	<c:choose>
		<c:when test="<%= (i == 0) && (portlets.size() == 1) %>">
			</td>
		</c:when>
		<c:when test="<%= (i == 0) && (portlets.size() > 1) %>">
			</td>
		</c:when>
		<c:when test="<%= (i + 1) == portlets.size() %>">
				</td>
			</tr>
		</c:when>
	</c:choose>

<%
}
%>

</table>

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />keywords);
	</script>
</c:if>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.search.search.jsp");
%>