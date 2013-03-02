<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
	<%String msg = (String) request.getAttribute("msg");
			if (msg != null) {
	%>
	<script language="javascript">
		alert('<%=msg%>');
	</script>
	<%}%>
	<script language="javascript">
		function change()
		{
		 create.createButton.disabled="true";
		 create.createButton.value="正在处理，请稍候...";
		}
	</script>
	<body>
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 生成考勤信息 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div>
			<form name="create" method="post" action="workInfo.do?method=createWorkInfo">
				<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
					<tr>
						<td height="40" align="left" valign="middle" class="tdborder02">
							选择日期:
							<input class="input_box" style="width:80" maxlength=20 name="startDate" readonly="readonly" value="<c:out value='${startDate}' />" onclick="change();">
							<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
							<input class="input_box" style="width:80" maxlength=20 name="endDate" readonly="readonly" value="<c:out value='${endDate}' />" onclick="change();">
							<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
							&nbsp;
							<input name="createButton" type="button" class="button_nor" value="生成考勤数据" onclick="create.createButton.value='正在处理，请稍候...';create.createButton.disabled='true';create.submit();">
							<script type="text/javascript">
                				new calendar("startDate", "calBegin", "%Y-%m-%d");
                				new calendar("endDate", "calEnd", "%Y-%m-%d");
            				</script>
						<td height="40" align="left" valign="middle" class="tdborder02">

							<input name="Submit" type="button" class="button_nor" value="启动自动生成数据功能" <c:out value='${openDisabled}' default="disabled"/> onclick="window.location.href='workInfo.do?method=openTread';">
							&nbsp;
							<input name="Submit" type="button" class="button_nor" value="关闭自动生成数据功能" <c:out value='${closeDisabled}' default="disabled"/> onclick="window.location.href='workInfo.do?method=closeTread';">
						</td>
					</tr>
				</table>
			</form>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>