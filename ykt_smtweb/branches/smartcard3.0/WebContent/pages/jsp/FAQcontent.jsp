<%@ page language="java" import="com.fredck.FCKeditor.*" pageEncoding="utf-8"%>
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
 * File Name: sample01.jsp
 * 	FCKeditor sample file 1.
 * 
 * Version:  2.1
 * Modified: 2005-03-29 21:30:00
 * 
 * File Authors:
 * 		Simone Chiaretta (simo@users.sourceforge.net)
-->
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
	<head>
		<title>FAQ</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta name="robots" content="noindex, nofollow">
		<link href="../css/sample.css" rel="stylesheet" type="text/css" />
		<script type="text/javascript">

function FCKeditor_OnComplete( editorInstance )
{
	window.status = editorInstance.Description ;
}

		</script>
	</head>
	<body>
		<h1>多媒体FAQ：</h1>
		<form action="/smartcardweb/AdminFAQAction.do" method="post" target="_blank">
			<%
			FCKeditor oFCKeditor ;
			oFCKeditor = new FCKeditor( request, "FAQEditor" ) ;
			oFCKeditor.setValue( "" );
			out.println( oFCKeditor.create() ) ;
			%>
			<br>
			<input type="submit" value="Submit">
		</form>
	</body>
</html>
