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
			<strong> <font class="medium"> 个人考勤信息查询 </font> </strong>
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
			<jodd:form bean="request">
				<form action="personalCheckDetail.do?method=getOnesCheckDetail" method="post" name="noSeat" onsubmit="return validate();">
					<table width="60%" border=0 cellPadding=1 cellSpacing=1>
						<tbody>
							<tr>
								<td>
									<span class="medium"> 开始日期 </span>
								</td>
								<td>
									<input class="input_box" maxlength=20 style="width:100" name="dutyInfo_startDate" readonly="readonly" value="<%=(String)request.getAttribute("startDate")==null?"":(String)request.getAttribute("startDate")%>">
									<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
								</td>
								<td>
									<span class="medium"> 结束日期 </span>
								</td>
								<td>
									<input name="dutyInfo_endDate" class="input_box" maxlength=20 style="width:100" readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
									<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
								</td>
								<script type="text/javascript">
					                new calendar("dutyInfo_startDate", "calBegin", "%Y-%m-%d");
					                new calendar("dutyInfo_endDate", "calEnd", "%Y-%m-%d");
            					</script>
								<td>
									<input name="Submit22" type="button" class="submitButton" value=" 查 询 " onclick="if(validate()==false) return false;noSeat.submit();">
								</td>
							</tr>
						</tbody>
					</table>
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
			<ec:table items="checkDetail" var="clerk" rowsDisplayed="15" action="personalCheckDetail.do?method=getOnesCheckDetail">
				<ec:exportXls fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
				<ec:column property="STUEMP_NO" headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="学/工号" 
						width="120"/>
					
					<ec:column property="CUT_NAME" title="姓    名" width="120" />
					<ec:column property="att_date" title="考勤日期" width="120" />
					<ec:column property="startTime" title="上班时间" width="80" />
					<ec:column property="endTime" title="下班时间" width="80" />
                   
				</ec:row>
			</ec:table>

		</div>


	</body>
</html>
