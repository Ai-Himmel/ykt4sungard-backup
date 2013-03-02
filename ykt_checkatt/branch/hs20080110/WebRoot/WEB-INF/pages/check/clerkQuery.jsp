<%@ page contentType="text/html;charset=UTF-8"%>
<%@ include file="/pages/common/taglibs.jsp"%>


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
			考勤人员信息查询
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
								<td class="filterCaption">
									学工号
								</td>
								<td class="filterComponent" >
									<input class="text" type="text" name="search_personCode" size="10" style="width: 120">
								</td>
								<td class="filterCaption" align="right">
									姓&nbsp;&nbsp;名
								</td>
								<td class="filterComponent">
									<input class="text" type="text" name="search_personName" size="10" style="width: 120">
								</td>
								<td class="filterCaption" align="right">
									部&nbsp;&nbsp;门
								</td>
								<td class="filterComponent">
									<select name="search_department"  style="width: 120">
										<option value="all">
											所有
										</option>
										<c:forEach var="department" items="${departments}">
											<option value="<c:out value="${department.deptId}"/>">
												<c:out value="${department.deptName}" />
											</option>
										</c:forEach>
									</select>
								</td>
								<td class="filterComponent">
									<input name="Submit" type="button" class="submitButton" value=" 查 询 " onclick="javascript:document.all.queryform.submit();">
									<!-- 
									<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
									&nbsp;<a href="#" onclick="javascript:document.all.queryform.submit();">查 询</a>
									-->
								</td>
							</tr>
						</tbody>
					</table>
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
			<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_del(document.forms.ec,'考勤人员','<c:url value="removeClerk.do?method=deleteClerk" />');">删 除</A> </span>
		</div>

		<div id="tableDiv">
			<ec:table items="clerks" var="clerk" rowsDisplayed="10" action="clerkManager.do?method=queryClerkInfo">
				<ec:exportXls fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="radio" name="itemlist" value="${clerk.cut_id}" style="border:0px" />
					</ec:column>
					
					<ec:column property="STUEMPID" title="学工号" width="60" escapeAutoFormat="true">
					</ec:column>
					
					<ec:column property="STUEMPNAME" title="姓名" width="80" />
					<ec:column property="DEPT_NAME" title="所属部门" width="120" />
					<ec:column property="IFOFFICE" title="考勤类别" width="60" />
				</ec:row>
			</ec:table>

		</div>
 <!--<a href="#" onclick="window.open('clerk.do?method=viewClerkDetail&clerkId=${clerk.cut_id}','详细信息','height=550,width=500,status=yes,toolbar=no,menubar=no,location=no');" >详细信息</a>-->

<script language="java">
function showDetail(clerkName,clerkId)
{
var name=encodeURI(clerkName);

}
</script>

</body>

</html>

