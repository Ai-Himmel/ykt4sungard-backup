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

<%@ include file="/html/portlet/wiki/init.jsp" %>

<%
WikiNode node = (WikiNode)request.getAttribute(WebKeys.WIKI_NODE);
WikiPage wikiPage = (WikiPage)request.getAttribute(WebKeys.WIKI_PAGE);

PortletURL addPageURL = renderResponse.createRenderURL();

addPageURL.setWindowState(WindowState.MAXIMIZED);

addPageURL.setParameter("nodeId", String.valueOf(node.getNodeId()));
%>

<script type="text/javascript">
	function <portlet:namespace />addPage() {
		var pageName = prompt('<liferay-ui:message key="page-name" /> (<liferay-ui:message key="use-camel-case-syntax" />)', '');

		window.location = '<%= addPageURL.toString() %>&<%= renderResponse.getNamespace() %>title=' + pageName;
	}
</script>

<liferay-util:include page="/html/portlet/wiki/node_tabs.jsp" />

<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" varImpl="searchURL"><portlet:param name="struts_action" value="/wiki/search" /></liferay-portlet:renderURL>

<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="searchURL" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= currentURL %>" />
<input name="<portlet:namespace />nodeId" type="hidden" value="<%= node.getNodeId() %>" />

<input name="<portlet:namespace />keywords" size="30" type="text" />

<input type="submit" value="<liferay-ui:message key="search" />" />

</form>

<br />

<%@ include file="/html/portlet/wiki/page_name.jspf" %>

<div>
	<%@ include file="/html/portlet/wiki/view_page_content.jspf" %>
</div>

<liferay-ui:icon-menu align="left">

	<%
	PortletURL portletURL = renderResponse.createRenderURL();

	portletURL.setWindowState(WindowState.MAXIMIZED);

	portletURL.setParameter("redirect", currentURL);
	portletURL.setParameter("nodeId", String.valueOf(node.getNodeId()));
	portletURL.setParameter("title", wikiPage.getTitle());
	%>

	<c:if test="<%= WikiPagePermission.contains(permissionChecker, wikiPage, ActionKeys.UPDATE) %>">

		<%
		portletURL.setParameter("struts_action", "/wiki/edit_page");
		%>

		<liferay-ui:icon image="edit" url="<%= portletURL.toString() %>" />
	</c:if>

	<c:if test="<%= WikiPagePermission.contains(permissionChecker, wikiPage, ActionKeys.PERMISSIONS) %>">
		<liferay-security:permissionsURL
			modelResource="<%= WikiPage.class.getName() %>"
			modelResourceDescription="<%= wikiPage.getTitle() %>"
			resourcePrimKey="<%= String.valueOf(wikiPage.getResourcePrimKey()) %>"
			var="permissionsURL"
		/>

		<liferay-ui:icon image="permissions" url="<%= permissionsURL %>" />
	</c:if>

	<liferay-ui:icon image="add_article" message="add-page" url='<%= "javascript: " + renderResponse.getNamespace() + "addPage();" %>' />

	<%
	portletURL.setParameter("struts_action", "/wiki/view_page_links");
	%>

	<liferay-ui:icon image="links" message="page-links" url="<%= portletURL.toString() %>" />

	<%
	portletURL.setParameter("struts_action", "/wiki/view_page_history");
	%>

	<liferay-ui:icon image="history" message="page-history" url="<%= portletURL.toString() %>" />

	<%
	portletURL.setParameter("struts_action", "/wiki/view_recent_changes");
	%>

	<liferay-ui:icon image="recent_changes" message="recent-changes" url="<%= portletURL.toString() %>" />

	<%
	portletURL.setParameter("struts_action", "/wiki/view_all_pages");
	%>

	<liferay-ui:icon image="all_pages" message="all-pages" url="<%= portletURL.toString() %>" />

	<%
	portletURL.setParameter("struts_action", "/wiki/view_orphan_pages");
	%>

	<liferay-ui:icon image="orphan_pages" message="orphan-pages" url="<%= portletURL.toString() %>" />

	<%
	if (themeDisplay.isSignedIn()) {
		if (PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.WIKI, ActionKeys.ADD_NODE)) {

			portletURL.setParameter("struts_action", "/wiki/view_nodes");
	%>

			<liferay-ui:icon image="manage_task" message="administer-nodes" url="<%= portletURL.toString() %>" />

	<%
		}
	}
	%>

</liferay-ui:icon-menu>

<c:if test="<%= WikiPagePermission.contains(permissionChecker, wikiPage, ActionKeys.ADD_DISCUSSION) %>">
	<br /><br />

	<liferay-ui:tabs names="comments" />

	<portlet:actionURL var="discussionURL">
		<portlet:param name="struts_action" value="/wiki/edit_page_discussion" />
	</portlet:actionURL>

	<liferay-ui:discussion
		formName="fm2"
		formAction="<%= discussionURL %>"
		className="<%= WikiPage.class.getName() %>"
		classPK="<%= wikiPage.getResourcePrimKey() %>"
		userId="<%= wikiPage.getUserId() %>"
		subject="<%= wikiPage.getTitle() %>"
		redirect="<%= currentURL %>"
	/>
</c:if>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />keywords);
	</script>
</c:if>