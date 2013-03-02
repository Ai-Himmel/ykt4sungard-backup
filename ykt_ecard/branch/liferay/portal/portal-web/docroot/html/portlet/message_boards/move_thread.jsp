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

long messageId = message.getMessageId();

long categoryId = BeanParamUtil.getLong(message, request, "categoryId");
long threadId = message.getThreadId();

MBMessage curParentMessage = null;
String parentAuthor = null;

String body = StringPool.BLANK;
boolean quote = false;
%>

<script type="text/javascript">
	function <portlet:namespace />moveThread() {
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

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/move_thread" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />moveThread(); return false;">
<input name="<portlet:namespace />threadId" type="hidden" value="<%= threadId %>" />
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

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="category" />
	</td>
	<td>

		<%
		MBCategory category = MBCategoryLocalServiceUtil.getCategory(categoryId);

		category = category.toEscapedModel();
		%>

		<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/view" /><portlet:param name="categoryId" value="<%= String.valueOf(categoryId) %>" /></portlet:renderURL>" id="<portlet:namespace />categoryName">
		<%= category.getName() %></a>

		<input type="button" value="<liferay-ui:message key="select" />" onClick="var categoryWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/message_boards/select_category" /><portlet:param name="categoryId" value="<%= String.valueOf(category.getParentCategoryId()) %>" /></portlet:renderURL>', 'category', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=no,status=no,toolbar=no,width=680'); void(''); categoryWindow.focus();" />
	</td>
</tr>
</table>

<br />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="add-explanation-post" />
	</td>
	<td>
		<input id="<portlet:namespace/>addExplanationPost" name="<portlet:namespace/>addExplanationPost" type="checkbox" onClick="<portlet:namespace/>toggleExplanationPost();" />
	</td>
</tr>
</table>

<br />

<table class="lfr-table" id="<portlet:namespace/>explanationPost" style="display: none;">
<tr>
	<td>
		<liferay-ui:message key="subject" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= MBMessage.class %>" field="subject" defaultValue="" />
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
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
</table>

<input type="submit" value='<%= LanguageUtil.get(pageContext, "move-thread") %>' />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>