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
    <div class="info">�û���:&nbsp;<b style="color:#FFF25F"><%=userName %></b>,&nbsp;��ɫ:<%=personName %>&nbsp;|&nbsp;<a href="" class="info">�޸�����</a>&nbsp;|&nbsp;<a href="logoutAction.do?method=logout"  class="info">ע��</a></div>
  </div>
</div>
</div>
<div id="line"></div>
