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

<%@ include file="/html/portlet/tagged_content/init.jsp" %>

<%
if (mergeUrlTags) {
	String[] compilerEntries = (String[])request.getAttribute(WebKeys.TAGS_COMPILER_ENTRIES);

	String titleEntry = null;

	if ((compilerEntries != null) && (compilerEntries.length > 0)) {
		String[] newEntries = ArrayUtil.append(entries, compilerEntries);

		entries = newEntries;

		titleEntry = compilerEntries[compilerEntries.length - 1];
	}

	String portletTitle = portletDisplay.getTitle();

	portletTitle = TagsUtil.substitutePropertyVariables(company.getCompanyId(), titleEntry, portletTitle);

	renderResponse.setTitle(portletTitle);
}

entries = ArrayUtil.distinct(entries, new StringComparator());
%>

<form name="<portlet:namespace/>fm">

	<%
	String portletId = portletDisplay.getId();
	%>

	<%@ include file="/html/portlet/tagged_content/add_asset.jspf" %>
</form>

<br />

<%
if (showQueryLogic) {
	StringMaker tagsText = new StringMaker();

	if (entries.length > 0) {
		tagsText.append("( ");
	}

	for (int i = 0; i < entries.length; i++) {
		if ((i + 1) == entries.length) {
			tagsText.append(entries[i]);
			tagsText.append(" )");
		}
		else {
			tagsText.append(entries[i]);

			if (andOperator) {
				tagsText.append(" AND ");
			}
			else {
				tagsText.append(" OR ");
			}
		}
	}

	if (entries.length > 0 && notEntries.length > 0) {
		tagsText.append(" AND NOT ( ");
	}

	for (int i = 0; i < notEntries.length; i++) {
		if ((i + 1) == notEntries.length) {
			tagsText.append(notEntries[i]);
			tagsText.append(" )");
		}
		else {
			tagsText.append(notEntries[i]);
			tagsText.append(" OR ");
		}
	}
%>

	<liferay-ui:message key="tags" />:

	<%= tagsText %>

	<div class="separator"><!-- --></div>

<%
}

// Display content

PortletURL portletURL = renderResponse.createRenderURL();

SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, delta, portletURL, null, null);
%>

<c:choose>
	<c:when test='<%= selectionStyle.equals("dynamic") && Validator.isNotNull(category)%>'>
		<%@ include file="/html/portlet/tagged_content/view_dynamic_by_category.jspf" %>
	</c:when>
	<c:when test='<%= selectionStyle.equals("dynamic") && Validator.isNull(category) %>'>
		<%@ include file="/html/portlet/tagged_content/view_dynamic_list.jspf" %>
	</c:when>
	<c:when test='<%= selectionStyle.equals("manual") %>'>
		<%@ include file="/html/portlet/tagged_content/view_manual.jspf" %>
	</c:when>
</c:choose>

<c:if test='<%= !paginationType.equals("none") && (searchContainer.getTotal() > searchContainer.getResults().size()) %>'>
	<liferay-ui:search-paginator searchContainer="<%= searchContainer %>"  type="<%= paginationType %>"/>
</c:if>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.tagged_content.view.jsp");
%>