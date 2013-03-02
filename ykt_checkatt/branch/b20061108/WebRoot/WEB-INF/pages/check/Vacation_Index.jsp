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
<% String msg=(String)request.getAttribute("msg");
if(msg!=null)
{
%>
<script language="javascript">
	alert('<%=msg%>');
</script>
<%}%>
<body>
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
公休日参数设置
</font>
</strong>
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
      <td height="40" align="left" valign="middle" class="tdborder02"> <input name="Submit" type="button" class="button_nor" value="添加" onclick="window.location.href='vacation.do?method=addVacation_step1';" > &nbsp; <input name="Submit" type="button" class="button_nor" value="查看全部" onclick="window.location.href='vacation.do?method=search';"> 
      </td>
    </tr>
<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>

<div>
<form name="searchVacation" action="vacation.do?method=search" method="post">
公休假日名称:&nbsp;
<input name="search_vacationName" class="input_box"  maxlength=20>&nbsp; 
<input name="Submit" type="submit" class="button_nor" value="查 询" >     
</form>
</div>

<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>
<div id="operationDiv"  style="display :<c:out value='${show}' default='none'/>">
			<%@ include file="/pages/common/messages.jsp"%>
			<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_del(document.forms.ec,'公休假日','<c:url value="vacation.do?method=delete" />');">删 除</A> </span>
		</div>
<div id="tableDiv" style="display :<c:out value='${show}' default='none'/>">
			<ec:table items="vacationList" var="vacation" rowsDisplayed="5" action="vacation.do?method=search">
				<ec:exportXls fileName="VacationList.xls" tooltip="导出 Excel" />
				<ec:row>
				<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${vacation.vid}" style="border:0px" />
					</ec:column>
					<ec:column property="vname" title="假日名称" width="80" />
					<ec:column property="startdate" title="开始时间" width="60" />
					<ec:column property="enddate" title="结束时间" width="80" />
					<ec:column property="dname" title="部门" width="120" />
					<ec:column property="update" title="修改" width="40" sortable="false">
					<a href="vacation.do?method=update_step1&vacationid=${vacation.vid}">修改</a>
					</ec:column>
				</ec:row>
			</ec:table>

</div>