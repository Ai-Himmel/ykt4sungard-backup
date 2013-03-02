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
<%@ page import="com.liferay.util.HttpUtil" %>

<%
long plid = ParamUtil.getLong(request, "p_l_id");
String mainPath = ParamUtil.getString(request, "p_main_path");
String doAsUserId = ParamUtil.getString(request, "doAsUserId");
String initMethod = ParamUtil.getString(request, "initMethod", DEFAULT_INIT_METHOD);
String onChangeMethod = ParamUtil.getString(request, "onChangeMethod");
String toolbarSet = ParamUtil.getString(request, "toolbarSet", "liferay");

// To upgrade FCKEditor, download the latest version and unzip it to fckeditor.
// Add custom configuration to fckeditor/fckconfig.jsp. Copy
// fckeditor/editor/filemanager/browser/default to
// fckeditor/editor/filemanager/browser/liferay. Modify browser.html,
// frmresourceslist.html, frmresourcetype.html, and frmupload.html.

%>

<html>

<head>
	<title>Editor</title>
	<script src="fckeditor/fckeditor.js" type="text/javascript"></script>
	<script type="text/javascript">
		function getHTML() {
			return FCKeditorAPI.GetInstance("FCKeditor1").GetXHTML();
		}

		function getText() {
			return FCKeditorAPI.GetInstance("FCKeditor1").GetXHTML();
		}

		function initFckArea() {

			// LEP-3563

			if (!document.all && window.frameElement.clientWidth == 0) {

				// This is hack since FCKEditor doesn't initialize properly in
				// Gecko if the editor is hidden.

				setTimeout('initFckArea();',250);
			}
			else {
				var textArea = document.getElementById("FCKeditor1");

				textArea.value = parent.<%= initMethod %>();

				var fckEditor = new FCKeditor("FCKeditor1");

				fckEditor.Config["CustomConfigurationsPath"] = "<%= request.getContextPath() %>/html/js/editor/fckeditor/fckconfig.jsp?p_l_id=<%= plid %>&p_main_path=<%= HttpUtil.encodeURL(mainPath) %>&doAsUserId=<%= HttpUtil.encodeURL(doAsUserId) %>";

				fckEditor.BasePath = "fckeditor/";
				fckEditor.Width = "100%";
				fckEditor.Height = "100%";
				fckEditor.ToolbarSet = '<%= toolbarSet %>';

				fckEditor.ReplaceTextarea();
			}
		}

		function onChangeCallback() {

			<%
			if (Validator.isNotNull(onChangeMethod)) {
			%>

				var dirty = FCKeditorAPI.GetInstance("FCKeditor1").IsDirty();

				if (dirty) {
					parent.<%= onChangeMethod %>(getText());

					FCKeditorAPI.GetInstance("FCKeditor1").ResetIsDirty();
				}

			<%
			}
			%>

		}

		window.onload = function() {
			initFckArea();
		}
	</script>
</head>

<body leftmargin="0" marginheight="0" marginwidth="0" rightmargin="0" topmargin="0">

<textarea id="FCKeditor1" name="FCKeditor1" style="display: none"></textarea>

</body>

</html>

<%!
public static final String DEFAULT_INIT_METHOD = "initEditor";
%>