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

<%@ include file="/html/portlet/mail/init.jsp" %>

<%
String originalId = GetterUtil.getString((String)request.getAttribute(WebKeys.MAIL_MESSAGE_ORIGINAL_ID), "0");

String to = StringPool.BLANK;
String cc = StringPool.BLANK;
String bcc = StringPool.BLANK;

String[] recipients = (String[])request.getAttribute(WebKeys.MAIL_MESSAGE_RECIPIENTS);

if (recipients != null) {
	to = recipients[0];
	cc = recipients[1];
	bcc = recipients[2];
}

String inReplyTo = GetterUtil.getString((String)request.getAttribute(WebKeys.MAIL_MESSAGE_IN_REPLY_TO));

String references = GetterUtil.getString((String)request.getAttribute(WebKeys.MAIL_MESSAGE_REFERENCES));

String subject = GetterUtil.getString((String)request.getAttribute(WebKeys.MAIL_MESSAGE_SUBJECT));
String body = GetterUtil.getString((String)request.getAttribute(WebKeys.MAIL_MESSAGE_BODY));

List attachments = (List)request.getAttribute(WebKeys.MAIL_MESSAGE_ATTACHMENTS);
%>

<script type="text/javascript">
	var <portlet:namespace />saved = false;
	var <portlet:namespace />fileIndex = 0;

	window.onbeforeunload = function() {
		if (!<portlet:namespace />saved) {
			return "Any unsaved text will be discarded.";
		}
	}

	function <portlet:namespace />addAttachment(remoteFile, contentPath) {
		var table = document.getElementById("<portlet:namespace />files");

		var newRow = table.insertRow(table.rows.length - 1);

		newRow.id = "<portlet:namespace />file" + <portlet:namespace />fileIndex;

		if (remoteFile == null) {
			var browser = jQuery('<input name="<portlet:namespace />attachment' + <portlet:namespace />fileIndex + '"size="30" type="file"  />')[0];

			var del = document.createElement("a");

			del.href = "javascript: <portlet:namespace />removeAttachment('" + newRow.id + "');";
			del.innerHTML = "<img src='<%= themeDisplay.getPathThemeImages() %>/common/remove.png'/>";

			newRow.insertCell(0).appendChild(browser);
			newRow.insertCell(1).appendChild(del);
		}
		else {
			var checkbox = jQuery('<input checked="checked" name="<portlet:namespace />remoteAttachment' + remoteFile + '" type="checkbox" value="' + contentPath + '" />')[0];

			var filename = document.createElement("span");

			var href = "<%= themeDisplay.getPathMain() %>/mail/get_attachment?fileName=" + remoteFile + "&contentPath=" + contentPath;

			filename.innerHTML = '<span class="font-small"><a href="' + href + '">' + remoteFile + '</a></span>';

			newRow.insertCell(0);

			newRow.cells[0].appendChild(checkbox);
			newRow.cells[0].appendChild(filename);
			newRow.cells[0].colSpan = 3;
		}

		<portlet:namespace />fileIndex++;
	}

	function initEditor() {
		return "<%= UnicodeFormatter.toString(body) %>";
	}

	function <portlet:namespace />removeAttachment(id) {
		var delRow = document.getElementById(id);

		document.getElementById("<portlet:namespace />files").deleteRow(delRow.rowIndex);
	}

	function <portlet:namespace />saveMessage() {
		<portlet:namespace />saved = true;

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.SAVE %>";
		document.<portlet:namespace />fm.<portlet:namespace />body.value = window.<portlet:namespace />editor.getHTML();
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />sendMessage() {
		<portlet:namespace />saved = true;

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.SEND %>";
		document.<portlet:namespace />fm.<portlet:namespace />body.value = window.<portlet:namespace />editor.getHTML();
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/mail/edit_message" /></portlet:actionURL>" autocomplete="off" enctype="multipart/form-data" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_render" value="/mail/view" /></portlet:renderURL>" />
<input name="<portlet:namespace />originalId" type="hidden" value="<%= originalId %>" />
<input name="<portlet:namespace />inReplyTo" type="hidden" value="<%= inReplyTo %>" />
<input name="<portlet:namespace />references" type="hidden" value="<%= references %>" />
<input name="<portlet:namespace />body" type="hidden" value="" />

<liferay-ui:error exception="<%= ContentException.class %>" message="please-enter-valid-content" />
<liferay-ui:error exception="<%= RecipientException.class %>" message="please-enter-a-valid-email-address" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="to" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />to" type="text" id="<portlet:namespace />to" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="cc" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />cc" type="text" id="<portlet:namespace />cc" value="<%= cc %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="bcc" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />bcc" type="text" id="<portlet:namespace />bcc" value="<%= bcc %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="subject" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />subject" type="text" value="<%= subject %>" />
	</td>
</tr>
</table>

<br />

<table class="lfr-table">
<tr>
	<td valign="top">
		<liferay-ui:message key="attachments" />
	</td>
	<td>
		<table cellpadding="0" cellspacing="0" border="0" id="<portlet:namespace />files">
		<tr>
			<td>
				<input type="button" value="<liferay-ui:message key="add-attachment" />" onclick="<portlet:namespace />addAttachment()" />
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>

<br />

<input type="button" value="<liferay-ui:message key="send" />" onClick="<portlet:namespace />sendMessage();" />

<input type="button" value="<liferay-ui:message key="save-draft" />" onclick="<portlet:namespace />saveMessage();" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/mail/view" /></portlet:renderURL>';" />

<br /><br />

<liferay-ui:input-editor editorImpl="<%= EDITOR_WYSIWYG_IMPL_KEY %>" width="100%" />

</form>

<script type="text/javascript">
	<c:if test="<%= attachments != null %>">

		<%
		for (int i = 0; i < attachments.size(); i++) {
			RemoteMailAttachment attachment = (RemoteMailAttachment)attachments.get(i);
		%>

			<portlet:namespace />addAttachment("<%= attachment.getFilename() %>", "<%= attachment.getContentPath() %>");

		<%
		}
		%>

	</c:if>

	var toFinder = null;
	var ccFinder = null;
	var bccFinder = null;

	jQuery(
		function() {
			toFinder = new RecipientSelector("<portlet:namespace />to");
			ccFinder = new RecipientSelector("<portlet:namespace />cc");
			bccFinder = new RecipientSelector("<portlet:namespace />bcc");

			<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
				Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />to);
			</c:if>
		}
	);
</script>

<%!
public static final String EDITOR_WYSIWYG_IMPL_KEY = "editor.wysiwyg.portal-web.docroot.html.portlet.mail.edit_message.jsp";
%>