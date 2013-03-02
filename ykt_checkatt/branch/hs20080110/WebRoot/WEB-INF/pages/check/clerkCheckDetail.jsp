<%@ page contentType="text/html;charset=UTF-8"%>
<%@ include file="/pages/common/taglibs.jsp"%>


<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>

	<body>

		<div id="titleDiv" class="pageTitle">
			考勤明细记录
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="tableDiv">
			<ec:table items="checkDetail" var="clerk" rowsDisplayed="15" action="clerkManager.do?method=queryClerkCheckDetail">
				<ec:exportXls fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="cust_id" title="客户号" sortable="false" viewsAllowed="html" width="40" style="text-align: center">
					</ec:column>
					
					<ec:column property="stuemp_no" title="学工号" width="80" escapeAutoFormat="true">
					</ec:column>
					<ec:column property="cut_name" title="姓名" width="80" escapeAutoFormat="true">
					</ec:column>
					<ec:column property="att_date" title="考勤日期" width="80" />
					<ec:column property="attnum" title="考勤次数" width="80" />
					<ec:column property="手工考勤" title="手工考勤" width="80" >
						<c:choose>
							<c:when test="${clerk.haveManual==0}">
								无
							</c:when>
							<c:when test="${clerk.haveManual>0}">
								<a href="searchNoSeatWorkInfo.do?method=goManualDetailInfo&custId=${clerk.cust_id}&clerkDate=${clerk.att_date}&minTime=&maxTime=">有手工考勤</a>
							</c:when>
							<c:otherwise>
								无
							</c:otherwise>
						</c:choose>
					</ec:column>
				</ec:row> 
			</ec:table>

		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		
		<a href="workInfo.do?method=goMenualRegister">返回手工考勤</a>
</body>

</html>

