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
User user2 = (User)request.getAttribute("edit_user.jsp-user2");

String sectionRedirectParams = (String)request.getAttribute("edit_user.jsp-sectionRedirectParams");

SearchContainer searchContainer = new SearchContainer();

List headerNames = new ArrayList();

headerNames.add("name");

if (user2.getUserId() != user.getUserId()) {
	headerNames.add(StringPool.BLANK);
}

searchContainer.setHeaderNames(headerNames);

if (user2.getUserId() == user.getUserId()) {
	searchContainer.setEmptyResultsMessage("you-do-not-have-any-regular-roles");
}
else {
	searchContainer.setEmptyResultsMessage("the-user-does-not-have-any-regular-roles");
}

List results = RoleLocalServiceUtil.getUserRoles(user2.getUserId());
List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	Role role = (Role)results.get(i);

	ResultRow row = new ResultRow(new Object[] {user2, role, currentURL + sectionRedirectParams}, role.getRoleId(), i);

	// Name

	row.addText(role.getName());

	// Action

	if (user2.getUserId() != user.getUserId()) {
		row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/enterprise_admin/user_role_action.jsp");
	}

	// Add result row

	resultRows.add(row);
}

searchContainer.setTotal(results.size());
%>

<c:if test="<%= portletName.equals(PortletKeys.ENTERPRISE_ADMIN) || portletName.equals(PortletKeys.ORGANIZATION_ADMIN) %>">
	<input onclick="javascript: self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_user_regular_role_assignments" /><portlet:param name="redirect" value='<%= currentURL + "&" + renderResponse.getNamespace() + "tabs2=regular-roles" %>' /><portlet:param name="p_u_i_d" value="<%= String.valueOf(user2.getUserId()) %>" /></portlet:renderURL>';" type="button" value="<liferay-ui:message key="assign-regular-roles" />" />

	<br /><br />
</c:if>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" paginate="<%= false %>" />

<br />