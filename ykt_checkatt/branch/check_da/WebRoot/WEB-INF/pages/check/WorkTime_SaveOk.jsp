<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
	<body>
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

			<div id="titleDiv" class="pageTitle">
				<strong> <font class="medium"> ����ʱ�����ã���ӳɹ� </font> </strong>
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
								<span class="medium">����ʱ������</span>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.worktimeName}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �ϰ�ʱ��1 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.ontime1}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �°�ʱ��1 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.offtime1}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �ϰ�ʱ��2 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.ontime2}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �°�ʱ��2 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.offtime2}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �ϰ�ʱ��3 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.ontime3}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �°�ʱ��3 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.offtime3}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �ϰ�ʱ��4 </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<c:out value="${workTimeComf.ontime4}" />
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �°�ʱ��4 </span>
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
								<input name="Submit22" type="button" class="submitButton" value=" �� �� " onclick="window.location.href='workTime.do?method=search'">
							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</table>
</html>
