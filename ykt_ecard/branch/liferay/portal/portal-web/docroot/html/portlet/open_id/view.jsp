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

<%@ include file="/html/portlet/open_id/init.jsp" %>

<c:choose>
	<c:when test="<%= OpenIdUtil.isEnabled(company.getCompanyId()) %>">
		<c:choose>
			<c:when test="<%= themeDisplay.isSignedIn() %>">

				<%
				String signedInAs = user.getFullName();

				if (themeDisplay.isShowMyAccountIcon()) {
					signedInAs = "<a href=\"" + themeDisplay.getURLMyAccount().toString() + "\">" + signedInAs + "</a>";
				}
				%>

				<%= LanguageUtil.format(pageContext, "you-are-signed-in-as-x", signedInAs) %>
			</c:when>
			<c:otherwise>

				<%
				String openId = ParamUtil.getString(request, "openId");
				%>

				<form action="<portlet:actionURL><portlet:param name="struts_action" value="/open_id/view" /><portlet:param name="<%= Constants.CMD %>" value="<%= Constants.UPDATE %>" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">

				<liferay-ui:error exception="<%= AuthException.class %>" message="authentication-failed" />
				<liferay-ui:error exception="<%= CookieNotSupportedException.class %>" message="authentication-failed-please-enable-browser-cookies" />
				<liferay-ui:error exception="<%= NoSuchUserException.class %>" message="please-enter-a-valid-login" />
				<liferay-ui:error exception="<%= UserEmailAddressException.class %>" message="please-enter-a-valid-login" />
				<liferay-ui:error exception="<%= UserPasswordException.class %>" message="please-enter-a-valid-password" />

				<table class="lfr-table">
				<tr>
					<td width="40%" align="right">
						<liferay-ui:message key="open-id" />
					</td>
					<td align="left">
						<input class="openid_login" name="<portlet:namespace />openId" style="width: 120px;" type="text" value="<%= Html.escape(openId) %>" />
					</td>
				</tr>

				</table>

				<br />

				<input type="submit" value="<liferay-ui:message key="sign-in" />" />

				</form>

				<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
					<script type="text/javascript">
						Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />openId);
					</script>
				</c:if>
			</c:otherwise>
		</c:choose>
	</c:when>
	<c:otherwise>
		<liferay-util:include page="/html/portal/portlet_inactive.jsp" />
	</c:otherwise>
</c:choose>