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
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/eqpdispatchAction.do?method=load4Detail" method="post">

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
												派发统计明细
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							</html:form>
							<logic:present name="eqplist" scope="request">

								<tr>
									<td height="35" align="center" valign="middle" class="mediumblack">
										派发统计明细
									</td>
								</tr>
								<tr>
									<td height="20" align="center" valign="middle">
										<ec:table items="eqplist" var="tl" rowsDisplayed="10" autoIncludeParameters="false" action="eqpdispatchAction.do?method=load4Detail">
											<ec:parameter name="inorout"></ec:parameter>
											<ec:parameter name="pfreason"></ec:parameter>
											<ec:parameter name="room"></ec:parameter>
											<ec:parameter name="building"></ec:parameter>
											<ec:parameter name="area"></ec:parameter>
											<ec:parameter name="pfdx"></ec:parameter>
											<ec:parameter name="thisAction"></ec:parameter>


											<ec:parameter name="search_wldl"></ec:parameter>
											<ec:parameter name="search_wlxl"></ec:parameter>
											<ec:parameter name="search_wlmc"></ec:parameter>
											<ec:parameter name="search_pfdx"></ec:parameter>
											<ec:parameter name="search_xq"></ec:parameter>
											<ec:parameter name="search_louyu"></ec:parameter>
											<ec:parameter name="search_jfkf"></ec:parameter>
											<ec:parameter name="search_sccj"></ec:parameter>
											<ec:parameter name="search_pfyy"></ec:parameter>
											<ec:parameter name="search_begindate"></ec:parameter>
											<ec:parameter name="search_enddate"></ec:parameter>



											<ec:row>
												<ec:column property="equipmentNo" title="设备标识" headerStyle="text-align:center" style="text-align: left" width="80">
													<c:if test="${tl.assetNo==null||tl.assetNo==''}">
													<a href="javascript:DoView('<c:out value="${tl.id}"/>')"><c:out value="${tl.equipmentNo}" /></a>&nbsp;
													</c:if>
													<c:if test="${tl.assetNo!=null&&tl.assetNo!=''}">
													<a href="javascript:DoView('<c:out value="${tl.id}"/>')"><c:out value="${tl.assetNo}" /></a>&nbsp;
													</c:if>														
												</ec:column>											
												<ec:column property="xlmc" title="小类" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="wlmc" title="名称" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="managerName" title="管理员" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="ocollegeArea" title="原校区" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="olymc" title="原楼宇" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="oroommc" title="原房间" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="ncollegeArea" title="新校区" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="nlymc" title="新楼宇" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="nroommc" title="新房间" headerStyle="text-align:center" style="text-align: center" />


												<ec:column property="sccjName" title="生产商" headerStyle="text-align:center" style="text-align: center" />

												<%if (request.getAttribute("ifLimit").equals("0")) {%>
												<ec:column property="procurePrice" title="采购价" headerStyle="text-align:center" style="text-align: center" />
												<%}%>
												<ec:column property="pfReason" title="派发原因" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="recordDate" title="登记日期" headerStyle="text-align:center" style="text-align: center" cell="date" format="yyyy-MM-dd" />
											</ec:row>
										</ec:table>
									</td>
								</tr>
							</logic:present>
						</table>
					</td>
				</tr>
				<tr>
					<td height="40" align="right" valign="middle">

						<input name="Submit3" type="button" class="button_nor" value="返 回" onClick="DoBack()">
					</td>
				</tr>
			</table>
	</body>
</html>

<SCRIPT language=javascript>

function DoView(eno){

    window.open("eqpdispatchAction.do?method=load4view&dispatchId="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoBack(){

   	ec.action = ec.thisAction.value;
	ec.submit();
}

</SCRIPT>

