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
String strutsAction = ParamUtil.getString(request, "struts_action");

String tabs2 = ParamUtil.getString(request, "tabs2", "version-history");

String redirect = ParamUtil.getString(request, "redirect");

DLFileShortcut fileShortcut = (DLFileShortcut)request.getAttribute(WebKeys.DOCUMENT_LIBRARY_FILE_SHORTCUT);

long fileShortcutId = BeanParamUtil.getLong(fileShortcut, request, "fileShortcutId");
long folderId = BeanParamUtil.getLong(fileShortcut, request, "folderId");
long toGroupId = ParamUtil.getLong(request, "toGroupId");
long toFolderId = BeanParamUtil.getLong(fileShortcut, request, "toFolderId");
String toName = BeanParamUtil.getString(fileShortcut, request, "toName");

Group toGroup = null;
DLFolder toFolder = null;
DLFileEntry toFileEntry = null;

if ((toFolderId > 0) && Validator.isNotNull(toName)) {
	try {
		toFileEntry = DLFileEntryLocalServiceUtil.getFileEntry(toFolderId, toName);
		toFolder = DLFolderLocalServiceUtil.getFolder(toFolderId);
		toGroup = GroupLocalServiceUtil.getGroup(toFolder.getGroupId());
	}
	catch (Exception e) {
	}
}
else if ((toFolderId > 0)) {
	try {
		toFolder = DLFolderLocalServiceUtil.getFolder(toFolderId);
		toGroup = GroupLocalServiceUtil.getGroup(toFolder.getGroupId());
	}
	catch (Exception e) {
	}
}

if ((toGroup == null) && (toGroupId > 0)) {
	try {
		toGroup = GroupLocalServiceUtil.getGroup(toGroupId);
	}
	catch (Exception e) {
	}
}

if (toGroup != null) {
	toGroup = toGroup.toEscapedModel();

	toGroupId = toGroup.getGroupId();
}

if (toFileEntry != null) {
	toFileEntry = toFileEntry.toEscapedModel();
}

Boolean isLocked = Boolean.TRUE;
Boolean hasLock = Boolean.FALSE;

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", strutsAction);
portletURL.setParameter("tabs2", tabs2);
portletURL.setParameter("redirect", redirect);
portletURL.setParameter("fileShortcutId", String.valueOf(fileShortcutId));
%>

