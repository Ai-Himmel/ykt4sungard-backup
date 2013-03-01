<%@ include file="/commons/init.jsp" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.UserUtil" %>
<%@ page import="com.kingstargroup.advquery.hibernate.user.TLeadqueryOperator" %>
<%@ page import="org.apache.struts.validator.DynaValidatorForm" %>
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
    <td width="584"><bean:message key="eadvquery.title.edituserstage1" /></td>
  </tr>
</table>
<%String userid= request.getParameter("userid");
	TLeadqueryOperator user = UserUtil.getUser(userid); 
	Object obj = request.getAttribute("EditUserInfoForm");
	String username = user.getOperName();
	String isShopOwner = user.getIsShopOwner();
	if (obj != null) {
		isShopOwner = ParamUtil.getString(request, "isshopowner");
		username = (String) ((DynaValidatorForm) obj).get("username");
	}%>
<html:form action="/usermanage/edit_result" method="POST">	
	<input type=hidden name=cmd value="update">
	<input type=hidden name=userid value="<%= userid%>">
	<c:if test='<%= request.getParameter("userLimitString") != null%>'>
		<input type=hidden name=userLimitString value='<%= ParamUtil.getString(request, "userLimitString")%>'>
	</c:if>
	<c:if test='<%= request.getParameter("userLimitString") == null%>'>
		<input type=hidden name=userLimitString value="<%= UserUtil.getUserLimitString(userid)%>">
	</c:if>
	<c:if test='<%= request.getParameter("storeLimitString") != null%>'>
		<input type=hidden name=storeLimitString value='<%= ParamUtil.getString(request, "storeLimitString")%>'>  
	</c:if>
	<c:if test='<%= request.getParameter("storeLimitString") == null%>'>
		<input type=hidden name=storeLimitString value='<%= UserUtil.getStoreLimitString(userid)%>'>  
	</c:if>

                    
      <table width="100%"  align=center  border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" valign="baseline" class="text_or_12"><bean:message key="eadvquery.username" />*
          </td>
        <td width="60%" valign="baseline" class="text_or_12">
        <html:text property="username" maxlength="20" value="<%= username%>" /></td>
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
 
    <table width="100%"  align=center   border="0" cellspacing="0" cellpadding="0">
    	
      <tr>            
        <td width="11%" valign="baseline" class="text_or_12"><bean:message key="eadvquery.isshopowner" />&nbsp;
          </td>
        <td width="60%" valign="baseline" class="text_or_12">
        <input type=checkbox name=isshopowner 
        <c:if test='<%= !isShopOwner.equals("") && !isShopOwner.equals("0")%>'>
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
          	<td align="center">
			&nbsp;	
			<button onclick="javascript:setCmdValue('next');"><bean:message key="eadvquery.nextstep" /></button>			
          &nbsp;	
			<button onclick="javascript:setCmdValue('update');"><bean:message key="eadvquery.save" /></button>
			&nbsp;	
			<button onclick="javascript:document.EditUserInfoForm.reset();"><bean:message key="eadvquery.reset" /></button>
			&nbsp;	
			<button onclick="javascript:renderCancelPage()"><bean:message key="eadvquery.cancel" /></button>			
			</td>
			</td>
        </tr>
</table>
</td>
	</tr>
		</table>
      </html:form>
      <script>
      	function setCmdValue(cmd) {
      		if (cmd == 'next') {
      			if (document.EditUserInfoForm.isshopowner.checked) {
      				cmd = 'stage2';
      			} else {
      				cmd = 'stage3';
      			}
      		}
      		if (!document.EditUserInfoForm.isshopowner.checked) {
      			document.EditUserInfoForm.storeLimitString.value = '';
      		}
      		document.EditUserInfoForm.cmd.value = cmd;
      		document.EditUserInfoForm.submit();
      	}
      	function renderCancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/usermanage/admin.do';
      	}
      </script>