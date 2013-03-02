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

<%@ include file="/html/common/init.jsp" %>

<%
String jSecurityCheck = "j_security_check";
if (!ServerDetector.isWebSphere()) {
	jSecurityCheck = themeDisplay.getPathMain() + "/portal/" + jSecurityCheck;
}

String jUserName = (String)session.getAttribute("j_username");
String jPassword = (String)session.getAttribute("j_password");
%>

<c:choose>
	<c:when test="<%= Validator.isNotNull(jUserName) && Validator.isNotNull(jPassword) %>">
		<html>

		<head>
			<meta content="<%= Constants.TEXT_HTML %>; charset=<%= LanguageUtil.getCharset(locale) %>" http-equiv="content-type">
			<meta content="no-cache" http-equiv="Cache-Control">
			<meta content="no-cache" http-equiv="Pragma">
			<meta content="0" http-equiv="Expires">
			<script language="JavaScript" src="<%= themeDisplay.getPathJavaScript() %>/xp_progress.js"></script>
		</head>

		<body onLoad="setTimeout('document.fm.submit()', 100);">

		<center>

		<table border="0" cellpadding="0" cellspacing="0" height="100%" width="600">
		<tr>
			<td align="center" valign="middle">
				<form action="<%= jSecurityCheck %>" method="post" name="fm">
				<input name="j_username" type="hidden" value="<%= jUserName %>">
				<input name="j_password" type="hidden" value="<%= jPassword %>">
				</form>

				<font face="Verdana, Tahoma, Arial" size="3">
				<b><%= LanguageUtil.get(pageContext, "processing-login") %>
				</font><br><br>

				<script language="JavaScript">
				var progressBar = createBar(300, 15, "#FFFFFF", 1, "#000000", "<%= colorScheme.getPortletTitleBg() %>", 85, 7, 3, "");
				</script>
			</td>
		</tr>
		</table>

		</center>

		</body>

		</html>

		<%
		session.removeAttribute("j_username");
		session.removeAttribute("j_password");

		SessionMessages.clear(request);
		SessionErrors.clear(request);
		%>

	</c:when>
	<c:otherwise>

		<!--
		This only happens if you're logged in and the server is rebooted and
		the user's old session is not recovered. Forward the user to the default
		page instead of posting to the protected page with invalid credentials.
		-->

		<%
		try {
			session.invalidate();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		%>

		<html>

		<head>
			<title></title>
			<meta content="0; url=<%= themeDisplay.getPathMain() %>" http-equiv="refresh">
			<meta content="no-cache" http-equiv="Cache-Control">
			<meta content="no-cache" http-equiv="Pragma">
			<meta content="0" http-equiv="Expires">
		</head>

		<body onLoad="javascript:location.replace('<%= themeDisplay.getPathMain() %>')">

		</body>

		</html>
	</c:otherwise>
</c:choose>