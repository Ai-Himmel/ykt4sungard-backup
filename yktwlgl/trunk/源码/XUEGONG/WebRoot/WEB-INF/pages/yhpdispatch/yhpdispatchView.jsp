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

		<html:form action="/gyf/yhpdispatchAction.do?method=update" method="post">

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
												�ɷ���Ϣ��
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<tbody>
											<input type="hidden" name="ifChanged" value="0">
											<logic:present name="eqpDetail" scope="request">
												<logic:iterate name="eqpDetail" id="el" type="java.util.Map" indexId="i">
													<tr align="center" valign="middle">
														<td width="15%" align="right" valign="middle" class="tableHeader2">
															�׺�Ʒ����
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="materialId" />
															<input type="hidden" name="dispatchId" value="<bean:write name="el" property="id"/>" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�ɷ�ԭ��
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="pfReasonName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��;����
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="usageCategoryName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��;˵��
														</td>
														<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" colspan="3">
															<bean:write name="el" property="pfUsage" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															ԭ�ɷ�����
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="opfName" />
														</td>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															���ɷ�����
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="npfName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															ԭУ��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="oxqName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��У��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nxqName" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															ԭ¥��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="obdName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��¥��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nbdName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															ԭ����
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="ormName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�·���
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nrmName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															ԭ��ϸ�ص�
														</td>
														<td width="35%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
															<bean:write name="el" property="OPlace" />
														</td>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															����ϸ�ص�
														</td>
														<td width="35%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
															<bean:write name="el" property="NPlace" />
														</td>
													</tr>
													<%if (request.getAttribute("ifLimit").equals("0")) {%>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�ɷ�����
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="pfNum" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�ɷ����
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="beginNo" />
															&nbsp;--&nbsp;
															<bean:write name="el" property="endNo" />
														</td>
													</tr>
													<%}%>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															������
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="actPersonName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��ע
														</td>
														<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" colspan="3">
															<bean:write name="el" property="memo" />
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
       alert("δ�ҵ��׺�Ʒ�ɷ���Ϣ��");
}

function DoBack(){   
   self.close();
}

</script>
