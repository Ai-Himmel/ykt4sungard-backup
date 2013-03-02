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

long messageId = BeanParamUtil.getLong(message, request, "messageId");

long categoryId = BeanParamUtil.getLong(message, request, "categoryId");
long threadId = BeanParamUtil.getLong(message, request, "threadId");
long parentMessageId = BeanParamUtil.getLong(message, request, "parentMessageId", MBMessageImpl.DEFAULT_PARENT_MESSAGE_ID);

String subject = BeanParamUtil.getString(message, request, "subject");

MBMessage curParentMessage = null;
String parentAuthor = null;

if (threadId > 0) {
	try {
		curParentMessage = MBMessageLocalServiceUtil.getMessage(parentMessageId);

		if (Validator.isNull(subject)) {
			if (curParentMessage.getSubject().startsWith("RE: ")) {
				subject = curParentMessage.getSubject();
			}
			else {
				subject = "RE: " + curParentMessage.getSubject();
			}
		}

		parentAuthor = curParentMessage.isAnonymous() ? LanguageUtil.get(pageContext, "anonymous") : PortalUtil.getUserName(curParentMessage.getUserId(), curParentMessage.getUserName());
	}
	catch (Exception e) {
	}
}

String body = BeanParamUtil.getString(message, request, "body");
boolean attachments = BeanParamUtil.getBoolean(message, request, "attachments");
boolean preview = ParamUtil.getBoolean(request, "preview");
boolean quote = ParamUtil.getBoolean(request, "quote");
%>

<script type="text/javascript">
	function <portlet:namespace />saveMessage() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= message == null ? Constants.ADD : Constants.UPDATE %>";
		document.<portlet:namespace />fm.<portlet:namespace />body.value = <portlet:namespace />getHTML();
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectCategory(categoryId, categoryName) {
		document.<portlet:namespace />fm.<portlet:namespace />categoryId.value = categoryId;

		var nameEl = document.getElementById("<portlet:namespace />categoryName");

		nameEl.href = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/view" /></portlet:renderURL>&<portlet:namespace />categoryId=" + categoryId;
		nameEl.innerHTML = categoryName + "&nbsp;";
	}
</script>

<c:if test="<%= preview %>">
	<liferay-ui:message key="preview" />:

	<%
	MBMessage temp = null;

	if (message != null) {
		temp = message;

		message = new MBMessageImpl();

		message.setUserId(temp.getUserId());
		message.setUserName(temp.getUserName());
		message.setCreateDate(temp.getCreateDate());
		message.setModifiedDate(temp.getModifiedDate());
		message.setThreadId(temp.getThreadId());
		message.setSubject(subject);
		message.setBody(body);
		message.setAnonymous(temp.isAnonymous());
	}
	else {
		message = new MBMessageImpl();

		message.setUserId(user.getUserId());
		message.setUserName(user.getFullName());
		message.setCreateDate(new Date());
		message.setModifiedDate(new Date());
		message.setThreadId(threadId);
		message.setSubject(subject);
		message.setBody(body);
		message.setAnonymous(BeanParamUtil.getBoolean(message, request, "anonymous"));
	}

	boolean editable = false;

	MBCategory category = null;

	int depth = 0;

	String className = "portlet-section-body";
	String classHoverName = "portlet-section-body-hover";
	%>

	<%@ include file="/html/portlet/message_boards/view_thread_message.jspf" %>

	<%
	message = temp;
	%>

	<br />
