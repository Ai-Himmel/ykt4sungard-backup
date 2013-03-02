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

<%@ page isErrorPage="true" %>

<%
String message = exception.getMessage();

if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_MESSAGE_LOG))) {
	_log.error(message);
}

if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_MESSAGE_PRINT))) {
	System.out.println(message);
}

String stackTrace = StringUtil.stackTrace(exception);

if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_STACK_TRACE_LOG))) {
	_log.error(stackTrace);
}

if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_STACK_TRACE_PRINT))) {
	System.out.println(stackTrace);
}
%>

<center>

<br>

<table border="0" cellpadding="0" cellspacing="0" width="95%">
<tr>
	<td>
		<font color="#FF0000" face="Verdana, Tahoma, Arial" size="2">
		<%= LanguageUtil.get(pageContext, "an-unexpected-system-error-occurred") %><br>
		</font>

		<%
		if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_MESSAGE_SHOW))) {
		%>

			<br>

			<font face="Verdana, Tahoma, Arial" size="2">
			<%= message %><br>
			</font>

		<%
		}

		if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_STACK_TRACE_SHOW))) {
		%>

<pre>
<%= stackTrace %>
</pre>

		<%
		}
		%>

	</td>
</tr>
</table>

<br>

</center>

<%!
private static final Log _log = LogFactory.getLog("portal-web.docroot.html.common.error.jsp");
%>