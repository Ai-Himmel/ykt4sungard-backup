<%@ include file="/html/commons/init.jsp"%>
<%@ include file="/html/commons/top_calendar.jsp"%>
<head>
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css">
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css">
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css">
</head>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<html:form action="deviceconfigure.do?flag=open" method="post">
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td>
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="25" align="left" valign="middle"
					background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
					<span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<span
							class="mediumwhite"><strong></strong> </span> <bean:message
								key="readcard.deviceconfigure" /> </strong> </span>
				</td>
			</tr>
			<tr>
				<td align="left" valign="top" class="medium">
					&nbsp;&nbsp;&nbsp;&nbsp;
					<a class="portlet-msg-error"><html:errors property="errorinfo" /> </a>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width="100%" border="1" cellspacing="0" cellpadding="2"
						bordercolor="#FFFFFF" bordercolordark="#F2F2F2">

						<tr>
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="readcard.port" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
							<html:select property="port" styleClass="input_box">
								<html:option value="1"><bean:message key="readcard.serial1" /></html:option>
								<html:option value="2"><bean:message key="readcard.serial2" /></html:option>
								<html:option value="3"><bean:message key="readcard.serial3" /></html:option>
								<html:option value="4"><bean:message key="readcard.serial4" /></html:option>
								<html:option value="5"><bean:message key="readcard.serial5" /></html:option>
								<html:option value="6"><bean:message key="readcard.serial6" /></html:option>
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								</html:select>
								<a class="portlet-msg-error"><html:errors property="port" />
								</a>
							</td>
						</tr>
						<tr>
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="readcard.frequency" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
							<html:select property="frequency" styleClass="input_box">
								<html:option value="19200">19200</html:option>
								<html:option value="600">600</html:option>
								<html:option value="1200">1200</html:option>
								<html:option value="2400">2400</html:option>
								<html:option value="4800">4800</html:option>
								<html:option value="9600">9600</html:option>
								<html:option value="14400">14400</html:option>								
								<html:option value="57600">57600</html:option>
							</html:select>
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="portlet-msg-error"><html:errors property="frequency" />
								</a>
							</td>
						</tr>						
					</table>
				</td>
			</tr>
			<tr>
				<td height="50" align="right" valign="middle" class="tdborder02">
					<html:submit>
						<bean:message key="readcard.open" />
					</html:submit>
					<html:submit onclick="javascript:mysubmit();">
						<bean:message key="readcard.close" />
					</html:submit>

				</td>
			</tr>

		</table>
	</html:form>
<script language="javascript">
function mysubmit(){
	document.forms[0].action='deviceconfigure.do?flag=close';
	document.forms[0].submit;
}
</script>
</body>
