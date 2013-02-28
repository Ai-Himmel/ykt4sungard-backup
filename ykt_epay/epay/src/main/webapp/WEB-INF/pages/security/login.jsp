<%@page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<bean:define id="loginTitle">
	<bean:message bundle="security" key="login.title" />
</bean:define>
<link href="<c:url value="/theme/style/epay/style.css"/>" type="text/css" rel=stylesheet>
 <body>
<div id="wrap">
  <div id="top">
    <div class="logo flt"><a href=""><img src="<c:url value="/theme/style/epay/images/logo.gif"/>" /></a></div>
    <div class="frt"><!-- <a href="">登录</a> <a href="">帮助</a> <a href=""> 安全中心</a> --></div>
  </div>
  <div id="container">
    <div class="flt loginPic"></div>
    <div class="frt lgPad">
      <div class="lgtop"></div>
      <div class="lgbg">
        <div class="content">
        	<div class="loginError">
      			<html:errors />
      		</div>
        	<html:form action="loginAction?method=login" target="_top"focus="name" onsubmit="return validateLoginForm(this);">
	          <p class="fieldBlock">
	            <label>账户类型:</label>
	            <html:select property="acctype">
	                <html:option value="1">持卡人</html:option>
					<html:option value="2">商户</html:option>
					<html:option value="3">操作员</html:option>
	            </html:select> 
	          </p>
	          <p class="fieldBlock">
	            <label>用户名:</label>
	            <html:text property="name" title="用户名"  styleClass="loginInput" onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) {loginForm.submit();}}"/>
	          </p>
	          <p class="fieldBlock">
	            <label>密码:</label>
	            <html:password property="password" title="密码"  styleClass="loginInput" onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) {loginForm.submit();}}"/>
	          </p>
	          <p class="fieldBlock">
	            <label>验证码:</label>
	            <input type="text" title="验证码" name="chkCode" class="loginYzm" onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) {loginForm.submit();}}"/>
	            <html:img page="/CheckCodeImage" align="absmiddle" style="border: 1 dotted black" width="52" height="20" /><span>
	            <!-- <button class="primary" type="button" onclick="">看不清</button> -->
	            </span> </p>
	          <p class="fieldBlock">
	            <label>&nbsp;</label>
	            <input class="loginBtn" type="submit" value="登录"/>
	            <span><a href="activate.do">激活账号</a></span>
	            <!-- <span><a href="">忘记密码？</a></span> --> </p>
	          <p class="fieldBlock">
	          <div class="underline"></div>
	          </p>
	          <p class="fieldBlock">
	            <label>&nbsp;</label>
	            <!-- <a href="">下载安全控件</a>&nbsp;&nbsp;|&nbsp;&nbsp;<a href="">控件有问题</a> --></p>
	        </html:form>
        </div>
      </div>
      <div class="lgbtm"></div>
    </div>
  </div>
  <div id="footer">版权所有&copy;sungard 金仕达 一卡通支付平台</div>
</div>
<html:javascript formName="loginForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>
</body>
</html>

