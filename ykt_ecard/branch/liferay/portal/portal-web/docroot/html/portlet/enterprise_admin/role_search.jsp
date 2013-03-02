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
String strutsAction = ParamUtil.getString(request, "struts_action");

RoleSearch searchContainer = (RoleSearch)request.getAttribute("liferay-ui:search:searchContainer");

RoleDisplayTerms displayTerms = (RoleDisplayTerms)searchContainer.getDisplayTerms();
%>

<div>
	<label for="<portlet:namespace /><%= displayTerms.NAME %>"><liferay-ui:message key="search" /></label>

	<input id="<portlet:namespace /><%= displayTerms.NAME %>" name="<portlet:namespace /><%= displayTerms.NAME %>" size="30" type="text" value="<%= Html.escape(displayTerms.getName()) %>" />
</div>

<br />

<div>
	<input type="submit" value="<liferay-ui:message key="search-roles" />" />

	<c:if test='<%= portletName.equals(PortletKeys.ENTERPRISE_ADMIN) && (Validator.isNull(strutsAction) || strutsAction.equals("/enterprise_admin/view")) && PortalPermissionUtil.contains(permissionChecker, ActionKeys.ADD_ROLE) %>'>
		<input type="button" value="<liferay-ui:message key="add-role" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_role" /></portlet:renderURL>&<portlet:namespace />redirect=' + encodeURIComponent(document.<portlet:namespace />fm.<portlet:namespace />rolesRedirect.value);" />
	</c:if>
</div>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= displayTerms.NAME %>);
	</script>
</c:if>