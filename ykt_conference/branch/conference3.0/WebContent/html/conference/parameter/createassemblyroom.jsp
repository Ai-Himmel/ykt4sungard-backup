<%@ include file="/html/commons/init.jsp" %>

<head>
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>

<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<html:form action="createassemblyroom.do">
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr>
      	<td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
			<span class="mediumwhite"><strong>
				&nbsp;&nbsp;&nbsp;
				<bean:message key="assemblyroom.create" />
			</strong></span>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<c:if test='<%=SessionErrors.contains(request, "assemblyroom.failed.roomid")%>'>	
				<font class="portlet-msg-error" style="font-size: 11;">					
					<bean:message key="assemblyroom.failed.roomid" />
				</font>
			</c:if>	
			<c:if test='<%=SessionErrors.contains(request, "assemblyroom.failed.name")%>'>	
				<font class="portlet-msg-error" style="font-size: 11;">
					<bean:message key="assemblyroom.failed.name" />
				</font>
			</c:if>
		</td>
    </tr>
    <tr> 
      <td align="left" valign="top">&nbsp; </td>
    </tr>
    <tr> 
		<td align="center" valign="top">
      		<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          		<!-- 
          		<tr> 
            		<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
						<bean:message key="assemblyroom.id" />
					</td>
					<td align="left" valign="middle" bgcolor="#E6ECF2">
						<input name="roomid" class="input_box" maxlength="8" 
							value="<%=ParamUtil.getString(request,"roomid")%>">
						&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		            	<a class="portlet-msg-error"><html:errors property="roomid" /></a>
					</td>
          		</tr>
          		-->
          		<tr>
					<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
						<bean:message key="assemblyroom.name" />
					</td>
					<td align="left" valign="middle" bgcolor="#E6ECF2">
						<input name="roomname" class="input_box" maxlength="25"
							value="<%=ParamUtil.getString(request,"roomname")%>">
						&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		            	<a class="portlet-msg-error"><html:errors property="roomname" /></a>	
					</td>
				</tr>
				<tr>
					<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
						<bean:message key="assemblyroom.address" />
					</td>
					<td align="left" valign="middle" bgcolor="#E6ECF2">
						<input name="address" class="input_box" maxlength="40"
							value="<%=ParamUtil.getString(request,"address")%>">
					</td>
				</tr>
				<tr>
					<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
						<bean:message key="assemblyroom.contain" />
					</td>
					<td align="left" valign="middle" bgcolor="#E6ECF2">
						<input name="contain" class="input_box" maxlength="4"
							value="<%=ParamUtil.getString(request,"contain")%>">
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
			<input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.ok"/>" >
				&nbsp;&nbsp;&nbsp; 
			<input name="Submit2" type="reset" class="button_nor" value="<bean:message key="button.cancle"/>" onclick="javascript:renderCancelPage()">
		</td>
    </tr>
</table>
</html:form>
<script>
	function renderCancelPage() {
		self.location = '<%=ContextUtil.getCtxPath(request)%>/viewassemblyroom.do';
	}
</script>
</body>
