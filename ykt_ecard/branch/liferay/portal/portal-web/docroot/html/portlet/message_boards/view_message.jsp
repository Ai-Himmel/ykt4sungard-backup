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
MBMessageDisplay messageDisplay = (MBMessageDisplay)request.getAttribute(WebKeys.MESSAGE_BOARDS_MESSAGE);

MBMessage message = messageDisplay.getMessage();

MBCategory category = messageDisplay.getCategory();

MBThread thread = messageDisplay.getThread();

MBMessage previousMessage = messageDisplay.getPreviousMessage();
MBMessage nextMessage = messageDisplay.getNextMessage();

MBMessage firstMessage = messageDisplay.getFirstMessage();
MBMessage lastMessage = messageDisplay.getLastMessage();

boolean isFirstMessage = messageDisplay.isFirstMessage();
boolean isLastMessage = messageDisplay.isLastMessage();

MBThread previousThread = messageDisplay.getPreviousThread();
MBThread nextThread = messageDisplay.getNextThread();

MBThread firstThread = messageDisplay.getFirstThread();
MBThread lastThread = messageDisplay.getLastThread();

boolean isFirstThread = messageDisplay.isFirstThread();
boolean isLastThread = messageDisplay.isLastThread();

PortalPreferences portalPrefs = PortletPreferencesFactoryUtil.getPortalPreferences(request);

String threadView = ParamUtil.getString(request, "threadView");

if (Validator.isNotNull(threadView)) {
	portalPrefs.setValue(PortletKeys.MESSAGE_BOARDS, "thread-view", threadView);
}
else {
	threadView = portalPrefs.getValue(PortletKeys.MESSAGE_BOARDS, "thread-view", "combination");
}
%>

<script type="text/javascript">
	<c:if test="<%= thread.getRootMessageId() != message.getMessageId() %>">
		jQuery(document).ready(
			function() {
				document.getElementById("<portlet:namespace />message_" + <%= message.getMessageId() %>).scrollIntoView(true);
			}
		);
	</c:if>
</script>

<form>
<input name="<portlet:namespace />breadcrumbsCategoryId" type="hidden" value="<%= category.getCategoryId() %>" />
<input name="<portlet:namespace />breadcrumbsMessageId" type="hidden" value="<%= message.getMessageId() %>" />
<input name="<portlet:namespace />threadId" type="hidden" value="<%= message.getThreadId() %>" />

<liferay-util:include page="/html/portlet/message_boards/tabs1.jsp" />

<table cellpadding="0" cellspacing="0" width="100%">
<tr>
	<td width="99%">
		<div class="breadcrumbs">
			<%= MBUtil.getBreadcrumbs(null, message, pageContext, renderRequest, renderResponse) %>
		</div>
	</td>
	<td>

		<%
		currentURLObj.setParameter("threadView", "combination");
		%>

		<liferay-ui:icon
			image="../message_boards/thread_view_combination"
			message="combination-view"
			url="<%= currentURLObj.toString() %>"
		/>
	</td>
	<td>

		<%
		currentURLObj.setParameter("threadView", "flat");
		%>

		<liferay-ui:icon
			image="../message_boards/thread_view_flat"
			message="flat-view"
			url="<%= currentURLObj.toString() %>"
		/>
	</td>
	<td>

		<%
		currentURLObj.setParameter("threadView", "tree");
		%>

		<liferay-ui:icon
			image="../message_boards/thread_view_tree"
			message="tree-view"
			url="<%= currentURLObj.toString() %>"
		/>
	</td>
</tr>
</table>

