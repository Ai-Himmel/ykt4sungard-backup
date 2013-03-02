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

<%@ include file="/html/portlet/communities/init.jsp" %>

<%
String tabs1 = ParamUtil.getString(request, "tabs1", "current");

String cur = ParamUtil.getString(request, "cur");

String redirect = ParamUtil.getString(request, "redirect");

Group group = (Group)request.getAttribute(WebKeys.GROUP);

String groupName = group.getName();

Role role = (Role)request.getAttribute(WebKeys.ROLE);

long roleId = BeanParamUtil.getLong(role, request, "roleId");

int roleType = RoleImpl.TYPE_COMMUNITY;

Organization organization = null;

if (group.isOrganization()) {
	organization = OrganizationLocalServiceUtil.getOrganization(group.getClassPK());

	groupName = organization.getName();

	roleType = RoleImpl.TYPE_ORGANIZATION;
}

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/communities/edit_user_roles");
portletURL.setParameter("tabs1", tabs1);
portletURL.setParameter("redirect", redirect);
portletURL.setParameter("groupId", String.valueOf(group.getGroupId()));
portletURL.setParameter("roleId", String.valueOf(roleId));

// Breadcrumbs

PortletURL breadcrumbsURL = renderResponse.createRenderURL();

breadcrumbsURL.setParameter("struts_action", "/communities/edit_user_roles");
breadcrumbsURL.setParameter("tabs1", tabs1);
breadcrumbsURL.setParameter("redirect", redirect);
breadcrumbsURL.setParameter("groupId", String.valueOf(group.getGroupId()));

String breadcrumbs = "<a href=\"" + redirect + "\">" + LanguageUtil.get(pageContext, group.isOrganization() ? "organizations" : "communities") + "</a> &raquo; ";

breadcrumbs += "<a href=\"" + breadcrumbsURL.toString() + "\">" + groupName + "</a>";

if (role != null) {
	breadcrumbsURL.setParameter("roleId", String.valueOf(roleId));

	breadcrumbs += " &raquo; <a href=\"" + breadcrumbsURL.toString() + "\">" + role.getName() + "</a>";
}
%>

<script type="text/javascript">
	function <portlet:namespace />updateUserGroupRoleUsers(redirect) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "user_group_role_users";
		document.<portlet:namespace />fm.<portlet:namespace />redirect.value = redirect;
		document.<portlet:namespace />fm.<portlet:namespace />addUserIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		document.<portlet:namespace />fm.<portlet:namespace />removeUserIds.value = Liferay.Util.listUncheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/communities/edit_user_roles" /></portlet:actionURL>");
	}
</script>

<form action="<%= portletURL.toString() %>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />tabs1" type="hidden" value="<%= tabs1 %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />groupId" type="hidden" value="<%= String.valueOf(group.getGroupId()) %>" />
<input name="<portlet:namespace />roleId" type="hidden" value="<%= roleId %>" />

<%= LanguageUtil.get(pageContext, "assign-" + (group.isOrganization() ? "organization" : "community") + "-roles-to-users") %>

<br /><br />

