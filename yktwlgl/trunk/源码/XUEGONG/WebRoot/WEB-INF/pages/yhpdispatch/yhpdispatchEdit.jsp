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

		<script>

var idcount=0;
idset=new Array();

<%
   int idsCount=0;
   String[] idsSet=null;
   if(request.getAttribute("ids")!=null)
       idsSet=(String[])request.getAttribute("ids");//��ȡ�׺�Ʒ�ɷ�id����
   
   if(idsSet!=null){
     for(idsCount=0;idsCount<idsSet.length;idsCount++)
     {
     %>
      idset[<%=idsCount%>] = new Array("<%=idsSet[idsCount]%>");//����javascript����
     <%
     }
   }
   %>
   idcount=<%=idsCount%>;
</script>
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
											<logic:present name="yhplist" scope="request">
												<logic:iterate name="yhplist" id="el" type="java.util.Map" indexId="i">
													<tr align="center" valign="middle">
														<td width="15%" align="right" valign="middle" class="tableHeader2">
															�׺�Ʒ����
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="materialId" />
															<input type="hidden" name="dispatchId" value="<bean:write name="el" property="id"/>" />
															<input type="hidden" name="yhpNo" value="<bean:write name="el" property="materialId"/>" />
															<input type="hidden" name="yhpNum" value="<bean:write name="el" property="yhpNum"/>" />
															<input type="hidden" name="ocurNum" value="<bean:write name="el" property="curNum"/>" />
															<input type="hidden" name="opfid" value="<bean:write name="el" property="pfid"/>" />
															<input type="hidden" name="opfNum" value="<bean:write name="el" property="pfNum"/>" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															<font color="red" style="font-weight:normal">*</font>&nbsp;�ɷ�ԭ��
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<select name="s_pfReason" class="select01" onchange="changePfReason(this)">
																<option value="" checked>
																	��ѡ��
																</option>
																<logic:present name="yhppfReasonlist" scope="request">
																	<logic:iterate name="yhppfReasonlist" id="pr" type="java.util.Map">
																		<option value="<bean:write name="pr" property="dictValue"/>">
																			<bean:write name="pr" property="dictCaption" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="pfReason" value="<bean:write name="el" property="pfReason"/>" title="�ɷ�ԭ��" isMust='1'>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��;����
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_usageCategory" class="select01" onchange="changeUsageCategory(this)">
																			<option value="" checked>
																				��ѡ��
																			</option>
																			<logic:present name="uclist" scope="request">
																				<logic:iterate name="uclist" id="uc" type="java.util.Map">
																					<option value="<bean:write name="uc" property="id"/>">
																						<bean:write name="uc" property="usageCategoryName" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="usageCategory" value="<bean:write name="el" property="usageCategory"/>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempUsageCategory" style="input_box" maxlength="50" value="<bean:write name="el" property="usageCategoryName"/>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addUsageCategory" type="button" value="����"
																			onclick="javascript:window.open('deptUsageCategoryAction.do?method=search4List&formName=yhpdispatchForm&addNum='+idcount,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��;˵��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<textarea name="pfUsage" cols=70 rows=2><bean:write name="el" property="pfUsage" /></textarea>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															<font color="red" style="font-weight:normal">*</font>&nbsp;���ɷ�����
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_pfid" class="select01" onchange="changePfid(this)">
																<option value="" checked>
																	��ѡ��
																</option>
																<logic:present name="pflist" scope="request">
																	<logic:iterate name="pflist" id="pfl" type="java.util.Map">
																		<option value="<bean:write name="pfl" property="dictValue"/>">
																			<bean:write name="pfl" property="dictCaption" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="pfid" value="<bean:write name="el" property="pfid"/>" title="���ɷ�����" isMust='1'>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��У��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_xqid" class="select01" onchange="changeBd(this);changeXqid(this)">
																<option value="" checked>
																	��ѡ��
																</option>
																<logic:present name="arealist" scope="request">
																	<logic:iterate name="arealist" id="al" type="java.util.Map">
																		<option value="<bean:write name="al" property="dictValue"/>">
																			<bean:write name="al" property="dictCaption" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="xqid" value="<bean:write name="el" property="xqid"/>">
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��¥��
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_bdid" class="select01" onchange="changeRm(this);changeBdid(this)">
																			<option value="" checked>
																				��ѡ��
																			</option>
																			<logic:present name="buildinglist" scope="request">
																				<logic:iterate name="buildinglist" id="bdl" type="java.util.Map">
																					<option value="<bean:write name="bdl" property="id"/>">
																						<bean:write name="bdl" property="lymc" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="bdid" value="<bean:write name="el" property="bdid"/>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempbuilding" style="input_box" maxlength="50" value="<bean:write name="el" property="lymc"/>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addBuilding" type="button" value="����" onclick="DoaddLymc()">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�·���
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_rmid" class="select01" onchange="changeRoom(this);changeRmid(this)">
																			<option value="" checked>
																				��ѡ��
																			</option>
																			<logic:present name="roomlist" scope="request">
																				<logic:iterate name="roomlist" id="rml" type="java.util.Map">
																					<option value="<bean:write name="rml" property="id"/>">
																						<bean:write name="rml" property="roommc" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="rmid" value="<bean:write name="el" property="rmid"/>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="temproom" style="input_box" maxlength="50" value="<bean:write name="el" property="roommc"/>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addRoom" type="button" value="����" onclick="DoaddRoom()">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��ϸ�ص�
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<textarea name="NPlace" cols=70 rows=2><bean:write name="el" property="NPlace" /></textarea>
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�ɷ�����
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<input name="pfNum" style="input_box" maxlength="50" value="<bean:write name="el" property="pfNum"/>" title="�ɷ�����" dataType="Int" isMust='1' />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															�ɷ����
														</td>
														<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" nowrap="nowrap">
															<input name="beginNo" style="input_box" maxlength="50" value="<bean:write name="el" property="beginNo"/>" />
															&nbsp;--&nbsp;
															<input name="endNo" style="input_box" maxlength="50" value="<bean:write name="el" property="endNo"/>" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															������(�ڲ�)
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_deptacpid" class="select01" onchange="changedeptAcpid(this)">
																<option value="" checked>
																	��ѡ��
																</option>
																<logic:present name="mglist" scope="request">
																	<logic:iterate name="mglist" id="mgl" type="java.util.Map">
																		<option value="<bean:write name="mgl" property="code"/>">
																			<bean:write name="mgl" property="personName" />
																			&nbsp;
																			<bean:write name="mgl" property="code" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															������(�ⲿ)
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_acpid" class="select01" onchange="changeAcpid(this)">
																			<option value="" checked>
																				��ѡ��
																			</option>
																			<logic:present name="acplist" scope="request">
																				<logic:iterate name="acplist" id="acpl" type="java.util.Map">
																					<option value="<bean:write name="acpl" property="id"/>">
																						<bean:write name="acpl" property="personName" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="acpid" value="<bean:write name="el" property="actPersonId"/>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempAcpPerson" style="input_box" maxlength="50" value="<bean:write name="el" property="actPersonName"/>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addAcpPerson" type="button" value="����"
																			onclick="javascript:window.open('deptOtherPersonAction.do?method=search4List&formName=yhpdispatchForm&addNum='+idcount,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															��ע
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<textarea name="memo" cols=70 rows=2><bean:write name="el" property="memo" /></textarea>
														</td>
													</tr>
												</logic:iterate>
											</logic:present>
											<logic:present name="yhpbatchlist" scope="request">

												<tr align="center" valign="middle">
													<td width="15%" align="right" valign="middle" class="tableHeader2">
														�׺�Ʒ����
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														---
													</td>
												</tr>
												<tr align="center" valign="middle">
													<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														�ɷ�ԭ��
													</td>
													<td width="35%" align="left" valign="middle" class="tableHeader3">
														<select name="bs_pfReason" class="select01" onchange="BchangePfReason(this)">
															<option value="" checked>
																��ѡ��
															</option>
															<logic:present name="yhppfReasonlist" scope="request">
																<logic:iterate name="yhppfReasonlist" id="pr" type="java.util.Map">
																	<option value="<bean:write name="pr" property="dictValue"/>">
																		<bean:write name="pr" property="dictCaption" />
																	</option>
																</logic:iterate>
															</logic:present>
														</select>
														<input type="hidden" name="bpfReason" value="<%=request.getParameter("bpfReason")==null||request.getParameter("bpfReason").equals("null")?"":request.getParameter("bpfReason")%>">
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														��;����
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<table border="0" cellspacing="0" cellpadding="0">
															<tr align="center" valign="middle">
																<td width="35">
																	<select name="bs_usageCategory" class="select01" onchange="BchangeUsageCategory(this)">
																		<option value="" checked>
																			��ѡ��
																		</option>
																		<logic:present name="uclist" scope="request">
																			<logic:iterate name="uclist" id="uc" type="java.util.Map">
																				<option value="<bean:write name="uc" property="id"/>">
																					<bean:write name="uc" property="usageCategoryName" />
																				</option>
																			</logic:iterate>
																		</logic:present>
																	</select>
																	<input type="hidden" name="busageCategory" value="<%=request.getParameter("busageCategory")==null||request.getParameter("busageCategory").equals("null")?"":request.getParameter("busageCategory")%>">
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="40" align="right">
																	<input name="btempUsageCategory" style="input_box" maxlength="50" value="<%=request.getParameter("btempUsageCategory")==null||request.getParameter("btempUsageCategory").equals("null")?"":request.getParameter("btempUsageCategory")%>"
																		readonly="readonly" />
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="20" align="right">
																	<input name="addUsageCategory" type="button" value="����"
																		onclick="javascript:window.open('deptUsageCategoryAction.do?method=search4List&formName=yhpdispatchForm&addNum='+idcount,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														��;˵��
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<textarea name="bpfUsage" cols=70 rows=2 onchange="BchangePfUsage(this)"></textarea>
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														���ɷ�����
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<select name="bs_pfid" class="select01" onchange="BchangePfid(this)">
															<option value="" checked>
																��ѡ��
															</option>
															<logic:present name="pflist" scope="request">
																<logic:iterate name="pflist" id="pfl" type="java.util.Map">
																	<option value="<bean:write name="pfl" property="dictValue"/>">
																		<bean:write name="pfl" property="dictCaption" />
																	</option>
																</logic:iterate>
															</logic:present>
														</select>
														<input type="hidden" name="bpfid" value="<%=request.getParameter("bpfid")==null||request.getParameter("bpfid").equals("null")?"":request.getParameter("bpfid")%>">
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														��У��
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<select name="bs_xqid" class="select01" onchange="BchangeBd(this);BchangeXqid(this)">
															<option value="" checked>
																��ѡ��
															</option>
															<logic:present name="arealist" scope="request">
																<logic:iterate name="arealist" id="al" type="java.util.Map">
																	<option value="<bean:write name="al" property="dictValue"/>">
																		<bean:write name="al" property="dictCaption" />
																	</option>
																</logic:iterate>
															</logic:present>
														</select>
														<input type="hidden" name="bxqid" value="<%=request.getParameter("bxqid")==null||request.getParameter("bxqid").equals("null")?"":request.getParameter("bxqid")%>">
													</td>
												</tr>
												<tr align="center" valign="middle">
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														��¥��
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<table border="0" cellspacing="0" cellpadding="0">
															<tr align="center" valign="middle">
																<td width="35">
																	<select name="bs_bdid" class="select01" onchange="BchangeRm(this);BchangeBdid(this)">
																		<option value="" checked>
																			��ѡ��
																		</option>
																		<logic:present name="buildinglist" scope="request">
																			<logic:iterate name="buildinglist" id="bdl" type="java.util.Map">
																				<option value="<bean:write name="bdl" property="id"/>">
																					<bean:write name="bdl" property="lymc" />
																				</option>
																			</logic:iterate>
																		</logic:present>
																	</select>
																	<input type="hidden" name="bbdid" value="<%=request.getParameter("bbdid")==null||request.getParameter("bbdid").equals("null")?"":request.getParameter("bbdid")%>">
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="40" align="right">
																	<input name="btempbuilding" style="input_box" maxlength="50" value="<%=request.getParameter("btempbuilding")==null||request.getParameter("btempbuilding").equals("null")?"":request.getParameter("btempbuilding")%>" readonly="readonly" />
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="20" align="right">
																	<input name="addBuilding" type="button" value="����" onclick="BDoaddLymc()">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														�·���
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<table border="0" cellspacing="0" cellpadding="0">
															<tr align="center" valign="middle">
																<td width="35">
																	<select name="bs_rmid" class="select01" onchange="BchangeRoom(this);BchangeRmid(this)">
																		<option value="" checked>
																			��ѡ��
																		</option>
																		<logic:present name="roomlist" scope="request">
																			<logic:iterate name="roomlist" id="rml" type="java.util.Map">
																				<option value="<bean:write name="rml" property="id"/>">
																					<bean:write name="rml" property="roommc" />
																				</option>
																			</logic:iterate>
																		</logic:present>
																	</select>
																	<input type="hidden" name="brmid" value="<%=request.getParameter("brmid")==null||request.getParameter("brmid").equals("null")?"":request.getParameter("brmid")%>">
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="40" align="right">
																	<input name="btemproom" style="input_box" maxlength="50" value="<%=request.getParameter("btemproom")==null||request.getParameter("btemproom").equals("null")?"":request.getParameter("btemproom")%>" readonly="readonly" />
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="20" align="right">
																	<input name="addRoom" type="button" value="����" onclick="BDoaddRoom()">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														��ϸ�ص�
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<textarea name="bNPlace" cols=70 rows=2 onchange="BchangeNPlace(this)"></textarea>
													</td>
												</tr>
												<tr align="center" valign="middle">
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														�ɷ�����
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<input type="text" name="bpfNum" style="input_box" maxlength="50" value="" onchange="BchangePfNum(this)" title="�ɷ�����" dataType="Int" />
													</td>
												</tr>
												<tr align="center" valign="middle">
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														�ɷ����
													</td>
													<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" nowrap="nowrap">
														<input name="bbeginNo" type="text" style="input_box" maxlength="50" value="" onchange="BchangeBeginNo(this)" />
														&nbsp;--&nbsp;
														<input name="bendNo" type="text" style="input_box" maxlength="50" value="" onchange="BchangeEndNo(this)" />
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														������(�ڲ�)
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<select name="bs_deptacpid" class="select01" onchange="BchangedeptAcpid(this)">
															<option value="" checked>
																��ѡ��
															</option>
															<logic:present name="mglist" scope="request">
																<logic:iterate name="mglist" id="mgl" type="java.util.Map">
																	<option value="<bean:write name="mgl" property="code"/>">
																		<bean:write name="mgl" property="personName" />
																		&nbsp;
																		<bean:write name="mgl" property="code" />
																	</option>
																</logic:iterate>
															</logic:present>
														</select>
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														������(�ⲿ)
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<table border="0" cellspacing="0" cellpadding="0">
															<tr align="center" valign="middle">
																<td width="35">
																	<select name="bs_acpid" class="select01" onchange="BchangeAcpid(this)">
																		<option value="" checked>
																			��ѡ��
																		</option>
																		<logic:present name="acplist" scope="request">
																			<logic:iterate name="acplist" id="acpl" type="java.util.Map">
																				<option value="<bean:write name="acpl" property="id"/>">
																					<bean:write name="acpl" property="personName" />
																				</option>
																			</logic:iterate>
																		</logic:present>
																	</select>
																	<input type="hidden" name="bacpid" value="<%=request.getParameter("bacpid")==null||request.getParameter("bacpid").equals("null")?"":request.getParameter("bacpid")%>">
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="40" align="right">
																	<input name="btempAcpPerson" style="input_box" maxlength="50" value="<%=request.getParameter("btempAcpPerson")==null||request.getParameter("btempAcpPerson").equals("null")?"":request.getParameter("btempAcpPerson")%>" readonly="readonly" />
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="20" align="right">
																	<input name="addAcpPerson" type="button" value="����"
																		onclick="javascript:window.open('deptOtherPersonAction.do?method=search4List&formName=yhpdispatchForm&addNum='+idcount,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														��ע
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<textarea name="bmemo" cols=70 rows=2 onchange="BchangeMemo(this)"></textarea>
													</td>
												</tr>

												<logic:iterate name="yhpbatchlist" id="ebl" type="java.util.Map" indexId="i">
													<input type="hidden" name="dispatchId_<bean:write name="ebl" property="id"/>" value="<bean:write name="ebl" property="id"/>">
													<input type="hidden" name="<bean:write name="ebl" property="id"/>yhpNo" value="<bean:write name="ebl" property="materialId"/>">
													<input type="hidden" name="<bean:write name="ebl" property="id"/>yhpNum" value="<bean:write name="ebl" property="yhpNum"/>">
													<input type="hidden" name="<bean:write name="ebl" property="id"/>ocurNum" value="<bean:write name="ebl" property="curNum"/>">
													<input type="hidden" name="<bean:write name="ebl" property="id"/>opfNum" value="<bean:write name="ebl" property="pfNum"/>">
													<input type="hidden" name="<bean:write name="ebl" property="id"/>opfid" value="<bean:write name="ebl" property="pfid"/>">
												</logic:iterate>
											</logic:present>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="30" align="right" valign="middle">
									<%if (idsCount == 1) {%>
									<input name="Submit11" type="button" class="button_nor" value="�� ��" onclick="doSave();">
									<%} else if (idsCount > 1) {%>
									<input name="Submit10" type="button" class="button_nor" value="��������" onclick="doBatchSave();">
									<%}%>
									&nbsp;
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
						<logic:present name="ncupdate" scope="request">
							<input name="hncupdate" type="hidden" value="<bean:write name="ncupdate" />">
						</logic:present>
						<logic:notPresent name="ncupdate" scope="request">
							<input name="hncupdate" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="nccols" scope="request">
							<input name="hnccols" type="hidden" value="<bean:write name="nccols" />">
						</logic:present>
						<logic:notPresent name="nccols" scope="request">
							<input name="hnccols" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="ncPfNum" scope="request">
							<input name="hncPfNum" type="hidden" value="<bean:write name="ncPfNum" />">
						</logic:present>
						<logic:notPresent name="ncPfNum" scope="request">
							<input name="hncPfNum" type="hidden" value="">
						</logic:notPresent>

						<jodd:form bean="request">
							<input type="hidden" name="ec_i" />
							<input type="hidden" name="ec_p" />
							<input type="hidden" name="ec_crd" />
							<input type="hidden" name="search_bh" />
							<input type="hidden" name="search_wlmc" />
							<input type="hidden" name="search_opfdx" />
							<input type="hidden" name="search_oxq" />
							<input type="hidden" name="search_olouyu" />
							<input type="hidden" name="search_npfdx" />
							<input type="hidden" name="search_nxq" />
							<input type="hidden" name="search_nlouyu" />
							<input type="hidden" name="search_pfyy" />
							<input type="hidden" name="search_pfbNo" />
							<input type="hidden" name="search_sqr" />
							<input type="hidden" name="search_djrqc" />
							<input type="hidden" name="search_djrqd" />

						</jodd:form>
						</html:form>
	</body>
