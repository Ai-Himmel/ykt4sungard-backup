<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
<head>
<title>上海复旦大学物料库存及仓储管理系统</title>
<meta http-equiv="Content-Type" content="text/html;">

<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

<SCRIPT language=javascript>
function back(){
 	wlArrivalDtlBillForm.action = "<c:url value="/lf/wlArrivalBillAction.do"/>?method=loadWlArrivalInfo4Search";
	wlArrivalDtlBillForm.submit();
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
								<html:form action="/lf/wlArrivalDtlAction" method="post">
									<table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">到货安置列表</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
										</tr>
									</table>
							</td>
						</tr>
						<tr>
							<td height="40" align="center" valign="top">
								<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
		<html:hidden property="wlArrivalId" styleClass="input_box"/>
		<html:hidden property="wlArrivalDtlId" styleClass="input_box"/>
									<tbody>
										<tr align="center" valign=center>
											<td width="13%" class="tableHeader2">
												物料名称
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
											<bean:write name="wlArrivalDtlBillForm" property="wlmc"/>
											</td>
											<td width="13%" class="tableHeader2">
												物料规格
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
											<bean:write name="wlArrivalDtlBillForm" property="wlsption"/>
											</td>
										</tr>
										<tr align="center" valign=center>
											<td width="13%" class="tableHeader2">
												物料来源
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<table border="0" cellspacing="0" cellpadding="0">
													<tr>
														<td><bean:write name="wlArrivalDtlBillForm" property="mtlSource"/>
														</td>

														<td width="25" align="right"></td>
													</tr>
												</table>
											</td>
											<td width="13%" align="left" valign="middle" class="tableHeader2">
												物料型号
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<table border="0" cellspacing="0" cellpadding="0">
													<tr>
														<td><bean:write name="wlArrivalDtlBillForm" property="wlmodel"/>
														</td>
														<td width="25" align="right">
															&nbsp;
														</td>
													</tr>
												</table>
											</td>
										</tr>
									</tbody>

								</table>
							</td>
						</tr>

						</html:form>
						<tr>
							<td height="35" align="center" valign="middle" class="mediumblack">
							</td>
						</tr>

      <tr>
        <td height="20" align="center" valign="middle" colspan="2">
        <ec:table items="allocationInfoList" var="allocationInfo" rowsDisplayed="5" action="wlArrivalDtlAction.do?method=loadAllocationList4Reg" >
								
				<ec:exportXls fileName="allocationInfoList" tooltip="导出 Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="50" headerStyle="text-align:center" style="text-align: center">
						<input type="checkbox" name="apiItemList" value="${allocationInfo.alId}" style="border:0px"/>
					</ec:column>

					<ec:column property="xqName" title="校区" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="bdName" title="楼宇" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="rmName" title="房间" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
					<ec:column property="placeNum" title="安置数量" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="managerName" title="管理员" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
				</ec:row>
			</ec:table></td>
      </tr>
 
      <tr>
        <td height="40" align="right" valign="middle" colspan="2">
          <input name="Submit31" type="button" class="button_nor" value="返 回" onClick="back()">
      </tr>
    </table></td>
  </tr>
  <%if(request.getAttribute("ifShowChecd").equals("1")){%>
     <tr>
  <td>
<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
<tr>
<td width="12%" align="center" valign="middle" class="tableHeader2" >审批日志:</td>
<td width="88%" align="left"><img onmouseover="this.style.cursor='hand';" id="opt_367628" src="<c:url value="/pages/style/default/images/title_open.gif"/>" onclick="openOrCloseOpt(105295,367628)" /></img></td>
</tr>
<tr><td colspan="2" height="10px"><td width="1"></tr>
<tr>
<td colspan="2">
<div id="opt_div_105295_367628" style="display:none">
<table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#3F738B bordercolordark=#ffffff id=submenu1> 
          <tbody>
<tr width="50" align="center">
    <td width="12%" valign="middle" class="tableHeader"><strong>审批人</strong></td>
    <td width="12%" valign="middle" class="tableHeader"><strong>审批结果</strong></td>
	<td width="58%" valign="middle" class="tableHeader"><strong>审批意见</strong></td>
	<td width="18%" valign="middle" class="tableHeader"><strong>审批时间</strong></td>
</tr>	
			   
<logic:present name="checkProcessList" scope="request">
	<logic:iterate name="checkProcessList" id="checkProcess" type="java.util.Map">
		<tr align="center">
			<td><bean:write name="checkProcess" property="checkPerson"/></td>
			<td><bean:write name="checkProcess" property="checkResult"/></td>
			<td><bean:write name="checkProcess" property="checkMemo"/></td>
			<td><bean:write name="checkProcess" property="checkTime" format="yyyy-MM-dd"/></td>
		</tr>
	</logic:iterate>
</logic:present>
 </tbody>
</table>
</div></td>
</tr>
</table>
  </td>
  </tr>
  <%} %>
</table>
</body>
</html>
