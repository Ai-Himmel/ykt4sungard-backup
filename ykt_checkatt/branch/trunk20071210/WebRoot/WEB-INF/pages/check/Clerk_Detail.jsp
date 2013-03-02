<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
	<head>
		<title>��ϸ��Ϣ</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>


	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ������Ա����ʱ���ƶ���ϸ��Ϣ </font> </strong>
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
						����:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<c:out value="${clerkInfo.stuempName}" />
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						�������ڲ���:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						<!-- 
						<SELECT name=search_dept style="width: 100">
							<option value="all">
								�����칫��
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
						����ʱ��:
					</td>
					<td align="left" valign="middle" bgcolor="#E7F1F5">
						
						�ϰ�ʱ��һ[
						<c:out value="${clerkInfo.onTime1}" />
						] &nbsp; �°�ʱ��һ[
						<c:out value="${clerkInfo.offTime1}" />
						] &nbsp; �ϰ�ʱ���[
						<c:out value="${clerkInfo.onTime2}" />
						] &nbsp; �°�ʱ���[
						<c:out value="${clerkInfo.offTime2}" />
						] &nbsp; �ϰ�ʱ����[
						<c:out value="${clerkInfo.onTime3}" />
						] &nbsp; �°�ʱ����[
						<c:out value="${clerkInfo.offTime3}" />
						] &nbsp; �ϰ�ʱ����[
						<c:out value="${clerkInfo.onTime4}" />
						] &nbsp; �°�ʱ����[
						<c:out value="${clerkInfo.offTime4}" />
						] &nbsp;
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						�����ƶ�:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						
						�������˵�ʱ��:
						<c:out value="${clerkInfo.leaveEarlyTime}" />
						���� &nbsp;����ٵ���ʱ��:
						<c:out value="${clerkInfo.overdueTime}" />
						���� &nbsp;�ϰ���ǰ�򿨲�������ʱ��:
						<c:out value="${clerkInfo.over}" />
						���� &nbsp;�°�������ͺ�ʱ��:
						<c:out value="${clerkInfo.delay}" />
						����
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						�Ƿ�����:
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<span class="right"> <c:out value="${clerkInfo.ifOffice}"/> </span>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						������Ϣ:
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
								
									��ǰ����Ӱ�
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
									
									�Ƴٴ���Ӱ�
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
									
									˫���մ���Ӱ�
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
									
									�ڼ��մ���Ӱ�
								</td>
							</TR>
						</table>
					</td>
				</tr>
				<tr>
					<td valign="middle" bgcolor="#D1DAE9" align="right">
						<span class="right">�Ӱ���㵥λ:</span>
					</td>
					<td valign="middle" bgcolor="#E7F1F5" align="left">
						<span class="right"> 
							<c:out value="${clerkInfo.overTime}" />
							 ����</span>
					</td>
				</tr>
				<tr align="center" valign=center>
					<td valign="middle">
					</td>
					<td valign="middle" align="center">
						<input type="button" value=" �� �� " class="submitButton" onClick="history.back();" />
					</td>
				</tr>
			</table>
		</div>
	</body>
</html>
