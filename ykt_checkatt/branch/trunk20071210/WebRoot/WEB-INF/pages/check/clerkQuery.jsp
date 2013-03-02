<%@ page contentType="text/html;charset=UTF-8"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<SCRIPT language=javascript>
function deleteBatch(form, entityName, action)
{
	if (confirm("你确定要删除选定的考勤人员吗?")){
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
</SCRIPT>

<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>

	<body>

		<div id="titleDiv" class="pageTitle">
			考勤人员维护
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
				<form id="queryform" method="post" action="clerkManager.do?method=queryClerkInfo">

					<table width="100%" border=0 cellPadding=1 cellSpacing=1>
						<tbody>
							<tr>
								学工号：
								<input class="text" type="text" name="search_personCode" size="10" style="width: 100">
								姓&nbsp;&nbsp;名：
								<input class="text" type="text" name="search_personName" size="10" style="width: 100">
								部&nbsp;&nbsp;门：
								<select name="search_department"  style="width: 150">
									<c:if test="${admin==1}">
										<option value="all">
											所有
										</option>
									</c:if>
									<c:forEach var="department" items="${departments}">
										<option value="<c:out value="${department.deptId}"/>">
											<c:out value="${department.deptName}" />
										</option>
									</c:forEach>
								</select>
								&nbsp;&nbsp;&nbsp;&nbsp;
								<input name="Submit" type="button" class="submitButton" value=" 查 询 " onclick="javascript:document.all.queryform.submit();">
								&nbsp;&nbsp;&nbsp;&nbsp;
								<input name="Submit" type="button" class="submitButton" value=" 删 除 " onclick="javascript:deleteBatch(document.forms.ec,'考勤人员','<c:url value="removeClerk.do?method=deleteClerk" />');">
							</tr>
						</tbody>
					</table>
				</form>
			</jodd:form>
		</div>
<%@ include file="/pages/common/messages.jsp"%>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		
		<!--
		<div id="operationDiv">
			<%@ include file="/pages/common/messages.jsp"%>
			
			<span class="operations"> 
			
			<img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:deleteBatch(document.forms.ec,'考勤人员','<c:url value="removeClerk.do?method=deleteClerk" />');">删 除</A> </span>
			
		</div>
		-->
		<div id="tableDiv">
			<ec:table items="clerks" var="clerk" rowsDisplayed="10" action="clerkManager.do?method=queryClerkInfo">
				<ec:exportXls fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="5%" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${clerk.cut_id}" style="border:0px" />
					</ec:column>
					<ec:column property="STUEMPID" title="学工号" width="10%" escapeAutoFormat="true"/>
					<ec:column property="STUEMPNAME" title="姓名" width="15%" />
					<ec:column property="DEPT_NAME" title="所属部门" width="35%" />
					<ec:column property="type_name" title="所在班次" width="25%" />
					<ec:column property="IFOFFICE" title="考勤类别" width="10%" />
				</ec:row>
			</ec:table>

		</div>
 <!--<a href="#" onclick="window.open('clerk.do?method=viewClerkDetail&clerkId=${clerk.cut_id}','详细信息','height=550,width=500,status=yes,toolbar=no,menubar=no,location=no');" >详细信息</a>-->

</body>

</html>

