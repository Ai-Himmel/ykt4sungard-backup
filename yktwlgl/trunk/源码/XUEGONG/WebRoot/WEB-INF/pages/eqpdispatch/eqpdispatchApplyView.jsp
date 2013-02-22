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
											<logic:present name="eqpDetail" scope="request">
												<logic:iterate name="eqpDetail" id="el" type="java.util.Map" indexId="i">
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
															<bean:write name="el" property="cabinetmc" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															起始位置
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="BLocation" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															终止位置
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="ELocation" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															上架经理人
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="actPersonName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															备注
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
												原始派发记录
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
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															派发原因
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="pfReasonName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															用途大类
														</td>
														<td align="left" valign="middle" class="tableHeader3" colspan="3">
															<bean:write name="el" property="usageCategoryName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															用途说明
														</td>
														<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" colspan="3">
															<bean:write name="el" property="pfUsage" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															原派发对象
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="opfName" />
														</td>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															新派发对象
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="npfName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															原校区
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="oxqName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															新校区
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nxqName" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															原楼宇
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="obdName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															新楼宇
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nbdName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															原房间
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="ormName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															新房间
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nrmName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															原详细地点
														</td>
														<td width="35%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
															<bean:write name="el" property="OPlace" />
														</td>
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															新详细地点
														</td>
														<td width="35%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
															<bean:write name="el" property="NPlace" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															原管理员
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="omgName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															新管理员
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="nmgName" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															接收人
														</td>
														<td align="left" valign="middle" class="tableHeader3" >
															<bean:write name="el" property="actPersonName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															派发后状态
														</td>
														<td align="left" valign="middle" class="tableHeader3" >
															<c:if test="${el.NEqpState=='3_zaiyong'}">在用</c:if>
															<c:if test="${el.NEqpState=='3_xianzhi'}">闲置</c:if>
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															管理员变更状态
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="managerCheckName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															登记人
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="rcdPersonName" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															更新人
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="updatorName" />
														</td>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															更新时间
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<bean:write name="el" property="updateTime" formatKey="dateTimeFormat" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
															备注
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
									<input name="Submit12" type="button" class="button_nor" value="关 闭" onClick="DoBack()">
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
						</html:form>
	</body>
</html>

<script type="text/javascript">

   setTimeout('DoInit()',10);
   
function DoInit(){
    
   if(document.all.hmsg.value=='0')
       alert("未找到派发申请记录！");  
  
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
