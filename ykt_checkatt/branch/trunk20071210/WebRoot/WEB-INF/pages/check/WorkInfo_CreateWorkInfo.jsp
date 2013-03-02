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
	<%String msg = (String) request.getAttribute("msg");
			if (msg != null) {
	%>
	<script language="javascript">
		alert('<%=msg%>');
	</script>
	<%}%>
	<script language="javascript">
		function change()
		{
		 create.createButton.disabled="true";
		 create.createButton.value="���ڴ������Ժ�...";
		}
	</script>
	<body>
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ���ɿ�����Ϣ </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div>
			<form name="create" method="post" action="workInfo.do?method=createWorkInfo">
				<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
					<tr>
						<td height="40" align="left" valign="middle" class="tdborder02">
							ѧ/����:
							<input class="input_box" style="width:100" maxlength=20 name="stuEmpNo" value="<c:out value='${stuEmpNo}' />" >
							&nbsp;&nbsp;
							��&nbsp;&nbsp;��:
							<select name="deptId" style="width: 150">
								<option value="">
									����
								</option>
								<c:forEach var="department" items="${departmentTree}">
									<option value="<c:out value="${department.deptId}"/>">
										<c:out value="${department.deptName}" />
									</option>
								</c:forEach>
							</select>
							&nbsp;&nbsp;
							���ڷ�Χ:
							<input class="input_box" style="width:80" maxlength=20 name="startDate" readonly="readonly" value="<c:out value='${startDate}' />" onclick="change();">
							<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
							<input class="input_box" style="width:80" maxlength=20 name="endDate" readonly="readonly" value="<c:out value='${endDate}' />" onclick="change();">
							<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
							<script type="text/javascript">
                				new calendar("startDate", "calBegin", "%Y-%m-%d");
                				new calendar("endDate", "calEnd", "%Y-%m-%d");
            				</script>
						    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<input name="createButton" type="button" class="submitButton" value="���ɿ�������" onclick="create.createButton.value='���ڴ������Ժ�...';create.createButton.disabled='true';create.submit();">
						</td>
					</tr>
				</table>
				<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
					<tr>
						<td height="40" align="center" valign="middle" class="tdborder02">
							<input name="Submit" type="button" class="submitButton" value="�����Զ��������ݹ���" <c:out value='${openDisabled}' default="disabled"/> onclick="window.location.href='workInfo.do?method=openTread';">
							&nbsp;&nbsp;
							<input name="Submit" type="button" class="submitButton" value="�ر��Զ��������ݹ���" <c:out value='${closeDisabled}' default="disabled"/> onclick="window.location.href='workInfo.do?method=closeTread';">
						</td>
					</tr>
				</table>
			</form>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>