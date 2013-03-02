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
String cmd = ParamUtil.getString(request, Constants.CMD);

tabs1 = "roles";
String tabs2 = ParamUtil.getString(request, "tabs2", "current");

String cur = ParamUtil.getString(request, "cur");

String redirect = ParamUtil.getString(request, "redirect");

Role role = (Role)request.getAttribute(WebKeys.ROLE);

String portletResource = ParamUtil.getString(request, "portletResource");

String portletResourceLabel = null;

if (Validator.isNotNull(portletResource)) {
	Portlet portlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), portletResource);

	portletResourceLabel = PortalUtil.getPortletTitle(portlet, application, locale);
}

List modelResources = null;

if (Validator.isNotNull(portletResource)) {
	modelResources = ResourceActionsUtil.getPortletModelResources(portletResource);
}

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/enterprise_admin/edit_role_permissions");
portletURL.setParameter("tabs1", tabs1);
portletURL.setParameter("tabs2", tabs2);
portletURL.setParameter("roleId", String.valueOf(role.getRoleId()));
portletURL.setParameter("portletResource", portletResource);

PortletURL addPermissionsURL = renderResponse.createRenderURL();

addPermissionsURL.setWindowState(WindowState.MAXIMIZED);

addPermissionsURL.setParameter("struts_action", "/enterprise_admin/edit_role_permissions");
addPermissionsURL.setParameter(Constants.CMD, Constants.EDIT);
addPermissionsURL.setParameter("tabs1", "roles");
addPermissionsURL.setParameter("redirect", currentURL);
addPermissionsURL.setParameter("roleId", String.valueOf(role.getRoleId()));

int totalSteps = 0;

if (portletResource.equals(PortletKeys.PORTAL)) {
	totalSteps = 1;
}
else if (role.getType() == RoleImpl.TYPE_REGULAR) {
	totalSteps = 2;
}
else if ((role.getType() == RoleImpl.TYPE_COMMUNITY) || (role.getType() == RoleImpl.TYPE_ORGANIZATION)) {
	totalSteps = 2;
}

// Breadcrumbs

PortletURL breadcrumbsURL = renderResponse.createRenderURL();

breadcrumbsURL.setWindowState(WindowState.MAXIMIZED);

breadcrumbsURL.setParameter("struts_action", "/enterprise_admin/view");
breadcrumbsURL.setParameter("tabs1", tabs1);
breadcrumbsURL.setParameter("roleId", String.valueOf(role.getRoleId()));

String breadcrumbs = "<a href=\"" + breadcrumbsURL.toString() + "\">" + LanguageUtil.get(pageContext, "roles") + "</a> &raquo; ";

breadcrumbsURL.setParameter("struts_action", "/enterprise_admin/edit_role_permissions");
breadcrumbsURL.setParameter(Constants.CMD, Constants.VIEW);

breadcrumbs += "<a href=\"" + breadcrumbsURL.toString() + "\">" + role.getName() + "</a>";

breadcrumbsURL.setParameter(Constants.CMD, Constants.EDIT);

if (!cmd.equals(Constants.VIEW) && Validator.isNotNull(portletResource)) {
	breadcrumbsURL.setParameter("portletResource", portletResource);

	breadcrumbs += " &raquo; <a href=\"" + breadcrumbsURL.toString() + "\">" + portletResourceLabel + "</a>";
}

request.setAttribute("edit_role_permissions.jsp-role", role);

request.setAttribute("edit_role_permissions.jsp-portletResource", portletResource);
%>

