<%@page pageEncoding="UTF-8"%>
<%@ include file = "tiles/include.jsp"%>
<%@page import="java.util.*" %>
<%@page import="org.king.security.domain.Menu;"%>
<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
			String stylePath = context + "/theme/style/" + style;

		%>
<html>
<head>
<META http-equiv="Content-Type" content="text/html; charset=GBK">
<!-- <link rel="StyleSheet" href="<%=context%>/theme/style/dtree.css" type="text/css" /> -->
<link rel="StyleSheet" href="<%=context%>/theme/style/epay/css.css" type="text/css" />
<link rel="StyleSheet" href="<%=context%>/theme/style/epay/sdmenu.css" type="text/css" />
<script type="text/javascript" src="<%=context%>/theme/scripts/sdmenu.js"></script>
<script type="text/javascript">
var myMenu;
window.onload = function() {
	myMenu = new SDMenu("my_menu");
	myMenu.init();
};
</script>
</head>		

<BODY>
<!-- 

<div class="dtree">
<script type="text/javascript" src="<%=context%>/theme/scripts/dtree.js"></script>
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
-->
<table height="100%">
<tr>
	<td valign="top" align="center">
<div id="left">	
 	<div class="left_top">
        <div class="leftTpad">一卡通支付平台</div>
    </div>
    <div id="my_menu" class="sdmenu">
    <%
      	List mList =  (List)request.getAttribute("menuTreeList");
      	if(mList!=null && mList.size()>0){
      		for(int i=0;i<mList.size();i++){
      		Menu tm = (Menu)mList.get(i);
      		String tpid = tm.getPid();
      		if(tpid.equals("00")){
      		String tid = tm.getId();
      %>
      <div class="collapsed">
        <span><img src="<%=context%>/theme/style/epay/images/<%=tm.getIcon() %>" /><%= tm.getName()%></span>
        <%
        	for(int j=0;j<mList.size();j++){
        		Menu tm1 = (Menu)mList.get(j);
        		if(tm1.getPid().equals(tid)){
        			
        %>
        	<a href="<%=tm1.getUrl() %>" target="main"><img src="<%=context%>/theme/style/epay/images/collapsed.gif" /><%= tm1.getName() %></a>
        <%
        		}
        		}
        %>
      </div>
      <%
      			}
      		}
      	}
      %>
      
	</div>
	<div class="leftpic"></div>
</div>
</td>
</tr>
</table>
</BODY>
</html>