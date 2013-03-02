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

<%
String tabs2 = ParamUtil.getString(request, "tabs2", "current");

String cur = ParamUtil.getString(request, "cur");

String redirect = ParamUtil.getString(request, "redirect");

User user2 = PortalUtil.getSelectedUser(request);

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/enterprise_admin/edit_user_regular_role_assignments");
portletURL.setParameter("redirect", redirect);
portletURL.setParameter("tabs2", tabs2);
portletURL.setParameter("p_u_i_d", String.valueOf(user2.getUserId()));
%>

<script type="text/javascript">
	function <portlet:namespace />updateUserRoles(redirect) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "user_roles";
		document.<portlet:namespace />fm.<portlet:namespace />redirect.value = redirect;
		document.<portlet:namespace />fm.<portlet:namespace />addRoleIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		document.<portlet:namespace />fm.<portlet:namespace />removeRoleIds.value = Liferay.Util.listUncheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_user_regular_role_assignments" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />p_u_i_d" type="hidden" value="<%= user2.getUserId() %>" />
<input name="<portlet:namespace />addRoleIds" type="hidden" value="" />
<input name="<portlet:namespace />removeRoleIds" type="hidden" value="" />

<liferay-ui:tabs
	names="assign-regular-roles"
	backURL="<%= redirect %>"
/>

<liferay-ui:tabs
	names="current,available"
	param="tabs2"
	url="<%= portletURL.toString() %>"
/>

<%
RoleSearch searchContainer = new RoleSearch(renderRequest, portletURL);
%>

<liferay-ui:search-form
	page="/html/portlet/enterprise_admin/role_search.jsp"
	searchContainer="<%= searchContainer %>"
/>

<%
RoleSearchTerms searchTerms = (RoleSearchTerms)searchContainer.getSearchTerms();

searchContainer.setRowChecker(new RoleUserChecker(renderResponse, user2));

LinkedHashMap roleParams = new LinkedHashMap();

if (tabs2.equals("current")) {
	roleParams.put("usersRoles", new Long(user2.getUserId()));
}

List results = RoleLocalServiceUtil.search(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), new Integer(RoleImpl.TYPE_REGULAR), roleParams, searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());

Iterator itr = results.iterator();

while (itr.hasNext()) {
	Role role = (Role)itr.next();

	if (!RolePermissionUtil.contains(permissionChecker, role.getRoleId(), ActionKeys.ASSIGN_MEMBERS)) {
		itr.remove();
	}
}

searchContainer.setResults(results);
searchContainer.setTotal(results.size());
%>

<div class="separator"><!-- --></div>

<input type="button" value="<liferay-ui:message key="update-associations" />" onClick="<portlet:namespace />updateUserRoles('<%= portletURL.toString() %>&<portlet:namespace />cur=<%= cur %>');" />

<br /><br />

<%
List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	Role role = (Role)results.get(i);

	ResultRow row = new ResultRow(role, role.getRoleId(), i);

	PortletURL rowURL = renderResponse.createRenderURL();

	rowURL.setWindowState(WindowState.MAXIMIZED);

	rowURL.setParameter("struts_action", "/enterprise_admin/edit_role");
	rowURL.setParameter("redirect", currentURL);
	rowURL.setParameter("roleId", String.valueOf(role.getRoleId()));

	// Name

	row.addText(role.getName(), rowURL);

	// Type

	row.addText(LanguageUtil.get(pageContext, role.getTypeLabel()), rowURL);

	// Description

	row.addText(role.getDescription(), rowURL);

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

</form>