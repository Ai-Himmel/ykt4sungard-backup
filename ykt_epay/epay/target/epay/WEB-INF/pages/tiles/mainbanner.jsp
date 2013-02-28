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

            String userName = (String) session.getAttribute("userName");
            if (userName == null) {
				userName = "";
			}
			String personName = (String) session.getAttribute("personName");
			if (personName == null) {
				personName = "";
			}
%>

<div class="right_titlebg">
<div class="title flt">
	欢迎您登录!
</div>
	<div class="frt">
		<%if(session.getAttribute("lastlogintime")!=null) {%>
		<div id="time">
			<img src="<%=context%>/theme/style/epay/images/clockico.gif" />您上次登录时间 <%=session.getAttribute("lastlogintime") %>
		</div>
		<%} %>
	</div>
</div>
</div>