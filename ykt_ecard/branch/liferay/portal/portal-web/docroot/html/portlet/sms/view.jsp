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

<%@ include file="/html/portlet/sms/init.jsp" %>

<%
String to = ParamUtil.getString(request, "to");
String subject = ParamUtil.getString(request, "subject");
String message = ParamUtil.getString(request, "message");
%>

<form action="<portlet:actionURL />" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.SEND %>" />

<liferay-ui:success key='<%= portletConfig.getPortletName() + ".send" %>' message="you-have-successfully-sent-a-sms-message" />

<liferay-ui:error key="to" message="please-enter-a-valid-email-address" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="to" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />to" type="text" value="<%= to %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="subject" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />subject" type="text" onChange="document.<portlet:namespace />fm.<portlet:namespace />length.value = document.<portlet:namespace />fm.<portlet:namespace />subject.value.length + document.<portlet:namespace />fm.<portlet:namespace />message.value.length;" onKeyUp="document.<portlet:namespace />fm.<portlet:namespace />length.value = document.<portlet:namespace />fm.<portlet:namespace />subject.value.length + document.<portlet:namespace />fm.<portlet:namespace />message.value.length;" value="<%= Html.escape(subject) %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="message" />
	</td>
	<td>
		<textarea class="lfr-textarea" name="<portlet:namespace />message" wrap="soft" onChange="document.<portlet:namespace />fm.<portlet:namespace />length.value = document.<portlet:namespace />fm.<portlet:namespace />subject.value.length + document.<portlet:namespace />fm.<portlet:namespace />message.value.length;" onKeyUp="document.<portlet:namespace />fm.<portlet:namespace />length.value = document.<portlet:namespace />fm.<portlet:namespace />subject.value.length + document.<portlet:namespace />fm.<portlet:namespace />message.value.length;"><%= Html.escape(message) %></textarea><br />
	</td>
</tr>
<tr>
	<td></td>
	<td>
		<input disabled maxlength="3" name="<portlet:namespace />length" size="3" type="text" value="<%= subject.length() + message.length() %>" />

		<span style="font-size: xx-small;">(500 <liferay-ui:message key="characters-maximum" />)</span>
	</td>
</tr>
</table>

<br />

<input type="submit" value="<liferay-ui:message key="send-text-message" />" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />to);
	</script>
</c:if>