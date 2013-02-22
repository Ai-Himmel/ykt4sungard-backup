<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
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
       idsSet=(String[])request.getAttribute("ids");//读取设备派发申请id数组
   
   if(idsSet!=null){
     for(idsCount=0;idsCount<idsSet.length;idsCount++)
     {
     %>
      idset[<%=idsCount%>] = new Array("<%=idsSet[idsCount]%>");//产生javascript数组
     <%
     }
   }
   %>
   idcount=<%=idsCount%>;
</script>
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
												派发申请表
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
											<logic:present name="eqplist" scope="request">
												<logic:iterate name="eqplist" id="el" type="java.util.Map" indexId="i">
													<tr align="center" valign="middle">
														<td width="15%" align="right" valign="middle" class="tableHeader2">
															设备编号
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="equipmentNo" />
															<input type="hidden" name="applyId" value="<bean:write name="el" property="id"/>" />
														</td>
														<td width="15%" align="right" valign="middle" class="tableHeader2">
															资产号
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="assetNo" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															设备名称
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="wlmc" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															派发申请名称
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="applyName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															校区
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="collegeArea" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															楼宇
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="lymc" />
														</td>
													</tr>
													<input type="hidden" name="collegeid" value="<bean:write name="el" property="collegeid"/>">
													<input type="hidden" name="lyid" value="<bean:write name="el" property="lyid"/>">
													<input type="hidden" name="roomid" value="<bean:write name="el" property="roomid"/>">
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															房间
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="roommc" />
														</td>
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
																			<logic:present name="cabinetlist" scope="request">
																				<logic:iterate name="cabinetlist" id="cbl" type="java.util.Map">
																					<option value="<bean:write name="cbl" property="id"/>">
																						<bean:write name="cbl" property="cabinetmc" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="cbid" value="<bean:write name="el" property="cabinetid"/>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<c:choose>
																			<c:when test="${el.cabinetmc!=null}">
																				<input name="tempcabinet" style="input_box" maxlength="50" value="<bean:write name="el" property="cabinetmc"/>" readonly="readonly" />
																			</c:when>
																			<c:otherwise>
																				<input name="tempcabinet" style="input_box" maxlength="50" value="" readonly="readonly" />
																			</c:otherwise>
																		</c:choose>
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
															<input name="BLocation" style="input_box" maxlength="5" value="<bean:write name="el" property="BLocation"/>" title="起始位置" dataType="Int" />&nbsp;U
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															终止位置
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<input name="ELocation" style="input_box" maxlength="5" value="<bean:write name="el" property="ELocation"/>" title="终止位置" dataType="Int" />&nbsp;U
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
															<input type="hidden" name="actid" value="<bean:write name="el" property="actPersonId"/>">
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															备注
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<textarea name="memo" cols=70 rows=2 maxLength="300"><bean:write name="el" property="memo" /></textarea>
														</td>
													</tr>
												</logic:iterate>
											</logic:present>
											<logic:present name="eqpbatchlist" scope="request">
												<tr align="center" valign="middle">
													<td width="15%" align="right" valign="middle" class="tableHeader2">
														设备编号
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														---
													</td>
													<td width="15%" align="right" valign="middle" class="tableHeader2">
														资产号
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														---
													</td>
												</tr>
												<tr align="center" valign="middle">
													<td width="15%" align="right" valign="middle" class="tableHeader2">
														设备名称
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														---
													</td>
													<td width="15%" align="right" valign="middle" class="tableHeader2">
														派发申请名称
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														---
													</td>
												</tr>
												<tr align="center" valign="middle">
													<td width="15%" align="right" valign="middle" class="tableHeader2">
														校区
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														---
													</td>
													<td width="15%" align="right" valign="middle" class="tableHeader2">
														楼宇
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														---
													</td>
												</tr>
												<tr align="center" valign="middle">
													<td width="15%" align="right" valign="middle" class="tableHeader2">
														房间
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														---
													</td>
													<td width="15%" align="right" valign="middle" class="tableHeader2">
														机柜编号
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<table border="0" cellspacing="0" cellpadding="0">
															<tr align="center" valign="middle">
																<td width="35">
																	<select name="bs_cbid" class="select01" onchange="BchangeCbid(this)">
																		<option value="" checked>
																			请选择
																		</option>
																		<logic:present name="cabinetlist" scope="request">
																			<logic:iterate name="cabinetlist" id="cbl" type="java.util.Map">
																				<option value="<bean:write name="cbl" property="id"/>">
																					<bean:write name="cbl" property="cabinetmc" />
																				</option>
																			</logic:iterate>
																		</logic:present>
																	</select>
																	<input type="hidden" name="bcbid" value="<%=request.getParameter("bcbid")==null||request.getParameter("bcbid").equals("null")?"":request.getParameter("bcbid")%>">
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="40" align="right">
																	<input name="btempcabinet" style="input_box" maxlength="50" value="<%=request.getParameter("btempcabinet")==null||request.getParameter("btempcabinet").equals("null")?"":request.getParameter("btempcabinet")%>" readonly="readonly" />
																</td>
																<td width="20">
																	&nbsp;
																</td>
																<td width="20" align="right">
																	<input name="addCabinet" type="button" value="查找"
																		onclick="javascript:window.open('deptCabinetAction.do?method=search4List&formName=eqpdispatchForm&addNum='+idcount,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
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
														<input name="bBLocation" style="input_box" maxlength="50" value="<%=request.getParameter("bBLocation")==null||request.getParameter("bBLocation").equals("null")?"":request.getParameter("bBLocation")%>" onchange="BchangeBLocation(this)"
															title="起始位置" dataType="Int" />&nbsp;U
													</td>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														终止位置
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<input name="bELocation" style="input_box" maxlength="50" value="<%=request.getParameter("bELocation")==null||request.getParameter("bELocation").equals("null")?"":request.getParameter("bELocation")%>" onchange="BchangeELocation(this)"
															title="终止位置" dataType="Int" />&nbsp;U
													</td>
												</tr>
												<tr align="center" valign="middle">
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														上架经理人
													</td>
													<td align="left" valign="middle" class="tableHeader3" colspan="3">
														<select name="bs_actid" class="select01" onchange="BchangeActid(this)">
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
														<input type="hidden" name="bactid" value="<%=request.getParameter("bactid")==null||request.getParameter("bactid").equals("null")?"":request.getParameter("bactid")%>">
													</td>
												</tr>
												<tr align="center" valign=center>
													<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
														备注
													</td>
													<td align="left" valign="middle" class="tableHeader3" colspan="3">
														<textarea name="bmemo" cols=70 rows=2 maxLength="300" onchange="BchangeMemo(this)"></textarea>
													</td>
												</tr>
												<logic:iterate name="eqpbatchlist" id="ebl" type="java.util.Map" indexId="i">
													<input type="hidden" name="applyId_<bean:write name="ebl" property="id"/>" value="<bean:write name="ebl" property="id"/>" />
												</logic:iterate>
											</logic:present>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="30" align="right" valign="middle">
									<%if (idsCount == 1) {%>
									<input name="Submit11" type="button" class="button_nor" value="保 存" onclick="doSave();">
									<%} else if (idsCount > 1) {%>
									<input name="Submit10" type="button" class="button_nor" value="批量保存" onclick="doBatchSave();">
									<%}%>
									&nbsp;
									<input name="Submit12" type="button" class="button_nor" value="返 回" onClick="DoBack()">
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
													审批结果
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
															审批层级
														</td>
														<td valign="middle" class="tableHeader">
															审批人
														</td>
														<td valign="middle" class="tableHeader">
															审批结果
														</td>
														<td valign="middle" class="tableHeader">
															审批备注
														</td>
														<td valign="middle" class="tableHeader">
															审批日期
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
						<logic:present name="nccols" scope="request">
							<input name="hnccols" type="hidden" value="<bean:write name="nccols" />">
						</logic:present>
						<logic:notPresent name="nccols" scope="request">
							<input name="hnccols" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="nsameloc" scope="request">
							<input name="hnsameloc" type="hidden" value="<bean:write name="nsameloc" />">
						</logic:present>
						<logic:notPresent name="nsameloc" scope="request">
							<input name="hnsameloc" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="nmHeight" scope="request">
							<input name="hnmHeight" type="hidden" value="<bean:write name="nmHeight" />">
						</logic:present>
						<logic:notPresent name="nmHeight" scope="request">
							<input name="hnmHeight" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="nmRoom" scope="request">
							<input name="hnmRoom" type="hidden" value="<bean:write name="nmRoom" />">
						</logic:present>
						<logic:notPresent name="nmRoom" scope="request">
							<input name="hnmRoom" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="ncupdate" scope="request">
							<input name="hncupdate" type="hidden" value="<bean:write name="ncupdate" />">
						</logic:present>
						<logic:notPresent name="ncupdate" scope="request">
							<input name="hncupdate" type="hidden" value="">
						</logic:notPresent>

						<jodd:form bean="request">
							<input type="hidden" name="ec_i" />
							<input type="hidden" name="ec_p" />
							<input type="hidden" name="ec_crd" />
							<input type="hidden" name="search_bh" />
							<input type="hidden" name="search_zch" />
							<input type="hidden" name="search_xlh" />
							<input type="hidden" name="search_xq" />
							<input type="hidden" name="search_louyu" />
							<input type="hidden" name="search_jfkf" />
							<input type="hidden" name="search_jgbh" />
							<input type="hidden" name="search_blocation" />
							<input type="hidden" name="search_elocation" />
							<input type="hidden" name="search_sqr" />
							<input type="hidden" name="search_sqrqc" />
							<input type="hidden" name="search_sqrqd" />
							<input type="hidden" name="search_applyname" />
							<input type="hidden" name="search_sqzt" />
						</jodd:form>
						</html:form>
	</body>
