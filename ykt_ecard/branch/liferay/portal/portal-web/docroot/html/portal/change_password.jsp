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

<%@ include file="/html/portal/init.jsp" %>

<%
PasswordPolicy passwordPolicy = user.getPasswordPolicy();
%>

<form action="<%= themeDisplay.getPathMain() %>/portal/change_password" method="post" name="fm" onSubmit="submitForm(document.fm); return false;">
<input name="doAsUserId" type="hidden" value="<%= themeDisplay.getDoAsUserId() %>" />
<input name="<%= Constants.CMD %>" type="hidden" value="password" />
<input name="<%= WebKeys.REFERER %>" type="hidden" value="<%= themeDisplay.getPathMain() %>/portal/layout?doAsUserId=<%= themeDisplay.getDoAsUserId() %>" />
<input name="passwordReset" type="hidden" value="false" />

<span class="portlet-msg-error">
<liferay-ui:message key="please-change-your-password" />
</span>

<c:if test="<%= SessionErrors.contains(request, UserPasswordException.class.getName()) %>">

	<%
	UserPasswordException upe = (UserPasswordException)SessionErrors.get(request, UserPasswordException.class.getName());
	%>

	<span class="portlet-msg-error">

	<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_ALREADY_USED %>">
		<liferay-ui:message key="that-password-has-already-been-used-please-enter-in-a-different-password" />
	</c:if>

	<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_CONTAINS_TRIVIAL_WORDS %>">
		<liferay-ui:message key="that-password-uses-common-words-please-enter-in-a-password-that-is-harder-to-guess-i-e-contains-a-mix-of-numbers-and-letters" />
	</c:if>

	<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_INVALID %>">
		<liferay-ui:message key="that-password-is-invalid-please-enter-in-a-different-password" />
	</c:if>

	<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_LENGTH %>">
		<%= LanguageUtil.format(pageContext, "that-password-is-too-short-or-too-long-please-make-sure-your-password-is-between-x-and-512-characters", String.valueOf(passwordPolicy.getMinLength()), false) %>
	</c:if>

	<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_NOT_CHANGEABLE %>">
		<liferay-ui:message key="your-password-cannot-be-changed" />
	</c:if>

	<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_SAME_AS_CURRENT %>">
		<liferay-ui:message key="your-new-password-cannot-be-the-same-as-your-old-password-please-enter-in-a-different-password" />
	</c:if>

	<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_TOO_YOUNG %>">
		<%= LanguageUtil.format(pageContext, "you-cannot-change-your-password-yet-please-wait-at-least-x-before-changing-your-password-again", LanguageUtil.getTimeDescription(pageContext, passwordPolicy.getMinAge() * 1000), false) %>
	</c:if>

	<c:if test="<%= upe.getType() == UserPasswordException.PASSWORDS_DO_NOT_MATCH %>">
		<liferay-ui:message key="the-passwords-you-entered-do-not-match-each-other-please-re-enter-your-password" />
	</c:if>

	</span>
</c:if>

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="password" />
	</td>
	<td>
		<input name="password1" size="30" type="password" value="" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="enter-again" />
	</td>
	<td>
		<input name="password2" size="30" type="password" value="" />
	</td>
</tr>
</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

</form>

<script type="text/javascript">
	Liferay.Util.focusFormField(document.fm.password1);
</script>