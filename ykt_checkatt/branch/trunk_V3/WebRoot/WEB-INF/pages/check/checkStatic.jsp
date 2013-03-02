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
		<SCRIPT language=javascript>


function back(){
window.open('login.htm','_self');
}

function check()
{    
	if(document.all.cs_startDate.value==''||document.all.cs_endDate.value=='')
	{
		alert('请将日期输入完整');
		return false;
	}
		if(document.all.cs_startDate.value>document.all.cs_endDate.value)
	{		
		alert("开始日期不能大于结束时间");
		return false;
	}

}

</SCRIPT>

	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 坐班考勤情况汇总表 </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="filterDiv" style="text-align: left;">
			<form name="clerkstatic" action="checkStatic.do?method=getCheckStatic" method="post" onsubmit="return check();">
				<jodd:form bean="request">
					部&nbsp;&nbsp;门:
					<select name="deptId" style="width: 150">
						<option value="">
							所有
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptName}" />
							</option>
						</c:forEach>
					</select>
					
					&nbsp;&nbsp;
                       学工号:&nbsp;
					<input class="text" type="text" name="cs_stuNo" size="20" style="width:80">
					&nbsp;&nbsp;
					开始日期
					<input class="input_box" style="width:100" name="cs_startDate" readonly="readonly" value="<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>">
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
					&nbsp;&nbsp;&nbsp;
					结束日期
					<input name="cs_endDate" class="input_box" style="width:100" readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">

					<script type="text/javascript">
					    new calendar("cs_startDate", "calBegin", "%Y-%m-%d");
		                new calendar("cs_endDate", "calEnd", "%Y-%m-%d");				
		            </script>
					&nbsp;&nbsp;&nbsp;&nbsp;
					<input name="Submit" type="submit" class="submitButton" value=" 查 询 ">

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
			<ec:table items="checkStaticStat" var="clerk" rowsDisplayed="12" action="checkStatic.do?method=getCheckStatic">
				<ec:exportXls  fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="stuemp_no" 
						headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						escapeAutoFormat="true"
						sortable="false"
						title="学/工号" 
						width="120"
						/>
					
					<ec:column property="cut_name" 
						headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title="姓    名" 
						width="120" 
					/>
					<ec:column property="dept_name" 
						headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title="部    门" 
						width="250" 
					/>
					<ec:column property="worktimeNum" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="应出勤次数" 
						width="100" 
					/>
					<ec:column property="checkNum" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="实出勤次数" 
						width="100" 
					/>
					<ec:column property="delayNum" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="迟到次数" 
						width="100" 
					/>
					<ec:column property="earlyNum" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="早退次数" 
						width="100" 
					/>
					<ec:column property="leaveNum" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="缺席次数" 
						width="100" 
					/>
				</ec:row>
			</ec:table>

		</div>
	</body>
</html>
