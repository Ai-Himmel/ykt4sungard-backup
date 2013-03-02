<%@ include file="/html/commons/init.jsp" %>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="java.util.HashMap" %>
<%@ taglib uri="http://ajaxanywhere.sourceforge.net/" prefix="aa" %>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<form name="CreateOperatorForm" id="CreateOperatorForm" action="<%=ContextUtil.getCtxPath(request)%>/usermanage/add_result.do" method="post">
	<input type=hidden name=cmd value="stage1">
	<input type=hidden name=userLimitString value='<%= ParamUtil.getString(request, "userLimitString")%>'>
	<input type=hidden name=deptLimitString value='<%= ParamUtil.getString(request, "deptLimitString")%>'>  
<table width="800" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td>&nbsp;
		</td>
	</tr>
    <c:if test='<%= SessionErrors.contains(request, "conference.error.createuserfailure") %>'>		
	<tr>
		<td>				
			<font class="portlet-msg-error" style="font-size: 11;">
			<bean:message key="conference.error.user.exists" />
			</font>
		</td>
	</tr>
	</c:if>
    <c:if test='<%= SessionErrors.contains(request, "conference.editpassword.unpairedpassword") %>'>		
	<tr>
		<td>				
			<font class="portlet-msg-error" style="font-size: 11;">
			<bean:message key="conference.editpwd.error" />
			</font>
		</td>
	</tr>
	</c:if>
    <c:if test='<%= SessionErrors.contains(request, "conference.opercode.error") %>'>		
	<tr>
		<td>				
			<font class="portlet-msg-error" style="font-size: 11;">
			<bean:message key="conference.opercode.error" />
			</font>
		</td>
	</tr>
	</c:if>
    <c:if test='<%= SessionErrors.contains(request, "conference.password.error") %>'>		
	<tr>
		<td>				
			<font class="portlet-msg-error" style="font-size: 11;">
			<bean:message key="conference.password.error" />
			</font>
		</td>
	</tr>
	</c:if>
	<tr>
		<td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
			<span class="mediumwhite"><strong> 
				&nbsp;&nbsp;&nbsp;
				<bean:message key="operator.create" /> 
			</strong></span>
		</td>
	</tr>
	<tr>
		<td align="left" valign="top">&nbsp;</td>
	</tr>
	<tr>
		<td align="center" valign="top">
		<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
			<tr>
				<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
					<bean:message key="operator.opercode" />
				</td>
				<td align="left" valign="middle" bgcolor="#E6ECF2">
					<input name=opercode class="input_box" style="width: 200" maxlength=15 
							value='<%=ParamUtil.getString(request,"opercode")%>'
							>
					<a class="portlet-msg-error"><html:errors property="opercode" /></a>
				</td>
			</tr>
			<tr>
				<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
					<bean:message key="operator.opername" />
				</td>
				<td align="left" valign="middle" bgcolor="#E6ECF2">
					<input name=opername class="input_box" style="width: 200" maxlength=50 
							value='<%=ParamUtil.getString(request,"opername")%>'>
					<a class="portlet-msg-error"><html:errors property="opername" /></a>
				</td>
			</tr>
			<tr>
				<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
					class="medium">
					<bean:message key="operator.operpwd" />
				</td>
				<td align="left" valign="middle" bgcolor="#E6ECF2">
					<input name=operpwd type="password" class="input_box" style="width: 200" maxlength=50 
							>
					<a class="portlet-msg-error"><html:errors property="operpwd" /></a>
				</td>
			</tr>
			<tr>
				<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
					class="medium">
					<bean:message key="operator.pwdagain" />
				</td>
				<td align="left" valign="middle" bgcolor="#E6ECF2">
					<input name=pwdagain type="password" class="input_box" style="width: 200" maxlength=50 
							>
					<a class="portlet-msg-error"><html:errors property="pwdagain" /></a>
				</td>								
			</tr>
			<tr>
				<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
					class="medium">
					<bean:message key="operator.deptid" />
				</td>
				<td align="left" valign="middle" bgcolor="#E6ECF2">
					<select name="deptcode" class="select01" style="width: 200" >
						<%
							List deptlist = GetDictionary.getDeptList();
							Iterator iter = deptlist.iterator();
							while(iter.hasNext()) {
								HashMap dept = (HashMap) iter.next();							
						%>					
								<option value="<%=dept.get("deptCode")%>"><%=dept.get("deptName")%></option>
						<% 								
							}
						%>
					</select>
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
			<input name="Submit2" type="button" class="button_nor" value="<bean:message key="button.next"/>"
				onclick="javascript:setCmdValue('stage2');">&nbsp;&nbsp;&nbsp; 
			<input name="Submit2" type="button" class="button_nor" value="<bean:message key="button.cancle"/>"
				onclick="javascript:renderCancelPage()">
		</td>
	</tr>
</table>
</form>
<script>
	function setCmdValue(cmd) {
		document.CreateOperatorForm.cmd.value = cmd;
		document.CreateOperatorForm.submit();
	}
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/operator.do';
	}
	
</script>
</body>
