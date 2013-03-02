<%@page pageEncoding="GBK" import="org.king.check.vo.*,java.util.*"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>������ѧУ԰һ��ͨ���ڹ���ϵͳ</title>
		<%String msg = (String) request.getAttribute("msg");
			if (msg != null) {

				%>
		<SCRIPT language=javascript>
		alert('<%=msg%>');
</SCRIPT>
		<%}%>

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
	var startDate=noSeat.dutyInfo_startDate.value;
	var endDate=noSeat.dutyInfo_endDate.value;
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
	<body>

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ������Ա������ˮ��ѯ </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<form action="checkStatic.do?method=getCheckSerial" method="post" name="noSeat" onsubmit="return validate();">
				<jodd:form bean="request">
					��&nbsp;&nbsp;��:
					<select name="dutyInfo_deptId" style="width: 150">
						<option value="">
							����
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptName}" />
							</option>
						</c:forEach>
					</select>
					
					&nbsp;&nbsp;
                       ѧ����:&nbsp;
					<input class="text" type="text" name="dutyInfo_stuempNo" size="20" style="width:80">
					&nbsp;&nbsp;
					��ʼ����
					<input class="input_box" style="width:80" name="dutyInfo_startDate" readonly="readonly" value="<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>">
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
					&nbsp;&nbsp;&nbsp;
					��������
					<input name="dutyInfo_endDate" class="input_box" style="width:80" readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">

					<script type="text/javascript">
					    new calendar("dutyInfo_startDate", "calBegin", "%Y-%m-%d");
		                new calendar("dutyInfo_endDate", "calEnd", "%Y-%m-%d");				
		            </script>
					&nbsp;&nbsp;
					<input name="Submit" type="submit" class="submitButton" value=" �� ѯ ">
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
			<ec:table items="checkSerial" var="clerk" rowsDisplayed="15" action="checkStatic.do?method=getCheckSerial">
				<ec:exportXls  fileName="ClerkList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="stuemp_no" 
						headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						escapeAutoFormat="true"
						sortable="false"
						title="ѧ/����" 
						width="100"
						/>
					
					<ec:column property="cut_name" 
						headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title="��    ��" 
						width="100" 
					/>
					<ec:column property="dept_name" 
						headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title="��    ��" 
						width="200" 
					/>
					<ec:column property="check_date" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="��������" 
						width="80" 
					/>
					<ec:column property="week" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="����" 
						width="40" 
					/>
					<ec:column property="fact_ontime1" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�ϰ�ʱ��һ" 
						width="70" 
					/>
					<ec:column property="fact_offtime1" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�°�ʱ��һ" 
						width="70" 
					/>
					<ec:column property="fact_ontime2" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�ϰ�ʱ���" 
						width="70" 
					/>
					<ec:column property="fact_offtime2" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�°�ʱ���" 
						width="70" 
					/>
					<ec:column property="fact_ontime3" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�ϰ�ʱ����" 
						width="70" 
					/>
					<ec:column property="fact_offtime3" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�°�ʱ����" 
						width="70" 
					/>
					<ec:column property="fact_ontime4" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�ϰ�ʱ����" 
						width="70" 
					/>
					<ec:column property="fact_offtime4" 
						headerStyle="text-align:center"
						escapeAutoFormat="true"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�°�ʱ����" 
						width="70" 
					/>
				</ec:row>
			</ec:table>

		</div>
	</body>
</html>
