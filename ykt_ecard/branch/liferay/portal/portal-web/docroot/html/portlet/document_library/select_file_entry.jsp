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

long groupId = BeanParamUtil.getLong(folder, request, "groupId");
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

portletURL.setParameter("struts_action", "/document_library/select_file_entry");
portletURL.setParameter("groupId", String.valueOf(groupId));

List headerNames = new ArrayList();

headerNames.add("folder");
headerNames.add("num-of-folders");
headerNames.add("num-of-documents");

SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

int total = DLFolderLocalServiceUtil.getFoldersCount(groupId, folderId);

searchContainer.setTotal(total);

List results = DLFolderLocalServiceUtil.getFolders(groupId, folderId, searchContainer.getStart(), searchContainer.getEnd());

searchContainer.setResults(results);

List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	DLFolder curFolder = (DLFolder)results.get(i);

	curFolder = curFolder.toEscapedModel();

	ResultRow row = new ResultRow(curFolder, curFolder.getFolderId(), i);

	PortletURL rowURL = renderResponse.createRenderURL();

	rowURL.setWindowState(LiferayWindowState.POP_UP);

	rowURL.setParameter("struts_action", "/document_library/select_file_entry");
	rowURL.setParameter("groupId", String.valueOf(groupId));
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

	DLFolderLocalServiceUtil.getSubfolderIds(subfolderIds, groupId, curFolder.getFolderId());

	int foldersCount = subfolderIds.size() - 1;
	int fileEntriesCount = DLFileEntryLocalServiceUtil.getFoldersFileEntriesCount(subfolderIds);

	row.addText(String.valueOf(foldersCount), rowURL);
	row.addText(String.valueOf(fileEntriesCount), rowURL);

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

<c:if test="<%= results.size() > 0 %>">
	<br />
</c:if>

<c:if test="<%= folder != null %>">
	<liferay-ui:tabs names="documents" />

	<%
	headerNames.clear();

	headerNames.add("document");
	headerNames.add("size");
	headerNames.add("downloads");
	headerNames.add("locked");

	searchContainer = new SearchContainer(renderRequest, null, null, "cur2", SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

	total = DLFileEntryLocalServiceUtil.getFileEntriesCount(folder.getFolderId());

	searchContainer.setTotal(total);

	results = DLFileEntryLocalServiceUtil.getFileEntries(folder.getFolderId(), searchContainer.getStart(), searchContainer.getEnd());

	searchContainer.setResults(results);

	resultRows = searchContainer.getResultRows();

	for (int i = 0; i < results.size(); i++) {
		DLFileEntry fileEntry = (DLFileEntry)results.get(i);

		fileEntry = fileEntry.toEscapedModel();

		ResultRow row = new ResultRow(fileEntry, fileEntry.getFileEntryId(), i);

		StringMaker sm = new StringMaker();

		sm.append("javascript: opener.");
		sm.append(renderResponse.getNamespace());
		sm.append("selectFileEntry('");
		sm.append(fileEntry.getFolderId());
		sm.append("', '");
		sm.append(UnicodeFormatter.toString(fileEntry.getName()));
		sm.append("', '");
		sm.append(UnicodeFormatter.toString(fileEntry.getTitle()));
		sm.append("'); window.close();");

		String rowHREF = sm.toString();

		// Title and description

		sm = new StringMaker();

		sm.append("<img align=\"left\" border=\"0\" src=\"");
		sm.append(themeDisplay.getPathThemeImages());
		sm.append("/document_library/");
		sm.append(DLUtil.getFileExtension(fileEntry.getName()));
		sm.append(".png\">");
		sm.append(fileEntry.getTitle());

		if (Validator.isNotNull(fileEntry.getDescription())) {
			sm.append("<br />");
			sm.append(fileEntry.getDescription());
		}

		row.addText(sm.toString(), rowHREF);

		// Statistics

		row.addText(TextFormatter.formatKB(fileEntry.getSize(), locale) + "k", rowHREF);
		row.addText(String.valueOf(fileEntry.getReadCount()), rowHREF);

		// Locked

		boolean isLocked = LockServiceUtil.isLocked(DLFileEntry.class.getName(), DLUtil.getLockId(fileEntry.getFolderId(), fileEntry.getName()));

		row.addText(LanguageUtil.get(pageContext, isLocked ? "yes" : "no"), rowHREF);

		// Add result row

		resultRows.add(row);
	}
	%>

	<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
</c:if>

</form>