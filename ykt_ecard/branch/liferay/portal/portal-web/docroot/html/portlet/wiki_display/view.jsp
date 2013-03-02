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

<%@ include file="/html/portlet/wiki_display/init.jsp" %>

<%
WikiNode node = (WikiNode)request.getAttribute(WebKeys.WIKI_NODE);
WikiPage wikiPage = (WikiPage)request.getAttribute(WebKeys.WIKI_PAGE);
%>

<div class="breadcrumbs">
	<a href="<portlet:renderURL><portlet:param name="struts_action" value="/wiki_display/view" /><portlet:param name="nodeId" value="<%= String.valueOf(node.getNodeId()) %>" /><portlet:param name="title" value="<%= WikiPageImpl.FRONT_PAGE %>" /></portlet:renderURL>">
	<%= node.getName() %>
	</a>

	&raquo;

	<a href="<portlet:renderURL><portlet:param name="struts_action" value="/wiki_display/view" /><portlet:param name="nodeId" value="<%= String.valueOf(node.getNodeId()) %>" /><portlet:param name="title" value="<%= wikiPage.getTitle() %>" /></portlet:renderURL>">
	<%= wikiPage.getTitle() %>
	</a>
</div>

<%@ include file="/html/portlet/wiki/view_page_content.jspf" %>

<c:if test="<%= WikiPagePermission.contains(permissionChecker, wikiPage, ActionKeys.UPDATE) %>">

	<%
	PortletURL portletURL = renderResponse.createRenderURL();

	portletURL.setWindowState(WindowState.MAXIMIZED);

	portletURL.setParameter("struts_action", "/wiki_display/edit_page");
	portletURL.setParameter("redirect", currentURL);
	portletURL.setParameter("nodeId", String.valueOf(node.getNodeId()));
	portletURL.setParameter("title", wikiPage.getTitle());
	%>

	<liferay-ui:icon image="edit" url="<%= portletURL.toString() %>" />
</c:if>

<c:if test="<%= WikiPagePermission.contains(permissionChecker, wikiPage, ActionKeys.PERMISSIONS) %>">
	<liferay-security:permissionsURL
		modelResource="<%= WikiPage.class.getName() %>"
		modelResourceDescription="<%= wikiPage.getTitle() %>"
		resourcePrimKey="<%= String.valueOf(wikiPage.getPageId()) %>"
		var="permissionsURL"
	/>

	<liferay-ui:icon image="permissions" url="<%= permissionsURL %>" />
</c:if>

<c:if test="<%= WikiPagePermission.contains(permissionChecker, wikiPage, ActionKeys.ADD_DISCUSSION) %>">
	<c:choose>
		<c:when test="<%= windowState.equals(WindowState.MAXIMIZED) %>">

			<br /><br />

			<liferay-ui:tabs names="comments" />

			<portlet:actionURL var="discussionURL">
				<portlet:param name="struts_action" value="/wiki_display/edit_page_discussion" />
			</portlet:actionURL>

			<liferay-ui:discussion
				formName="fm"
				formAction="<%= discussionURL %>"
				className="<%= WikiPage.class.getName() %>"
				classPK="<%= wikiPage.getResourcePrimKey() %>"
				userId="<%= wikiPage.getUserId() %>"
				subject="<%= wikiPage.getTitle() %>"
				redirect="<%= currentURL %>"
			/>
		</c:when>
		<c:otherwise>

			<%
			currentURLObj.setWindowState(WindowState.MAXIMIZED);
			%>

			<liferay-ui:icon
				image="reply"
				message="comments"
				url="<%= currentURLObj.toString() %>"
			/>
		</c:otherwise>
	</c:choose>
</c:if>