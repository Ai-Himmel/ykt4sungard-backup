<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>上海电大校园一卡通考勤管理系统</title>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
	<body>
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

			<div id="titleDiv" class="pageTitle">
				<strong> <font class="medium"> 工作时间设置－添加成功 </font> </strong>
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
							<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium">工作时间名称</span>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.worktimeName}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 上班时间1 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.ontime1}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 下班时间1 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.offtime1}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 上班时间2 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.ontime2}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 下班时间2 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.offtime2}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 上班时间3 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.ontime3}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 下班时间3 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.offtime3}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 上班时间4 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.ontime4}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 下班时间4 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.offtime4}" />
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="button" class="submitButton" value=" 返 回 " onclick="window.location.href='workTime.do?method=search'">
							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</table>
</html>
