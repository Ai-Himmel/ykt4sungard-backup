<%@ include file="/commons/init.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/js/util.js"></script>
</head>
<table width="100%" height="5" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td></td>
  </tr>
</table>
<table>
<tr>
<td width=2%>&nbsp;</td>
<td>
<table width="598" height="27" border="0" cellpadding="0" cellspacing="0" background="<%=ContextUtil.getCtxPath(request)%>/commons/images/tit.jpg">
  <tr>
    <td width="14">&nbsp;</td>
    <td width="584"><bean:message key="eadvquery.title.editpassword" /></td>
  </tr>
</table>
 <html:form action="/usermanage/edit_password_result" method="POST">	
    <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
      <tr>
      	<td width="11%">&nbsp;
          </td>
        <td width="89%">
        		<a class="portlet-msg-sucess">
        <c:if test='<%= SessionErrors.contains(request, "eadvquery.editpassword.success")%>'>
							<bean:message key="eadvquery.editpassword.success" />
		</c:if></a>
				<a class="portlet-msg-error">
		<c:if test='<%= SessionErrors.contains(request, "eadvquery.editpassword.failure")%>'>
			<bean:message key="eadvquery.editpassword.failure" />
		</c:if></a>
        </td>
      </tr>
    </table>
    <table width="100%"  border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" align=right valign="baseline" class="text_or_12"><bean:message key="eadvquery.oldpassword" />&nbsp;&nbsp;</td>
        <td width="60%" valign="baseline" class="text_or_12">
        <html:password property="oldpassword" size="40" value="" /></td>
        <td width="29%" align=left><a class="portlet-msg-error"><html:errors
						property="oldpassword" /></a>
		</td>
      </tr>
    </table>
      
      <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td></td>
        </tr>
      </table>                  
      <table width="100%"  border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" align=right valign="baseline" class="text_or_12"><bean:message key="eadvquery.newpassword" />&nbsp;&nbsp;</td>
        <td width="60%" valign="baseline" class="text_or_12">
        <html:password property="newpassword" size="40" value="" /></td>
        <td width="29%" align=left><a class="portlet-msg-error"><html:errors
						property="newpassword" />
						
						</a>
		</td>
      </tr>
    </table>
	<table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td></td>
        </tr>
      </table>                  
    
    <table width="100%"  border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" align=right valign="baseline" class="text_or_12"><bean:message key="eadvquery.confirmpassword" />&nbsp;&nbsp;</td>
        <td width="60%" valign="baseline" class="text_or_12">
        <html:password property="confirmpassword" size="40" value="" /></td>
        <td width="29%" align=left>		<a class="portlet-msg-error"><html:errors
						property="confirmpassword" />
						<c:if test='<%= SessionErrors.contains(request, "eadvquery.editpassword.unpairpassword")%>'>
							<bean:message key="eadvquery.editpassword.unpairedpassword" />
						</c:if></a>
						</td>
      </tr>
    </table>
		<table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td bgcolor="#e1e1e2"></td>
        </tr>
      </table>
      <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td></td>
        </tr>
      </table>
      <table width="99%" height="35"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td align="center">
          	<button onclick="javascript:document.EditPwdForm.submit()"><bean:message key="eadvquery.save" /></button>
          	&nbsp;
          	<button onclick="javascript:document.EditPwdForm.reset()"><bean:message key="eadvquery.reset" /></button>
			</td>
        </tr>
      </table>
      </html:form>
      </td>
  </tr>
</table>