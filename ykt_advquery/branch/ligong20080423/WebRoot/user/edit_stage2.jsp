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
    <td width="584"><bean:message key="eadvquery.title.edituserstage2" /></td>
  </tr>
</table>
<html:form action="/usermanage/edit_result" method="POST">
	<%
		String userid = ParamUtil.getString(request, "userid");
		String storeLimitString = ParamUtil.getString(request, "storeLimitString");
	%>	
	<input type=hidden name=cmd value="update">	
	<input type=hidden name=isshopowner value='<%= ParamUtil.getString(request, "isshopowner")%>'>
	<input type=hidden name=userid value='<%= ParamUtil.getString(request, "userid")%>'>
	<input type=hidden name=username value='<%= ParamUtil.getString(request, "username")%>'>
	<c:if test='<%= request.getParameter("userLimitString") != null%>'>
		<input type=hidden name=userLimitString value='<%= ParamUtil.getString(request, "userLimitString")%>'>
	</c:if>
	<input type=hidden name=storeLimitString value='<%= storeLimitString%>'>
    <table border="0" cellspacing="0" cellpadding="0">
    	
      <tr> 
      	<td>

        <%@ include file="/user/shop_tree.jsp" %></td>
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
			<button onclick="javascript:setCmdValue('stage1');"><bean:message key="eadvquery.previousstep" /></button>			
			&nbsp;	
			<button onclick="javascript:setCmdValue('stage3');"><bean:message key="eadvquery.nextstep" /></button>
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
      		var childs = document.all;
      		var storelimit = '';
      		for (var i = 0; i < childs.length; i++) {
      			var element = childs.item(i);      			

      			if (element.type == 'checkbox' &&       				
      				element.id.indexOf('box') == 0 &&
      				element.checked) {      				
      				storelimit = storelimit + element.value + ',';
				}
      		}
      		if (storelimit.length != 0) {
      			storelimit = storelimit.substring(0, storelimit.length -1);
      		}
      		document.EditUserInfoForm.storeLimitString.value = storelimit;
      		document.EditUserInfoForm.cmd.value = cmd;
      		document.EditUserInfoForm.submit();
      	}
      	function renderCancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/usermanage/admin.do';
      	}
      	//inital tree select status
      	
      </script>
