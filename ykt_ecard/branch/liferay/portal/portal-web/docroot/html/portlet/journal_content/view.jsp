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

<%@ include file="/html/portlet/journal_content/init.jsp" %>

<%
JournalArticleDisplay articleDisplay = (JournalArticleDisplay)request.getAttribute(WebKeys.JOURNAL_ARTICLE_DISPLAY);
%>

<c:choose>
	<c:when test="<%= themeDisplay.isStateExclusive() %>">

		<%
		RuntimeLogic portletLogic = new PortletLogic(application, request, response, renderRequest, renderResponse);
		RuntimeLogic actionURLLogic = new ActionURLLogic(renderResponse);
		RuntimeLogic renderURLLogic = new RenderURLLogic(renderResponse);

		String content = articleDisplay.getContent();

		content = RuntimePortletUtil.processXML(request, content, portletLogic);
		content = RuntimePortletUtil.processXML(request, content, actionURLLogic);
		content = RuntimePortletUtil.processXML(request, content, renderURLLogic);
		%>

		<%= content %>
	</c:when>
	<c:otherwise>
		<c:choose>
			<c:when test="<%= articleDisplay != null %>">

				<%
				RuntimeLogic portletLogic = new PortletLogic(application, request, response, renderRequest, renderResponse);
				RuntimeLogic actionURLLogic = new ActionURLLogic(renderResponse);
				RuntimeLogic renderURLLogic = new RenderURLLogic(renderResponse);

				String content = articleDisplay.getContent();

				content = RuntimePortletUtil.processXML(request, content, portletLogic);
				content = RuntimePortletUtil.processXML(request, content, actionURLLogic);
				content = RuntimePortletUtil.processXML(request, content, renderURLLogic);

				PortletURL portletURL = renderResponse.createRenderURL();
				%>

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

				<span class="journal-content-article" id="<%= articleDisplay.getGroupId() %>_<%= articleDisplay.getArticleId() %>_<%= articleDisplay.getVersion() %>">
				<%= content %>
				</span>

				<c:if test="<%= articleDisplay.isPaginate() %>">
					<liferay-ui:page-iterator
						curParam='<%= "page" %>'
						curValue="<%= articleDisplay.getCurrentPage() %>"
						delta="<%= 1 %>"
						maxPages="<%= 25 %>"
						total="<%= articleDisplay.getNumberOfPages() %>"
						type="article"
						url="<%= portletURL.toString() %>"
					/>

					<br />
				</c:if>
			</c:when>
			<c:when test="<%= portletDisplay.isShowConfigurationIcon() %>">
				<br />

				<liferay-ui:message key="select-an-existing-article-or-add-an-article-to-be-displayed-in-this-portlet" />

				<br />

				<c:if test="<%= Validator.isNotNull(articleId) %>">
					<br />

					<span class="portlet-msg-error">
					<%= LanguageUtil.format(pageContext, "x-is-expired,-is-not-approved,-does-not-have-any-content,-or-no-longer-exists", articleId) %>
					</span>

					<br />
				</c:if>
			</c:when>
		</c:choose>

		<%
		JournalArticle article = null;

		try {
			article = JournalArticleLocalServiceUtil.getLatestArticle(groupId, articleId);
		}
		catch (NoSuchArticleException nsae) {
		}

		boolean showEditArticleIcon = (article != null) && JournalArticlePermission.contains(permissionChecker, article, ActionKeys.UPDATE);
		boolean showSelectArticleIcon = PortletPermissionUtil.contains(permissionChecker, plid.longValue(), portletDisplay.getId(), ActionKeys.CONFIGURATION);
		boolean showAddArticleIcon = PortletPermissionUtil.contains(permissionChecker, plid.longValue(), portletDisplay.getId(), ActionKeys.CONFIGURATION) && PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.JOURNAL, ActionKeys.ADD_ARTICLE) && PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.JOURNAL, ActionKeys.APPROVE_ARTICLE);
		%>

		<c:if test="<%= themeDisplay.isSignedIn() && (showEditArticleIcon || showSelectArticleIcon || showAddArticleIcon) %>">
			<div>
				<br />

				<c:if test="<%= showEditArticleIcon %>">
					<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="editURL" portletName="<%= PortletKeys.JOURNAL %>">
						<portlet:param name="struts_action" value="/journal/edit_article" />
						<portlet:param name="redirect" value="<%= currentURL %>" />
						<portlet:param name="groupId" value="<%= String.valueOf(article.getGroupId()) %>" />
						<portlet:param name="articleId" value="<%= article.getArticleId() %>" />
						<portlet:param name="version" value="<%= String.valueOf(article.getVersion()) %>" />
					</liferay-portlet:renderURL>

					<liferay-ui:icon image="edit" message="edit-article" url="<%= editURL %>" />
				</c:if>

				<c:if test="<%= showSelectArticleIcon %>">
					<liferay-ui:icon image="configuration" message="select-article" url="<%= portletDisplay.getURLConfiguration() %>" />
				</c:if>

				<c:if test="<%= showAddArticleIcon %>">
					<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="addArticleURL" portletName="<%= PortletKeys.JOURNAL %>">
						<portlet:param name="struts_action" value="/journal/edit_article" />
						<portlet:param name="portletResource" value="<%= portletDisplay.getId() %>" />
						<portlet:param name="redirect" value="<%= currentURL %>" />
					</liferay-portlet:renderURL>

					<liferay-ui:icon image="add_article" message="add-article" url="<%= addArticleURL %>" />
				</c:if>
			</div>
		</c:if>

		<c:if test="<%= (articleDisplay != null) && (enableRatings || enableComments) %>">
			<div>
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
						<portlet:param name="struts_action" value="/journal_content/edit_article_discussion" />
					</portlet:actionURL>

					<liferay-ui:discussion
						formAction="<%= discussionURL %>"
						className="<%= JournalArticle.class.getName() %>"
						classPK="<%= articleDisplay.getResourcePrimKey() %>"
						userId="<%= articleDisplay.getUserId() %>"
						subject="<%= articleDisplay.getTitle() %>"
						redirect="<%= currentURL %>"
					/>
				</c:if>
			</div>
		</c:if>
	</c:otherwise>
</c:choose>