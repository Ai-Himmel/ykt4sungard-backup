  <%@page 
	language="java"
	contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"
	import="com.wiscom.is.*, java.net.*"
%>
<%@page import="org.king.web.util.KSConfiguration"%>
 <%
    String logoutgotoUrl = KSConfiguration.getInstance().getProperty("logoutgotoUrl");
    String is_config = request.getRealPath("/client.properties");
  
	IdentityFactory factory = IdentityFactory.createFactory( is_config );
	IdentityManager im = factory.getIdentityManager();	
	
    //通过认证接口获取HTTP登出URL	
	String logoutUrl = im.getLogoutURL();
	//构建最终的登出URL：logoutURL			
	String logoutURL = logoutUrl +"?goto=" + logoutgotoUrl;
	response.sendRedirect(logoutURL);
%>