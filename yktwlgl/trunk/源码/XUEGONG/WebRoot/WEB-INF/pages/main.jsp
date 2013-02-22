<%@ include file = "tiles/include.jsp"%>

<meta HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
<!--  
<FRAMESET border=0 frameBorder=NO frameSpacing=0 rows=109>
<FRAMESET border=0 cols=166,* frameBorder=0 frameSpacing=0 name=content>
<FRAME marginHeight=0 marginWidth=0 name=BoardMenu noResize scrolling=no src="./left.do">
<FRAME marginHeight=0 marginWidth=0 name=BoardMain noResize src="./right.do">
</FRAMESET>   
-->
<frameset framespacing="0" border="0" frameborder="0" rows="86,*,25">
	<frame name="banner" scrolling="no" noresize target="menu" src="./header.do" marginwidth="0" marginheight="0">
	<frameset name="content" cols="180,*" >
		<frame name="menu" target="main" src="getMenu.do?method=getUserMenu" marginwidth="0" marginheight="0" scrolling="auto">
		<frame name="main" src="wxg/loginAction.do?method=load4Welcome" noResize marginwidth="0" marginheight="0" scrolling="auto">
	</frameset>
	<!-- <frame name="footer" src="footer.do" noResize scrolling=no marginwidth="0" marginheight="0">-->
	<noframes>
	<body>

	<p>This page use fram,but your brower can't suport fram!</p>

	</body>
	</noframes>
</frameset>