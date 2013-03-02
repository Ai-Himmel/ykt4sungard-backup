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

function check()
{
	var startDate=putin.register_sDate.value;
	var endDate=putin.register_eDate.value;
	var description=putin.register_description.value;

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
			<strong> <font class="medium"> 请假/出差登记 </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="filterDiv" style="text-align: left;">
			<form name="leaveRegister" action="leaveRegister.do?method=search" method="post">
				<jodd:form bean="request">
						姓名:
						<input name="register_trueName" class="input_box" maxlength=20 style="width:100">
						&nbsp;&nbsp;
						<!-- 
						卡号:
						<input name="register_cardNumber" class="input_box" maxlength=20>
						&nbsp;&nbsp;
						-->
						学/工号:
						<input name="register_stuNumber" class="input_box" maxlength=20 style="width:100">
						&nbsp;&nbsp;
						部门:
						<select name="register_deptId">
						<option value="">
							所有
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptTitle}" />
							</option>
						</c:forEach>
					</select>
						&nbsp;&nbsp;&nbsp;
						人员性质:
						<select name="register_clerkType">
						<option value="1">
							坐班
						</option>
						<option value="2">
							不坐班
						</option>
					</select>
					&nbsp;&nbsp;&nbsp;
					 <input name="Submit" type="Submit" class="submitButton" value=" 查 询 ">
				</jodd:form>
			</form>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="titleDiv" >
			<strong> <font color="red"> <c:out value="${msg}" /> </font> </strong>
		</div>
		
		<form name="register" action="leaveRegister.do?method=search" method="post">
			<div id="tableDiv">
				<ec:table items="clerkList" var="clerk" rowsDisplayed="5" action="leaveRegister.do?method=search" form="register">
					<ec:exportXls fileName="clerkList.xls" tooltip="导出 Excel" />
					<ec:row>
						<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
							<input type="checkbox" name="itemlist" value="${clerk.CUT_ID}" style="border:0px" />
						</ec:column>
						<ec:column property="DEPT_NAME" title="部门" width="60" />
						<ec:column property="STUEMP_NO" title="学/工号" width="60" />
						<ec:column property="CUT_NAME" title="姓名" width="60" />
						<ec:column property="DICT_CAPTION" title="是否坐班" width="60" />
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
		<div id="tableDiv" style="display :<%=(String)request.getAttribute("display")==null?"none":(String)request.getAttribute("display")%>">
			<form name="putin" method="post" action='leaveRegister.do?method=register'>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr>
							<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								开始日期
							</td>
							<td width="20%" valign="middle" class="tableHeader3">
								<input name="register_sDate" class="input_box" maxlength=20 readonly="true" style="width:100">
								<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="enddate" style="cursor:pointer">
							</td>
							<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								开始时间
							</td>
							<td width="60%" valign="middle" class="tableHeader3">
								<select name="register_startHour">
									<option value="00">
										00
									</option>
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
									<option value="00">
										00
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
								<input name="register_eDate" class="input_box" maxlength=20 readonly="true" style="width:100">
								<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="enddate" style="cursor:pointer">
							</td>
							<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								结束时间
							</td>
							<td valign="middle" class="tableHeader3">
								<select name="register_endHour">
									<option value="00">
										00
									</option>
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
									<option value="00">
										00
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
			    			new calendar("register_sDate", "calBegin", "%Y-%m-%d");	
			    			new calendar("register_eDate", "calEnd", "%Y-%m-%d");		
               				</script>
							
						</tr>
						<tr>
							<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								请假类别
							</td>
							<td align="left" valign="middle" class="tableHeader3">
								<select name="register_type" style="width: 120">
									<c:forEach var="leaveType" items="${leavetype}">
										<option value="<c:out value="${leaveType.DICT_VALUE}"/>">
											<c:out value="${leaveType.DICT_CAPTION}" />
										</option>
									</c:forEach>
								</select>
							
							</td>
							<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								请假原因
							</td>
							<td width="60%" align="left" valign="middle" class="tableHeader3">
								<input name="register_description" class="textarea1" maxlength=20 width="300">
							</td>
						</tr>
					</tbody>
				</table>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
				<tr>
					<td align="center" valign="middle">
						<input name="Submit" type="button" class="submitButton" value=" 确 定 " onclick="if(check()==false) return false;registerLeave(document.forms.register,'请假登记','<c:url value="leaveRegister.do?method=register" />',document.forms.putin);">
					</td>
				</tr>
				</table>
			</form>
		</div>
	</body>
</html>
