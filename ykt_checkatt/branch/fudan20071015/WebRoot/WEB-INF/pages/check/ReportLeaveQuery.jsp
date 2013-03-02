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
	var query_sDate=putin.query_sDate.value;
	var query_eDate=putin.query_eDate.value;
	var description=putin.register_description.value;

	if(query_sDate==''||query_eDate=='')
	{
		alert('请将日期输入完整');
		return false;
	}
		if(query_sDate>query_eDate)
	{		
		alert("开始日期不能大于结束时间");
		return false;
	}

}

</SCRIPT>

	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 请假申请查询 </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="filterDiv" style="text-align: left;">
			<form name="leaveCheck" action="leaveReportQuery.do?method=queryLeaveReport" method="post">
				<jodd:form bean="request">
						开始日期:
						<input name="query_sDate" class="input_box" maxlength=20 readonly="readonly" style="width:80" value="<c:out value='${beginDate}'/>">
						<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begindate" style="cursor:pointer">
						结束日期:
						<input name="query_eDate" class="input_box" maxlength=20 readonly="readonly" style="width:80" value="<c:out value='${endDate}'/>">
						<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="enddate" style="cursor:pointer">
						是否审批:
						<select name="query_ifcheck">
							<option value="-1">
								所有
							</option>
							<option value="1">
								已审批
							</option>
							<option value="0">
								未审批
							</option>
						</select>
						是否同意:
						<select name="query_ifagree">
							<option value="-1">
								所有
							</option>
							<option value="1">
								同意
							</option>
							<option value="0">
								不同意
							</option>
						</select>
						&nbsp;&nbsp;
						<input name="Submit" type="Submit" class="submitButton" value=" 查 询 ">&nbsp;&nbsp;&nbsp;
						<input name="reportLeave" type="button" style="color: red" class="submitButton" value="请假申请" onclick="window.location.href='leaveReportQuery.do?method=goLeaveReport';">
						&nbsp;&nbsp;
						<input name="reportLeave" type="button" style="color: red" class="submitButton" value="代替请假" onclick="window.location.href='leaveReportQuery.do?method=goReplaceLeaveReport';">
					<script type="text/javascript">
	    			new calendar("query_sDate", "calBegin", "%Y-%m-%d");	
	    			new calendar("query_eDate", "calEnd", "%Y-%m-%d");		
       				</script>
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
		
		<div id="tableDiv">
			<ec:table items="leaveReportList" var="leave" rowsDisplayed="15" action="leaveReportQuery.do?method=queryLeaveReport" form="leaveCheck">
				<ec:exportXls fileName="clerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column 
						property="REPROT_DATE" 
						title="请假日期" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
						width="120" 
						
					/>
					<ec:column 
						property="LEAVE_ID" 
						title="请假类型" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
						width="80" 
						
					/>
					<ec:column property="LEAVE_BEGINDATE" 
						title="开始日期" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
						width="120" 
					/>
					<ec:column property="LEAVE_BEGINTIME" 
						title="开始时间" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
					/>
					<ec:column property="LEAVE_ENDDATE" 
						title="结束日期" 
						width="120" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
					/>
					<ec:column property="LEAVE_ENDTIME" 
						title="结束时间" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
					/>
					<ec:column property="IFCHECK" 
						title="是否审批" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					/>
					<ec:column property="IFAGREE" 
						title="是否同意" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					/>
					<ec:column property="详细信息" 
						title="详细信息" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					>
						<a href="leaveReportQuery.do?method=leaveReportDetailInfo&leaveReportId=${leave.ID}">详细信息</a>
					</ec:column>
					<ec:column property="修改" 
						title="修改" 
						width="50" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					>
						<c:choose>
							<c:when test="${leave.IFAGREE=='同意'}">
								<a href=""></a>
							</c:when>
							<c:when test="${leave.IFAGREE=='不同意'}">
								<a href="leaveReportQuery.do?method=goLeaveReport&leaveReportId=${leave.ID}">修改</a>
							</c:when>
							<c:otherwise>
								<a href="leaveReportQuery.do?method=goLeaveReport&leaveReportId=${leave.ID}">修改</a>
							</c:otherwise>
						</c:choose>
					</ec:column>
					<ec:column property="删除" 
						title="删除" 
						width="50" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					>
						<c:choose>
							<c:when test="${leave.IFAGREE=='同意'}">
								<a href=""></a>
							</c:when>
							<c:when test="${leave.IFAGREE=='不同意'}">
								<a href="leaveReportQuery.do?method=deleteLeaveReport&leaveId=${leave.ID}">删除</a>
							</c:when>
							<c:otherwise>
								<a href="leaveReportQuery.do?method=deleteLeaveReport&leaveId=${leave.ID}">删除</a>
							</c:otherwise>
						</c:choose>
					</ec:column>
				</ec:row>
			</ec:table>
		</div>

	</body>
</html>
