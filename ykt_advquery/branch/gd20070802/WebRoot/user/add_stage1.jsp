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
    <td width="584"><bean:message key="eadvquery.title.adduserstage1" /></td>
  </tr>
</table>
<html:form action="/usermanage/add_result" method="POST">	
	<input type=hidden name=cmd value="create">
	<input type=hidden name=userLimitString value='<%= ParamUtil.getString(request, "userLimitString")%>'>
	<input type=hidden name=storeLimitString value='<%= ParamUtil.getString(request, "storeLimitString")%>'>  
	<table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td></td>
        </tr>
        <c:if test='<%= SessionErrors.contains(request, "eadvquery.error.createuserfailure") %>'>		
		<tr>
			<td>				
					<font class="portlet-msg-error" style="font-size: 11;">
					<bean:message key="eadvquery.error.createuserfailure" />
					</font>
			</td>
		</tr>
		</c:if>
      </table>
    <table width="100%"  align=center border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" align=right valign="baseline" class="text_or_12"><bean:message key="eadvquery.userid" />*</td>
        <td width="60%" valign="baseline" class="text_or_12">
        <html:text property="userid" maxlength="10" style="width:153px" /></td>
        <td width="29%" class="portlet-msg-error" align=left><html:errors
						property="userid" />
		</td>
      </tr>
    </table>
      
      <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td></td>
        </tr>
      </table>                  
      <table width="100%"  align=center  border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" align=right valign="baseline" class="text_or_12"><bean:message key="eadvquery.username" />*</td>
        <td width="60%" valign="baseline" class="text_or_12">
        <html:text property="username" style="width:153px" maxlength="40" /></td>
        <td width="29%" align=left><a class="portlet-msg-error"><html:errors
						property="username" />
						
						</a>
		</td>
      </tr>
    </table>
	<table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td></td>
        </tr>
      </table>                  
    
    <table width="100%"  align=center  border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" align=right valign="baseline" class="text_or_12"><bean:message key="eadvquery.password" />*</td>
        <td width="60%" valign="baseline" class="text_or_12">
        <html:password property="password" style="width:153px" maxlength="30" /></td>
        <td width="29%" class="portlet-msg-error" align=left><html:errors
						property="password" />
						<c:if test='<%= SessionErrors.contains(request, "eadvquery.editpassword.unpairpassword")%>'>
							<bean:message key="eadvquery.editpassword.unpairedpassword" />
						</c:if>
						</td>
      </tr>
    </table>
    
    <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td></td>
        </tr>
      </table>                  
    
    <table width="100%"  align=center  border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" align=right valign="baseline" class="text_or_12"><bean:message key="eadvquery.confirmpassword" />*</td>
        <td width="60%" valign="baseline" class="text_or_12">
        <html:password property="confirmpassword" style="width:153px" maxlength="30" /></td>
        <td width="29%" class="portlet-msg-error" align=left><html:errors
						property="confirmpassword" />
						
						</td>
      </tr>
    </table>
    <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td></td>
        </tr>
      </table>                  
    
    <table width="100%"  align=center  border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" align=right valign="baseline" class="text_or_12"><bean:message key="eadvquery.isshopowner" />&nbsp;</td>
        <td width="60%" valign="baseline" class="text_or_12">
        <input type=checkbox name=isshopowner 
        <c:if test='<%= !ParamUtil.getString(request, "isshopowner").equals("")%>'>
        checked
        </c:if>
        ></td>
        <td width="29%" align=left>
						
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
			&nbsp;	
			<button onclick="javascript:setCmdValue('next');"><bean:message key="eadvquery.nextstep" /></button>			
          &nbsp;	
			<button onclick="javascript:setCmdValue('create');"><bean:message key="eadvquery.create" /></button>
			&nbsp;	
			<button onclick="javascript:document.UserInfoForm.reset();"><bean:message key="eadvquery.reset" /></button>
			&nbsp;	
			<button onclick="javascript:renderCancelPage()"><bean:message key="eadvquery.cancel" /></button>			
			</td>
        </tr>
      	</table></td>
  </tr>
</table>
</td>
	</tr>
		</table>
      </html:form>
      <script>
      	function setCmdValue(cmd) {
      		if (cmd == 'next') {
      			if (document.UserInfoForm.isshopowner.checked) {
      				cmd = 'stage2';
      			} else {
      				cmd = 'stage3';
      			}
      		}
      		if (!document.UserInfoForm.isshopowner.checked) {
      			document.UserInfoForm.storeLimitString.value = '';
      		}
      		document.UserInfoForm.cmd.value = cmd;
      		document.UserInfoForm.submit();
      	}
      	function renderCancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/usermanage/admin.do';
      	}
      </script>