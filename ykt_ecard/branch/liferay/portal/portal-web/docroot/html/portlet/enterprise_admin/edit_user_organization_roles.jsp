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

List userOrganizations = user2.getOrganizations();

SearchContainer searchContainer = new SearchContainer();

List headerNames = new ArrayList();

headerNames.add("name");
headerNames.add("organization");

if (user2.getUserId() != user.getUserId()) {
	headerNames.add(StringPool.BLANK);
}

searchContainer.setHeaderNames(headerNames);

if (user2.getUserId() == user.getUserId()) {
	searchContainer.setEmptyResultsMessage("you-do-not-have-any-organization-roles");
}
else {
	searchContainer.setEmptyResultsMessage("the-user-does-not-have-any-organization-roles");
}

List results = new ArrayList();
List resultRows = searchContainer.getResultRows();

for (int i = 0; i < userOrganizations.size(); i++) {
	Organization organization = (Organization)userOrganizations.get(i);

	Group group = organization.getGroup();

	List userGroupRoles = UserGroupRoleLocalServiceUtil.getUserGroupRoles(user2.getUserId(), group.getGroupId());

	for (int j = 0; j < userGroupRoles.size(); j++) {
		UserGroupRole userGroupRole = (UserGroupRole)userGroupRoles.get(j);

		Role role = RoleLocalServiceUtil.getRole(userGroupRole.getRoleId());

		ResultRow row = new ResultRow(new Object[] {user2, group, role, currentURL + sectionRedirectParams}, role.getRoleId(), j);

		// Name

		row.addText(role.getName());

		// Organization

		row.addText(organization.getName());

		// Action

		if (user2.getUserId() != user.getUserId()) {
			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/enterprise_admin/user_group_role_action.jsp");
		}

		// Add result row

		resultRows.add(row);
		results.add(userGroupRole);
	}
}

searchContainer.setTotal(results.size());
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" paginate="<%= false %>" />

<br />