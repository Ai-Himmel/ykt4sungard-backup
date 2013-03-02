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
	<script src="tiny_mce/tiny_mce.js" type="text/javascript"></script>
	<script type="text/javascript">
		var onChangeCallbackCounter = 0;

		tinyMCE.init({
			mode : "textareas",
			theme : "advanced",
			extended_valid_elements : "a[name|href|target|title|onclick],img[class|src|border=0|alt|title|hspace|vspace|width|height|align|onmouseover|onmouseout|name],hr[class|width|size|noshade],font[face|size|color|style],span[class|align|style]",
			file_browser_callback : "fileBrowserCallback",
			onchange_callback : "onChangeCallback",
			plugins : "preview,print,contextmenu",
			theme_advanced_buttons1_add : "code,preview,print",
			theme_advanced_buttons2: "",
			theme_advanced_buttons3: "",
			theme_advanced_disable : "formatselect,styleselect,help,strikethrough",
			theme_advanced_toolbar_align : "left",
			theme_advanced_toolbar_location : "top",
			theme_advanced_path : false
		});

		function init(value) {
			setHTML(decodeURIComponent(value));
		}

		function getHTML() {
			return tinyMCE.getContent();
		}

		function setHTML(value) {
			tinyMCE.setContent(value);
		}

		function initEditor() {
			init(parent.<%= initMethod %>());
		}

		function fileBrowserCallback(field_name, url, type) {
		}

		function onChangeCallback(tinyMCE) {

			// This purposely ignores the first callback event because each call
			// to setContent triggers an undo level which fires the callback
			// when no changes have yet been made.

			// setContent is not really the correct way of initializing this
			// editor with content. The content should be placed statically
			// (from the editor's perspective) within the textarea. This is a
			// problem from the portal's perspective because it's passing the
			// content via a javascript method (initMethod).

			if (onChangeCallbackCounter > 0) {

				<%
				if (Validator.isNotNull(onChangeMethod)) {
				%>

					parent.<%= onChangeMethod %>(getHTML());

				<%
				}
				%>

			}

			onChangeCallbackCounter++;
		}
	</script>
</head>

<body leftmargin="0" marginheight="0" marginwidth="0" rightmargin="0" topmargin="0" onLoad="initEditor();">

<textarea id="textArea" name="textArea" style="height: 100%; width: 100%;"></textarea>

</body>

</html>

<%!
public static final String DEFAULT_INIT_METHOD = "initEditor";
%>