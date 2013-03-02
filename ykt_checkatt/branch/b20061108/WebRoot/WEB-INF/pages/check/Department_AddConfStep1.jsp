<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>

	<body>
		<div class="pageTitle">
			�����Ű�����
		</div>
		<form name="clerkForm" action="department.do?method=addConf" method="post">
			<jodd:form bean="request">
				<%@ include file="/pages/common/messages.jsp"%>
				<table class="border" width=100% cellSpacing=0 cellPadding=2 align="center">
					<tr>
						<td class="left" width="20%">
							�Űಿ��:
						</td>
						<td class="right" align="left">
							<select name="new_deptId" style="width:200">
								<option value="">
									����
								</option>
								<c:forEach var="department" items="${departmentTree}">
									<option value="<c:out value="${department.deptId}"/>">
										<c:out value="${department.deptTitle}" />
									</option>
								</c:forEach>
							</select>
						</td>
					</tr>
					<tr>
						<td class="left">
							�����ƶ�:
						</td>
						<td class="right">
							<select name="new_clerkRule" style="width:200" onchange=" if(this.value!='') changed();">
								<option value="">
									��ѡ��
								</option>
								<c:forEach var="workConf" items="${workConfList}">
									<option value="<c:out value="${workConf.workconfId}"/>">
										<c:out value="${workConf.workconfName}" />
									</option>
								</c:forEach>
							</select>
							<br>
								<c:out value="${workconfDetail}" />
								<input type="hidden" name="new_workconfDetail" value="<c:out value='${workconfDetail}' />" />
							</br>
						</td>
					</tr>
					<tr>
						<td class="left">
							���ڹ���ʱ��:
						</td>
						<td class="right">
							<select name="new_cherkTimeRule" style="width:200" onchange=" if(this.value!='') changed();">
								<option value="">
									��ѡ��
								</option>
								<c:forEach var="workTime" items="${workTimeConfList}">
									<option value="<c:out value="${workTime.worktimeId}"/>">
										<c:out value="${workTime.worktimeName}" />
									</option>
								</c:forEach>
							</select>
							<br>
								<c:out value="${timeDetail}" />
								<input type="hidden" name="new_timeDetail" value="<c:out value='${timeDetail}' />" />
							</br>
						</td>
					</tr>
					<tr>
						<td class="left" width="20%">
							������������:
						</td>
						<td class="right">
							<span class="medium"> ��ʼ���� </span> &nbsp;
							<input class="input_box" maxlength=20 style="width:100" name="new_startDate" readonly="readonly">
							<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
							&nbsp; �������� &nbsp;
							<input name="new_endDate" class="input_box" maxlength=20 style="width:100" readonly="readonly">
							<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
							&nbsp;&nbsp;&nbsp;
							<input type="checkbox" value="1" checked name="new_ifWork">
							&nbsp;�Ƿ��ϰ�
							<script type="text/javascript">
								new calendar("new_startDate", "calBegin", "%Y-%m-%d");
								new calendar("new_endDate", "calEnd", "%Y-%m-%d");
							</script>
						</td>
					</tr>
					<input type="hidden" name="new_department" value="<c:out value='${new_department}'/>" />
					<tr>
						<td colspan="2" class="bottom">
							<input type="submit" class="submitButton" name="submitButton" value=" ȷ �� " style="margin-right:60px" onclick="return onSubmit();" />
							<input type="button" class="submitButton" name="submitButton" value=" ȡ �� " style="margin-right:60px" onclick="window.location.href='department.do?method=goDeptConf';" />

						</td>
					</tr>
				</table>
			</jodd:form>
		</form>

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> <c:out value="${dptName}" />�����Ű���Ϣ </font> </strong>
		</div>

	</body>
</html>
<script>
function onSubmit(){
    
	if(clerkForm.new_cherkTimeRule.value==""||clerkForm.new_clerkRule.value=="")
	{
		alert('��ѡ�����ƶ��빤��ʱ��!');
	    return false;
	}
	if(clerkForm.new_deptId.value==""||clerkForm.new_deptId.value=="")
	{
		alert('��ѡ���ڲ���');
	    return false;
	}
    if(clerkForm.new_startDate.value==""||clerkForm.new_endDate.value=="")
	{
		alert('�뽫������д����!');
		return false;
	}
    if(clerkForm.new_startDate.value>clerkForm.new_endDate.value)
	{
		alert('��ʼ���ڲ��ܴ��ڽ�������!');
		return false;
	}

	if(clerkForm.new_isSeat[0].checked&&clerkForm.new_cherkTimeRule.value!=""&&clerkForm.new_clerkRule.value!="")
	{
		 return true;
	}
   
    
}
function changed()
{
	clerkForm.submitButton.disabled="true";
	clerkForm.action='department.do?method=getConfDetail';
	clerkForm.submit();
}
</script>
