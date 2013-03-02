<%@ page import="com.kingstargroup.conference.common.ParamUtil" %>
<%@ include file="/html/commons/init.jsp" %>
<%@ include file="/html/commons/permission.jsp" %>
<head>
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<%
	String opercode = ParamUtil.getString(request,"opercode");
	String password = ParamUtil.getString(request,"password");
%>
<form name="EditPwdForm" action="<%=ContextUtil.getCtxPath(request)%>/usermanage/editpwd_result.do" method=post >
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp; </td>
      
    </tr>
    <tr>
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
      	<span class="mediumwhite"><strong><bean:message key="operator.editpassword"/></strong><strong></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top">&nbsp; </td>
    </tr>
    <tr> 
      <td align="center" valign="top"><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="operator.opercode"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=opercode value="<%=opercode%>" class="input_box" style="width: 200"  maxlength=50>
            	<a class="portlet-msg-error"><html:errors property="opercode" /></a>
            </td>
          </tr>
          <tr>
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="operator.newpwd"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=operpwd type="password" value="<%=password%>" class="input_box" style="width: 200"  maxlength=50>
            	<a class="portlet-msg-error"><html:errors property="operpwd" /></a>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="operator.renewpwd"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=pwdagain type="password" class="input_box" style="width: 200"  maxlength=50>
            	<a class="portlet-msg-error"><html:errors property="pwdagain" /></a>
            </td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td align="center" valign="top">&nbsp;</td>
    </tr>
    <tr> 
      <td height="50" align="right" valign="middle" class="tdborder02"> 
      	<input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.ok"/>" 
      		> &nbsp;&nbsp;&nbsp; 
      	<input name="Submit2" type="reset" class="button_nor" value="<bean:message key="button.cancle"/>"></td>
    </tr>
	</table>
</form>
</body>
