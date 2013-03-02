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

<%@ include file="/html/portlet/portlet_configuration/init.jsp" %>

<%
String tabs2 = ParamUtil.getString(request, "tabs2", "users");
String tabs3 = ParamUtil.getString(request, "tabs3", "current");

String cur = ParamUtil.getString(request, "cur");

String redirect = ParamUtil.getString(request, "redirect");
String returnToFullPageURL = ParamUtil.getString(request, "returnToFullPageURL");

String portletResource = ParamUtil.getString(request, "portletResource");

String modelResource = ParamUtil.getString(request, "modelResource");
String modelResourceDescription = ParamUtil.getString(request, "modelResourceDescription");
String modelResourceName = ResourceActionsUtil.getModelResource(pageContext, modelResource);

String resourcePrimKey = ParamUtil.getString(request, "resourcePrimKey");

if (Validator.isNull(resourcePrimKey)) {
	throw new ResourcePrimKeyException();
}

String selResource = modelResource;
String selResourceDescription = modelResourceDescription;
String selResourceName = modelResourceName;

if (Validator.isNull(modelResource)) {
	PortletURL portletURL = new PortletURLImpl(request, portletResource, plid.longValue(), false);

	portletURL.setWindowState(WindowState.NORMAL);
	portletURL.setPortletMode(PortletMode.VIEW);

	redirect = portletURL.toString();

	Portlet portlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), portletResource);

	selResource = portlet.getRootPortletId();
	selResourceDescription = PortalUtil.getPortletTitle(portlet, application, locale);
	selResourceName = LanguageUtil.get(pageContext, "portlet");
}

long groupId = layout.getGroupId();

Layout selLayout = null;

if (modelResource.equals(Layout.class.getName())) {
	selLayout = LayoutLocalServiceUtil.getLayout(GetterUtil.getLong(resourcePrimKey));

	groupId = selLayout.getGroupId();
}

Resource resource = null;

try {
	resource = ResourceLocalServiceUtil.getResource(company.getCompanyId(), selResource, ResourceImpl.SCOPE_INDIVIDUAL, resourcePrimKey);
}
catch (NoSuchResourceException nsre) {
	boolean portletActions = Validator.isNull(modelResource);

	ResourceLocalServiceUtil.addResources(company.getCompanyId(), groupId, 0, selResource, resourcePrimKey, portletActions, true, true);

	resource = ResourceLocalServiceUtil.getResource(company.getCompanyId(), selResource, ResourceImpl.SCOPE_INDIVIDUAL, resourcePrimKey);
}

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setParameter("struts_action", "/portlet_configuration/edit_permissions");
portletURL.setParameter("tabs2", tabs2);
portletURL.setParameter("tabs3", tabs3);
portletURL.setParameter("redirect", redirect);
portletURL.setParameter("returnToFullPageURL", returnToFullPageURL);
portletURL.setParameter("portletResource", portletResource);
portletURL.setParameter("modelResource", modelResource);
portletURL.setParameter("modelResourceDescription", modelResourceDescription);
portletURL.setParameter("resourcePrimKey", resourcePrimKey);
%>

