<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="college.collegemanage" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
				</td>
			</tr>
			<tr>
				<td height="40" align="center" valign="top">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<logic:present name="collegeleaders" scope="request">
							<logic:iterate name="collegeleaders" id="collegeandleader" indexId="i">
								<c:if test="${i%2 == 0}">
									<tr align="center" valign="top" height="100">
								</c:if>
								<td width="50%">
									<table width=95% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
										<tbody>
											<tr align="center" valign="middle">
												<td height="24" valign="middle" class="tableHeader">
													<a href="collegeAction.do?method=load4Edit&collegeId=<bean:write name="collegeandleader" property="collegeId"/>" class="topmenu_link"><bean:write name="collegeandleader" property="collegeName" />&nbsp;</a>
												</td>
											</tr>
											<tr align="center" valign="middle">
												<td height="24" align="center" valign="middle" bgcolor="#FFFFFF" class="medium">
													<bean:write name="collegeandleader" property="managerName" />&nbsp;
												</td>
											</tr>
											<tr align="center" valign="middle" bgcolor="#F6F4F5" height="120">
												<td>
													<bean:write name="collegeandleader" property="introduction" />&nbsp;
												</td>
											</tr>
										</tbody>
									</table>
								</td>

								<c:if test="${i%2 != 0}">
									</tr>
									<tr align="center" valign="top">
										<td>
											&nbsp;
										</td>
										<td>
											&nbsp;
										</td>
									</tr>
								</c:if>
							</logic:iterate>
						</logic:present>
					</table>
				</td>
			</tr>
			<tr>
				<td height="30" align="right" valign="middle">
					<input name="Submit2" type="button" class="button_nor" value="<bean:message key="button.add"/>" onclick="location.href='collegeAction.do?method=load4Add'">
				</td>
			</tr>
		</table>

	</body>
</center>

<script language="JavaScript">
 
	 function my_onload(){
	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 }
	 
	 window.onload=my_onload;	 

</script>
