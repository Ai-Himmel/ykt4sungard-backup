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

<html dir="<liferay-ui:message key="lang.dir" />">

<head>
	<meta content="<%= ContentTypes.TEXT_HTML_UTF8 %>" http-equiv="content-type" />
	<meta content="no-cache" http-equiv="Cache-Control" />
	<meta content="no-cache" http-equiv="Pragma" />
	<meta content="0" http-equiv="Expires" />
	<script src="<%= themeDisplay.getPathJavaScript() %>/misc/xp_progress.js" type="text/javascript"></script>
</head>

<body onLoad="self.location = '<%= themeDisplay.getPathMain() %>/portal/protected';">

<center>

<table border="0" cellpadding="0" cellspacing="0" height="100%" width="600">
<tr>
	<td align="center" valign="middle">
		<strong><liferay-ui:message key="processing-login" /></strong>

		<br /><br />

		<script type="text/javascript">
			var progressBar = createBar(300, 15, "#FFFFFF", 1, "#000000", "", 85, 7, 3, "");
		</script>
	</td>
</tr>
</table>

</center>

</body>

</html>