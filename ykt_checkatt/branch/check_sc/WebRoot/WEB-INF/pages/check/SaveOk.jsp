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
	<body>
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

			<div id="titleDiv" class="pageTitle">
				<strong> <font class="medium"> �����ƶ����óɹ� </font> </strong>
			</div>
			<div id=lineDiv class="hrLine">
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td class="tdborderLine"></td>
					</tr>
				</table>
			</div>

			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr align="center" valign=center>
							<td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium">���ڲ�������</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.workconfName}' />
							</td>
						</tr>
						<!--
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> ����ٵ� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.overdueTime}' />
								����
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> �������� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.leaveearlyTime}' />
								����
							</td>
						</tr>
						-->
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> �ϰ���ǰ�򿨲������� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.overTime}' />
								����
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> �°��ͺ�򿨲������� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.delayTime}' />
								����
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								<input name="Submit22" type="submit" class="submitButton" value=" �� �� " onclick="window.location.href='workConf.do?method=search'">

							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</table>
</html>
