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

<%@ include file="/html/portlet/enterprise_admin/init.jsp" %>

<%
String baseProviderURL = ParamUtil.getString(request, "baseProviderURL");
String principal = ParamUtil.getString(request, "principal");
String credentials = ParamUtil.getString(request, "credentials");

LdapContext ctx = PortalLDAPUtil.getContext(themeDisplay.getCompanyId(), baseProviderURL, principal, credentials);
%>

<c:choose>
	<c:when test="<%= ctx != null %>">
		<liferay-ui:message key="liferay-has-successfully-connected-to-the-ldap-server" />
	</c:when>
	<c:otherwise>
		<liferay-ui:message key="liferay-has-failed-to-connect-to-the-ldap-server" />
	</c:otherwise>
</c:choose>

<%
if (ctx != null) {
	ctx.close();
}
%>