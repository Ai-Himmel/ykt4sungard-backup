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

<%@ include file="/html/portlet/tagged_content/init.jsp" %>

<%
List results = (List)request.getAttribute("view.jsp-results");

int assetIndex = ((Integer)request.getAttribute("view.jsp-assetIndex")).intValue();

TagsAsset asset = (TagsAsset)request.getAttribute("view.jsp-asset");

String title = (String)request.getAttribute("view.jsp-title");
String summary = (String)request.getAttribute("view.jsp-summary");
String viewURL = (String)request.getAttribute("view.jsp-viewURL");
String viewURLMessage = (String)request.getAttribute("view.jsp-viewURLMessage");

String className = (String)request.getAttribute("view.jsp-className");
long classPK = ((Long)request.getAttribute("view.jsp-classPK")).longValue();

boolean show = ((Boolean)request.getAttribute("view.jsp-show")).booleanValue();

if (className.equals(BlogsEntry.class.getName())) {
	BlogsEntry entry = BlogsEntryLocalServiceUtil.getEntry(classPK);

	if (Validator.isNull(title)) {
		title = entry.getTitle();
	}

	summary = entry.getTitle();

	PortletURL entryURL = renderResponse.createRenderURL();

	entryURL.setParameter("struts_action", "/tagged_content/view_content");
	entryURL.setParameter("redirect", currentURL);
	entryURL.setParameter("assetId", String.valueOf(asset.getAssetId()));

	viewURL = entryURL.toString();

	viewURLMessage = "read-more";
}
else if (className.equals(BookmarksEntry.class.getName())) {
	BookmarksEntry entry = BookmarksEntryLocalServiceUtil.getEntry(classPK);

	if (Validator.isNull(title)) {
		title = entry.getName();
	}

	summary = entry.getComments();
	viewURL = entry.getUrl();
	viewURLMessage = "go";
}
else if (className.equals(DLFileEntry.class.getName())) {
	DLFileEntry fileEntry = DLFileEntryLocalServiceUtil.getFileEntry(classPK);

	if (Validator.isNull(title)) {
		StringMaker sm = new StringMaker();

		sm.append("<img align=\"left\" border=\"0\" src=\"");
        sm.append(themeDisplay.getPathThemeImages());
        sm.append("/document_library/");
        sm.append(DLUtil.getFileExtension(fileEntry.getName()));
        sm.append(".png\" />");
		sm.append(fileEntry.getTitle());

		title = sm.toString();
	}

	summary = fileEntry.getDescription();
	viewURL = themeDisplay.getPathMain() + "/document_library/get_file?p_l_id=" + themeDisplay.getPlid() + "&folderId=" + fileEntry.getFolderId() + "&name=" + HttpUtil.encodeURL(fileEntry.getName());
	viewURLMessage = "download";
}
else if (className.equals(IGImage.class.getName())) {
	IGImage image = IGImageLocalServiceUtil.getImage(classPK);

	summary = image.getDescription();

	PortletURL imageURL = new PortletURLImpl(request, PortletKeys.IMAGE_GALLERY, plid.longValue(), false);

	imageURL.setWindowState(WindowState.MAXIMIZED);

	imageURL.setParameter("struts_action", "/image_gallery/view");
	imageURL.setParameter("folderId", String.valueOf(image.getFolderId()));

	viewURL = imageURL.toString();

	viewURLMessage = "view";
}
else if (className.equals(JournalArticle.class.getName())) {
	JournalArticleResource articleResource = JournalArticleResourceLocalServiceUtil.getArticleResource(classPK);

	String languageId = LanguageUtil.getLanguageId(request);

	JournalArticleDisplay articleDisplay = JournalContentUtil.getDisplay(articleResource.getGroupId(), articleResource.getArticleId(), null, languageId, themeDisplay);

	if (articleDisplay != null) {
		if (Validator.isNull(title)) {
			title = articleDisplay.getTitle();
		}

		StringMaker sm = new StringMaker();

		if (articleDisplay.isSmallImage()) {
			sm.append("<div style=\"float: left; padding-right: 10px;\"><img src=\"");

			if (Validator.isNotNull(articleDisplay.getSmallImageURL())) {
				sm.append(articleDisplay.getSmallImageURL());
			}
			else {
				sm.append(themeDisplay.getPathImage());
				sm.append("/journal/article?img_id=");
				sm.append(articleDisplay.getSmallImageId());
				sm.append("&t=");
				sm.append(ImageServletTokenUtil.getToken(articleDisplay.getSmallImageId()));
			}

			sm.append("\" /></div>");
		}

		sm.append(articleDisplay.getDescription());

		summary = sm.toString();

		PortletURL articleURL = renderResponse.createRenderURL();

		articleURL.setParameter("struts_action", "/tagged_content/view_content");
		articleURL.setParameter("redirect", currentURL);
		articleURL.setParameter("assetId", String.valueOf(asset.getAssetId()));

		viewURL = articleURL.toString();

		viewURLMessage = "read-more";
	}
	else {
		show = false;
	}
}
else if (className.equals(WikiPage.class.getName())) {
	WikiPageResource pageResource = WikiPageResourceLocalServiceUtil.getPageResource(classPK);

	WikiPage wikiPage = WikiPageLocalServiceUtil.getPage(pageResource.getNodeId(), pageResource.getTitle());

	PortletURL pageURL = new PortletURLImpl(request, PortletKeys.WIKI, plid.longValue(), true);

	pageURL.setWindowState(WindowState.MAXIMIZED);
	pageURL.setPortletMode(PortletMode.VIEW);

	pageURL.setParameter("struts_action", "/wiki/view");
	pageURL.setParameter("title", wikiPage.getTitle());

	viewURL = pageURL.toString();
}

// URLs set through the asset override automatically generated URLs

if (Validator.isNotNull(asset.getUrl())) {
	viewURL = asset.getUrl();
}
%>

<c:if test="<%= show %>">
	<div class="portlet-journal-abstract">
		<c:choose>
			<c:when test="<%= Validator.isNotNull(viewURL) %>">
				<h3 class="journal-content-title"><a href="<%= viewURL %>"><%= title %></a></h3>
			</c:when>
			<c:otherwise>
				<h3 class="journal-content-title"><%= title %></h3>
			</c:otherwise>
		</c:choose>

		<div class="portlet-journal-metadata">
			<%@ include file="/html/portlet/tagged_content/asset_metadata.jspf" %>
		</div>

		<p class="portlet-journal-summary">
			<%= summary %>
		</p>

		<c:if test="<%= Validator.isNotNull(viewURL) %>">
			<div class="portlet-journal-more">
				<a href="<%= viewURL %>"><liferay-ui:message key="<%= viewURLMessage %>" /></a>
			</div>
		</c:if>
	</div>

	<div>
		<br />

		<%@ include file="/html/portlet/tagged_content/asset_actions.jspf" %>
	</div>

	<c:if test="<%= (assetIndex + 1) < results.size() %>">
		<div class="separator"><!-- --></div>
	</c:if>
</c:if>