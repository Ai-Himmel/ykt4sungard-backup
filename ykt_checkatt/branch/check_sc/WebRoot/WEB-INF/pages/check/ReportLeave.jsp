<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>复旦大学校园一卡通考勤管理系统</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<SCRIPT language=javascript>


function back(){
window.open('login.htm','_self');
}

function check(){
	var startDate=document.putin.register_startDate.value;
	var endDate=document.putin.register_endDate.value;
	var startTime = document.putin.register_startHour.value+putin.register_startMin.value;
	var endTime = document.putin.register_endHour.value+putin.register_endMin.value;
	if(startDate==''||endDate==''){
		alert('请将日期输入完整!');
		return false;
	}
	if(startDate>endDate){		
		alert("开始日期不能大于结束日期!");
		return false;
	}
	if (startTime>endTime){
		alert("开始时间不能大于结束时间!");
		return false;
	}
	document.putin.action = "leaveReportQuery.do?method=leaveReport";
	document.putin.submit();
}

function registerLeave(form, entityName, action,putinForm)
{
 if (!atleaseOneCheck())
        {
            alert('请至少选择一' + entityName + '！');
            return;
        }
        form.ec_ev.value = '';
        form.ec_efn.value = '';
		var radioValue;
				if(putinForm.register_type[0].checked)
	{
        radioValue=putinForm.register_type[0].value;
	}
	else
	{
		radioValue=putinForm.register_type[1].value;
	}

        form.action = action+"&register_startDate="+putinForm.register_sDate.value+"&register_endDate="+putinForm.register_eDate.value+"&register_description="+putinForm.register_description.value+"&register_startHour="+putinForm.register_startHour.value+"&register_startMin="+putinForm.register_startMin.value+"&register_endHour="+putinForm.register_endHour.value+"&register_endMin="+putinForm.register_endMin.value+"&register_type="+radioValue;



       form.submit();

}

</SCRIPT>

	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 请假申请 </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="tableDiv" >
			<form name="putin" method="post" action='leaveReportQuery.do?method=leaveReport'>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								申请人
							</td>
							<td width="15%" valign="middle" class="tableHeader3">
								<input type=hidden name=register_custId value="<c:out value='${custId}'/>">
								<c:out value='${custName}'/>
							</td>
							<input type=hidden name=register_repCustId value="<c:out value='${repCustId}'/>">
							<!--
							<td width="15%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								替代申请人
							</td>
							<td width="15%" valign="middle" class="tableHeader3">
								<input type=hidden name=register_repCustId value="<c:out value='${repCustId}'/>">
								<c:out value='${repCustName}'/>
							</td>
							-->
						</tr>
						<tr>
							
							<td width="15%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								开始日期
							</td>
							<td width="15%" valign="middle" class="tableHeader3">
								<input name="register_startDate" class="input_box" maxlength=20 readonly="readonly" style="width:100"  value="<c:out value='${beginDate}'/>" >
								<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="enddate" style="cursor:pointer">
							</td>
							<td width="15%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								开始时间
							</td>
							<td width="45%" valign="middle" class="tableHeader3">
								<select name="register_startHour">
									<%for (int i = 1; i < 24; i++) {
									String mm = "";
									if (i<10){
										mm="0"+String.valueOf(i);
									}else{
									    mm=String.valueOf(i);
									}
									%>
									<option value="<%=mm%>">
										<%=mm%>
									</option>
									<%}%>
								</select>点
								<select name="register_startMin">
									<option value="<c:out value='${beginMin}'/>">
										<c:out value='${beginMin}'/>
									</option>
									<%for (int i = 1; i < 60; i++) {
									String mm = "";
									if (i<10){
										mm="0"+String.valueOf(i);
									}else{
									    mm=String.valueOf(i);
									}
									%>
									<option value="<%=mm%>">
										<%=mm%>
									</option>
									<%}%>
								</select>分
							</td>
						</tr>
						<tr>
							<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								结束日期
							</td>
							<td valign="middle" class="tableHeader3">
								<input name="register_endDate" class="input_box" maxlength=20 readonly="readonly" style="width:100"   value="<c:out value='${endDate}'/>">
								<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="enddate" style="cursor:pointer">
							</td>
							<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								结束时间
							</td>
							<td valign="middle" class="tableHeader3">
								<select name="register_endHour">
									<%for (int i = 1; i < 24; i++) {
									String mm = "";
									if (i<10){
										mm="0"+String.valueOf(i);
									}else{
									    mm=String.valueOf(i);
									}
									%>
									<option value="<%=mm%>">
										<%=mm%>
									</option>
									<%}%>
								</select>点
								<select name="register_endMin">
									<option value="<c:out value='${endMin}'/>">
										<c:out value='${endMin}'/>
									</option>
									<%for (int i = 1; i < 60; i++) {
									String mm = "";
									if (i<10){
										mm="0"+String.valueOf(i);
									}else{
									    mm=String.valueOf(i);
									}
									%>
									<option value="<%=mm%>">
										<%=mm%>
									</option>
									<%}%>
								</select>分
							</td>
							<script type="text/javascript">
				    			new calendar("register_startDate", "calBegin", "%Y-%m-%d");	
				    			new calendar("register_endDate", "calEnd", "%Y-%m-%d");		
               				</script>
							
						</tr>
						<tr>
							<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								请假类别
							</td>
							<td align="left" valign="middle" class="tableHeader3">
								<select name="register_leaveId" style="width: 120">
									<c:forEach var="leaveType" items="${leavetype}">
										<c:choose>
											<c:when test="${leaveType.DICT_VALUE==leaveTypeId}">
												<option value="<c:out value="${leaveType.DICT_VALUE}"/>" selected="selected">
													<c:out value="${leaveType.DICT_CAPTION}" />
												</option>
											</c:when>
											<c:otherwise>
												<option value="<c:out value="${leaveType.DICT_VALUE}"/>" >
													<c:out value="${leaveType.DICT_CAPTION}" />
												</option>
											</c:otherwise>
										</c:choose>
									</c:forEach>
								</select>
							
							</td>
							<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								请假原因
							</td>
							<td align="left" valign="middle" class="tableHeader3">
								<input name="register_leaveInfo" class="textarea1" maxlength=100 style="width: 400" value="<c:out value="${leaveInfo}" />" >
							</td>
						</tr>
					</tbody>
				</table>
				<input type=hidden name=leaveReportId value=<c:out value="${leaveReportId}" />>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
				<tr>
					<td align="center" valign="middle">
						<input name="Submit" type="button" class="submitButton" value=" 确 定 " onclick="javascript:check()">
						<input name="Submit" type="button" class="submitButton" value=" 取 消 " onclick="history.back();">
					</td>
				</tr>
				</table>
			</form>
		</div>
	</body>
</html>
