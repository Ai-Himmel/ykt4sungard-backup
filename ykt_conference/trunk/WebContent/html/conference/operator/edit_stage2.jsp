<%@ include file="/html/commons/init.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/js/util.js"></script>
</head>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<form action="<%=ContextUtil.getCtxPath(request)%>/usermanage/edit_result.do" name="CreateOperatorForm" method="post">
	<%
		String opercode = ParamUtil.getString(request, "opercode");
		String deptLimitString = ParamUtil.getString(request, "deptLimitString");
	%>	
	<input type=hidden name=cmd value="update">	
	<input type=hidden name=deptcode value='<%= ParamUtil.getString(request, "deptcode")%>'>
	<input type=hidden name=opercode value='<%= ParamUtil.getString(request, "opercode")%>'>
	<input type=hidden name=opername value='<%= ParamUtil.getString(request, "opername")%>'>
	<input type=hidden name=opername value='<%= ParamUtil.getString(request, "opername")%>'>
	<input type=hidden name=opername value='<%= ParamUtil.getString(request, "opername")%>'>
	<input type=hidden name=operpwd value='<%= ParamUtil.getString(request, "operpwd")%>'>	
	<input type=hidden name=pwdagain value='<%= ParamUtil.getString(request, "pwdagain")%>'>
	<c:if test='<%= request.getParameter("userLimitString") != null%>'>
		<input type=hidden name=userLimitString value='<%= ParamUtil.getString(request, "userLimitString")%>'>
	</c:if>
	<input type=hidden name=deptLimitString value='<%= deptLimitString%>'>
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
      <span class="mediumwhite"><strong><bean:message key="operator.dept"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="left" valign="top" >
      	<%@ include file="dept_tree.jsp" %>
      </td>
    </tr>
    <tr> 
      <td align="center" valign="top" class="tdborder02" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle" >
      	<input name="Submit24" type="button" class="button_nor" value="<bean:message key="button.back"/>" 
      		onclick="javascript:setCmdValue('stage1');"> &nbsp;&nbsp; 
      	<input name="Submit252" type="button" class="button_nor" value="<bean:message key="button.next"/>" 
      		onclick="javascript:setCmdValue('stage3');">&nbsp;&nbsp; 
      	<input name="Submit2522" type="button" class="button_nor" value="<bean:message key="button.cancle"/>" 
      		onclick="javascript:renderCancelPage()"></td>
    </tr>
	</table>
</form>
<script>
      	function setCmdValue(cmd) {      		
      		var childs = document.all;
      		var deptlimit = '';
      		for (var i = 0; i < childs.length; i++) {
      			var element = childs.item(i);      			

      			if (element.type == 'checkbox' &&       				
      				element.id.indexOf('box') == 0 &&
      				element.checked) {      				
      				deptlimit = deptlimit + element.value + ',';
				}
      		}
      		if (deptlimit.length != 0) {
      			deptlimit = deptlimit.substring(0, deptlimit.length -1);
      		}
      		document.CreateOperatorForm.deptLimitString.value = deptlimit;
      		document.CreateOperatorForm.cmd.value = cmd;
      		document.CreateOperatorForm.submit();
      	}
      	
      	//inital tree select status
      	function renderCancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/operator.do';
	}
</script>
</body>
