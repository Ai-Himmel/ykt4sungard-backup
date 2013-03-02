<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>


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
			<strong> <font class="medium"> 班次信息设置 </font> </strong>
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
					<input name="Submit" type="button" class="submitButton" value=" 添 加 " onclick="window.location.href='checkType.do?method=addCheckType_step1';">
					&nbsp;&nbsp;
					<input name="Submit" type="button" class="submitButton" value=" 删 除 " onclick="javascript:batch_del(document.forms.ec,'班次信息','<c:url value="checkType.do?method=delete" />');">
				</td>
			</tr>
			<div id=lineDiv class="hrLine">
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td class="tdborderLine"></td>
					</tr>
				</table>
			</div>
			<!-- 
			<div>
				<form name="searchWorkConf" action="workConf.do?method=search" method="post">
					考勤参数名称:&nbsp;
					<input name="search_workConfName" class="input_box" maxlength=20>
					&nbsp;
					<input name="Submit" type="submit" class="button_nor" value="查 询">
				</form>
			</div>

			<div id=lineDiv class="hrLine">
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td class="tdborderLine"></td>
					</tr>
				</table>
			</div>
			
			<div id="operationDiv" style="display :<c:out value='${show}' default='none'/>">
				<%@ include file="/pages/common/messages.jsp"%>
				<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_del(document.forms.ec,'考勤制度','<c:url value="workConf.do?method=delete" />');">删 除</A> </span>
			</div>
			-->
			<div id="tableDiv"> <!-- style="display :<c:out value='${show}' default='none'/>"-->
				<ec:table items="checkTypeList" var="checkType" rowsDisplayed="12" action="checkType.do?method=search">
					<ec:exportXls fileName="leaveInfoList.xls" tooltip="导出 Excel" />
					<ec:row>
						<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="5%" style="text-align: center">
							<input type="checkbox" name="itemlist" value="${checkType.typeId}" style="border:0px" />
						</ec:column>
						<ec:column property="typeName" title="班次信息名称" width="85%" sortable="false"/>
						<ec:column property="update" title="修改" width="10%" sortable="false">
							<a href="checkType.do?method=update_step1&typeId=${checkType.typeId}">修改</a>
						</ec:column>
					</ec:row>
				</ec:table>

			</div>