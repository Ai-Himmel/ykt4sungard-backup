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

			<form name="addConf" action="workConf.do?method=update" method="post" onsubmit="return check();">
				<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium"> �����ƶ��޸� </font> </strong>
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
							<input type="hidden" name="add_workConfId" value="<c:out value='${workConf.workconfId}' />" />
							<td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium">���ڲ�������</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="add_confName" class="input_box" maxlength=20 value="<c:out value='${workConf.workconfName}' />">
								<font color=#ff0000>*</font>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> ����ٵ� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="add_permitLateTime" class="input_box" maxlength=5 onblur="count(addConf.add_permitLateTime)" value="<c:out value='${workConf.overdueTime}' />">
								<font color=#ff0000>*</font>����
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> �������� </span>
							</td>
							<td align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="add_permitEarly" class="input_box" maxlength=5 onblur="count(addConf.add_permitEarly)" value="<c:out value='${workConf.leaveearlyTime}' />">
								<font color=#ff0000>*</font>����
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> �ϰ���ǰ�򿨲������� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="add_ondutyAdvancedTime" class="input_box" maxlength=5 value="<c:out value='${workConf.overTime}' />" onblur="count(addConf.add_ondutyAdvancedTime)">
								<font color=#ff0000>*</font>����
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> �°��ͺ�򿨲������� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="add_offDutyLastTime" class="input_box" maxlength=5 value="<c:out value='${workConf.delayTime}' />" onblur="count(addConf.add_offDutyLastTime)">
								<font color=#ff0000>*</font>����
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> У��ʱ�� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="add_checkTime" class="input_box" maxlength=5 value="<c:out value='${workConf.checkTime}' />" onblur="count(addConf.add_checkTime)">
								<font color=#ff0000>*</font>����
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="submit" class="submitButton" value=" �� �� ">
								<input name="Submit22" type="button" class="submitButton" value=" ȡ �� " onclick="history.back();">

							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</form>
	</table>
</html>
