<%@ include file="/commons/init.jsp" %>
<%%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>Login</title>
<link href="<%=ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css">
</head>
<body onload="loaderror();">
<form action="/advquery/usermanage/login.do" name=LoginForm method=post>
<table width="997" height="389" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td align="center" valign="top" background="<%=ContextUtil.getCtxPath(request)%>/commons/images/login.jpg">
<table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td width="53%">&nbsp;</td>
          <td width="23%">&nbsp;</td>
          <td width="24%" height="239">&nbsp;</td>
        </tr>
        <tr> 
          <td>&nbsp;</td>
          <td align="left" valign="top"><table width="200" border="0" cellspacing="0" cellpadding="0">
              <tr> 
                <td height="30" align="right" nowrap class="bottom"><bean:message key="eadvquery.login.username" /></td>
                <td height="30"><input type="text" style="width:153px" name="username"></td>
              </tr>
              <tr> 
                <td height="30" align="right" nowrap class="bottom"><bean:message key="eadvquery.login.password" /></td>
                <td height="30"><input type="password" style="width:153px" name="password"></td>
              </tr>
              <!-- <tr> 
                <td height="30" align="right" nowrap class="bottom"><bean:message key="eadvquery.login.authcode" /></td>
                <td height="30"><input type="text" style="width:153px" name="authCode"></td>
              </tr>
             
			  <tr>
		        <td height="30" align="right" nowrap class="bottom">&nbsp;</td>
		        <td height="30"><img border="0" hspace="0" src="<%= ContextUtil.getCtxPath(request)%>/captcha/challenge" vspace="0" width=153 height=50></td>
		      </tr> -->
		      <%String unify = request.getAttribute("unify")==null?"":request.getAttribute("unify").toString();%>
		      <%if(unify!=null && "true".equals(unify)){
		        response.sendRedirect("http://10.14.158.96/YKTRedirect/default.aspx?type=LDCX");
		      %>
		      
		      <tr> 
                <td height="30" colspan=2 align="right" nowrap ><bean:message key="eadvquery.no.user" /></td>
                <td height="30"></td>
              </tr>
		      <%}%>
            </table></td>
          <td height="66" align="left" valign="top"><input type=image src="<%=ContextUtil.getCtxPath(request)%>/commons/images/login_button.gif" width="59" height="59" border="0"></td>
        </tr>
      </table>
    </td>
  </tr>
</table>
<form action="/advquery/usermanage/login.do" name=LoginForm method=post>
<table width="997" height="100" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td width="22%" align="right" valign="top">
    </td>
    <td align="center" valign="middle"> 
      <p class="bottom">
      <a href="<bean:message key="eadvquery.bottom.link1.url" />" class="topmenu_link_14"><bean:message key="eadvquery.bottom.link1" /></a>&nbsp;&nbsp;&nbsp;&nbsp;
      <a href="<bean:message key="eadvquery.bottom.link2.url" />" class="topmenu_link_14"><bean:message key="eadvquery.bottom.link2" /></a>&nbsp;&nbsp;&nbsp;&nbsp;
      <a href="<bean:message key="eadvquery.bottom.link3.url" />" class="topmenu_link_14"><bean:message key="eadvquery.bottom.link3" /></a>&nbsp;&nbsp;&nbsp;&nbsp;
      <a href="<bean:message key="eadvquery.bottom.link4.url" />" class="topmenu_link_14"><bean:message key="eadvquery.bottom.link4" /></a>&nbsp;&nbsp;&nbsp;&nbsp;
      <a href="<bean:message key="eadvquery.bottom.link5.url" />" class="topmenu_link_14"><bean:message key="eadvquery.bottom.link5" /></a>&nbsp;&nbsp;&nbsp;&nbsp;
      <a href="<bean:message key="eadvquery.bottom.link6.url" />" class="topmenu_link_14"><bean:message key="eadvquery.bottom.link6" /></a></p>
      <p class="bottom"><bean:message key="system.copyright" /></p>
    <td width="18%">&nbsp; </td>
  </tr>
</table>
</body>
</html>
<%boolean sessionError = SessionErrors.contains(request, "eadvquery.error.validate");%>
<script>
	function loaderror() {
	<c:if test="<%= sessionError%>">	
			alert('<bean:message key="eadvquery.error.validate" />');
	</c:if>
	}
</script>
