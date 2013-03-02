<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>������ѧУ԰һ��ͨ���ڹ���ϵͳ</title>
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
				<ec:exportXls fileName="leaveList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="STUEMP_NO" title="ѧ/����" width="60" />
					<ec:column property="CUT_NAME" title="����" width="60" />
					<ec:column property="STARTDATE" title="��ٿ�ʼ����" width="90" />
					<ec:column property="STARTTIME" title="��ٿ�ʼʱ��" width="90" />
					<ec:column property="ENDDATE" title="��ٽ�������" width="90" />
					<ec:column property="ENDTIME" title="��ٽ���ʱ��" width="90" />
					<ec:column property="OPER_DATE" title="��������" width="90" />
					<ec:column property="OPER_TIME" title="����ʱ��" width="90" />
					<ec:column property="leavetype" title="�������" width="90" />
				</ec:row>
			</ec:table>
		</div>
		<P></P>
		<div align="center">
			<input type="button" value=" �� �� " class="submitButton" onclick="<c:out value='${url}'/>" />
		</div>