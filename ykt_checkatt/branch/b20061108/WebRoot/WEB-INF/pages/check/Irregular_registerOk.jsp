<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
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

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
登记成功
</font>
</strong>
</div>
<div id="tableDiv">
         <ec:table items="irreList" var="irregular" rowsDisplayed="10" action="irregularRest.do?method=register">
				<ec:exportXls fileName="irreList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="clerkname" title="人员" width="60" />
					<ec:column property="startdate" title="加班开始时间" width="95" />
					<ec:column property="enddate" title="加班结束日期" width="100" />
				</ec:row>
			</ec:table>
</div>
<div align="center">
<input type="button" value="返回" class="button_nor" onclick="window.location.href='irregularRest.do?method=goIrregularRest'"/>
</div>