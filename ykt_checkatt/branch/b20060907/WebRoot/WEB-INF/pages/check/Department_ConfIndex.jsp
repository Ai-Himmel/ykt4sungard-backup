<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
<head>
<title>复旦大学校园一卡通考勤管理系统</title>
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
	var startDate=deptConf.search_startDate.value;
	var endDate=deptConf.search_endDate.value;
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
<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
部门排班信息
</font>
</strong>
</div>
<tr>
&nbsp;
</tr>
<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>
<div id="filterDiv" style="text-align: left;">
  <form action="department.do?method=search" method="post" name="deptConf" onsubmit="return validate();">
  <jodd:form bean="request">
&nbsp;
<span class="medium">
开始日期
</span> &nbsp;
<input class="input_box"  maxlength=20 name="search_startDate" readonly="true" value="<c:out value='${startDate}'/>">
&nbsp;
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
&nbsp;	
结束日期

&nbsp;
<input name="search_endDate" class="input_box"  maxlength=20  readonly="true" value="<c:out value='${endDate}'/>">
<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
           <script type="text/javascript">
                new calendar("search_startDate", "calBegin", "%Y-%m-%d");
                new calendar("search_endDate", "calEnd", "%Y-%m-%d");
            </script>
&nbsp;
&nbsp;
部门:&nbsp;
					<select name="search_deptId">
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
<a href="#" onclick="if(validate()==false) return false;deptConf.submit();">查询</a>
&nbsp;&nbsp;&nbsp;
<input type="button" value="添加排班计划" onclick="window.location.href='department.do?method=addConfSltDpt';"/>
</jodd:form>
</form>
</div>
<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>
		<div id="tableDiv">
			<ec:table items="dpConfList" var="dptconf" rowsDisplayed="5" action="department.do?method=search">
				<ec:exportXls fileName="deptConfList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="dptname" title="部门" width="60" />
                    <ec:column property="startdate" title="开始时间" width="60" />
					<ec:column property="enddate" title="结束时间" width="60" />
					<ec:column property="wconfname" title="考勤制度" width="120" />
					<ec:column property="tconfname" title="工作时间" width="120" />
					
				</ec:row>
			</ec:table>

		</div>
</body>
</html>