</html>

<script type="text/javascript">

if(idcount==1)
   setTimeout('DoInit()',10);
else if(idcount>1)
   setTimeout('DoBatchInit()',10);
   
function DoInit(){
  var cb,act;
  var hascb=false;
     cb=document.eqpdispatchForm.elements["cbid"].value;
     act=document.eqpdispatchForm.elements["actid"].value;
     
   for(var i=0;i<document.eqpdispatchForm.elements["s_cbid"].length;i++){//机柜
       if(document.eqpdispatchForm.elements["s_cbid"][i].value==cb){
            document.eqpdispatchForm.elements["s_cbid"][i].selected=true;
            hascb=true;
       }
   }
   if(hascb){
	      document.eqpdispatchForm.elements["s_cbid"].style.display='';
	      document.eqpdispatchForm.elements["tempcabinet"].style.display='none';	  
   }
	else{
	     document.eqpdispatchForm.elements["s_cbid"].style.display='none';
	     document.eqpdispatchForm.elements["tempcabinet"].style.display='';	  
	}
   	
    for(var i=0;i<document.eqpdispatchForm.elements["s_actid"].length;i++){//上架人
       if(document.eqpdispatchForm.elements["s_actid"][i].value==act)
            document.eqpdispatchForm.elements["s_actid"][i].selected=true;
   }   
   
   if(document.all.hmsg.value=='1')
       alert("保存成功！");
   else if(document.all.hmsg.value=='0')
       alert("保存失败！");  
   else if(document.all.hmsg.value=='7')
       alert("机柜起止位置差不能小于设备高度,保存失败！"); 
   else if(document.all.hmsg.value=='8')
       alert("派发申请在审核中或已审核通过，不能修改！");
   if(document.all.hnsameloc.value!='')
       alert("已有其它设备放在该起始位置！");
   if(document.all.hnmRoom.value!='')
       alert("机柜所属房间与派发记录相关内容不符,请检查！");  
   if(document.all.hncupdate.value!=''){
       alert("修改"+document.all.hncupdate.value+"条派发申请！若派发申请在审核中或已审核通过，不能修改！");       
   }
}

