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

String className = (String)request.getAttribute("view.jsp-className");
long classPK = ((Long)request.getAttribute("view.jsp-classPK")).longValue();

boolean show = ((Boolean)request.getAttribute("view.jsp-show")).booleanValue();
%>

<c:choose>
	<c:when test="<%= className.equals(BlogsEntry.class.getName()) %>">

		<%
		BlogsEntry entry = BlogsEntryLocalServiceUtil.getEntry(classPK);
		%>

		<h3 class="journal-content-title"><%= title %></h3>

		<%= entry.getContent() %>

		<br />

		<a href="<%= themeDisplay.getPathMain() %>/blogs/find_entry?entryId=<%= entry.getEntryId() %>"><liferay-ui:message key="view-in-context" /> &raquo;</a>

		<c:if test="<%= enableRatings %>">
			<liferay-ui:ratings
				className="<%= BlogsEntry.class.getName() %>"
				classPK="<%= entry.getEntryId() %>"
				url='<%= themeDisplay.getPathMain() + "/blogs/rate_entry" %>'
			/>
		</c:if>

		<c:if test="<%= enableComments %>">
			<br />

			<portlet:actionURL var="discussionURL">
				<portlet:param name="struts_action" value="/tagged_content/edit_entry_discussion" />
			</portlet:actionURL>

			<liferay-ui:discussion
				formName='<%= "fm" + entry.getEntryId() %>'
				formAction="<%= discussionURL %>"
				className="<%= BlogsEntry.class.getName() %>"
				classPK="<%= entry.getEntryId() %>"
				userId="<%= entry.getUserId() %>"
				subject="<%= entry.getTitle() %>"
				redirect="<%= currentURL %>"
			/>
		</c:if>
	</c:when>
	<c:when test="<%= className.equals(BookmarksEntry.class.getName()) %>">

		<%
		BookmarksEntry entry = BookmarksEntryLocalServiceUtil.getEntry(classPK);
		%>

		<h3 class="journal-content-title"><%= title %></h3>

		<a href="<%= themeDisplay.getPathMain() %>/bookmarks/open_entry?entryId=<%= entry.getEntryId() %>" target="_blank"><%= entry.getName() %></a>

		<p class="journal-content-field-comments"><%= entry.getComments() %></p>
	</c:when>
	<c:when test="<%= className.equals(DLFileEntry.class.getName()) %>">

		<%
		DLFileEntry fileEntry = DLFileEntryLocalServiceUtil.getFileEntry(classPK);
		%>

		<h3 class="journal-content-title"><%= title %></h3>

		<a href="<%= themeDisplay.getPathMain() %>/document_library/get_file?p_l_id=<%= themeDisplay.getPlid() %>&folderId=<%= fileEntry.getFolderId() %>&name=<%= HttpUtil.encodeURL(fileEntry.getName()) %>">
		<img align="left" border="0" src="<%= themeDisplay.getPathThemeImages() %>/document_library/<%= DLUtil.getFileExtension(fileEntry.getName()) %>.png" /><%= fileEntry.getTitle() %>
		</a>

		<p class="journal-content-field-description"><%= fileEntry.getDescription() %></p>

		<c:if test="<%= enableRatings %>">
			<br />

			<liferay-ui:ratings
				className="<%= DLFileEntry.class.getName() %>"
				classPK="<%= fileEntry.getFileEntryId() %>"
				url='<%= themeDisplay.getPathMain() + "/document_library/rate_file_entry" %>'
			/>
		</c:if>

		<c:if test="<%= enableComments %>">
			<br />

			<portlet:actionURL var="discussionURL">
				<portlet:param name="struts_action" value="/tagged_content/edit_file_entry_discussion" />
			</portlet:actionURL>

			<liferay-ui:discussion
				formName='<%= "fm" + fileEntry.getFileEntryId() %>'
				formAction="<%= discussionURL %>"
				className="<%= DLFileEntry.class.getName() %>"
				classPK="<%= fileEntry.getFileEntryId() %>"
				userId="<%= fileEntry.getUserId() %>"
				subject="<%= fileEntry.getTitle() %>"
				redirect="<%= currentURL %>"
			/>
		</c:if>
	</c:when>
	<c:when test="<%= className.equals(IGImage.class.getName()) %>">

		<%
		IGImage image = IGImageLocalServiceUtil.getImage(classPK);
		%>

		<h3 class="journal-content-title"><%= title %></h3>

		<img border="1" src="<%= themeDisplay.getPathImage() %>/image_gallery?img_id=<%= image.getLargeImageId() %>&t=<%= ImageServletTokenUtil.getToken(image.getLargeImageId()) %>" />

		<p class="journal-content-field-description"><%= image.getDescription() %></p>
	</c:when>
	<c:when test="<%= className.equals(JournalArticle.class.getName()) %>">

		<%
		JournalArticleResource articleResource = JournalArticleResourceLocalServiceUtil.getArticleResource(classPK);

		String languageId = LanguageUtil.getLanguageId(request);
		int articlePage = ParamUtil.getInteger(request, "page", 1);
		String xmlRequest = PortletRequestUtil.toXML(renderRequest, renderResponse);

		JournalArticleDisplay articleDisplay = JournalContentUtil.getDisplay(articleResource.getGroupId(), articleResource.getArticleId(), null, languageId, themeDisplay, articlePage, xmlRequest);

		if (articleDisplay == null) {

			// No version has been approved yet, the article should not be rendered

			show = false;
		}
		%>

		<c:if test="<%= articleDisplay != null %>">
			<h3 class="journal-content-title"><%= title %></h3>

			<c:if test="<%= showAvailableLocales %>">

				<%
				String[] availableLocales = articleDisplay.getAvailableLocales();
				%>

				<c:if test="<%= availableLocales.length > 0 %>">
					<div>
						<br />

						<liferay-ui:language languageIds="<%= availableLocales %>" displayStyle="<%= 0 %>" />
					</div>
				</c:if>
			</c:if>

			<%= articleDisplay.getContent() %>

			<c:if test="<%= articleDisplay.isPaginate() %>">

				<%
				String pageRedirect = ParamUtil.getString(request, "redirect");

				if (Validator.isNull(pageRedirect)) {
					pageRedirect = currentURL;
				}

				int cur = ParamUtil.getInteger(request, "cur");

				PortletURL articlePageURL = renderResponse.createRenderURL();

				articlePageURL.setParameter("struts_action", "/tagged_content/view_content");
				articlePageURL.setParameter("redirect", pageRedirect);
				articlePageURL.setParameter("assetId", String.valueOf(asset.getAssetId()));
				articlePageURL.setParameter("cur", String.valueOf(cur));
				%>

				<br />

				<liferay-ui:page-iterator
					curParam="<%= "page" %>"
					curValue="<%= articleDisplay.getCurrentPage() %>"
					delta="<%= 1 %>"
					maxPages="<%= 25 %>"
					total="<%= articleDisplay.getNumberOfPages() %>"
					type="article"
					url="<%= articlePageURL.toString() %>"
				/>

				<br />
			</c:if>

			<c:if test="<%= enableRatings %>">
				<br />

				<liferay-ui:ratings
					className="<%= JournalArticle.class.getName() %>"
					classPK="<%= articleDisplay.getResourcePrimKey() %>"
					url='<%= themeDisplay.getPathMain() + "/journal_content/rate_article" %>'
				/>
			</c:if>

			<c:if test="<%= enableComments %>">
				<br />

				<portlet:actionURL var="discussionURL">
					<portlet:param name="struts_action" value="/tagged_content/edit_article_discussion" />
				</portlet:actionURL>

				<liferay-ui:discussion
					formName='<%= "fm" + articleDisplay.getResourcePrimKey() %>'
					formAction="<%= discussionURL %>"
					className="<%= JournalArticle.class.getName() %>"
					classPK="<%= articleDisplay.getResourcePrimKey() %>"
					userId="<%= articleDisplay.getUserId() %>"
					subject="<%= articleDisplay.getTitle() %>"
					redirect="<%= currentURL %>"
				/>
			</c:if>
		</c:if>
	</c:when>
	<c:when test="<%= className.equals(MBMessage.class.getName()) %>">

		<%
		MBMessage message = MBMessageLocalServiceUtil.getMessage(classPK);
		%>

		<h3 class="journal-content-title"><%= message.getSubject() %></h3>

		<br /><br />

		<%= message.getBody() %>
	</c:when>
	<c:when test="<%= className.equals(WikiPage.class.getName()) %>">
		<h3 class="journal-content-title"><%= title %></h3>

		<div class="wiki-body">

			<%
			WikiPageResource pageResource = WikiPageResourceLocalServiceUtil.getPageResource(classPK);

			WikiPage wikiPage = WikiPageLocalServiceUtil.getPage(pageResource.getNodeId(), pageResource.getTitle());

			WikiNode node = wikiPage.getNode();
			%>

			<c:if test="<%= wikiPage.getFormat().equals(WikiPageImpl.HTML_FORMAT) %>">
				<%= wikiPage.getContent() %>
			</c:if>

			<c:if test="<%= wikiPage.getFormat().equals(WikiPageImpl.CLASSIC_WIKI_FORMAT) %>">

				<%
				PortletURL pageURL = new PortletURLImpl(request, PortletKeys.WIKI, plid.longValue(), true);

				pageURL.setWindowState(WindowState.MAXIMIZED);
				pageURL.setPortletMode(PortletMode.VIEW);

				pageURL.setParameter("struts_action", "/wiki/view");
				%>

				<%= WikiUtil.convert(WikiUtil.getFilter(pageURL, node.getNodeId()), wikiPage.getContent()) %>
			</c:if>

			<c:if test="<%= wikiPage.getFormat().equals(WikiPageImpl.PLAIN_TEXT_FORMAT) %>">
