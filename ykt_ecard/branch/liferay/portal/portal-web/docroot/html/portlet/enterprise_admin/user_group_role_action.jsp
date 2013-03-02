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
ResultRow row = (ResultRow)request.getAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW);

Object[] objArray = (Object[])row.getObject();

User user2 = (User)objArray[0];
Group group = (Group)objArray[1];
Role role = (Role)objArray[2];
String redirect = (String)objArray[3];
%>

<liferay-ui:icon-menu>
	<c:if test="<%= (!portletName.equals(PortletKeys.MY_ACCOUNT)) && (!role.getName().equals(RoleImpl.COMMUNITY_MEMBER)) %>">
		<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="portletURL">
			<portlet:param name="struts_action" value="/enterprise_admin/edit_user_roles" />
			<portlet:param name="<%= Constants.CMD %>" value="user_group_role_users" />
			<portlet:param name="redirect" value="<%= redirect %>" />
			<portlet:param name="removeUserIds" value="<%= String.valueOf(user2.getUserId()) %>" />
			<portlet:param name="groupId" value="<%= String.valueOf(group.getGroupId()) %>" />
			<portlet:param name="roleId" value="<%= String.valueOf(role.getRoleId()) %>" />
		</portlet:actionURL>

		<liferay-ui:icon image="unlink" message="remove" url="<%= portletURL %>" />
	</c:if>
</liferay-ui:icon-menu>