<c:choose>
	<c:when test="<%= role == null %>">
		<div class="portlet-section-body" style="border: 1px solid; padding: 5px;">
			Step 1 of 2: Choose a role.
		</div>

		<br />

		<div class="breadcrumbs">
			<%= breadcrumbs %>
		</div>

		<liferay-ui:tabs
			names="roles"
		/>

		<%
		RoleSearch searchContainer = new RoleSearch(renderRequest, portletURL);
		%>

		<liferay-ui:search-form
			page="/html/portlet/enterprise_admin/role_search.jsp"
			searchContainer="<%= searchContainer %>"
		/>

		<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">

			<%
			RoleSearchTerms searchTerms = (RoleSearchTerms)searchContainer.getSearchTerms();

			int total = RoleLocalServiceUtil.searchCount(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), new Integer(roleType));

			searchContainer.setTotal(total);

			List results = RoleLocalServiceUtil.search(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), new Integer(roleType), searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());

			searchContainer.setResults(results);
			%>

			<div class="separator"><!-- --></div>

			<%
			List resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.size(); i++) {
				Role curRole = (Role)results.get(i);

				ResultRow row = new ResultRow(curRole, curRole.getRoleId(), i);

				PortletURL rowURL = renderResponse.createRenderURL();

				rowURL.setWindowState(WindowState.MAXIMIZED);

				rowURL.setParameter("struts_action", "/communities/edit_user_roles");
				rowURL.setParameter("redirect", redirect);
				rowURL.setParameter("groupId", String.valueOf(group.getGroupId()));
				rowURL.setParameter("roleId", String.valueOf(curRole.getRoleId()));

				// Name

				row.addText(curRole.getName(), rowURL);

				// Type

				row.addText(LanguageUtil.get(pageContext, curRole.getTypeLabel()), rowURL);

				// Description

				row.addText(curRole.getDescription(), rowURL);

				// Add result row

				resultRows.add(row);
			}
			%>

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
		</c:if>
	</c:when>
	<c:otherwise>
		<input name="<portlet:namespace />addUserIds" type="hidden" value="" />
		<input name="<portlet:namespace />removeUserIds" type="hidden" value="" />

		<div class="portlet-section-body" style="border: 1px solid; padding: 5px;">
			Step 2 of 2: <%= LanguageUtil.get(pageContext, "assign-" + (group.isOrganization() ? "organization" : "community") + "-roles-to-users") %>

			<i>Current</i> signifies current users associated with the <i><%= role.getName() %></i> role. <i>Available</i> signifies all users associated with the <i><%= groupName %></i> <%= (group.isOrganization()) ? "organization" : "community" %>.
		</div>

		<br />

		<div class="breadcrumbs">
			<%= breadcrumbs %>
		</div>

		<liferay-ui:tabs
			names="users"
		/>

		<liferay-ui:tabs
			names="current,available"
			param="tabs1"
			url="<%= portletURL.toString() %>"
		/>

		<%
		UserSearch searchContainer = new UserSearch(renderRequest, portletURL);

		searchContainer.setRowChecker(new UserGroupRoleUserChecker(renderResponse, group, role));
		%>

		<liferay-ui:search-form
			page="/html/portlet/enterprise_admin/user_search.jsp"
			searchContainer="<%= searchContainer %>"
		/>

		<%
		UserSearchTerms searchTerms = (UserSearchTerms)searchContainer.getSearchTerms();

		LinkedHashMap userParams = new LinkedHashMap();

		if (group.isOrganization()) {
			userParams.put("usersOrgs", new Long(organization.getOrganizationId()));
		}
		else {
			userParams.put("usersGroups", new Long(group.getGroupId()));
		}

		if (tabs1.equals("current")) {
			userParams.put("userGroupRole", new Long[] {new Long(group.getGroupId()), new Long(roleId)});
		}
		%>

		<%@ include file="/html/portlet/enterprise_admin/user_search_results.jspf" %>

		<div class="separator"><!-- --></div>

		<input type="button" value="<liferay-ui:message key="update-associations" />" onClick="<portlet:namespace />updateUserGroupRoleUsers('<%= portletURL.toString() %>&<portlet:namespace />cur=<%= cur %>');" />

		<br /><br />

		<%
		List headerNames = new ArrayList();

		headerNames.add("name");
		headerNames.add("screen-name");
		//headerNames.add("email-address");

		searchContainer.setHeaderNames(headerNames);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			User user2 = (User)results.get(i);

			ResultRow row = new ResultRow(user2, user2.getUserId(), i);

			// Name, screen name, and email address

			row.addText(user2.getFullName());
			row.addText(user2.getScreenName());
			//row.addText(user2.getEmailAddress());

			// Add result row

			resultRows.add(row);
		}
		%>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:otherwise>
</c:choose>

</form>