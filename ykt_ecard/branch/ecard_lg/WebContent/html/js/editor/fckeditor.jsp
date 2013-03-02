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

<%@ page import="com.liferay.util.ParamUtil" %>

<%
String initMethod = ParamUtil.get(request, "init_method", DEFAULT_INIT_METHOD);
%>

<html>

<head>
	<title>Editor</title>
	<script type="text/javascript" src="fckeditor/fckeditor.js"></script>
	<script language="JavaScript">
		function getHTML() {
			var innerHTML = (document.getElementById("FCKeditor1___Frame").contentWindow.document.getElementById("eEditorArea")).contentWindow.document.body.innerHTML;			
			if (innerHTML=='<P>&nbsp;</P>') {
				innerHTML = '';
			}
			return innerHTML;
		}
		
		function resetHTML(setContent) {
			if (!setContent) {
				setContent = '';
			}
			(document.getElementById("FCKeditor1___Frame").contentWindow.document.getElementById("eEditorArea")).contentWindow.document.body.innerHTML = setContent;
		}
	</script>
</head>

<body leftmargin="0" marginheight="0" marginwidth="0" rightmargin="0" topmargin="0">

<script type="text/javascript">
	var oFCKeditor = new FCKeditor("FCKeditor1");

	oFCKeditor.BasePath = "fckeditor/";
	oFCKeditor.Value = parent.<%= initMethod %>();
	oFCKeditor.Width = "100%";
	oFCKeditor.Height = "100%";
	oFCKeditor.ToolbarSet = "Ecard";

	oFCKeditor.Create() ;
</script>

</body>

</html>

<%!
public static final String DEFAULT_INIT_METHOD = "initEditor";
%>