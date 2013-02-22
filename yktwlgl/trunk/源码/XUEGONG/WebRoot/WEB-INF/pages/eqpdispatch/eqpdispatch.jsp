<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="java.util.List,java.util.Map" %>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>

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
       idsSet=(String[])request.getAttribute("ids");//读取设备号数组
   
   if(idsSet!=null){
     for(idsCount=0;idsCount<idsSet.length;idsCount++)
     {
     %>
      idset[<%=idsCount%>] = new Array("<%=idsSet[idsCount]%>");//产生javascript数组，对应小类id、小类名称、大类id
     <%
     }
   }
   %>
   idcount=<%=idsCount%>;
<%
	List list = (List)request.getAttribute("eqplist");
	String usageCategoryOld = "";
	String ManagerIdOld = "";
	String pfidOld="";
	String xqidOld="";
	String bdidOld="";
	String bdnameOld="";
	String rmidOld="";
	String rmnameOld="";
	String placeOld="";	
	String cbidOld="";	
	String cbnameOld="";	
	String blocOld="";
	String elocOld="";
	String eqpstateOld="";
	if(list!=null&&list.size()==1){
		Map map = (Map)list.get(0);
		usageCategoryOld = (String)map.get("ousageCategory");
		ManagerIdOld = (String)map.get("omanagerId");	
		request.setAttribute("usageCategoryOld",usageCategoryOld);
		request.setAttribute("ManagerIdOld",ManagerIdOld);
		
		pfidOld=(String)map.get("opfid");
		xqidOld=(String)map.get("oxqid");
		bdidOld=(String)map.get("obdid");
		bdnameOld=(String)map.get("obdname");
		rmidOld=(String)map.get("ormid");
		rmnameOld=(String)map.get("ormname");				
		placeOld=(String)map.get("oplace");
		cbidOld=(String)map.get("ocbid");
		cbnameOld=(String)map.get("ocbname");
		blocOld=(String)map.get("oblocation");
		elocOld=(String)map.get("oelocation");
		
		request.setAttribute("pfidOld",pfidOld);	
		request.setAttribute("xqidOld",xqidOld);
		request.setAttribute("bdidOld",bdidOld);
		request.setAttribute("bdnameOld",bdnameOld);
		request.setAttribute("rmidOld",rmidOld);
		request.setAttribute("rmnameOld",rmnameOld);
		request.setAttribute("placeOld",placeOld);
		request.setAttribute("cbidOld",cbidOld);
		request.setAttribute("cbnameOld",cbidOld);
		request.setAttribute("blocOld",blocOld);
		request.setAttribute("elocOld",elocOld);
		
		eqpstateOld=(String)map.get("oeqpstate");
		request.setAttribute("eqpstateOld",eqpstateOld);
	}
