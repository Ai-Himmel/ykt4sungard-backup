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
			<strong> <font class="medium"> 考勤制度详细信息 </font> </strong>
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
				<tr align="center" valign=center>
					<td align="right" valign="middle" bgcolor="#D1DAE9" width=15%>
						班次名称:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${typeName}" />
					</td>
				</tr>
				<tr align="center" valign=center>
					<td align="right" valign="middle" bgcolor="#D1DAE9" width=15%>
						考勤日期:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${confDate}" />
					</td>
				</tr>
				<tr align="center" valign=center>
					<td align="right" valign="middle" bgcolor="#D1DAE9">
						是否上班:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:choose>
							<c:when test="${ifWORK=='1'}">
								上班
							</c:when>
							<c:otherwise>
								不上班
							</c:otherwise>
						</c:choose>
					</td>
				</tr>

				<tr align="center" valign=center>
					<td align="right" valign="middle" bgcolor="#D1DAE9">
						工作时间:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${workTimeDetail}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						考勤制度:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${workConfDetail}" />
					</td>
				</tr>
				<tr align="center" valign=center>
					<td valign="middle">
					</td>
					<td valign="middle" align="center">
						<input type="button" value=" 返 回 " class="submitButton" onClick="history.back();" />
					</td>
				</tr>
			</table>
		</div>
	</body>
</html>
