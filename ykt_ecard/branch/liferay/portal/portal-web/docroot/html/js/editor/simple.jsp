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

<%@ page import="com.liferay.portal.kernel.util.ParamUtil" %>
<%@ page import="com.liferay.portal.kernel.util.Validator" %>

<%
String initMethod = ParamUtil.get(request, "initMethod", DEFAULT_INIT_METHOD);
String onChangeMethod = ParamUtil.getString(request, "onChangeMethod");
%>

<html>
<head>
	<title>Editor</title>
	<script type="text/javascript">
		function getHTML() {
			return document.getElementById("textArea").value;
		}

		function setHTML(value) {
			document.getElementById("textArea").value = value;
		}

		function initEditor() {
			setHTML(parent.<%= initMethod %>());
		}
	</script>
</head>

<body leftmargin="0" marginheight="0" marginwidth="0" rightmargin="0" topmargin="0" onLoad="initEditor();">

<table bgcolor="#FFFFFF" cellpadding="0" cellspacing="0" height="100%" width="100%">
<tr>
	<td bgcolor="#FFFFFF" height="100%">
		<textarea style="font-family: monospace; height: 100%; width: 100%;" id="textArea" name="textArea"

		<%
		if (Validator.isNotNull(onChangeMethod)) {
		%>

			onChange="parent.<%= onChangeMethod %>(this.value)"

		<%
		}
		%>

		></textarea>
	</td>
</tr>
</table>

</body>

</html>

<%!
public static final String DEFAULT_INIT_METHOD = "initEditor";
%>