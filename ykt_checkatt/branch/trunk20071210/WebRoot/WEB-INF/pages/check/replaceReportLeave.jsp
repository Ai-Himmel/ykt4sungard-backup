<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<title>������ѧУ԰һ��ͨ���ڹ���ϵͳ</title>
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
		alert('�뽫������������');
		return false;
	}
		if(startDate>endDate)
	{		
		alert("��ʼ���ڲ��ܴ��ڽ���ʱ��");
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
		alert('�뽫������������!');
		return false;
	}
	if(startDate>endDate){		
		alert("��ʼ���ڲ��ܴ��ڽ�������!");
		return false;
	}
	if (startTime>endTime){
		alert("��ʼʱ�䲻�ܴ��ڽ���ʱ��!");
		return false;
	}
	
	if (!atleaseOneCheck())
	{
	    alert('������ѡ��һ' + entityName + '��');
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
			<strong> <font class="medium"> ������� </font> </strong>
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
						����:
						<input name="register_trueName" style="width:100" class="input_box" maxlength=20 value="<c:out value="${stuempName}"/>">
						&nbsp;&nbsp;
						ѧ/����:
						<input name="register_stuNumber" style="width:100" class="input_box" maxlength=20 value="<c:out value="${stuempNo}"/>">
						<!-- 
						&nbsp;&nbsp;
						����:
						<select name="register_deptId" style="width:120">
						<option value="">
							����
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptName}" />
							</option>
						</c:forEach>
						</select>
						&nbsp;&nbsp;&nbsp;
						��Ա����:
						<select name="register_clerkType">
						<option value="2">
							������
						</option>
						<option value="1">
							����
						</option>
					</select>
					&nbsp;&nbsp;
					
					<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
					-->
					&nbsp;&nbsp;&nbsp;
					<input name="Submit" type="submit" class="submitButton" value=" �� ѯ ">
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
					<ec:exportXls fileName="clerkList.xls" tooltip="���� Excel" />
					<ec:row>
						<ec:column property="radio" 
							title="ѡ��" 
							width="50" 
							headerStyle="text-align: center"
							sortable="false">
							<input type="radio" name="itemlist" value="${clerk.CUT_ID}" style="border:0px"/>
						</ec:column>
						<ec:column property="STUEMP_NO" 
							title="ѧ/����" 
							width="200" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
						<ec:column property="CUT_NAME" 
							title="����" 
							width="200" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
						<ec:column property="DEPT_NAME" 
							title="�������ڲ���" 
							width="450" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
						<ec:column property="DICT_CAPTION" 
							title="�Ƿ�����" 
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
								��ʼ����
							</td>
							<td width="15%" valign="middle" class="tableHeader3">
								<input name="register_startDate" class="input_box" maxlength=20 readonly="readonly" style="width:100"  value="<c:out value='${beginDate}'/>" >
								<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="enddate" style="cursor:pointer">
							</td>
							<td width="15%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								��ʼʱ��
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
								</select>��
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
								</select>��
							</td>
						</tr>
						<tr>
							<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								��������
							</td>
							<td valign="middle" class="tableHeader3">
								<input name="register_endDate" class="input_box" maxlength=20 readonly="readonly" style="width:100"   value="<c:out value='${endDate}'/>">
								<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="enddate" style="cursor:pointer">
							</td>
							<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								����ʱ��
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
								</select>��
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
								</select>��
							</td>
							<script type="text/javascript">
				    			new calendar("register_startDate", "calBegin", "%Y-%m-%d");	
				    			new calendar("register_endDate", "calEnd", "%Y-%m-%d");		
               				</script>
							
						</tr>
						<tr>
							<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								������
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
								���ԭ��
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
						<input name="Submit" type="button" class="submitButton" value=" �� �� " onclick="if(check()==false) return false;registerirre(document.forms.putin,'������Ա','<c:url value="leaveReportQuery.do?method=leaveReport" />',document.forms.register);">
						<input name="Submit" type="button" class="submitButton" value=" ȡ �� " onclick="history.back();">
					</td>
				</tr>
				</table>
			</form>
		</div>
		</jodd:form>
	</body>
</html>
