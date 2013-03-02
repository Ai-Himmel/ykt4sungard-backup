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

<%@ include file="/html/common/init.jsp" %>

<%@ page isErrorPage="true" %>

<%
String userId = request.getRemoteUser();
String currentURL = PortalUtil.getCurrentURL(request);

if (exception instanceof PrincipalException) {
	_log.warn("User ID " + userId);
	_log.warn("Current URL " + currentURL);

	_log.warn(exception, exception);
}
else {
	_log.error("User ID " + userId);
	_log.error("Current URL " + currentURL);

	_log.error(exception, exception);
}

String message = exception.getMessage();
%>

<center>

<br />

<table border="0" cellpadding="0" cellspacing="0" width="95%">
<tr>
	<td>
		<font color="#FF0000" face="Verdana, Tahoma, Arial" size="2">

		<c:choose>
			<c:when test="<%= exception instanceof PrincipalException %>">
				<liferay-ui:message key="you-do-not-have-permission-to-view-this-page" />
			</c:when>
			<c:otherwise>
				<liferay-ui:message key="an-unexpected-system-error-occurred" />
			</c:otherwise>
		</c:choose>

		<br />

		</font>

		<c:if test="<%= message != null %>">
			<br />

			<%= Html.escape(message) %>
		</c:if>

	</td>
</tr>
</table>

<br />

</center>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.common.error.jsp");
%>