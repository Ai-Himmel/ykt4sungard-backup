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

		<div id="filterDiv" style="text-align: left;">
			<jodd:form bean="request">
				<form id="queryform" method="post" action="clerkManager.do?method=QueryAvailablePerson">
					学号:&nbsp;
					<input class="text" type="text" name="search_personCode" size="10">
					姓名:&nbsp;
					<input class="text" type="text" name="search_personName" size="10">
					卡号:&nbsp;
					<input class="text" type="text" name="search_card" size="10">
					类型:&nbsp;
					<select name="search_personType">
						<option value="all">
							所有
						</option>
						<c:forEach var="dictionary" items="${dictionarys}">
							<option value="<c:out value="${dictionary.id.dictValue}"/>">
								<c:out value="${dictionary.dictCaption}" />
							</option>
						</c:forEach>
					</select>
					部门:&nbsp;
					<select name="search_department">
						<option value="all">
							所有
						</option>
						<c:forEach var="department" items="${departments}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptTitle}" />
							</option>
						</c:forEach>
					</select>
					&nbsp; &nbsp;
					<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
				</form>
			</jodd:form>
		</div>
		
		<div id="operationDiv">
			<%@ include file="/pages/common/messages.jsp"%>
			<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/modify.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_do(document.forms.clerkForm,'设置考勤人员','<c:url value="clerkManager.do?method=load4setupClerk" />');">设 置</A> </span>
		</div>


		<div id="tableDiv">
		<form id="clerkForm" action="clerkManager.do?method=load4setupClerk" method="post">
			<ec:table items="clerks" var="clerk" rowsDisplayed="5" 
			action="clerkManager.do?method=QueryAvailablePerson" form="clerkForm">
				<ec:exportXls fileName="ClerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${clerk.person_code}" style="border:0px" />
					</ec:column>
					<ec:column property="person_code" title="学工号" width="60" />
					<ec:column property="person_name" title="姓名" width="120" />
					<ec:column property="dept_name" title="部门" width="120" />
					<ec:column property="is_clerk_title" title="考勤人员" width="120" />
					<ec:column property="is_seat" title="坐班情况" width="120" />

				</ec:row>
			</ec:table>
         </form>
		</div>




	</body>

</html>

