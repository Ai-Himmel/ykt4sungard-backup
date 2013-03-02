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
String tabs1 = ParamUtil.getString(request, "tabs1", "folders");

DLFolder folder = (DLFolder)request.getAttribute(WebKeys.DOCUMENT_LIBRARY_FOLDER);

long defaultFolderId = GetterUtil.getLong(prefs.getValue("rootFolderId", StringPool.BLANK), DLFolderImpl.DEFAULT_PARENT_FOLDER_ID);

long folderId = BeanParamUtil.getLong(folder, request, "folderId", defaultFolderId);

if ((folder == null) && (defaultFolderId != DLFolderImpl.DEFAULT_PARENT_FOLDER_ID)) {
	try {
		folder = DLFolderLocalServiceUtil.getFolder(folderId);
	}
	catch (NoSuchFolderException nsfe) {
		folderId = DLFolderImpl.DEFAULT_PARENT_FOLDER_ID;
	}
}

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/document_library/view");
portletURL.setParameter("tabs1", tabs1);
portletURL.setParameter("folderId", String.valueOf(folderId));
%>

<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" varImpl="searchURL"><portlet:param name="struts_action" value="/document_library/search" /></liferay-portlet:renderURL>

<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm1" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="searchURL" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= currentURL %>" />
<input name="<portlet:namespace />breadcrumbsFolderId" type="hidden" value="<%= folderId %>" />
<input name="<portlet:namespace />searchFolderIds" type="hidden" value="<%= folderId %>" />

<c:choose>
	<c:when test="<%= showTabs && (rootFolder == null) %>">
		<liferay-ui:tabs
			names="folders,my-documents,recent-documents"
			url="<%= portletURL.toString() %>"
		/>
	</c:when>
	<c:when test="<%= showTabs && showSubfolders %>">
		<liferay-ui:tabs names="folders" />
	</c:when>
</c:choose>

