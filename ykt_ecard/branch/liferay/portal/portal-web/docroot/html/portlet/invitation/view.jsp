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

<%@ include file="/html/portlet/invitation/init.jsp" %>

<c:choose>
	<c:when test="<%= windowState.equals(WindowState.NORMAL) %>">
		<liferay-ui:success key="invitationSent" message="your-invitations-have-been-sent" />

		<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/invitation/view"/></portlet:renderURL>">
			<liferay-ui:message key="invite-friends" />
		</a>
	</c:when>
	<c:otherwise>
		<form action="<portlet:actionURL><portlet:param name="struts_action" value="/invitation/view" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
		<input name="redirect" type="hidden" value="<portlet:renderURL windowState="<%= WindowState.NORMAL.toString() %>" />" />

		<%= LanguageUtil.format(pageContext, "enter-up-to-x-email-addresses-of-friends-you-would-like-to-invite", String.valueOf(InvitationUtil.getEmailMessageMaxRecipients())) %>

		<br /><br />

		<%
		Set invalidEmailAddresses = (Set)SessionErrors.get(renderRequest, "emailAddresses");

		int emailMessageMaxRecipients = InvitationUtil.getEmailMessageMaxRecipients();

		for (int i = 0; i < emailMessageMaxRecipients; i++) {
			String emailAddress = ParamUtil.getString(request, "emailAddress" + i);
		%>

			<c:if test='<%= (invalidEmailAddresses != null) && invalidEmailAddresses.contains("emailAddress" + i) %>'>
				<div class="portlet-msg-error">
				<liferay-ui:message key="please-enter-a-valid-email-address" />
				</div>
			</c:if>

			<input class="lfr-input-text" name="<portlet:namespace />emailAddress<%= i %>" type="text" value="<%= emailAddress %>" />

			<br />

		<%
		}
		%>

		<br />

		<input type="button" value="<liferay-ui:message key="invite-friends" />" onClick="submitForm(document.<portlet:namespace />fm);" />

		</form>
	</c:otherwise>
</c:choose>