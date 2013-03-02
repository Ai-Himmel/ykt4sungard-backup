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
	
		   
			function deleteBatch(form, entityName, action)
			{
				if (confirm("你确定要删除选定的排班信息吗?")){
					var grouplist="";
					if (!atleaseOneCheck()){
						alert('请至少选择一' + entityName + '！');
						return;
					}
					document.forms.ec.ec_ev.value = '';
					document.forms.ec.ec_efn.value = '';
					
					if (document.forms.ec.itemlist.length==null){
						grouplist=document.forms.ec.itemlist.value;
					}else{
					for (i=0;i<document.forms.ec.itemlist.length;i++){
						if (document.forms.ec.itemlist[i].checked){
							grouplist=document.forms.ec.itemlist[i].value;
						}
					}}
					
					form.action = action;
					form.submit();
				}
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
				var startDate=deptConf.search_startDate.value;
				var endDate=deptConf.search_endDate.value;
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
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" >

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 考勤排班管理 </font> </strong>
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
			<form action="department.do?method=search" method="post" name="deptConf" onsubmit="return validate();">
				<jodd:form bean="request">
					&nbsp;
					<span class="medium"> 开始日期: </span>
					<input class="input_box" style="width: 80" name="search_startDate" readonly="readonly" value="<c:out value='${startDate}'/>">
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
					&nbsp;	
					结束日期:
					<input name="search_endDate" class="input_box"  style="width: 80" readonly="readonly" value="<c:out value='${endDate}'/>">
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
					<script type="text/javascript">
		                new calendar("search_startDate", "calBegin", "%Y-%m-%d");
		                new calendar("search_endDate", "calEnd", "%Y-%m-%d");
            		</script>
						&nbsp;
						班次名称:
					<select name="search_typeId" style="width:150">
						<option value="">
							所有
						</option>
						<c:forEach var="type" items="${checkType}">
							<option value="<c:out value="${type.typeId}"/>">
								<c:out value="${type.typeName}" />
							</option>
						</c:forEach>
					</select>
					&nbsp;&nbsp;
					<input type="button" value=" 查 询 " class="submitButton" onclick="if(validate()==false) return false;deptConf.submit();" />
					&nbsp;&nbsp;
					<input type="button" value="添加排班计划" class="submitButton" onclick="window.location.href='department.do?method=addConfStep1';" />
					&nbsp;&nbsp;
					<input type="button" value=" 删 除 " class="submitButton" onclick="javascript:deleteBatch(document.forms.ec,'排班信息','<c:url value="department.do?method=delDepConf" />');" />
				</jodd:form>
			</form>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="dpConfList" var="dptconf"   rowsDisplayed="15" action="department.do?method=search">
				<ec:exportXls fileName="deptConfList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${dptconf.CHECK_TYPEID}/${dptconf.BEGINDATE}" style="border:0px" />
					</ec:column>
					<ec:column property="TYPE_NAME" title="班次名称" width="100" />
					<ec:column property="BEGINDATE" title="日期" width="30" />
					<ec:column property="WORKCONF_NAME" title="考勤制度" width="100" />
					<ec:column property="WORKTIME_NAME" title="工作时间" width="100" />
					<ec:column property="detailinfo" title="详细信息" width="60" sortable="false" >
					<a href="department.do?method=getDeptConfDetail&pre_typeId=${dptconf.CHECK_TYPEID}&pre_beginDate=${dptconf.BEGINDATE}" >详细信息</a>
					</ec:column>

				</ec:row>
			</ec:table>
		</div>
	</body>
</html>
   <%String msg = (String) request.getAttribute("msg");
			if (msg != null) {
	%>
	<script language="javascript">
	document.deptConf.submit();
	alert('<%=msg%>');
	</script>
	<%}%>