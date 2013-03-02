<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<title>��ϸ��Ϣ</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>


	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ���������ϸ��Ϣ </font> </strong>
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
						��������������:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportDetail.repCustName}"/>
					</td>
				</tr>
				
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						������ѧ/����:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportDetail.STUEMP_NO}"/>
					</td>
				</tr>

				<tr align="center" valign="middle">
					<td align="right" valign="middle" bgcolor="#D1DAE9" width=15%>
						����������:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportDetail.CUST_NAME}" />
					</td>
				</tr>
				<tr align="center" valign="middle">
					<td align="right" valign="middle" bgcolor="#D1DAE9">
						����ʱ��:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						
						<c:out value="${leaveReportDetail.REPROT_DATE}" />
						--<c:out value="${leaveReportDetail.REPORT_TIME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						������:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.LEAVE_ID}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						���ԭ��:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.LEAVEINFO}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						��ٿ�ʼʱ��:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.LEAVE_BEGINDATE}" />
						--<c:out value="${leaveReportDetail.LEAVE_BEGINTIME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						��ٽ���ʱ��:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.LEAVE_ENDDATE}" />
						--<c:out value="${leaveReportDetail.LEAVE_ENDTIME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						�Ƿ�����:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.IFCHECK}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						�Ƿ�ͬ�����:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.IFAGREE}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						������:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.CHECKNAME}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						����ʱ��:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.CHECKDATE}"/>
						--<c:out value="${leaveReportDetail.CHECKTIME}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						������Ϣ:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportDetail.COMMENTS}"/>
					</td>
				</tr>
				<tr align="center" valign="middle">
					<td valign="middle">
					</td>
					<td valign="middle" align="center">
						<input type="button" value=" �� �� " class="submitButton" onClick="history.back();" />
					</td>
				</tr>
			</table>
		</div>
	</body>
</html>