<script type="text/javascript">
	function <portlet:namespace />addPermissions(type) {
		var addPermissionsURL = "<%= addPermissionsURL.toString() %>";

		if (type == "portal") {
			addPermissionsURL += "&<portlet:namespace />portletResource=<%= PortletKeys.PORTAL %>";
		}

		self.location = addPermissionsURL;
	}

	function <portlet:namespace />removeGroup(pos, target) {
		var selectedGroupIds = document.<portlet:namespace />fm['<portlet:namespace />groupIds' + target].value.split(",");
		var selectedGroupNames = document.<portlet:namespace />fm['<portlet:namespace />groupNames' + target].value.split("@@");

		selectedGroupIds.splice(pos, 1);
		selectedGroupNames.splice(pos, 1);

		<portlet:namespace />updateGroups(selectedGroupIds, selectedGroupNames, target);
	}

	function <portlet:namespace />selectGroup(groupId, name, target) {
		var selectedGroupIds = [];
		var selectedGroupIdsField = document.<portlet:namespace />fm['<portlet:namespace />groupIds' + target].value;

		if (selectedGroupIdsField != "") {
			selectedGroupIds = selectedGroupIdsField.split(",");
		}

		var selectedGroupNames = [];
		var selectedGroupNamesField = document.<portlet:namespace />fm['<portlet:namespace />groupNames' + target].value;

		if (selectedGroupNamesField != "") {
			selectedGroupNames = selectedGroupNamesField.split("@@");
		}

		selectedGroupIds.push(groupId);
		selectedGroupNames.push(name);

		<portlet:namespace />updateGroups(selectedGroupIds, selectedGroupNames, target);
	}

	function <portlet:namespace />toggleGroupDiv(target) {
		var scope = document.<portlet:namespace />fm['<portlet:namespace />scope' + target].value;

		if (scope == '<%= ResourceImpl.SCOPE_GROUP %>') {
			document.getElementById("<portlet:namespace />groupDiv" + target).style.display = "";
		}
		else {
			document.getElementById("<portlet:namespace />groupDiv" + target).style.display = "none";
		}
	}

	function <portlet:namespace />updateActions() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "actions";
		document.<portlet:namespace />fm.<portlet:namespace />redirect.value = "<%= portletURL.toString() %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />updateGroups(selectedGroupIds, selectedGroupNames, target) {
		document.<portlet:namespace />fm['<portlet:namespace />groupIds' + target].value = selectedGroupIds.join(',');
		document.<portlet:namespace />fm['<portlet:namespace />groupNames' + target].value = selectedGroupNames.join('@@');

		var nameEl = document.getElementById("<portlet:namespace />groupHTML" + target);

		var groupsHTML = '';

		for (var i = 0; i < selectedGroupIds.length; i++) {
			var id = selectedGroupIds[i];
			var name = selectedGroupNames[i];

			groupsHTML += '<span>' + name + '&nbsp;[<a href="javascript: <portlet:namespace />removeGroup(' + i + ', \'' + target + '\' );">x</a>]</span>';

			if (i < selectedGroupIds.length) {
				groupsHTML += ',&nbsp;'
			}
		}

		nameEl.innerHTML = groupsHTML;
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_role_permissions" /></portlet:actionURL>" id="<portlet:namespace />fm" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="" />
<input name="<portlet:namespace />roleId" type="hidden" value="<%= role.getRoleId() %>" />
<input name="<portlet:namespace />portletResource" type="hidden" value="<%= portletResource %>" />
<input name="<portlet:namespace />modelResources" type="hidden" value='<%= (modelResources == null) ? "" : StringUtil.merge(modelResources) %>' />

