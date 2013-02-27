<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
			String stylePath = context + "/pages/style/" + style;

			response.setHeader("Pragma", "no-cache"); //http 1.0
			response.setHeader("Cache-Control", "no-cache"); //http 1.1
			response.setDateHeader("Expires", 0); //prevents caching at the proxy server

			%>
<bean:define id="loginTitle">
	<bean:message bundle="security" key="login.title" />
</bean:define>
<center>
 <link rel="stylesheet" type="text/css" href="<%=stylePath%>/login.css"/>

	<div id="main">
	  <div id="login_box">
	    <ul>
	   	<html:form action="loginAction?method=login" target="_top"focus="name" onsubmit="return validateLoginForm(this);">
	      <li>用户名：<html:text property="name" size="20" maxlength="18"
							style="width:120;background: url(none); FONT-SIZE: 12px;  border: 1 solid #000000"
							onkeydown="if(event.keyCode==13) {event.keyCode=9}" /></li>
		  <li>密　码：<html:password property="password" maxlength="255"
							redisplay="false"
							style="width:120;background: url(none); FONT-SIZE: 12px;  border: 1 solid #000000"
							onkeydown="if(event.keyCode==13) {event.keyCode=9}" /></li>

	      <li>验证码：<input name="chkCode"
										style="width: 80; background: url(none); FONT-SIZE: 12px; border: 1 solid #000000"
										maxlength=50
										onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) {loginForm.submit();}}"><html:img page="/CheckCodeImage" align="absmiddle" style="border: 1 dotted black"
										width="52" height="20" /></li>
			<li style="padding-left: 48px;">
		    <input type="submit" class="btn" value=" 登录 " name="dosubmit"> 
		    <input type="reset" class="btn" value=" 清除 " name="reset">
	      </li>
	      <li style="text-align: center">
	      	<html:errors />
	      </li>
	    </html:form>
	    </ul>
	  </div>
	</div>

</center>
<html:javascript formName="loginForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>
