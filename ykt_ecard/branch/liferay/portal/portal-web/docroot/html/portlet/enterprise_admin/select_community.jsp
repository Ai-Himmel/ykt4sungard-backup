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

<%@ include file="/html/portlet/enterprise_admin/init.jsp" %>

<script type="text/javascript">
	var <portlet:namespace />selectedCommunities = [];

	function <portlet:namespace />selectGroup(groupId, name, target) {
		opener.<portlet:namespace />selectGroup(groupId, name, target);

		<portlet:namespace />selectedCommunities[<portlet:namespace />selectedCommunities.length] = name;

		var selectedCommunities = document.getElementById('<portlet:namespace />selectedCommunitiesDiv')

		selectedCommunities.innerHTML = '<bean:message key="selected"/>: <b>' + <portlet:namespace />selectedCommunities.join(', ') + '</b><br/><br/>';
	}
</script>

<form method="post" name="<portlet:namespace />fm">

<liferay-ui:tabs names="communities" />

<liferay-ui:message key="please-select-at-least-one-community" />

<br /><br />

<%
String target = ParamUtil.getString(request, "target");

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(LiferayWindowState.POP_UP);

portletURL.setParameter("struts_action", "/enterprise_admin/select_community");

GroupSearch searchContainer = new GroupSearch(renderRequest, portletURL);

List headerNames = new ArrayList();

headerNames.add("name");
headerNames.add("type");
headerNames.add("members");

searchContainer.setHeaderNames(headerNames);
%>

<liferay-ui:search-form
	page="/html/portlet/enterprise_admin/group_search.jsp"
	searchContainer="<%= searchContainer %>"
/>

<%
GroupSearchTerms searchTerms = (GroupSearchTerms)searchContainer.getSearchTerms();

LinkedHashMap groupParams = new LinkedHashMap();

int total = GroupLocalServiceUtil.searchCount(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), groupParams);

searchContainer.setTotal(total);

List results = GroupLocalServiceUtil.search(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), groupParams, searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());

searchContainer.setResults(results);
%>

<div class="separator"><!-- --></div>

<div id="<portlet:namespace/>selectedCommunitiesDiv"></div>

<%
List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	Group group = (Group)results.get(i);

	group = group.toEscapedModel();

	ResultRow row = new ResultRow(group, group.getGroupId(), i);

	StringMaker sm = new StringMaker();

	sm.append("javascript: ");
	sm.append(renderResponse.getNamespace());
	sm.append("selectGroup('");
	sm.append(group.getGroupId());
	sm.append("', '");
	sm.append(UnicodeFormatter.toString(group.getName()));
	sm.append("', '");
	sm.append(target);
	sm.append("');");

	String rowHREF = sm.toString();

	// Name

	row.addText(group.getName(), rowHREF);

	// Type

	row.addText(LanguageUtil.get(pageContext, group.getTypeLabel()), rowHREF);

	// Members

	LinkedHashMap userParams = new LinkedHashMap();

	userParams.put("usersGroups", new Long(group.getGroupId()));

	int membersCount = UserLocalServiceUtil.searchCount(company.getCompanyId(), null, Boolean.TRUE, userParams);

	row.addText(String.valueOf(membersCount));

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

<br/>

<input onclick="window.close();" type="button" value="<liferay-ui:message key="close"/>" />

</form>

<script type="text/javascript">
	Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />name);
</script>