<script type="text/javascript">
	function <portlet:namespace />saveFileShortcut() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= fileShortcut == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectFileEntry(folderId, name, title) {
		document.<portlet:namespace />fm.<portlet:namespace />toFolderId.value = folderId;
		document.<portlet:namespace />fm.<portlet:namespace />toName.value = name;

		var titleEl = document.getElementById("<portlet:namespace />toFileEntryTitle");

		if (title != "") {
			title += "&nbsp;";
		}

		titleEl.innerHTML = title;
	}

	function <portlet:namespace />selectGroup(groupId, groupName) {
		if (document.<portlet:namespace />fm.<portlet:namespace />toGroupId.value != groupId) {
			<portlet:namespace />selectFileEntry("", "", "");
		}

		document.<portlet:namespace />fm.<portlet:namespace />toGroupId.value = groupId;
		document.<portlet:namespace />fm.<portlet:namespace />toFolderId.value = "";
		document.<portlet:namespace />fm.<portlet:namespace />toName.value = "";

		var nameEl = document.getElementById("<portlet:namespace />toGroupName");

		nameEl.innerHTML = groupName + "&nbsp;";

		document.getElementById("<portlet:namespace />selectToFileEntryButton").disabled = false;
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/document_library/edit_file_shortcut" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveFileShortcut(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />fileShortcutId" type="hidden" value="<%= fileShortcutId %>" />
<input name="<portlet:namespace />folderId" type="hidden" value="<%= folderId %>" />
<input name="<portlet:namespace />toGroupId" type="hidden" value="<%= toGroupId %>" />
<input name="<portlet:namespace />toFolderId" type="hidden" value="<%= toFolderId %>" />
<input name="<portlet:namespace />toName" type="hidden" value="<%= toName %>" />

<liferay-ui:tabs
	names="shortcut"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= FileShortcutPermissionException.class %>" message="you-do-not-have-permission-to-create-a-shortcut-to-the-selected-document" />
<liferay-ui:error exception="<%= NoSuchFileEntryException.class %>" message="the-document-could-not-be-found" />

<div class="breadcrumbs">
	<%= DLUtil.getBreadcrumbs(folderId, null, pageContext, renderRequest, renderResponse) %>
</div>

<c:if test="<%= (fileShortcut != null) && (toFileEntry != null) %>">
	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="name" />
		</td>
		<td>
			<a href="<%= themeDisplay.getPathMain() %>/document_library/get_file?p_l_id=<%= themeDisplay.getPlid() %>&fileShortcutId=<%= fileShortcutId %>">
			<%= toFileEntry.getTitle() %>
			</a>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="version" />
		</td>
		<td>
			<%= toFileEntry.getVersion() %>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="size" />
		</td>
		<td>
			<%= TextFormatter.formatKB(toFileEntry.getSize(), locale) %>k
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="downloads" />
		</td>
		<td>
			<%= toFileEntry.getReadCount() %>
		</td>
	</tr>
	<tr>
		<td colspan="3">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="url" />
		</td>
		<td>
			<liferay-ui:input-resource
				url='<%= PortalUtil.getPortalURL(request) + themeDisplay.getPathMain() + "/document_library/get_file?p_l_id=" + themeDisplay.getPlid() + "&fileShortcutId=" + fileShortcutId %>'
			/>
		</td>
	</tr>
	</table>

	<br />
</c:if>

<liferay-ui:message key="you-can-create-a-shortcut-to-any-document-that-you-have-read-access-for" />

<br /><br />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="community" />
	</td>
	<td>

		<%
		String toGroupName = BeanUtil.getString(toGroup, "name");
		%>

		<span id="<portlet:namespace />toGroupName">
		<%= toGroupName %>
		</span>

		<c:if test='<%= strutsAction.equals("/document_library/edit_file_shortcut") && ((fileShortcut == null) || DLFileShortcutPermission.contains(permissionChecker, fileShortcut, ActionKeys.UPDATE)) %>'>
			<input type="button" value="<liferay-ui:message key="select" />" onClick="var toGroupWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/document_library/select_group" /></portlet:renderURL>', 'toGroup', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=no,status=no,toolbar=no,width=680'); void(''); toGroupWindow.focus();" />
		</c:if>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="document" />
	</td>
	<td>

		<%
		String toFileEntryTitle = BeanUtil.getString(toFileEntry, "title");
		%>

		<span id="<portlet:namespace />toFileEntryTitle">
		<%= toFileEntryTitle %>
		</span>

		<c:if test='<%= strutsAction.equals("/document_library/edit_file_shortcut") && ((fileShortcut == null) || DLFileShortcutPermission.contains(permissionChecker, fileShortcut, ActionKeys.UPDATE)) %>'>
			<input <%= (toGroup == null) ? "disabled" : "" %> id="<portlet:namespace />selectToFileEntryButton" type="button" value="<liferay-ui:message key="select" />" onClick="var toFileEntryWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/document_library/select_file_entry" /></portlet:renderURL>&<portlet:namespace />groupId=' + document.<portlet:namespace />fm.<portlet:namespace />toGroupId.value + '&<portlet:namespace />folderId=' + document.<portlet:namespace />fm.<portlet:namespace />toFolderId.value + '&<portlet:namespace />name=' + document.<portlet:namespace />fm.<portlet:namespace />toName.value, 'toFileEntry', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=no,status=no,toolbar=no,width=680'); void(''); toFileEntryWindow.focus();">
		</c:if>
	</td>