<div class="thread-controls">
	<div class="thread-navigation">
		<liferay-ui:message key="threads" />

		[

		<c:if test="<%= previousThread != null %>">
			<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/view_message" /><portlet:param name="messageId" value="<%= String.valueOf(previousThread.getRootMessageId()) %>" /></portlet:renderURL>">
		</c:if>

		<liferay-ui:message key="previous" />

		<c:if test="<%= previousThread != null %>">
			</a>
		</c:if>

		|

		<c:if test="<%= nextThread != null %>">
			<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/view_message" /><portlet:param name="messageId" value="<%= String.valueOf(nextThread.getRootMessageId()) %>" /></portlet:renderURL>">
		</c:if>

		<liferay-ui:message key="next" />

		<c:if test="<%= nextThread != null %>">
			</a>
		</c:if>

		]
	</div>

	<div class="thread-actions">
		<table class="lfr-table">
		<tr>
			<c:if test="<%= MBCategoryPermission.contains(permissionChecker, category, ActionKeys.ADD_MESSAGE) %>">
				<td>
					<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="addMessageURL">
						<portlet:param name="struts_action" value="/message_boards/edit_message" />
						<portlet:param name="redirect" value="<%= currentURL %>" />
						<portlet:param name="categoryId" value="<%= String.valueOf(category.getCategoryId()) %>" />
					</portlet:renderURL>

					<liferay-ui:icon image="post" message="post-new-thread" url="<%= addMessageURL %>" label="<%= true %>" />
				</td>
			</c:if>

			<c:if test="<%= MBMessagePermission.contains(permissionChecker, message, ActionKeys.SUBSCRIBE) %>">
				<td>
					<c:choose>
						<c:when test="<%= SubscriptionLocalServiceUtil.isSubscribed(user.getCompanyId(), user.getUserId(), MBThread.class.getName(), message.getThreadId()) %>">
							<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="unsubscribeURL">
								<portlet:param name="struts_action" value="/message_boards/edit_message" />
								<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.UNSUBSCRIBE %>" />
								<portlet:param name="redirect" value="<%= currentURL %>" />
								<portlet:param name="messageId" value="<%= String.valueOf(message.getMessageId()) %>" />
							</portlet:actionURL>

							<liferay-ui:icon image="unsubscribe" url="<%= unsubscribeURL %>" label="<%= true %>" />
						</c:when>
						<c:otherwise>
							<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="subscribeURL">
								<portlet:param name="struts_action" value="/message_boards/edit_message" />
								<portlet:param name="<%= Constants.CMD %>" value="<%= Constants.SUBSCRIBE %>" />
								<portlet:param name="redirect" value="<%= currentURL %>" />
								<portlet:param name="messageId" value="<%= String.valueOf(message.getMessageId()) %>" />
							</portlet:actionURL>

							<liferay-ui:icon image="subscribe" url="<%= subscribeURL %>" label="<%= true %>" />
						</c:otherwise>
					</c:choose>
				</td>
			</c:if>

			<c:if test="<%= MBCategoryPermission.contains(permissionChecker, category, ActionKeys.MOVE_THREAD) %>">
				<td>
					<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="editThreadURL">
						<portlet:param name="struts_action" value="/message_boards/move_thread" />
						<portlet:param name="redirect" value="<%= currentURL %>" />
						<portlet:param name="threadId" value="<%= String.valueOf(message.getThreadId()) %>" />
					</portlet:renderURL>

					<liferay-ui:icon image="forward" message="move-thread" url="<%= editThreadURL %>" label="<%= true %>" />
				</td>
			</c:if>
		</tr>
		</table>
	</div>

	<div class="clear"></div>
</div>

<div class="portlet-section-header title">
	<%= Html.escape(message.getSubject()) %>
</div>

<div>

	<%
	MBTreeWalker treeWalker = messageDisplay.getTreeWalker();

	List messages = new ArrayList();

	messages.addAll(treeWalker.getMessages());

	Collections.sort(messages, new MessageCreateDateComparator(true, false));
	%>

	<div class="message-scroll" id="<portlet:namespace />message_0"></div>

	<c:if test='<%= threadView.equals("combination") && (messages.size() > 1) %>'>
		<liferay-ui:toggle
			id="toggle_id_message_boards_view_message_thread"
			defaultOn="true"
		/>

		<table class="toggle_id_message_boards_view_message_thread" id="toggle_id_message_boards_view_message_thread" style="display: <liferay-ui:toggle-value id="toggle_id_message_boards_view_message_thread" />;" width="100%">

		<%
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER, treeWalker);
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_SEL_MESSAGE, message);
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_CUR_MESSAGE, treeWalker.getRoot());
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_CATEGORY, category);
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_LAST_NODE, Boolean.valueOf(false));
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_DEPTH, new Integer(0));
		%>

		<liferay-util:include page="/html/portlet/message_boards/view_thread_shortcut.jsp" />

		</table>
	</c:if>

	<c:choose>
		<c:when test='<%= threadView.equals("tree") %>'>

			<%
			request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER, treeWalker);
			request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_SEL_MESSAGE, message);
			request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_CUR_MESSAGE, treeWalker.getRoot());
			request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_CATEGORY, category);
			request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_LAST_NODE, Boolean.valueOf(false));
			request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_DEPTH, new Integer(0));
			%>

			<liferay-util:include page="/html/portlet/message_boards/view_thread_tree.jsp" />
		</c:when>
		<c:otherwise>
			<%@ include file="/html/portlet/message_boards/view_thread_flat.jspf" %>
		</c:otherwise>
	</c:choose>
</div>

</form>

<%
MBMessageFlagLocalServiceUtil.addReadFlags(themeDisplay.getUserId(), messages);

PortalUtil.setPageSubtitle(message.getSubject(), request);
%>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.message_boards.view_message.jsp");
%>