</html>


<script>

    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("ablist")!=null)
       resultset=(String[][])request.getAttribute("ablist");//��ȡУ����¥���Ӧ����
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//����javascript��ά���飬��Ӧ¥��id��¥�����ơ�У��id
     <%
     }
   }
   %>
   datacount=<%=count%>;

</script>
<script>

    var datacount2=0;
    dataset2=new Array();
    
   <%
   int count2=0;
   String[][] resultset2=null;
   if(request.getAttribute("bmlist")!=null)
       resultset2=(String[][])request.getAttribute("bmlist");//��ȡ¥������Ӧ����
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>","<%=resultset2[count2][3]%>");//����javascript��ά���飬��Ӧ����id���������ơ������ʶ��¥��id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>


<script type="text/javascript">

if(idcount==1)
   setTimeout('DoInit()',10);
else if(idcount>1)
   setTimeout('DoBatchInit()',10);
   
function DoInit(){
  var pr,uc,pf,xq,bd,rm,acp;
  var hasuc=false;
  var hasbd=false;
  var hasrm=false;
  var hasacp=false;
     //alert("idcount="+idcount);
     pr=document.yhpdispatchForm.elements["pfReason"].value;
     uc=document.yhpdispatchForm.elements["usageCategory"].value;
     pf=document.yhpdispatchForm.elements["pfid"].value;
     xq=document.yhpdispatchForm.elements["xqid"].value;
     bd=document.yhpdispatchForm.elements["bdid"].value;
     rm=document.yhpdispatchForm.elements["rmid"].value;
     acp=document.yhpdispatchForm.elements["acpid"].value;
  
   for(var i=0;i<document.yhpdispatchForm.elements["s_pfReason"].length;i++){//�ɷ�ԭ��
       if(document.yhpdispatchForm.elements["s_pfReason"][i].value==pr)
            document.yhpdispatchForm.elements["s_pfReason"][i].selected=true;
   }
   for(var i=0;i<document.yhpdispatchForm.elements["s_usageCategory"].length;i++){//��;����
       if(document.yhpdispatchForm.elements["s_usageCategory"][i].value==uc){
            document.yhpdispatchForm.elements["s_usageCategory"][i].selected=true;
            hasuc=true;
       }
   }
   
   if(hasuc){
       document.yhpdispatchForm.elements["s_usageCategory"].style.display='';
       document.yhpdispatchForm.elements["tempUsageCategory"].style.display='none';
   }
   else{
       document.yhpdispatchForm.elements["s_usageCategory"].style.display='none';
       document.yhpdispatchForm.elements["tempUsageCategory"].style.display='';   
   }
   
   for(var i=0;i<document.yhpdispatchForm.elements["s_pfid"].length;i++){//�ɷ�����
       if(document.yhpdispatchForm.elements["s_pfid"][i].value==pf)
            document.yhpdispatchForm.elements["s_pfid"][i].selected=true;
   }
  
  for(var i=0;i<document.yhpdispatchForm.elements["s_xqid"].length;i++){//У��
       if(document.yhpdispatchForm.elements["s_xqid"][i].value==xq)
            document.yhpdispatchForm.elements["s_xqid"][i].selected=true;  
   }
   if(xq!='')
      changeBd(document.yhpdispatchForm.elements["s_xqid"]);
      for(var j=0;j<document.yhpdispatchForm.elements["s_bdid"].length;j++){
      if(document.yhpdispatchForm.elements["s_bdid"][j].value==bd){
	     document.yhpdispatchForm.elements["s_bdid"][j].selected=true;
	     hasbd=true;
	  }
	  }		
	  
   if(hasbd){
	      document.yhpdispatchForm.elements["s_bdid"].style.display='';
	      document.yhpdispatchForm.elements["tempbuilding"].style.display='none';	  
   }
	else{
	     document.yhpdispatchForm.elements["s_bdid"].style.display='none';
	     document.yhpdispatchForm.elements["tempbuilding"].style.display='';	  
	}	
   
   if(bd!='')
        changeRm(document.yhpdispatchForm.elements["s_bdid"]);
   for(var j=0;j<document.yhpdispatchForm.elements["s_rmid"].length;j++){
      if(document.yhpdispatchForm.elements["s_rmid"][j].value==rm){
	     document.yhpdispatchForm.elements["s_rmid"][j].selected=true;
	     hasrm=true;
	  }
   }
   
   if(hasrm){
	      document.yhpdispatchForm.elements["s_rmid"].style.display='';
	      document.yhpdispatchForm.elements["temproom"].style.display='none';	  
   }
	else{
	     document.yhpdispatchForm.elements["s_rmid"].style.display='none';
	     document.yhpdispatchForm.elements["temproom"].style.display='';	  
	}   
   
    for(var i=0;i<document.yhpdispatchForm.elements["s_deptacpid"].length;i++){//�ڲ�������
       if(document.yhpdispatchForm.elements["s_deptacpid"][i].value==acp)
            document.yhpdispatchForm.elements["s_deptacpid"][i].selected=true;        
   }
    for(var i=0;i<document.yhpdispatchForm.elements["s_acpid"].length;i++){//�ⲿ������
       if(document.yhpdispatchForm.elements["s_acpid"][i].value==acp){
            document.yhpdispatchForm.elements["s_acpid"][i].selected=true;
            hasacp=true;
       }
   }   
   if(hasacp){
       document.yhpdispatchForm.elements["s_acpid"].style.display='';
       document.yhpdispatchForm.elements["tempAcpPerson"].style.display='none';
   }
   else{
       document.yhpdispatchForm.elements["s_acpid"].style.display='none';
       document.yhpdispatchForm.elements["tempAcpPerson"].style.display='';   
   }
   if(document.yhpdispatchForm.elements["s_deptacpid"].value!='')   
       document.yhpdispatchForm.elements["tempAcpPerson"].value="";
   
   if(document.all.hmsg.value=='1')
       alert("����ɹ���");
   else if(document.all.hmsg.value=='0')
       alert("����ʧ�ܣ�");   
   else if(document.all.hmsg.value=='8')
       alert("�����޸ģ�");
   if(document.all.hncupdate.value!=''){
       alert("�޸�"+document.all.hncupdate.value+"���ɷ���¼��");
       alert("һ���׺�Ʒֻ���޸����µ��ɷ���¼��");
   }
}

