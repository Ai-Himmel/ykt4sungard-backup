<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
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
			<strong> <font class="medium"> ������������ </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="40" align="left" valign="middle" class="tdborder02">
					<input name="Submit" type="button" class="submitButton" value=" �� �� " onclick="window.location.href='location.do?method=viewLocation';">
					&nbsp;&nbsp;
					<input name="Submit" type="button" class="submitButton" value=" ɾ �� " onclick="javascript:batch_del(document.forms.ec,'��������','<c:url value="location.do?method=deleteLocation" />');">
				</td>
			</tr>
			<div id=lineDiv class="hrLine">
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td class="tdborderLine"></td>
					</tr>
				</table>
			</div>
			<div id="tableDiv"> 
				<ec:table items="locations" var="location" rowsDisplayed="50" action="location.do?method=listLocation">
					<ec:exportXls fileName="locations.xls" tooltip="���� Excel" />
					<ec:row>
						<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="5%" style="text-align: left">
							<input type="checkbox" name="itemlist" value="${location.id}" style="border:0px" />
						</ec:column>
						<ec:column property="id" title="ID" width="30%" />
						<ec:column property="name" title="����" width="55%" />
						<ec:column property="update" title="�޸�" width="10%" sortable="false">
							<a href="location.do?method=viewLocation&locationId=${location.id}">�޸�</a>
						</ec:column>
					</ec:row>
				</ec:table>

			</div>
<%String msg = (String) request.getAttribute("msg");
	if (msg != null) {
%>
<script language="javascript">
	alert('<%=msg%>');
	window.location.href="workConf.do?method=search";
</script>
	<%}%>