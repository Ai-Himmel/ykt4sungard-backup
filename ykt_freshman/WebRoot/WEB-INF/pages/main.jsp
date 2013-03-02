<%@page pageEncoding="UTF-8"%>
<%@ include file = "tiles/include.jsp"%>
<head>
<meta HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
<META name="DownloadOptions" content="noopen">
<TITLE>复旦大学迎新系统</title>
</head>
<!--  
<FRAMESET border=0 frameBorder=NO frameSpacing=0 rows=109>
<FRAMESET border=0 cols=166,* frameBorder=0 frameSpacing=0 name=content>
<FRAME marginHeight=0 marginWidth=0 name=BoardMenu noResize scrolling=no src="./left.do">
<FRAME marginHeight=0 marginWidth=0 name=BoardMain noResize src="./right.do">
</FRAMESET>
-->
<frameset framespacing="0" border="0" frameborder="0" rows="86,*,25">
	<frame name="banner" scrolling="no" noresize target="menu" src="./header.do" marginwidth="0" marginheight="0">
	<frameset name="content" cols="190,*">
		<frame name="menu" target="main" src="getMenu.do?method=getUserMenu" marginwidth="0" marginheight="0" scrolling="auto">
		<frame name="main" src="about.do" frameborder="1" marginwidth="10" marginheight="0"  onload="this.focus()">
	</frameset>
	<frame name="footer" src="footer.do" noResize scrolling=no marginwidth="0" marginheight="0">
	<noframes>
	<body>

	<p>This page use fram,but your brower can't suport fram!</p>

	</body>
	</noframes>
</frameset>