</c:if>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/edit_message" /></portlet:actionURL>" enctype="multipart/form-data" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveMessage(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />messageId" type="hidden" value="<%= messageId %>" />
<input name="<portlet:namespace />categoryId" type="hidden" value="<%= categoryId %>" />
<input name="<portlet:namespace />threadId" type="hidden" value="<%= threadId %>" />
<input name="<portlet:namespace />parentMessageId" type="hidden" value="<%= parentMessageId %>" />
<input name="<portlet:namespace />attachments" type="hidden" value="<%= attachments %>" />
<input name="<portlet:namespace />preview" type="hidden" value="" />

<liferay-ui:tabs
	names="message"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= CaptchaTextException.class %>" message="text-verification-failed" />
<liferay-ui:error exception="<%= MessageBodyException.class %>" message="please-enter-a-valid-message" />
<liferay-ui:error exception="<%= MessageSubjectException.class %>" message="please-enter-a-valid-subject" />

<liferay-ui:error exception="<%= FileNameException.class %>">
	<liferay-ui:message key="document-names-must-end-with-one-of-the-following-extensions" /><%= StringUtil.merge(PropsValues.DL_FILE_EXTENSIONS, ", ") %>.
</liferay-ui:error>

<liferay-ui:error exception="<%= FileSizeException.class %>" message="please-enter-a-file-with-a-valid-file-size" />

<liferay-ui:tags-error />

<%
long breadcrumbsMessageId = parentMessageId;

if (threadId <= 0) {
	breadcrumbsMessageId = messageId;
}

if (message != null) {
	breadcrumbsMessageId = message.getMessageId();
}
%>

<div class="breadcrumbs">
	<%= MBUtil.getBreadcrumbs(categoryId, breadcrumbsMessageId, pageContext, renderRequest, renderResponse) %>
</div>

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="subject" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= MBMessage.class %>" field="subject" defaultValue="<%= subject %>" />
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

<c:if test="<%= attachments %>">
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>

	<%
	for (int i = 1; i <= 5; i++) {
	%>

		<tr>
			<td>
				<liferay-ui:message key="file" /> <%= i %>
			</td>
			<td>
				<input name="<portlet:namespace />msgFile<%= i %>" size="70" type="file" />
			</td>
		</tr>

	<%
	}
	%>

</c:if>

<c:if test="<%= (message == null) && themeDisplay.isSignedIn() && allowAnonymousPosting %>">
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="anonymous" />
		</td>
		<td>
			<liferay-ui:input-checkbox param="anonymous" />
		</td>
	</tr>
</c:if>

<c:if test="<%= (priorities.length > 0) && MBCategoryPermission.contains(permissionChecker, categoryId, ActionKeys.UPDATE_THREAD_PRIORITY) %>">
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="priority" />
		</td>
		<td>

			<%
			double threadPriority = 0.0;

			try {
				MBThread thread = MBThreadLocalServiceUtil.getThread(threadId);

				threadPriority = thread.getPriority();
			}
			catch (NoSuchThreadException nste) {
			}

			threadPriority = ParamUtil.getDouble(request, "priority", threadPriority);
			%>

			<select name="<portlet:namespace />priority">
				<option value=""></option>

				<%
				for (int i = 0; i < priorities.length; i++) {
					String[] priority = StringUtil.split(priorities[i]);

					try {
						String priorityName = priority[0];
						String priorityImage = priority[1];
						double priorityValue = GetterUtil.getDouble(priority[2]);

						if (priorityValue > 0) {
				%>

							<option <%= (threadPriority == priorityValue) ? "selected" : "" %> value="<%= priorityValue %>"><%= priorityName %></option>

				<%
						}
					}
					catch (Exception e) {
					}
				}
				%>

			</select>
		</td>
	</tr>
</c:if>

<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="tags" />
	</td>
	<td>

		<%
		long classPK = 0;

		if (message != null) {
			classPK = message.getMessageId();
		}
		%>

		<liferay-ui:tags-selector
			className="<%= MBMessage.class.getName() %>"
			classPK="<%= classPK %>"
			hiddenInput="tagsEntries"
		/>
	</td>
</tr>

<c:if test="<%= message == null %>">
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="permissions" />
		</td>
		<td>
			<liferay-ui:input-permissions
				modelName="<%= MBMessage.class.getName() %>"
			/>
		</td>
	</tr>
</c:if>

</table>

<br />

<c:if test="<%= message == null %>">
	<portlet:actionURL windowState="<%= LiferayWindowState.EXCLUSIVE.toString() %>" var="captchaURL">
		<portlet:param name="struts_action" value="/message_boards/captcha" />
	</portlet:actionURL>

	<liferay-ui:captcha url="<%= captchaURL %>" />
</c:if>

<input type="submit" value="<liferay-ui:message key="save" />" />

<c:if test="<%= MBCategoryPermission.contains(permissionChecker, categoryId, ActionKeys.ADD_FILE) %>">
	<input type="button" value='<%= LanguageUtil.get(pageContext, ((attachments) ? "remove" : "attach") + "-files") %>' onClick="document.<portlet:namespace />fm.<portlet:namespace />body.value = <portlet:namespace />getHTML(); document.<portlet:namespace />fm.<portlet:namespace />attachments.value = '<%= !attachments %>'; submitForm(document.<portlet:namespace />fm);" />
</c:if>

<input type="button" value="<liferay-ui:message key="preview" />" onClick="document.<portlet:namespace />fm.<portlet:namespace />body.value = <portlet:namespace />getHTML(); document.<portlet:namespace />fm.<portlet:namespace />preview.value = 'true'; submitForm(document.<portlet:namespace />fm);" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

<c:if test="<%= curParentMessage != null %>">
	<br /><br />

	<liferay-ui:message key="replying-to" />:

	<%
	boolean editable = false;

	message = curParentMessage;
	MBCategory category = null;

	int depth = 0;

	String className = "portlet-section-body";
	String classHoverName = "portlet-section-body-hover";
	%>

	<%@ include file="/html/portlet/message_boards/view_thread_message.jspf" %>
</c:if>

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />subject);
	</script>
</c:if>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.message_boards.edit_message.jsp");
%>