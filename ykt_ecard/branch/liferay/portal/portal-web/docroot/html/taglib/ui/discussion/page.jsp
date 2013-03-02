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

<%@ include file="/html/taglib/init.jsp" %>

<%@ page import="com.liferay.portlet.messageboards.model.MBCategory" %>
<%@ page import="com.liferay.portlet.messageboards.model.MBDiscussion" %>
<%@ page import="com.liferay.portlet.messageboards.model.MBMessage" %>
<%@ page import="com.liferay.portlet.messageboards.model.MBMessageDisplay" %>
<%@ page import="com.liferay.portlet.messageboards.model.MBThread" %>
<%@ page import="com.liferay.portlet.messageboards.model.MBTreeWalker" %>
<%@ page import="com.liferay.portlet.messageboards.service.MBMessageLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.messageboards.service.permission.MBDiscussionPermission" %>
<%@ page import="com.liferay.portlet.messageboards.util.BBCodeUtil" %>
<%@ page import="com.liferay.portlet.messageboards.util.comparator.MessageCreateDateComparator" %>

<%
String formName = namespace + request.getAttribute("liferay-ui:discussion:formName");
String formAction = (String)request.getAttribute("liferay-ui:discussion:formAction");
String className = (String)request.getAttribute("liferay-ui:discussion:className");
long classPK = GetterUtil.getLong((String)request.getAttribute("liferay-ui:discussion:classPK"));
long userId = GetterUtil.getLong((String)request.getAttribute("liferay-ui:discussion:userId"));
String redirect = (String)request.getAttribute("liferay-ui:discussion:redirect");

MBMessageDisplay messageDisplay = MBMessageLocalServiceUtil.getDiscussionMessageDisplay(userId, className, classPK);

MBCategory category = messageDisplay.getCategory();
MBThread thread = messageDisplay.getThread();
MBTreeWalker treeWalker = messageDisplay.getTreeWalker();
MBMessage rootMessage = treeWalker.getRoot();

DateFormat dateFormatDateTime = DateFormats.getDateTime(locale, timeZone);
%>

<script type="text/javascript">
	function <%= namespace %>deleteMessage(i) {
		eval("var messageId = document.<%= formName %>.<%= namespace %>messageId" + i + ".value;");

		document.<%= formName %>.<%= namespace %><%= Constants.CMD %>.value = "<%= Constants.DELETE %>";
		document.<%= formName %>.<%= namespace %>messageId.value = messageId;
		submitForm(document.<%= formName %>);
	}

	function <%= namespace %>postReply(i) {
		eval("var parentMessageId = document.<%= formName %>.<%= namespace %>parentMessageId" + i + ".value;");
		eval("var body = document.<%= formName %>.<%= namespace %>postReplyBody" + i + ".value;");

		document.<%= formName %>.<%= namespace %><%= Constants.CMD %>.value = "<%= Constants.ADD %>";
		document.<%= formName %>.<%= namespace %>parentMessageId.value = parentMessageId;
		document.<%= formName %>.<%= namespace %>body.value = body;
		submitForm(document.<%= formName %>);
	}

	function <%= namespace %>scrollIntoView(messageId) {
		document.getElementById("<%= namespace %>messageScroll" + messageId).scrollIntoView();
	}

	function <%= namespace %>showForm(rowId, textAreaId) {
		document.getElementById(rowId).style.display = "";
		document.getElementById(textAreaId).focus();
	}

	function <%= namespace %>updateMessage(i) {
		eval("var messageId = document.<%= formName %>.<%= namespace %>messageId" + i + ".value;");
		eval("var body = document.<%= formName %>.<%= namespace %>editBody" + i + ".value;");

		document.<%= formName %>.<%= namespace %><%= Constants.CMD %>.value = "<%= Constants.UPDATE %>";
		document.<%= formName %>.<%= namespace %>messageId.value = messageId;
		document.<%= formName %>.<%= namespace %>body.value = body;
		submitForm(document.<%= formName %>);
	}
</script>

<form action="<%= formAction %>" method="post" name="<%= formName %>">
<input name="<%= namespace %><%= Constants.CMD %>" type="hidden" value="" />
<input name="<%= namespace %>redirect" type="hidden" value="<%= redirect %>" />
<input name="<%= namespace %>className" type="hidden" value="<%= className %>" />
<input name="<%= namespace %>classPK" type="hidden" value="<%= classPK %>" />
<input name="<%= namespace %>messageId" type="hidden" value="" />
<input name="<%= namespace %>threadId" type="hidden" value="<%= thread.getThreadId() %>" />
<input name="<%= namespace %>parentMessageId" type="hidden" value="" />
<input name="<%= namespace %>body" type="hidden" value="" />

<table border="0" cellpadding="0" cellspacing="0" id="<%= namespace %>messageScroll0" width="100%">

<%
int i = 0;

MBMessage message = rootMessage;

String postReplyHREF = null;
String topHREF = null;
String editHREF = null;
String deleteHREF = null;
%>

