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

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/eqpdispatchAction.do?method=search4ApplyList" method="post">

			<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
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
												�豸�ɷ�����
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
											<tr align="center" valign=center>
												<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													�豸���
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_bh" styleClass="input_box" maxlength="32" />
												</td>
												<td width="20%" lign="left" valign="middle" class="tableHeader2">
													�豸�ʲ���
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_zch" styleClass="input_box" maxlength="50" />
												</td>
												<td width="15%" align="left" valign="middle" class="tableHeader2">
													�豸���к�
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_xlh" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													����У��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_xq" styleClass="select01" onchange="changeOBd(this)">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													����¥��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_louyu" styleClass="select01">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													���ڷ���
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_jfkf" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													������
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_jgbh" styleClass="input_box" maxlength="50" />
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													��ʼλ��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_blocation" styleClass="input_box" maxlength="10" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													��ֹλ��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_elocation" styleClass="input_box" maxlength="10" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													������
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_sqr" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													�������ڴ�
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_sqrqc" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_sqrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��ʼ����" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td align="right" valign="middle" class="tableHeader2">
													�������ڵ�
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_sqrqd" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_sqrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��������" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
											</tr>
											<script type="text/javascript">
                new calendar("search_sqrqc", "select_sqrqc", "%Y-%m-%d");
                new calendar("search_sqrqd", "select_sqrqd", "%Y-%m-%d");
           </script>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													�ɷ�����״̬
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_sqzt" styleClass="select01">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="sqztlist" labelProperty="ztName" property="ztCode" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													�ɷ���������
												</td>
												<td align="left" valign="middle" class="tableHeader3" colspan="3">
													<html:select property="search_applyname" styleClass="select01">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="appNamelist" labelProperty="applyName" property="applyName" />
													</html:select>
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">
									<input name="Submit" type="submit" class="button_nor" value="�� ѯ">
									&nbsp;
									<input name="Submit2" type="button" class="button_nor" value="�� ��" onclick="DoClear()">
								</td>

							</tr>
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
							</html:form>

							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									�豸�ɷ������б�
								</td>
							</tr>
							<tr>
								<td height="20" align="center" valign="middle">
									<ec:table items="eqplist" var="eqpJBInfo" autoIncludeParameters="false" rowsDisplayed="10" action="eqpdispatchAction.do?method=search4ApplyList">

										<ec:parameter name="search_bh" />
										<ec:parameter name="search_zch" />
										<ec:parameter name="search_xlh" />
										<ec:parameter name="search_xq" />
										<ec:parameter name="search_louyu" />
										<ec:parameter name="search_jfkf" />
										<ec:parameter name="search_jgbh" />
										<ec:parameter name="search_blocation" />
										<ec:parameter name="search_elocation" />
										<ec:parameter name="search_sqr" />
										<ec:parameter name="search_sqrqc" />
										<ec:parameter name="search_sqrqd" />
										<ec:parameter name="search_applyname" />
										<ec:parameter name="search_sqzt" />

										<ec:exportXls fileName="eqpdispatchApplyList.xls" tooltip="���� Excel" />
										<ec:row>
											<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
												<input type="checkbox" name="cbgroup" value="${eqpJBInfo.id}" style="border:0px" onClick="doSel(this)" />
											</ec:column>
											<ec:column property="equipmentNo" title="�豸��ʶ" headerStyle="text-align:center" style="text-align: left" width="80">
														
																						
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')">${eqpJBInfo.equipmentNo}</a>
												</c:if>
												<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')">${eqpJBInfo.assetNo}</a>
												</c:if>
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'}">
							<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="#000000">${eqpJBInfo.equipmentNo}</font></a>
												</c:if>
												<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="#000000">${eqpJBInfo.assetNo}</font></a>
												</c:if>	&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="green">${eqpJBInfo.equipmentNo}</font></a>
												</c:if>
												<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="green">${eqpJBInfo.assetNo}</font></a>
												</c:if>	&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="red">${eqpJBInfo.equipmentNo}</font></a>
												</c:if>
												<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="red">${eqpJBInfo.assetNo}</font></a>
												</c:if>	&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������'}">
							<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="#000000">${eqpJBInfo.equipmentNo}</font></a>
												</c:if>
												<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="#000000">${eqpJBInfo.assetNo}</font></a>
												</c:if>	&nbsp;
					</c:when>
					</c:choose>
					</ec:column>																				
											<ec:column property="managerName" title="����Ա" headerStyle="text-align:center" style="text-align: left" width="50" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.managerName}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.managerName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.managerName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.managerName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.managerName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="applyName" title="�ɷ�����" headerStyle="text-align:center" style="text-align: left" width="80" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.applyName}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.applyName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.applyName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.applyName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.applyName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="collegeArea" title="У��" headerStyle="text-align:center" style="text-align: left" width="60" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.collegeArea}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.collegeArea}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.collegeArea}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.collegeArea}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.collegeArea}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="lymc" title="¥��" headerStyle="text-align:center" style="text-align: left" width="50" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.lymc}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.lymc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.lymc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.lymc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.lymc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="roommc" title="����" headerStyle="text-align:center" style="text-align: left" width="60" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.roommc}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.roommc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.roommc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.roommc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.roommc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="cabinetmc" title="���" headerStyle="text-align:center" style="text-align: left" width="40" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.cabinetmc}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.cabinetmc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.cabinetmc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.cabinetmc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.cabinetmc}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="BLocation" title="��U" headerStyle="text-align:center" style="text-align: left" width="40" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.BLocation}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.BLocation}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.BLocation}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.BLocation}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.BLocation}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="ELocation" title="��U" headerStyle="text-align:center" style="text-align: left" width="40" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.ELocation}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.ELocation}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.ELocation}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.ELocation}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.ELocation}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="applyStateName" title="״̬" headerStyle="text-align:center" style="text-align: left" width="50" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.applyStateName}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.applyStateName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.applyStateName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.applyStateName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.applyStateName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="applyPersonName" title="������" headerStyle="text-align:center" style="text-align: left" width="50" >
												<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							${eqpJBInfo.applyPersonName}&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000">${eqpJBInfo.applyPersonName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green">${eqpJBInfo.applyPersonName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red">${eqpJBInfo.applyPersonName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000">${eqpJBInfo.applyPersonName}</font>&nbsp;
					</c:when>
					</c:choose>
					
					</ec:column>
											<ec:column property="recordDate" title="��������"  headerStyle="text-align:center" style="text-align: left" width="70" >
																													<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='δ�ύ'}">
							<bean:write name="eqpJBInfo" property="recordDate" format="yyyy-MM-dd"/>&nbsp;
					</c:when>
					</c:choose>
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='���ύ'||eqpJBInfo.applyStateName=='������'}">
							<font color="#000000"><bean:write name="eqpJBInfo" property="recordDate" format="yyyy-MM-dd"/></font>&nbsp;
					</c:when>
					</c:choose>
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='����ͨ��'||eqpJBInfo.applyStateName=='������'}">
							<font color="green"><bean:write name="eqpJBInfo" property="recordDate" format="yyyy-MM-dd"/></font>&nbsp;
					</c:when>
					</c:choose>
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='������ͨ��'}">
							<font color="red"><bean:write name="eqpJBInfo" property="recordDate" format="yyyy-MM-dd"/></font>&nbsp;
					</c:when>
					</c:choose>
					
					<c:choose>
						<c:when test="${eqpJBInfo.applyStateName=='�����'}">
							<font color="#000000"><bean:write name="eqpJBInfo" property="recordDate" format="yyyy-MM-dd"/></font>&nbsp;
					</c:when>
					</c:choose>
					</ec:column>											
											
										</ec:row>
									</ec:table>
								</td>
							</tr>
							<%if (((java.util.ArrayList) request.getAttribute("eqplist")).size() > 0) {%>
							<tr>
								<td height="40" align="left" valign="middle">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<tbody>
											<tr align="center" valign=center>
												<td height="40" align="left" valign="middle">
													<input name="selectall" type="button" class="button_nor" value="ȫ ѡ" onClick="DoSelectall()">
													<input name="notselectall" type="button" class="button_nor" value="ȫ��ѡ" onClick="DoNotselectall()">
													<input name="reverseselect" type="button" class="button_nor" value="�� ѡ" onClick="DoReverseselect()">
												</td>
												<td height="40" align="right" valign="middle">
													<input name="bupdate" type="button" class="button_nor" value="�� ��" onClick="DoUpdate()">
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<%}%>
						</table>
					</td>
				</tr>
			</table>
	</body>
