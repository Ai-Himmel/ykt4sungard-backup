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

	</head>
	<%String msg = (String) request.getAttribute("msg");
			if (msg != null) {%>
	<script language="javascript">
		alert('<%=msg%>');
	</script>
	<%}%>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 手工考勤修改 </font> </strong>
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
			<form name="menualRegister" action="workInfo.do?method=searchClerkModify" method="post">
					姓名:
					<input name="register_trueName" style="width:80" class="input_box" maxlength=20>
					&nbsp;&nbsp;
					学/工号:
					<input name="register_stuNumber" style="width:80" class="input_box" maxlength=20>
					开始日期:
					<input name="register_sDate" class="input_box" maxlength=20 readonly="readonly" style="width:80" value="<c:out value='${beginDate}'/>">
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begindate" style="cursor:pointer">
					结束日期:
					<input name="register_eDate" class="input_box" maxlength=20 readonly="readonly" style="width:80" value="<c:out value='${endDate}'/>">
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="enddate" style="cursor:pointer">
					&nbsp;&nbsp;
					部门:
					<select name="register_deptId" style="width:120">
						<option value="">
							所有
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptName}" />
							</option>
						</c:forEach>
					</select>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<input name="Submit" type="submit" class="submitButton" value=" 查 询 ">
					<script type="text/javascript">
	    			new calendar("register_sDate", "calBegin", "%Y-%m-%d");	
	    			new calendar("register_eDate", "calEnd", "%Y-%m-%d");		
       				</script>
		</form>
		</jodd:form>
		</div>
		<div>
			<%@ include file="/pages/common/messages.jsp"%>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<form name="menualDelete" action="workInfo.do?method=deleteManual" method="post">
			<div id="operationDiv">
				<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:manualdel();">删 除</A> </span>
			</div>
		<div id="tableDiv">
			<ec:table items="clerkList" var="clerk" rowsDisplayed="12" action="workInfo.do?method=searchClerk" form="register">
				<ec:exportXls fileName="clerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="checkbox" 
						title="选择" 
						width="50" 
						headerStyle="text-align: center"
						sortable="false">
						<input type="checkbox" name="itemlist" value="${clerk.serial_id}" style="border:0px" />
					</ec:column>
					<ec:column property="STUEMP_NO" 
						title="学/工号" 
						width="200" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
					/>
					<ec:column property="CUT_NAME" 
						title="姓名" 
						width="200" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
					/>
					<ec:column property="DEPT_NAME" 
						title="所属考勤部门" 
						width="450" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
					/>
					<ec:column property="ATT_DATE" 
						title="考勤日期" 
						width="200" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					/>
					<ec:column property="ATT_TIME" 
						title="考勤时间" 
						width="200" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					/>
					<ec:column property="修改" 
						title="修改" 
						width="60" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					>
					<a href="workInfo.do?method=goClerkModify&serial_id=${clerk.serial_id}">修改</a>
					</ec:column>
				</ec:row>
			</ec:table>
		</div>
		</form>
	</body>
</html>
<script>
function manualdel()
{
	if (!leaseOneCheck()){
		alert("请先选择要删除的记录！");
		return;
	}
    if (confirm("你确定要删除手工签到记录吗?"))
    {
        document.menualDelete.submit();
    }
}
function leaseOneCheck()
{
    var items = document.all["itemlist"];
    if(items==null)
        return false;
    if(items.length>0){
	    for (var i = 0; i < items.length; i++)
	    {
	        if (items[i].checked == true)
	        {
	            return true;
	        }
	    }
	}else{
		if(items.checked == true){
			  return true;		   	 
		}
	}
    return false;
}

</script>
