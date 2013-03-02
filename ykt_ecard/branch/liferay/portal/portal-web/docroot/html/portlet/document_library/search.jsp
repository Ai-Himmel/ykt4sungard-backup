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
String redirect = ParamUtil.getString(request, "redirect");

long breadcrumbsFolderId = ParamUtil.getLong(request, "breadcrumbsFolderId");

long searchFolderId = ParamUtil.getLong(request, "searchFolderId");
long searchFolderIds = ParamUtil.getLong(request, "searchFolderIds");

long[] folderIdsArray = null;

if (searchFolderId > 0) {
	folderIdsArray = new long[] {searchFolderId};
}
else {
	List folderIds = new ArrayList();

	folderIds.add(new Long(searchFolderIds));

	DLFolderLocalServiceUtil.getSubfolderIds(folderIds, portletGroupId.longValue(), searchFolderIds);

	folderIdsArray = StringUtil.split(StringUtil.merge(folderIds), 0L);
}

String keywords = ParamUtil.getString(request, "keywords");
%>

<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" varImpl="searchURL"><portlet:param name="struts_action" value="/document_library/search" /></liferay-portlet:renderURL>

<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="searchURL" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />breadcrumbsFolderId" type="hidden" value="<%= breadcrumbsFolderId %>" />
<input name="<portlet:namespace />searchFolderId" type="hidden" value="<%= searchFolderId %>" />
<input name="<portlet:namespace />searchFolderIds" type="hidden" value="<%= searchFolderIds %>" />

<liferay-ui:tabs
	names="search"
	backURL="<%= redirect %>"
/>

<%
PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/document_library/search");
portletURL.setParameter("breadcrumbsFolderId", String.valueOf(breadcrumbsFolderId));
portletURL.setParameter("searchFolderId", String.valueOf(searchFolderId));
portletURL.setParameter("searchFolderIds", String.valueOf(searchFolderIds));
portletURL.setParameter("keywords", keywords);

List headerNames = new ArrayList();

headerNames.add("#");
headerNames.add("folder");
headerNames.add("document");
headerNames.add("score");
headerNames.add(StringPool.BLANK);

SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, LanguageUtil.format(pageContext, "no-documents-were-found-that-matched-the-keywords-x", "<b>" + Html.escape(keywords) + "</b>"));

Hits hits = null;

try {
	hits = DLFolderLocalServiceUtil.search(company.getCompanyId(), portletGroupId.longValue(), folderIdsArray, keywords);

	Hits results = hits.subset(searchContainer.getStart(), searchContainer.getEnd());
	int total = hits.getLength();

	searchContainer.setTotal(total);

	List resultRows = searchContainer.getResultRows();

	for (int i = 0; i < results.getLength(); i++) {
		Document doc = results.doc(i);

		ResultRow row = new ResultRow(doc, i, i);

		// Position

		row.addText(searchContainer.getStart() + i + 1 + StringPool.PERIOD);

		// Folder and document

		long folderId = GetterUtil.getLong(doc.get("repositoryId"));
		String fileName = doc.get("path");

		DLFileEntry fileEntry = DLFileEntryLocalServiceUtil.getFileEntry(folderId, fileName);

		row.setObject(fileEntry);

		DLFolder folder = DLFolderLocalServiceUtil.getFolder(folderId);

		PortletURL rowURL = renderResponse.createActionURL();

		rowURL.setWindowState(LiferayWindowState.EXCLUSIVE);

		rowURL.setParameter("struts_action", "/document_library/get_file");
		rowURL.setParameter("folderId", String.valueOf(folderId));
		rowURL.setParameter("name", fileName);

		row.addText(folder.getName(), rowURL);
		row.addText(fileEntry.getTitle(), rowURL);

		// Score

		row.addScore(results.score(i));

		// Action

		row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/document_library/file_entry_action.jsp");

		// Add result row

		resultRows.add(row);
	}
%>

	<input name="<portlet:namespace />keywords" size="30" type="text" value="<%= Html.escape(keywords) %>" />

	<input type="submit" value="<liferay-ui:message key="search-file-entries" />" />

	<br /><br />

	<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

<%
}
catch (Exception e) {
	_log.error(e.getMessage());
}
finally {
	if (hits != null) {
		hits.closeSearcher();
	}
}
%>

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />keywords);
	</script>
</c:if>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.document_library.search.jsp");
%>