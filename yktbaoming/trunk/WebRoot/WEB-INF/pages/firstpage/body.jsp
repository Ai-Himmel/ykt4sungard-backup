<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%
	String style = (session!=null && session.getAttribute("STYLE")!=null)?(String)session.getAttribute("STYLE"):"default";
	String serverPath = request.getScheme()+ "://" + request.getServerName() + ":" + request.getServerPort();
	String context = request.getScheme()+ "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
	String stylePath = context + "/pages/style/"+style;
%>

<!--mid_in-->
  <div id="mid">
  <div id="left">
  
  </div>
  
  <div id="right">
   <div id="right_1">

   </div>
   <div id="right_2">
    <div id="right_2_top"></div>
	<div id="right_2_main">
      <!-- 登录模块开始 -->
      <div id="login">
	      <jsp:include page="/login.do" />
      </div>
      <!-- 登录模块结束 -->
    
	</div> 
	<div id="right_2_bottom"></div>
   </div>
   <div id="right_bottom"></div>
   </div>
  </div>
<!--mid_out-->
 
    <div id="other">
 
    </div>