<c:choose>
	<c:when test="<%= cmd.equals(Constants.VIEW) %>">

		<%
		portletURL.setParameter(Constants.CMD, Constants.VIEW);
		%>

		<div class="breadcrumbs">
			<%= breadcrumbs %>
		</div>

		<liferay-ui:success key="permissionDeleted" message="the-permission-was-deleted" />
		<liferay-ui:success key="permissionsUpdated" message="the-role-permissions-were-updated" />

		<%
		List headerNames = new ArrayList();

		headerNames.add("portlet");
		headerNames.add("resource");
		headerNames.add("action");

		if ((role.getType() == RoleImpl.TYPE_REGULAR)) {
			headerNames.add("scope");
			headerNames.add("community");
		}

		headerNames.add(StringPool.BLANK);

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, "this-role-does-have-any-permissions");

		List permissions = PermissionLocalServiceUtil.getRolePermissions(role.getRoleId());

		List permissionsDisplay = new ArrayList(permissions.size());

		for (int i = 0; i < permissions.size(); i++) {
			Permission permission = (Permission)permissions.get(i);

			Resource resource = ResourceLocalServiceUtil.getResource(permission.getResourceId());

			String curPortletName = null;
			String curPortletLabel = null;
			String curModelName = null;
			String curModelLabel = null;
			String actionId = permission.getActionId();
			String actionLabel = ResourceActionsUtil.getAction(pageContext, actionId);

			if (PortletLocalServiceUtil.hasPortlet(company.getCompanyId(), resource.getName())) {
				curPortletName = resource.getName();
				curModelName = StringPool.BLANK;
				curModelLabel = StringPool.BLANK;
			}
			else {
				curModelName = resource.getName();
				curModelLabel = ResourceActionsUtil.getModelResource(pageContext, curModelName);

				List portletResources = ResourceActionsUtil.getModelPortletResources(curModelName);

				if (portletResources.size() > 0) {
					curPortletName = (String)portletResources.get(0);
				}
			}

			if (curPortletName == null) {
				continue;
			}

			Portlet portlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), curPortletName);

			curPortletLabel = PortalUtil.getPortletTitle(portlet, application, locale);

			PermissionDisplay permissionDisplay = new PermissionDisplay(permission, resource, curPortletName, curPortletLabel, curModelName, curModelLabel, actionId, actionLabel);

			if (!permissionsDisplay.contains(permissionDisplay)) {
				permissionsDisplay.add(permissionDisplay);
			}
		}

		Collections.sort(permissionsDisplay);

		int total = permissionsDisplay.size();

		searchContainer.setTotal(total);

		List results = ListUtil.subList(permissionsDisplay, searchContainer.getStart(), searchContainer.getEnd());

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			PermissionDisplay permissionDisplay = (PermissionDisplay) results.get(i);

			Permission permission = permissionDisplay.getPermission();
			Resource resource = permissionDisplay.getResource();
			String curPortletName = permissionDisplay.getPortletName();
			String curPortletLabel = permissionDisplay.getPortletLabel();
			String curModelName = permissionDisplay.getModelName();
			String curModelLabel = permissionDisplay.getModelLabel();
			String actionId = permissionDisplay.getActionId();
			String actionLabel = permissionDisplay.getActionLabel();

			ResultRow row = new ResultRow(new Object[]{permission, role}, actionId, i);

			boolean hasCompanyScope = (role.getType() == RoleImpl.TYPE_REGULAR) && PermissionLocalServiceUtil.hasRolePermission(role.getRoleId(), company.getCompanyId(), resource.getName(), ResourceImpl.SCOPE_COMPANY, actionId);
			boolean hasGroupTemplateScope = ((role.getType() == RoleImpl.TYPE_COMMUNITY) || (role.getType() == RoleImpl.TYPE_ORGANIZATION)) && PermissionLocalServiceUtil.hasRolePermission(role.getRoleId(), company.getCompanyId(), resource.getName(), ResourceImpl.SCOPE_GROUP_TEMPLATE, actionId);
			boolean hasGroupScope = (role.getType() == RoleImpl.TYPE_REGULAR) && PermissionLocalServiceUtil.hasRolePermission(role.getRoleId(), company.getCompanyId(), resource.getName(), ResourceImpl.SCOPE_GROUP, actionId);

			PortletURL editResourcePermissionsURL = renderResponse.createRenderURL();

			editResourcePermissionsURL.setWindowState(WindowState.MAXIMIZED);

			editResourcePermissionsURL.setParameter("struts_action", "/enterprise_admin/edit_role_permissions");
			editResourcePermissionsURL.setParameter("tabs1", "roles");
			editResourcePermissionsURL.setParameter("redirect", currentURL);
			editResourcePermissionsURL.setParameter("roleId", String.valueOf(role.getRoleId()));
			editResourcePermissionsURL.setParameter("portletResource", curPortletName);

			row.addText(curPortletLabel, editResourcePermissionsURL);
			row.addText(curModelLabel);
			row.addText(actionLabel);

			if (hasCompanyScope) {
				row.addText(LanguageUtil.get(pageContext, "enterprise"));
				row.addText(StringPool.BLANK);
			}
			else if (hasGroupTemplateScope) {
			}
			else if (hasGroupScope) {
				row.addText(LanguageUtil.get(pageContext, "community"));

				long groupId = GetterUtil.getLong(resource.getPrimKey());

				Group group = GroupLocalServiceUtil.getGroup(groupId);

				row.addText(group.getName());
			}

			// Action

			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/enterprise_admin/permission_action.jsp");

			if (hasCompanyScope || hasGroupTemplateScope || hasGroupScope) {
				resultRows.add(row);
			}
		}
		%>

		<input type="button" value="<liferay-ui:message key="add-portlet-permissions" />" onclick="<portlet:namespace />addPermissions('portlet');" />

		<c:if test="<%= role.getType() == RoleImpl.TYPE_REGULAR%>">
			<input type="button" value="<liferay-ui:message key="add-portal-permissions" />" onclick="<portlet:namespace />addPermissions('portal');" />
		</c:if>

		<br /><br />

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
	<c:when test="<%= Validator.isNotNull(portletResource) %>">
		<liferay-ui:error key="missingGroupIdsForAction" message="select-at-least-one-community-for-each-action-with-scope-set-to-communities" />

		<div class="portlet-section-body" style="border: 1px solid; padding: 5px;">
			<c:choose>
				<c:when test="<%= portletResource.equals(PortletKeys.PORTAL) %>">
					<%= LanguageUtil.format(pageContext, "step-x-of-x", new String[] {"1", String.valueOf(totalSteps)}) %>

					<%= LanguageUtil.format(pageContext, "select-the-scope-of-the-action-that-this-role-can-perform-on-the-portal", portletResourceLabel) %>
				</c:when>
				<c:when test="<%= role.getType() == RoleImpl.TYPE_REGULAR %>">
					<%= LanguageUtil.format(pageContext, "step-x-of-x", new String[] {"2", String.valueOf(totalSteps)}) %>

					<%= LanguageUtil.format(pageContext, "select-the-scope-of-the-action-that-this-role-can-perform-on-each-resource-of-x-portlet", portletResourceLabel) %>
				</c:when>
				<c:otherwise>
					<%= LanguageUtil.format(pageContext, "step-x-of-x", new String[] {"2", String.valueOf(totalSteps)}) %>

					<%= LanguageUtil.format(pageContext, "select-the-actions-that-this-role-can-perform-on-each-resource-of-x-portlet", portletResourceLabel) %>
				</c:otherwise>
			</c:choose>
		</div>

		<br />

		<div class="breadcrumbs">
			<%= breadcrumbs %>
		</div>

		<c:if test="<%= (role.getType() == RoleImpl.TYPE_COMMUNITY) || (role.getType() == RoleImpl.TYPE_ORGANIZATION) %>">
			<table class="lfr-table">
			<tr>
				<td>
					<liferay-ui:message key="all" />
				</td>
				<td>
					<input name="<portlet:namespace />actionAllBox" type="checkbox" />
				</td>
			</tr>
			</table>

			<br />
		</c:if>

		<fieldset>
			<legend><%= portletResourceLabel %></legend>

			<%
			request.setAttribute("edit_role_permissions.jsp-curPortletResource", portletResource);
			%>

			<liferay-util:include page="/html/portlet/enterprise_admin/edit_role_permissions_resource.jsp" />
		</fieldset>

		<c:if test="<%= (modelResources != null) && (modelResources.size() > 0) %>">

			<%
			SearchContainer searchContainer = new SearchContainer();

			List headerNames = new ArrayList();

			headerNames.add("name");

			searchContainer.setHeaderNames(headerNames);

			Collections.sort(modelResources, new ModelResourceComparator(company.getCompanyId(), locale));

			List resultRows = searchContainer.getResultRows();

			for (int i = 0; i < modelResources.size(); i++) {
				String curModelResource = (String)modelResources.get(i);

				String curModelResourceName = ResourceActionsUtil.getModelResource(pageContext, curModelResource);

				boolean selectable = true;

				if ((role.getType() != RoleImpl.TYPE_REGULAR) && ResourceActionsUtil.isPortalModelResource(curModelResource)) {
					selectable = false;
				}
				%>

				<br />

				<fieldset>
					<legend><%= curModelResourceName %></legend>

					<c:choose>
						<c:when test="<%= selectable %>">

							<%
							request.removeAttribute("edit_role_permissions.jsp-curPortletResource");
							request.setAttribute("edit_role_permissions.jsp-curModelResource", curModelResource);
							request.setAttribute("edit_role_permissions.jsp-curModelResourceName", curModelResourceName);
							%>

							<liferay-util:include page="/html/portlet/enterprise_admin/edit_role_permissions_resource.jsp" />
						</c:when>
						<c:otherwise>
							<liferay-ui:message key="not-available-for-this-type-of-role" />

							<br />
						</c:otherwise>
					</c:choose>
				</fieldset>

			<%
			}
			%>

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
		</c:if>

		<br />

		<input type="button" value="<liferay-ui:message key="save" />" onclick="<portlet:namespace />updateActions();" />

		<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

		<script type="text/javascript">
			jQuery(
				function() {
					var form = jQuery("#<portlet:namespace />fm");

					var allBox = form.find("input[@name=<portlet:namespace />actionAllBox]");
					var inputs = form.find("input[@type=checkbox]").not(allBox);

					var inputsCount = inputs.length;

					if (inputs.not(":checked").length == 0) {
						allBox.attr("checked", true);
					}

					allBox.click(
						function() {
							var allBoxChecked = this.checked;

							if (allBoxChecked) {
								var uncheckedInputs = inputs.not(":checked");

								uncheckedInputs.trigger("click");
							}
							else {
								var checkedInputs = inputs.filter(":checked");

								checkedInputs.trigger("click");
							}

							allBox.attr("checked", allBoxChecked);
						}
					);

					inputs.click(
						function() {
							var uncheckedCount = inputs.not(":checked").length;

							if (this.checked) {
								if (uncheckedCount == 0) {
									allBox.attr("checked", true);
								}
							}
							else {
								if (inputsCount > uncheckedCount) {
									allBox.attr("checked", false);
								}
							}
						}
					);
				}
			);
		</script>
	</c:when>
	<c:otherwise>

		<%
		List headerNames = new ArrayList();

		headerNames.add("portlet");

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

		List portlets = PortletLocalServiceUtil.getPortlets(company.getCompanyId(), false, false);

		Collections.sort(portlets, new PortletTitleComparator(application, locale));

		int total = portlets.size();

		searchContainer.setTotal(total);

		List results = ListUtil.subList(portlets, searchContainer.getStart(), searchContainer.getEnd());

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			Portlet portlet = (Portlet)results.get(i);

			ResultRow row = new ResultRow(portlet, portlet.getId(), i);

			PortletURL rowURL = renderResponse.createRenderURL();

			rowURL.setWindowState(WindowState.MAXIMIZED);

			rowURL.setParameter("struts_action", "/enterprise_admin/edit_role_permissions");
			rowURL.setParameter("redirect", redirect);
			rowURL.setParameter("roleId", String.valueOf(role.getRoleId()));
			rowURL.setParameter("portletResource", portlet.getPortletId());

			// Name

			row.addText(PortalUtil.getPortletTitle(portlet, application, locale), rowURL);

			// Add result row

			resultRows.add(row);
		}
		%>

		<div class="portlet-section-body" style="border: 1px solid; padding: 5px;">
			<%= LanguageUtil.format(pageContext, "step-x-of-x", new String[] {"1", String.valueOf(totalSteps)}) %>

			<liferay-ui:message key="choose-a-portlet" />
		</div>

		<br />

		<div class="breadcrumbs">
			<%= breadcrumbs %>
		</div>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:otherwise>
</c:choose>

</form>