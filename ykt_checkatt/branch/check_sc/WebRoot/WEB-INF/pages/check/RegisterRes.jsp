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
	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> <c:out value="${msg}" /> </font> </strong>
		</div>
		<div id="tableDiv">
			<ec:table items="leaveList" var="leave" rowsDisplayed="10" action="leaveRegister.do?method=register">
				<ec:exportXls fileName="leaveList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="STUEMP_NO" title="学/工号" width="60" />
					<ec:column property="CUT_NAME" title="姓名" width="60" />
					<ec:column property="STARTDATE" title="请假开始日期" width="90" />
					<ec:column property="STARTTIME" title="请假开始时间" width="90" />
					<ec:column property="ENDDATE" title="请假结束日期" width="90" />
					<ec:column property="ENDTIME" title="请假结束时间" width="90" />
					<ec:column property="OPER_DATE" title="操作日期" width="90" />
					<ec:column property="OPER_TIME" title="操作时间" width="90" />
					<ec:column property="leavetype" title="请假类型" width="90" />
				</ec:row>
			</ec:table>
		</div>
		<P></P>
		<div align="center">
			<input type="button" value=" 返 回 " class="submitButton" onclick="<c:out value='${url}'/>" />
		</div>