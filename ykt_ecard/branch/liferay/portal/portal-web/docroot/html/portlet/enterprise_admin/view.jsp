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
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>

<%
String tabs2 = ParamUtil.getString(request, "tabs2");
String tabs3 = ParamUtil.getString(request, "tabs3");

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/enterprise_admin/view");
portletURL.setParameter("tabs1", tabs1);
portletURL.setParameter("tabs2", tabs2);
portletURL.setParameter("tabs3", tabs3);

pageContext.setAttribute("portletURL", portletURL);

String portletURLString = portletURL.toString();

request.setAttribute("view.jsp-portletURL", portletURL);
request.setAttribute("view.jsp-portletURLString", portletURLString);
%>

<script type="text/javascript">
	function <portlet:namespace />deleteOrganizations() {
		if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-delete-the-selected-organizations") %>')) {
			document.<portlet:namespace />fm.method = "post";
			document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.DELETE %>";
			document.<portlet:namespace />fm.<portlet:namespace />redirect.value = document.<portlet:namespace />fm.<portlet:namespace />organizationsRedirect.value;
			document.<portlet:namespace />fm.<portlet:namespace />deleteOrganizationIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
			submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_organization" /></portlet:actionURL>");
		}
	}

	function <portlet:namespace />deleteUserGroups() {
		if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-delete-the-selected-user-groups") %>')) {
			document.<portlet:namespace />fm.method = "post";
			document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.DELETE %>";
			document.<portlet:namespace />fm.<portlet:namespace />redirect.value = document.<portlet:namespace />fm.<portlet:namespace />userGroupsRedirect.value;
			document.<portlet:namespace />fm.<portlet:namespace />deleteUserGroupIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
			submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_user_group" /></portlet:actionURL>");
		}
	}

	function <portlet:namespace />deleteUsers(cmd) {
		var deleteUsers = true;

		if (cmd == "<%= Constants.DEACTIVATE %>") {
			if (!confirm('<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-deactivate-the-selected-users") %>')) {
				deleteUsers = false;
			}
		}
		else if (cmd == "<%= Constants.DELETE %>") {
			if (!confirm('<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-permanently-delete-the-selected-users") %>')) {
				deleteUsers = false;
			}
		}

		if (deleteUsers) {
			document.<portlet:namespace />fm.method = "post";
			document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = cmd;
			document.<portlet:namespace />fm.<portlet:namespace />redirect.value = document.<portlet:namespace />fm.<portlet:namespace />usersRedirect.value;
			document.<portlet:namespace />fm.<portlet:namespace />deleteUserIds.value = Liferay.Util.listCheckedExcept(document.<portlet:namespace />fm, "<portlet:namespace />allRowIds");
			submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_user" /></portlet:actionURL>");
		}
	}

	function <portlet:namespace />saveCompany() {
		document.<portlet:namespace />fm.method = "post";
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.UPDATE %>";
		document.<portlet:namespace />fm.<portlet:namespace />redirect.value = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/view" /><portlet:param name="tabs1" value="<%= tabs1 %>" /><portlet:param name="tabs2" value="<%= tabs2 %>" /><portlet:param name="tabs3" value="<%= tabs3 %>" /></portlet:renderURL>";
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_company" /></portlet:actionURL>");
	}

	function <portlet:namespace />saveSettings(cmd) {
		document.<portlet:namespace />fm.method = "post";
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = cmd;
		document.<portlet:namespace />fm.<portlet:namespace />redirect.value = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/view" /><portlet:param name="tabs1" value="<%= tabs1 %>" /><portlet:param name="tabs2" value="<%= tabs2 %>" /><portlet:param name="tabs3" value="<%= tabs3 %>" /></portlet:renderURL>";
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_settings" /></portlet:actionURL>");
	}
</script>

<form action="<%= portletURLString %>" method="get" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="portletURL" />
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />tabs1" type="hidden" value="<%= tabs1 %>" />
<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
<input name="<portlet:namespace />tabs3" type="hidden" value="<%= tabs3 %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= portletURLString %>" />