function DoBatchInit(){

   var cb;
   var hascb=false;
   cb=document.all.bs_cbid.value;
   
   for(var i=0;i<document.all.bs_cbid.length;i++){//机柜
       if(document.all.bs_cbid[i].value==cb){
            document.all.bs_cbid[i].selected=true;
            hascb=true;
       }
   }
   
   if(hascb){
	      document.all.bs_cbid.style.display='';
	      document.all.btempcabinet.style.display='none';	  
	}
	  else{
	      document.all.bs_cbid.style.display='none';
	      document.all.btempcabinet.style.display='';	  
	}
   
    
   if(document.all.hmsg.value=='1')
       alert("保存成功！");
   else if(document.all.hmsg.value=='0')
       alert("保存失败！");
   if(document.all.hnccols.value!='')
       alert(document.all.hnccols.value+" 派发申请在审核中或已审核完毕，不能修改！");
   if(document.all.hnmHeight.value!='')
       alert(document.all.hnmHeight.value+" 机柜起止位置差不能小于设备高度,保存失败！");
   if(document.all.hnmRoom.value!='')
       alert(document.all.hnmRoom.value+" 机柜所属房间与派发记录相关内容不符,请检查！");
   if(document.all.hncupdate.value!=''){
       alert("修改"+document.all.hncupdate.value+"条派发记录！");
       alert("一个设备只能修改最新的派发记录，若派发申请在审核中或已审核结束，不能修改！");
   }
}

function changeCbid(sel){
    document.all.cbid.value=sel.value;
}

function changeActid(sel){
    document.all.actid.value=sel.value;
}

function DoaddCabinet(){

window.open("deptCabinetAction.do?method=search4List&formName=eqpdispatchForm&addNum="+idcount+"&area="+document.all.collegeid.value+"&building="+document.all.lyid.value+"&room="+document.all.roomid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
}

function doSave(){

if(doCheckForm(eqpdispatchForm)){
    
    if(document.all.memo.value.length>300){
        alert("备注过长！");
        return;        
    }
	eqpdispatchForm.action="eqpdispatchAction.do?method=updateApply&idset="+idset+"&idcount="+idcount;
	eqpdispatchForm.submit();
}

}

function BchangeBLocation(sel){
       
    document.all.ifChanged.value="1";
}

function BchangeELocation(sel){
       
    document.all.ifChanged.value="1";
}

function BchangeCbid(sel){
   
     document.all.bcbid.value=sel.value;
     document.all.ifChanged.value="1";
}

function BchangeActid(sel){
   
    document.all.bactid.value=sel.value;
    document.all.ifChanged.value="1";
}

function BchangeMemo(sel){    
     document.all.ifChanged.value="1";
}

function doBatchSave(){

if(document.all.ifChanged.value!='1'){
    alert("您没有修改任何字段。");
    return;
}

if(doCheckForm(eqpdispatchForm)){
	eqpdispatchForm.action="eqpdispatchAction.do?method=batchupdateApply&idset="+idset+"&idcount="+idcount;
	eqpdispatchForm.submit();
}

}

function DoBack(){   
   eqpdispatchForm.action="eqpdispatchAction.do?method=search4ApplyList";
   eqpdispatchForm.submit();
}

function openOrCloseOpt(opts_id,opt_id)
{
      var optDiv = document.getElementById('opt_div_'+opts_id+'_'+opt_id);
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
