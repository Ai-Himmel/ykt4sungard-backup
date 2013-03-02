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
String tabs1 = ParamUtil.getString(request, "tabs1", "communities-owned");

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/communities/view");
portletURL.setParameter("tabs1", tabs1);

pageContext.setAttribute("portletURL", portletURL);
%>

<liferay-ui:success key="membership_request_sent" message="your-request-was-sent-you-will-receive-a-reply-by-email" />

<form action="<%= portletURL.toString() %>" method="get" name="<portlet:namespace />fm">
<liferay-portlet:renderURLParams varImpl="portletURL" />

<liferay-ui:tabs
	names="communities-owned,communities-joined,available-communities,all-communities"
	url="<%= portletURL.toString() %>"
/>

<%
GroupSearch searchContainer = new GroupSearch(renderRequest, portletURL);
%>

<liferay-ui:search-form
	page="/html/portlet/enterprise_admin/group_search.jsp"
	searchContainer="<%= searchContainer %>"
/>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">

	<%
	GroupSearchTerms searchTerms = (GroupSearchTerms)searchContainer.getSearchTerms();

	LinkedHashMap groupParams = new LinkedHashMap();

	if (tabs1.equals("communities-owned")) {
		Role role = RoleLocalServiceUtil.getRole(company.getCompanyId(), RoleImpl.COMMUNITY_OWNER);

		List userGroupRole = new ArrayList();

		userGroupRole.add(new Long(user.getUserId()));
		userGroupRole.add(new Long(role.getRoleId()));

		groupParams.put("userGroupRole", userGroupRole);
		//groupParams.put("active", Boolean.TRUE);
	}
	else if (tabs1.equals("communities-joined")) {
		groupParams.put("usersGroups", new Long(user.getUserId()));
		//groupParams.put("active", Boolean.TRUE);
	}
	else if (tabs1.equals("available-communities")) {
		List types = new ArrayList();

		types.add(new Integer(GroupImpl.TYPE_COMMUNITY_OPEN));
		types.add(new Integer(GroupImpl.TYPE_COMMUNITY_RESTRICTED));

		groupParams.put("types", types);
		groupParams.put("active", Boolean.TRUE);
	}

	int total = GroupLocalServiceUtil.searchCount(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), groupParams);

	searchContainer.setTotal(total);

	List results = GroupLocalServiceUtil.search(company.getCompanyId(), searchTerms.getName(), searchTerms.getDescription(), groupParams, searchContainer.getStart(), searchContainer.getEnd(), searchContainer.getOrderByComparator());

	searchContainer.setResults(results);
	%>

	<div class="separator"><!-- --></div>

	<liferay-ui:error exception="<%= NoSuchLayoutSetException.class %>">

		<%
		NoSuchLayoutSetException nslse = (NoSuchLayoutSetException)errorException;

		PKParser pkParser = new PKParser(nslse.getMessage());

		long groupId = pkParser.getLong("groupId");

		Group group = GroupLocalServiceUtil.getGroup(groupId);
		%>

		<%= LanguageUtil.format(pageContext, "community-x-does-not-have-any-private-pages", group.getName()) %>
	</liferay-ui:error>

	<liferay-ui:error exception="<%= RequiredGroupException.class %>" message="the-group-cannot-be-deleted-because-it-is-a-required-system-group" />

	<%
	List headerNames = new ArrayList();

	headerNames.add("name");
	headerNames.add("type");
	headerNames.add("members");
	headerNames.add("online-now");

	if (tabs1.equals("communities-owned") || tabs1.equals("communities-joined") || tabs1.equals("all-communities")) {
		headerNames.add("active");
	}

	if (tabs1.equals("communities-owned")) {
		headerNames.add("pending-requests");
	}

	headerNames.add(StringPool.BLANK);

	searchContainer.setHeaderNames(headerNames);

	List resultRows = searchContainer.getResultRows();

	for (int i = 0; i < results.size(); i++) {
		Group group = (Group)results.get(i);

		group = group.toEscapedModel();

		ResultRow row = new ResultRow(new Object[] {group, tabs1}, group.getGroupId(), i);

		PortletURL rowURL = renderResponse.createActionURL();

		rowURL.setWindowState(WindowState.NORMAL);

		rowURL.setParameter("struts_action", "/communities/page");
		rowURL.setParameter("redirect", currentURL);

		// Name

		StringMaker sm = new StringMaker();

		sm.append(group.getName());

		int publicLayoutsPageCount = group.getPublicLayoutsPageCount();
		int privateLayoutsPageCount = group.getPrivateLayoutsPageCount();

		Group stagingGroup = null;

		if (group.hasStagingGroup()) {
			stagingGroup = group.getStagingGroup();
		}

		if ((tabs1.equals("communities-owned") || tabs1.equals("communities-joined")) &&
			((publicLayoutsPageCount > 0) || (privateLayoutsPageCount > 0))) {

			sm.append("<br />");

			if (publicLayoutsPageCount > 0) {
				rowURL.setParameter("groupId", String.valueOf(group.getGroupId()));
				rowURL.setParameter("privateLayout", Boolean.FALSE.toString());

				sm.append("<a href=\"");
				sm.append(rowURL.toString());
				sm.append("\">");
				sm.append(LanguageUtil.get(pageContext, "public-pages"));
				sm.append(" - ");
				sm.append(LanguageUtil.get(pageContext, "live"));
				sm.append(" (");
				sm.append(group.getPublicLayoutsPageCount());
				sm.append(")");
				sm.append("</a>");
			}
			else {
				sm.append(LanguageUtil.get(pageContext, "public-pages"));
				sm.append(" (0)");
			}

			if ((stagingGroup != null) && GroupPermissionUtil.contains(permissionChecker, group.getGroupId(), ActionKeys.MANAGE_LAYOUTS)) {
				rowURL.setParameter("groupId", String.valueOf(stagingGroup.getGroupId()));
				rowURL.setParameter("privateLayout", Boolean.FALSE.toString());

				if (stagingGroup.getPublicLayoutsPageCount() > 0) {
					sm.append(" / ");
					sm.append("<a href=\"");
					sm.append(rowURL.toString());
					sm.append("\">");
					sm.append(LanguageUtil.get(pageContext, "staging"));
					sm.append("</a>");
				}
			}

			sm.append("<br />");

			if (privateLayoutsPageCount > 0) {
				rowURL.setParameter("groupId", String.valueOf(group.getGroupId()));
				rowURL.setParameter("privateLayout", Boolean.TRUE.toString());

				sm.append("<a href=\"");
				sm.append(rowURL.toString());
				sm.append("\">");
				sm.append(LanguageUtil.get(pageContext, "private-pages"));
				sm.append(" - ");
				sm.append(LanguageUtil.get(pageContext, "live"));
				sm.append(" (");
				sm.append(group.getPrivateLayoutsPageCount());
				sm.append(")");
				sm.append("</a>");
			}
			else {
				sm.append(LanguageUtil.get(pageContext, "private-pages"));
				sm.append(" (0)");
			}

			if ((stagingGroup != null) && GroupPermissionUtil.contains(permissionChecker, group.getGroupId(), ActionKeys.MANAGE_LAYOUTS)) {
				rowURL.setParameter("groupId", String.valueOf(stagingGroup.getGroupId()));
				rowURL.setParameter("privateLayout", Boolean.TRUE.toString());

				if (stagingGroup.getPrivateLayoutsPageCount() > 0) {
					sm.append(" / ");
					sm.append("<a href=\"");
					sm.append(rowURL.toString());
					sm.append("\">");
					sm.append(LanguageUtil.get(pageContext, "staging"));
					sm.append("</a>");
				}
			}
		}

		row.addText(sm.toString());

		// Type

		row.addText(LanguageUtil.get(pageContext, group.getTypeLabel()), rowURL);

		// Members

		LinkedHashMap userParams = new LinkedHashMap();

		userParams.put("usersGroups", new Long(group.getGroupId()));

		int membersCount = UserLocalServiceUtil.searchCount(company.getCompanyId(), null, Boolean.TRUE, userParams);

		row.addText(String.valueOf(membersCount));

		// Online Now

		int onlineCount = LiveUsers.getGroupUsersCount(group.getGroupId());

		row.addText(String.valueOf(onlineCount));

		// Active

		if (tabs1.equals("communities-owned") || tabs1.equals("communities-joined") || tabs1.equals("all-communities")) {
			row.addText(LanguageUtil.get(pageContext, (group.isActive() ? "yes" : "no")));
		}

		// Restricted number of petitions

		if (tabs1.equals("communities-owned")) {
			int pendingRequests = MembershipRequestLocalServiceUtil.searchCount(group.getGroupId(), MembershipRequestImpl.STATUS_PENDING);

			if (group.getType() == GroupImpl.TYPE_COMMUNITY_RESTRICTED) {
				row.addText(Integer.toString(pendingRequests));
			}
			else {
				row.addText(StringPool.BLANK);
			}
		}

		// Action

		row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/communities/community_action.jsp");

		// Add result row

		resultRows.add(row);
	}
	%>

	<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
</c:if>

</form>