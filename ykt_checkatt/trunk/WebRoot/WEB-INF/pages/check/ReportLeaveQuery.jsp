<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>������ѧУ԰һ��ͨ���ڹ���ϵͳ</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<SCRIPT language=javascript>


function back(){
window.open('login.htm','_self');
}

function check()
{
	var query_sDate=putin.query_sDate.value;
	var query_eDate=putin.query_eDate.value;
	var description=putin.register_description.value;

	if(query_sDate==''||query_eDate=='')
	{
		alert('�뽫������������');
		return false;
	}
		if(query_sDate>query_eDate)
	{		
		alert("��ʼ���ڲ��ܴ��ڽ���ʱ��");
		return false;
	}

}

</SCRIPT>

	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ��������ѯ </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="filterDiv" style="text-align: left;">
			<form name="leaveCheck" action="leaveReportQuery.do?method=queryLeaveReport" method="post">
				<jodd:form bean="request">
						��ʼ����:
						<input name="query_sDate" class="input_box" maxlength=20 readonly="readonly" style="width:80" value="<c:out value='${beginDate}'/>">
						<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begindate" style="cursor:pointer">
						��������:
						<input name="query_eDate" class="input_box" maxlength=20 readonly="readonly" style="width:80" value="<c:out value='${endDate}'/>">
						<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="enddate" style="cursor:pointer">
						�Ƿ�����:
						<select name="query_ifcheck">
							<option value="-1">
								����
							</option>
							<option value="1">
								������
							</option>
							<option value="0">
								δ����
							</option>
						</select>
						�Ƿ�ͬ��:
						<select name="query_ifagree">
							<option value="-1">
								����
							</option>
							<option value="1">
								ͬ��
							</option>
							<option value="0">
								��ͬ��
							</option>
						</select>
						&nbsp;&nbsp;
						<input name="Submit" type="Submit" class="submitButton" value=" �� ѯ ">&nbsp;&nbsp;&nbsp;
						<input name="reportLeave" type="button" style="color: red" class="submitButton" value="�������" onclick="window.location.href='leaveReportQuery.do?method=goLeaveReport';">
						&nbsp;&nbsp;
						<input name="reportLeave" type="button" style="color: red" class="submitButton" value="�������" onclick="window.location.href='leaveReportQuery.do?method=goReplaceLeaveReport';">
					<script type="text/javascript">
	    			new calendar("query_sDate", "calBegin", "%Y-%m-%d");	
	    			new calendar("query_eDate", "calEnd", "%Y-%m-%d");		
       				</script>
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
		<div id="titleDiv" >
			<strong> <font color="red"> <c:out value="${msg}" /> </font> </strong>
		</div>
		
		<div id="tableDiv">
			<ec:table items="leaveReportList" var="leave" rowsDisplayed="15" action="leaveReportQuery.do?method=queryLeaveReport" form="leaveCheck">
				<ec:exportXls fileName="clerkList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column 
						property="REPROT_DATE" 
						title="�������" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
						width="120" 
						
					/>
					<ec:column 
						property="LEAVE_ID" 
						title="�������" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
						width="80" 
						
					/>
					<ec:column property="LEAVE_BEGINDATE" 
						title="��ʼ����" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
						width="120" 
					/>
					<ec:column property="LEAVE_BEGINTIME" 
						title="��ʼʱ��" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
					/>
					<ec:column property="LEAVE_ENDDATE" 
						title="��������" 
						width="120" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
					/>
					<ec:column property="LEAVE_ENDTIME" 
						title="����ʱ��" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: left"
						sortable="false"
					/>
					<ec:column property="IFCHECK" 
						title="�Ƿ�����" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					/>
					<ec:column property="IFAGREE" 
						title="�Ƿ�ͬ��" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					/>
					<ec:column property="��ϸ��Ϣ" 
						title="��ϸ��Ϣ" 
						width="80" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					>
						<a href="leaveReportQuery.do?method=leaveReportDetailInfo&leaveReportId=${leave.ID}">��ϸ��Ϣ</a>
					</ec:column>
					<ec:column property="�޸�" 
						title="�޸�" 
						width="50" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					>
						<c:choose>
							<c:when test="${leave.IFAGREE=='ͬ��'}">
								<a href=""></a>
							</c:when>
							<c:when test="${leave.IFAGREE=='��ͬ��'}">
								<a href="leaveReportQuery.do?method=goLeaveReport&leaveReportId=${leave.ID}">�޸�</a>
							</c:when>
							<c:otherwise>
								<a href="leaveReportQuery.do?method=goLeaveReport&leaveReportId=${leave.ID}">�޸�</a>
							</c:otherwise>
						</c:choose>
					</ec:column>
					<ec:column property="ɾ��" 
						title="ɾ��" 
						width="50" 
						headerStyle="text-align:center" 
						style="text-align: center"
						sortable="false"
					>
						<c:choose>
							<c:when test="${leave.IFAGREE=='ͬ��'}">
								<a href=""></a>
							</c:when>
							<c:when test="${leave.IFAGREE=='��ͬ��'}">
								<a href="leaveReportQuery.do?method=deleteLeaveReport&leaveId=${leave.ID}">ɾ��</a>
							</c:when>
							<c:otherwise>
								<a href="leaveReportQuery.do?method=deleteLeaveReport&leaveId=${leave.ID}">ɾ��</a>
							</c:otherwise>
						</c:choose>
					</ec:column>
				</ec:row>
			</ec:table>
		</div>

	</body>
</html>
