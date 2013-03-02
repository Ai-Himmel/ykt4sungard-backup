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
			考勤人员设置
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
				<form id="queryform" method="post" action="clerkManager.do?method=QueryAvailablePerson" name="Search">
					学&nbsp;&nbsp;&nbsp;&nbsp;号:&nbsp;<td></td>
					<input class="text" type="text" name="search_personCode" size="11" style="width: 100">
					姓&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;名:&nbsp;
					<input class="text" type="text" name="search_personName" size="10"  style="width: 100">
					<p>
					</p>
					<div>
				
				卡类别:&nbsp;
					<select name="search_cardType" style="width: 100">
						<option value="all">
							所有
						</option>
						<c:forEach var="cardType" items="${cardTypeList}">
							<option value="<c:out value="${cardType.value}"/>">
								<c:out value="${cardType.caption}" />
							</option>
						</c:forEach>
					</select>
					身份类别:&nbsp;
					</td>
					<select name="search_personType" style="width: 100">
						<option value="all">
							所有
						</option>
						<c:forEach var="personType" items="${personTypeList}">
							<option value="<c:out value="${personType.type}"/>">
								<c:out value="${personType.name}" />
							</option>
						</c:forEach>
					</select>
					部&nbsp;&nbsp;&nbsp;&nbsp;门:&nbsp;
					<select name="search_department" style="width: 200">
						<option value="all">
							所有
						</option>
						<c:forEach var="department" items="${departList}">
							<option value="<c:out value="${department.dept_code}"/>">
								<c:out value="${department.dept_name}" />
							</option>
						</c:forEach>
					</select>	
					<td class='tableHeader'>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
					&nbsp;&nbsp;&nbsp;&nbsp;
					<a href="#" onclick="Search.submit();">查询</a>
					&nbsp;&nbsp;&nbsp;&nbsp;
					<input type="reset" value="重设"/>
					</div>
					<p></p>
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
			<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/modify.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_do_no_confirm(document.forms.clerkForm,'设置考勤人员','<c:url value="clerkManager.do?method=load4setupClerk" />');">设 置</A> </span>
		</div>


		<div id="tableDiv">
		<form id="clerkForm" action="clerkManager.do?method=load4setupClerk" method="post">
			<ec:table items="searchRes" var="clerk" rowsDisplayed="10" 
			action="clerkManager.do?method=QueryAvailablePerson" form="clerkForm">
				<ec:exportXls fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${clerk.customer_id}" style="border:0px" />
					</ec:column>
					<ec:column property="card_id" title="卡号" width="60" />
					<ec:column property="stuemp_no" title="学工号" width="60" />
					<ec:column property="cut_name" title="姓名" width="120" />
					<ec:column property="type" title="卡类型" width="60" />
					<ec:column property="p_type_name" title="身份类别" width="120" />
					<ec:column property="dept_name" title="部门" width="120" />
				</ec:row>
			</ec:table>
         </form>
		</div>

	</body>

</html>

