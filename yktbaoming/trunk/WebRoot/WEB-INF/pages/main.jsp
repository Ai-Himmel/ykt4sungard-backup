<%@page pageEncoding="UTF-8"%>
<%@ include file = "tiles/include.jsp"%>
<head>
<meta HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
<META name="DownloadOptions" content="noopen">
<TITLE>考试报名系统</title>

<script language="Javascript">
function init()
{ 
var ga=null;
if(tomain.studentForm!=null)
    ga=tomain.studentForm.giveAlert.value;

if(ga!=null&&ga=='1'){
    var opentop=(screen.height-350)/2;
    var openleft=(screen.width-450)/2;
	window.open('userAccessAction.do?method=load4stuAlertbyWin','newwindow','height=350,width=450,top='+opentop+',left='+openleft+',toolbar=no,menubar=no,scrollbars=yes, resizable=no,location=no, status=no');
}
else{
    if(tomain.testPublishForm!=null)
        ga=tomain.testPublishForm.giveAlert.value;
   
    if(ga!=null&&ga=='1'){  
        var opentop=(screen.height-350)/2;
        var openleft=(screen.width-450)/2;
	    window.open('userAccessAction.do?method=load4stuAlertbyWin','newwindow','height=350,width=450,top='+opentop+',left='+openleft+',toolbar=no,menubar=no,scrollbars=yes, resizable=no,location=no, status=no');
    }
}

}
window.onbeforeunload=init;
</script>
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
		<frame id="tomain" name="main" src="about.do" frameborder="1" marginwidth="10" marginheight="0"  onload="this.focus()" >
	</frameset>
	<frame name="footer" src="footer.do" noResize scrolling=no marginwidth="0" marginheight="0">
	<noframes>
	<body>
     
	<p>This page use fram,but your brower can't suport fram!</p>

	</body>
	</noframes>
</frameset>
