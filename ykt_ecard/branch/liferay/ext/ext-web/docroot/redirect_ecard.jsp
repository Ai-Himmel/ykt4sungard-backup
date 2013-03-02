<html>
<head>

</head>
 <%
  String un=""; 
  String time="";
  String verify ="";
  String port = String.valueOf(request.getServerPort());
  String serverName  =   request.getServerName(); 
  String scode="";
  String uid="";
  String key="";
  
  if(scode.equalsIgnoreCase("SHITAC")){
	un= request.getParameter("uid"); 
	time= request.getParameter("time");
	verify = request.getParameter("password");
	key="sitc";
	scode="SHITAC";
  }else{
	un= request.getParameter("un"); 
	time= request.getParameter("time");
	verify = request.getParameter("verify");
  }
 %>
 
<body onload="document._ext_login_png_fm.submit()">
  <form
   action="http://<%=serverName%>:<%=port%>/web/guest/home?p_p_id=ext_login_png&p_p_action=1&p_p_state=normal&p_p_mode=view&p_p_col_id=column-1&p_p_col_count=1&_ext_login_png_struts_action=%2Fext%2Fextloginview&_ext_login_png_cmd=sso"
  method="post" name="_ext_login_png_fm">
 <input type="hidden" name="un" value="<%=un%>"/>
 <input type="hidden" name="time" value="<%=time%>"/>
 <input type="hidden" name="verify" value="<%=verify%>"/>
 <input type="hidden" name="cmd" value="sso"/>
 <input type="hidden" name="scode" value="<%=scode%>"/>
 <input type="hidden" name="key" value="<%=key%>"/>
</form>
  
</body>
  
</html>