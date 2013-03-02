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

<%@ include file="/html/portlet/image_gallery/init.jsp" %>

<%
long groupId = ParamUtil.getLong(request, "groupId");

IGFolder folder = (IGFolder)request.getAttribute(WebKeys.IMAGE_GALLERY_FOLDER);

long folderId = BeanParamUtil.getLong(folder, request, "folderId", IGFolderImpl.DEFAULT_PARENT_FOLDER_ID);

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(LiferayWindowState.POP_UP);

portletURL.setParameter("struts_action", "/journal/select_image_gallery");
portletURL.setParameter("folderId", String.valueOf(folderId));
portletURL.setParameter("groupId", String.valueOf(groupId));
%>

<form method="post" name="<portlet:namespace />">

<liferay-ui:tabs names="folders" />

<c:if test="<%= folder != null %>">

	<%
	String breadcrumbs = IGUtil.getBreadcrumbs(folder, null, pageContext, renderRequest, renderResponse);

	breadcrumbs = StringUtil.replace(breadcrumbs, "image_gallery%2Fselect_folder", "journal%2Fselect_image_gallery");
	%>

	<div class="breadcrumbs">
		<%= breadcrumbs %>
	</div>
</c:if>

<%
List headerNames = new ArrayList();

headerNames.add("folder");
headerNames.add("num-of-folders");
headerNames.add("num-of-images");

SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, "cur1", SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

int total = IGFolderLocalServiceUtil.getFoldersCount(groupId, folderId);

searchContainer.setTotal(total);

List results = IGFolderLocalServiceUtil.getFolders(groupId, folderId, searchContainer.getStart(), searchContainer.getEnd());

searchContainer.setResults(results);

List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	IGFolder curFolder = (IGFolder)results.get(i);

	ResultRow row = new ResultRow(curFolder, curFolder.getFolderId(), i);

	PortletURL rowURL = renderResponse.createRenderURL();

	rowURL.setWindowState(LiferayWindowState.POP_UP);

	rowURL.setParameter("struts_action", "/journal/select_image_gallery");
	rowURL.setParameter("folderId", String.valueOf(curFolder.getFolderId()));
	rowURL.setParameter("groupId", String.valueOf(groupId));

	// Name

	row.addText(curFolder.getName(), rowURL);

	// Statistics

	List subfolderIds = new ArrayList();

	subfolderIds.add(new Long(curFolder.getFolderId()));

	IGFolderLocalServiceUtil.getSubfolderIds(subfolderIds, groupId, curFolder.getFolderId());

	int foldersCount = subfolderIds.size() - 1;
	int imagesCount = IGImageLocalServiceUtil.getFoldersImagesCount(subfolderIds);

	row.addText(String.valueOf(foldersCount), rowURL);
	row.addText(String.valueOf(imagesCount), rowURL);

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

<c:if test="<%= folder != null %>">
	<liferay-ui:tabs names="images" />

	<%
	headerNames.clear();

	headerNames.add("thumbnail");
	headerNames.add("height");
	headerNames.add("width");
	headerNames.add("size");
	headerNames.add(StringPool.BLANK);

	searchContainer = new SearchContainer(renderRequest, null, null, "cur2", SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

	total = IGImageLocalServiceUtil.getImagesCount(folder.getFolderId());

	searchContainer.setTotal(total);

	results = IGImageLocalServiceUtil.getImages(folder.getFolderId(), searchContainer.getStart(), searchContainer.getEnd());

	searchContainer.setResults(results);

	resultRows = searchContainer.getResultRows();

	for (int i = 0; i < results.size(); i++) {
		IGImage image = (IGImage)results.get(i);

		Image largeImage = ImageLocalServiceUtil.getImage(image.getLargeImageId());

		ResultRow row = new ResultRow(image, image.getImageId(), i);

		// Thumbnail

		row.addJSP("/html/portlet/image_gallery/image_thumbnail.jsp");

		// Statistics

		row.addText(String.valueOf(largeImage.getHeight()));
		row.addText(String.valueOf(largeImage.getWidth()));
		row.addText(TextFormatter.formatKB(largeImage.getSize(), locale) + "k");

		// Action

		StringMaker sm = new StringMaker();

		sm.append("opener.");
		sm.append(renderResponse.getNamespace());
		sm.append("selectImageGallery('");
		sm.append("@image_path@/image_gallery?uuid=");
		sm.append(image.getUuid());
		sm.append("&groupId=@group_id@&t=");
		sm.append(ImageServletTokenUtil.getToken(image.getLargeImageId()));
		sm.append("'); window.close();");

		row.addButton("right", SearchEntry.DEFAULT_VALIGN, LanguageUtil.get(pageContext, "choose"), sm.toString());

		// Add result row

		resultRows.add(row);
	}
	%>

	<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
</c:if>

</form>