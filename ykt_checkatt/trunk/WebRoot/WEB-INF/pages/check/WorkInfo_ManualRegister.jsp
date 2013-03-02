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
	var startDate=putin.register_sDate.value;
	if(startDate=='')
	{
		alert('请将日期输入完整');
		return false;
	}
}
function registerirre(form, entityName, action,putinForm)
{
 var grouplist="";
 if (!atleaseOneCheck())
    {
        alert('请至少选择一' + entityName + '！');
        return;
    }
    form.ec_ev.value = '';
    form.ec_efn.value = '';
    if (document.forms.register.itemlist.length==null){
    	grouplist=document.forms.register.itemlist.value;
    }else{
	for (i=0;i<document.forms.register.itemlist.length;i++){
		if (document.forms.register.itemlist[i].checked){
			grouplist=document.forms.register.itemlist[i].value;
		}
	}}
	
    form.action = action+"&itemlist="+grouplist+"&register_startDate="+putinForm.register_sDate.value+"&register_startHour="+putinForm.register_startHour.value+"&register_startMin="+putinForm.register_startMin.value;
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
			<strong> <font class="medium"> 手工考勤 </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="filterDiv" style="text-align: left;">
			<form name="menualRegister" action="workInfo.do?method=searchClerk" method="post">
				<jodd:form bean="request">
						姓名:
						<input name="register_trueName" style="width:100" class="input_box" maxlength=20>
						&nbsp;&nbsp;
						<!-- 
						卡号:
						<input name="register_cardNumber" class="input_box" maxlength=20>
						&nbsp;&nbsp;
						-->
						学/工号:
						<input name="register_stuNumber" style="width:100" class="input_box" maxlength=20>
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
					<!-- 
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
		<form name="register" action="workInfo.do?method=searchClerk" method="post">
			<div id="tableDiv">
				<ec:table items="clerkList" var="clerk" rowsDisplayed="5" action="workInfo.do?method=searchClerk" form="register">
					<ec:exportXls fileName="clerkList.xls" tooltip="导出 Excel" />
					<ec:row>
						<ec:column property="radio" 
							title="选择" 
							width="50" 
							headerStyle="text-align: center"
							sortable="false">
							<input type="radio" name="itemlist" value="${clerk.CUT_ID}" style="border:0px" />
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
			<form name="putin" method="post" action='workInfo.do?method=manualRegister'>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr>
							<td width=10% height="20" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								考勤日期
							</td>
							<td width=20% align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="register_sDate" class="input_box" maxlength=20 style="width:100" readonly="readonly" value="<c:out value="${checkDate}"/>">
								<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
							</td>
							<td width=10% height="20" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								考勤时间
							</td>
							<td width=20% align="left" valign="middle" bgcolor="#E7F1F5">
								<p></p>
								<select name="register_startHour">
									<option value="00">
										00
									</option>
									<%for (int i = 1; i < 24; i++) {%>
									<option value="<%=i%>">
										<%=i%>
									</option>
									<%}%>
								</select>
								点
								<select name="register_startMin">
									<option value="00">
										00
									</option>
									<%for (int i = 0; i < 60; i++) {%>
									<option value="<%=i%>">
										<%=i%>
									</option>
									<%}%>
								</select>
								分
							</td>
								<script type="text/javascript">
				    			new calendar("register_sDate", "calBegin", "%Y-%m-%d");			
	               				</script>
							<td height="20" align="left" valign="middle" class="tdborder02">
								
								<input name="Submit" type="button" class="submitButton" value=" 考 勤 " onclick="if(check()==false) return false;registerirre(document.forms.register,'考勤人员','<c:url value="workInfo.do?method=manualRegister" />',document.forms.putin);">
							</td>
					</tbody>
				</table>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tr>
						<td height="40" align="left" valign="middle" class="tdborder02">
						</td>
					
					</tr>
				
				</table>
				
			</form>
		</div>
		</jodd:form>
	</body>
</html>
