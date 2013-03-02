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
	<body>
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

			<div id="titleDiv" class="pageTitle">
				<strong> <font class="medium"> 考勤制度设置成功 </font> </strong>
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
								<span class="medium">考勤参数名称</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.workconfName}' />
							</td>
						</tr>
						<!--
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> 允许迟到 </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.overdueTime}' />
								分钟
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> 允许早退 </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.leaveearlyTime}' />
								分钟
							</td>
						</tr>
						-->
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> 上班提前打卡不允许超过 </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.overTime}' />
								分钟
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> 下班滞后打卡不允许超过 </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value='${workConf.delayTime}' />
								分钟
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								<input name="Submit22" type="submit" class="submitButton" value=" 返 回 " onclick="window.location.href='workConf.do?method=search'">

							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</table>
</html>
