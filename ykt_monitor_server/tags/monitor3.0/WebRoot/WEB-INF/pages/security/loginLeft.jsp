<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
			String stylePath = context + "/pages/style/" + style;
	String accountId = (String)session.getAttribute("account");
	if(accountId==null){
			%>
<html:form action = "loginAction?method=login" target="_blank"  onsubmit = "return validateLoginForm(this);">
<img src="<%=stylePath%>/images/name2.gif" width="175" height="16" />
 <html:text property = "name" onkeydown="if(event.keyCode==13) {event.keyCode=9}"/>
<img src="<%=stylePath%>/images/pass2.gif" width="175" height="16" />
 <html:password property = "password" redisplay = "false" onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) loginForm.submit();}"/>
<img src="<%=stylePath%>/images/login_button2.gif" width="175" height="43" border="0" usemap="#Map2" />
<map name="Map2" id="Map2">
	<area shape="rect" coords="135,12,175,39" href="javascript:if(validateLoginForm(loginForm)) loginForm.submit();" style="cursor:hand; cursor:pointer;"/>
</map>

</html:form>        

<html:javascript formName="loginForm"
        dynamicJavascript="true"
         staticJavascript="false"/>
         <script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>         
<%}else {%>
<br>
      您已登陆<br><br>
     <a href="logoutAction.do?method=logout">退出系统</a> 
         
<%}%> 
