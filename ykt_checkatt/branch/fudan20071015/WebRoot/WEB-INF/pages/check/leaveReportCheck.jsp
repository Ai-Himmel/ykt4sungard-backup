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
			<strong> <font class="medium"> 请假申请审批 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            	<td align="center" valign="middle" ><A style="font-size:12pt;">请假申请详细信息</A></td>
          </tr>
        </table>
		
		<div id="tableDiv">
			<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						代替请假人姓名:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportCheck.repCustName}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						申请人学/工号:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportCheck.STUEMP_NO}"/>
					</td>
				</tr>

				<tr align="center" valign="middle">
					<td align="right" valign="middle" bgcolor="#D1DAE9" width=15%>
						申请人姓名:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${leaveReportCheck.CUST_NAME}" />
					</td>
				</tr>
				<tr align="center" valign="middle">
					<td align="right" valign="middle" bgcolor="#D1DAE9">
						申请时间:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						
						<c:out value="${leaveReportCheck.REPROT_DATE}" />
						--<c:out value="${leaveReportCheck.REPORT_TIME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						请假类别:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportCheck.LEAVE_ID}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						请假原因:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportCheck.LEAVEINFO}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						请假开始时间:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportCheck.LEAVE_BEGINDATE}" />
						--<c:out value="${leaveReportCheck.LEAVE_BEGINTIME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						请假结束时间:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportCheck.LEAVE_ENDDATE}" />
						--<c:out value="${leaveReportCheck.LEAVE_ENDTIME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						是否审批:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportCheck.IFCHECK}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						是否同意请假:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportCheck.IFAGREE}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						审批信息:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${leaveReportCheck.COMMENTS}"/>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
					</td>
				</tr>
			</table>
		    <table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td align="center" valign="middle"><A style="font-size:12pt;color: red;">审批意见</A></td>
              </tr>
            </table>
	<form name="leaveRegister" action="leaveReportCheck.do?method=saveLeaveReportCheck" method="post">
		<jodd:form bean="request">
		    <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
				<input type="hidden" name="check_leaveReportId" value="<c:out value="${leaveReportId}"/>">
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right" width=15%>
						是否同意请假:
					</td>
			        <td align="left"  bgcolor="#E7F1F5" align="left">
			          	<input type="radio" name="check_ifagree" value="1" checked="checked">同意
			          	<input type="radio" name="check_ifagree" value="0">不同意
			        </td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						审批内容:
					</td>
      				<td align="left" valign="middle" class="tableHeader3" >
      					<input name=check_comments class="input_box" maxlength=100 style="width:600">
      				</td>
				</tr>
				<tr align="center" valign="middle">
					<td valign="middle">
					</td>
					<td valign="middle" align="center">
						<input type="submit" value=" 审 批 " class="submitButton" />
						<input type="button" value=" 取 消 " class="submitButton" onClick="history.back();" />
					</td>
				</tr>
			</table>
		</jodd:form>
	</form>
		</div>
	</body>
</html>
