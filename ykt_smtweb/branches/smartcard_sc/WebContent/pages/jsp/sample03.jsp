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
 * File Name: sample03.jsp
 * 	FCKeditor sample file 3.
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
		<link href="../sample.css" rel="stylesheet" type="text/css">
			<script type="text/javascript" src="../../fckeditor.js"></script>
			<script type="text/javascript">

function FCKeditor_OnComplete( editorInstance )
{
	var oCombo = document.getElementById( 'cmbLanguages' ) ;
	for ( code in editorInstance.Language.AvailableLanguages )
	{
		AddComboOption( oCombo, editorInstance.Language.AvailableLanguages[code] + ' (' + code + ')', code ) ;
	}
	oCombo.value = editorInstance.Language.ActiveLanguage.Code ;
}	

function AddComboOption(combo, optionText, optionValue)
{
	var oOption = document.createElement("OPTION") ;

	combo.options.add(oOption) ;

	oOption.innerHTML = optionText ;
	oOption.value     = optionValue ;
	
	return oOption ;
}

function ChangeLanguage( languageCode )
{
	window.location.href = window.location.pathname + "?code=" + languageCode ;
}
			</script>
	</head>
<%
String autoDetectLanguageStr;
String defaultLanguageStr;

String codeStr=request.getParameter("code");
if(codeStr==null) {
	autoDetectLanguageStr="true";
	defaultLanguageStr="en";
}
else {
	autoDetectLanguageStr="false";
	defaultLanguageStr=codeStr;
}

%>	
	<body>
		<h1>FCKeditor - JSP - Sample 3</h1>
		This sample shows the editor in all it's available languages.<br>
		The Language dropdown is populated with JavaScript API.
		<hr>
		<table cellpadding="0" cellspacing="0" border="0">
			<tr>
				<td>
					Select a language:&nbsp;
				</td>
				<td>
					<select id="cmbLanguages" onchange="ChangeLanguage(this.value);">
					</select>
				</td>
			</tr>
		</table>
		<br>
		<form action="sampleposteddata.jsp" method="get" target="_blank">
			<FCK:editor id="EditorDefault" basePath="/FCKeditor/"
				autoDetectLanguage="<%=autoDetectLanguageStr%>"
				defaultLanguage="<%=defaultLanguageStr%>"
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