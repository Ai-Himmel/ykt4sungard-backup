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
			<strong> <font class="medium"> 手工考勤修改 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
		<form name="manualModify" method="post" action='workInfo.do?method=manualRegisterModify' >
			<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
				<INPUT type="hidden" name=register_seriId value="<c:out value='${serial_id}'/>">
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						学/工号:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${STUEMP_NO}"/>
					</td>
				</tr>

				<tr align="center" valign="middle">
					<td align="right" valign="middle" bgcolor="#D1DAE9" width=15%>
						姓  名:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${CUT_NAME}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						所属部门:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<c:out value="${DEPT_NAME}" />
					</td>
				</tr>
				<tr>
					<td width=10% height="20" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
						考勤日期
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<input name="register_sDate" class="input_box" maxlength=20 style="width:100" readonly="readonly" value="<c:out value="${ATT_DATE}"/>">
						<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
					</td>
					<script type="text/javascript">
	    			new calendar("register_sDate", "calBegin", "%Y-%m-%d");			
	   				</script>
					
				</tr>
				<tr>
					<td width=10% height="20" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
						考勤时间
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<p></p>
						<select name="register_startHour">
							<%for (int i = 0; i < 24; i++) {
								if (i==Integer.parseInt(request.getAttribute("ATT_HOUR").toString())){
							%>
							<option value="<%=i%>" selected="selected">
								<%=i%>
							</option>
							<%}else{%>
							<option value="<%=i%>" >
								<%=i%>
							</option>
							<%}}%>
						</select>
						点
						<select name="register_startMin">
							<%for (int i = 0; i < 60; i++) {
								if (i==Integer.parseInt(request.getAttribute("ATT_MIN").toString())){
							%>
							<option value="<%=i%>" selected="selected">
								<%=i%>
							</option>
							<%}else{%>
							<option value="<%=i%>" >
								<%=i%>
							</option>
							<%}}%>
						</select>
						分
				</tr>
				<tr align="left" valign="middle">
					<td valign="middle"/>
					<td valign="middle" align="center">
						<input type="submit" value=" 确 定 " class="submitButton"/>
						<input type="button" value=" 返 回 " class="submitButton" onClick="history.back();" />
					</td>
				</tr>
			</table>
		</form>
		</div>
	</body>
</html>
