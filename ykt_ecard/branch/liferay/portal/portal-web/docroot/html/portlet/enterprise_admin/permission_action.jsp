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

Permission permission = (Permission)objArray[0];
Role role = (Role)objArray[1];
%>

<liferay-ui:icon-menu>
	<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="deletePermissionURL">
		<portlet:param name="struts_action" value="/enterprise_admin/edit_role_permissions" />
		<portlet:param name="<%= Constants.CMD %>" value="delete_permission" />
		<portlet:param name="redirect" value="<%= currentURL %>" />
		<portlet:param name="roleId" value="<%= String.valueOf(role.getRoleId()) %>" />
		<portlet:param name="permissionId" value="<%= String.valueOf(permission.getPermissionId()) %>" />
	</portlet:actionURL>

	<liferay-ui:icon image="delete" url="<%= deletePermissionURL %>" />
</liferay-ui:icon-menu>