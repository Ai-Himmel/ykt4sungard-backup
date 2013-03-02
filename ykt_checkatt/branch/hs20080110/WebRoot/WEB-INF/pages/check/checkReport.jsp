<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<form name="makeReportForm" method="post" >
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ���ɿ��ڱ��� </font> </strong>
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
				��&nbsp;&nbsp;��:
				<select name="deptId" style="width: 150">
					<option value="">
						����
					</option>
					<c:forEach var="department" items="${departmentTree}">
						<option value="<c:out value="${department.deptId}"/>">
							<c:out value="${department.deptName}" />
						</option>
					</c:forEach>
				</select>
				&nbsp;&nbsp;
				ͳ���·�:
				<input class="input_box" style="width:80" maxlength=20 name="statDate" readonly="readonly" value="<c:out value='${statDate}' />" >
				<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
				<script type="text/javascript">
    				new calendar("statDate", "calBegin", "%Y-%m");
				</script>
				
				<input type=hidden name=finance value="0">
			
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value="���ɱ���" onclick="javascript:makeReport('0')"/>
				&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value="�������ΪExcel" onclick="javascript:downLoadFile()"/>
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				
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
		      <td height="40" align="left" valign="middle" > 
			  <table width=85% border=1 cellpadding=1 cellspacing=0 bordercolor=#3462AD bordercolordark=#000000  id=submenu1>
		          <tbody>
		            <tr align="center" valign=center> 
		              <td rowspan="3" width="350" valign="middle" ><strong>����</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>����</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>����</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>�������</strong></td>

		              <td colspan=<c:out value="${dayNum}" /> valign="middle" ><strong><c:out value="${statDate}"/>�����������ڼ�¼</strong></td>

		          
		              <td rowspan="3" width="80" valign="middle" ><strong>����</strong></td>
		              
		              <td></td>
		            </tr>
		            
		            <tr align="center" valign=center> 		            
		            <c:forEach items="${ss}" var="items" >
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><c:out value="${items.week}" /></td>
		            </c:forEach>
		            </tr>
		            <tr align="center" valign=center> 
		            <c:forEach items="${ss}" var="items" >
		              <td align="center" valign="middle" bgcolor="#FFFFFF" width="20"><c:out value="${items.date}" /></td>
		            </c:forEach>
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
								List dayList = (List)request.getAttribute("ss");
								Iterator dayIter = dayList.iterator();
								while (dayIter.hasNext()){
								Map dayMap = (Map)dayIter.next();								
								%>
							<td align="center" valign="middle" bgcolor="#FFFFFF" ></td>						
		            <%}%>
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
						String totMoney = "";
						Iterator checkIter = checkReportList.iterator();
						while (checkIter.hasNext()){
							Map checkMap = (Map)checkIter.next();
							deptName = checkMap.get("bm").toString();
							stuempNo = checkMap.get("gh").toString();
							custName = checkMap.get("xm").toString();
							custType = checkMap.get("kqlb").toString();
							totNum = checkMap.get("cs").toString();
							totMoney = checkMap.get("bt").toString();
							%>
							
		            <tr align="center" valign=center> 
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=deptName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=stuempNo%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custType%></td>
					<%		
								List dayList = (List)request.getAttribute("ss");
								Iterator dayIter = dayList.iterator();
								while (dayIter.hasNext()){
								Map dayMap = (Map)dayIter.next();
								sdate = "day"+dayMap.get("date").toString();
								checkInfo = checkMap.get(sdate)==null?"":checkMap.get(sdate).toString();	
								%>
							<td align="center" valign="middle" bgcolor="#FFFFFF" ><%=checkInfo%></td>						
		            <%}%>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=totNum%></td>
		           
		            </tr>
		            <%}
		            }%>
		            
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
function makeReport(makeSign)
{
    if (confirm("��ȷ�Ͽ�����Ϣ�޸���Ϻ����ɱ���"))
    {

    	document.makeReportForm.action="checkStatic.do?method=getMakeCheckReport";

    	//document.makeReportForm.action="checkStatic.do?method=getReportByMonth";
    	document.makeReportForm.action="checkStatic.do?method=getMakeCheckReport";

        document.makeReportForm.submit();
    }
}

function downLoadFile(){
    if (confirm("ȷ�����Excel���Ĳ��ź�ͳ���·ݵ���ȷ��,Ҫ�����?"))
    {
    	document.makeReportForm.action="checkStatic.do?method=downLoadFileAction"
        document.makeReportForm.submit();
    }
}
</script>
		