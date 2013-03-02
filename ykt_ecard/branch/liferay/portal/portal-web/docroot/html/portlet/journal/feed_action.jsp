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

<%@ include file="/html/portlet/journal/init.jsp" %>

<%
ResultRow row = (ResultRow)request.getAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW);

JournalFeed feed = (JournalFeed)row.getObject();
%>

<liferay-ui:icon-menu>
	<c:if test="<%= JournalFeedPermission.contains(permissionChecker, feed, ActionKeys.UPDATE) %>">
		<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="editeFeedURL">
			<portlet:param name="struts_action" value="/journal/edit_feed" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="groupId" value="<%= String.valueOf(feed.getGroupId()) %>" />
			<portlet:param name="feedId" value="<%= feed.getFeedId() %>" />
		</portlet:renderURL>

		<liferay-ui:icon image="edit" url="<%= editeFeedURL %>" />
	</c:if>

	<c:if test="<%= JournalFeedPermission.contains(permissionChecker, feed, ActionKeys.PERMISSIONS) %>">
		<liferay-security:permissionsURL
			modelResource="<%= JournalFeed.class.getName() %>"
			modelResourceDescription="<%= feed.getName() %>"
			resourcePrimKey="<%= String.valueOf(feed.getId()) %>"
			var="permissionsFeedURL"
		/>

		<liferay-ui:icon image="permissions" url="<%= permissionsFeedURL %>" />
	</c:if>

	<c:if test="<%= JournalFeedPermission.contains(permissionChecker, feed, ActionKeys.DELETE) %>">
		<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="deleteFeedURL">
			<portlet:param name="struts_action" value="/journal/edit_feed" />
			<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.DELETE %>" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="groupId" value="<%= String.valueOf(feed.getGroupId()) %>" />
			<portlet:param name="deleteFeedIds" value="<%= feed.getFeedId() %>" />
		</portlet:actionURL>

		<liferay-ui:icon-delete url="<%= deleteFeedURL %>" />
	</c:if>
</liferay-ui:icon-menu>