function DoBatchInit(){

   var xq,bd,rm;
   
   var hasbd=false;
   var hasrm=false;
       
     xq=document.all.bs_xqid.value;
     bd=document.all.bs_bdid.value;
     rm=document.all.bs_rmid.value;
          
     if(xq!='')
      BchangeBd(document.all.bs_xqid);
      for(var j=0;j<document.all.bs_bdid.length;j++){
      if(document.all.bs_bdid[j].value==bd){
	     document.all.bs_bdid[j].selected=true;
	     hasbd=true;
	  }
	  }	
	  
	if(hasbd){
	      document.all.bs_bdid.style.display='';
	      document.all.btempbuilding.style.display='none';	  
	  }
	  else{
	      document.all.bs_bdid.style.display='none';
	      document.all.btempbuilding.style.display='';	  
	  }			
   
   if(bd!='')
        BchangeRm(document.all.bs_bdid);
   for(var j=0;j<document.all.bs_rmid.length;j++){
      if(document.all.bs_rmid[j].value==rm){
	     document.all.bs_rmid[j].selected=true;
	     hasrm=true;
	  }
   }   
   
   if(hasrm){
	      document.all.bs_rmid.style.display='';
	      document.all.btemproom.style.display='none';	  
	  }
	  else{
	      document.all.bs_rmid.style.display='none';
	      document.all.btemproom.style.display='';	  
   }		  
   
   var uc;
   var hasuc=false;
   uc=document.all.busageCategory.value;
   for(var i=0;i<document.all.bs_usageCategory.length;i++){//��;����
       if(document.all.bs_usageCategory[i].value==uc){
           hasuc=true;
       }
   }
   
   if(hasuc){
       document.all.bs_usageCategory.style.display='';
       document.all.btempUsageCategory.style.display='none';
   }
   else{
       document.all.bs_usageCategory.style.display='none';
       document.all.btempUsageCategory.style.display='';   
   }
   
   var acp;
   var hasacp=false;
   
   acp=document.all.bacpid.value;
   for(var i=0;i<document.all.bs_deptacpid.length;i++){//�ڲ�������
       if(document.all.bs_deptacpid[i].value==acp)
            document.all.bs_deptacpid[i].selected=true;        
   }
   for(var i=0;i<document.all.bs_acpid.length;i++){//�ⲿ��Ա
       if(document.all.bs_acpid[i].value==acp){
           hasacp=true;
       }
   }
   
   if(hasacp){
       document.all.bs_acpid.style.display='';
       document.all.btempAcpPerson.style.display='none';
   }
   else{
       document.all.bs_acpid.style.display='none';
       document.all.btempAcpPerson.style.display='';   
   }
   
   if(document.all.bs_deptacpid.value!='')   
       document.all.btempAcpPerson.value="";
   
   if(document.all.hmsg.value=='1')
       alert("����ɹ���");
   else if(document.all.hmsg.value=='0')
       alert("����ʧ�ܣ�");
   if(document.all.hnccols.value!='')
       alert(document.all.hnccols.value+" �����޸ģ�");
   if(document.all.hncupdate.value!=''){
       alert("�޸�"+document.all.hncupdate.value+"���ɷ���¼��");
       alert("һ���׺�Ʒֻ���޸����µ��ɷ���¼��");
   }
   if(document.all.hncPfNum.value!='')
       alert(document.all.hncPfNum.value+" �ɷ����������׺�Ʒ�Ŀ���������ɷ�ʧ�ܣ�");
}

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.s_bdid.length=1; //���ԭ¥���б�
   document.all.s_rmid.length=1; //���ԭ�����б�        
      
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.all.s_bdid.options[document.all.s_bdid.length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.all.s_bdid.options[document.all.s_bdid.length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
      for (i=0;i < datacount2; i++)
      {
          document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
    }
   

}

function changeRm(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.s_rmid.length=1; //���ԭ�����б�        
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
      for (i=0;i < datacount; i++){
          if (dataset[i][0] == id){
             document.all.s_xqid.value=dataset[i][2];
          }
      }
    }else{
       //alert("wl is null");
       for (i=0;i < datacount2; i++)
      {
          document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function changeRoom(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   
   if(id!="")
      for (var i=0;i < datacount2; i++)
      {
         if (dataset2[i][0] == id)
          {                
             document.all.s_bdid.value=dataset2[i][3];              
             for (var j=0;j< datacount;j++){
                 if (dataset[j][0] == document.all.s_bdid.value){
                     document.all.s_xqid.value=dataset[j][2];
                 }
             }
          }
      }
    
}

function changePfReason(sel){
    document.all.pfReason.value=sel.value;
}

function changeUsageCategory(sel){
    document.all.usageCategory.value=sel.value;
}

function changePfid(sel){
    document.all.pfid.value=sel.value;
}

function changeXqid(sel){
    document.all.xqid.value=sel.value;
}

function changeBdid(sel){
    document.all.bdid.value=sel.value;
}

function changeRmid(sel){
    document.all.rmid.value=sel.value;
}

function changeAcpid(sel){
    document.all.acpid.value=sel.value;
    document.all.s_deptacpid.value="";
}

function changedeptAcpid(sel){
    document.all.acpid.value=sel.value;
    document.all.s_acpid.value="";
    document.all.tempAcpPerson.value="";
}

function DoaddLymc(){

window.open("deptBuildingAction.do?method=search4List&formName=yhpdispatchForm&addNum="+idcount+"&area="+document.all.s_xqid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
//document.all.s_xqid.value="";
//changeBd(document.all.s_xqid);
//document.all.s_rmid.style.display='';
//document.all.temproom.style.display='none';
}

function DoaddRoom(){

window.open("deptRoomAction.do?method=search4List&formName=yhpdispatchForm&addNum="+idcount+"&area="+document.all.s_xqid.value+"&building="+document.all.s_bdid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
//document.all.s_xqid.value="";
//changeBd(document.all.s_xqid);
//document.all.s_bdid.style.display='';
//document.all.tempbuilding.style.display='none';
}

function doSave(){

if(document.all.pfid.value!=''&&document.all.pfid.value!='2_geren'){
    if(document.all.rmid.value==''){
        alert("���ɷ������˱���ѡ���ɷ����ľ��巿�䣡");
        return;
    }    
}
if(document.all.pfid.value!=''&&document.all.pfid.value!='2_xianzhichu'){
   if(document.all.pfNum.value==''){
       alert("���ɷ������ô�������д�ɷ�������");
       return;
   }
}
if(doCheckForm(yhpdispatchForm)){

    var yNo=document.yhpdispatchForm.yhpNo.value;
    var ynum=document.yhpdispatchForm.yhpNum.value;
    var ocnum=document.yhpdispatchForm.ocurNum.value;
    var opfnum=document.yhpdispatchForm.opfNum.value;
    var opfid=document.yhpdispatchForm.opfid.value;
    var pfnum=document.yhpdispatchForm.pfNum.value;
     
    if(document.yhpdispatchForm.opfid.value!='2_xianzhichu'){
        var oocnum=parseInt(ocnum)+parseInt(opfnum);
        if(parseInt(oocnum)<parseInt(pfnum)){
            alert(yNo+" �ɷ����������׺�Ʒ�Ŀ��������");
            return;
        }                
    }
    
	yhpdispatchForm.action="yhpdispatchAction.do?method=update&idset="+idset+"&idcount="+idcount;
	yhpdispatchForm.submit();
}

}

function BchangeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.bs_bdid.length=1; //���ԭ¥���б�
   document.all.bs_rmid.length=1; //���ԭ�����б�        
      
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.all.bs_bdid.options[document.all.bs_bdid.length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.all.bs_bdid.options[document.all.bs_bdid.length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
      for (i=0;i < datacount2; i++)
      {
          document.all.bs_rmid.options[document.all.bs_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
    }
   

}

function BchangeRm(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.bs_rmid.length=1; //���ԭ�����б�        
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.all.bs_rmid.options[document.all.bs_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
      for (i=0;i < datacount; i++){
          if (dataset[i][0] == id){
             document.all.bs_xqid.value=dataset[i][2];
          }
      }
    }else{
       //alert("wl is null");
       for (i=0;i < datacount2; i++)
      {
          document.all.bs_rmid.options[document.all.bs_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function BchangeRoom(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   
   if(id!="")
      for (var i=0;i < datacount2; i++)
      {
         if (dataset2[i][0] == id)
          {                
             document.all.bs_bdid.value=dataset2[i][3];              
             for (var j=0;j< datacount;j++){
                 if (dataset[j][0] == document.all.bs_bdid.value){
                     document.all.bs_xqid.value=dataset[j][2];
                 }
             }
          }
      }
    
}

function BchangePfReason(sel){

     document.all.bpfReason.value=sel.value; 
     document.all.ifChanged.value="1";
}

function BchangeUsageCategory(sel){    
   
     document.all.busageCategory.value=sel.value;
     document.all.ifChanged.value="1";
}


function BchangePfUsage(sel){
       
    document.all.ifChanged.value="1";
}

function BchangePfid(sel){
    
    document.all.bpfid.value=sel.value; 
    document.all.ifChanged.value="1";
}

function BchangeXqid(sel){
   
    document.all.bxqid.value=sel.value;
     document.all.ifChanged.value="1";
}

function BchangeBdid(sel){
    
     document.all.bbdid.value=sel.value;
     document.all.ifChanged.value="1";
}

function BchangeRmid(sel){
     document.all.brmid.value=sel.value;
     document.all.ifChanged.value="1";
}

function BchangeNPlace(sel){
    
     document.all.ifChanged.value="1";
}

function BchangePfNum(sel){
   
    document.all.ifChanged.value="1";
}

function BchangeBeginNo(sel){
   
    document.all.ifChanged.value="1";
}

function BchangeEndNo(sel){
   
    document.all.ifChanged.value="1";
}

function BchangeAcpid(sel){
   
    document.all.bacpid.value=sel.value;
    document.all.ifChanged.value="1";
    document.all.bs_deptacpid.value="";
}

function BchangedeptAcpid(sel){
    document.all.bacpid.value=sel.value;
    document.all.bs_acpid.value="";
    document.all.btempAcpPerson.value="";
}

function BchangeMemo(sel){    
     document.all.ifChanged.value="1";
}

function BDoaddLymc(){

window.open("deptBuildingAction.do?method=search4List&formName=yhpdispatchForm&addNum="+idcount+"&area="+document.all.bs_xqid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
document.all.bs_xqid.value="";
BchangeBd(document.all.bs_xqid);
document.all.bs_rmid.style.display='';
document.all.btemproom.style.display='none';
}

function BDoaddRoom(){

window.open("deptRoomAction.do?method=search4List&formName=yhpdispatchForm&addNum="+idcount+"&area="+document.all.bs_xqid.value+"&building="+document.all.bs_bdid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
document.all.bs_xqid.value="";
BchangeBd(document.all.bs_xqid);
document.all.bs_bdid.style.display='';
document.all.btempbuilding.style.display='none';
}

function doBatchSave(){

if(document.all.ifChanged.value!='1'){
    alert("��û���޸��κ��ֶΡ�");
    return;
}

if(document.all.bpfid.value!=''&&document.all.bpfid.value!='2_geren'){
    if(document.all.brmid.value==''){
        alert("���ɷ������˱���ѡ���ɷ����ľ��巿�䣡");
        return;
    }    
}

if(document.all.bpfid.value!=''&&document.all.bpfid.value!='2_xianzhichu'){
   if(document.all.bpfNum.value==''){
       alert("���ɷ������ô�������д�ɷ�������");
       return;
   }
}

if(doCheckForm(yhpdispatchForm)){
    
	yhpdispatchForm.action="yhpdispatchAction.do?method=batchupdate&idset="+idset+"&idcount="+idcount;
	yhpdispatchForm.submit();
}

}

function DoBack(){   
   yhpdispatchForm.action="yhpdispatchAction.do?method=search4List";
   yhpdispatchForm.submit();
}
</script>