<pre>
<%= wikiPage.getContent() %>
</pre>
			</c:if>
		</div>

		<c:if test="<%= enableComments %>">
			<br />

			<portlet:actionURL var="discussionURL">
				<portlet:param name="struts_action" value="/tagged_content/edit_page_discussion" />
			</portlet:actionURL>

			<liferay-ui:discussion
				formName='<%= "fm" + wikiPage.getResourcePrimKey() %>'
				formAction="<%= discussionURL %>"
				className="<%= WikiPage.class.getName() %>"
				classPK="<%= wikiPage.getResourcePrimKey() %>"
				userId="<%= wikiPage.getUserId() %>"
				subject="<%= wikiPage.getTitle() %>"
				redirect="<%= currentURL %>"
			/>
		</c:if>
	</c:when>
	<c:otherwise>
		<%= className %> is not a valid type.
	</c:otherwise>
</c:choose>

<c:if test="<%= show %>">
	<div class="portlet-journal-metadata">
		<%@ include file="/html/portlet/tagged_content/asset_metadata.jspf" %>
	</div>

	<div>
		<br />

		<%@ include file="/html/portlet/tagged_content/asset_actions.jspf" %>
	</div>

	<c:if test="<%= (assetIndex + 1) < results.size() %>">
		<div class="separator"><!-- --></div>
	</c:if>
</c:if>