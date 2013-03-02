<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
<head>
<title>复旦大学校园一卡通考勤管理系统</title>
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
	var startDate=extrastatic.extra_startDate.value;
	var endDate=extrastatic.extra_endDate.value;
	if(startDate==''||endDate=='')
	{
		alert('请将日期输入完整');
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

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
加班情况统计
</font>
</strong>
</div>

<div id=lineDiv class="hrLine" >
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>

<div id="filterDiv" style="text-align: left;">
  <form name="extrastatic" action="extraWork.do?method=staticExtraInfo" method="post" onsubmit="return check();">
	  <jodd:form bean="request">
姓名:
<input name="extra_trueName" class="input_box"  maxlength=20>
&nbsp;&nbsp;&nbsp;
单位:
<select name="extra_deptId">
	<option value="">
		所有
	</option>
    <c:forEach var="department" items="${departmentTree}">
	  <option value="<c:out value="${department.deptId}"/>">
      <c:out value="${department.deptTitle}" />
	  </option>
	</c:forEach>
</select>
&nbsp;&nbsp;&nbsp;
开始日期
<input class="input_box"  maxlength=20 name="extra_startDate" readonly="true" value="<%=request.getParameter("extra_startDate")==null?"":request.getParameter("extra_startDate")%>">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
&nbsp;&nbsp;&nbsp;
截止日期
<input  name="extra_endDate" class="input_box"  maxlength=20 readonly="true" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
			  <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
			   <script type="text/javascript">
			    new calendar("extra_startDate", "calBegin", "%Y-%m-%d");
                new calendar("extra_endDate", "calEnd", "%Y-%m-%d");				
               </script>
			   <input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
&nbsp;&nbsp;&nbsp;
 <input name="Submit" type="submit" class="button_nor" value="查 询" > 

		</jodd:form>
	</form>
</div>

<div id=lineDiv class="hrLine" >
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>

	<div id="tableDiv">
         <ec:table items="staticInfoList" var="staticInfo" rowsDisplayed="5" action="extraWork.do?method=staticExtraInfo">
				<ec:exportXls fileName="staticInfoList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="departname" title="部门" width="60" />
					<ec:column property="clerkname" title="人员" width="60" />
					<ec:column property="tatol" title="加班总天数" width="120" />
					<ec:column property="confname" title="班制" width="120" />
					<ec:column property="isseat" title="人员性质" width="120" />

					<ec:column property="detail" title="详细信息" width="60" sortable="false" >
					<a href="#"  onclick="window.open('extraWork.do?method=viewExtraDetail&startDate='+extrastatic.extra_startDate.value+'&endDate='+extrastatic.extra_endDate.value+'&clerkId=${staticInfo.cut_id}','详细信息','height=550,width=500,status=yes,toolbar=no,menubar=no,location=no')">详细信息</a>					
					</ec:column>
				</ec:row>
			</ec:table>
	</div>
</body>
</html>
