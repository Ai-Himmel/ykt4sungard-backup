<%@ include file="/html/commons/init.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/util.js"></script>
</head>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<form name="CreateOperatorForm" action="<%=ContextUtil.getCtxPath(request)%>/usermanage/add_result.do" method="post">
	<%String userLimitString = ParamUtil.getString(request, "userLimitString");%>	
	<input type=hidden name=cmd value="create">
	<input type=hidden name=opercode value='<%= ParamUtil.getString(request, "opercode")%>'>
	<input type=hidden name=opername value='<%= ParamUtil.getString(request, "opername")%>'>
	<input type=hidden name=operpwd value='<%= ParamUtil.getString(request, "operpwd")%>'>	
	<input type=hidden name=pwdagain value='<%= ParamUtil.getString(request, "pwdagain")%>'>
	<input type=hidden name=deptcode value='<%= ParamUtil.getString(request, "deptcode")%>'>
	<input type=hidden name=deptLimitString value='<%= ParamUtil.getString(request, "deptLimitString")%>'>
	<input type=hidden name=userLimitString value='<%= userLimitString%>'>
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr> 
    <tr> 
      <td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
      <span class="mediumwhite"><strong><bean:message key="operator.limit"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="left" valign="top" >
      	<%@ include file="module_tree.jsp" %>
      </td>
    </tr>
    <tr> 
      <td align="center" valign="top" class="tdborder02" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle" >
      	<input name="Submit24" type="button" class="button_nor" value="<bean:message key="button.back"/>" 
      		onClick="javascript:setCmdValue('stage2');" > &nbsp;&nbsp; 
      	<input name="Submit252" type="button" class="button_nor" value="<bean:message key="button.ok"/>" 
      		onClick="javascript:setCmdValue('create');" >&nbsp;&nbsp; 
      	<input name="Submit2522" type="button" class="button_nor" value="<bean:message key="button.cancle"/>" 
      		onClick="javascript:renderCancelPage();" ></td>
    </tr>
	</table>
</form>
<script>
      	function setCmdValue(cmd) {
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
      		document.CreateOperatorForm.userLimitString.value = userlimit;
      		document.CreateOperatorForm.cmd.value = cmd;
      		document.CreateOperatorForm.submit();
      	}      	
      	//inital tree select status
      	function renderCancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/operator.do';
      	}
</script>
	<script language="JavaScript">
		var dlTree = new Tree("dlTree", dlArray, dlIcons, "topmenu_link_12", "<%= userLimitString%>");
		dlTree.create("dlTree");		
	</script>
</body>
