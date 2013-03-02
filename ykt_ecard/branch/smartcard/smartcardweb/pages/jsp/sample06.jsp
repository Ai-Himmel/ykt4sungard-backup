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
 * File Name: sample06.jsp
 * 	FCKeditor sample file 6.
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
		<title>FCKeditor - Sample</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta name="robots" content="noindex, nofollow">
		<link href="../sample.css" rel="stylesheet" type="text/css" />
		<script type="text/javascript" src="../../fckeditor.js"></script>
	</head>
	<body>
		<h1>FCKeditor - JSP - Sample 6</h1>
		This sample shows a sample plugin implementation.
		<br>
		These are sample "Find" and "Replace" plugin that do exactly the same thing that the built in ones do. Use the green toolbar buttons the test then.
		<br>
		There is also another sample plugin that is available in the package: the "Placeholder" command (use the yellow icon).
		<hr>
		<form action="sampleposteddata.jsp" method="post" target="_blank">
			<FCK:editor id="EditorDefault" basePath="/FCKeditor/"
				toolbarSet="PluginTest"
				customConfigurationsPath="/FCKeditor/_samples/jsp/sample06.config.js"
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