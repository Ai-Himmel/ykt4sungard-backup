<%@page pageEncoding="GBK" import="org.king.check.vo.*,java.util.*"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>复旦大学校园一卡通考勤管理系统</title>
		<%String msg = (String) request.getAttribute("msg");
			if (msg != null) {

				%>
		<SCRIPT language=javascript>
		alert('<%=msg%>');
</SCRIPT>
		<%}%>

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
	var startDate=noSeat.dutyInfo_startDate.value;
	var endDate=noSeat.dutyInfo_endDate.value;
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
	<body>

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 坐班人员考勤流水查询 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<form action="checkStatic.do?method=getCheckSerial" method="post" name="noSeat" onsubmit="return validate();">
				<jodd:form bean="request">
					部&nbsp;&nbsp;门:
					<select name="dutyInfo_deptId" style="width: 150">
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
					<input class="text" type="text" name="dutyInfo_stuempNo" size="20" style="width:80">
					&nbsp;&nbsp;
					开始日期
					<input class="input_box" style="width:80" name="dutyInfo_startDate" readonly="readonly" value="<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>">
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
					&nbsp;&nbsp;&nbsp;
					结束日期
					<input name="dutyInfo_endDate" class="input_box" style="width:80" readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">

					<script type="text/javascript">
					    new calendar("dutyInfo_startDate", "calBegin", "%Y-%m-%d");
		                new calendar("dutyInfo_endDate", "calEnd", "%Y-%m-%d");				
		            </script>
					&nbsp;&nbsp;
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
			<ec:table items="checkSerial" var="clerk" rowsDisplayed="15" action="checkStatic.do?method=getCheckSerial">
				<ec:exportXls  fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="stuemp_no" 
						headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						escapeAutoFormat="true"
						sortable="false"
						title="学/工号" 
						width="100"
						/>
					
					<ec:column property="cut_name" 
						headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title="姓    名" 
						width="100" 
					/>
					<ec:column property="dept_name" 
						headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title="部    门" 
						width="200" 
					/>
					<ec:column property="check_date" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="考勤日期" 
						width="80" 
					/>
					<ec:column property="week" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="星期" 
						width="40" 
					/>
					<ec:column property="fact_ontime1" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="上班时间一" 
						width="70" 
					/>
					<ec:column property="fact_offtime1" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="下班时间一" 
						width="70" 
					/>
					<ec:column property="fact_ontime2" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="上班时间二" 
						width="70" 
					/>
					<ec:column property="fact_offtime2" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="下班时间二" 
						width="70" 
					/>
					<ec:column property="fact_ontime3" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="上班时间三" 
						width="70" 
					/>
					<ec:column property="fact_offtime3" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="下班时间三" 
						width="70" 
					/>
					<ec:column property="fact_ontime4" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="上班时间四" 
						width="70" 
					/>
					<ec:column property="fact_offtime4" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="下班时间四" 
						width="70" 
					/>
				</ec:row>
			</ec:table>

		</div>
	</body>
</html>