%>   
</script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>

		<html:form action="/gyf/eqpdispatchAction.do?method=dispatch" method="post">

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
												派发信息表
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
											<logic:present name="eqplist" scope="request">
												<jodd:form bean="request">
													<tr align="center" valign="middle">
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															<font color="red" style="font-weight:normal">*</font>&nbsp;派发原因
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<select name="s_pfReason" class="select01" onchange="changePfReason(this)">
																<option value="" checked>
																	请选择
																</option>
																<logic:present name="eqppfReasonlist" scope="request">
																	<logic:iterate name="eqppfReasonlist" id="pr" type="java.util.Map">
																		<option value="<bean:write name="pr" property="dictValue"/>">
																			<bean:write name="pr" property="dictCaption" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="pfReason" value="<%=request.getParameter("pfReason")==null||request.getParameter("pfReason").equals("null")?"":request.getParameter("pfReason")%>" title="派发原因" isMust='1'>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															用途大类
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_usageCategory" class="select01" onchange="changeUsageCategory(this)">
																			<option value="" checked>
																				请选择
																			</option>
																			<logic:present name="uclist" scope="request">
																				<logic:iterate name="uclist" id="uc" type="java.util.Map">
																					<option value="<bean:write name="uc" property="id"/>" <c:if test="${uc.id==usageCategoryOld}">selected</c:if>>
																						<bean:write name="uc" property="usageCategoryName" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="usageCategory" value="<%=request.getParameter("usageCategory")==null||request.getParameter("usageCategory").equals("null")?"":request.getParameter("usageCategory")%>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempUsageCategory" style="input_box" maxlength="50" value="<%=request.getParameter("tempUsageCategory")==null||request.getParameter("tempUsageCategory").equals("null")?"":request.getParameter("tempUsageCategory")%>"
																			readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addUsageCategory" type="button" value="查找"
																			onclick="javascript:window.open('deptUsageCategoryAction.do?method=search4List&formName=eqpdispatchForm&addNum='+idcount,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															用途说明
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<textarea name="pfUsage" cols=70 rows=2 maxLength="100" title="用途说明"></textarea>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															<font color="red" style="font-weight:normal">*</font>&nbsp;新派发对象
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_pfid" class="select01" onchange="changePfid(this)">
																<option value="" checked>
																	请选择
																</option>
																<logic:present name="pflist" scope="request">
																	<logic:iterate name="pflist" id="pfl" type="java.util.Map">
																		<option value="<bean:write name="pfl" property="dictValue"/>" <c:if test="${pfl.dictValue==pfidOld}">selected</c:if>>
																			<bean:write name="pfl" property="dictCaption" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="pfid" value="<%=pfidOld==null?"":pfidOld%>" title="新派发对象" isMust='1'>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															新校区
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_xqid" class="select01" onchange="changeBd(this);changeXqid(this)">
																<option value="" checked>
																	请选择
																</option>
																<logic:present name="arealist" scope="request">
																	<logic:iterate name="arealist" id="al" type="java.util.Map">
																		<option value="<bean:write name="al" property="dictValue"/>" <c:if test="${al.dictValue==xqidOld}">selected</c:if>>
																			<bean:write name="al" property="dictCaption" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="xqid" value="<%=xqidOld==null?"":xqidOld%>" >
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															新楼宇
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_bdid" class="select01" onchange="changeRm(this);changeBdid(this)">
																			<option value="" checked>
																				请选择
																			</option>
																			<logic:present name="buildinglist" scope="request">
																				<logic:iterate name="buildinglist" id="bdl" type="java.util.Map">
																					<option value="<bean:write name="bdl" property="id"/>" >
																						<bean:write name="bdl" property="lymc" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="bdid" value="<%=bdidOld==null?"":bdidOld%>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempbuilding" style="input_box" maxlength="50" value="<%=bdnameOld==null?"":bdnameOld%>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addBuilding" type="button" value="查找" onclick="DoaddLymc()">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															新房间
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_rmid" class="select01" onchange="changeRoom(this);changeRmid(this)">
																			<option value="" checked>
																				请选择
																			</option>
																			<logic:present name="roomlist" scope="request">
																				<logic:iterate name="roomlist" id="rml" type="java.util.Map">
																					<option value="<bean:write name="rml" property="id"/>" >
																						<bean:write name="rml" property="roommc" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="rmid" value="<%=rmidOld==null?"":rmidOld%>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="temproom" style="input_box" maxlength="50" value="<%=rmnameOld==null?"":rmnameOld%>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addRoom" type="button" value="查找" onclick="DoaddRoom()">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=middle>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															详细地点
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<textarea name="NPlace" cols=70 rows=2 maxLength="100" title="详细地点"><c:if test="${placeOld!=null&&placeOld!=''}"><%=placeOld%></c:if></textarea>
														</td>
													</tr>
													<tr align="center" valign=middle>
													    <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															机柜编号
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_cbid" class="select01" onchange="changeCbid(this)">
																			<option value="" checked>
																				请选择
																			</option>																			
																		</select>
																		<input type="hidden" name="cbid" value="<%=cbidOld==null?"":cbidOld%>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempcabinet" style="input_box" maxlength="50" value="<%=cbnameOld==null?"":cbnameOld%>" readonly="readonly" />
																	</td>																	
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addCabinet" type="button" value="查找" onclick="DoaddCabinet()">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															起始位置
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<input name="BLocation" style="input_box" maxlength="5" value="<c:if test="${blocOld!=null&&blocOld!=''}"><%=blocOld%></c:if>" title="起始位置" dataType="Int" />&nbsp;U
														</td>
												    </tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															终止位置
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<input name="ELocation" style="input_box" maxlength="5" value="<c:if test="${elocOld!=null&&elocOld!=''}"><%=elocOld%></c:if>" title="终止位置" dataType="Int" />&nbsp;U
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															上架经理人
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<select name="s_actid" class="select01" onchange="changeActid(this)">
																<option value="" checked>
																	请选择
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
															<input type="hidden" name="actid" value="<%=request.getParameter("actid")==null||request.getParameter("actid").equals("null")?"":request.getParameter("actid")%>">
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															设备状态
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_eqpstate" class="select01" onchange="changeEqpstate(this)">
																<option value="" checked>
																	请选择
																</option>
																<option value="3_zaiyong" <c:if test="${eqpstateOld=='3_zaiyong'}">selected</c:if>>在用</option>
																<option value="3_xianzhi" <c:if test="${eqpstateOld=='3_xianzhi'}">selected</c:if>>闲置</option>
															</select>
															<input type="hidden" name="NEqpState" value="<%=eqpstateOld==null?"":eqpstateOld%>">
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															<font color="red" style="font-weight:normal">*</font>&nbsp;新管理员
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_managerid" class="select01" onchange="changeManagerid(this)">
																<option value="" checked>
																	请选择
																</option>
																<logic:present name="mglist" scope="request">
																	<logic:iterate name="mglist" id="mgl" type="java.util.Map">
																		<option value="<bean:write name="mgl" property="code"/>" <c:if test="${mgl.code==ManagerIdOld}">selected</c:if>>
																			<bean:write name="mgl" property="personName" />
																			&nbsp;
																			<bean:write name="mgl" property="code" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="mgid" value="<%=request.getParameter("mgid")==null||request.getParameter("mgid").equals("null")?"":request.getParameter("mgid")%>">
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															接收人(内部)
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_deptacpid" class="select01" onchange="changedeptAcpid(this)">
																<option value="" checked>
																	请选择
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
															接收人(外部)
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_acpid" class="select01" onchange="changeAcpid(this)">
																			<option value="" checked>
																				请选择
																			</option>
																			<logic:present name="acplist" scope="request">
																				<logic:iterate name="acplist" id="acpl" type="java.util.Map">
																					<option value="<bean:write name="acpl" property="id"/>">
																						<bean:write name="acpl" property="personName" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="acpid" value="<%=request.getParameter("acpid")==null||request.getParameter("acpid").equals("null")?"":request.getParameter("acpid")%>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempAcpPerson" style="input_box" maxlength="50" value="<%=request.getParameter("tempAcpPerson")==null||request.getParameter("tempAcpPerson").equals("null")?"":request.getParameter("tempAcpPerson")%>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addAcpPerson" type="button" value="查找"
																			onclick="javascript:window.open('deptOtherPersonAction.do?method=search4List&formName=eqpdispatchForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															备注
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<textarea name="memo" cols=70 rows=2 maxLength="300" title="备注"></textarea>
														</td>
													</tr>
												</jodd:form>
												<logic:iterate name="eqplist" id="ebl" type="java.util.Map" indexId="i">
													<c:if test="${ebl.assetNo==null||ebl.assetNo==''}">
													<input type="text" name="equipmentNo_<bean:write name="ebl" property="equipmentNo"/>" value="<bean:write name="ebl" property="equipmentNo"/>" readonly="readonly">
													<input type="hidden" name="<bean:write name="ebl" property="equipmentNo"/>old_assetNo" value="<bean:write name="ebl" property="assetNo"/>" readonly="readonly">								
													</c:if>
													<c:if test="${ebl.assetNo!=null&&ebl.assetNo!=''}">
													<input type="hidden" name="equipmentNo_<bean:write name="ebl" property="equipmentNo"/>" value="<bean:write name="ebl" property="equipmentNo"/>" readonly="readonly">
													<input type="text" name="<bean:write name="ebl" property="equipmentNo"/>old_assetNo" value="<bean:write name="ebl" property="assetNo"/>" readonly="readonly">								
													</c:if>														
													<input type="hidden" name="<bean:write name="ebl" property="equipmentNo"/>ousageCategory" value="<bean:write name="ebl" property="ousageCategory"/>">
													<input type="hidden" name="<bean:write name="ebl" property="equipmentNo"/>omanagerId" value="<bean:write name="ebl" property="omanagerId"/>">
													<input type="hidden" name="<bean:write name="ebl" property="equipmentNo"/>opfid" value="<bean:write name="ebl" property="opfid"/>">
													<input type="hidden" name="<bean:write name="ebl" property="equipmentNo"/>oxqid" value="<bean:write name="ebl" property="oxqid"/>">
													<input type="hidden" name="<bean:write name="ebl" property="equipmentNo"/>obdid" value="<bean:write name="ebl" property="obdid"/>">
													<input type="hidden" name="<bean:write name="ebl" property="equipmentNo"/>ormid" value="<bean:write name="ebl" property="ormid"/>">
												</logic:iterate>
											</logic:present>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="30" align="right" valign="middle">
									<input name="Submit10" type="button" class="button_nor" value="保存" onclick="doSave();">
									&nbsp;
									<input name="Submit12" type="button" class="button_nor" value="返 回" onClick="DoBack()">
								</td>
							</tr>
						</table>
						<logic:present name="msg" scope="request">
							<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
						</logic:present>
						<logic:notPresent name="msg" scope="request">
							<input name="hmsg" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="ncdispatch" scope="request">
							<input name="hncdispatch" type="hidden" value="<bean:write name="ncdispatch" />">
						</logic:present>
						<logic:notPresent name="ncdispatch" scope="request">
							<input name="hncdispatch" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="ncManager" scope="request">
							<input name="hncManager" type="hidden" value="<bean:write name="ncManager" />">
						</logic:present>
						<logic:notPresent name="ncManager" scope="request">
							<input name="hncManager" type="hidden" value="">
						</logic:notPresent>
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
       resultset=(String[][])request.getAttribute("ablist");//读取校区、楼宇对应数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//产生javascript二维数组，对应楼宇id、楼宇名称、校区id
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
       resultset2=(String[][])request.getAttribute("bmlist");//读取楼宇、房间对应数据
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>","<%=resultset2[count2][3]%>");//产生javascript二维数组，对应房间id、房间名称、房间标识、楼宇id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<script>

    var datacount3=0;
    dataset3=new Array();
    
   <%
   int count3=0;
   String[][] resultset3=null;
   if(request.getAttribute("rclist")!=null)
       resultset3=(String[][])request.getAttribute("rclist");//读取房间、机柜对应数据
   
   if(resultset3!=null){
     for(count3=0;count3<resultset3.length;count3++)
     {
     %>
      dataset3[<%=count3%>] = new Array("<%=resultset3[count3][0]%>","<%=resultset3[count3][1]%>","<%=resultset3[count3][2]%>");//产生javascript二维数组，对应机柜id、机柜名称、房间id
     <%
     }
   }
   %>
   datacount3=<%=count3%>;
   
