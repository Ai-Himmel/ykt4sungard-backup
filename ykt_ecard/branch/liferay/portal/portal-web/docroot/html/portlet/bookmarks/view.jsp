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

<%@ include file="/html/portlet/bookmarks/init.jsp" %>

<%
String tabs1 = ParamUtil.getString(request, "tabs1", "folders");

BookmarksFolder folder = (BookmarksFolder)request.getAttribute(WebKeys.BOOKMARKS_FOLDER);

long folderId = BeanParamUtil.getLong(folder, request, "folderId", BookmarksFolderImpl.DEFAULT_PARENT_FOLDER_ID);

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/bookmarks/view");
portletURL.setParameter("folderId", String.valueOf(folderId));
%>

<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" varImpl="searchURL"><portlet:param name="struts_action" value="/bookmarks/search" /></liferay-portlet:renderURL>

<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm1" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="searchURL" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= currentURL %>" />
<input name="<portlet:namespace />breadcrumbsFolderId" type="hidden" value="<%= folderId %>" />
<input name="<portlet:namespace />searchFolderIds" type="hidden" value="<%= folderId %>" />

<liferay-ui:tabs
	names="folders,my-entries,recent-entries"
	url="<%= portletURL.toString() %>"
/>

<c:choose>
	<c:when test='<%= tabs1.equals("folders") %>'>
		<c:if test="<%= folder != null %>">
			<div class="breadcrumbs">
				<%= BookmarksUtil.getBreadcrumbs(folder, null, pageContext, renderRequest, renderResponse) %>
			</div>
		</c:if>

		<%
		List headerNames = new ArrayList();

		headerNames.add("folder");
		headerNames.add("num-of-folders");
		headerNames.add("num-of-entries");
		headerNames.add(StringPool.BLANK);

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, "cur1", SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

		int total = BookmarksFolderLocalServiceUtil.getFoldersCount(portletGroupId.longValue(), folderId);

		searchContainer.setTotal(total);

		List results = BookmarksFolderLocalServiceUtil.getFolders(portletGroupId.longValue(), folderId, searchContainer.getStart(), searchContainer.getEnd());

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			BookmarksFolder curFolder = (BookmarksFolder)results.get(i);

			curFolder = curFolder.toEscapedModel();

			ResultRow row = new ResultRow(curFolder, curFolder.getFolderId(), i);

			PortletURL rowURL = renderResponse.createRenderURL();

			rowURL.setWindowState(WindowState.MAXIMIZED);

			rowURL.setParameter("struts_action", "/bookmarks/view");
			rowURL.setParameter("folderId", String.valueOf(curFolder.getFolderId()));

			// Name and description

			StringMaker sm = new StringMaker();

			sm.append("<a href=\"");
			sm.append(rowURL);
			sm.append("\">");
			sm.append("<img align=\"left\" border=\"0\" src=\"");
			sm.append(themeDisplay.getPathThemeImages());
			sm.append("/common/folder.png\">");
			sm.append("<b>");
			sm.append(curFolder.getName());
			sm.append("</b>");

			if (Validator.isNotNull(curFolder.getDescription())) {
				sm.append("<br />");
				sm.append(curFolder.getDescription());
			}

			sm.append("</a>");

			List subfolders = BookmarksFolderLocalServiceUtil.getFolders(portletGroupId.longValue(), curFolder.getFolderId(), 0, 5);

			if (subfolders.size() > 0) {
				sm.append("<br /><u>");
				sm.append(LanguageUtil.get(pageContext, "subfolders"));
				sm.append("</u>: ");

				for (int j = 0; j < subfolders.size(); j++) {
					BookmarksFolder subfolder = (BookmarksFolder)subfolders.get(j);

					subfolder = subfolder.toEscapedModel();

					rowURL.setParameter("folderId", String.valueOf(subfolder.getFolderId()));

					sm.append("<a href=\"");
					sm.append(rowURL);
					sm.append("\">");
					sm.append(subfolder.getName());
					sm.append("</a>");

					if ((j + 1) < subfolders.size()) {
						sm.append(", ");
					}
				}

				rowURL.setParameter("folderId", String.valueOf(curFolder.getFolderId()));
			}

			row.addText(sm.toString());

			// Statistics

			List subfolderIds = new ArrayList();

			subfolderIds.add(new Long(curFolder.getFolderId()));

			BookmarksFolderLocalServiceUtil.getSubfolderIds(subfolderIds, portletGroupId.longValue(), curFolder.getFolderId());

			int foldersCount = subfolderIds.size() - 1;
			int entriesCount = BookmarksEntryLocalServiceUtil.getFoldersEntriesCount(subfolderIds);

			row.addText(String.valueOf(foldersCount), rowURL);
			row.addText(String.valueOf(entriesCount), rowURL);

			// Action

			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/bookmarks/folder_action.jsp");

			// Add result row

			resultRows.add(row);
		}

		boolean showAddFolderButton = BookmarksFolderPermission.contains(permissionChecker, plid.longValue(), folderId, ActionKeys.ADD_FOLDER);
		%>

		<c:if test="<%= showAddFolderButton || (results.size() > 0) %>">
			<div>
				<c:if test="<%= results.size() > 0 %>">
					<label for="<portlet:namespace />keywords1"><liferay-ui:message key="search" /></label>

					<input id="<portlet:namespace />keywords1" name="<portlet:namespace />keywords" size="30" type="text" />

					<input type="submit" value="<liferay-ui:message key="search-entries" />" />
				</c:if>

				<c:if test="<%= showAddFolderButton %>">
					<input type="button" value="<liferay-ui:message key='<%= (folder == null) ? "add-folder" : "add-subfolder" %>' />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/bookmarks/edit_folder" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="parentFolderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>';" />
				</c:if>
			</div>

			<c:if test="<%= results.size() > 0 %>">
				<br />
			</c:if>
		</c:if>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

		<c:if test="<%= (folder != null) && (showAddFolderButton || (results.size() > 0)) %>">
			<br />
		</c:if>

		</form>

		<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
			<script type="text/javascript">
				Liferay.Util.focusFormField(document.<portlet:namespace />fm1.<portlet:namespace />keywords);
			</script>
		</c:if>

		<c:if test="<%= folder != null %>">
			<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm2" onSubmit="submitForm(this); return false;">
			<liferay-portlet:renderURLParams varImpl="searchURL" />
			<input name="<portlet:namespace />redirect" type="hidden" value="<%= currentURL %>" />
			<input name="<portlet:namespace />breadcrumbsFolderId" type="hidden" value="<%= folderId %>" />
			<input name="<portlet:namespace />searchFolderId" type="hidden" value="<%= folderId %>" />

			<liferay-ui:tabs names="entries" />

			<%
			String orderByCol = ParamUtil.getString(request, "orderByCol");
			String orderByType = ParamUtil.getString(request, "orderByType");

			if (Validator.isNotNull(orderByCol) && Validator.isNotNull(orderByType)) {
				portalPrefs.setValue(PortletKeys.BOOKMARKS, "entries-order-by-col", orderByCol);
				portalPrefs.setValue(PortletKeys.BOOKMARKS, "entries-order-by-type", orderByType);
			}
			else {
				orderByCol = portalPrefs.getValue(PortletKeys.BOOKMARKS, "entries-order-by-col", "name");
				orderByType = portalPrefs.getValue(PortletKeys.BOOKMARKS, "entries-order-by-type", "asc");
			}

			OrderByComparator orderByComparator = BookmarksUtil.getEntriesOrderByComparator(orderByCol, orderByType);

			headerNames.clear();

			headerNames.add("entry");
			headerNames.add("url");
			headerNames.add("visits");
			headerNames.add("priority");
			headerNames.add("modified-date");
			headerNames.add(StringPool.BLANK);

			Map orderableHeaders = CollectionFactory.getHashMap();

			orderableHeaders.put("entry", "name");
			orderableHeaders.put("url", "url");
			orderableHeaders.put("visits", "visits");
			orderableHeaders.put("priority", "priority");
			orderableHeaders.put("modified-date", "modified-date");

			searchContainer = new SearchContainer(renderRequest, null, null, "cur2", SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

			searchContainer.setOrderableHeaders(orderableHeaders);
			searchContainer.setOrderByCol(orderByCol);
			searchContainer.setOrderByType(orderByType);

			total = BookmarksEntryLocalServiceUtil.getEntriesCount(folder.getFolderId());

			searchContainer.setTotal(total);

			results = BookmarksEntryLocalServiceUtil.getEntries(folder.getFolderId(), searchContainer.getStart(), searchContainer.getEnd(), orderByComparator);

			searchContainer.setResults(results);

			resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.size(); i++) {
				BookmarksEntry entry = (BookmarksEntry)results.get(i);

				entry = entry.toEscapedModel();

				ResultRow row = new ResultRow(entry, entry.getEntryId(), i);

				StringMaker sm = new StringMaker();

				sm.append(themeDisplay.getPathMain());
				sm.append("/bookmarks/open_entry?entryId=");
				sm.append(entry.getEntryId());

				String rowHREF = sm.toString();

				TextSearchEntry rowTextEntry = new TextSearchEntry(SearchEntry.DEFAULT_ALIGN, SearchEntry.DEFAULT_VALIGN, entry.getName(), rowHREF, "_blank", entry.getComments());

				// Name

				row.addText(rowTextEntry);

				// URL

				rowTextEntry = (TextSearchEntry)rowTextEntry.clone();

				rowTextEntry.setName(entry.getUrl());

				row.addText(rowTextEntry);

				// Visits

				rowTextEntry = (TextSearchEntry)rowTextEntry.clone();

				rowTextEntry.setName(String.valueOf(entry.getVisits()));

				row.addText(rowTextEntry);

				// Priority

				rowTextEntry = (TextSearchEntry)rowTextEntry.clone();

				rowTextEntry.setName(String.valueOf(entry.getPriority()));

				row.addText(rowTextEntry);

				// ModifiedDate

				rowTextEntry = (TextSearchEntry)rowTextEntry.clone();

				rowTextEntry.setName(dateFormatDate.format(entry.getModifiedDate()));

				row.addText(rowTextEntry);

				// Action

				row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/bookmarks/entry_action.jsp");

				// Add result row

				resultRows.add(row);
			}

			boolean showAddEntryButton = BookmarksFolderPermission.contains(permissionChecker, folder, ActionKeys.ADD_ENTRY);
			%>

			<c:if test="<%= showAddEntryButton || (results.size() > 0) %>">
				<div>
					<c:if test="<%= results.size() > 0 %>">
						<label for="<portlet:namespace />keywords2"><liferay-ui:message key="search" /></label>

						<input id="<portlet:namespace />keywords2" name="<portlet:namespace />keywords" size="30" type="text" />

						<input type="submit" value="<liferay-ui:message key="search-entries" />" />
					</c:if>

					<c:if test="<%= showAddEntryButton %>">
						<input type="button" value="<liferay-ui:message key="add-entry" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/bookmarks/edit_entry" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>';" />
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
	<c:when test='<%= tabs1.equals("my-entries") || tabs1.equals("recent-entries") %>'>

		<%
		long groupEntriesUserId = 0;

		if (tabs1.equals("my-entries") && themeDisplay.isSignedIn()) {
			groupEntriesUserId = user.getUserId();
		}

		List headerNames = new ArrayList();

		headerNames.add("entry");
		headerNames.add("url");
		headerNames.add("visits");
		headerNames.add(StringPool.BLANK);

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

		int total = BookmarksEntryLocalServiceUtil.getGroupEntriesCount(portletGroupId.longValue(), groupEntriesUserId);

		searchContainer.setTotal(total);

		List results = BookmarksEntryLocalServiceUtil.getGroupEntries(portletGroupId.longValue(), groupEntriesUserId, searchContainer.getStart(), searchContainer.getEnd());

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			BookmarksEntry entry = (BookmarksEntry)results.get(i);

			entry = entry.toEscapedModel();

			ResultRow row = new ResultRow(entry, entry.getEntryId(), i);

			StringMaker sm = new StringMaker();

			sm.append(themeDisplay.getPathMain());
			sm.append("/bookmarks/open_entry?entryId=");
			sm.append(entry.getEntryId());

			String rowHREF = sm.toString();

			TextSearchEntry rowTextEntry = new TextSearchEntry(SearchEntry.DEFAULT_ALIGN, SearchEntry.DEFAULT_VALIGN, entry.getName(), rowHREF, "_blank", entry.getComments());

			// Name

			row.addText(rowTextEntry);

			// URL

			rowTextEntry = (TextSearchEntry)rowTextEntry.clone();

			rowTextEntry.setName(entry.getUrl());

			row.addText(rowTextEntry);

			// Visits

			rowTextEntry = (TextSearchEntry)rowTextEntry.clone();

			rowTextEntry.setName(String.valueOf(entry.getVisits()));

			row.addText(rowTextEntry);

			// Action

			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/bookmarks/entry_action.jsp");

			// Add result row

			resultRows.add(row);
		}
		%>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
</c:choose>