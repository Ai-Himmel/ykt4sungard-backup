<%@ include file="/commons/init.jsp" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.UserUtil" %>
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
    <td width="584"><bean:message key="eadvquery.title.edituserstage3" /></td>
  </tr>
</table>
<html:form action="/usermanage/edit_result" method="POST">
	<%
		String userid = ParamUtil.getString(request, "userid");
		String userLimitString = ParamUtil.getString(request, "userLimitString");
	%>
	<input type=hidden name=cmd value="update">
	<input type=hidden name=isshopowner value='<%= ParamUtil.getString(request, "isshopowner")%>'>
	<input type=hidden name=userid value='<%= ParamUtil.getString(request, "userid")%>'>
	<input type=hidden name=username value='<%= ParamUtil.getString(request, "username")%>'>
	<input type=hidden name=userLimitString value='<%= userLimitString%>'>
	<input type=hidden name=storeLimitString value='<%= ParamUtil.getString(request, "storeLimitString")%>'>
    <table border="0" cellspacing="0" cellpadding="0">
    	
      <tr> 
      	<td>
        <%@ include file="/user/module_tree.jsp" %></td>
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
			<button onclick="javascript:setCmdValue('previous');"><bean:message key="eadvquery.previousstep" /></button>
			&nbsp;	
			<button onclick="javascript:setCmdValue('update');"><bean:message key="eadvquery.save" /></button>
			&nbsp;	
			<button onclick="javascript:renderCancelPage()"><bean:message key="eadvquery.cancel" /></button>
			</td>
        </tr>
      </table>
            </td>
	</tr>
		</table>
      </html:form>
      <script>
      	function setCmdValue(cmd) {
      		if (cmd == 'previous') {
      			if (document.EditUserInfoForm.isshopowner.value != '') {
      				cmd = 'stage2';
      			} else {
      				cmd = 'stage1';      				
      			}
      		}      		
      		var childs = document.all;
      		var userlimit = '';
      		for (var i = 0; i < childs.length; i++) {
      			var element = childs.item(i);      			

      			if (element.type == 'checkbox' &&       				
      				element.id.indexOf('box') == 0 &&
      				element.checked) {      				
      				userlimit = userlimit + element.value + ',';
				}
      		}
      		if (userlimit.length != 0) {
      			userlimit = userlimit.substring(0, userlimit.length -1);
      		}
      		document.EditUserInfoForm.userLimitString.value = userlimit;
      		document.EditUserInfoForm.cmd.value = cmd;
      		document.EditUserInfoForm.submit();
      	}
      	
      	//inital tree select status
      	function renderCancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/usermanage/admin.do';
      	}
      </script>
