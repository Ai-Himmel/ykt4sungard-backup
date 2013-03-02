<%@ include file="/html/commons/init.jsp" %>

<head>
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>

<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<html:form action="queryassemblyroom.do">
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr>
		<td>&nbsp;</td>
	</tr>
	<tr>
		<td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
			<span class="mediumwhite"><strong>
				&nbsp;&nbsp;&nbsp;
				<bean:message key="assemblyroom.query" />
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
						<bean:message key="assemblyroom.id" />
					</td>
					<td align="left" valign="middle" bgcolor="#E6ECF2">
						<input name="roomId" class="input_box" maxlength=50>
					</td>
				</tr>
				<tr>
					<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
						<bean:message key="assemblyroom.name" />
					</td>
					<td align="left" valign="middle" bgcolor="#E6ECF2">
						<input name="roomName" class="input_box" maxlength="50">
					</td>
				</tr>
				<tr>
					<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
						<bean:message key="assemblyroom.address" />
					</td>
					<td align="left" valign="middle" bgcolor="#E6ECF2">
						<input name="address" class="input_box" maxlength="50">
					</td>
				</tr>
				<tr>
					<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
						<bean:message key="assemblyroom.contain" />
					</td>
					<td align="left" valign="middle" bgcolor="#E6ECF2">
						<input name="contain" class="input_box" maxlength="4">
						&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		            	<a class="portlet-msg-error"><html:errors property="contain" /></a>
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
			<input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.query"/>" >
				&nbsp;&nbsp;&nbsp; 
			<input name="Submit2" type="reset" class="button_nor" value="<bean:message key="button.reset"/>" onclick="javascript:renderCancelPage()">
		</td>
	</tr>
</table>
</html:form>
<script>
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/viewassemblyroom.do';
	}
</script>
</body>