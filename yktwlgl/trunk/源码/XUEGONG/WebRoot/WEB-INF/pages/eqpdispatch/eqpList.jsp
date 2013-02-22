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

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" onload="init()">
		<br>
		<html:form action="/gyf/eqpdispatchAction.do?method=load4add" method="post">

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
												设备派发
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
											<input type="hidden" name="querymode" value="<%=request.getAttribute("querymode")==null?"1":request.getAttribute("querymode")%>">
											<tr align="center" valign=center>
												<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													设备编号
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_bh" styleClass="input_box" maxlength="32" />
												</td>
												<td width="20%" lign="left" valign="middle" class="tableHeader2">
													设备资产号
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<table border="0" cellspacing="0" cellpadding="0">
														<tr align="center" valign="middle">
															<td width="35">
																<html:text property="search_zch" styleClass="input_box" maxlength="50" />
															</td>
															<td width="25">
																&nbsp;
															</td>
															<td width="40" align="right">
																<html:select property="search_haszch" onchange="zchSetup(this)">
																	<html:option value="">请选择</html:option>
																	<html:option value="1">已有资产号</html:option>
																	<html:option value="0">尚无资产号</html:option>
																</html:select>
															</td>
														</tr>
													</table>
												</td>
												<td width="15%" align="left" valign="middle" class="tableHeader2">
													设备序列号
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_xlh" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													设备大类
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wldl" styleClass="select01" onchange="changeXl(this)">
														<html:option value="">请选择	</html:option>
														<html:options collection="dllist" labelProperty="dlmc" property="id" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													设备小类
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wlxl" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="xllist" labelProperty="xlmc" property="id" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													设备名称
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_wlmc" styleClass="input_box" maxlength="100" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													设备型号
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_xh" styleClass="input_box" maxlength="100" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													管理员
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_gly" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													生产厂家
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_sccj" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="sccjlist" labelProperty="companyName" property="id" />
													</html:select>
												</td>
											</tr>
											<tr id="tr1" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													设备来源
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_ly" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="sourcelist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													是否附件
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_fj" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:option value="0">否</html:option>
														<html:option value="1">是</html:option>
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													上级设备号
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_sjssh" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr id="tr2" align="center" valign=center>												
												<td align="left" valign="middle" class="tableHeader2">
													合同号
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_hth" styleClass="input_box" maxlength="100" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													供应商
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_gys" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="gyslist" labelProperty="companyName" property="id" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													维修商
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wxs" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="wxslist" labelProperty="companyName" property="id" />
													</html:select>
												</td>
											</tr>
											<tr id="tr3" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													到货号
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_dhh" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													到货日期从
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_dhrqc" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_dhrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="开始日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													到货日期到
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_dhrqd" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_dhrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="结束日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
											</tr>
											<script type="text/javascript">
                new calendar("search_dhrqc", "select_dhrqc", "%Y-%m-%d");
                new calendar("search_dhrqd", "select_dhrqd", "%Y-%m-%d");
           </script>
											<tr id="tr4" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													采购日期从
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_cgrqc" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_cgrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="开始日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													入账日期从
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_rzrqc" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_rzrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="结束日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													到发票日期从
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_dfprqc" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_dfprqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="结束日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
											</tr>
											<tr id="tr5" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													采购日期到
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_cgrqd" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_cgrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="开始日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													入账日期到
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_rzrqd" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_rzrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="结束日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													到发票日期到
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_dfprqd" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_dfprqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="结束日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
											</tr>
											<script type="text/javascript">                
			    new calendar("search_cgrqc", "select_cgrqc", "%Y-%m-%d");
                new calendar("search_cgrqd", "select_cgrqd", "%Y-%m-%d");
                new calendar("search_rzrqc", "select_rzrqc", "%Y-%m-%d");
                new calendar("search_rzrqd", "select_rzrqd", "%Y-%m-%d");
                new calendar("search_dfprqc", "select_dfprqc", "%Y-%m-%d");
                new calendar("search_dfprqd", "select_dfprqd", "%Y-%m-%d");				
            </script>
											<%if (request.getAttribute("ifLimit").equals("0")) {%>
											<tr id="tr6" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													采购单价从
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_djc" styleClass="input_box" maxlength="50" />
													&nbsp;元
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													采购单价到
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_djd" styleClass="input_box" maxlength="50" />
													&nbsp;元
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													发票号码
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_fphm" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<%} else {%>
											<tr id="tr6" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													发票号码
												</td>
												<td align="left" valign="middle" class="tableHeader3" colspan="5">
													<html:text property="search_fphm" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<%}%>
											<tr id="tr7" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													经费来源
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_jfly" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													采购经办人
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_cgjbr" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													到货经办人
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_dhjbr" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr id="tr8" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													派发对象
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_pfdx" styleClass="select01">
														<html:option value="">请选择</html:option>
														<html:options collection="pflist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													所处校区
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_xq" styleClass="select01" onchange="changeBd(this)">
														<html:option value="">请选择</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													所在楼宇
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_louyu" styleClass="select01">
														<html:option value="">请选择</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
											</tr>
											<tr id="tr9" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													机房/库房
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_jfkf" styleClass="input_box" maxlength="100" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													机柜编号
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_jgbh" styleClass="input_box" maxlength="100" />
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													设备状态
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_sbzt" styleClass="select01">
														<html:option value="">请选择</html:option>
														<html:options collection="eqpstatelist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
											</tr>
											<tr id="tr10" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													IPv4地址
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_ipv4dz" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													服务器域名1
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_fwqym1" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													上连交换机IP
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_sljhjip" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">
									<input name="bquerymode" type="button" class="button_nor" value="高级查询" onclick="ChangeQueryMode(this)">
									&nbsp;
									<input name="Submit" type="button" class="button_nor" value="查 询" onclick="DoFind()">
									&nbsp;
									<input name="Submit2" type="button" class="button_nor" value="重 置" onclick="DoClear()">
								</td>

							</tr>
							</html:form>

							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									设备列表
								</td>
							</tr>
							<jodd:form bean="request">
								<tr>
									<td height="20" align="center" valign="middle">
										<ec:table items="eqplist" var="eqpJBInfo" autoIncludeParameters="false" rowsDisplayed="10" action="eqpdispatchAction.do?method=load4add">
                                            <ec:parameter name="search_bh" />
											<ec:parameter name="search_zch" />
											<ec:parameter name="search_xlh" />
											<ec:parameter name="search_wldl" />
											<ec:parameter name="search_wlxl" />
											<ec:parameter name="search_wlmc" />
											<ec:parameter name="search_xh" />
											<ec:parameter name="search_hth" />
											<ec:parameter name="search_sccj" />

											<ec:parameter name="search_ly" />
											<ec:parameter name="search_fj" />
											<ec:parameter name="search_sjssh" />
											<ec:parameter name="search_gly" />
											<ec:parameter name="search_gys" />
											<ec:parameter name="search_wxs" />
											<ec:parameter name="search_dhh" />
											<ec:parameter name="search_dhrqc" />
											<ec:parameter name="search_dhrqd" />
											<ec:parameter name="search_cgrqc" />
											<ec:parameter name="search_rzrqc" />
											<ec:parameter name="search_dfprqc" />
											<ec:parameter name="search_cgrqd" />
											<ec:parameter name="search_rzrqd" />
											<ec:parameter name="search_dfprqd" />
											<ec:parameter name="search_djc" />
											<ec:parameter name="search_djd" />
											<ec:parameter name="search_fphm" />
											<ec:parameter name="search_jfly" />
											<ec:parameter name="search_cgjbr" />
											<ec:parameter name="search_dhjbr" />
											<ec:parameter name="search_pfdx" />
											<ec:parameter name="search_xq" />
											<ec:parameter name="search_louyu" />
											<ec:parameter name="search_jfkf" />
											<ec:parameter name="search_jgbh" />
											<ec:parameter name="search_sbzt" />
											<ec:parameter name="search_ipv4dz" />
											<ec:parameter name="search_fwqym1" />
											<ec:parameter name="search_sljhjip" />
											<ec:exportXls fileName="equipmentList.xls" tooltip="导出 Excel" />
											<ec:row>
												<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
													<input type="checkbox" name="cbgroup" value="${eqpJBInfo.equipmentNo}" style="border:0px" onClick="doSel(this)" />
												</ec:column>
												<ec:column property="equipmentNo" title="设备编号" headerStyle="text-align:center" style="text-align: left" width="80">
													<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
													<a href="javascript:DoView('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.equipmentNo}</a>
													</c:if>
													<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
													<a href="javascript:DoView('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.assetNo}</a>
													</c:if>														

												</ec:column>
												<ec:column property="serialNo" title="序列号" headerStyle="text-align:center" style="text-align: left" width="70" />
												<ec:column property="xlmc" title="小类" headerStyle="text-align:center" style="text-align: left" width="80" />
												<ec:column property="wlmc" title="名称" headerStyle="text-align:center" style="text-align: left" width="90" />
												<ec:column property="eqpModel" title="型号" headerStyle="text-align:center" style="text-align: left" width="60" />
												<ec:column property="eqpSource" title="来源" headerStyle="text-align:center" style="text-align: left" width="40" />
												<ec:column property="sccjName" title="生产厂家" headerStyle="text-align:center" style="text-align: left" width="100" />
												<ec:column property="contractNo" title="合同" headerStyle="text-align:center" style="text-align: left" width="40" />
												<ec:column property="managerName" title="管理员" headerStyle="text-align:center" style="text-align: left" width="50" />
												<ec:column property="usageCategoryName" title="用途大类" headerStyle="text-align:center" style="text-align: left" width="60" />															
												<ec:column property="eqpState" title="状态" headerStyle="text-align:center" style="text-align: left" width="40" />
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
														<input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()">
														<input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()">
														<input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()">
													</td>
													<td height="40" align="right" valign="middle">
														<input name="Submit3" type="button" class="button_nor" value="派发登记" onClick="DoDispatch()">
														<input name="Submit12" type="button" class="button_nor" value="返 回" onClick="DoBack()">
													</td>
												</tr>
											</tbody>
										</table>
									</td>
								</tr>
								<%} else {%>
								<tr>
									<td height="40" align="right" valign="middle">
										<input name="Submit12" type="button" class="button_nor" value="返 回" onClick="DoBack()">
									</td>
								</tr>
								<%}%>
							</jodd:form>
						</table>
					</td>
				</tr>
			</table>
	</body>
