<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
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

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<div id="tableDiv">
         <ec:table items="leaveDetailList" var="eaveDetail" rowsDisplayed="50" action="leaveInfo.do?method=viewLeaveDetail">
				<ec:exportXls fileName="leaveDetailList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="clerkname" title="����" width="60" />
					<ec:column property="startDate" title="��ʼ����" width="120" />
					<ec:column property="endDate" title="��������" width="120" />				
				</ec:row>
			</ec:table>
	</div>
</body>
</html>