<c:choose>
	<c:when test='<%= tabs1.equals("folders") %>'>
		<c:if test="<%= showBreadcrumbs && (folder != null) %>">
			<div class="breadcrumbs">
				<%= DLUtil.getBreadcrumbs(folder, null, pageContext, renderRequest, renderResponse) %>
			</div>
		</c:if>

		<c:choose>
			<c:when test='<%= folderDisplayStyle.equals("classic") %>'>
				<c:if test="<%= showSubfolders %>">

					<%
					List headerNames = new ArrayList();

					for (int i = 0; i < folderColumns.length; i++) {
						String folderColumn = folderColumns[i];

						if (folderColumn.equals("action")) {
							folderColumn = StringPool.BLANK;
						}

						headerNames.add(folderColumn);
					}

					SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, "cur1", SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

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

						rowURL.setWindowState(WindowState.MAXIMIZED);

						rowURL.setParameter("struts_action", "/document_library/view");
						rowURL.setParameter("folderId", String.valueOf(curFolder.getFolderId()));

						List subfolderIds = new ArrayList();

						subfolderIds.add(new Long(curFolder.getFolderId()));

						DLFolderLocalServiceUtil.getSubfolderIds(subfolderIds, portletGroupId.longValue(), curFolder.getFolderId());

						int foldersCount = subfolderIds.size() - 1;
						int fileEntriesCount = DLFileEntryLocalServiceUtil.getFileEntriesAndShortcutsCount(subfolderIds);
					%>

						<%@ include file="/html/portlet/document_library/folder_columns.jspf" %>

					<%

						// Add result row

						resultRows.add(row);
					}

					boolean showAddFolderButton = showButtons && DLFolderPermission.contains(permissionChecker, plid.longValue(), folderId, ActionKeys.ADD_FOLDER);
					boolean showCurFolderSearch = showFoldersSearch && (results.size() > 0);
					%>

					<c:if test="<%= showAddFolderButton || showCurFolderSearch %>">
						<div>
							<c:if test="<%= showCurFolderSearch %>">
								<label for="<portlet:namespace />keywords1"><liferay-ui:message key="search" /></label>

								<input id="<portlet:namespace />keywords1" name="<portlet:namespace />keywords" size="30" type="text" />

								<input type="submit" value="<liferay-ui:message key="search-file-entries" />" />
							</c:if>

							<c:if test="<%= showAddFolderButton %>">
								<input type="button" value="<liferay-ui:message key='<%= (folder == null) ? "add-folder" : "add-subfolder" %>' />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/document_library/edit_folder" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="parentFolderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>';" />
							</c:if>
						</div>

						<c:if test="<%= results.size() > 0 %>">
							<br />
						</c:if>
					</c:if>

					<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

					<c:if test="<%= showAddFolderButton || showCurFolderSearch || (results.size() > 0) %>">
						<br />
					</c:if>

					</form>

					<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
						<script type="text/javascript">
							Liferay.Util.focusFormField(document.<portlet:namespace />fm1.<portlet:namespace />keywords);
						</script>
					</c:if>
				</c:if>
			</c:when>
			<c:otherwise>

				<%
				List folders = DLFolderLocalServiceUtil.getFolders(portletGroupId.longValue(), folderId);

				boolean showAddFolderButton = showButtons && DLFolderPermission.contains(permissionChecker, plid.longValue(), folderId, ActionKeys.ADD_FOLDER);
				boolean showCurFolderSearch = showFoldersSearch && (folders.size() > 0);
				%>

				<c:if test="<%= showAddFolderButton || showCurFolderSearch %>">
					<div>
						<c:if test="<%= showCurFolderSearch %>">
							<label for="<portlet:namespace />keywords1"><liferay-ui:message key="search" /></label>

							<input id="<portlet:namespace />keywords1" name="<portlet:namespace />keywords" size="30" type="text" />

							<input type="submit" value="<liferay-ui:message key="search-file-entries" />" />
						</c:if>

						<c:if test="<%= showAddFolderButton %>">
							<input type="button" value="<liferay-ui:message key='<%= (folder == null) ? "add-folder" : "add-subfolder" %>' />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/document_library/edit_folder" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="parentFolderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>';" />
						</c:if>
					</div>
				</c:if>

				<c:if test="<%= folders.size() > 0 %>">
					<link type="text/css" rel="stylesheet" href="<%= themeDisplay.getPathContext() %>/html/portlet/document_library/portlet.css">

					<style type="text/css">

						/* This CSS fixes the display of the liferay-actions-menu button. It must be included in view.jsp to work correctly in the Freeform layout on IE6. */

						.portlet-document-library li .lfr-actions {
							display: inline;
							float: none;
							position: absolute;
							right: 0%;
						}

						.ie .portlet-document-library li .lfr-actions {
							display: block;
						}
					</style>

					<br />

					<ul class="lfr-component">
						<li class="header">
							<span class="col-name"><liferay-ui:message key="name" /></span>
							<span class="col-folders"><liferay-ui:message key="num-of-folders" /></span>
							<span class="col-documents"><liferay-ui:message key="num-of-documents" /></span>
						</li>

						<%
						PortletURL folderURL = renderResponse.createRenderURL();

						folderURL.setParameter("struts_action", "/document_library/view");

						for (int i = 0; i < folders.size(); i++) {
							DLFolder curFolder = (DLFolder)folders.get(i);

							curFolder = curFolder.toEscapedModel();

							ResultRow row = new ResultRow(curFolder, curFolder.getFolderId(), i);

							request.setAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW, row);

							List subfolderIds = new ArrayList();

							subfolderIds.add(new Long(curFolder.getFolderId()));

							DLFolderLocalServiceUtil.getSubfolderIds(subfolderIds, portletGroupId.longValue(), curFolder.getFolderId());

							int foldersCount = subfolderIds.size() - 1;
							int fileEntriesCount = DLFileEntryLocalServiceUtil.getFileEntriesAndShortcutsCount(subfolderIds);

							folderURL.setParameter("folderId", String.valueOf(curFolder.getFolderId()));
						%>

						<li class="top-row">
							<img border="0" class="expand-image" hspace="0" id="<portlet:namespace />expand-image-<%= curFolder.getFolderId() %>" onclick="<portlet:namespace />getFolders(this.id);" src="<%= themeDisplay.getPathThemeImages() %>/trees/plus.png" vspace="0" />

							<img border="0" class="folder-image" hspace="0" id="<portlet:namespace />folder-image-<%= curFolder.getFolderId() %>" onclick="<portlet:namespace />getFolders(this.id);" src="<%= themeDisplay.getPathThemeImages() %>/common/folder.png" vspace="0" />

							<a href="<%= folderURL %>"><%= curFolder.getName() %></a>

							<span class="col-folders"><%= foldersCount %></span>

							<span class="col-documents"><%= fileEntriesCount %></span>

							<liferay-util:include page="/html/portlet/document_library/folder_action.jsp" />
						</li>

						<%
						}
						%>

					</ul>

					<%
					PortletURL actionMenuURL = renderResponse.createRenderURL();

					actionMenuURL.setWindowState(LiferayWindowState.EXCLUSIVE);

					actionMenuURL.setParameter("struts_action", "/document_library/folder_action_ajax");
					actionMenuURL.setParameter("folderId", "");

					folderURL.setParameter("folderId", "");
					%>

					<script type="text/javascript">
						function <portlet:namespace />getFolders(imageId) {
							var folderId = imageId.substr(imageId.lastIndexOf('-') + 1);

							var expandImage = jQuery('#<portlet:namespace />expand-image-' + folderId);
							var folderImage = jQuery('#<portlet:namespace />folder-image-' + folderId);

							jQuery.getJSON(
								themeDisplay.getPathMain() + '/document_library/get_folders',
								{groupId: '<%= portletGroupId %>', folderId: '"' + folderId + '"'},
								function(json) {
									if (json.length > 0) {
										var ulId = '<portlet:namespace />ul-' + json[0].parentFolderId;

										expandImage.parent('li').append('<ul id="' + ulId + '"></ul>');

										var ul = jQuery('#' + ulId);
										var folderURL = '<%= folderURL %>';
										var actionMenuURL = '<%= actionMenuURL %>';

										for (var i = 0; i < json.length; i++) {
											ul.append(
												'<li class="list-item">' +
													'<img border="0" class="expand-image" hspace="0" id="<portlet:namespace />expand-image-' + json[i].folderId + '" onclick="<portlet:namespace />getFolders(this.id);" src="<%= themeDisplay.getPathThemeImages() %>/trees/plus.png" vspace="0" />\n' +
													'<img border="0" class="folder-image" hspace="0" id="<portlet:namespace />folder-image-' + json[i].folderId + '" onclick="<portlet:namespace />getFolders(this.id);" src="<%= themeDisplay.getPathThemeImages() %>/common/folder.png" vspace="0" />\n' +
													'<a href="' + folderURL + json[i].folderId + '">' + json[i].name + '</a>\n' +
													'<span class="col-folders">' + json[i].subFoldersCount + '</span>\n' +
													'<span class="col-documents">' + json[i].fileEntriesCount + '</span>\n' +
													'<span id="span-' + json[i].folderId + '"></span>' +
												'</li>'
											);

											jQuery('#span-' + json[i].folderId).load(actionMenuURL + json[i].folderId + '&<portlet:namespace />ajaxRedirect=' + folderURL, function() {
												new Liferay.Menu(
													{
														trigger: '.lfr-trigger',
														button: '.lfr-actions'
													}
												);
											});
										}
									}

									if (jQuery.browser.msie) {

										// Must create a new element to change the onclick attribute for IE

										expandImage.after(document.createElement('<img border="0" class="expand-image" hspace="0" id="<portlet:namespace />expand-image-' + folderId + '" onclick="<portlet:namespace />toggle(this.id);" src="<%= themeDisplay.getPathThemeImages() %>/trees/minus.png" vspace="0" />'));
										expandImage.remove();

										folderImage.after(document.createElement('<img border="0" class="folder-image" hspace="0" id="<portlet:namespace />folder-image-' + folderId + '" onclick="<portlet:namespace />toggle(this.id);" src="<%= themeDisplay.getPathThemeImages() %>/common/folder_open.png" vspace="0" />'));
										folderImage.remove();
									}
									else {
										expandImage.attr("src", "<%= themeDisplay.getPathThemeImages() %>/trees/minus.png");
										expandImage.attr("onclick", "<portlet:namespace />toggle(this.id);");

										folderImage.attr("src", "<%= themeDisplay.getPathThemeImages() %>/common/folder_open.png");
										folderImage.attr("onclick", "<portlet:namespace />toggle(this.id);");
									}
								}
							);
						}

						function <portlet:namespace />toggle(imageId) {
							var folderId = imageId.substr(imageId.lastIndexOf('-') + 1);

							var selId = document.getElementById('<portlet:namespace />ul-' + folderId);

							if (selId != null) {
								var expandImage = jQuery('#<portlet:namespace />expand-image-' + folderId);
								var folderImage = jQuery('#<portlet:namespace />folder-image-' + folderId);

								if (selId.style.display == '') {
									selId.style.display = 'none';
									expandImage.attr('src', '<%= themeDisplay.getPathThemeImages() %>/trees/plus.png');
									folderImage.attr('src', '<%= themeDisplay.getPathThemeImages() %>/common/folder.png');
								}
								else {
									selId.style.display = '';
									expandImage.attr('src', '<%= themeDisplay.getPathThemeImages() %>/trees/minus.png');
									folderImage.attr('src', '<%= themeDisplay.getPathThemeImages() %>/common/folder_open.png');
								}
							}
						}
					</script>
				</c:if>

				<c:if test="<%= showAddFolderButton || showCurFolderSearch || (folders.size() > 0) %>">
					<br />
				</c:if>

				</form>
			</c:otherwise>
		</c:choose>

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="webdav-url" />
			</td>
			<td>

				<%
				StringBuffer sb = new StringBuffer();

				if (folder != null) {
					DLFolder curFolder = folder;

					while (true) {
						sb.insert(0, curFolder.getName());
						sb.insert(0, StringPool.SLASH);

						if (curFolder.getParentFolderId() == DLFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
							break;
						}
						else {
							curFolder = DLFolderLocalServiceUtil.getFolder(curFolder.getParentFolderId());
						}
					}
				}

				sb.insert(0, layout.getGroupId());
				sb.insert(0, StringPool.SLASH);
				%>

				<liferay-ui:input-resource
					url='<%= PortalUtil.getPortalURL(request) + "/tunnel-web/secure/webdav/document_library/" + company.getCompanyId() + sb.toString() %>'
				/>
			</td>
		</tr>
		</table>

		<c:if test="<%= folder != null %>">
			<br />

			<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm2" onSubmit="submitForm(this); return false;">
			<liferay-portlet:renderURLParams varImpl="searchURL" />
			<input name="<portlet:namespace />redirect" type="hidden" value="<%= currentURL %>" />
			<input name="<portlet:namespace />breadcrumbsFolderId" type="hidden" value="<%= folderId %>" />
			<input name="<portlet:namespace />searchFolderId" type="hidden" value="<%= folderId %>" />

			<c:if test="<%= showTabs && showSubfolders %>">
				<liferay-ui:tabs names="documents" />
			</c:if>

			<%
			List headerNames = new ArrayList();

			for (int i = 0; i < fileEntryColumns.length; i++) {
				String fileEntryColumn = fileEntryColumns[i];

				if (fileEntryColumn.equals("action")) {
					fileEntryColumn = StringPool.BLANK;
				}

				headerNames.add(fileEntryColumn);
			}

			SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, "cur2", fileEntriesPerPage, portletURL, headerNames, null);

			int total = DLFileEntryLocalServiceUtil.getFileEntriesAndShortcutsCount(folder.getFolderId());

			searchContainer.setTotal(total);

			List results = DLFileEntryLocalServiceUtil.getFileEntriesAndShortcuts(folder.getFolderId(), searchContainer.getStart(), searchContainer.getEnd());

			searchContainer.setResults(results);

			List resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.size(); i++) {
				Object result = results.get(i);

				long primaryKey = 0;

				DLFileEntry fileEntry = null;
				DLFileShortcut fileShortcut = null;

				if (result instanceof DLFileEntry) {
					fileEntry = (DLFileEntry)result;

					fileEntry = fileEntry.toEscapedModel();

					primaryKey = fileEntry.getFileEntryId();
				}
				else {
					fileShortcut = (DLFileShortcut)result;

					fileShortcut = fileShortcut.toEscapedModel();

					fileEntry = DLFileEntryLocalServiceUtil.getFileEntry(fileShortcut.getToFolderId(), Html.unescape(fileShortcut.getToName()));

					fileEntry = fileEntry.toEscapedModel();

					primaryKey = fileShortcut.getFileShortcutId();
				}

				ResultRow row = new ResultRow(result, primaryKey, i);

				String rowHREF = null;

				if (fileShortcut == null) {
					rowHREF = themeDisplay.getPathMain() + "/document_library/get_file?p_l_id=" + themeDisplay.getPlid() + "&folderId=" + fileEntry.getFolderId() + "&name=" + HttpUtil.encodeURL(Html.unescape(fileEntry.getName()));
				}
				else {
					rowHREF = themeDisplay.getPathMain() + "/document_library/get_file?p_l_id=" + themeDisplay.getPlid() + "&fileShortcutId=" + fileShortcut.getFileShortcutId();
				}
			%>

				<%@ include file="/html/portlet/document_library/file_entry_columns.jspf" %>

			<%

				// Add result row

				resultRows.add(row);
			}

			boolean showAddFileEntryButton = showButtons && DLFolderPermission.contains(permissionChecker, folder, ActionKeys.ADD_DOCUMENT);
			boolean showAddFileShortcutButton = showButtons && DLFolderPermission.contains(permissionChecker, folder, ActionKeys.ADD_SHORTCUT);
			boolean showCurDocumentSearch = showFileEntriesSearch && (results.size() > 0);
			%>

			<c:if test="<%= showAddFileEntryButton || showAddFileShortcutButton || showCurDocumentSearch %>">
				<div>
					<c:if test="<%= showCurDocumentSearch %>">
						<label for="<portlet:namespace />keywords2"><liferay-ui:message key="search" /></label>

						<input id="<portlet:namespace />keywords2" name="<portlet:namespace />keywords" size="30" type="text" />

						<input type="submit" value="<liferay-ui:message key="search-file-entries" />" />
					</c:if>

					<c:if test="<%= showAddFileEntryButton || showAddFileShortcutButton %>">
						<c:if test="<%= showAddFileEntryButton %>">
							<input type="button" value="<liferay-ui:message key="add-document" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/document_library/edit_file_entry" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>';" />
						</c:if>

						<c:if test="<%= showAddFileShortcutButton %>">
							<input type="button" value="<liferay-ui:message key="add-shortcut" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/document_library/edit_file_shortcut" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>';" />
						</c:if>
					</c:if>
				</div>

				<c:if test="<%= results.size() > 0 %>">
					<br />
				</c:if>
			</c:if>

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

			</form>

			<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
				<script type="text/javascript">
					Liferay.Util.focusFormField(document.<portlet:namespace />fm2.<portlet:namespace />keywords);
					Liferay.Util.focusFormField(document.<portlet:namespace />fm1.<portlet:namespace />keywords);
				</script>
			</c:if>
		</c:if>
	</c:when>
	<c:when test='<%= tabs1.equals("my-documents") || tabs1.equals("recent-documents") %>'>

		<%
		long groupFileEntriesUserId = 0;

		if (tabs1.equals("my-documents") && themeDisplay.isSignedIn()) {
			groupFileEntriesUserId = user.getUserId();
		}

		List headerNames = new ArrayList();

		for (int i = 0; i < fileEntryColumns.length; i++) {
			String fileEntryColumn = fileEntryColumns[i];

			if (fileEntryColumn.equals("action")) {
				fileEntryColumn = StringPool.BLANK;
			}

			headerNames.add(fileEntryColumn);
		}

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, fileEntriesPerPage, portletURL, headerNames, null);

		int total = DLFileEntryLocalServiceUtil.getGroupFileEntriesCount(portletGroupId.longValue(), groupFileEntriesUserId);

		searchContainer.setTotal(total);

		List results = DLFileEntryLocalServiceUtil.getGroupFileEntries(portletGroupId.longValue(), groupFileEntriesUserId, searchContainer.getStart(), searchContainer.getEnd());

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			DLFileEntry fileEntry = (DLFileEntry)results.get(i);

			fileEntry = fileEntry.toEscapedModel();

			ResultRow row = new ResultRow(fileEntry, fileEntry.getFileEntryId(), i);

			String rowHREF = themeDisplay.getPathMain() + "/document_library/get_file?p_l_id=" + themeDisplay.getPlid() + "&folderId=" + fileEntry.getFolderId() + "&name=" + HttpUtil.encodeURL(Html.unescape(fileEntry.getName()));
		%>

			<%@ include file="/html/portlet/document_library/file_entry_columns.jspf" %>

		<%

			// Add result row

			resultRows.add(row);
		}
		%>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
</c:choose>