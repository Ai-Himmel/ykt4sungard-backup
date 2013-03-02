<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel="stylesheet">
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
		<form name="makeReportFinanceForm" method="post" >
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 生成考勤报表 </font> </strong>
		</div>
		<div id="lineDiv" class="hrLine">
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
				开始日期:
				<input class="input_box" maxlength="20" style="width:100" name="startDate" readonly="readonly" value="<%=(String)request.getAttribute("startDate")==null?"":(String)request.getAttribute("startDate")%>">
				<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" style="cursor:pointer">
				&nbsp;&nbsp;&nbsp;&nbsp;
				结束日期:
				<input name="endDate" class="input_box" maxlength="20" style="width:100" readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
				<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0"  style="cursor:pointer">
				<script type="text/javascript">
	                new calendar("startDate", "calBegin", "%Y-%m-%d");
	                new calendar("endDate", "calEnd", "%Y-%m-%d");
				</script>
				&nbsp;&nbsp;
				
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value="生成报表" onclick="javascript:makeReport()"/>
				&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value="报表另存为Excel" onclick="javascript:downLoadFile()"/>
				
			</jodd:form>
		</div>
     

		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		
			  <table align="left" width="65%" border=1 cellpadding=1 cellspacing=0 bordercolor=#3462AD bordercolordark=#ffffff >
		        
		            <tr align="center" > 
		              <td  width="25%" height="24" align="center" ><strong>部门</strong></td>
		              <td  width="15%" height="24" align="center" ><strong>工号</strong></td>
		              <td  width="15%" height="24" align="center" ><strong>姓名</strong></td>
		              <td  width="15%" height="24" align="center" ><strong>考勤类别</strong></td>
		              <td  width="15%" height="24" align="center" ><strong>有效考勤次数</strong></td>
		              <td  width="1%"  height="24" align="center" ><strong>&nbsp;</strong></td>
		            </tr> 
		            <tr align="center" valign=center></tr>
		          
		            <%
						List checkReportList = (List)request.getAttribute("checkReportList");
						if (null==checkReportList){%>
		            <tr align="center" > 
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
					
						Iterator checkIter = checkReportList.iterator();
						while (checkIter.hasNext()){
							Map checkMap = (Map)checkIter.next();
							deptName = checkMap.get("deptName").toString();
							stuempNo = checkMap.get("stuempNo").toString();
							custName = checkMap.get("custName").toString();
							custType = checkMap.get("custType").toString();
							totNum = checkMap.get("totNum").toString();
							%>
							
		            <tr align="center"> 
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=deptName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=stuempNo%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custType%></td>
				
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=totNum%></td>
		            </tr>
		            <%}}%>
		            
		            <tr><td></td></tr>
		         
		        </table>
		       
	  	</form>

	</body>
</html>

<script>

function makeReport()
{  
    if (makeReportFinanceForm.startDate.value=="" || makeReportFinanceForm.endDate.value==""){
        alert("请选择日期范围!")
    }else{
    	document.makeReportFinanceForm.action="checkStatic.do?method=getMakeCheckReportFinance";
        document.makeReportFinanceForm.submit();
    }
}

function downLoadFile(){
    if (confirm("确认另存Excel表格的部门和统计日期的正确性,要另存吗?"))
    {
    	document.makeReportFinanceForm.action="checkStatic.do?method=downLoadFileFinanceAction"
        document.makeReportFinanceForm.submit();
    }
}
</script>
		