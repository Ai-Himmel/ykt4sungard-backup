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
String strutsAction = "/document_library_display";

if (portletResource.equals(PortletKeys.DOCUMENT_LIBRARY)) {
	strutsAction = "/document_library";
}

String redirect = ParamUtil.getString(request, "redirect");
%>

<script type="text/javascript">
	function <portlet:namespace />removeFolder() {
		document.<portlet:namespace />fm.<portlet:namespace />rootFolderId.value = "<%= DLFolderImpl.DEFAULT_PARENT_FOLDER_ID %>";

		var nameEl = document.getElementById("<portlet:namespace />rootFolderName");

		nameEl.href = "";
		nameEl.innerHTML = "";
	}

	function <%= PortalUtil.getPortletNamespace(portletResource) %>selectFolder(rootFolderId, rootFolderName) {
		document.<portlet:namespace />fm.<portlet:namespace />rootFolderId.value = rootFolderId;

		var nameEl = document.getElementById("<portlet:namespace />rootFolderName");

		nameEl.href = "<liferay-portlet:renderURL portletName="<%= portletResource %>" windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value='<%= strutsAction + "/view" %>' /></liferay-portlet:renderURL>&<portlet:namespace />folderId=" + rootFolderId;
		nameEl.innerHTML = rootFolderName + "&nbsp;";
	}
</script>

<form action="<liferay-portlet:actionURL portletConfiguration="true" />" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />rootFolderId" type="hidden" value="<%= rootFolderId %>" />
<input name="<portlet:namespace />folderColumns" type="hidden" value="" />
<input name="<portlet:namespace />fileEntryColumns" type="hidden" value="" />

<liferay-ui:error key="rootFolderId" message="please-enter-a-valid-root-folder" />

<liferay-ui:tabs names="display-style" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="classic" />
	</td>
	<td>
		<input <%= folderDisplayStyle.equals("classic") ? "checked" : "" %> name="<portlet:namespace />folderDisplayStyle" type="radio" value="classic" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="tree-view" />
	</td>
	<td>
		<input <%= folderDisplayStyle.equals("tree") ? "checked" : "" %> name="<portlet:namespace />folderDisplayStyle" type="radio" value="tree" />
	</td>
</tr>
</table>

<br />

<liferay-ui:tabs names="folders-listing" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="root-folder" />
	</td>
	<td>
		<a href="<liferay-portlet:renderURL portletName="<%= portletResource %>" windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value='<%= strutsAction + "/view" %>' /><portlet:param name="folderId" value="<%= String.valueOf(rootFolderId) %>" /></liferay-portlet:renderURL>" id="<portlet:namespace />rootFolderName">
		<%= rootFolderName %></a>

		<input type="button" value="<liferay-ui:message key="select" />" onClick="var folderWindow = window.open('<liferay-portlet:renderURL portletName="<%= portletResource %>" windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value='<%= strutsAction + "/select_folder" %>' /></liferay-portlet:renderURL>', 'folder', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=no,status=no,toolbar=no,width=830'); void(''); folderWindow.focus();">

		<input type="button" value="<liferay-ui:message key="remove" />" onClick="<portlet:namespace />removeFolder();" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="show-breadcrumbs" />
	</td>
	<td>
		<liferay-ui:input-checkbox param="showBreadcrumbs" defaultValue="<%= showBreadcrumbs %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="show-search" />
	</td>
	<td>
		<liferay-ui:input-checkbox param="showFoldersSearch" defaultValue="<%= showFoldersSearch %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="show-subfolders" />
	</td>
	<td>
		<liferay-ui:input-checkbox param="showSubfolders" defaultValue="<%= showSubfolders %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="folders-per-page" />
	</td>
	<td>
		<input name="<portlet:namespace />foldersPerPage" size="2" type="text" value="<%= foldersPerPage %>" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="show-columns" />
	</td>
	<td>

		<%
		Set availableFolderColumns = SetUtil.fromArray(StringUtil.split(allFolderColumns));

		// Left list

		List leftList = new ArrayList();

		for (int i = 0; i < folderColumns.length; i++) {
			String folderColumn = folderColumns[i];

			leftList.add(new KeyValuePair(folderColumn, LanguageUtil.get(pageContext, folderColumn)));
		}

		// Right list

		List rightList = new ArrayList();

		Arrays.sort(folderColumns);

		Iterator itr = availableFolderColumns.iterator();

		while (itr.hasNext()) {
			String folderColumn = (String)itr.next();

			if (Arrays.binarySearch(folderColumns, folderColumn) < 0) {
				rightList.add(new KeyValuePair(folderColumn, LanguageUtil.get(pageContext, folderColumn)));
			}
		}

		Collections.sort(rightList, new KeyValuePairComparator(false, true));
		%>

		<liferay-ui:input-move-boxes
			formName="fm"
			leftTitle="current"
			rightTitle="available"
			leftBoxName="currentFolderColumns"
			rightBoxName="availableFolderColumns"
			leftReorder="true"
			leftList="<%= leftList %>"
			rightList="<%= rightList %>"
		/>
	</td>
</tr>
</table>

<br />

<liferay-ui:tabs names="documents-listing" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="show-search" />
	</td>
	<td>
		<liferay-ui:input-checkbox param="showFileEntriesSearch" defaultValue="<%= showFileEntriesSearch %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="documents-per-page" />
	</td>
	<td>
		<input name="<portlet:namespace />fileEntriesPerPage" size="2" type="text" value="<%= fileEntriesPerPage %>" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="show-columns" />
	</td>
	<td>

		<%
		Set availableFileEntryColumns = SetUtil.fromArray(StringUtil.split(allFileEntryColumns));

		// Left list

		leftList = new ArrayList();

		for (int i = 0; i < fileEntryColumns.length; i++) {
			String fileEntryColumn = fileEntryColumns[i];

			leftList.add(new KeyValuePair(fileEntryColumn, LanguageUtil.get(pageContext, fileEntryColumn)));
		}

		// Right list

		rightList = new ArrayList();

		Arrays.sort(fileEntryColumns);

		itr = availableFileEntryColumns.iterator();

		while (itr.hasNext()) {
			String fileEntryColumn = (String)itr.next();

			if (Arrays.binarySearch(fileEntryColumns, fileEntryColumn) < 0) {
				rightList.add(new KeyValuePair(fileEntryColumn, LanguageUtil.get(pageContext, fileEntryColumn)));
			}
		}

		Collections.sort(rightList, new KeyValuePairComparator(false, true));
		%>

		<liferay-ui:input-move-boxes
			formName="fm"
			leftTitle="current"
			rightTitle="available"
			leftBoxName="currentFileEntryColumns"
			rightBoxName="availableFileEntryColumns"
			leftReorder="true"
			leftList="<%= leftList %>"
			rightList="<%= rightList %>"
		/>
	</td>
</tr>
</table>

<br />

<input type="button" value="<liferay-ui:message key="save" />" onClick="document.<portlet:namespace />fm.<portlet:namespace />folderColumns.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />currentFolderColumns); document.<portlet:namespace />fm.<portlet:namespace />fileEntryColumns.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />currentFileEntryColumns); submitForm(document.<portlet:namespace />fm);" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>