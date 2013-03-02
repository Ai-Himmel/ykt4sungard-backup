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

<%@ include file="/html/extportlet/shopquery/init.jsp" %>

<%
PortletURL portletURL = (PortletURL)request.getAttribute("view.jsp-portletURL");

List manageableOrganizations = null;

Long[] manageableOrganizationIds = null;

if (portletName.equals(PortletKeys.ORGANIZATION_ADMIN)) {
	manageableOrganizations = OrganizationLocalServiceUtil.getManageableOrganizations(user.getUserId());

	manageableOrganizationIds = EnterpriseAdminUtil.getOrganizationIds(manageableOrganizations);
}
%>


<%
UserSearch searchContainer = new UserSearch(renderRequest, portletURL);

List headerNames = searchContainer.getHeaderNames();

headerNames.add(StringPool.BLANK);

portletURL.setParameter(searchContainer.getCurParam(), String.valueOf(searchContainer.getCurValue()));
%>

<input name="<portlet:namespace />usersRedirect" type="hidden" value="<%= portletURL.toString() %>" />

<liferay-ui:search-form
	page="/html/extportlet/shopquery/shopbind/user_search.jsp"
	searchContainer="<%= searchContainer %>"
/>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">

	<%
	UserSearchTerms searchTerms = (UserSearchTerms)searchContainer.getSearchTerms();

	long organizationId = searchTerms.getOrganizationId();
	long roleId = searchTerms.getRoleId();
	long userGroupId = searchTerms.getUserGroupId();

	LinkedHashMap userParams = new LinkedHashMap();

	if (organizationId > 0) {
		userParams.put("usersOrgs", new Long(organizationId));
	}
	else {
		if (portletName.equals(PortletKeys.ORGANIZATION_ADMIN)) {
			userParams.put("usersOrgs", manageableOrganizationIds);
		}
	}

	if (roleId > 0) {
		userParams.put("usersRoles", new Long(roleId));
	}

	if (userGroupId > 0) {
		userParams.put("usersUserGroups", new Long(userGroupId));
	}
	%>

	<%@ include file="/html/extportlet/shopquery/shopbind/user_search_results.jspf" %>

	<%
	Organization organization = null;

	if ((organizationId > 0)) {
		try {
			organization = OrganizationLocalServiceUtil.getOrganization(organizationId);
		}
		catch (NoSuchOrganizationException nsoe) {
		}
	}

	Role role = null;

	if (roleId > 0) {
		try {
			role = RoleLocalServiceUtil.getRole(roleId);
		}
		catch (NoSuchRoleException nsre) {
		}
	}

	UserGroup userGroup = null;

	if (userGroupId > 0) {
		try {
			userGroup = UserGroupLocalServiceUtil.getUserGroup(userGroupId);
		}
		catch (NoSuchUserGroupException nsuge) {
		}
	}
	%>

	<c:if test="<%= (organization != null) || (role != null) || (userGroup != null) %>">
		<br />
	</c:if>

	<c:if test="<%= organization != null %>">
		<input name="<portlet:namespace /><%= UserDisplayTerms.ORGANIZATION_ID %>" type="hidden" value="<%= organization.getOrganizationId() %>" />

		<liferay-ui:message key="filter-by-organization" />: <%= organization.getName() %><br />
	</c:if>

	<c:if test="<%= role != null %>">
		<input name="<portlet:namespace /><%= UserDisplayTerms.ROLE_ID %>" type="hidden" value="<%= role.getRoleId() %>" />

		<liferay-ui:message key="filter-by-role" />: <%= role.getName() %><br />
	</c:if>

	<c:if test="<%= userGroup != null %>">
		<input name="<portlet:namespace /><%= UserDisplayTerms.USER_GROUP_ID %>" type="hidden" value="<%= userGroup.getUserGroupId() %>" />

		<liferay-ui:message key="filter-by-user-group" />: <%= userGroup.getName() %><br />
	</c:if>

	<div class="separator"><!-- --></div>


	<%
	List resultRows = searchContainer.getResultRows();

	for (int i = 0; i < results.size(); i++) {
		User user2 = (User)results.get(i);

		ResultRow row = new ResultRow(user2, user2.getUserId(), i);

		PortletURL rowURL = renderResponse.createRenderURL();

		rowURL.setWindowState(WindowState.MAXIMIZED);

		rowURL.setParameter("struts_action", "/ext/shop_admin_edit_user");
		rowURL.setParameter("redirect", searchContainer.getIteratorURL().toString());
		rowURL.setParameter("p_u_i_d", String.valueOf(user2.getUserId()));

		// First name

		row.addText(user2.getFirstName(), rowURL);

		// Last name

		//row.addText(user2.getLastName(), rowURL);

		// Screen name

		row.addText(user2.getScreenName(), rowURL);

		// Email address

		//row.addText(user2.getEmailAddress(), rowURL);

		// Job title

		Contact contact2 = user2.getContact();

		row.addText(contact2.getJobTitle(), rowURL);

		// Organizations

		List organizations = user2.getOrganizations();

		if (portletName.equals(PortletKeys.ORGANIZATION_ADMIN)) {
			organizations = OrganizationLocalServiceUtil.getSubsetOrganizations(organizations, manageableOrganizations);
		}

		row.addText(ListUtil.toString(organizations, "name", ", "), rowURL);

		// Action

		row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/extportlet/shopquery/shopbind/user_action.jsp");

		// Add result row

		resultRows.add(row);
	}
	%>

	<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
</c:if>