<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ include file="../tiles/include.jsp"%>
<%List checkReportList = (List)request.getAttribute("checkReportList");%>
<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
	
	<%String msg = (String) request.getAttribute("msg");
			if (msg != null) {
	%>
	<script language="javascript">
		alert('<%=msg%>');
	</script>
	<%}%>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<form name="makeReportForm" method="post" >
		 <input type="hidden" name="cmd" value=""/>
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 生成考勤报表 </font> </strong>
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
				部&nbsp;&nbsp;门:
				<select name="deptId" style="width: 150">
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
				&nbsp;&nbsp;
				统计月份:
				<input class="input_box" style="width:80" maxlength=20 name="statDate" readonly="readonly" value="<c:out value='${statDate}' />" >
				<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
				<script type="text/javascript">
    				new calendar("statDate", "calBegin", "%Y-%m");
				</script>
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value="生成报表" onclick="javascript:makeReport()"/>
				&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value="报表另存为Excel" onclick="javascript:downLoadFile()"/>
				<!-- 
				<a href=loadFile><strong><font face="Arial, Helvetica" size="2" color="blue">报表另存为Excel</font></strong></a>
				-->
				&nbsp;&nbsp;&nbsp;&nbsp;
				<%if (null !=checkReportList){%>
				<input name="createButton" type="button" class="submitButton" value="打印报表" onclick="javascript:printReport()"/>
				<%}%>
			</jodd:form>
		</div>


		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		
		<table width="160%" border="0" align="left" cellpadding="0" cellspacing="0">
		    <tr> 
		      <td height="100%" align="left" valign="middle" > 
			  <table width=50% border=1 cellpadding=1 cellspacing=0 bordercolor=#3462AD bordercolordark=#ffffff  id=submenu1>
		          <tbody>
		            <tr align="center" valign=center> 
		              <td rowspan="3" width="350" valign="middle" ><strong>部门</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>工号</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>姓名</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>考勤类别</strong></td>
		              <td rowspan="3" width="60" valign="middle" ><strong>当月总考勤天数</strong></td>
		              <td></td>
		            </tr>
		            
		            <tr align="center" valign=center> 		            
		           
		            </tr>
		             <tr align="center" valign=center> 		            
		           
		            </tr>
		            
		            <%
						
						if (null==checkReportList){%>
		            <tr align="center" valign=center> 
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
					  <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		            </tr>
					<%	}else{
						String sdate = "";
						String checkInfo="";
						String deptName = "";
						String stuempNo = "";
						String custName = "";
						String custType = "";
						String totNum = "";
						String halfNum = "";
						String linkNum = "";
						String patchMoney = "";
						String holidayNum = "";
						Iterator checkIter = checkReportList.iterator();
						while (checkIter.hasNext()){
							Map checkMap = (Map)checkIter.next();
							deptName = checkMap.get("deptName").toString();
							stuempNo = checkMap.get("stuempNo").toString();
							custName = checkMap.get("custName").toString();
							custType = checkMap.get("custType").toString();
							totNum = checkMap.get("totNum").toString();
						
							%>
							
		            <tr align="center" valign=center> 
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=deptName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=stuempNo%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custType%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=totNum%></td>
		            
		            </tr>
		            <%}}%>
		            
		            <tr><td></td></tr>
		          </tbody>
		        </table>
				</td>
		    </tr>			  
		</table>
	</form>
	<form name="printForm" action="checkStatic.do?method=getMakeCheckReport" method="post" target="print">
	
	</form>
	</body>
</html>

<script>
function makeReport()
{
    if (confirm("生成报表后将不能修改考勤记录,你确定吗?"))
    {
    	document.makeReportForm.action="checkStatic.do?method=getMakeCheckReport"
        document.makeReportForm.submit();
    }
}

function downLoadFile(){
    if (confirm("确认另存Excel表格的部门和统计月份的正确性,要另存吗?"))
    {
    	document.makeReportForm.action="checkStatic.do?method=downLoadFileAction"
        document.makeReportForm.submit();
    }
}
function  printReport(){
    var statDate = document.makeReportForm.statDate.value;
    var deptId =   document.makeReportForm.deptId.value;
	window.open('/check/checkStatic.do?method=getMakeCheckReport&cmd=print&statDate='+statDate+'&deptId='+deptId,"print","toolbar=yes,location=(10,10),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=900,height=700");
  
}
</script>
		