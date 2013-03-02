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
				<form action="searchNoSeatWorkInfo.do?method=getNewFormatDutyTimeInfo" method="post" name="noSeat" onsubmit="return validate();">
					<table width="100%" border=0 cellPadding=1 cellSpacing=1>
					<tr>
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
    					&nbsp;&nbsp;&nbsp;&nbsp;
						部门:
						<select name="dutyInfo_deptId" style="width:150">
							<option value="all">
								所有
							</option>
							<c:forEach var="department" items="${departmentTree}">
								<option value="<c:out value="${department.deptId}"/>">
									<c:out value="${department.deptName}" />
								</option>
							</c:forEach>
						</select>
						&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
						<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
						<a href="#" onclick="if(validate()==false) return false;noSeat.submit();">查询</a> &nbsp; &nbsp;&nbsp;&nbsp;
					</tr>
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
		<%String titleStr = (String) request.getAttribute("titleStr");
			List newFormatL = (List) request.getAttribute("newFormatL");
			if (titleStr == null) {
				titleStr = "信息";
			}

			%>
		<div>
			<table id="atblData" border="1" cellspacing="0" cellpadding="0" align="left" bordercolor=#445386>
				<tbody>
					<tr>
						<%out.print(titleStr);%>
					</tr>
					<%if (newFormatL != null && !newFormatL.isEmpty()) {
							Iterator ite = newFormatL.iterator();
							while (ite.hasNext()) {
								DutyTimeVo dutyTimeVo = (DutyTimeVo) ite.next();
								out.print(dutyTimeVo.getDutyTimeStr());
							}

						  }

						%>
				</tbody>
			</table>
		</div>
	</body>
</html>

<script language="javascript"> 
  function   AutomateExcel()     
  {   
  var   oXL   =   new   ActiveXObject("Excel.Application");     
  var   oWB   =   oXL.Workbooks.Add();     
  var   oSheet   =   oWB.ActiveSheet;     
  var   hang   =   atblData.rows.length;     
    
  var   lie   =   atblData.rows(0).cells.length;     
    
  for   (i=0;i<hang;i++)     
  {     
  for   (j=0;j<lie;j++)     
  {     
  oSheet.Cells(i+1,j+1).value   =   atblData.rows(i).cells(j).innerText;     
  }     
    
  }     
  oXL.Visible   =   true;     
  oXL.UserControl   =   true;     
  }     
   function   AutomateExcel11()     
  {   
  //   Start   Excel   and   get   Application   object.   
  var   oXL   =   new   ActiveXObject("Excel.Application");     
  //   Get   a   new   workbook.   
  var   oWB   =   oXL.Workbooks.Add();   
  var   oSheet   =   oWB.ActiveSheet;   
  var   table   =   document.all.atblData;     
  var   hang   =   table.rows.length;   
    
  var   lie   =   table.rows(0).cells.length;     
    
  //   Add   table   headers   going   cell   by   cell.   
  for   (i=0;i<hang;i++)   
  {   
  for   (j=0;j<lie;j++)   
  {   
  oSheet.Cells(i+1,j+1).Value   =   table.rows(i).cells(j).innerText;   
  }   
    
  }   
  oXL.Visible   =   true;   
  oXL.UserControl   =   true;   
  }   
 
</script> 