<c:if test="<%= SessionErrors.contains(request,EcardConstants.USER_NOT_SELECTEDE) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="user_not_selected" />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.SHOP_BIND_SUCCESS) %>">
        <font class="portlet-msg-success"> <liferay-ui:message
                key="shop_bind_success" /> </font>
    </c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.SHOP_BIND_FAILUE) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="shop_bind_failue" />
 </font>
</c:if>

<liferay-util:include page="/html/portlet/enterprise_admin/tabs1.jsp" />

<c:choose>
	<c:when test='<%= tabs1.equals("users") %>'>
		<liferay-util:include page="/html/portlet/enterprise_admin/view_users.jsp" />
	</c:when>
	<c:when test='<%= tabs1.equals("organizations") %>'>
		<liferay-util:include page="/html/portlet/enterprise_admin/view_organizations.jsp" />
	</c:when>
	<c:when test='<%= tabs1.equals("user-groups") %>'>
		<input name="<portlet:namespace />deleteUserGroupIds" type="hidden" value="" />

		<liferay-ui:error exception="<%= RequiredUserGroupException.class %>" message="you-cannot-delete-user-groups-that-have-users" />

		<%
		UserGroupSearch searchContainer = new UserGroupSearch(renderRequest, portletURL);

		List headerNames = searchContainer.getHeaderNames();

		headerNames.add(StringPool.BLANK);

		if (portletName.equals(PortletKeys.ENTERPRISE_ADMIN) && PortalPermissionUtil.contains(permissionChecker, ActionKeys.ADD_USER_GROUP)) {
			RowChecker rowChecker = new RowChecker(renderResponse);

			searchContainer.setRowChecker(rowChecker);
		}
		%>

		<liferay-ui:search-form
			page="/html/portlet/enterprise_admin/user_group_search.jsp"
			searchContainer="<%= searchContainer %>"
		/>

		<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">

			<%
			UserGroupSearchTerms searchTerms = (UserGroupSearchTerms)searchContainer.getSearchTerms();

			int total = UserGroupLocalServiceUtil.searchCount(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), null);

			searchContainer.setTotal(total);

			List results = UserGroupLocalServiceUtil.search(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), null, searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());

			searchContainer.setResults(results);

			portletURL.setParameter(searchContainer.getCurParam(), String.valueOf(searchContainer.getCurValue()));
			%>

			<input name="<portlet:namespace />userGroupsRedirect" type="hidden" value="<%= portletURL.toString() %>" />

			<div class="separator"><!-- --></div>

			<c:if test="<%= portletName.equals(PortletKeys.ENTERPRISE_ADMIN) && PortalPermissionUtil.contains(permissionChecker, ActionKeys.ADD_USER_GROUP) %>">
				<input type="button" value="<liferay-ui:message key="delete" />" onClick="<portlet:namespace />deleteUserGroups();" />

				<br /><br />
			</c:if>

			<%
			List resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.size(); i++) {
				UserGroup userGroup = (UserGroup)results.get(i);

				ResultRow row = new ResultRow(userGroup, userGroup.getUserGroupId(), i);

				PortletURL rowURL = renderResponse.createRenderURL();

				rowURL.setWindowState(WindowState.MAXIMIZED);

				rowURL.setParameter("struts_action", "/enterprise_admin/edit_user_group");
				rowURL.setParameter("redirect", searchContainer.getIteratorURL().toString());
				rowURL.setParameter("userGroupId", String.valueOf(userGroup.getUserGroupId()));

				// Name

				row.addText(userGroup.getName(), rowURL);

				// Description

				row.addText(userGroup.getDescription(), rowURL);

				// Action

				row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/enterprise_admin/user_group_action.jsp");

				// Add result row

				resultRows.add(row);
			}
			%>

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
		</c:if>
	</c:when>
	<c:when test='<%= tabs1.equals("roles") %>'>
		<liferay-ui:error exception="<%= RequiredRoleException.class %>" message="you-cannot-delete-a-system-role" />

		<%
		RoleSearch searchContainer = new RoleSearch(renderRequest, portletURL);

		List headerNames = searchContainer.getHeaderNames();

		headerNames.add(StringPool.BLANK);
		%>

		<liferay-ui:search-form
			page="/html/portlet/enterprise_admin/role_search.jsp"
			searchContainer="<%= searchContainer %>"
		/>

		<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">

			<%
			RoleSearchTerms searchTerms = (RoleSearchTerms)searchContainer.getSearchTerms();

			int total = RoleLocalServiceUtil.searchCount(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), searchTerms.getTypeObj());

			searchContainer.setTotal(total);

			List results = RoleLocalServiceUtil.search(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), searchTerms.getTypeObj(), searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());

			searchContainer.setResults(results);

			portletURL.setParameter(searchContainer.getCurParam(), String.valueOf(searchContainer.getCurValue()));
			%>

			<input name="<portlet:namespace />rolesRedirect" type="hidden" value="<%= portletURL.toString() %>" />

			<div class="separator"><!-- --></div>

			<%
			List resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.size(); i++) {
				Role role = (Role)results.get(i);

				ResultRow row = new ResultRow(role, role.getRoleId(), i);

				PortletURL rowURL = renderResponse.createRenderURL();

				rowURL.setWindowState(WindowState.MAXIMIZED);

				rowURL.setParameter("struts_action", "/enterprise_admin/edit_role");
				rowURL.setParameter("redirect", searchContainer.getIteratorURL().toString());
				rowURL.setParameter("roleId", String.valueOf(role.getRoleId()));

				// Name

				row.addText(role.getName(), rowURL);

				// Type

				row.addText(LanguageUtil.get(pageContext, role.getTypeLabel()), rowURL);

				// Description

				row.addText(role.getDescription(), rowURL);

				// Action

				row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/enterprise_admin/role_action.jsp");

				// Add result row

				resultRows.add(row);
			}
			%>

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
		</c:if>
	</c:when>
	<c:when test='<%= tabs1.equals("password-policies") %>'>

		<%
		boolean passwordPolicyEnabled = PortalLDAPUtil.isPasswordPolicyEnabled(company.getCompanyId());
		%>

		<c:if test="<%= passwordPolicyEnabled %>">
			<liferay-ui:message key="you-are-using-ldaps-password-policy" />
		</c:if>

		<%
		PasswordPolicySearch searchContainer = new PasswordPolicySearch(renderRequest, portletURL);

		List headerNames = searchContainer.getHeaderNames();

		headerNames.add(StringPool.BLANK);
		%>

		<c:if test="<%= !passwordPolicyEnabled %>">
			<liferay-ui:search-form
				page="/html/portlet/enterprise_admin/password_policy_search.jsp"
				searchContainer="<%= searchContainer %>"
			/>
		</c:if>

		<c:if test="<%= !passwordPolicyEnabled && windowState.equals(WindowState.MAXIMIZED) %>">

			<%
			PasswordPolicySearchTerms searchTerms = (PasswordPolicySearchTerms)searchContainer.getSearchTerms();

			int total = PasswordPolicyLocalServiceUtil.searchCount(company.getCompanyId(), searchTerms.getName());

			searchContainer.setTotal(total);

			List results = PasswordPolicyLocalServiceUtil.search(company.getCompanyId(), searchTerms.getName(), searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());

			searchContainer.setResults(results);

			PortletURL passwordPoliciesRedirect = PortletURLUtil.clone(portletURL, renderResponse);

			passwordPoliciesRedirect.setParameter(searchContainer.getCurParam(), String.valueOf(searchContainer.getCurValue()));
			%>

			<input name="<portlet:namespace />passwordPoliciesRedirect" type="hidden" value="<%= passwordPoliciesRedirect.toString() %>" />

			<div class="separator"><!-- --></div>

			<%
			List resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.size(); i++) {
				PasswordPolicy passwordPolicy = (PasswordPolicy)results.get(i);

				ResultRow row = new ResultRow(passwordPolicy, passwordPolicy.getPasswordPolicyId(), i);

				PortletURL rowURL = renderResponse.createRenderURL();

				rowURL.setWindowState(WindowState.MAXIMIZED);

				rowURL.setParameter("struts_action", "/enterprise_admin/edit_password_policy");
				rowURL.setParameter("redirect", searchContainer.getIteratorURL().toString());
				rowURL.setParameter("passwordPolicyId", String.valueOf(passwordPolicy.getPasswordPolicyId()));

				// Name

				row.addText(passwordPolicy.getName(), rowURL);

				// Description

				row.addText(passwordPolicy.getDescription(), rowURL);

				// Action

				row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/enterprise_admin/password_policy_action.jsp");

				// Add result row

				resultRows.add(row);
			}
			%>

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
		</c:if>
	</c:when>
	<c:when test='<%= tabs1.equals("settings") %>'>
		<liferay-util:include page="/html/portlet/enterprise_admin/view_settings.jsp" />
	</c:when>
	<c:when test='<%= tabs1.equals("monitoring") %>'>
		<c:choose>
			<c:when test="<%= PropsValues.SESSION_TRACKER_MEMORY_ENABLED %>">
				<liferay-ui:tabs
					names="live-sessions"
					param="tabs2"
					url="<%= portletURLString %>"
				/>

				<%
				SearchContainer searchContainer = new SearchContainer();

				List headerNames = new ArrayList();

				headerNames.add("session-id");
				headerNames.add("user-id");
				headerNames.add("name");
				headerNames.add("screen-name");
				//headerNames.add("email-address");
				headerNames.add("last-request");
				headerNames.add("num-of-hits");

				searchContainer.setHeaderNames(headerNames);
				searchContainer.setEmptyResultsMessage("there-are-no-live-sessions");

				List results = new ArrayList();

				Iterator itr = LiveUsers.getSessionUsers().entrySet().iterator();

				while (itr.hasNext()) {
					Map.Entry entry = (Map.Entry)itr.next();

					results.add(entry.getValue());
				}

				Collections.sort(results, new UserTrackerModifiedDateComparator());

				List resultRows = searchContainer.getResultRows();

				for (int i = 0; i < results.size(); i++) {
					UserTracker userTracker = (UserTracker)results.get(i);

					ResultRow row = new ResultRow(userTracker, userTracker.getUserTrackerId(), i);

					PortletURL rowURL = renderResponse.createRenderURL();

					rowURL.setWindowState(WindowState.MAXIMIZED);

					rowURL.setParameter("struts_action", "/enterprise_admin/edit_session");
					rowURL.setParameter("redirect", currentURL);
					rowURL.setParameter("sessionId", userTracker.getSessionId());

					User user2 = null;

					try {
						user2 = UserLocalServiceUtil.getUserById(userTracker.getUserId());
					}
					catch (NoSuchUserException nsue) {
					}

					// Session ID

					row.addText(userTracker.getSessionId(), rowURL);

					// User ID

					row.addText(String.valueOf(userTracker.getUserId()), rowURL);

					// Name

					row.addText(((user2 != null) ? user2.getFullName() : LanguageUtil.get(pageContext, "not-available")), rowURL);

					// Screen Name

					row.addText(((user2 != null) ? user2.getScreenName() : LanguageUtil.get(pageContext, "not-available")), rowURL);

					// Email Address

					//row.addText(((user2 != null) ? user2.getEmailAddress() : LanguageUtil.get(pageContext, "not-available")), rowURL);

					// Last Request

					row.addText(dateFormatDateTime.format(userTracker.getModifiedDate()), rowURL);

					// # of Hits

					row.addText(String.valueOf(userTracker.getHits()), rowURL);

					// Add result row

					resultRows.add(row);
				}
				%>

				<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
			</c:when>
			<c:otherwise>
				<%= LanguageUtil.format(pageContext, "display-of-live-session-data-is-disabled", PropsUtil.SESSION_TRACKER_MEMORY_ENABLED) %>
			</c:otherwise>
		</c:choose>
	</c:when>
	<c:when test='<%= tabs1.equals("plugins") %>'>

		<%
		boolean installable = false;

		PortletURL installPluginsURL = null;
		%>

		<%@ include file="/html/portlet/enterprise_admin/plugins.jspf" %>
	</c:when>
</c:choose>

</form>

<%!
private static final long[] _DURATIONS = {300, 600, 1800, 3600, 7200, 10800, 21600};
%>