<%@page pageEncoding="UTF-8"%>
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
<table width="218" height="100%" border="0" cellpadding="0" cellspacing="0">
<tr><td align="left" height="300" valign="top" class="tdborder01" nowrap> 
<div class="navbarlogo">
<a href="#"><img src="<%=stylePath%>/images/left_top.gif" border="0" alt="监控系统"></a>
</div>

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
</script>
</div>
    </td>
  </tr>
</table>
</BODY>
</html>