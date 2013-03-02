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

<%@ include file="/html/portlet/message_boards/init.jsp" %>

<%
ResultRow row = (ResultRow)request.getAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW);

MBMessage message = (MBMessage)row.getObject();

MBCategory category = message.getCategory();
%>

<liferay-ui:icon-menu>
	<c:if test="<%= MBMessagePermission.contains(permissionChecker, message, ActionKeys.UPDATE) %>">
		<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="editURL">
			<portlet:param name="struts_action" value="/message_boards/edit_message" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="messageId" value="<%= String.valueOf(message.getMessageId()) %>" />
		</portlet:renderURL>

		<liferay-ui:icon image="edit" url="<%= editURL %>" />
	</c:if>

	<c:if test="<%= MBMessagePermission.contains(permissionChecker, message, ActionKeys.PERMISSIONS) %>">
		<liferay-security:permissionsURL
			modelResource="<%= MBMessage.class.getName() %>"
			modelResourceDescription="<%= message.getSubject() %>"
			resourcePrimKey="<%= String.valueOf(message.getMessageId()) %>"
			var="permissionsURL"
		/>

		<liferay-ui:icon image="permissions" url="<%= permissionsURL %>" />
	</c:if>

	<liferay-ui:icon image="rss" url='<%= themeDisplay.getPathMain() + "/message_boards/rss?p_l_id=" + plid + "&threadId=" + message.getThreadId() + rssURLParams %>' target="_blank" />

	<c:if test="<%= MBMessagePermission.contains(permissionChecker, message, ActionKeys.SUBSCRIBE) %>">
		<c:choose>
			<c:when test="<%= SubscriptionLocalServiceUtil.isSubscribed(user.getCompanyId(), user.getUserId(), MBThread.class.getName(), message.getThreadId()) %>">
				<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="unsubscribeURL">
					<portlet:param name="struts_action" value="/message_boards/edit_message" />
					<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.UNSUBSCRIBE %>" />
					<portlet:param name="redirect" value="<%= currentURL %>" />
					<portlet:param name="messageId" value="<%= String.valueOf(message.getMessageId()) %>" />
				</portlet:actionURL>

				<liferay-ui:icon image="unsubscribe" url="<%= unsubscribeURL %>" />
			</c:when>
			<c:otherwise>
				<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="subscribeURL">
					<portlet:param name="struts_action" value="/message_boards/edit_message" />
					<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.SUBSCRIBE %>" />
					<portlet:param name="redirect" value="<%= currentURL %>" />
					<portlet:param name="messageId" value="<%= String.valueOf(message.getMessageId()) %>" />
				</portlet:actionURL>

				<liferay-ui:icon image="subscribe" url="<%= subscribeURL %>" />
			</c:otherwise>
		</c:choose>
	</c:if>

	<c:if test="<%= MBCategoryPermission.contains(permissionChecker, category, ActionKeys.MOVE_THREAD) %>">
		<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="moveThreadURL">
			<portlet:param name="struts_action" value="/message_boards/move_thread" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="threadId" value="<%= String.valueOf(message.getThreadId()) %>" />
		</portlet:renderURL>

		<liferay-ui:icon image="forward" message="move-thread" url="<%= moveThreadURL %>" />
	</c:if>

	<c:if test="<%= MBMessagePermission.contains(permissionChecker, message, ActionKeys.DELETE) %>">
		<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="deleteURL">
			<portlet:param name="struts_action" value="/message_boards/edit_message" />
			<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.DELETE %>" />
			<portlet:param name="redirect" value="<%= currentURL %>" />
			<portlet:param name="messageId" value="<%= String.valueOf(message.getMessageId()) %>" />
		</portlet:actionURL>

		<liferay-ui:icon-delete url="<%= deleteURL %>" />
	</c:if>
</liferay-ui:icon-menu>