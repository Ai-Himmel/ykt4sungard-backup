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
String redirect = ParamUtil.getString(request, "redirect");

MBMessage message = (MBMessage)request.getAttribute(WebKeys.MESSAGE_BOARDS_MESSAGE);

MBCategory category = message.getCategory();

long messageId = message.getMessageId();

long categoryId = message.getCategoryId();
long threadId = message.getThreadId();

MBMessage curParentMessage = null;
String parentAuthor = null;

String body = StringPool.BLANK;
boolean quote = false;
%>

<script type="text/javascript">
	function <portlet:namespace />splitThread() {
		document.<portlet:namespace />fm.<portlet:namespace />body.value = <portlet:namespace />getHTML();
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectCategory(categoryId, categoryName) {
		document.<portlet:namespace />fm.<portlet:namespace />categoryId.value = categoryId;

		var nameEl = document.getElementById("<portlet:namespace />categoryName");

		nameEl.href = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/view" /></portlet:renderURL>&<portlet:namespace />categoryId=" + categoryId;
		nameEl.innerHTML = categoryName + "&nbsp;";
	}

	function <portlet:namespace />toggleExplanationPost() {
		if (document.getElementById("<portlet:namespace />addExplanationPost").checked) {
			document.getElementById("<portlet:namespace />explanationPost").style.display = "";
		}
		else {
			document.getElementById("<portlet:namespace />explanationPost").style.display = "none";
		}
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/split_thread" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />splitThread(); return false;">
<input name="<portlet:namespace />messageId" type="hidden" value="<%= messageId %>" />
<input name="<portlet:namespace />categoryId" type="hidden" value="<%= categoryId %>" />

<liferay-ui:tabs
	names="message"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= MessageBodyException.class %>" message="please-enter-a-valid-message" />
<liferay-ui:error exception="<%= MessageSubjectException.class %>" message="please-enter-a-valid-subject" />
<liferay-ui:error exception="<%= NoSuchCategoryException.class %>" message="please-enter-a-valid-category" />

<%
long breadcrumbsMessageId = message.getMessageId();
%>

<div class="breadcrumbs">
	<%= MBUtil.getBreadcrumbs(categoryId, breadcrumbsMessageId, pageContext, renderRequest, renderResponse) %>
</div>

<div class="portlet-msg-info">
	<liferay-ui:message key="click-ok-to-create-a-new-thread-with-the-following-messages" />
</div>

<%
MBMessageDisplay messageDisplay = MBMessageLocalServiceUtil.getMessageDisplay(messageId);

MBTreeWalker treeWalker = messageDisplay.getTreeWalker();

List messages = new ArrayList();

messages.addAll(treeWalker.getMessages());

Collections.sort(messages, new MessageCreateDateComparator(true, false));
%>

<table class="toggle_id_message_boards_view_message_thread" id="toggle_id_message_boards_view_message_thread" style="display: <liferay-ui:toggle-value id="toggle_id_message_boards_view_message_thread" />;" width="100%">

<%
request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER, treeWalker);
request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_SEL_MESSAGE, message);
request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_CUR_MESSAGE, message);
request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_CATEGORY, category);
request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_LAST_NODE, Boolean.valueOf(false));
request.setAttribute(WebKeys.MESSAGE_BOARDS_TREE_WALKER_DEPTH, new Integer(0));
%>

<liferay-util:include page="/html/portlet/message_boards/view_thread_shortcut.jsp" />

</table>

<br />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="add-explanation-post-to-the-source-thread" />
	</td>
	<td>
		<input id="<portlet:namespace/>addExplanationPost" name="<portlet:namespace/>addExplanationPost" type="checkbox" onClick="<portlet:namespace/>toggleExplanationPost();" />
	</td>
</tr>
</table>

<br />

<table class="lfr-table" id="<portlet:namespace/>explanationPost" style="display: none;">
<tr>
	<td colspan="2">
		<liferay-ui:message key="the-following-post-will-be-added-in-place-of-the-moved-message" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="subject" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= MBMessage.class %>" field="subject" defaultValue="<%= LanguageUtil.get(pageContext, "thread-splitted") %>" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="body" />
	</td>
	<td>
		<%@ include file="/html/portlet/message_boards/bbcode_editor.jspf" %>

		<input name="<portlet:namespace />body" type="hidden" value="" />

		<script type="text/javascript">
			<portlet:namespace />setHTML('<%= LanguageUtil.format(pageContext, "the-new-thread-can-be-found-at-x", "[url=[$NEW_THREAD_URL$]][$NEW_THREAD_URL$][/url]") %>');
		</script>
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
</table>

<input type="submit" value="<liferay-ui:message key="ok" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>