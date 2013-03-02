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
	<script language="JavaScript" src="../sniffer.js"></script>
	<script language="JavaScript" src="../util.js"></script>
	<script language="javascript" type="text/javascript" src="tinymce/tiny_mce.js"></script>
	<script language="JavaScript">
		tinyMCE.init({
			mode : "textareas",
			theme : "advanced",
			plugins : "table,advhr,advimage,advlink,emotions,iespell,insertdatetime,preview,zoom,flash,searchreplace,print,contextmenu",
			theme_advanced_buttons1_add : "fontselect,fontsizeselect",
			theme_advanced_buttons2_add : "separator,insertdate,inserttime,preview,zoom,separator,forecolor,backcolor",
			theme_advanced_buttons2_add_before: "cut,copy,paste,separator,search,replace,separator",
			theme_advanced_buttons3_add_before : "tablecontrols,separator",
			theme_advanced_buttons3_add : "emotions,flash,advhr,separator,print",
			extended_valid_elements : "a[name|href|target|title|onclick],img[class|src|border=0|alt|title|hspace|vspace|width|height|align|onmouseover|onmouseout|name],hr[class|width|size|noshade],font[face|size|color|style],span[class|align|style]",
			external_image_list_url : "example_data/example_image_list.js",
			theme_advanced_toolbar_align : "left",
			theme_advanced_toolbar_location : "top",
			theme_advanced_path_location : "bottom",
			file_browser_callback : "fileBrowserCallBack"
		});

		function fileBrowserCallBack(field_name, url, type) {
		}

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
	</script>
</head>

<body leftmargin="0" marginheight="0" marginwidth="0" rightmargin="0" topmargin="0" onLoad="initEditor();">

<textarea cols="100" id="textArea" name="textArea" rows="22"></textarea>

</body>

</html>

<%!
public static final String DEFAULT_INIT_METHOD = "initEditor";
%>