<script type="text/javascript">
	function <portlet:namespace />saveGroupPermissions() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "group_permissions";
		document.<portlet:namespace />fm.<portlet:namespace />permissionsRedirect.value = "<%= portletURL.toString() %>";
		document.<portlet:namespace />fm.<portlet:namespace />groupIdActionIds.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />current_actions);
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL><portlet:param name="struts_action" value="/portlet_configuration/edit_permissions" /></portlet:actionURL>");
	}

	function <portlet:namespace />saveGuestPermissions() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "guest_permissions";
		document.<portlet:namespace />fm.<portlet:namespace />permissionsRedirect.value = "<%= portletURL.toString() %>";
		document.<portlet:namespace />fm.<portlet:namespace />guestActionIds.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />current_actions);
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL><portlet:param name="struts_action" value="/portlet_configuration/edit_permissions" /></portlet:actionURL>");
	}

	function <portlet:namespace />saveOrganizationPermissions(organizationIdsPos, organizationIdsPosValue) {

		<%
		PortletURL saveOrganizationPermissionsRedirectURL = PortletURLUtil.clone(portletURL, renderResponse);

		new OrganizationSearch(renderRequest, saveOrganizationPermissionsRedirectURL);
		%>

		var organizationIds = document.<portlet:namespace />fm.<portlet:namespace />organizationIds.value;

		if (organizationIdsPos == -1) {
			organizationIds = "";
			organizationIdsPos = 0;
		}

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "organization_permissions";
		document.<portlet:namespace />fm.<portlet:namespace />permissionsRedirect.value = "<%= saveOrganizationPermissionsRedirectURL.toString() %>&<portlet:namespace />cur=<%= cur %>&<portlet:namespace />organizationIds=" + organizationIds + "&<portlet:namespace />organizationIdsPos=" + organizationIdsPos;
		document.<portlet:namespace />fm.<portlet:namespace />organizationIds.value = organizationIds;
		document.<portlet:namespace />fm.<portlet:namespace />organizationIdsPosValue.value = organizationIdsPosValue;
		document.<portlet:namespace />fm.<portlet:namespace />organizationIdActionIds.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />current_actions);
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL><portlet:param name="struts_action" value="/portlet_configuration/edit_permissions" /></portlet:actionURL>");
	}

	function <portlet:namespace />saveRolePermissions(roleIdsPos, roleIdsPosValue) {

		<%
		PortletURL saveRolePermissionsRedirectURL = PortletURLUtil.clone(portletURL, renderResponse);

		new RoleSearch(renderRequest, saveRolePermissionsRedirectURL);
		%>

		var roleIds = document.<portlet:namespace />fm.<portlet:namespace />roleIds.value;

		if (roleIdsPos == -1) {
			roleIds = "";
			roleIdsPos = 0;
		}

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "role_permissions";
		document.<portlet:namespace />fm.<portlet:namespace />permissionsRedirect.value = "<%= saveRolePermissionsRedirectURL.toString() %>&<portlet:namespace />cur=<%= cur %>&<portlet:namespace />roleIds=" + roleIds + "&<portlet:namespace />roleIdsPos=" + roleIdsPos;
		document.<portlet:namespace />fm.<portlet:namespace />roleIds.value = roleIds;
		document.<portlet:namespace />fm.<portlet:namespace />roleIdsPosValue.value = roleIdsPosValue;
		document.<portlet:namespace />fm.<portlet:namespace />roleIdActionIds.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />current_actions);
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL><portlet:param name="struts_action" value="/portlet_configuration/edit_permissions" /></portlet:actionURL>");
	}

	function <portlet:namespace />saveUserGroupPermissions(userGroupIdsPos, userGroupIdsPosValue) {

		<%
		PortletURL saveUserGroupPermissionsRedirectURL = PortletURLUtil.clone(portletURL, false, renderResponse);

		new UserGroupSearch(renderRequest, saveUserGroupPermissionsRedirectURL);
		%>

		var userGroupIds = document.<portlet:namespace />fm.<portlet:namespace />userGroupIds.value;

		if (userGroupIdsPos == -1) {
			userGroupIds = "";
			userGroupIdsPos = 0;
		}

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "user_group_permissions";
		document.<portlet:namespace />fm.<portlet:namespace />permissionsRedirect.value = "<%= saveUserGroupPermissionsRedirectURL.toString() %>&<portlet:namespace />cur=<%= cur %>&<portlet:namespace />userGroupIds=" + userGroupIds + "&<portlet:namespace />userGroupIdsPos=" + userGroupIdsPos;
		document.<portlet:namespace />fm.<portlet:namespace />userGroupIds.value = userGroupIds;
		document.<portlet:namespace />fm.<portlet:namespace />userGroupIdsPosValue.value = userGroupIdsPosValue;
		document.<portlet:namespace />fm.<portlet:namespace />userGroupIdActionIds.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />current_actions);
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL><portlet:param name="struts_action" value="/portlet_configuration/edit_permissions" /></portlet:actionURL>");
	}

	function <portlet:namespace />saveUserPermissions(userIdsPos, userIdsPosValue) {

		<%
		PortletURL saveUserPermissionsRedirectURL = PortletURLUtil.clone(portletURL, false, renderResponse);

		new UserSearch(renderRequest, saveUserPermissionsRedirectURL);
		%>

		var userIds = document.<portlet:namespace />fm.<portlet:namespace />userIds.value;

		if (userIdsPos == -1) {
			userIds = "";
			userIdsPos = 0;
		}

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "user_permissions";
		document.<portlet:namespace />fm.<portlet:namespace />permissionsRedirect.value = "<%= saveUserPermissionsRedirectURL.toString() %>&<portlet:namespace />cur=<%= cur %>&<portlet:namespace />userIds=" + userIds + "&<portlet:namespace />userIdsPos=" + userIdsPos;
		document.<portlet:namespace />fm.<portlet:namespace />userIds.value = userIds;
		document.<portlet:namespace />fm.<portlet:namespace />userIdsPosValue.value = userIdsPosValue;
		document.<portlet:namespace />fm.<portlet:namespace />userIdActionIds.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />current_actions);
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL><portlet:param name="struts_action" value="/portlet_configuration/edit_permissions" /></portlet:actionURL>");
	}

	function <portlet:namespace />updateOrganizationPermissions() {
		document.<portlet:namespace />fm.<portlet:namespace />organizationIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />updateRolePermissions() {
		document.<portlet:namespace />fm.<portlet:namespace />roleIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />updateUserGroupPermissions() {
		document.<portlet:namespace />fm.<portlet:namespace />userGroupIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />updateUserPermissions() {
		document.<portlet:namespace />fm.<portlet:namespace />userIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<%= portletURL.toString() %>" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />permissionsRedirect" type="hidden" value="" />
<input name="<portlet:namespace />cur" type="hidden" value="<%= cur %>" />
<input name="<portlet:namespace />resourceId" type="hidden" value="<%= resource.getResourceId() %>" />

<c:choose>
	<c:when test="<%= Validator.isNull(modelResource) %>">
		<liferay-util:include page="/html/portlet/portlet_configuration/tabs1.jsp">
			<liferay-util:param name="tabs1" value="permissions" />
		</liferay-util:include>
	</c:when>
	<c:otherwise>
		<div>
			<liferay-ui:message key="edit-permissions-for" /> <%= selResourceName %>: <a href="<%= redirect %>"><%= selResourceDescription %></a>
		</div>

		<br />
	</c:otherwise>
</c:choose>

<%
String tabs2Names = "users,organizations,user-groups,regular-roles,community-roles,community,guest";

if (ResourceActionsUtil.isPortalModelResource(modelResource)) {
	tabs2Names = StringUtil.replace(tabs2Names, "community,", StringPool.BLANK);
	tabs2Names = StringUtil.replace(tabs2Names, "community-roles,", StringPool.BLANK);
	tabs2Names = StringUtil.replace(tabs2Names, "guest,", StringPool.BLANK);
}
else if (modelResource.equals(Layout.class.getName())) {
	Group group = GroupLocalServiceUtil.getGroup(groupId);

	// User layouts should not have community assignments

	if (group.isUser()) {
		tabs2Names = StringUtil.replace(tabs2Names, "community,", StringPool.BLANK);
		tabs2Names = StringUtil.replace(tabs2Names, "community-roles,", StringPool.BLANK);
	}
	else if (group.isOrganization()) {
		tabs2Names = StringUtil.replace(tabs2Names, "community,", "organization,");
		tabs2Names = StringUtil.replace(tabs2Names, "community-roles,", "organization-roles,");
	}

	// Private layouts should not have guest assignments

	if (selLayout.isPrivateLayout()) {
		tabs2Names = StringUtil.replace(tabs2Names, "guest,", StringPool.BLANK);
	}
}
else {
	Group group = GroupLocalServiceUtil.getGroup(groupId);

	if (group.isUser()) {
		tabs2Names = StringUtil.replace(tabs2Names, "community,", StringPool.BLANK);
		tabs2Names = StringUtil.replace(tabs2Names, "community-roles,", StringPool.BLANK);
	}
	else if (group.isOrganization()) {
		tabs2Names = StringUtil.replace(tabs2Names, "community,", "organization,");
		tabs2Names = StringUtil.replace(tabs2Names, "community-roles,", "organization-roles,");
	}
}
%>

<c:choose>
	<c:when test="<%= Validator.isNull(modelResource) %>">
		<liferay-ui:tabs
			names="<%= tabs2Names %>"
			param="tabs2"
			url="<%= portletURL.toString() %>"
		/>
	</c:when>
	<c:otherwise>
		<liferay-ui:tabs
			names="<%= tabs2Names %>"
			param="tabs2"
			url="<%= portletURL.toString() %>"
			backURL="<%= redirect %>"
		/>
	</c:otherwise>
</c:choose>


<c:choose>
	<c:when test='<%= tabs2.equals("users") %>'>

		<%
		String userIds = ParamUtil.getString(request, "userIds");
		long[] userIdsArray = StringUtil.split(userIds, 0L);
		int userIdsPos = ParamUtil.getInteger(request, "userIdsPos");
		%>

		<input name="<portlet:namespace />userIds" type="hidden" value="<%= userIds %>" />
		<input name="<portlet:namespace />userIdsPos" type="hidden" value="<%= userIdsPos %>" />
		<input name="<portlet:namespace />userIdsPosValue" type="hidden" value="" />
		<input name="<portlet:namespace />userIdActionIds" type="hidden" value="" />

		<c:choose>
			<c:when test="<%= userIdsArray.length == 0 %>">
				<liferay-ui:tabs
					names="current,available"
					param="tabs3"
					url="<%= portletURL.toString() %>"
				/>

				<%
				UserSearch searchContainer = new UserSearch(renderRequest, portletURL);

				searchContainer.setRowChecker(new RowChecker(renderResponse));
				%>

				<liferay-ui:search-form
					page="/html/portlet/enterprise_admin/user_search.jsp"
					searchContainer="<%= searchContainer %>"
				/>

				<%
				UserSearchTerms searchTerms = (UserSearchTerms)searchContainer.getSearchTerms();

				LinkedHashMap userParams = new LinkedHashMap();

				if (tabs3.equals("current")) {
					userParams.put("permission", new Long(resource.getResourceId()));
				}
				else if (tabs3.equals("available") && modelResource.equals(Layout.class.getName())) {
					userParams.put("usersGroups", new Long(groupId));
				}
				%>

				<%@ include file="/html/portlet/enterprise_admin/user_search_results.jspf" %>

				<div class="separator"><!-- --></div>

				<input type="button" value="<liferay-ui:message key="update-permissions" />" onClick="<portlet:namespace />updateUserPermissions();" />

				<br /><br />

				<%
				List headerNames = new ArrayList();

				headerNames.add("name");
				headerNames.add("screen-name");
				//headerNames.add("email-address");
				headerNames.add("permissions");

				searchContainer.setHeaderNames(headerNames);

				List resultRows = searchContainer.getResultRows();

				for (int i = 0; i < results.size(); i++) {
					User user2 = (User)results.get(i);

					ResultRow row = new ResultRow(user2, user2.getUserId(), i);

					// Name, screen name, and email address

					row.addText(user2.getFullName());
					row.addText(user2.getScreenName());
					//row.addText(user2.getEmailAddress());

					// Permissions

					List permissions = PermissionLocalServiceUtil.getUserPermissions(user2.getUserId(), resource.getResourceId());

					List actions = ResourceActionsUtil.getActions(permissions);
					List actionsNames = ResourceActionsUtil.getActionsNames(pageContext, actions);

					row.addText(StringUtil.merge(actionsNames, ", "));

					// Add result row

					resultRows.add(row);
				}
				%>

				<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
			</c:when>
			<c:otherwise>

				<%
				User user2 = UserLocalServiceUtil.getUserById(userIdsArray[userIdsPos]);
				%>

				<liferay-ui:tabs names="<%= user2.getFullName() %>" />

				<%
				List permissions = PermissionLocalServiceUtil.getUserPermissions(user2.getUserId(), resource.getResourceId());

				List actions1 = ResourceActionsUtil.getResourceActions(company.getCompanyId(), portletResource, modelResource);
				List actions2 = ResourceActionsUtil.getActions(permissions);

				// Left list

				List leftList = new ArrayList();

				for (int i = 0; i < actions2.size(); i++) {
					String actionId = (String)actions2.get(i);

					leftList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
				}

				Collections.sort(leftList, new KeyValuePairComparator(false, true));

				// Right list

				List rightList = new ArrayList();

				for (int i = 0; i < actions1.size(); i++) {
					String actionId = (String)actions1.get(i);

					if (!actions2.contains(actionId)) {
						rightList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
					}
				}

				Collections.sort(rightList, new KeyValuePairComparator(false, true));
				%>

				<liferay-ui:input-move-boxes
					leftTitle="current"
					rightTitle="available"
					leftBoxName="current_actions"
					rightBoxName="available_actions"
					leftList="<%= leftList %>"
					rightList="<%= rightList %>"
				/>

				<br />

				<table border="0" cellpadding="0" cellspacing="0" width="100%">
				<tr>
					<td>
						<input <%= userIdsPos > 0 ? "" : "disabled" %> type="button" value="<liferay-ui:message key="previous" />" onClick="<portlet:namespace />saveUserPermissions(<%= userIdsPos - 1 %>, '<%= userIdsArray[userIdsPos] %>');">

						<input <%= userIdsPos + 1 < userIdsArray.length ? "" : "disabled" %> type="button" value="<liferay-ui:message key="next" />" onClick="<portlet:namespace />saveUserPermissions(<%= userIdsPos + 1 %>, '<%= userIdsArray[userIdsPos] %>');">
					</td>
					<td align="right">
						<input type="button" value="<liferay-ui:message key="finished" />" onClick="<portlet:namespace />saveUserPermissions(-1, '<%= userIdsArray[userIdsPos] %>');" />
					</td>
				</tr>
				</table>
			</c:otherwise>
		</c:choose>
	</c:when>
	<c:when test='<%= tabs2.equals("organizations") %>'>

		<%
		String organizationIds = ParamUtil.getString(request, "organizationIds");
		long[] organizationIdsArray = StringUtil.split(organizationIds, 0L);
		int organizationIdsPos = ParamUtil.getInteger(request, "organizationIdsPos");
		%>

		<input name="<portlet:namespace />organizationIds" type="hidden" value="<%= organizationIds %>" />
		<input name="<portlet:namespace />organizationIdsPos" type="hidden" value="<%= organizationIdsPos %>" />
		<input name="<portlet:namespace />organizationIdsPosValue" type="hidden" value="" />
		<input name="<portlet:namespace />organizationIdActionIds" type="hidden" value="" />

		<c:choose>
			<c:when test="<%= organizationIdsArray.length == 0 %>">
				<liferay-ui:tabs
					names="current,available"
					param="tabs3"
					url="<%= portletURL.toString() %>"
				/>

				<%
				OrganizationSearch searchContainer = new OrganizationSearch(renderRequest, portletURL);

				searchContainer.setRowChecker(new RowChecker(renderResponse));
				%>

				<liferay-ui:search-form
					page="/html/portlet/enterprise_admin/organization_search.jsp"
					searchContainer="<%= searchContainer %>"
				/>

				<%
				OrganizationSearchTerms searchTerms = (OrganizationSearchTerms)searchContainer.getSearchTerms();

				long parentOrganizationId = OrganizationImpl.ANY_PARENT_ORGANIZATION_ID;

				LinkedHashMap organizationParams = new LinkedHashMap();

				if (tabs3.equals("current")) {
					organizationParams.put("permissionsResourceId", new Long(resource.getResourceId()));
					organizationParams.put("permissionsGroupId", new Long(groupId));
				}
				%>

				<%@ include file="/html/portlet/enterprise_admin/organization_search_results.jspf" %>

				<div class="separator"><!-- --></div>

				<input type="button" value="<liferay-ui:message key="update-permissions" />" onClick="<portlet:namespace />updateOrganizationPermissions();" />

				<br /><br />

				<%
				List headerNames = new ArrayList();

				headerNames.add("name");
				headerNames.add("parent-organization");
				headerNames.add("type");
				headerNames.add("city");
				headerNames.add("permissions");
				//headerNames.add("exclusive");

				searchContainer.setHeaderNames(headerNames);

				List resultRows = searchContainer.getResultRows();

				for (int i = 0; i < results.size(); i++) {
					Organization organization = (Organization)results.get(i);

					ResultRow row = new ResultRow(organization, organization.getOrganizationId(), i);

					// Name

					row.addText(organization.getName());

					// Parent organization

					String parentOrganizationName = StringPool.BLANK;

					if (organization.getParentOrganizationId() > 0) {
						try {
							Organization parentOrganization = OrganizationLocalServiceUtil.getOrganization(organization.getParentOrganizationId());

							parentOrganizationName = parentOrganization.getName();
						}
						catch (Exception e) {
						}
					}

					row.addText(parentOrganizationName);

					// Type

					row.addText(LanguageUtil.get(pageContext, organization.getTypeLabel()));

					// City

					Address address = organization.getAddress();

					row.addText(address.getCity());

					// Permissions

					//boolean organizationIntersection = false;

					List permissions = PermissionLocalServiceUtil.getGroupPermissions(organization.getGroup().getGroupId(), resource.getResourceId());

					/*if (permissions.size() == 0) {
						permissions = PermissionLocalServiceUtil.getOrgGroupPermissions(organization.getOrganizationId(), groupId, resource.getResourceId());

						if (permissions.size() > 0) {
							organizationIntersection = true;
						}
					}*/

					List actions = ResourceActionsUtil.getActions(permissions);
					List actionsNames = ResourceActionsUtil.getActionsNames(pageContext, actions);

					row.addText(StringUtil.merge(actionsNames, ", "));

					/*if (permissions.size() == 0) {
						row.addText(StringPool.BLANK);
					}
					else {
						row.addText(LanguageUtil.get(pageContext, (organizationIntersection ? "yes" : "no")));
					}*/

					// Add result row

					resultRows.add(row);
				}
				%>

				<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
			</c:when>
			<c:otherwise>

				<%
				Organization organization = OrganizationLocalServiceUtil.getOrganization(organizationIdsArray[organizationIdsPos]);
				%>

				<liferay-ui:tabs names="<%= Html.escape(organization.getName()) %>" />

				<%
				//boolean organizationIntersection = false;

				List permissions = PermissionLocalServiceUtil.getGroupPermissions(organization.getGroup().getGroupId(), resource.getResourceId());

				/*if (permissions.size() == 0) {
					permissions = PermissionLocalServiceUtil.getOrgGroupPermissions(organization.getOrganizationId(), groupId, resource.getResourceId());

					if (permissions.size() > 0) {
						organizationIntersection = true;
					}
				}*/

				List actions1 = ResourceActionsUtil.getResourceActions(company.getCompanyId(), portletResource, modelResource);
				List actions2 = ResourceActionsUtil.getActions(permissions);

				// Left list

				List leftList = new ArrayList();

				for (int i = 0; i < actions2.size(); i++) {
					String actionId = (String)actions2.get(i);

					leftList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
				}

				Collections.sort(leftList, new KeyValuePairComparator(false, true));

				// Right list

				List rightList = new ArrayList();

				for (int i = 0; i < actions1.size(); i++) {
					String actionId = (String)actions1.get(i);

					if (!actions2.contains(actionId)) {
						rightList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
					}
				}

				Collections.sort(rightList, new KeyValuePairComparator(false, true));
				%>

				<liferay-ui:input-move-boxes
					formName="fm"
					leftTitle="current"
					rightTitle="available"
					leftBoxName="current_actions"
					rightBoxName="available_actions"
					leftList="<%= leftList %>"
					rightList="<%= rightList %>"
				/>

				<br />

				<%--<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="assign-permissions-only-to-users-that-are-also-members-of-the-current-community" />
					</td>
					<td>
						<select name="<portlet:namespace />organizationIntersection">
							<option <%= organizationIntersection ? "selected" : "" %> value="1"><liferay-ui:message key="yes" /></option>
							<option <%= !organizationIntersection ? "selected" : "" %> value="0"><liferay-ui:message key="no" /></option>
						</select>
					</td>
				</tr>
				</table>

				<br />--%>

				<table border="0" cellpadding="0" cellspacing="0" width="100%">
				<tr>
					<td>
						<input <%= organizationIdsPos > 0 ? "" : "disabled" %> type="button" value="<liferay-ui:message key="previous" />" onClick="<portlet:namespace />saveOrganizationPermissions(<%= organizationIdsPos - 1 %>, '<%= organizationIdsArray[organizationIdsPos] %>');">

						<input <%= organizationIdsPos + 1 < organizationIdsArray.length ? "" : "disabled" %> type="button" value="<liferay-ui:message key="next" />" onClick="<portlet:namespace />saveOrganizationPermissions(<%= organizationIdsPos + 1 %>, '<%= organizationIdsArray[organizationIdsPos] %>');">
					</td>
					<td align="right">
						<input type="button" value="<liferay-ui:message key="finished" />" onClick="<portlet:namespace />saveOrganizationPermissions(-1, '<%= organizationIdsArray[organizationIdsPos] %>');" />
					</td>
				</tr>
				</table>
			</c:otherwise>
		</c:choose>
	</c:when>
	<c:when test='<%= tabs2.equals("user-groups") %>'>

		<%
		String userGroupIds = ParamUtil.getString(request, "userGroupIds");
		long[] userGroupIdsArray = StringUtil.split(userGroupIds, 0L);
		int userGroupIdsPos = ParamUtil.getInteger(request, "userGroupIdsPos");
		%>

		<input name="<portlet:namespace />userGroupIds" type="hidden" value="<%= userGroupIds %>" />
		<input name="<portlet:namespace />userGroupIdsPos" type="hidden" value="<%= userGroupIdsPos %>" />
		<input name="<portlet:namespace />userGroupIdsPosValue" type="hidden" value="" />
		<input name="<portlet:namespace />userGroupIdActionIds" type="hidden" value="" />

		<c:choose>
			<c:when test="<%= userGroupIdsArray.length == 0 %>">
				<liferay-ui:tabs
					names="current,available"
					param="tabs3"
					url="<%= portletURL.toString() %>"
				/>

				<%
				UserGroupSearch searchContainer = new UserGroupSearch(renderRequest, portletURL);

				searchContainer.setRowChecker(new RowChecker(renderResponse));
				%>

				<liferay-ui:search-form
					page="/html/portlet/enterprise_admin/user_group_search.jsp"
					searchContainer="<%= searchContainer %>"
				/>

				<%
				UserGroupSearchTerms searchTerms = (UserGroupSearchTerms)searchContainer.getSearchTerms();

				LinkedHashMap userGroupParams = new LinkedHashMap();

				if (tabs3.equals("current")) {
					userGroupParams.put("permissionsResourceId", new Long(resource.getResourceId()));
				}

				int total = UserGroupLocalServiceUtil.searchCount(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), userGroupParams);

				searchContainer.setTotal(total);

				List results = UserGroupLocalServiceUtil.search(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), userGroupParams, searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());

				searchContainer.setResults(results);
				%>

				<div class="separator"><!-- --></div>

				<input type="button" value="<liferay-ui:message key="update-permissions" />" onClick="<portlet:namespace />updateUserGroupPermissions();" />

				<br /><br />

				<%
				List headerNames = new ArrayList();

				headerNames.add("name");
				headerNames.add("description");
				headerNames.add("permissions");

				searchContainer.setHeaderNames(headerNames);

				List resultRows = searchContainer.getResultRows();

				for (int i = 0; i < results.size(); i++) {
					UserGroup userGroup = (UserGroup)results.get(i);

					ResultRow row = new ResultRow(userGroup, userGroup.getUserGroupId(), i);

					// Name

					row.addText(userGroup.getName());

					// Name

					row.addText(userGroup.getName());

					// Permissions

					List permissions = PermissionLocalServiceUtil.getGroupPermissions(userGroup.getGroup().getGroupId(), resource.getResourceId());

					List actions = ResourceActionsUtil.getActions(permissions);
					List actionsNames = ResourceActionsUtil.getActionsNames(pageContext, actions);

					row.addText(StringUtil.merge(actionsNames, ", "));

					// Add result row

					resultRows.add(row);
				}
				%>

				<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
			</c:when>
			<c:otherwise>

				<%
				UserGroup userGroup = UserGroupLocalServiceUtil.getUserGroup(userGroupIdsArray[userGroupIdsPos]);
				%>

				<liferay-ui:tabs names="<%= userGroup.getName() %>" />

				<%
				List permissions = PermissionLocalServiceUtil.getGroupPermissions(userGroup.getGroup().getGroupId(), resource.getResourceId());

				List actions1 = ResourceActionsUtil.getResourceActions(company.getCompanyId(), portletResource, modelResource);
				List actions2 = ResourceActionsUtil.getActions(permissions);

				// Left list

				List leftList = new ArrayList();

				for (int i = 0; i < actions2.size(); i++) {
					String actionId = (String)actions2.get(i);

					leftList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
				}

				Collections.sort(leftList, new KeyValuePairComparator(false, true));

				// Right list

				List rightList = new ArrayList();

				for (int i = 0; i < actions1.size(); i++) {
					String actionId = (String)actions1.get(i);

					if (!actions2.contains(actionId)) {
						rightList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
					}
				}

				Collections.sort(rightList, new KeyValuePairComparator(false, true));
				%>

				<liferay-ui:input-move-boxes
					formName="fm"
					leftTitle="current"
					rightTitle="available"
					leftBoxName="current_actions"
					rightBoxName="available_actions"
					leftList="<%= leftList %>"
					rightList="<%= rightList %>"
				/>

				<br />

				<table border="0" cellpadding="0" cellspacing="0" width="100%">
				<tr>
					<td>
						<input <%= userGroupIdsPos > 0 ? "" : "disabled" %> type="button" value="<liferay-ui:message key="previous" />" onClick="<portlet:namespace />saveUserGroupPermissions(<%= userGroupIdsPos - 1 %>, '<%= userGroupIdsArray[userGroupIdsPos] %>');">

						<input <%= userGroupIdsPos + 1 < userGroupIdsArray.length ? "" : "disabled" %> type="button" value="<liferay-ui:message key="next" />" onClick="<portlet:namespace />saveUserGroupPermissions(<%= userGroupIdsPos + 1 %>, '<%= userGroupIdsArray[userGroupIdsPos] %>');">
					</td>
					<td align="right">
						<input type="button" value="<liferay-ui:message key="finished" />" onClick="<portlet:namespace />saveUserGroupPermissions(-1, '<%= userGroupIdsArray[userGroupIdsPos] %>');" />
					</td>
				</tr>
				</table>
			</c:otherwise>
		</c:choose>
	</c:when>
	<c:when test='<%= tabs2.equals("regular-roles") || tabs2.equals("community-roles") || tabs2.equals("organization-roles") %>'>

		<%
		String roleIds = ParamUtil.getString(request, "roleIds");

		long[] roleIdsArray = StringUtil.split(roleIds, 0L);

		int roleIdsPos = ParamUtil.getInteger(request, "roleIdsPos");

		int type = RoleImpl.TYPE_REGULAR;

		if (tabs2.equals("community-roles")) {
			type = RoleImpl.TYPE_COMMUNITY;
		}
		else if (tabs2.equals("organization-roles")) {
			type = RoleImpl.TYPE_ORGANIZATION;
		}
		%>

		<input name="<portlet:namespace />roleIds" type="hidden" value="<%= roleIds %>" />
		<input name="<portlet:namespace />roleIdsPos" type="hidden" value="<%= roleIdsPos %>" />
		<input name="<portlet:namespace />roleIdsPosValue" type="hidden" value="" />
		<input name="<portlet:namespace />roleIdActionIds" type="hidden" value="" />

		<c:choose>
			<c:when test="<%= roleIdsArray.length == 0 %>">
				<liferay-ui:tabs
					names="current,available"
					param="tabs3"
					url="<%= portletURL.toString() %>"
				/>

				<%
				RoleSearch searchContainer = new RoleSearch(renderRequest, portletURL);

				searchContainer.setRowChecker(new RowChecker(renderResponse));
				%>

				<liferay-ui:search-form
					page="/html/portlet/enterprise_admin/role_search.jsp"
					searchContainer="<%= searchContainer %>"
				/>

				<%
				RoleSearchTerms searchTerms = (RoleSearchTerms)searchContainer.getSearchTerms();

				LinkedHashMap roleParams = new LinkedHashMap();

				if (tabs3.equals("current")) {
					roleParams.put("permissionsResourceId", new Long(resource.getResourceId()));
				}

				int total = RoleLocalServiceUtil.searchCount(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), new Integer(type), roleParams);

				searchContainer.setTotal(total);

				List results = RoleLocalServiceUtil.search(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), new Integer(type), roleParams, searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());

				searchContainer.setResults(results);
				%>

				<div class="separator"><!-- --></div>

				<input type="button" value="<liferay-ui:message key="update-permissions" />" onClick="<portlet:namespace />updateRolePermissions();" />

				<br /><br />

				<%
				List headerNames = new ArrayList();

				headerNames.add("name");
				headerNames.add("type");
				headerNames.add("permissions");

				searchContainer.setHeaderNames(headerNames);

				List resultRows = searchContainer.getResultRows();

				for (int i = 0; i < results.size(); i++) {
					Role role = (Role)results.get(i);

					ResultRow row = new ResultRow(role, role.getRoleId(), i);

					// Name

					row.addText(role.getName());

					// Type

					row.addText(LanguageUtil.get(pageContext, role.getTypeLabel()));

					// Permissions

					List permissions = PermissionLocalServiceUtil.getRolePermissions(role.getRoleId(), resource.getResourceId());

					List actions = ResourceActionsUtil.getActions(permissions);
					List actionsNames = ResourceActionsUtil.getActionsNames(pageContext, actions);

					row.addText(StringUtil.merge(actionsNames, ", "));

					// Add result row

					resultRows.add(row);
				}
				%>

				<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
			</c:when>
			<c:otherwise>

				<%
				Role role = RoleLocalServiceUtil.getRole(roleIdsArray[roleIdsPos]);
				%>

				<liferay-ui:tabs names="<%= role.getName() %>" />

				<%
				List permissions = PermissionLocalServiceUtil.getRolePermissions(role.getRoleId(), resource.getResourceId());

				List actions1 = ResourceActionsUtil.getResourceActions(company.getCompanyId(), portletResource, modelResource);
				List actions2 = ResourceActionsUtil.getActions(permissions);

				// Left list

				List leftList = new ArrayList();

				for (int i = 0; i < actions2.size(); i++) {
					String actionId = (String)actions2.get(i);

					leftList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
				}

				Collections.sort(leftList, new KeyValuePairComparator(false, true));

				// Right list

				List rightList = new ArrayList();

				for (int i = 0; i < actions1.size(); i++) {
					String actionId = (String)actions1.get(i);

					if (!actions2.contains(actionId)) {
						rightList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
					}
				}

				Collections.sort(rightList, new KeyValuePairComparator(false, true));
				%>

				<liferay-ui:input-move-boxes
					formName="fm"
					leftTitle="current"
					rightTitle="available"
					leftBoxName="current_actions"
					rightBoxName="available_actions"
					leftList="<%= leftList %>"
					rightList="<%= rightList %>"
				/>

				<br />

				<table border="0" cellpadding="0" cellspacing="0" width="100%">
				<tr>
					<td>
						<input <%= roleIdsPos > 0 ? "" : "disabled" %> type="button" value="<liferay-ui:message key="previous" />" onClick="<portlet:namespace />saveRolePermissions(<%= roleIdsPos - 1 %>, '<%= roleIdsArray[roleIdsPos] %>');">

						<input <%= roleIdsPos + 1 < roleIdsArray.length ? "" : "disabled" %> type="button" value="<liferay-ui:message key="next" />" onClick="<portlet:namespace />saveRolePermissions(<%= roleIdsPos + 1 %>, '<%= roleIdsArray[roleIdsPos] %>');">
					</td>
					<td align="right">
						<input type="button" value="<liferay-ui:message key="finished" />" onClick="<portlet:namespace />saveRolePermissions(-1, '<%= roleIdsArray[roleIdsPos] %>');" />
					</td>
				</tr>
				</table>
			</c:otherwise>
		</c:choose>
	</c:when>
	<c:when test='<%= tabs2.equals("community") || tabs2.equals("organization") %>'>

		<%
		Group group = GroupLocalServiceUtil.getGroup(groupId);
		%>

		<input name="<portlet:namespace />groupId" type="hidden" value="<%= String.valueOf(group.getGroupId()) %>" />
		<input name="<portlet:namespace />groupIdActionIds" type="hidden" value="" />

		<%
		List permissions = PermissionLocalServiceUtil.getGroupPermissions(group.getGroupId(), resource.getResourceId());

		List actions1 = ResourceActionsUtil.getResourceActions(company.getCompanyId(), portletResource, modelResource);
		List actions2 = ResourceActionsUtil.getActions(permissions);

		List guestUnsupportedActions = ResourceActionsUtil.getResourceGuestUnsupportedActions(portletResource, modelResource);

		// Left list

		List leftList = new ArrayList();

		for (int i = 0; i < actions2.size(); i++) {
			String actionId = (String)actions2.get(i);

			leftList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
		}

		Collections.sort(leftList, new KeyValuePairComparator(false, true));

		// Right list

		List rightList = new ArrayList();

		for (int i = 0; i < actions1.size(); i++) {
			String actionId = (String)actions1.get(i);

			if (!actions2.contains(actionId)) {
				rightList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
			}
		}

		Collections.sort(rightList, new KeyValuePairComparator(false, true));
		%>

		<liferay-ui:input-move-boxes
			formName="fm"
			leftTitle="current"
			rightTitle="available"
			leftBoxName="current_actions"
			rightBoxName="available_actions"
			leftList="<%= leftList %>"
			rightList="<%= rightList %>"
		/>

		<br />

		<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td align="right">
				<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveGroupPermissions();" />
			</td>
		</tr>
		</table>
	</c:when>
	<c:when test='<%= tabs2.equals("guest") %>'>
		<input name="<portlet:namespace />guestActionIds" type="hidden" value="" />

		<%
		User guestUser = UserLocalServiceUtil.getDefaultUser(company.getCompanyId());

		List permissions = PermissionLocalServiceUtil.getUserPermissions(guestUser.getUserId(), resource.getResourceId());

		List actions1 = ResourceActionsUtil.getResourceActions(company.getCompanyId(), portletResource, modelResource);
		List actions2 = ResourceActionsUtil.getActions(permissions);

		List guestUnsupportedActions = ResourceActionsUtil.getResourceGuestUnsupportedActions(portletResource, modelResource);

		// Left list

		List leftList = new ArrayList();

		for (int i = 0; i < actions2.size(); i++) {
			String actionId = (String)actions2.get(i);

			if (!guestUnsupportedActions.contains(actionId)) {
				leftList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
			}
		}

		Collections.sort(leftList, new KeyValuePairComparator(false, true));

		// Right list

		List rightList = new ArrayList();

		for (int i = 0; i < actions1.size(); i++) {
			String actionId = (String)actions1.get(i);

			if (!guestUnsupportedActions.contains(actionId)) {
				if (!actions2.contains(actionId)) {
					rightList.add(new KeyValuePair(actionId, ResourceActionsUtil.getAction(pageContext, actionId)));
				}
			}
		}

		Collections.sort(rightList, new KeyValuePairComparator(false, true));
		%>

		<liferay-ui:input-move-boxes
			formName="fm"
			leftTitle="current"
			rightTitle="available"
			leftBoxName="current_actions"
			rightBoxName="available_actions"
			leftList="<%= leftList %>"
			rightList="<%= rightList %>"
		/>

		<br />

		<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td align="right">
				<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveGuestPermissions();" />
			</td>
		</tr>
		</table>
	</c:when>
	<c:when test='<%= false && tabs2.equals("associated") %>'>

		<%
		String selectedActionId = ParamUtil.getString(request, "selectedActionId");
		%>

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="list-users-with-the-permission-to-perform-the-action" />:
			</td>
			<td>
				<select name="<portlet:namespace />selectedActionId">

					<%
					List actions = ResourceActionsUtil.getResourceActions(company.getCompanyId(), portletResource, modelResource);

					Collections.sort(actions, new ActionComparator(company.getCompanyId(), locale));

					for (int i = 0; i < actions.size(); i++) {
						String actionId = (String)actions.get(i);

						if (selectedActionId.equals("")) {
							selectedActionId = actionId;
						}

						%>
						<option <%= actionId.equals(selectedActionId) ? "selected" : "" %> value="<%= actionId %>"><%= ResourceActionsUtil.getAction(pageContext, actionId) %></option>
					<%
					}
					%>

				</select>
			</td>
		</tr>
		</table>

		<br />

		<%
		portletURL.setParameter("selectedActionId", selectedActionId);

		UserSearch searchContainer = new UserSearch(renderRequest, portletURL);
		%>

		<liferay-ui:search-form
			page="/html/portlet/enterprise_admin/user_search.jsp"
			searchContainer="<%= searchContainer %>"
		/>

		<%
		UserSearchTerms searchTerms = (UserSearchTerms)searchContainer.getSearchTerms();

		int total = UserLocalServiceUtil.getPermissionUsersCount(company.getCompanyId(), groupId, modelResource, resourcePrimKey, selectedActionId, searchTerms.getFirstName(), searchTerms.getMiddleName(), searchTerms.getLastName(), searchTerms.getEmailAddress(), searchTerms.isAndOperator());

		searchContainer.setTotal(total);

		List results = UserLocalServiceUtil.getPermissionUsers(company.getCompanyId(), groupId, modelResource, resourcePrimKey, selectedActionId, searchTerms.getFirstName(), searchTerms.getMiddleName(), searchTerms.getLastName(), searchTerms.getEmailAddress(), searchTerms.isAndOperator(), searchContainer.getStart(), searchContainer.getEnd());

		searchContainer.setResults(results);
		%>

		<div class="separator"><!-- --></div>

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
	</c:when>
</c:choose>

</form>