</script>


<script type="text/javascript">

setTimeout('DoInit()',10);

function DoInit(){

   var xq,bd,rm,cb;
     
     xq=document.all.xqid.value;
     bd=document.all.bdid.value;
     rm=document.all.rmid.value;
     cb=document.all.cbid.value;
          
     var hasbd=false;
     var hasrm=false;  
     var hascb=false;  
          
     if(xq!='')
      changeBd(document.all.s_xqid);
      for(var j=0;j<document.all.s_bdid.length;j++){
      if(document.all.s_bdid[j].value==bd){
	     document.all.s_bdid[j].selected=true;
	     hasbd=true;
	  }
	  }
	  
	  if(hasbd){
	      document.all.s_bdid.style.display='';
	      document.all.tempbuilding.style.display='none';	  
	  }
	  else{
	      document.all.s_bdid.style.display='none';
	      document.all.tempbuilding.style.display='';	  
	  }		
   
   if(bd!='')
        changeRm(document.all.s_bdid);
   for(var j=0;j<document.all.s_rmid.length;j++){
      if(document.all.s_rmid[j].value==rm){
	     document.all.s_rmid[j].selected=true;
	     hasrm=true;
	  }
   }
   
   if(hasrm){
	      document.all.s_rmid.style.display='';
	      document.all.temproom.style.display='none';	  
	  }
	else{
	      document.all.s_rmid.style.display='none';
	      document.all.temproom.style.display='';	  
	}
	
	if(rm!='')
	    changeRoom(document.all.s_rmid);
	for(var j=0;j<document.all.s_cbid.length;j++){
      if(document.all.s_cbid[j].value==cb){
	     document.all.s_cbid[j].selected=true;
	     hascb=true;
	  }
   }
   if(hascb){
	      document.all.s_cbid.style.display='';
	      document.all.tempcabinet.style.display='none';	  
   }
	else{
	     document.all.s_cbid.style.display='none';
	     document.all.tempcabinet.style.display='';	  
	}
	
	
   var uc;
   var hasuc=false;
   
   uc=document.all.usageCategory.value;
   for(var i=0;i<document.all.s_usageCategory.length;i++){//用途大类
       if(document.all.s_usageCategory[i].value==uc){
           hasuc=true;
       }
   }
   
   if(hasuc){
       document.all.s_usageCategory.style.display='';
       document.all.tempUsageCategory.style.display='none';
   }
   else{
       document.all.s_usageCategory.style.display='none';
       document.all.tempUsageCategory.style.display='';   
   }
   
   var acp;
   var hasacp=false;
   
   acp=document.all.acpid.value;
   for(var i=0;i<document.all.s_acpid.length;i++){//外部人员
       if(document.all.s_acpid[i].value==acp){
           hasacp=true;
       }
   }
   
   if(hasacp){
       document.all.s_acpid.style.display='';
       document.all.tempAcpPerson.style.display='none';
   }
   else{
       document.all.s_acpid.style.display='none';
       document.all.tempAcpPerson.style.display='';   
   }     
      
   if(document.all.hmsg.value=='1')
       alert("保存成功！");
   else if(document.all.hmsg.value=='0')
       alert("保存失败！");
   if(document.all.hncdispatch.value!='')
       alert(document.all.hncdispatch.value+" 派发审核尚未结束，暂时不能重新派发！");
   if(document.all.hncManager.value!='')
       alert(document.all.hncManager.value+" 管理员字段在审核中，不能修改！");
}

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.s_bdid.length=1; //清空原楼宇列表
   document.all.s_rmid.length=1; //清空原房间列表        
      
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
        
   document.all.s_rmid.length=1; //清空原房间列表        
   
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
   document.all.s_cbid.length=1; //清空原机柜列表
   
   if(id!=""){
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
      for(var i=0;i<datacount3;i++){
          if (dataset3[i][2] == id)
          {   
             document.all.s_cbid.options[document.all.s_cbid.length]=new Option(dataset3[i][1], dataset3[i][0]); 
                  
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

function changeManagerid(sel){
    document.all.mgid.value=sel.value;
}

function changeEqpstate(sel){
    document.all.NEqpState.value=sel.value;
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

function changeCbid(sel){
    document.all.cbid.value=sel.value;
}

function changeActid(sel){
    document.all.actid.value=sel.value;
}

function DoaddCabinet(){

window.open("deptCabinetAction.do?method=search4List&formName=eqpdispatchForm&addNum="+idcount+"&area="+document.all.s_xqid.value+"&building="+document.all.s_bdid.value+"&room="+document.all.s_rmid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
}

function DoaddLymc(){

window.open("deptBuildingAction.do?method=search4List&formName=eqpdispatchForm&addNum="+idcount+"&area="+document.all.s_xqid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
//document.all.s_xqid.value="";
//changeBd(document.all.s_xqid);

}

function DoaddRoom(){

window.open("deptRoomAction.do?method=search4List&formName=eqpdispatchForm&addNum="+idcount+"&area="+document.all.s_xqid.value+"&building="+document.all.s_bdid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
//document.all.s_xqid.value="";
//changeBd(document.all.s_xqid);

}

function doSave(){

if(document.all.pfid.value!=''&&document.all.pfid.value!='2_geren'){
    if(document.all.rmid.value==''){
        alert("非派发给个人必须选择派发到的具体房间！");
        return;
    }    
}

if(doCheckForm(eqpdispatchForm)){
	eqpdispatchForm.action="eqpdispatchAction.do?method=dispatch&idset="+idset+"&idcount="+idcount;
	eqpdispatchForm.submit();
}

}

function DoBack(){   
   eqpdispatchForm.action="eqpdispatchAction.do?method=search4List&listNum='all'";
   eqpdispatchForm.submit();
}
</script>
