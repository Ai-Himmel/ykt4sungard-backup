<%@page pageEncoding="UTF-8"%>
<%@ include file = "./tiles/include.jsp"%>
<%   String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session.getAttribute("STYLE")	: "default";
	 String context = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
     String stylePath = context + "/theme/style/" + style;
%>
<bean:define id="title">
<bean:message key="about.title"/>
</bean:define>
<center>
<link rel="stylesheet" type="text/css" href="<%=stylePath %>/info.css"/>
<SCRIPT language=javascript>
	function my_onload(){	 
	    var msg = '<%=request.getAttribute("msg")%>';
	    if(msg!='null'){
			alert(msg);
		}
	 }
	 window.onload=my_onload;

</SCRIPT>
<table width="100%" >

<TR align="center">
<td>
  <!--IMG src="<%=stylePath%>/images/first.jpg"-->
</td>
</TR>
<TR align="center">
<td>
	<input type="button" name="aaa" value="test" onmouseover="javascript:showme(this);" onmouseout="javascript:notshowme(this);">
</td>
</TR>

<TR align="center">
<td>
</td>
</TR>

</table>

<span ></span>

</center>
