<%@page pageEncoding="GBK"%>
<%@ include file = "./tiles/include.jsp"%>
<%   String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session.getAttribute("STYLE")	: "default";
	 String context = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
     String stylePath = context + "/pages/style/" + style;
%>
<bean:define id="title">
<bean:message key="about.title"/>
</bean:define>
<html:form action = "stuBmAction.do?method=stuinfoview">
<center>
<SCRIPT language=javascript>
	function my_onload(){	 
	    var msg = '<%=request.getAttribute("msg")%>';
	    if(msg!='null'){
			alert(msg);
		}
	 }
	 window.onload=my_onload;
</SCRIPT>
<table width="100%" height="200">

<TR align="center">
<td>
<%if(session.getAttribute("isStu")!=null&&session.getAttribute("isStu").equals("1")){%>
  <IMG src="<%=stylePath%>/images/firstforstu.jpg" border="0" usemap="#Map">
  <map name="Map">
	<area shape="rect" coords="275,170,160,130" href="stuBmAction.do?method=stuinfoview" target="main" >
	<area shape="rect" coords="275,250,160,210" href="stuBmAction.do?method=search4stuBmList" target="main" >
	<area shape="rect" coords="445,330,335,295" href="stuBmAction.do?method=search4stuBmListview" target="main" >
  </map>
 <%}else{%>
  <IMG src="<%=stylePath%>/images/first.jpg" >
 <%}%>
</td>
</TR>
<TR align="center">
<td>

</td>
</TR>

<TR align="center">
<td>
</td>
</TR>

</table>
</center>
<input name="giveAlert" type="hidden" value="<%=(String)session.getAttribute("giveAlert")%>">
</html:form>