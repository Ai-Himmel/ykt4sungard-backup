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
	</head>
	<div id="titleDiv" class="pageTitle">
		<strong> <font class="medium"> 修改请假信息 </font> </strong>
	</div>
	<div id="tableDiv">
		<form name="update" method="post" action='leaveInfo.do?method=update'>
			<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
			<input type="hidden" value='<c:out value="${new_leaveInfoId}" />' name="new_leaveInfoId" />
			<input type="hidden" value='<c:out value="${clerkName}" />' name="new_clerkName" />
			<input type="hidden" value='<c:out value="${custId}" />' name="new_custId" />
				<tbody>
					<tr align="center" valign=center>
						<td width="10%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
							姓名
						</td>
						<td width="15%" align="left" valign="middle" bgcolor="#E7F1F5">
							<c:out value='${clerkName}' />
						</td>
		                  <td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">&nbsp;</td>
		                  <td width="65%"  valign="middle" class="tableHeader3">&nbsp;</td>
					</tr>

					<tr align="center" valign=center>
						<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
							开始日期
						</td>
						<td align="left" valign="middle" class="tableHeader3">
							<input style="width:100" name="new_startDate" class="input_box" maxlength=20 readonly="true" value="<c:out value='${new_startDate}' />">
							<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" >
						</td>
						<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2"> 
							开始时间 
						</td>
						<td valign="middle" class="tableHeader3">
							<select name="new_startHour">
								<option value="<c:out value='${new_startHour}' />">
									<c:out value='${new_startHour}' />
								</option>
								<%for (int i = 1; i < 24; i++) {
									String mm="";
									if (i<10){
										mm = "0"+String.valueOf(i);
									}else{
										mm = String.valueOf(i);
									}
								%>
								<option value="<%=mm%>">
									<%=mm%>
								</option>
								<%}%>
							</select>点
							<select name="new_startMin">
								<option value="<c:out value='${new_startMin}' />">
									<c:out value='${new_startMin}' />
								</option>
								<%for (int i = 1; i < 60; i++) {
									String mm="";
									if (i<10){
										mm = "0"+String.valueOf(i);
									}else{
										mm = String.valueOf(i);
									}
								%>
								<option value="<%=mm%>">
									<%=mm%>
								</option>
								<%}%>
							</select>分
						</td>
					</tr>
					<tr>
						<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
							结束日期
						</td>
						<td align="left" valign="middle" class="tableHeader3">
							<input style="width:100"  name="new_endDate" class="input_box" maxlength=20 readonly="true" value="<c:out value='${new_endDate}' />">
							<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" >
						</td>
						<td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2"> 
							结束时间 
						</td>
						<td valign="middle" class="tableHeader3">
							<select name="new_endHour">
								<option value="<c:out value='${new_endHour}' />">
									<c:out value='${new_endHour}' />
								<%for (int i = 1; i < 24; i++) {
									String mm="";
									if (i<10){
										mm = "0"+String.valueOf(i);
									}else{
										mm = String.valueOf(i);
									}
								%>
								<option value="<%=mm%>">
									<%=mm%>
								</option>
								<%}%>
								</option>
							</select>点
							<select name="new_endMin">
								<option value="<c:out value='${new_endMin}' />">
									<c:out value='${new_endMin}' />
								</option>
								<%for (int i = 1; i < 60; i++) {
									String mm="";
									if (i<10){
										mm = "0"+String.valueOf(i);
									}else{
										mm = String.valueOf(i);
									}
								%>
								<option value="<%=mm%>">
									<%=mm%>
								</option>
								<%}%>
							</select>分
						</td>
						<script type="text/javascript">
						    new calendar("new_startDate", "calBegin", "%Y-%m-%d");
			                new calendar("new_endDate", "calEnd", "%Y-%m-%d");				
		               	</script>
					</tr>
	                <tr>
	                  <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2"> 
	                  		请假类别 
	                  </td>
	                  <td align="left" valign="middle" class="tableHeader3">
	                  <select name="new_type" style="width: 120">
	                      	<option value="<c:out value='${new_type}' />"> <c:out value='${leaveInfoName}' /> </option>
							<c:forEach var="leaveType" items="${leaveType}">
								
								<option value="<c:out value="${leaveType.DICT_VALUE}"/>">
									<c:out value="${leaveType.DICT_CAPTION}" />
								</option>
							</c:forEach>
							
	                    </select>
	                  </td>
	                  <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2"> 
	                  		请假原因 
	                  </td>
	                  <td align="left" valign="middle" class="tableHeader3">
	                  	<input name="new_description" class="input_box" maxlength=20 value="<c:out value='${new_description}' />">
	                  </td>
	                </tr>
					<tr>
						<td colspan="4"  height="40" align="center" valign="middle" class="tdborder02">
							<input name="Submit" type="submit" class="submitButton" value=" 确 定 ">
							<input name="Submit" type="button" class="submitButton" value=" 返 回 " onclick="history.back();">
						</td>
					</tr>
				</tbody>
			</table>
		</form>
	</div>