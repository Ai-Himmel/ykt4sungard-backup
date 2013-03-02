<%@page pageEncoding="GBK"%>
<%@ include file = "./tiles/include.jsp"%>
<%   String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session.getAttribute("STYLE")	: "default";
	 String context = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
     String stylePath = context + "/pages/style/" + style;
%>
<bean:define id="title">
<bean:message key="about.title"/>
</bean:define>
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
  <IMG src="<%=stylePath%>/images/first.jpg">
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