</html>

<script>

    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("dxlist")!=null)
       resultset=(String[][])request.getAttribute("dxlist");//读取大小类对应数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//产生javascript二维数组，对应小类id、小类名称、大类id
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
   if(request.getAttribute("ablist")!=null)
       resultset2=(String[][])request.getAttribute("ablist");//读取校区、楼宇对应数据
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>");//产生javascript二维数组，对应楼宇id、楼宇名称、校区id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<SCRIPT language=javascript>

//setTimeout('init()',10);
function init(){
  var dl=document.eqpdispatchForm.elements["search_wldl"].value;
  var xl=document.eqpdispatchForm.elements["search_wlxl"].value;
  
  if(dl!='')
      changeXl(document.eqpdispatchForm.elements["search_wldl"]);
  for(var j=0;j<document.eqpdispatchForm.elements["search_wlxl"].length;j++){
      if(document.eqpdispatchForm.elements["search_wlxl"][j].value==xl)
	     document.eqpdispatchForm.elements["search_wlxl"][j].selected=true;
					
  }
  
  var area=document.eqpdispatchForm.elements["search_xq"].value;
  var building=document.eqpdispatchForm.elements["search_louyu"].value;
  
  if(area!='')
      changeBd(document.eqpdispatchForm.elements["search_xq"]);
  for(var j=0;j<document.eqpdispatchForm.elements["search_louyu"].length;j++){
      if(document.eqpdispatchForm.elements["search_louyu"][j].value==building)
	     document.eqpdispatchForm.elements["search_louyu"][j].selected=true;
					
  }
  
  if(document.eqpdispatchForm.querymode.value=='1'){
      document.eqpdispatchForm.bquerymode.value="高级查询";
      tr1.style.display='none';
      tr2.style.display='none';
      tr3.style.display='none';       
      tr4.style.display='none';
      tr5.style.display='none';
      tr6.style.display='none';
      tr7.style.display='none';
      //tr8.style.display='none';
      //tr9.style.display='none';
      tr10.style.display='none';
  }
  else if(document.eqpdispatchForm.querymode.value=='2'){
      document.eqpdispatchForm.bquerymode.value="简单查询";
      tr1.style.display='';
      tr2.style.display='';
      tr3.style.display=''; 
      tr4.style.display='';
      tr5.style.display='';
      tr6.style.display='';
      tr7.style.display='';
      tr8.style.display='';
      tr9.style.display='';
      tr10.style.display='';
  }
    
}  

