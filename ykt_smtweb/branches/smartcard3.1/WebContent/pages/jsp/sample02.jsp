<%@ taglib uri="http://fckeditor.net/tags-fckeditor" prefix="FCK" %>
<!--
 * FCKeditor - The text editor for internet
 * Copyright (C) 2003-2005 Frederico Caldeira Knabben
 * 
 * Licensed under the terms of the GNU Lesser General Public License:
 * 		http://www.opensource.org/licenses/lgpl-license.php
 * 
 * For further information visit:
 * 		http://www.fckeditor.net/
 * 
 * File Name: sample02.jsp
 * 	FCKeditor sample file 2.
 * 
 * Version:  2.3
 * Modified: 2005-07-19 13:57:00
 * 
 * File Authors:
 * 		Simone Chiaretta (simo@users.sourceforge.net)
-->
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
	<head>
		<title>FCKeditor - JSP Sample</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta name="robots" content="noindex, nofollow">
		<link href="../sample.css" rel="stylesheet" type="text/css" />
		<script type="text/javascript">

function FCKeditor_OnComplete( editorInstance )
{
	window.status = editorInstance.Description ;
}

		</script>
	</head>
	<body>
		<h1>FCKeditor - JSP - Sample 2</h1>
		This sample displays a normal HTML form with an FCKeditor with full features enabled.<br>
		This sample uses the FCKeditor Taglib: this method is preferred to <a href="sample01.jsp">the API version</a><br>
		All other sample pages will use this method.
		<hr>
		<form action="sampleposteddata.jsp" method="get" target="_blank">
			<FCK:editor id="EditorDefault" basePath="/FCKeditor/"
				imageBrowserURL="/FCKeditor/editor/filemanager/browser/default/browser.html?Type=Image&Connector=connectors/jsp/connector"
				linkBrowserURL="/FCKeditor/editor/filemanager/browser/default/browser.html?Connector=connectors/jsp/connector"
				flashBrowserURL="/FCKeditor/editor/filemanager/browser/default/browser.html?Type=Flash&Connector=connectors/jsp/connector"
				imageUploadURL="/FCKeditor/editor/filemanager/upload/simpleuploader?Type=Image"
				linkUploadURL="/FCKeditor/editor/filemanager/upload/simpleuploader?Type=File"
				flashUploadURL="/FCKeditor/editor/filemanager/upload/simpleuploader?Type=Flash">
				This is some <strong>sample text</strong>. You are using <a href="http://www.fredck.com/fckeditor/">FCKeditor</a>.
			</FCK:editor>
			<br>
			<input type="submit" value="Submit">
		</form>
	</body>
</html>