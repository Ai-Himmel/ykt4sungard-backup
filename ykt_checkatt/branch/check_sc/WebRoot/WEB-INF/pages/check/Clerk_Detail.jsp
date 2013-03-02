<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<title>详细信息</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>


	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 考勤人员工作时间制度详细信息 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
				<tr align="center" valign=center>
					<td align="right" valign="middle" bgcolor="#D1DAE9" width=15%>
						姓名:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${clerkInfo.stuempName}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						所属考勤部门:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<!-- 
						<SELECT name=search_dept style="width: 100">
							<option value="all">
								招生办公室
							</option>
							<option value="1"></option>
							<option value="2"></option>
						</SELECT>
						-->
						<c:out value="${clerkInfo.deptName}"/>
					</td>
				</tr>

				<tr align="center" valign=center>
					<td align="right" valign="middle" bgcolor="#D1DAE9">
						工作时间:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						
						上班时间一[
						<c:out value="${clerkInfo.onTime1}" />
						] &nbsp; 下班时间一[
						<c:out value="${clerkInfo.offTime1}" />
						] &nbsp; 上班时间二[
						<c:out value="${clerkInfo.onTime2}" />
						] &nbsp; 下班时间二[
						<c:out value="${clerkInfo.offTime2}" />
						] &nbsp; 上班时间三[
						<c:out value="${clerkInfo.onTime3}" />
						] &nbsp; 下班时间三[
						<c:out value="${clerkInfo.offTime3}" />
						] &nbsp; 上班时间四[
						<c:out value="${clerkInfo.onTime4}" />
						] &nbsp; 下班时间四[
						<c:out value="${clerkInfo.offTime4}" />
						] &nbsp;
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						考勤制度:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						
						允许早退的时间:
						<c:out value="${clerkInfo.leaveEarlyTime}" />
						分钟 &nbsp;允许迟到的时间:
						<c:out value="${clerkInfo.overdueTime}" />
						分钟 &nbsp;上班提前打卡不允许超过时间:
						<c:out value="${clerkInfo.over}" />
						分钟 &nbsp;下班打卡允许滞后时间:
						<c:out value="${clerkInfo.delay}" />
						分钟
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						是否坐班:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<span class="right"> <c:out value="${clerkInfo.ifOffice}"/> </span>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						其他信息:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<TR>
								<td width="15%" align="left" class="right">
								
								<c:choose>
									<c:when test="${clerkInfo.aheadOverTime=='1'}">
										<input type="checkbox" name="search_aheadOverTime" checked="checked"/>
									</c:when>
									<c:otherwise>
										<input type="checkbox" name="search_aheadOverTime"/>
									</c:otherwise>
								</c:choose>
								
									提前打卡算加班
								</td>
								<td width="15%" align="left" class="right">
									
								<c:choose>
									<c:when test="${clerkInfo.delayOverTime=='1'}">
										<input type="checkbox" name="search_delayOverTime" checked="checked"/>
									</c:when>
									<c:otherwise>
										<input type="checkbox" name="search_delayOverTime" />
									</c:otherwise>
								</c:choose>
									
									推迟打卡算加班
								</td>
								<td width="15%" align="left" class="right">
								<c:choose>
									<c:when test="${clerkInfo.twoReset=='1'}">
										<input type="checkbox" name="search_twoReset" checked="checked"/>
									</c:when>
									<c:otherwise>
										<input type="checkbox" name="search_twoReset" />
									</c:otherwise>
								</c:choose>
									
									双休日打卡算加班
								</td>
								<td width="15%" align="left" class="right">
								<c:choose>
									<c:when test="${clerkInfo.holiday=='1'}">
										<input type="checkbox" name="search_holiday" checked="checked"/>
									</c:when>
									<c:otherwise>
										<input type="checkbox" name="search_holiday" />
									</c:otherwise>
								</c:choose>
									
									节假日打卡算加班
								</td>
							</TR>
						</table>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						<span class="right">加班计算单位:</span>
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<span class="right"> 
							<c:out value="${clerkInfo.overTime}" />
							 分钟</span>
					</td>
				</tr>
				<tr align="center" valign=center>
					<td valign="middle">
					</td>
					<td valign="middle" align="center">
						<input type="button" value=" 返 回 " class="submitButton" onClick="history.back();" />
					</td>
				</tr>
			</table>
		</div>
	</body>
</html>
