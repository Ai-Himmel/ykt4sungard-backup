<%@ include file="/html/commons/init.jsp" %>

<head>
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<%
	String userid = (String) session.getAttribute("username");	
%>

<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<html:form action="createdelegate.do">
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
			<span class="mediumwhite"><strong>
				&nbsp;&nbsp;&nbsp;
				<bean:message key="delegate.create" />
			</strong></span>
			<c:if test='<%=SessionErrors.contains(request, "delegate.failed.delegate") %>'>	
				<font class="portlet-msg-error" style="font-size: 11;">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<bean:message key="delegate.failed.delegate" />
				</font>
			</c:if>	
		</td>
    </tr>
    <tr> 
      <td align="left" valign="top">&nbsp; </td>
    </tr>
    <tr> 
      <td align="center" valign="top">
      	<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
            	<bean:message key="delegate.name" />
            </td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name="dlgtName" class="input_box" maxlength="40" value="<%=ParamUtil.getString(request,"dlgtName")%>">
            	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            	<a class="portlet-msg-error"><html:errors property="dlgtName" /></a>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
            	<bean:message key="delegate.comment" />
            </td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<textarea name="comment" cols=50 rows=5 maxlength="40"><%=ParamUtil.getString(request,"comment")%></textarea>
            	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            	<a class="portlet-msg-error"><html:errors property="comment" /></a>
            </td>
          </tr>
        </table>
      </td>
    </tr>
    <tr> 
      <td align="center" valign="top">&nbsp;</td>
    </tr>
    <tr> 
      <td height="50" align="right" valign="middle" class="tdborder02">
      	<input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.ok"/>" >
				&nbsp;&nbsp;&nbsp; 
		<input name="Submit2" type="reset" class="button_nor" value="<bean:message key="button.cancle"/>" onclick="javascript:renderCancelPage()">
      </td>
    </tr>
</table>
</html:form>
<script>
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/viewdelegate.do';
	}
</script>
</body>

