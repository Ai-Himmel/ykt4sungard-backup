<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
	<head>
		<title>�Ϻ�������ѧ���Ͽ�漰�ִ�����ϵͳ</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<script src="<c:url value="/pages/scripts/util.js"/>" type="text/javascript"></script>

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>

		<html:form action="/gyf/yhpAction.do?method=load4view" method="post">

			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="left" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												������Ϣ
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="20" align="left" valign="top" background="<c:url value="/pages/style/default/images/titlebg3.jpg"/>" class="mediumblack">
									<table height="26" border="0" cellpadding="0" cellspacing="0">
										<tr align="center" valign="middle">
											<td width="98" background="<c:url value="/pages/style/default/images/titlebg2.gif"/>">
												<a href="javascript:DoUpdateYhpInfo()" class="black_link3">������Ϣ�޸�</a>
											</td>
											<td width="98" background="<c:url value="/pages/style/default/images/titlebg1.gif"/>" class="mediumblue">
												������Ϣ
											</td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="20" align="center" valign="top" bgcolor="#C3E0FC" class="tdborder04">
									<table width="98%" border="0" cellspacing="3" cellpadding="0">
										<tr>
											<td align="left" valign="top">
												<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#3F738B bordercolordark=#FFFFFF id=submenu1>
													<tbody>
														<logic:present name="yhpArl" scope="request">
															<logic:iterate name="yhpArl" id="el" type="java.util.Map" indexId="i">
																<tr align="center" valign="middle">
																	<td width="15%" align="right" valign="middle" class="tableHeader2" bgcolor="#FFFFFF">
																		�׺�Ʒ����
																	</td>
																	<td align="left" valign="middle" class="tableHeader3" colspan="3">
																		<bean:write name="el" property="id" />
																		&nbsp;
																		<input type="hidden" name="yhpNo" value="<bean:write name="el" property="id"/>">
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td width="15%" align="right" valign="middle" class="tableHeader2" bgcolor="#FFFFFF">
																		������
																	</td>
																	<td width="35%" align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="arrivalId" />
																		&nbsp;
																	</td>
																	<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		��������
																	</td>
																	<td width="35%" align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="arrivalDate" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		��������
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="arrivalNum" />
																		&nbsp;
																	</td>
																	<td align="right" valign="middle" class="tableHeader2" bgcolor="#FFFFFF">
																		����������
																	</td>
																	<td align="left" valign="middle" class="tableHeader3" nowrap>
																		<bean:write name="el" property="arrPersonName" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		������Դ
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="yhpSource" />
																		&nbsp;
																	</td>
																	<td align="right" valign="middle" class="tableHeader2" bgcolor="#FFFFFF">
																		�ɹ�����
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="procureDate" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		�ɹ���
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<%if (request.getAttribute("ifLimit").equals("0")) {%>
																		<bean:write name="el" property="procurePrice" />
																		<%}%>
																		&nbsp;
																	</td>
																	<td align="right" valign="middle" class="tableHeader2" bgcolor="#FFFFFF">
																		�ɹ�������
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="purPersonName" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		��������
																	</td>
																	<td width="35%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
																		<bean:write name="el" property="sccjName" />
																		&nbsp;
																	</td>
																	<td width="15%" align="right" valign="middle" class="tableHeader2" bgcolor="#FFFFFF">
																		��Ӧ��
																	</td>
																	<td width="35%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
																		<bean:write name="el" property="gysName" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		��ͬ����
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="contractNo" />
																		&nbsp;
																	</td>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		������
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="warrantyPeriod" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		������Դ
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="fundSource" />
																		&nbsp;
																	</td>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		��������
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="accountDate" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		��Ʊ����
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="receiptNo" />
																		&nbsp;
																	</td>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		����Ʊ����
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="receiptDate" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		������
																	</td>
																	<td align="left" valign="middle" class="tableHeader3" colspan="3">
																		<bean:write name="el" property="tkPersonName" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		��ע
																	</td>
																	<td colspan="3" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
																		<bean:write name="el" property="arlmemo" />
																		&nbsp;
																	</td>
																</tr>
															</logic:iterate>
														</logic:present>
													</tbody>
												</table>
											</td>
										</tr>
										<tr>
											<td height="30" align="right" valign="middle">
												<input name="Submit12" type="button" class="button_nor" value="�� ��" onClick="DoBack()">
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
						<logic:present name="msg" scope="request">
							<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
						</logic:present>
						<logic:notPresent name="msg" scope="request">
							<input name="hmsg" type="hidden" value="">
						</logic:notPresent>

						</html:form>
	</body>
</html>

<script type="text/javascript">

   setTimeout('DoInit()',10);

function DoInit(){
 
   if(document.all.hmsg.value=='0')
       alert("δ�ҵ��׺�Ʒ������Ϣ��");
}

function DoUpdateYhpInfo(){
    
    yhpsearchForm.action="yhpAction.do?method=load4update&cbgroup="+document.all.yhpNo.value;
	yhpsearchForm.submit();

}

function DoBack(){   
   yhpsearchForm.action="yhpAction.do?method=search4List&listNum='all'";
   yhpsearchForm.submit();
}
</script>
