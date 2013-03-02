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
	var startDate=extra.extra_startDate.value;
	var endDate=extra.extra_endDate.value;
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
加班情况查询
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
  <form action="extraWork.do?method=searchExtraInfo" method="post" name="extra" onsubmit="return validate();">
开始日期
<input class="input_box"  maxlength=20 name="extra_startDate" readonly="true" value="<c:out value='${extra_startDate}' />">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
结束日期
<input name="extra_endDate" class="input_box"  maxlength=20  readonly="true" value="<c:out value='${extra_endDate}' />">
<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
           <script type="text/javascript">
                new calendar("extra_startDate", "calBegin", "%Y-%m-%d");
                new calendar("extra_endDate", "calEnd", "%Y-%m-%d");
            </script>
姓 名
<input class="input_box"  maxlength=20 name="extra_trueName" value="<c:out value='${extra_trueName}' />">
单 位
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
<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">&nbsp;
<a href="#" onclick="if(validate()==false) return false;extra.submit();">查询</a>
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
			<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_delete_leaveInfo(document.forms.ec,'加班信息','<c:url value="extraWork.do?method=delete" />');">删 除</A> </span>
		</div>
		<div id="tableDiv">
			<ec:table items="extraInfoList" var="extrainfo" rowsDisplayed="5" action="extraWork.do?method=searchExtraInfo">
				<ec:exportXls fileName="extraInfoList.xls" tooltip="导出 Excel" />
				<ec:row>
				<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${extrainfo.extrainfoid}" style="border:0px" />
					</ec:column>
					<ec:column property="cardnumber" title="卡号" width="60" />
					<ec:column property="clerkname" title="姓名" width="60" />
					<ec:column property="departname" title="单位" width="80" />
					<ec:column property="startdate" title="加班开始时间" width="120" />
					<ec:column property="enddate" title="加班结束时间" width="120" />
                    <ec:column property="confname" title="班制" width="60" />
					<ec:column property="isseat" title="人员性质" width="60" />
					<ec:column property="recorddate" title="记录时间" width="60" />
					<ec:column property="operatorname" title="记录人员" width="60" />
					<ec:column property="update" title="修改" width="40" sortable="false" >
					<a href="#" onclick="update('extraWork.do?method=preUpdate&pre_extrainfoid=${extrainfo.extrainfoid}','${extrainfo.clerkname}');">修改</a>
					</ec:column>
				</ec:row>
			</ec:table>

		</div>
</body>
</html>
