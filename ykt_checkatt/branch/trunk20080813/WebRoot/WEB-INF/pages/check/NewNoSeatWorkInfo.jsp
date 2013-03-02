<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.check.util.StringUtil" %>
<%@ page import="org.king.check.config.CommonConfig" %>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
	</head>
	<%String msg = (String) request.getAttribute("msg");
			if (msg != null) {
	%>
	<script language="javascript">
		alert('<%=msg%>');
	</script>
	<%}%>
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
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<form action="searchNoSeatWorkInfo.do?method=getNewFormatDutyTimeInfo" method="post" name="noSeat" onsubmit="return validate();">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 考勤日志查询 </font> </strong>
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
				开始日期:
				<input class="input_box" maxlength=20 style="width:100" name="dutyInfo_startDate" readonly="readonly" value="<%=(String)request.getAttribute("startDate")==null?"":(String)request.getAttribute("startDate")%>">
				<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
				&nbsp;&nbsp;&nbsp;&nbsp;
				结束日期:
				<input name="dutyInfo_endDate" class="input_box" maxlength=20 style="width:100" readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
				<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
				<script type="text/javascript">
	                new calendar("dutyInfo_startDate", "calBegin", "%Y-%m-%d");
	                new calendar("dutyInfo_endDate", "calEnd", "%Y-%m-%d");
				</script>
			
				部&nbsp;&nbsp;门:
				<select name="dutyInfo_deptId" style="width: 150">
				<c:if test="${admin==1}">
					<option value="">
						所有
					</option>
				</c:if>
					<c:forEach var="department" items="${departmentTree}">
						<option value="<c:out value="${department.deptId}"/>">
							<c:out value="${department.deptName}" />
						</option>
					</c:forEach>
				</select>
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value=" 查 询 " onclick="if(validate()==false) return false;noSeat.submit();"/>
			
			</jodd:form>
		</div>


		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		
			<ec:table items="noSeatList" var="leave" rowsDisplayed="15" action="searchNoSeatWorkInfo.do?method=getNewFormatDutyTimeInfo" form="noSeat">
					<ec:exportXls fileName="clerkList.xls" tooltip="导出 Excel" />
					<ec:row>
						<ec:column property="deptName" 
							title="部门" 
							width="80" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
					
						<ec:column property="stuempNo" 
							title="工号" 
							width="80" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
						<ec:column property="custName" 
							title="姓名" 
							width="80" 
							headerStyle="text-align:center" 
							style="text-align: left"
							sortable="false"
						/>
						<c:forEach items="${ss}" var="items" >
						<ec:column property="sdate" 
						title="${items.date}" 
						>
						</ec:column>
						</c:forEach>
						</ec:row>
		</ec:table>
		
		
				</td>
		    </tr>			  
		</table>
	</form>
	</body>
</html>
		