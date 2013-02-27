<%@page pageEncoding="GBK"%>
<%@ include file="include.jsp"%>
<%@page import="java.text.SimpleDateFormat"%>

<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
			String stylePath = context + "/pages/style/" + style;

            String userName = (String) session.getAttribute("userName");
            if (userName == null) {
				userName = "";
			}
			String personName = (String) session.getAttribute("personName");
			if (personName == null) {
				personName = "";
			}
%>

<div id="top">
<div id="top_left">
  <div id="top_right">
    <div class="info">用户名:&nbsp;<b style="color:#FFF25F"><%=userName %></b>,&nbsp;角色:<%=personName %>&nbsp;|&nbsp;<a href="" class="info">修改密码</a>&nbsp;|&nbsp;<a href="logoutAction.do?method=logout"  class="info">注销</a></div>
  </div>
</div>
</div>
<div id="line"></div>
