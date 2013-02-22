<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="org.king.web.util.Constants"%>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>
		<meta http-equiv="Content-Type" content="text/html;">
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

<SCRIPT language=javascript>	

function search(){
    wlArrivalSearchForm.action = "<c:url value="/lf/wlArrivalAction.do"/>?method=loadWlArrivalList4Search";
	wlArrivalSearchForm.submit();
}
function show(id){
    ec.action = "<c:url value="/lf/wlArrivalBillAction.do"/>?method=loadWlArrivalInfo4Search&wlArrivalId="+id;
	ec.submit();
}
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>

		<table width="99%" border="0" align="left" cellpadding="0" cellspacing="0" style="padding-left:10px">
			<tr>
				<td align="left" valign="top">

					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td height="25" align="left" valign="top">
								<html:form action="/lf/wlArrivalAction" method="post">
									<table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">到货查询</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
										</tr>
									</table>
							</td>
						</tr>
						<tr>
							<td height="40" align="center" valign="top">
								<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>

									<tbody>
										<tr align="center" valign=center>
											<td width="13%" align="left" valign="middle" class="tableHeader2">
												到货单号
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<html:text property="search_wlArrivalId" styleClass="input_box" maxlength="50" />
											</td>
											<td width="13%" align="left" valign="middle" class="tableHeader2">
												登记人
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<html:text property="search_regPName" styleClass="input_box" maxlength="50" />
											</td>

										</tr>
										
										<tr align="center" valign=center>
											<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
												登记日期
											</td>
											<td align="left" valign="middle" class="tableHeader3" colspan=3>
												<table border="0" cellspacing="0" cellpadding="0">
													<tr>
														<td>
															<html:text property="search_regTimeStart" styleClass="input_box" maxlength="50" readonly="true" />
														</td>
														<td width="25" align="right">&nbsp;
															<img id="selectregTimeStart" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>"
																border="0" alt="开始日期" style="cursor:pointer">
														</td>
														<td>&nbsp;－&nbsp;</td>
														<td>
															<html:text property="search_regTimeEnd" styleClass="input_box" maxlength="50" readonly="true" />
														</td>
														<td width="25" align="right">&nbsp;
															<img id="selectregTimeEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>"
																border="0" alt="结束日期" style="cursor:pointer">
														</td>
													</tr>
												</table>
											</td>
										</tr>
									</tbody>

								</table>
							</td>
						</tr>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<input name="Submit" type="button" class="button_nor" onClick="search()" value="查 询">
								&nbsp;
								<input name="Submit2" type="button" class="button_nor" value="重 置" onclick="DoClear()">
							</td>
						</tr>
            		<logic:present name="wlArrList" scope="request">
						<logic:iterate name="wlArrList" id="wlArrival" type="java.util.Map">
							<input type="hidden" id="<bean:write name="wlArrival" property="wlArrivalId"/>" value="<bean:write name="wlArrival" property="notSubNum"/>"/>
							<input type="hidden" id="<bean:write name="wlArrival" property="wlArrivalId"/>" value="<bean:write name="wlArrival" property="notPassNum"/>"/>
							<input type="hidden" id="<bean:write name="wlArrival" property="wlArrivalId"/>" value="<bean:write name="wlArrival" property="ifaccount"/>"/>
							<input type="hidden" id="<bean:write name="wlArrival" property="wlArrivalId"/>" value="<bean:write name="wlArrival" property="ifreceiptavl"/>"/>
						</logic:iterate>
					</logic:present>
						</html:form>
						<tr>
							<td height="35" align="center" valign="middle" class="mediumblack">
								到货明细列表
							</td>
						</tr>
						<tr>
							<td height="20" align="center" valign="middle">
								<ec:table items="wlArrList" var="wlArrival" rowsDisplayed="10" action="wlArrivalAction.do?method=loadWlArrivalList4Search">
			    <ec:parameter name="search_wlArrivalId" />
				<ec:parameter name="search_regPName" />
				<ec:parameter name="search_regTimeStart" />
				<ec:parameter name="search_regTimeEnd" />
									<ec:exportXls fileName="wlArrList.xls" tooltip="导出 Excel" />
									<ec:row>
										<ec:column property="wlArrivalId" title="到货单号" headerStyle="text-align:center" style="text-align: center"
											width="90" >
											<a href="javascript:show('${wlArrival.wlArrivalId}')">${wlArrival.wlArrivalId}</a>
										</ec:column>
										<ec:column property="rcdPersonName" title="登记人" headerStyle="text-align:center" style="text-align: center"
											width="60" />
										<ec:column property="wlmc" title="物料名称" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="80" />
										<ec:column property="arrivalNum" title="到货数" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="60" 
										/>
										<ec:column property="ifaccount" title="是否已入帐" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="80" 
										/>
										<ec:column property="ifreceiptavl" title="发票是否到齐" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="80" 
										/>
										<ec:column property="providerName" title="供应商" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="130" 
										/>
										<ec:column property="producterName" title="生产商" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="130" 
										/>
										<ec:column property="state" title="明细状态" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="80" 
										/>
									</ec:row>
								</ec:table>
							</td>
						</tr>
						<tr>
							<td height="40" align="right" valign="middle">
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>

	</body>

</html>
<script>
function DoClear(){
    document.wlArrivalSearchForm.elements["search_wlArrivalId"].value="";
    document.wlArrivalSearchForm.elements["search_regPName"].value="";
    document.wlArrivalSearchForm.elements["search_regTimeStart"].value="";
    document.wlArrivalSearchForm.elements["search_regTimeEnd"].value="";
}
</SCRIPT>
           <script type="text/javascript">
                new calendar("search_regTimeStart", "selectregTimeStart", "%Y-%m-%d");
                new calendar("search_regTimeEnd", "selectregTimeEnd", "%Y-%m-%d");
           </script>