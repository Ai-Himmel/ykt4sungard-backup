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

<%@ include file="/html/portlet/journal/init.jsp" %>

<%
ResultRow row = (ResultRow)request.getAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW);

JournalStructure structure = (JournalStructure)row.getObject();
%>

<liferay-ui:icon-menu>
	<c:if test="<%= JournalStructurePermission.contains(permissionChecker, structure, ActionKeys.UPDATE) %>">
		<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="editURL">
			<portlet:param name="struts_action" value="/journal/edit_structure" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="groupId" value="<%= String.valueOf(structure.getGroupId()) %>" />
			<portlet:param name="structureId" value="<%= structure.getStructureId() %>" />
		</portlet:renderURL>

		<liferay-ui:icon image="edit" url="<%= editURL %>" />
	</c:if>

	<c:if test="<%= JournalStructurePermission.contains(permissionChecker, structure, ActionKeys.PERMISSIONS) %>">
		<liferay-security:permissionsURL
			modelResource="<%= JournalStructure.class.getName() %>"
			modelResourceDescription="<%= structure.getName() %>"
			resourcePrimKey="<%= String.valueOf(structure.getId()) %>"
			var="permissionsURL"
		/>

		<liferay-ui:icon image="permissions" url="<%= permissionsURL %>" />
	</c:if>

	<c:if test="<%= PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.JOURNAL, ActionKeys.ADD_ARTICLE) %>">
		<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="addArticleURL">
			<portlet:param name="struts_action" value="/journal/edit_article" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="groupId" value="<%= String.valueOf(structure.getGroupId()) %>" />
			<portlet:param name="structureId" value="<%= structure.getStructureId() %>" />
		</portlet:renderURL>

		<liferay-ui:icon image="add_article" message="add-article" url="<%= addArticleURL %>" />
	</c:if>

	<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="viewArticleURL">
		<portlet:param name="struts_action" value="/journal/view" />
		<portlet:param name="tabs1" value="articles" />
		<portlet:param name="groupId" value="<%= String.valueOf(structure.getGroupId()) %>" />
		<portlet:param name="structureId" value="<%= structure.getStructureId() %>" />
	</portlet:renderURL>

	<liferay-ui:icon image="view_articles" message="view-articles" url="<%= viewArticleURL %>" />

	<c:if test="<%= PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.JOURNAL, ActionKeys.ADD_TEMPLATE) %>">
		<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="addTemplateURL">
			<portlet:param name="struts_action" value="/journal/edit_template" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="groupId" value="<%= String.valueOf(structure.getGroupId()) %>" />
			<portlet:param name="structureId" value="<%= structure.getStructureId() %>" />
		</portlet:renderURL>

		<liferay-ui:icon image="add_template" message="add-template" url="<%= addTemplateURL %>" />
	</c:if>

	<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="viewTemplateURL">
		<portlet:param name="struts_action" value="/journal/view" />
		<portlet:param name="tabs1" value="templates" />
		<portlet:param name="groupId" value="<%= String.valueOf(structure.getGroupId()) %>" />
		<portlet:param name="structureId" value="<%= structure.getStructureId() %>" />
	</portlet:renderURL>

	<liferay-ui:icon image="view_templates" message="view-templates" url="<%= viewTemplateURL %>" />

	<c:if test="<%= JournalStructurePermission.contains(permissionChecker, structure, ActionKeys.DELETE) %>">
		<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="deleteURL">
			<portlet:param name="struts_action" value="/journal/edit_structure" />
			<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.DELETE %>" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="groupId" value="<%= String.valueOf(structure.getGroupId()) %>" />
			<portlet:param name="deleteStructureIds" value="<%= structure.getStructureId() %>" />
		</portlet:actionURL>

		<liferay-ui:icon-delete url="<%= deleteURL %>" />
	</c:if>
</liferay-ui:icon-menu>