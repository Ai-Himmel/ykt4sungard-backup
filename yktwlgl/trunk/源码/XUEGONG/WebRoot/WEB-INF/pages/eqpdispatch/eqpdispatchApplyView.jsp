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

		<html:form action="/gyf/eqpdispatchAction.do?method=updateApply" method="post">

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
												�ɷ������
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
															�豸���
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="equipmentNo" />
															<input type="hidden" name="applyId" value="<bean:write name="el" property="id"/>" />
														</td>
														<td width="15%" align="right" valign="middle" class="tableHeader2">
															�ʲ���
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="assetNo" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�豸����
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="wlmc" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�ɷ���������
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="applyName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															У��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="collegeArea" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															¥��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="lymc" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															����
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="roommc" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															������
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="cabinetmc" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��ʼλ��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="BLocation" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��ֹλ��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="ELocation" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�ϼܾ�����
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
									&nbsp;
								</td>
							</tr>
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												ԭʼ�ɷ���¼
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
											<logic:present name="dispatchDetail" scope="request">
												<logic:iterate name="dispatchDetail" id="el" type="java.util.Map" indexId="i">													
													<tr align="center" valign="middle">
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															�ɷ�ԭ��
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="pfReasonName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															��;����
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="usageCategoryName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															��;˵��
														</td>
														<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" colspan="3">
															<bean:write name="el" property="pfUsage" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															ԭ�ɷ�����
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="opfName" />
														</td>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															���ɷ�����
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="npfName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															ԭУ��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="oxqName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															��У��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nxqName" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															ԭ¥��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="obdName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															��¥��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nbdName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															ԭ����
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="ormName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															�·���
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nrmName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															ԭ��ϸ�ص�
														</td>
														<td width="35%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
															<bean:write name="el" property="OPlace" />
														</td>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															����ϸ�ص�
														</td>
														<td width="35%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
															<bean:write name="el" property="NPlace" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															ԭ����Ա
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="omgName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															�¹���Ա
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nmgName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															������
														</td>
														<td align="left" valign="middle" class="tableHeader3" >
															<bean:write name="el" property="actPersonName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															�ɷ���״̬
														</td>
														<td align="left" valign="middle" class="tableHeader3" >
															<c:if test="${el.NEqpState=='3_zaiyong'}">����</c:if>
															<c:if test="${el.NEqpState=='3_xianzhi'}">����</c:if>
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															����Ա���״̬
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="managerCheckName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															�Ǽ���
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="rcdPersonName" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															������
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="updatorName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
															����ʱ��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="updateTime" formatKey="dateTimeFormat" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
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
							<logic:present name="processlist" scope="request">
								<tr>
									<td height="35" align="center" valign="middle" class="mediumblack">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="35" align="left" valign="middle" class="mediumblack">
										<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
											<tr align="left" valign=center>
												<td width="12%" align="left" valign="middle" class="tableHeader8">
													�������
												</td>
												<td width="88%" align="left" valign="middle">
													<img onmouseover="this.style.cursor='hand';" id="opt_367628" src="<c:url value="/pages/style/default/images/title_open.gif"/>" onclick="openOrCloseOpt(105295,367628)" /></img>
												</td>
											</tr>
										</table>
									</td>
								</tr>
								<tr>
									<td height="20" align="center" valign="middle">
										<div id="opt_div_105295_367628" style="display:none">
											<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#3F738B bordercolordark=#ffffff id=submenu1>
												<tbody>
													<tr align="center" valign=center>
														<td valign="middle" class="tableHeader">
															�����㼶
														</td>
														<td valign="middle" class="tableHeader">
															������
														</td>
														<td valign="middle" class="tableHeader">
															�������
														</td>
														<td valign="middle" class="tableHeader">
															������ע
														</td>
														<td valign="middle" class="tableHeader">
															��������
														</td>
													</tr>
													<%int j = 0;%>
													<logic:iterate name="processlist" id="pl" type="java.util.Map" indexId="i">
														<tr align="center" valign=center <%if(j%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
															<td align="center" valign="middle">
																<bean:write name="pl" property="serial" />
																&nbsp;
															</td>
															<td align="center" valign="middle">
																<bean:write name="pl" property="checkPersonName" />
																&nbsp;
															</td>
															<td align="center" valign="middle">
																<bean:write name="pl" property="checkStateName" />
																&nbsp;
															</td>
															<td align="center" valign="middle">
																<bean:write name="pl" property="checkMemo" />
																&nbsp;
															</td>
															<td align="center" valign="middle">
																<bean:write name="pl" property="checkTime" formatKey="dateTimeFormat" />
																&nbsp;
															</td>
														</tr>
													</logic:iterate>
												</tbody>
											</table>
										</div>
									</td>
								</tr>
							</logic:present>
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
       alert("δ�ҵ��ɷ������¼��");  
  
}

function DoBack(){   
   self.close();
}

function openOrCloseOpt(opts_id,opt_id)
{
      var optDiv = document.getElementById('opt_div_'+opts_id+'_'+opt_id);5
      if(optDiv!=null){
	  if(optDiv.style.display=="none"){
	    optDiv.style.display="inline";
	    document.getElementById('opt_'+opt_id).src='<c:url value="/pages/style/default/images/title_close.gif"/>';
	  }else{
	    optDiv.style.display="none";
	    document.getElementById('opt_'+opt_id).src='<c:url value="/pages/style/default/images/title_open.gif"/>';
         }
       }
}
</script>
