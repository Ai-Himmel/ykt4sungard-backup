<%@ page import="com.kingstargroup.conference.common.SessionErrors" %>
<%@ include file="init.jsp" %>
<head>
<title>Login</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">

<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">

</head>
<body bgcolor="#EFEAEE"  leftmargin="0"   bottommargin="0"   topmargin="0" ><br><br>
<body onload="loaderror();">
<form action="/conference/conference.do" name=LoginForm method=post>
<table width="900" height="460" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td align="center" valign="top" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/login_bgright.jpg">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td width="58%">&nbsp;</td>
          <td width="27%">&nbsp;</td>
          <td height="316">&nbsp;</td>
        </tr>
        <tr> 
          <td>&nbsp;</td>
          <td align="left" valign="top"><table width="232" border="0" cellspacing="0" cellpadding="0">
              <tr> 
                <td width="65" height="30" align="center" valign="middle" nowrap class="bottom"><bean:message key="system.username" /></td>
                <td width="167" height="30"><input 
            name=username style="width:155;background-color: #ffffff; FONT-SIZE: 12px;  border: 1 solid #000000" maxlength=50></td>
              </tr>
              <tr> 
                <td height="30" align="center" valign="middle" nowrap class="bottom"><bean:message key="system.password" /></td>
                <td height="30"><input 
            name=password type="password" style="width:155;background-color: #ffffff; FONT-SIZE: 12px;  border: 1 solid #000000" maxlength=50></td>
              </tr>
              <tr>
                <td height="30" align="center" valign="middle" nowrap class="bottom"><bean:message key="system.authcode" /></td>
                <td height="30"><input 
            name=authCode style="width:155;background-color: #ffffff; FONT-SIZE: 12px;  border: 1 solid #000000" maxlength=50></td>
              </tr>
              <tr> 
		        <td height="30" align="right" nowrap class="bottom">&nbsp;</td>
		        <td height="30"><img border="0" hspace="0" src="<%= ContextUtil.getCtxPath(request)%>/captcha/challenge" vspace="0" width=153 height=50></td>
              </tr>
            </table></td>
          <td height="66" align="left" valign="top">
<table border="0" cellspacing="0" cellpadding="0">
              <tr> 
                <td height="90" align="left" valign="middle" nowrap class="bottom"><input type=image src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_login.jpg" width="43" height="40" border="0"></td>
              </tr>
              <tr> 
                <td height="30" align="left" nowrap class="bottom">&nbsp;</td>
              </tr>
            </table>
          </td>
        </tr>
      </table></td>
  </tr>
</table>
<form action="/conference/login.do" name=LoginForm method=post>
<table width="700" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr align="center" valign="bottom">
    <td width="120" height="80" align="right" valign="middle"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_xinxiban.gif" width="48" height="59"></td>
    <td width="10" align="left" class="bottom">&nbsp;</td>
    <td width="570" align="left" valign="middle" class="bottom"><bean:message key="system.bottom.tip" /></td>
  </tr>
</table>
<p>&nbsp;</p>
</body>
<%boolean sessionError = SessionErrors.contains(request, "system.error.validate");%>
<script>
	function loaderror() {
	<c:if test="<%= sessionError%>">	
			alert('<bean:message key="system.error.validate" />');
	</c:if>
	}
</script>
