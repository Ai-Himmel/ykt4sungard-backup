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
 * File Name: sampleslist.html
 * 	FCKeditor samples list.
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
		<title>FCKeditor - Sample Selection</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta name="robots" content="noindex, nofollow">
		<link href="sample.css" rel="stylesheet" type="text/css" />
		<script language="javascript">
<!--

if ( window.top == window )
	document.location = 'index.jsp' ;

function OpenSample( sample )
{
	if ( sample.length > 0 )
		window.open( sample, 'Sample' ) ;
}

//-->
		</script>
	</head>
	<body bottommargin="0" topmargin="0">
		<table height="100%" border="0" cellpadding="0" cellspacing="0">
			<tr>
				<td>
					Please select the sample you want to view:
					<br>
					<select onchange="OpenSample(this.value);">
						<option value="jsp/sample01.jsp" selected>JSP : Sample 01 : Editor with all features generated via API</option>
						<option value="jsp/sample02.jsp">JSP : Sample 02 : Editor with all features generated with JSP Taglib</option>
						<option value="jsp/sample03.jsp">JSP : Sample 03 : Multi-language support</option>
						<option value="jsp/sample04.jsp">JSP : Sample 04 : Toolbar selection</option>
						<option value="jsp/sample05.jsp">JSP : Sample 05 : Skins support</option>
						<option value="jsp/sample06.jsp">JSP : Sample 06 : Plugins support</option>
						<option value="jsp/sample07.jsp">JSP : Sample 07 : Full Page editing</option>
					</select>
				</td>
			</tr>
		</table>
	</body>
</html>
