<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>上海电大校园一卡通考勤管理系统</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<SCRIPT language=javascript>


function back(){
window.open('login.htm','_self');
}
function on_FD(){
	document.all("sd").click();
}
function on_validate(para){
	if(document.all(para).value!=''){
		document.forms[0].submit();
	}
	else{
		alert('请选择日期');
	}
}
function validate()
{
	var startDate=noSeat.startDate.value;
	var endDate=noSeat.endDate.value;
	if(startDate==''||endDate=='')
	{
		alert("请将日期输入完整");
		return false;
	}
	if(startDate>endDate)
	{		
		alert("开始日期不能大于结束时间");
		return false;
	}
}
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 非坐班人员考勤日志查询 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<jodd:form bean="request">
				<form action="searchNoSeatWorkInfo.do?method=searchNoSeatWorkInfo" method="post" name="noSeat" onsubmit="return validate();">
					&nbsp; 开始日期:
					<input class="input_box" maxlength=20 name="startDate" readonly="readonly" value="<%=request.getParameter("startDate")==null?"":request.getParameter("startDate")%>">
					&nbsp;
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
					&nbsp; 结束日期:
					<input name="endDate" class="input_box" maxlength=20 readonly="readonly" value="<%=request.getParameter("endDate")==null?"":request.getParameter("endDate")%>">
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
					<script type="text/javascript">
		                new calendar("startDate", "calBegin", "%Y-%m-%d");
		                new calendar("endDate", "calEnd", "%Y-%m-%d");
            		</script>
					&nbsp; &nbsp; 部门:&nbsp;
					<select name="deptId">
						<option value="">
							所有
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptTitle}" />
							</option>
						</c:forEach>
					</select>
					<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
					<a href="#" onclick="if(validate()==false) return false;noSeat.submit();">查询</a> &nbsp; &nbsp;&nbsp;&nbsp;
					<input name="Submit" width="50" type="button" class="button_nor" value="生成考勤信息" onclick="noSeat.action='noSeatWorkInfo.do?method=dealWithNoSeatClerkInfo';noSeat.submit();">
				</form>
			</jodd:form>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="noSeatWorkInfoList" var="dutytime" rowsDisplayed="50" action="searchNoSeatWorkInfo.do?method=searchNoSeatWorkInfo">
				<ec:exportXls fileName="noSeatWorkInfoList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="department.name" title="部门" width="60" />
					<ec:column property="clerk.clerkname" title="人员" width="60" />
					<ec:column property="ondutytime" title="上班时间" width="120" />
					<ec:column property="offdutytime" title="下班时间" width="120" />
				</ec:row>
			</ec:table>

		</div>
	</body>
</html>