</html>

<script>

    var datacount2=0;
    dataset2=new Array();
    
   <%
   int count2=0;
   String[][] resultset2=null;
   if(request.getAttribute("ablist")!=null)
       resultset2=(String[][])request.getAttribute("ablist");//��ȡУ����¥���Ӧ����
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>");//����javascript��ά���飬��Ӧ¥��id��¥�����ơ�У��id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<SCRIPT language=javascript>

setTimeout('init()',10);
function init(){
   
  var area=document.eqpdispatchForm.elements["search_xq"].value;
  var building=document.eqpdispatchForm.elements["search_louyu"].value;
  
  if(area!='')
      changeBd(document.eqpdispatchForm.elements["search_xq"]);
  for(var j=0;j<document.eqpdispatchForm.elements["search_louyu"].length;j++){
      if(document.eqpdispatchForm.elements["search_louyu"][j].value==building)
	     document.eqpdispatchForm.elements["search_louyu"][j].selected=true;
					
  }
  if(document.all.hncupdate.value!=''&&!isNaN(document.all.hncupdate.value)){
       alert("�޸�"+document.all.hncupdate.value+"���ɷ����룡���ɷ�����������л������ͨ���������޸ģ�");
   }
    
}  

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpdispatchForm.elements["search_louyu"].length=1; //���ԭ¥���б�        
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][2] == id)
          {   
             document.eqpdispatchForm.elements["search_louyu"].options[document.eqpdispatchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount2; i++)
      {
          document.eqpdispatchForm.elements["search_louyu"].options[document.eqpdispatchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function zchSetup(sel){

   alert(sel.value);

}
function doSel(sel){
//alert(sel.value);
}

function DoSelectall(){

  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=true;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}

function DoNotselectall(){
  
  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=false;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }

}

function DoReverseselect(){
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
           if(document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=false;
           else if(!document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
      if(document.all.cbgroup.checked)
          document.all.cbgroup.checked=false; 
      else if(!document.all.cbgroup.checked)
          document.all.cbgroup.checked=true;    
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}

function DoUpdate(){
 
   var sflag=0;
   var ids="";
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1; 
                   ids=ids+document.all.cbgroup[i].value+",";                                                 
              }
          }           
         if(sflag==0){
              alert("��ѡ��Ҫ�޸ĵ��豸�ɷ����룡");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              ids=ids+document.all.cbgroup.value+","; 
              sflag=sflag+1;     
        }
        else{
            alert("��ѡ��Ҫ�޸ĵ��豸�ɷ����룡");
            return;   
        }            
   }
   
   document.forms.ec.action="eqpdispatchAction.do?method=load4Applyupdate&idset="+ids.substring(0,ids.length-1)+"&idcount="+sflag;     
   document.forms.ec.submit();
   
  
  
}

function DoView(eno){

    window.open("eqpdispatchAction.do?method=load4Applyview&applyId="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoViewDispatch(eno){

    window.open("eqpdispatchAction.do?method=load4view&dispatchId="+eno,"dispatchInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoClear(){

    document.eqpdispatchForm.elements["search_bh"].value="";
    document.eqpdispatchForm.elements["search_zch"].value="";    
    document.eqpdispatchForm.elements["search_xlh"].value="";
    
    document.eqpdispatchForm.elements["search_jfkf"].value="";
    document.eqpdispatchForm.elements["search_xq"].value="";
    document.eqpdispatchForm.elements["search_louyu"].value="";
    
    document.eqpdispatchForm.elements["search_jgbh"].value="";
    document.eqpdispatchForm.elements["search_blocation"].value="";
    document.eqpdispatchForm.elements["search_elocation"].value="";
    
    document.eqpdispatchForm.elements["search_applyname"].value="";   
    document.eqpdispatchForm.elements["search_sqzt"].value="";
    
    document.eqpdispatchForm.elements["search_sqr"].value="";
    document.eqpdispatchForm.elements["search_sqrqc"].value="";
    document.eqpdispatchForm.elements["search_sqrqd"].value="";
            
}

</SCRIPT>