</tr>

<c:if test="<%= fileShortcut == null %>">
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="permissions" />
		</td>
		<td>
			<liferay-ui:input-permissions
				modelName="<%= DLFileShortcut.class.getName() %>"
			/>
		</td>
	</tr>
</c:if>

</table>

<c:if test='<%= strutsAction.equals("/document_library/edit_file_shortcut") && ((fileShortcut == null) || DLFileShortcutPermission.contains(permissionChecker, fileShortcut, ActionKeys.UPDATE)) %>'>
	<br />

	<input type="submit" value="<liferay-ui:message key="save" />" />

	<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

	<br />
</c:if>

</form>

<c:if test="<%= (fileShortcut != null) && (toFileEntry != null) %>">
	<br />

	<liferay-ui:ratings
		className="<%= DLFileEntry.class.getName() %>"
		classPK="<%= toFileEntry.getFileEntryId() %>"
		url='<%= themeDisplay.getPathMain() + "/document_library/rate_file_entry" %>'
	/>

	<br />

	<%
	String tabs2Names = "version-history,comments";

	if (!DLFileShortcutPermission.contains(permissionChecker, fileShortcut, ActionKeys.ADD_DISCUSSION)) {
		tabs2Names = "version-history";
	}
	%>

	<liferay-ui:tabs
		names="<%= tabs2Names %>"
		param="tabs2"
		url="<%= portletURL.toString() %>"
	/>

	<c:choose>
		<c:when test='<%= tabs2.equals("version-history") %>'>

			<%
			SearchContainer searchContainer = new SearchContainer();

			List headerNames = new ArrayList();

			headerNames.add("version");
			headerNames.add("date");
			headerNames.add("size");
			headerNames.add(StringPool.BLANK);

			searchContainer.setHeaderNames(headerNames);

			List results = DLFileVersionLocalServiceUtil.getFileVersions(toFileEntry.getFolderId(), toFileEntry.getName());
			List resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.size(); i++) {
				DLFileVersion fileVersion = (DLFileVersion)results.get(i);

				ResultRow row = new ResultRow(new Object[] {toFileEntry, fileVersion, portletURL, isLocked, hasLock}, fileVersion.getFileVersionId(), i);

				StringMaker sm = new StringMaker();

				sm.append(themeDisplay.getPathMain());
				sm.append("/document_library/get_file?p_l_id=");
				sm.append(themeDisplay.getPlid());
				sm.append("&fileShortcutId=");
				sm.append(fileShortcutId);
				sm.append("&version=");
				sm.append(String.valueOf(fileVersion.getVersion()));

				String rowHREF = sm.toString();

				// Statistics

				row.addText(Double.toString(fileVersion.getVersion()), rowHREF);
				row.addText(dateFormatDateTime.format(fileVersion.getCreateDate()), rowHREF);
				row.addText(TextFormatter.formatKB(fileVersion.getSize(), locale) + "k", rowHREF);

				// Action

				row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/document_library/file_version_action.jsp");

				// Add result row

				resultRows.add(row);
			}
			%>

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
		</c:when>
		<c:when test='<%= tabs2.equals("comments") %>'>
			<c:if test="<%= DLFileShortcutPermission.contains(permissionChecker, fileShortcut, ActionKeys.ADD_DISCUSSION) %>">
				<portlet:actionURL var="discussionURL">
					<portlet:param name="struts_action" value="/document_library/edit_file_entry_discussion" />
				</portlet:actionURL>

				<liferay-ui:discussion
					formName="fm2"
					formAction="<%= discussionURL %>"
					className="<%= DLFileEntry.class.getName() %>"
					classPK="<%= toFileEntry.getFileEntryId() %>"
					userId="<%= toFileEntry.getUserId() %>"
					subject="<%= toFileEntry.getTitle() %>"
					redirect="<%= currentURL %>"
				/>
			</c:if>
		</c:when>
	</c:choose>
</c:if>