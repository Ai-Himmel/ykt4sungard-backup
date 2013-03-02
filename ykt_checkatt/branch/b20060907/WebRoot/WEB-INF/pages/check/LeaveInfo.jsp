<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
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

function update(url,clerkname)
{
	var new_url=url+"&pre_clerkName="+encodeURI(clerkname);
	ec.action=new_url;
	ec.submit();
}
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
	var startDate=leave.leave_startDate.value;
	var endDate=leave.leave_endDate.value;
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
<% String msg=(String)request.getAttribute("msg");
if(msg!=null)
{
%>
	alert('<%=msg%>');
<%}%>
</SCRIPT>

</head>
<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
请假情况查询
</font>
</strong>
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
  <form action="leaveInfo.do?method=searchLeaveInfo" method="post" name="leave" onsubmit="return validate();">
开始日期
<input class="input_box"  maxlength=20 name="leave_startDate" readonly="true" value="<%=request.getParameter("leave_startDate")==null?"":request.getParameter("leave_startDate")%>">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
结束日期
<input name="leave_endDate" class="input_box"  maxlength=20  readonly="true" value="<%=request.getParameter("leave_endDate")==null?"":request.getParameter("leave_endDate")%>">
<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
           <script type="text/javascript">
                new calendar("leave_startDate", "calBegin", "%Y-%m-%d");
                new calendar("leave_endDate", "calEnd", "%Y-%m-%d");
            </script>
姓 名
<input class="input_box"  maxlength=20 name="leave_trueName" value="<%=request.getParameter("leave_trueName")==null?"":request.getParameter("leave_trueName")%>">
单 位
<select name="leave_deptId">
						<option value="">
							所有
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptTitle}" />
							</option>
						</c:forEach>
					</select>
<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">&nbsp;
<a href="#" onclick="if(validate()==false) return false;leave.submit();">查询</a>
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
        <div id="operationDiv">
			<%@ include file="/pages/common/messages.jsp"%>
			<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_delete_leaveInfo(document.forms.ec,'请假信息','<c:url value="leaveInfo.do?method=delete" />');">删 除</A> </span>
		</div>
		<div id="tableDiv">
			<ec:table items="leaveInfoList" var="leaveinfo" rowsDisplayed="5" action="leaveInfo.do?method=searchLeaveInfo">
				<ec:exportXls fileName="leaveInfoList.xls" tooltip="导出 Excel" />
				<ec:row>
				<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${leaveinfo.leaveinfoId}" style="border:0px" />
					</ec:column>
					<ec:column property="cardnumber" title="卡号" width="60" />
					<ec:column property="clerkname" title="姓名" width="60" />
					<ec:column property="departname" title="单位" width="80" />
					<ec:column property="startdate" title="请假开始时间" width="120" />
					<ec:column property="enddate" title="请假结束时间" width="120" />
					<ec:column property="description" title="请假原因" width="120" />
                    <ec:column property="confname" title="班制" width="60" />
					<ec:column property="isseat" title="人员性质" width="60" />
					<ec:column property="recordDate" title="记录时间" width="60" />
					<ec:column property="operatorName" title="记录人员" width="60" />
					<ec:column property="update" title="修改" width="40" sortable="false" >
					<a href="#" onclick="update('leaveInfo.do?method=preUpdate&pre_leaveinfoId=${leaveinfo.leaveinfoId}','${leaveinfo.clerkname}');">修改</a>
					</ec:column>
				</ec:row>
			</ec:table>

		</div>
</body>
</html>
