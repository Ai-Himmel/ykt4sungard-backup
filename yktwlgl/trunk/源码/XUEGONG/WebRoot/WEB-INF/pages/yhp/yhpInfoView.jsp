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
												易耗品信息
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
											<td width="98" background="<c:url value="/pages/style/default/images/titlebg1.gif"/>" class="mediumblue">
												基本信息
											</td>
											<td width="98" background="<c:url value="/pages/style/default/images/titlebg2.gif"/>">
												<a href="javascript:DoViewArlInfo()" class="black_link3">到货信息</a>
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
														<logic:present name="yhpDetail" scope="request">
															<logic:iterate name="yhpDetail" id="el" type="java.util.Map" indexId="i">
																<tr align="center" valign="middle">
																	<td width="15%" height="26" align="right" valign="middle" class="tableHeader2">
																		易耗品批号
																	</td>
																	<td width="85%" align="left" valign="middle" class="tableHeader3" colspan="3">
																		<bean:write name="el" property="id" />
																		&nbsp;
																		<input type="hidden" name="yhpNo" value="<bean:write name="el" property="id"/>">
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		品名
																	</td>
																	<td width="35%" align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="wlmc" />
																		&nbsp;
																	</td>
																	<td width="15%" align="right" valign="middle" class="tableHeader2">
																		单位
																	</td>
																	<td width="35%" align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="wldw" />
																		&nbsp;
																	</td>

																</tr>
																<tr align="center" valign="middle">
																	<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		起始编号
																	</td>
																	<td width="35%" align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="beginNo" />
																		&nbsp;
																	</td>
																	<td width="15%" align="right" valign="middle" class="tableHeader2">
																		结束编号
																	</td>
																	<td width="35%" align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="endNo" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		资产所属
																	</td>
																	<td align="left" valign="middle" class="tableHeader3" colspan="3">
																		<bean:write name="el" property="deptName" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		用途大类
																	</td>
																	<td align="left" valign="middle" class="tableHeader3" colspan="3">
																		<bean:write name="el" property="usageCategoryName" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		用途说明
																	</td>
																	<td colspan="3" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
																		<bean:write name="el" property="yhpUsage" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		备注
																	</td>
																	<td colspan="3" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
																		<bean:write name="el" property="memo" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		派发对象
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="pfCategory" />
																		&nbsp;
																	</td>
																	<td align="right" valign="middle" class="tableHeader2">
																		所处校区
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="collegeArea" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		所在楼宇
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="lymc" />
																		&nbsp;
																	</td>
																	<td align="right" valign="middle" class="tableHeader2">
																		库房/机房
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="roommc" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		详细地点
																	</td>
																	<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" colspan="3">
																		<bean:write name="el" property="place" />
																		&nbsp;
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
																		进货数量
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<bean:write name="el" property="yhpNum" />
																		&nbsp;
																	</td>
																	<td align="right" valign="middle" class="tableHeader2">
																		当前数量
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<%if (request.getAttribute("ifLimit").equals("0")) {%>
																		<bean:write name="el" property="curNum" />
																		<%}%>
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
												<input name="Submit12" type="button" class="button_nor" value="关 闭" onClick="DoBack()">
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
       alert("未找到设备基本信息！");
}

function DoViewArlInfo(){

    yhpsearchForm.action="yhpAction.do?method=viewArlInfo";
	yhpsearchForm.submit();

}

function DoBack(){   
   self.close();
}
</script>
