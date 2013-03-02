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

<%@ include file="/html/portlet/document_library/init.jsp" %>

<%
ResultRow row = (ResultRow)request.getAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW);

Object result = row.getObject();

DLFileEntry fileEntry = null;
DLFileShortcut fileShortcut = null;

if (result instanceof DLFileEntry) {
	fileEntry = (DLFileEntry)result;
}
else {
	fileShortcut = (DLFileShortcut)result;
}
%>

<liferay-ui:icon-menu>
	<c:choose>
		<c:when test="<%= fileEntry != null %>">
			<c:if test="<%= DLFileEntryPermission.contains(permissionChecker, fileEntry, ActionKeys.VIEW) %>">
				<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="viewURL">
					<portlet:param name="struts_action" value="/document_library/view_file_entry" />
					<portlet:param name="redirect" value="<%= currentURL %>" />
					<portlet:param name="folderId" value="<%= String.valueOf(fileEntry.getFolderId()) %>" />
					<portlet:param name="name" value="<%= fileEntry.getName() %>" />
				</portlet:renderURL>

				<liferay-ui:icon image="view" url="<%= viewURL %>" />
			</c:if>

			<c:if test="<%= DLFileEntryPermission.contains(permissionChecker, fileEntry, ActionKeys.UPDATE) %>">
				<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="editURL">
					<portlet:param name="struts_action" value="/document_library/edit_file_entry" />
					<portlet:param name="redirect" value="<%= currentURL %>" />
					<portlet:param name="folderId" value="<%= String.valueOf(fileEntry.getFolderId()) %>" />
					<portlet:param name="name" value="<%= fileEntry.getName() %>" />
				</portlet:renderURL>

				<liferay-ui:icon image="edit" url="<%= editURL %>" />
			</c:if>

			<c:if test="<%= DLFileEntryPermission.contains(permissionChecker, fileEntry, ActionKeys.PERMISSIONS) %>">
				<liferay-security:permissionsURL
					modelResource="<%= DLFileEntry.class.getName() %>"
					modelResourceDescription="<%= fileEntry.getName() %>"
					resourcePrimKey="<%= String.valueOf(fileEntry.getFileEntryId()) %>"
					var="permissionsURL"
				/>

				<liferay-ui:icon image="permissions" url="<%= permissionsURL %>" />
			</c:if>

			<c:if test="<%= DLFileEntryPermission.contains(permissionChecker, fileEntry, ActionKeys.DELETE) %>">
				<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="deleteURL">
					<portlet:param name="struts_action" value="/document_library/edit_file_entry" />
					<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.DELETE %>" />
					<portlet:param name="redirect" value="<%= currentURL %>" />
					<portlet:param name="folderId" value="<%= String.valueOf(fileEntry.getFolderId()) %>" />
					<portlet:param name="name" value="<%= fileEntry.getName() %>" />
				</portlet:actionURL>

				<liferay-ui:icon-delete url="<%= deleteURL %>" />
			</c:if>
		</c:when>
		<c:otherwise>
			<c:if test="<%= DLFileShortcutPermission.contains(permissionChecker, fileShortcut, ActionKeys.VIEW) %>">
				<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="viewShortcutURL">
					<portlet:param name="struts_action" value="/document_library/view_file_shortcut" />
					<portlet:param name="redirect" value="<%= currentURL %>" />
					<portlet:param name="fileShortcutId" value="<%= String.valueOf(fileShortcut.getFileShortcutId()) %>" />
				</portlet:renderURL>

				<liferay-ui:icon image="view" url="<%= viewShortcutURL %>" />
			</c:if>

			<c:if test="<%= DLFileShortcutPermission.contains(permissionChecker, fileShortcut, ActionKeys.UPDATE) %>">
				<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="editShortcutURL">
					<portlet:param name="struts_action" value="/document_library/edit_file_shortcut" />
					<portlet:param name="redirect" value="<%= currentURL %>" />
					<portlet:param name="fileShortcutId" value="<%= String.valueOf(fileShortcut.getFileShortcutId()) %>" />
				</portlet:renderURL>

				<liferay-ui:icon image="edit" url="<%= editShortcutURL %>" />
			</c:if>

			<c:if test="<%= DLFileShortcutPermission.contains(permissionChecker, fileShortcut, ActionKeys.PERMISSIONS) %>">
				<liferay-security:permissionsURL
					modelResource="<%= DLFileShortcut.class.getName() %>"
					modelResourceDescription="<%= fileShortcut.getToName() %>"
					resourcePrimKey="<%= String.valueOf(fileShortcut.getFileShortcutId()) %>"
					var="shortcutPermissionsURL"
				/>

				<liferay-ui:icon image="permissions" url="<%= shortcutPermissionsURL %>" />
			</c:if>

			<c:if test="<%= DLFileShortcutPermission.contains(permissionChecker, fileShortcut, ActionKeys.DELETE) %>">
				<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="deleteShortcutURL">
					<portlet:param name="struts_action" value="/document_library/edit_file_shortcut" />
					<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.DELETE %>" />
					<portlet:param name="redirect" value="<%= currentURL %>" />
					<portlet:param name="fileShortcutId" value="<%= String.valueOf(fileShortcut.getFileShortcutId()) %>" />
				</portlet:actionURL>

				<liferay-ui:icon-delete url="<%= deleteShortcutURL %>" />
			</c:if>
		</c:otherwise>
	</c:choose>
</liferay-ui:icon-menu>