function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpdispatchForm.elements["search_wlxl"].length=1; //清空原小类列表        
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.eqpdispatchForm.elements["search_wlxl"].options[document.eqpdispatchForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.eqpdispatchForm.elements["search_wlxl"].options[document.eqpdispatchForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpdispatchForm.elements["search_louyu"].length=1; //清空原楼宇列表        
   
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

   //alert(sel.value);

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
       alert("当前无记录！");
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
       alert("当前无记录！");
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
       alert("当前无记录！");
  }
  

}

function DoFind(){

    if(document.eqpdispatchForm.elements["search_djc"]!=null&&document.eqpdispatchForm.elements["search_djc"].value!=''&&isNaN(document.eqpdispatchForm.elements["search_djc"].value)){
        alert("采购单价从必须填写数字！");
        return;
    }
    if(document.eqpdispatchForm.elements["search_djd"]!=null&&document.eqpdispatchForm.elements["search_djd"].value!=''&&isNaN(document.eqpdispatchForm.elements["search_djd"].value)){
        alert("采购单价到必须填写数字！");
        return;
    }
    
    eqpdispatchForm.action="eqpdispatchAction.do?method=load4add";
    eqpdispatchForm.submit();

}

function DoDispatch(){
 
   var sflag=0;
   
   if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("请选择要派发的设备记录！");
              return;
          } 
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要派发的设备记录！");
              return;        
        }
   }
   
   document.forms.ec.action="eqpdispatchAction.do?method=load4dispatch";       
   document.forms.ec.submit();
   
  
  
}

