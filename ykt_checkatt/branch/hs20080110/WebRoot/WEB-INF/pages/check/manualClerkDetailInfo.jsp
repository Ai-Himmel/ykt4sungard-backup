<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<title>详细信息</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>


	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 手工考勤详细信息 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						学/工号:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportDetail.stuempNo}"/>
					</td>
				</tr>

				<tr align="center" valign="middle">
					<td align="right" valign="middle" bgcolor="#D1DAE9" width=15%>
						姓名:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportDetail.custName}" />
					</td>
				</tr>
				<tr align="center" valign="middle">
					<td align="right" valign="middle" bgcolor="#D1DAE9">
						考勤日期:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						
						<c:out value="${leaveReportDetail.clerkDate}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						考勤时间:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.minTime}" />--
						<c:out value="${leaveReportDetail.maxTime}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						操作员:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.operName}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						操作日期:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.operDate}" />
					</td>
				</tr> 
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						操作时间:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.operTime}" />
					</td>
				</tr> 
				<tr align="center" valign="middle">
					<td valign="middle">
					</td>
					<td valign="middle" align="center">
						<input type="button" value=" 返 回 " class="submitButton" onClick="history.back();" />
					</td>
				</tr>
			</table>
		</div>
	</body>
</html>
