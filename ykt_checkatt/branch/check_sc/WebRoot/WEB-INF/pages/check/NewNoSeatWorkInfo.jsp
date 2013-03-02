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
		
		<table  border="0" align="left" cellpadding="0" cellspacing="0">
		    <tr> 
		      <td height="40" align="left" valign="middle" > 
			  <table border=1 cellpadding=1 cellspacing=0 bordercolor=#3462AD bordercolordark=#ffffff  id=submenu1>
		          <tbody>
		            <tr align="center" valign=center> 
		              <td rowspan="3" height="24" width="120" valign="middle" nowrap="nowrap"><strong>部门</strong></td>
		              <td rowspan="3" height="24" width="80" valign="middle" nowrap="nowrap"><strong>工号</strong></td>
		              <td rowspan="3" height="24" width="80" valign="middle" nowrap="nowrap"><strong>姓名</strong></td>
		              <td colspan=<c:out value="${dayNum}" /> valign="middle" ><strong><c:out value="${dateRange}"/>考勤记录</strong></td>
		              <td></td>
		            </tr>
		            
		            <tr align="center" valign=center> 
		            <c:forEach items="${ss}" var="items" >
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;&nbsp;&nbsp;<c:out value="${items.date}" />&nbsp;&nbsp;&nbsp;</td>
		            </c:forEach>
		            </tr>
		            <tr align="center" valign=center> 		            
		            <c:forEach items="${ss}" var="items" >
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><c:out value="${items.week}" /></td>
		            </c:forEach>
		            </tr>
		            
		            <%
						List checkReportList = (List)request.getAttribute("noSeatList");
						if (null==checkReportList){%>
		            <tr align="center" valign=center> 
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
		            </tr>
					<%	}else{
						String sdate = "";
						String checkInfo="";
						String deptName = "";
						String stuempNo = "";
						String custName = "";
						Iterator checkIter = checkReportList.iterator();
						while (checkIter.hasNext()){
							Map checkMap = (Map)checkIter.next();
							deptName = checkMap.get("deptName").toString();
							stuempNo = checkMap.get("stuempNo").toString();
							custName = checkMap.get("custName").toString();
							%>
							
		            <tr align="center" valign=center> 
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=deptName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=stuempNo%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custName%></td>
					<%		
							List dayList = (List)request.getAttribute("ss");
							Iterator dayIter = dayList.iterator();
							while (dayIter.hasNext()){
								Map dayMap = (Map)dayIter.next();
								sdate = dayMap.get("date").toString();
								checkInfo = checkMap.get(sdate).toString();
								String[] chkInfo = StringUtil.split(checkInfo,"/");
								String chkTime = chkInfo[0];
								String chkSign = chkInfo[1];								
								String chkLink = chkInfo[2];
								if (CommonConfig.leaveManual.equals(chkSign)){
								
					%>
									<td align="center" valign="middle" bgcolor="#F1D17E" ><a href="<%=chkLink%>"/><%=chkTime%></td>		
								<%}else if (CommonConfig.leave.equals(chkSign)){%>	
									<td align="center" valign="middle" bgcolor="#A6F0F0" ><a href="<%=chkLink%>"/><%=chkTime%></td>
								<%}else if (CommonConfig.manual.equals(chkSign)){%>
									<td align="center" valign="middle" bgcolor="#C0EEA8" ><a href="<%=chkLink%>"/><%=chkTime%></td>	
								<%}else{%>	
										<%if ("--".equals(chkTime)){%>
											<td align="center" valign="middle" bgcolor="#FFFFFF" ><%=chkTime%></td>
										<%}else{%>
											<td align="center" valign="middle" bgcolor="#DCE7FA" ><%=chkTime%></td>
										<%}%>
		            	<%}}%>
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
		