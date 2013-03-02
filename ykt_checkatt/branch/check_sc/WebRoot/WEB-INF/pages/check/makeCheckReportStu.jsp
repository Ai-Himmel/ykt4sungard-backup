<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.check.util.DateUtilExtend" %>
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
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<form name="makeReportForm" method="post" >
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 生成考勤报表(学生) </font> </strong>
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
				开始日期:
				<input class="input_box" style="width:80" maxlength=20 name="beginDate" readonly="readonly" value="<c:out value='${beginDate}' />" >
				<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
				<script type="text/javascript">
    				new calendar("beginDate", "calBegin", "%Y-%m-%d");
				</script>
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value="生成报表" onclick="javascript:makeReport()"/>
				&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value="报表另存为Excel" onclick="javascript:downLoadFile()"/>
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
			  <table width=85% border=1 cellpadding=1 cellspacing=0 bordercolor=#3462AD bordercolordark=#ffffff  id=submenu1>
		          <tbody>
		            <tr align="center" valign=center> 
		              <td rowspan="3" width="350" valign="middle" ><strong>部门/院系</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>学/工号</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>姓名</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>考勤类别</strong></td>
		              <td colspan="28" valign="middle" ><strong><c:out value="${beginDate1}"/>--<c:out value="${endDate}"/>出勤记录</strong></td>
		              <td rowspan="3" width="60" valign="middle" ><strong>签到次数</strong></td>
		              <td rowspan="3" width="60" valign="middle" ><strong>迟到次数</strong></td>
		              <td rowspan="3" width="60" valign="middle" ><strong>缺席次数</strong></td>
		             
		              <td></td>
		            </tr>
		            <!--日期-->
		            <tr align="center" valign=center> 		            
		            <%
		            	String startDate = DateUtilExtend.formatDate2(request.getAttribute("beginDate").toString());
		            	String tempDate = startDate;
		            	for (int i=0;i<7;i++){
		            %>
		              <td colspan="4" align="center" valign="middle" bgcolor="#FFFFFF" ><%=tempDate%></td>
		            <%
		            		tempDate = DateUtilExtend.addDate2(tempDate.toString(),1);
		            	}
		            %>
		            </tr>
		            
		            <!--早上下晚-->
		            <tr align="center" valign=center> 
		            <%
		            	String tempS = "";
		            	for (int i=0;i<28;i++){
		            	tempS=DateUtilExtend.getCheckSign(i%4);
		            %>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" width="20"><%=tempS%></td>
		            <%}%>
		            </tr>
		            
		            <%
						List checkReportList = (List)request.getAttribute("checkReportList");
						if (null==checkReportList){%>
		            <tr align="center" valign=center> 
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		             
					<%		
						for (int i=0;i<28;i++){
						
					%>
							<td align="center" valign="middle" bgcolor="#FFFFFF" ></td>						
		            <%}%>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		            </tr>
					<%	}else{
						//String sdate = "";
						String checkInfo="";
						String deptName = "";
						String stuempNo = "";
						String custName = "";
						String custType = "";
						String checkNum = "";
						String lateNum = "";
						String leaveNum = "";
						String earlyNum = "";
						Iterator checkIter = checkReportList.iterator();
						while (checkIter.hasNext()){
							Map checkMap = (Map)checkIter.next();
							deptName = checkMap.get("deptName").toString();
							stuempNo = checkMap.get("stuempNo").toString();
							custName = checkMap.get("custName").toString();
							custType = checkMap.get("custType").toString();
							checkNum = checkMap.get("checkNum").toString();
							lateNum = checkMap.get("lateNum").toString();
							leaveNum = checkMap.get("leaveNum").toString();
							earlyNum = checkMap.get("earlyNum").toString();
							%>
							
		            <tr align="center" valign=center> 
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=deptName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=stuempNo%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custType%></td>
					<%		
		            	String startDate1 = DateUtilExtend.formatDate2(request.getAttribute("beginDate").toString());
		            	String tempDate1 = startDate1;
		            	
						for (int i=0;i<28;i++){
							checkInfo = checkMap.get(DateUtilExtend.getCheckSign2(i%4)+tempDate1).toString();
							if ((i%4==3)&&(i>0)){
								tempDate1 = DateUtilExtend.addDate2(tempDate1.toString(),1);
							}
					%>
					<td align="center" valign="middle" bgcolor="#FFFFFF" ><%=checkInfo%></td>						
		            <%}%>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=checkNum%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=lateNum%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=leaveNum%></td>
		             
		            </tr>
		            <%}}%>
		            
		            <tr><td></td></tr>
		          </tbody>
		        </table>
				</td>
		    </tr>			  
		</table>
	</form>
	</body>
</html>

<script>
function makeReport()
{
    if (confirm("你确定要生成考勤记录吗?"))
    {
    	document.makeReportForm.action="checkStatic.do?method=getMakeCheckReportStu"
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
</script>
		