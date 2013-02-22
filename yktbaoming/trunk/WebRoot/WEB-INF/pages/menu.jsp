<%@page pageEncoding="GBK"%>
<%@ include file = "tiles/include.jsp"%>
<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
			String stylePath = context + "/pages/style/" + style;

		%>
<html>
<head>
<META http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="StyleSheet" href="<%=context%>/pages/styles/dtree.css" type="text/css" />
</head>		

<BODY>
<table width="190" height="100%" border="0" cellpadding="0" cellspacing="0" bgcolor="#E7F1F5">
<tr><td align="left" height="300" valign="top" class="tdborder01" nowrap> 
<div class="dtree">
<script type="text/javascript" src="<%=context%>/pages/scripts/dtree.js"></script>
<script type='text/javascript'>
	tree = new dTree('tree');
	tree.config.folderLinks=false;
	tree.config.useCookies=false;
<logic:iterate id="menu" name="menuTreeList" scope="request">
    tree.add("<bean:write name="menu" property="id"/>","<bean:write name="menu" property="pid"/>","<bean:write name="menu" property="name"/>","<bean:write name="menu" property="url"/>","<bean:write name="menu" property="title"/>","<bean:write name="menu" property="target"/>","<bean:write name="menu" property="icon"/>");
</logic:iterate>
      document.write(tree);
      
function doout(){
var ga=null;
if(window.parent.main.studentForm!=null)
    ga=window.parent.main.studentForm.giveAlert.value;

if(ga!=null&&ga=='1'){
    var opentop=(screen.height-350)/2;
    var openleft=(screen.width-450)/2;
	window.open('userAccessAction.do?method=load4stuAlertbyWin','newwindow','height=350,width=450,top='+opentop+',left='+openleft+',toolbar=no,menubar=no,scrollbars=yes, resizable=no,location=no, status=no');
}
else{
   if(window.parent.main.testPublishForm!=null)
        ga=window.parent.main.testPublishForm.giveAlert.value;
   
    if(ga!=null&&ga=='1'){
        var opentop=(screen.height-350)/2;
        var openleft=(screen.width-450)/2;
	    window.open('userAccessAction.do?method=load4stuAlertbyWin','newwindow','height=350,width=450,top='+opentop+',left='+openleft+',toolbar=no,menubar=no,scrollbars=yes, resizable=no,location=no, status=no');
    }
    else{
        window.parent.location="logoutAction.do?method=logout";
    }
}
    
}
</script>
</div>
    </td>
  </tr>
</table>
</BODY>
</html>