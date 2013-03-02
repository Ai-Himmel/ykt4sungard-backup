<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
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
			<strong> <font class="medium"> 非坐班工作时间统计 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<form name="create" method="post" action="workInfo.do?method=custWorkTimeInfoStat">
				<jodd:form bean="request">
					部&nbsp;&nbsp;门:
					<select name="deptId" style="width: 150">
						<!-- 
						<option value="all">
							所有
						</option>
						-->
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptName}" />
							</option>
						</c:forEach>
					</select>
					&nbsp;&nbsp;
					日期范围:
					<input class="input_box" style="width:80" maxlength=20 name="startDate" readonly="readonly" value="<c:out value='${startDate}' />" >
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
					<input class="input_box" style="width:80" maxlength=20 name="endDate" readonly="readonly" value="<c:out value='${endDate}' />" >
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
					<script type="text/javascript">
        				new calendar("startDate", "calBegin", "%Y-%m-%d");
        				new calendar("endDate", "calEnd", "%Y-%m-%d");
    				</script>
				    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<input name="createButton" type="submit" class="submitButton" value=" 统 计 " />
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
			<ec:table items="custWorkTimeList" var="custWorkTime" rowsDisplayed="15" action="workInfo.do?method=custWorkTimeInfoStat" >
				<ec:exportXls fileName="clerkList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column 
						property="deptName" 
						title="所属部门" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
						width="200" 
						
					/>
					<ec:column 
						property="stuempId" 
						title="学/工号" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
						width="150" 
						
					/>
					<ec:column property="custName" 
						title="姓  名" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
						width="150" 
					/>
					<ec:column property="workTime" 
						title="工作时间(小时)" 
						width="120" 
						cell="number"
						format="##0.00"
						headerStyle="text-align:center" 
						style="text-align: right"
						sortable="false"
					/>
					<ec:column property="pubRestH" 
						title="公事假(小时)" 
						width="120" 
						cell="number"
						format="##0.00"
						headerStyle="text-align:center" 
						style="text-align: right"
						sortable="false"
					/>
					<ec:column property="personRestH" 
						title="私事假(小时)" 
						width="120" 
						cell="number"
						format="##0.00"
						headerStyle="text-align:center" 
						style="text-align: right"
						sortable="false"
					/>
					<ec:column property="totleTime" 
						title="合计(小时)" 
						width="120" 
						cell="number"
						format="##0.00"
						headerStyle="text-align:center" 
						style="text-align: right"
						sortable="false"
					/>
				</ec:row>
			</ec:table>
		</div>
	</body>
</html>
		