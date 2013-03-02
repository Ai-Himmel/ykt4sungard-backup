<%@page pageEncoding="GBK"%>
<%@ page import="org.king.security.domain.Account" %>
<%@ include file="../tiles/include.jsp"%>
<%
	String style = (session!=null && session.getAttribute("STYLE")!=null)?(String)session.getAttribute("STYLE"):"default";
	String context = request.getScheme()+ "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
	String stylePath = context + "/pages/style/"+style;
	Account account = (Account)session.getAttribute("accountPerson");
	String name = "";
	
	
	
	if(account!=null){
	   name = account.getPerson().getPersonName();
	}
	if(account==null){
%>
<html:form action = "loginAction?method=login" target="_blank">
 <img src="<%=stylePath%>/images/name.gif" width="118" height="16">
        <html:text property = "name" onkeydown="if(event.keyCode==13) {event.keyCode=9}"/>
		<img src="<%=stylePath%>/images/pass.gif" width="118" height="16">
        <html:password property = "password" redisplay = "false" onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) {loginForm.submit();;document.location.reload();}}"/><img src="<%=stylePath%>/images/login_button.gif" border="0" usemap="#Map2" >
        <map name="Map2"><area shape="rect" coords="77,12,117,39" href="javascript:if(validateLoginForm(loginForm)) {loginForm.submit();document.location.reload();}" style="cursor:hand; cursor:pointer;"></map>
</html:form>        

<html:javascript formName="loginForm"
        dynamicJavascript="true"
         staticJavascript="false"/>
         <script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>         
<%}else {%>

      <a href="main.do" target="_blank"><%=name%> 已登陆 </a><br><br>
     <a href="logoutAction.do?method=logout">退出系统</a> 
         
<%}%>  
<br>
<br>       