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

<%@ include file="/html/portlet/iframe/init.jsp" %>

<%
String[] hiddenVariablesArray = StringUtil.split(hiddenVariables, StringPool.SEMICOLON);
%>

<html dir="<liferay-ui:message key="lang.dir" />">

<head>
	<meta content="no-cache" http-equiv="Cache-Control" />
	<meta content="no-cache" http-equiv="Pragma" />
	<meta content="0" http-equiv="Expires" />
</head>

<body onLoad="setTimeout('document.fm.submit()', 100);">

<form action="<%= src %>" method="<%= formMethod %>" name="fm">

<%
for (int i = 0; i < hiddenVariablesArray.length; i++) {
	String hiddenKey = StringPool.BLANK;
	String hiddenValue = StringPool.BLANK;

	int pos = hiddenVariablesArray[i].indexOf(StringPool.EQUAL);

	if (pos != -1) {
		hiddenKey = hiddenVariablesArray[i].substring(0, pos);
		hiddenValue = hiddenVariablesArray[i].substring(pos + 1, hiddenVariablesArray[i].length());
	}
%>

	<input name="<%= hiddenKey %>" type="hidden" value="<%= hiddenValue %>" />

<%
}

String userNameKey = StringPool.BLANK;
String userNameValue = StringPool.BLANK;

int pos = userName.indexOf("=");
if (pos != -1) {
	userNameKey = userName.substring(0, pos);
	userNameValue = userName.substring(pos + 1, userName.length());
}
%>

<input name="<%= userNameKey %>" type="hidden" value="<%= userNameValue %>" />

<%
String passwordKey = StringPool.BLANK;
String passwordValue = StringPool.BLANK;

pos = password.indexOf("=");
if (pos != -1) {
	passwordKey = password.substring(0, pos);
	passwordValue = password.substring(pos + 1, password.length());
}
%>

<input name="<%= passwordKey %>" type="hidden" value="<%= passwordValue %>" />

</form>

</body>

</html>