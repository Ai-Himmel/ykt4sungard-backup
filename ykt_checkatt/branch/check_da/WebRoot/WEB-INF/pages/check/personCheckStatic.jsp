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

function check()
{    
	if(document.all.cs_stuNo.value=='')
	{
		alert('请输入考勤人员的学工号！');
		return false;
	}
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
			<strong> <font class="medium"> 个人出勤情况报表 </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="filterDiv" style="text-align: left;">
			<form name="clerkstatic" action="checkStatic.do?method=getPersonCheckStatic" method="post" onsubmit="return check();">
				<jodd:form bean="request">
                       学工号:&nbsp;<td>
						&nbsp;&nbsp;&nbsp;&nbsp;
					</td>
					<input class="text" type="text" name="cs_stuNo" size="20" style="width:120">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;					
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
			<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#445386 bordercolordark=#ffffff id=submenu1>
				<tbody>
					<tr valign=middle>
						<td colspan="2" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader1">
							姓名：
							<%=request.getAttribute("clerkName") == null ? "": request.getAttribute("clerkName")%>
							<br>
							学/工号：
							<%=request.getAttribute("stuempNo") == null ? "": request.getAttribute("stuempNo")%>
							<br>
							部门：
							<%=request.getAttribute("deptName") == null ? "": request.getAttribute("deptName")%>
							<br>
							统计日期：
							<%=request.getAttribute("startDate") == null ? "": request.getAttribute("startDate")%>
							～
							<%=request.getAttribute("endDate") == null ? "": request.getAttribute("endDate")%>
						</td>
						<td colspan="3" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader1">
							应上班时间：
							<%=request.getAttribute("workValue") == null ? "0": request.getAttribute("workValue")%>
							小时&nbsp;&nbsp;&nbsp;&nbsp;实际上班时间：
							<%=request.getAttribute("factWorkValue") == null ? "0": request.getAttribute("factWorkValue")%>
							小时<br>
							请假时间：
							<%=request.getAttribute("leaveTimeValue") == null ? "0": request.getAttribute("leaveTimeValue")%>
							小时&nbsp;&nbsp;&nbsp;&nbsp;缺席时间：
							<%=request.getAttribute("leaveValue") == null ? "0": request.getAttribute("leaveValue")%>
							小时<br>
							迟到时间：
							<%=request.getAttribute("delayValue") == null ? "0": request.getAttribute("delayValue")%>
							小时&nbsp;&nbsp;&nbsp;&nbsp;早退时间：
							<%=request.getAttribute("leaveEarlyValue") == null ? "0": request.getAttribute("leaveEarlyValue")%>
							小时<br>
							加班时间：
							<%=request.getAttribute("overValue") == null ? "0": request.getAttribute("overValue")%>
							小时&nbsp;&nbsp;&nbsp;&nbsp;双休日加班时间：
							<%=request.getAttribute("twoRestValue") == null ? "0": request.getAttribute("twoRestValue")%>
							小时
						</td>
					</tr>
				</tbody>
			</table>
		</div>
		<c:if test="${ifOffice=='1'}">
		<div id="tableDiv">
			<ec:table items="checkDetail" var="clerk" rowsDisplayed="50" action="checkStatic.do?method=getPersonCheckStatic">
				<ec:exportXls  fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="STUEMP_NO" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="学/工号" 
						width="200"
						/>
					
					<ec:column property="CUT_NAME" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="姓    名" 
						width="250" 
					/>
					<ec:column property="CHECK_DATE" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="考勤日期" 
						width="150" 
					/>
					<ec:column property="FACT_ONTIME1" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="上班一" 
						width="100" 
					/>
					<ec:column property="FACT_OFFTIME1" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="下班一" 
						width="100" 
					/>
					<ec:column property="FACT_ONTIME2" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="上班二" 
						width="100" 
					/>
					<ec:column property="FACT_OFFTIME2" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="下班二" 
						width="100" 
					/>
					<ec:column property="FACT_ONTIME3" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="上班三" 
						width="100" 
					/>
					<ec:column property="FACT_OFFTIME3" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="下班三" 
						width="100" 
					/>
					<ec:column property="FACT_ONTIME4" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="上班四" 
						width="100" 
					/>
					<ec:column property="FACT_OFFTIME4" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="下班四" 
						width="100" 
					/>
				</ec:row>
			</ec:table>

		</div>
		</c:if>
		<c:if test="${ifOffice=='2'}">
		<div id="tableDiv">
			<ec:table items="checkDetail" var="clerk" rowsDisplayed="50" action="checkStatic.do?method=getPersonCheckStatic">
				<ec:exportXls  fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="STUEMP_NO" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="学/工号" 
						width="200"
						/>
					
					<ec:column property="CUT_NAME" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="姓    名" 
						width="250" 
					/>
					<ec:column property="CHECK_DATE" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="考勤日期" 
						width="200" 
					/>
					<ec:column property="FACT_ONTIME" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="上班时间" 
						width="200" 
					/>
					<ec:column property="FACT_OFFTIME" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="下班时间" 
						width="200" 
					/>
				</ec:row>
			</ec:table>

		</div>
		</c:if>
	</body>
</html>
