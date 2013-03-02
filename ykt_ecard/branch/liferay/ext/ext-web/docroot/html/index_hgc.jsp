<%@page pageEncoding="UTF-8" %>
<%@ page import="com.kingstargroup.ecard.hibernate.information.EcardInformation" %>
<%@ page import="java.util.List" %>
<%@ page import="com.kingstargroup.ecard.util.DateUtil" %>
<%
	String errorMsg = request.getSession().getAttribute("LOGIN_ERROR")!=null?request.getSession().getAttribute("LOGIN_ERROR").toString():"";
	System.out.println("dd:"+request.getSession().getAttribute("LOGIN_ERROR"));
	request.getSession().removeAttribute("LOGIN_ERROR");
%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>黑龙江工程学院校园一卡通</title>
<link href="/html/extcommon/hgc/style.css" rel="stylesheet" type="text/css" />
<script>
function imgclick(){
	document.all.cauthcodeimg.src='/servlet/ImageCaptchaServlet?time='+Math.random();
}
function login(){
	document._ext_login_png_fm.submit();
}
function autoLogin()
{
 if (event.keyCode == 13)
 {
    document._ext_login_png_fm.submit();
   }
}
</script>
</head>

<body>
<form method="post" name="_ext_login_png_fm" action="/web/guest/home?p_p_id=ext_login_png&p_p_action=1&p_p_state=normal&p_p_mode=view&p_p_col_id=column-1&p_p_col_count=1&_ext_login_png_struts_action=%2Fext%2Fextloginhgcview&_ext_login_png_cmd=update&filter=true">
<div id="wrap">
  <div id="header"></div>
  <div id="container">
    <div id="left">
      <div id="member">
        <div class="loginForm">
          <label for="idInput" class="loginTh">帐　号</label>
          <input type="text" maxlength="50" name="_ext_login_png_login" id="idInput" title="请输入帐号" tabindex="1" class="loginInput" autocomplete="on">
        </div>
        <div class="loginForm">
          <label class="loginTh">密　码</label>
          <input type="password" name="_ext_login_png_password" id="pwdInput" title="请输入密码" tabindex="2" class="loginInput">
        </div>
        <div class="loginForm">
          <label class="loginTh">验证码</label>
          <input type="yzm" name="authCode" id="authCode" title="请输入验证码" tabindex="2" class="loginYzm" onkeydown="autoLogin()">
          <input name="" type="button" value="登录" class="loginBtn" onclick="login();"/>
		</div>
		<div>
		<label class="loginTh">&nbsp;&nbsp;</label>
		<img id="cauthcodeimg" border="0" hspace="0" padding="0"
									src="/servlet/ImageCaptchaServlet" vspace="0" width="128px"
									height="31px" onclick="javascript:imgclick();"> </div>
          <div>
			<label class="loginTh"></label>
			<span class="error"><%=errorMsg%></span>
		 </div>
      </div>
      
    </div>
    <div id="right">
      <div class="flt NewsBox">
        <div class="titlebg">
          <div class="title flt">新闻公告</div>
          <div class="more frt"><a href="/web/guest/home?p_p_id=ecardnews&p_p_action=0&p_p_state=maximized&p_p_mode=view&p_p_col_id=column-3&p_p_col_count=1&_ecardnews_struts_action=%2Fext%2Fecardnewsview&filter=true"><img src="/html/extcommon/hgc/images/more.gif" /></a></div>
        </div>
        <div class="content">
          <ul class="news">
			<%
				List newsList = (List)request.getAttribute("newsList");
				for(int i=0;i<newsList.size();i++){
					EcardInformation row = (EcardInformation)newsList.get(i);
			%>
					<li><a href="/web/guest/home?p_p_id=ecardnews&p_p_action=0&p_p_state=maximized&p_p_mode=view&p_p_col_id=column-3&p_p_col_count=1&_ecardnews_struts_action=%2Fext%2Fecardnewsview&id=<%=row.getId()%>"><%=row.getInfoTitle()%></a><%=DateUtil.formatDate(row.getCreateDate())%></li>
			<%
				}
			%>
          </ul>
        </div>
      </div>
      <div class="flt NewsBox">
        <div class="titlebg">
          <div class="title flt">丢失招领</div>
          <div class="more frt"><a href="/web/guest/home?p_p_id=lostfound&p_p_action=0&p_p_state=maximized&p_p_mode=view&p_p_col_id=column-4&p_p_col_count=1&_lostfound_struts_action=%2Fext%2Flostfoundview&filter=true"><img src="/html/extcommon/hgc/images/more.gif" /></a></div>
        </div>
        <div class="content">
          <ul class="news">
			<%
				List lostList = (List)request.getAttribute("lostList");
				for(int i=0;i<lostList.size();i++){
					EcardInformation row = (EcardInformation)lostList.get(i);
			%>
					<li><a href="/web/guest/home?p_p_id=lostfound&p_p_action=0&p_p_state=maximized&p_p_mode=view&p_p_col_id=column-1&p_p_col_count=5&_lostfound_struts_action=%2Fext%2Flostfoundview&id=<%=row.getId()%>"><%=row.getInfoTitle()%></a><%=DateUtil.formatDate(row.getCreateDate())%></li>
			<%
				}
			%>
          </ul>
        </div>
      </div>
    </div>
  </div>
  <div id="footer">版权所有&copy;黑龙江工程学院校园一卡通 2011</div>
</div>
</form>
</body>
</html>
