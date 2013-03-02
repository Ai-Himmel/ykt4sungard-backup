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

			<form name="addConf" action="checkType.do?method=addCheckType" method="post" onsubmit="return check();">
				<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium"> 班次信息设置 </font> </strong>
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
								<span class="medium">班次信息名称</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="add_typeName" class="input_box" maxlength=40 width="60">
								<font color=#ff0000>*</font>
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="submit" class="submitButton" value=" 创 建 ">
								<input name="Submit22" type="button" class="submitButton" value=" 取 消 " onclick="history.back();">

							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</form>
	</table>
</html>
