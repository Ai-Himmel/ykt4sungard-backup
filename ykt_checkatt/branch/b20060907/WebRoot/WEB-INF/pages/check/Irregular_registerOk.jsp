<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
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

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
�Ǽǳɹ�
</font>
</strong>
</div>
<div id="tableDiv">
         <ec:table items="irreList" var="irregular" rowsDisplayed="10" action="irregularRest.do?method=register">
				<ec:exportXls fileName="irreList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="clerkname" title="��Ա" width="60" />
					<ec:column property="startdate" title="�Ӱ࿪ʼʱ��" width="95" />
					<ec:column property="enddate" title="�Ӱ��������" width="100" />
				</ec:row>
			</ec:table>
</div>
<div align="center">
<input type="button" value="����" class="button_nor" onclick="window.location.href='irregularRest.do?method=goIrregularRest'"/>
</div>