<tr>
	<td id="<%= namespace %>messageScroll<%= message.getMessageId() %>">
		<input name="<%= namespace %>messageId<%= i %>" type="hidden" value="<%= message.getMessageId() %>" />
		<input name="<%= namespace %>parentMessageId<%= i %>" type="hidden" value="<%= message.getMessageId() %>" />
	</td>
</tr>
<tr>
	<td>
		<c:if test="<%= themeDisplay.isSignedIn() && MBDiscussionPermission.contains(permissionChecker, portletGroupId.longValue(), className, classPK, ActionKeys.ADD_DISCUSSION) %>">

			<%
			postReplyHREF = "javascript: " + namespace + "showForm('" + namespace + "postReplyForm" + i + "', '" + namespace + "postReplyBody" + i + "');";
			%>

			<liferay-ui:icon image="reply" message="post-reply" url="<%= postReplyHREF %>" label="<%= true %>" />
		</c:if>
	</td>
</tr>
<tr id="<%= namespace %>postReplyForm<%= i %>" style="display: none;">
	<td>
		<br />

		<div>
			<textarea id="<%= namespace %>postReplyBody<%= i %>" name="<%= namespace %>postReplyBody<%= i %>" style="height: <%= ModelHintsDefaults.TEXTAREA_DISPLAY_HEIGHT %>px; width: <%= ModelHintsDefaults.TEXTAREA_DISPLAY_WIDTH %>px;" wrap="soft" onKeyUp="document.<%= formName %>.<%= namespace %>postReplyButton<%= i %>.disabled = (this.value == '');"></textarea>
		</div>

		<br />

		<input disabled id="<%= namespace %>postReplyButton<%= i %>" type="button" value="<liferay-ui:message key="reply" />" onClick="<%= namespace %>postReply(<%= i %>);" />

		<input type="button" value="<liferay-ui:message key="cancel" />" onClick="document.getElementById('<%= namespace %>postReplyForm<%= i %>').style.display = 'none'; void('');" />
	</td>
</tr>
</table>

<%
List messages = treeWalker.getMessages();
%>

