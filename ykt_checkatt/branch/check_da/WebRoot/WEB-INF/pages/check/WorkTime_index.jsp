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
	<body>
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 工作时间设置 </font> </strong>
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
					<input name="Submit" type="button" class="submitButton" value=" 添 加 " onclick="window.location.href='workTime.do?method=addworkTime_step1';">
					&nbsp;
					<!-- 
					<input name="Submit" type="button" class="button_nor" value="查看全部" onclick="window.location.href='workTime.do?method=search';">
					<img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_del(document.forms.ec,'作休时间','<c:url value="workTime.do?method=delete" />');">删 除</A>
					-->
					&nbsp;&nbsp;&nbsp;&nbsp;
					<input name="Submit" type="button" class="submitButton" value=" 删 除 " onclick="javascript:batch_del(document.forms.ec,'作休时间','<c:url value="workTime.do?method=delete" />');">
					
				</td>
			</tr>
			<!-- hanjiwei delete it 20060913
			<div id=lineDiv class="hrLine">
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td class="tdborderLine"></td>
					</tr>
				</table>
			</div>

			<div>
				<form name="searchworkTime" action="workTime.do?method=search" method="post">
					作休时间名称:&nbsp;
					<input name="search_workTimeName" class="input_box" maxlength=20>
					&nbsp;
					<input name="Submit" type="submit" class="button_nor" value="查 询">
				</form>
			</div>
			-->

			<div id=lineDiv class="hrLine">
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td class="tdborderLine"></td>
					</tr>
				</table>
			</div>
			<!-- 
			<div id="operationDiv"> style="display :<c:out value='${show}' default='none'/>">
				<%@ include file="/pages/common/messages.jsp"%>
				<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_del(document.forms.ec,'作休时间','<c:url value="workTime.do?method=delete" />');">删 除</A> </span>
			</div>
			-->
			<div id="tableDiv" ><!-- style="display :<c:out value='${show}' default='none'/>">-->
				<ec:table items="workTimeList" var="workTime" rowsDisplayed="50" action="workTime.do?method=search">
					<ec:exportXls fileName="workTimeList.xls" tooltip="导出 Excel" />
					<ec:row>
						<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
							<input type="checkbox" name="itemlist" value="${workTime.worktimeId}" style="border:0px" />
						</ec:column>
						<ec:column property="worktimeName" title="工作时间名称" width="150" />
						<ec:column property="ontime1" title="上班一" width="40" />
						<ec:column property="offtime1" title="下班一" width="40" />
						<ec:column property="ontime2" title="上班二" width="40" />
						<ec:column property="offtime2" title="下班二" width="40" />
						<ec:column property="ontime3" title="上班三" width="40" />
						<ec:column property="offtime3" title="下班三" width="40" />
						<ec:column property="ontime4" title="上班四" width="40" />
						<ec:column property="offtime4" title="下班四" width="40" />
						<ec:column property="update" title="修改" width="40" sortable="false">
							<a href="workTime.do?method=update_step1&workTimeConfId=${workTime.worktimeId}">修改</a>
						</ec:column>
					</ec:row>
				</ec:table>

			</div>