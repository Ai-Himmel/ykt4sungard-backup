<%
/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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
Boolean staleSession = (Boolean)session.getAttribute(WebKeys.STALE_SESSION);

String userLogin = user.getEmailAddress();
if (company.getAuthType().equals(Company.AUTH_TYPE_ID)) {
	userLogin = user.getUserId();
}
%>

<table border="0" cellpadding="0" cellspacing="0">
<tr>
	<td>
		<font class="gamma" size="2">

		<c:if test="<%= staleSession != null && staleSession.booleanValue() == true %>">
			<span class="gamma-neg-alert">
			<%= LanguageUtil.get(pageContext, "you-have-been-logged-off-because-you-signed-on-with-this-account-using-a-different-session") %>
			</span>

			<%
			session.invalidate();
			%>
		</c:if>

		<c:if test="<%= SessionErrors.contains(request, PortletActiveException.class.getName()) %>">
			<span class="gamma-neg-alert">
			<%= LanguageUtil.get(pageContext, "this-page-is-part-of-an-inactive-portlet") %>
			</span>
		</c:if>

		<c:if test="<%= SessionErrors.contains(request, PrincipalException.class.getName()) %>">
			<span class="gamma-neg-alert">
			<%= LanguageUtil.get(pageContext, "you-do-not-have-the-roles-required-to-access-this-page") %>
			</span>
		</c:if>

		<c:if test="<%= SessionErrors.contains(request, RequiredLayoutException.class.getName()) %>">
			<span class="gamma-neg-alert">
			<%= LanguageUtil.get(pageContext, "please-contact-the-administrator-because-you-do-not-have-any-pages-configured") %>
			</span>
		</c:if>

		<c:if test="<%= SessionErrors.contains(request, RequiredRoleException.class.getName()) %>">
			<span class="gamma-neg-alert">
			<%= LanguageUtil.get(pageContext, "please-contact-the-administrator-because-you-do-not-have-any-roles") %>
			</span>
		</c:if>

		<c:if test="<%= SessionErrors.contains(request, UserActiveException.class.getName()) %>">
			<span class="gamma-neg-alert">
			<%= LanguageUtil.format(pageContext, "your-account-with-login-x-is-not-active", new LanguageWrapper[] {new LanguageWrapper("", user.getFullName(), ""), new LanguageWrapper("<b><i>", userLogin, "</i></b>")}, false) %><br><br>
			</span>

			<%= LanguageUtil.format(pageContext, "if-you-are-not-x-logout-and-try-again", user.getFullName(), false) %><br><br>
		</c:if>

		</font>
	</td>
</tr>
</table>