<c:if test="<%= messages.size() > 1 %>">
	<c:if test="<%= MBDiscussionPermission.contains(permissionChecker, portletGroupId.longValue(), className, classPK, ActionKeys.ADD_DISCUSSION) %>">
		<br />
	</c:if>

	<table border="0" cellpadding="4" cellspacing="0" class="taglib-discussion" width="100%">
	<tr class="portlet-section-header" style="font-size: x-small; font-weight: bold;">
		<td>
			<liferay-ui:message key="threaded-replies" />
		</td>
		<td></td>
		<td>
			<liferay-ui:message key="author" />
		</td>
		<td></td>
		<td>
			<liferay-ui:message key="date" />
		</td>
	</tr>

	<%
	int[] range = treeWalker.getChildrenRange(rootMessage);

	for (i = range[0]; i < range[1]; i++) {
		message = (MBMessage)messages.get(i);

		boolean lastChildNode = false;

		if ((i + 1) == range[1]) {
			lastChildNode = true;
		}

		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER, treeWalker);
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_SEL_MESSAGE, rootMessage);
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_CUR_MESSAGE, message);
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_CATEGORY, category);
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_LAST_NODE, Boolean.valueOf(lastChildNode));
		request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_DEPTH, new Integer(0));
	%>

		<liferay-util:include page="/html/taglib/ui/discussion/view_message_thread.jsp" />

	<%
	}
	%>

	</table>

	<br />

	<table class="lfr-table" width="100%">

	<%
	Collections.sort(messages, new MessageCreateDateComparator(true, false));

	for (i = 1; i < messages.size(); i++) {
		message = (MBMessage)messages.get(i);

		User user2 = UserLocalServiceUtil.getUserById(message.getUserId());
	%>

		<tr>
			<td colspan="2" id="<%= namespace %>messageScroll<%= message.getMessageId() %>">
				<input name="<%= namespace %>messageId<%= i %>" type="hidden" value="<%= message.getMessageId() %>" />
				<input name="<%= namespace %>parentMessageId<%= i %>" type="hidden" value="<%= message.getMessageId() %>" />
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<liferay-ui:user-display
					userId="<%= message.getUserId() %>"
					userName="<%= message.getUserName() %>"
					displayStyle="<%= 2 %>"
				/>
			</td>
			<td valign="top" width="99%">
				<div>

					<%
					String msgBody = message.getBody();

					try {
						msgBody = BBCodeUtil.getHTML(msgBody);
					}
					catch (Exception e) {
						_log.error("Could not parse message " + message.getMessageId() + " " + e.getMessage());
					}

					msgBody = StringUtil.replace(msgBody, "@theme_images_path@/emoticons", themeDisplay.getPathThemeImages() + "/emoticons");
					%>

					<%= msgBody %>
				</div>

				<br />

				<div>
					<c:choose>
						<c:when test="<%= message.getParentMessageId() == rootMessage.getMessageId() %>">
							<%= LanguageUtil.format(pageContext, "posted-on-x", dateFormatDateTime.format(message.getModifiedDate())) %>
						</c:when>
						<c:otherwise>

							<%
							MBMessage parentMessage = MBMessageLocalServiceUtil.getMessage(message.getParentMessageId());

							StringMaker sm = new StringMaker();

							sm.append("<a href=\"javascript: ");
							sm.append(renderResponse.getNamespace());
							sm.append("scrollIntoView('");
							sm.append(parentMessage.getMessageId());
							sm.append("');\">");
							sm.append(parentMessage.getUserName());
							sm.append("</a>");
							%>

							<%= LanguageUtil.format(pageContext, "posted-on-x-in-reply-to-x", new Object[] {dateFormatDateTime.format(message.getModifiedDate()), sm.toString()}) %>
						</c:otherwise>
					</c:choose>
				</div>

				<br />

				<table class="lfr-table">
				<tr>
					<c:if test="<%= themeDisplay.isSignedIn() && MBDiscussionPermission.contains(permissionChecker, portletGroupId.longValue(), className, classPK, ActionKeys.ADD_DISCUSSION) %>">
						<td>

							<%
							postReplyHREF = "javascript: " + namespace + "showForm('" + namespace + "postReplyForm" + i + "', '" + namespace + "postReplyBody" + i + "');";
							%>

							<liferay-ui:icon image="reply" message="post-reply" url="<%= postReplyHREF %>" label="<%= true %>" />
						</td>
					</c:if>

					<c:if test="<%= i > 0 %>">

						<%
						topHREF = "javascript: " + namespace + "scrollIntoView('0');";
						%>

						<td>
							<liferay-ui:icon image="top" url="<%= topHREF %>" label="<%= true %>" />
						</td>

						<c:if test="<%= MBDiscussionPermission.contains(permissionChecker, portletGroupId.longValue(), className, classPK, ActionKeys.UPDATE_DISCUSSION) %>">

							<%
							editHREF = "javascript: " + namespace + "showForm('" + namespace + "editForm" + i + "', '" + namespace + "editBody" + i + "');";
							%>

							<td>
								<liferay-ui:icon image="edit" url="<%= editHREF %>" label="<%= true %>" />
							</td>
						</c:if>

						<c:if test="<%= MBDiscussionPermission.contains(permissionChecker, portletGroupId.longValue(), className, classPK, ActionKeys.DELETE_DISCUSSION) %>">

							<%
							deleteHREF = "javascript: " + namespace + "deleteMessage(" + i + ");";
							%>

							<td>
								<liferay-ui:icon-delete url="<%= deleteHREF %>" label="<%= true %>" />
							</td>
						</c:if>
					</c:if>
				</tr>
				</table>

				<table class="lfr-table">
				<tr id="<%= namespace %>postReplyForm<%= i %>" style="display: none;">
					<td>
						<br />

						<div>
							<textarea id="<%= namespace %>postReplyBody<%= i %>" name="<%= namespace %>postReplyBody<%= i %>" style="height: <%= ModelHintsDefaults.TEXTAREA_DISPLAY_HEIGHT %>px; width: <%= ModelHintsDefaults.TEXTAREA_DISPLAY_WIDTH %>px;" wrap="soft" onKeyUp="document.<%= formName %>.<%= namespace %>postReplyButton<%= i %>.disabled = (this.value == '');"></textarea>
						</div>

						<br />

						<input disabled id="<%= namespace %>postReplyButton<%= i %>" type="button" value="<liferay-ui:message key="reply" />" onClick="<%= namespace %>postReply(<%= i %>);" />

						<input type="button" value="<liferay-ui:message key="cancel" />" onClick="document.getElementById('<%= namespace %>postReplyForm<%= i %>').style.display = 'none'; void('');" />
					</td>
				</tr>

				<c:if test="<%= MBDiscussionPermission.contains(permissionChecker, portletGroupId.longValue(), className, classPK, ActionKeys.UPDATE_DISCUSSION) %>">
					<tr id="<%= namespace %>editForm<%= i %>" style="display: none;">
						<td>
							<br />

							<div>
								<textarea id="<%= namespace %>editBody<%= i %>" name="<%= namespace %>editBody<%= i %>" style="height: <%= ModelHintsDefaults.TEXTAREA_DISPLAY_HEIGHT %>px; width: <%= ModelHintsDefaults.TEXTAREA_DISPLAY_WIDTH %>px;" wrap="soft" onKeyUp="document.<%= formName %>.<%= namespace %>updateReplyButton<%= i %>.disabled = (this.value == '');"><%= Html.escape(message.getBody()) %></textarea>
							</div>

							<br />

							<input id="<%= namespace %>updateReplyButton<%= i %>" type="button" value="<liferay-ui:message key="update" />" onClick="<%= namespace %>updateMessage(<%= i %>);" />

							<input type="button" value="<liferay-ui:message key="cancel" />" onClick="document.getElementById('<%= namespace %>editForm<%= i %>').style.display = 'none'; void('');" />
						</td>
					</tr>
				</c:if>

				</table>
			</td>
		</tr>

		<c:if test="<%= i + 1 < messages.size() %>">
			<tr>
				<td colspan="2">
					<div class="separator"><!-- --></div>
				</td>
			</tr>
		</c:if>

	<%
	}
	%>

	</table>
</c:if>

</form>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.taglib.ui.discussion.page.jsp");
%>