function DoView(eno){

    window.open("equipmentAction.do?method=load4view&equipmentNo="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function ChangeQueryMode(btn){

    if(btn.value=='高级查询'){
       document.eqpdispatchForm.querymode.value="2";
       btn.value='简单查询';
       tr1.style.display='';
       tr2.style.display='';
       tr3.style.display='';   
       tr4.style.display='';
       tr5.style.display='';
       tr6.style.display='';
       tr7.style.display='';
       tr8.style.display='';
       tr9.style.display='';
       tr10.style.display='';
    }
    else if(btn.value=='简单查询'){
       document.eqpdispatchForm.querymode.value="1";
       btn.value='高级查询';
       tr1.style.display='none';
       tr2.style.display='none';
       tr3.style.display='none'; 
       tr4.style.display='none';
       tr5.style.display='none';
       tr6.style.display='none';
       tr7.style.display='none';
       //tr8.style.display='none';
       //tr9.style.display='none';
       tr10.style.display='none';
    }

}

function DoClear(){

    document.eqpdispatchForm.elements["search_bh"].value="";
    document.eqpdispatchForm.elements["search_zch"].value="";
    document.eqpdispatchForm.elements["search_haszch"].value="";
    document.eqpdispatchForm.elements["search_haszch"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_xlh"].value="";
    document.eqpdispatchForm.elements["search_wldl"].value="";
    document.eqpdispatchForm.elements["search_wldl"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_wlxl"].value="";
    document.eqpdispatchForm.elements["search_wlxl"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_wlmc"].value="";
    document.eqpdispatchForm.elements["search_xh"].value="";
    document.eqpdispatchForm.elements["search_hth"].value="";
    document.eqpdispatchForm.elements["search_sccj"].value="";
    document.eqpdispatchForm.elements["search_sccj"].options[0].selected=true;
    
    document.eqpdispatchForm.elements["search_ly"].value="";
    document.eqpdispatchForm.elements["search_ly"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_fj"].value="";
    document.eqpdispatchForm.elements["search_fj"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_sjssh"].value="";
    document.eqpdispatchForm.elements["search_gly"].value="";
    document.eqpdispatchForm.elements["search_gys"].value="";
    document.eqpdispatchForm.elements["search_gys"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_wxs"].value="";
    document.eqpdispatchForm.elements["search_wxs"].options[0].selected=true;    
    document.eqpdispatchForm.elements["search_dhh"].value="";
    document.eqpdispatchForm.elements["search_dhrqc"].value="";
    document.eqpdispatchForm.elements["search_dhrqd"].value="";
    document.eqpdispatchForm.elements["search_cgrqc"].value="";
    document.eqpdispatchForm.elements["search_rzrqc"].value="";
    document.eqpdispatchForm.elements["search_dfprqc"].value="";
    document.eqpdispatchForm.elements["search_cgrqd"].value="";
    document.eqpdispatchForm.elements["search_rzrqd"].value="";
    document.eqpdispatchForm.elements["search_dfprqd"].value="";
    if(document.eqpdispatchForm.elements["search_djc"]!=null){
        document.eqpdispatchForm.elements["search_djc"].value="";
        document.eqpdispatchForm.elements["search_djd"].value="";
    }
    document.eqpdispatchForm.elements["search_fphm"].value="";
    document.eqpdispatchForm.elements["search_jfly"].value="";
    document.eqpdispatchForm.elements["search_cgjbr"].value="";
    document.eqpdispatchForm.elements["search_dhjbr"].value="";
    document.eqpdispatchForm.elements["search_pfdx"].value="";
    document.eqpdispatchForm.elements["search_pfdx"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_xq"].value="";
    document.eqpdispatchForm.elements["search_xq"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_louyu"].value="";
    document.eqpdispatchForm.elements["search_louyu"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_jfkf"].value="";
    document.eqpdispatchForm.elements["search_jgbh"].value="";
    document.eqpdispatchForm.elements["search_sbzt"].value="";
    document.eqpdispatchForm.elements["search_sbzt"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_ipv4dz"].value="";
    document.eqpdispatchForm.elements["search_fwqym1"].value="";
    document.eqpdispatchForm.elements["search_sljhjip"].value="";
}

function DoBack(){   
   eqpdispatchForm.action="eqpdispatchAction.do?method=search4List&listNum='all'";
   eqpdispatchForm.submit();
}

</SCRIPT>

