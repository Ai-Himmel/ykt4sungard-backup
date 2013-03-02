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
			<strong> <font class="medium"> 请假申请详细信息 </font> </strong>
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
						代替申请人姓名:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportDetail.repCustName}"/>
					</td>
				</tr>
				
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						申请人学/工号:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportDetail.STUEMP_NO}"/>
					</td>
				</tr>

				<tr align="center" valign="middle">
					<td align="right" valign="middle" bgcolor="#D1DAE9" width=15%>
						申请人姓名:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportDetail.CUST_NAME}" />
					</td>
				</tr>
				<tr align="center" valign="middle">
					<td align="right" valign="middle" bgcolor="#D1DAE9">
						申请时间:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						
						<c:out value="${leaveReportDetail.REPROT_DATE}" />
						--<c:out value="${leaveReportDetail.REPORT_TIME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						请假类别:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.LEAVE_ID}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						请假原因:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.LEAVEINFO}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						请假开始时间:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.LEAVE_BEGINDATE}" />
						--<c:out value="${leaveReportDetail.LEAVE_BEGINTIME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						请假结束时间:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.LEAVE_ENDDATE}" />
						--<c:out value="${leaveReportDetail.LEAVE_ENDTIME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						是否审批:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.IFCHECK}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						是否同意请假:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.IFAGREE}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						审批人:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.CHECKNAME}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						审批时间:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.CHECKDATE}"/>
						--<c:out value="${leaveReportDetail.CHECKTIME}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						审批信息:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.COMMENTS}"/>
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
