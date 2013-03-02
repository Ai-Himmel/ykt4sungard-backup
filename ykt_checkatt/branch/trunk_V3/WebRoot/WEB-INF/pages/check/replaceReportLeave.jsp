<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
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

function check()
{
	var startDate=putin.register_startDate.value;
	var endDate=putin.register_endDate.value;

	if(startDate==''||endDate=='')
	{
		alert('请将日期输入完整');
		return false;
	}
		if(startDate>endDate)
	{		
		alert("开始日期不能大于结束时间");
		return false;
	}

}
function registerirre(form, entityName, action,putinForm)
{
 	var grouplist="";
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
	
	if (!atleaseOneCheck())
	{
	    alert('请至少选择一' + entityName + '！');
	    return;
	}
	putinForm.ec_ev.value = '';
	putinForm.ec_efn.value = '';
	if (putinForm.itemlist.length==null){
		grouplist=putinForm.itemlist.value;
	}else{
	for (i=0;i<putinForm.itemlist.length;i++){
		if (putinForm.itemlist[i].checked){
			grouplist=putinForm.itemlist[i].value;
		}
	}}
	form.action = action+"&itemlist="+grouplist+"&repLeaveSign=1";
	form.submit();

}

</SCRIPT>

	</head>
	<%String msg = (String) request.getAttribute("msg");
			if (msg != null) {
%>
	<script language="javascript">
	alert('<%=msg%>');
</script>
	<%}%>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 代替请假 </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="filterDiv" style="text-align: left;">
			<form name="menualRegister" action="workInfo.do?method=searchClerkForReplace" method="post">
				<jodd:form bean="request">
						姓名:
						<input name="register_trueName" style="width:100" class="input_box" maxlength=20 value="<c:out value="${stuempName}"/>">
						&nbsp;&nbsp;
						学/工号:
						<input name="register_stuNumber" style="width:100" class="input_box" maxlength=20 value="<c:out value="${stuempNo}"/>">
						<!-- 
						&nbsp;&nbsp;
						部门:
						<select name="register_deptId" style="width:120">
						<option value="">
							所有
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptName}" />
							</option>
						</c:forEach>
						</select>
						&nbsp;&nbsp;&nbsp;
						人员性质:
						<select name="register_clerkType">
						<option value="2">
							不坐班
						</option>
						<option value="1">
							坐班
						</option>
					</select>
					&nbsp;&nbsp;
					
					<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
					-->
					&nbsp;&nbsp;&nbsp;
					<input name="Submit" type="submit" class="submitButton" value=" 查 询 ">
				</jodd:form>
			</form>
		</div>
		<div>
			<%@ include file="/pages/common/messages.jsp"%>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<jodd:form bean="request">
		<form name="register" action="workInfo.do?method=searchClerkForReplace" method="post">
			<div id="tableDiv">
				<ec:table items="clerkList" var="clerk" rowsDisplayed="5" action="workInfo.do?method=searchClerkForReplace" form="register">
					<ec:exportXls fileName="clerkList.xls" tooltip="导出 Excel" />
					<ec:row>
						<ec:column property="radio" 
							title="选择" 
							width="50" 
							headerStyle="text-align: center"
							sortable="false">
							<input type="radio" name="itemlist" value="${clerk.CUT_ID}" style="border:0px"/>
						</ec:column>
						<ec:column property="STUEMP_NO" 
							title="学/工号" 
							width="200" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
						<ec:column property="CUT_NAME" 
							title="姓名" 
							width="200" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
						<ec:column property="DEPT_NAME" 
							title="所属考勤部门" 
							width="450" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
						<ec:column property="DICT_CAPTION" 
							title="是否坐班" 
							width="100" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
					</ec:row>
				</ec:table>
			</div>
		</form>
		<p>
		</p>


		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv" style="display :<c:out value='${show}' default='none'/>">
			<form name="putin" method="post" action='leaveReportQuery.do?method=leaveReport'>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
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
									<%for (int i = 0; i < 60; i++) {
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
									<%for (int i = 0; i < 60; i++) {
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
											<c:when test="${leaveType.DICT_VALUE}==${leaveType}">
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
						<input name="Submit" type="button" class="submitButton" value=" 请 假 " onclick="if(check()==false) return false;registerirre(document.forms.putin,'考勤人员','<c:url value="leaveReportQuery.do?method=leaveReport" />',document.forms.register);">
						<input name="Submit" type="button" class="submitButton" value=" 取 消 " onclick="history.back();">
					</td>
				</tr>
				</table>
			</form>
		</div>
		</jodd:form>
	</body>
</html>
