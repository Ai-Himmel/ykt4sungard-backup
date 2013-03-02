<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
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
function on_FD(){
	document.all("sd").click();
}
function on_validate(para){
	if(document.all(para).value!=''){
		document.forms[0].submit();
	}
	else{
		alert('��ѡ������');
	}
}
function validate()
{
	var startDate=noSeat.startDate.value;
	var endDate=noSeat.endDate.value;
	if(startDate==''||endDate=='')
	{
		alert("�뽫������������");
		return false;
	}
	if(startDate>endDate)
	{		
		alert("��ʼ���ڲ��ܴ��ڽ���ʱ��");
		return false;
	}
}
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ��������Ա������־��ѯ </font> </strong>
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
				<form action="searchNoSeatWorkInfo.do?method=searchNoSeatWorkInfo" method="post" name="noSeat" onsubmit="return validate();">
					&nbsp; ��ʼ����:
					<input class="input_box" maxlength=20 name="startDate" readonly="readonly" value="<%=request.getParameter("startDate")==null?"":request.getParameter("startDate")%>">
					&nbsp;
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
					&nbsp; ��������:
					<input name="endDate" class="input_box" maxlength=20 readonly="readonly" value="<%=request.getParameter("endDate")==null?"":request.getParameter("endDate")%>">
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
					<script type="text/javascript">
		                new calendar("startDate", "calBegin", "%Y-%m-%d");
		                new calendar("endDate", "calEnd", "%Y-%m-%d");
            		</script>
					&nbsp; &nbsp; ����:&nbsp;
					<select name="deptId">
						<option value="">
							����
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptTitle}" />
							</option>
						</c:forEach>
					</select>
					<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
					<a href="#" onclick="if(validate()==false) return false;noSeat.submit();">��ѯ</a> &nbsp; &nbsp;&nbsp;&nbsp;
					<input name="Submit" width="50" type="button" class="button_nor" value="���ɿ�����Ϣ" onclick="noSeat.action='noSeatWorkInfo.do?method=dealWithNoSeatClerkInfo';noSeat.submit();">
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
		<div id="tableDiv">
			<ec:table items="noSeatWorkInfoList" var="dutytime" rowsDisplayed="50" action="searchNoSeatWorkInfo.do?method=searchNoSeatWorkInfo">
				<ec:exportXls fileName="noSeatWorkInfoList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="department.name" title="����" width="60" />
					<ec:column property="clerk.clerkname" title="��Ա" width="60" />
					<ec:column property="ondutytime" title="�ϰ�ʱ��" width="120" />
					<ec:column property="offdutytime" title="�°�ʱ��" width="120" />
				</ec:row>
			</ec:table>

		</div>
	</body>
</html>
