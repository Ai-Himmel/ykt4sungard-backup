<%@page pageEncoding="UTF-8"%>
<%@ include file="include.jsp"%>
<%@page import="java.text.SimpleDateFormat"%>

<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
			String stylePath = context + "/theme/style/" + style;

            String acctype = (String) session.getAttribute("acctype");
            if (acctype == null) {
				acctype = "";
			}
			String personName = (String) session.getAttribute("personName");
			if (personName == null) {
				personName = "";
			}
			String accno = (String) session.getAttribute("accno");
			if (accno == null) {
				accno = "";
			}
%>

<div id="top">
<div id="top_left"></div>
 <div id="top_right">
    <div class="user">
    <p>
    		<% if (acctype.equals("1")||acctype.equals("3")) { %>用户名<%} %>
   			<% if(acctype.equals("2")) { %>商户名 <%} %>:<span class="greentext"> <%=personName %></span>;&nbsp;&nbsp;&nbsp;&nbsp;您的账号：<span class="greentext"><%=accno %></span></p>
    <p>&nbsp;&nbsp;&nbsp;&nbsp;
           <% if(!acctype.equals("3")) { %>
           <a href="accountManager.do?method=toupdateview" target="main" class="info">修改密码</a>
           &nbsp;&nbsp;|&nbsp;&nbsp;
           <%} %>
           <a href="logoutAction.do?method=logout"  class="info" target="_parent">注销</a></p></div>
 	</div>

</div>
<div id="line"></div>
