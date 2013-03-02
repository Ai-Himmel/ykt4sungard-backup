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
String tabs1 = ParamUtil.getString(request, "tabs1", "already-registered");

String tabs1Names = "already-registered";

if (company.isSendPassword()) {
	tabs1Names += ",forgot-password";
}

if (company.isStrangers()) {
	tabs1Names += ",create-account";
}

if (tabs1Names.equals("already-registered")) {
	tabs1Names = StringPool.BLANK;
}

String redirect = ParamUtil.getString(request, "redirect");

PortletURL createAccountURL = themeDisplay.getURLCreateAccount();
%>

<c:if test="<%= SessionErrors.contains(request, PrincipalException.class.getName()) %>">
	<span class="portlet-msg-error">
	<liferay-ui:message key="you-have-attempted-to-access-a-section-of-the-site-that-requires-authentication" />
	<liferay-ui:message key="please-sign-in-to-continue" />
	</span>
</c:if>

<c:choose>
	<c:when test="<%= company.isSendPassword() %>">
		<liferay-ui:tabs
			names="<%= tabs1Names %>"
			url2="<%= createAccountURL.toString() %>"
			refresh="<%= false %>"
		>
			<liferay-ui:section>
				<%@ include file="/html/portal/login_create_account.jspf" %>
			</liferay-ui:section>
			<liferay-ui:section>
				<%@ include file="/html/portal/login_forgot_password.jspf" %>
			</liferay-ui:section>
		</liferay-ui:tabs>
	</c:when>
	<c:otherwise>
		<liferay-ui:tabs
			names="<%= tabs1Names %>"
			url1="<%= createAccountURL.toString() %>"
			refresh="<%= false %>"
		>
			<liferay-ui:section>
				<%@ include file="/html/portal/login_create_account.jspf" %>
			</liferay-ui:section>
			<liferay-ui:section>
				<%@ include file="/html/portal/login_forgot_password.jspf" %>
			</liferay-ui:section>
		</liferay-ui:tabs>
	</c:otherwise>
</c:choose>

<script type="text/javascript">
	<c:choose>
		<c:when test='<%= tabs1.equals("already-registered") %>'>
			Liferay.Util.focusFormField(document.fm1.login);
		</c:when>
		<c:when test='<%= tabs1.equals("forgot-password") %>'>
			Liferay.Util.focusFormField(document.fm3.emailAddress);
		</c:when>
	</c:choose>
</script>