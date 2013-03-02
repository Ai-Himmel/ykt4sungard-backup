<%@ include file="/html/commons/init.jsp" %>
<%@ page import="com.kingstargroup.conference.util.OperatorUtil" %>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TOperator" %>
<%@ page import="java.util.HashMap" %>

<head>
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<% 	String opercode = request.getParameter("opercode").toString();
	TOperator oper = OperatorUtil.getOperByOperCode(opercode);
	String operdept = oper.getDeptId().toString();
	String opername = oper.getOperName();
%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<form action="<%=ContextUtil.getCtxPath(request)%>/usermanage/edit_result.do" name="CreateOperatorForm" method="post">
	<input type=hidden name=cmd value="update">
	<input type=hidden name=opercode value="<%= opercode%>">
	<c:if test='<%= request.getParameter("userLimitString") != null%>'>
		<input type=hidden name=userLimitString value='<%= ParamUtil.getString(request, "userLimitString")%>'>
	</c:if>
	<c:if test='<%= request.getParameter("userLimitString") == null%>'>
		<input type=hidden name=userLimitString value="<%= OperatorUtil.getUserLimitString(opercode)%>">
	</c:if>
	<c:if test='<%= request.getParameter("deptLimitString") != null%>'>
		<input type=hidden name=deptLimitString value='<%= ParamUtil.getString(request, "deptLimitString")%>'>  
	</c:if>
	<c:if test='<%= request.getParameter("deptLimitString") == null%>'>
		<input type=hidden name=deptLimitString value='<%= OperatorUtil.getDeptLimitString(opercode)%>'>  
	</c:if>
<table width="800" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td>&nbsp;</td>
	</tr>
	<tr>
		<td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
			<span class="mediumwhite"><strong> 
				&nbsp;&nbsp;&nbsp;
				<bean:message key="operator.modify" /> 
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
					<input name="opercode" class="input_box" style="width: 200" 
						readonly="readonly" value="<%=opercode%>" maxlength=15>
					<a class="portlet-msg-error"><html:errors property="opercode" /></a>
				</td>
			</tr>
			<tr>
				<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
					<bean:message key="operator.opername" />
				</td>
				<td align="left" valign="middle" bgcolor="#E6ECF2">
					<input name="opername" class="input_box" style="width: 200" value="<%=opername%>" maxlength=15>
					<a class="portlet-msg-error"><html:errors property="opername" /></a>
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
								if (dept.get("deptCode").toString().equals(operdept)){
						%>					
								<option value="<%=dept.get("deptCode")%>" selected="selected"><%=dept.get("deptName")%></option>
						<%}else{%>						
								<option value="<%=dept.get("deptCode")%>"><%=dept.get("deptName")%></option>
						<%}}%>
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
			<input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.next"/>"
				onclick="javascript:setCmdValue('stage2');">&nbsp;&nbsp;&nbsp; 
			<input name="Submit2" type="reset" class="button_nor" value="<bean:message key="button.cancle"/>"
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
