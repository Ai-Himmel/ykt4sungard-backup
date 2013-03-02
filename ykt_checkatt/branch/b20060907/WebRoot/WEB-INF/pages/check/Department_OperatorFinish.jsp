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
<div class="pageTitle">
<c:out value="${msg}" />
</div>
<form name="clerkForm"  action="department.do?method=addConf" method="post" >
<jodd:form bean="request">
       <%@ include file="/pages/common/messages.jsp" %>
        <table class="border" width=100% cellSpacing=0 cellPadding=2 align="center">
           <tr>
                <td class="left" width="20%">排班部门:</td>
                <td class="right" align="left">
                    <c:out value="${dptName}" />
                </td>
            </tr>
            <tr>
                <td class="left">考勤制度:</td>
                <td class="right">
					<c:out value="${workconfDetail}" />
					<input type="hidden" name="new_workconfDetail" value="<c:out value='${workconfDetail}' />"/>
                </td>
            </tr>
            <tr>
                <td class="left">考勤工作时间:</td>
                <td class="right"> 
				<c:out value="${timeDetail}" />
				<input type="hidden" name="new_timeDetail" value="<c:out value='${timeDetail}' />"/>
			    </td>
            </tr>
			<tr>
               <td class="left" width="20%">
			   设置时间:
			   </td>
               <td class="right">
				<span class="medium">
				开始日期
				</span> &nbsp;
                <c:out value="${startDate}" />
				&nbsp;	
				结束日期
				&nbsp;
				 <c:out value="${endDate}" />
               </td>
            </tr>
			<tr>
                <td class="left" width="20%">坐班:</td>
                <td class="right">
                   <c:out value="${isSeat}" />
                </td>
            </tr>
            <tr>
                <td colspan="2" class="bottom">
                    <input type="button" class="submitButton" name="submitButton" value="<c:out value='${btnInfo}' />"  style="margin-right:60px" onclick="<c:out value='${actionUrl}' />"/>
					 <input type="button" class="submitButton" name="submitButton" value="退出"  style="margin-right:60px" onclick="window.location.href='department.do?method=goDeptConf';"/>
					<BUTTON onclick="history.back();">上一步</BUTTON>
                   
                </td>
            </tr>
        </table>
		</jodd:form>
</form>

<div id="titleDiv" class="pageTitle" style="display:<c:out value='${display}'/>">
<strong>
<font class="medium">
<c:out value="${dptName}" />重叠的排班信息
</font>
</strong>
</div>

<div id="tableDiv" style="display:<c:out value='${display}'/>">
			<ec:table items="existList" var="dptConf" rowsDisplayed="5" action="department.do?method=addConf">
				<ec:exportXls fileName="existList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="dptname" title="部门" width="60" />
                    <ec:column property="startdate" title="开始时间" width="60" />
					<ec:column property="enddate" title="结束时间" width="60" />
					<ec:column property="wconfname" title="考勤制度" width="120" />
					<ec:column property="tconfname" title="工作时间" width="120" />
					
				</ec:row>
			</ec:table>

		</div>
</body>
</html>
