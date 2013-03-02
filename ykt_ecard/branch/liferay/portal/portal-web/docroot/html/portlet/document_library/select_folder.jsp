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
DLFolder folder = (DLFolder)request.getAttribute(WebKeys.DOCUMENT_LIBRARY_FOLDER);

long folderId = BeanParamUtil.getLong(folder, request, "folderId", DLFolderImpl.DEFAULT_PARENT_FOLDER_ID);
%>

<form method="post" name="<portlet:namespace />fm">

<liferay-ui:tabs names="folders" />

<c:if test="<%= folder != null %>">
	<div class="breadcrumbs">
		<%= DLUtil.getBreadcrumbs(folder, null, pageContext, renderRequest, renderResponse) %>
	</div>
</c:if>

<%
PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(LiferayWindowState.POP_UP);

portletURL.setParameter("struts_action", "/document_library/select_folder");
portletURL.setParameter("folderId", String.valueOf(folderId));

List headerNames = new ArrayList();

headerNames.add("folder");
headerNames.add("num-of-folders");
headerNames.add("num-of-documents");
headerNames.add(StringPool.BLANK);

SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

int total = DLFolderLocalServiceUtil.getFoldersCount(portletGroupId.longValue(), folderId);

searchContainer.setTotal(total);

List results = DLFolderLocalServiceUtil.getFolders(portletGroupId.longValue(), folderId, searchContainer.getStart(), searchContainer.getEnd());

searchContainer.setResults(results);

List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	DLFolder curFolder = (DLFolder)results.get(i);

	curFolder = curFolder.toEscapedModel();

	ResultRow row = new ResultRow(curFolder, curFolder.getFolderId(), i);

	PortletURL rowURL = renderResponse.createRenderURL();

	rowURL.setWindowState(LiferayWindowState.POP_UP);

	rowURL.setParameter("struts_action", "/document_library/select_folder");
	rowURL.setParameter("folderId", String.valueOf(curFolder.getFolderId()));

	// Name

	StringMaker sm = new StringMaker();

	sm.append("<img align=\"left\" border=\"0\" src=\"");
	sm.append(themeDisplay.getPathThemeImages());
	sm.append("/common/folder.png\">");
	sm.append(curFolder.getName());

	row.addText(sm.toString(), rowURL);

	// Statistics

	List subfolderIds = new ArrayList();

	subfolderIds.add(new Long(curFolder.getFolderId()));

	DLFolderLocalServiceUtil.getSubfolderIds(subfolderIds, portletGroupId.longValue(), curFolder.getFolderId());

	int foldersCount = subfolderIds.size() - 1;
	int fileEntriesCount = DLFileEntryLocalServiceUtil.getFoldersFileEntriesCount(subfolderIds);

	row.addText(String.valueOf(foldersCount), rowURL);
	row.addText(String.valueOf(fileEntriesCount), rowURL);

	// Action

	sm = new StringMaker();

	sm.append("opener.");
	sm.append(renderResponse.getNamespace());
	sm.append("selectFolder('");
	sm.append(curFolder.getFolderId());
	sm.append("', '");
	sm.append(UnicodeFormatter.toString(curFolder.getName()));
	sm.append("'); window.close();");

	row.addButton("right", SearchEntry.DEFAULT_VALIGN, LanguageUtil.get(pageContext, "choose"), sm.toString());

	// Add result row

	resultRows.add(row);
}

boolean showAddFolderButton = showButtons && DLFolderPermission.contains(permissionChecker, plid.longValue(), folderId, ActionKeys.ADD_FOLDER);
%>

<c:if test="<%= showAddFolderButton %>">
	<div>
		<input type="button" value="<liferay-ui:message key='<%= (folder == null) ? "add-folder" : "add-subfolder" %>' />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/document_library/edit_folder" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="parentFolderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>';" />
	</div>

	<c:if test="<%= results.size() > 0 %>">
		<br />
	</c:if>
</c:if>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

</form>