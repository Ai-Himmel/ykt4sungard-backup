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

function check()
{    
	if(document.all.cs_stuNo.value=='')
	{
		alert('�����뿼����Ա��ѧ���ţ�');
		return false;
	}
	if(document.all.cs_startDate.value==''||document.all.cs_endDate.value=='')
	{
		alert('�뽫������������');
		return false;
	}
		if(document.all.cs_startDate.value>document.all.cs_endDate.value)
	{		
		alert("��ʼ���ڲ��ܴ��ڽ���ʱ��");
		return false;
	}

}

</SCRIPT>

	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ���˳���������� </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<div id="filterDiv" style="text-align: left;">
			<form name="clerkstatic" action="checkStatic.do?method=getPersonCheckStatic" method="post" onsubmit="return check();">
				<jodd:form bean="request">
                       ѧ����:&nbsp;<td>
						&nbsp;&nbsp;&nbsp;&nbsp;
					</td>
					<input class="text" type="text" name="cs_stuNo" size="20" style="width:120">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;					
					��ʼ����
					<input class="input_box" style="width:100" name="cs_startDate" readonly="readonly" value="<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>">
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
					&nbsp;&nbsp;&nbsp;
					��������
					<input name="cs_endDate" class="input_box" style="width:100" readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">

					<script type="text/javascript">
					    new calendar("cs_startDate", "calBegin", "%Y-%m-%d");
		                new calendar("cs_endDate", "calEnd", "%Y-%m-%d");				
		            </script>
					&nbsp;&nbsp;&nbsp;&nbsp;
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
			<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#445386 bordercolordark=#ffffff id=submenu1>
				<tbody>
					<tr valign=middle>
						<td colspan="2" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader1">
							������
							<%=request.getAttribute("clerkName") == null ? "": request.getAttribute("clerkName")%>
							<br>
							ѧ/���ţ�
							<%=request.getAttribute("stuempNo") == null ? "": request.getAttribute("stuempNo")%>
							<br>
							���ţ�
							<%=request.getAttribute("deptName") == null ? "": request.getAttribute("deptName")%>
							<br>
							ͳ�����ڣ�
							<%=request.getAttribute("startDate") == null ? "": request.getAttribute("startDate")%>
							��
							<%=request.getAttribute("endDate") == null ? "": request.getAttribute("endDate")%>
						</td>
						<td colspan="3" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader1">
							Ӧ�ϰ�ʱ�䣺
							<%=request.getAttribute("workValue") == null ? "0": request.getAttribute("workValue")%>
							Сʱ&nbsp;&nbsp;&nbsp;&nbsp;ʵ���ϰ�ʱ�䣺
							<%=request.getAttribute("factWorkValue") == null ? "0": request.getAttribute("factWorkValue")%>
							Сʱ<br>
							���ʱ�䣺
							<%=request.getAttribute("leaveTimeValue") == null ? "0": request.getAttribute("leaveTimeValue")%>
							Сʱ&nbsp;&nbsp;&nbsp;&nbsp;ȱϯʱ�䣺
							<%=request.getAttribute("leaveValue") == null ? "0": request.getAttribute("leaveValue")%>
							Сʱ<br>
							�ٵ�ʱ�䣺
							<%=request.getAttribute("delayValue") == null ? "0": request.getAttribute("delayValue")%>
							Сʱ&nbsp;&nbsp;&nbsp;&nbsp;����ʱ�䣺
							<%=request.getAttribute("leaveEarlyValue") == null ? "0": request.getAttribute("leaveEarlyValue")%>
							Сʱ<br>
							�Ӱ�ʱ�䣺
							<%=request.getAttribute("overValue") == null ? "0": request.getAttribute("overValue")%>
							Сʱ&nbsp;&nbsp;&nbsp;&nbsp;˫���ռӰ�ʱ�䣺
							<%=request.getAttribute("twoRestValue") == null ? "0": request.getAttribute("twoRestValue")%>
							Сʱ
						</td>
					</tr>
				</tbody>
			</table>
		</div>
		<c:if test="${ifOffice=='1'}">
		<div id="tableDiv">
			<ec:table items="checkDetail" var="clerk" rowsDisplayed="50" action="checkStatic.do?method=getPersonCheckStatic">
				<ec:exportXls  fileName="ClerkList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="STUEMP_NO" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="ѧ/����" 
						width="200"
						/>
					
					<ec:column property="CUT_NAME" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="��    ��" 
						width="250" 
					/>
					<ec:column property="CHECK_DATE" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="��������" 
						width="150" 
					/>
					<ec:column property="FACT_ONTIME1" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�ϰ�һ" 
						width="100" 
					/>
					<ec:column property="FACT_OFFTIME1" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�°�һ" 
						width="100" 
					/>
					<ec:column property="FACT_ONTIME2" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�ϰ��" 
						width="100" 
					/>
					<ec:column property="FACT_OFFTIME2" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�°��" 
						width="100" 
					/>
					<ec:column property="FACT_ONTIME3" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�ϰ���" 
						width="100" 
					/>
					<ec:column property="FACT_OFFTIME3" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�°���" 
						width="100" 
					/>
					<ec:column property="FACT_ONTIME4" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�ϰ���" 
						width="100" 
					/>
					<ec:column property="FACT_OFFTIME4" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�°���" 
						width="100" 
					/>
				</ec:row>
			</ec:table>

		</div>
		</c:if>
		<c:if test="${ifOffice=='2'}">
		<div id="tableDiv">
			<ec:table items="checkDetail" var="clerk" rowsDisplayed="50" action="checkStatic.do?method=getPersonCheckStatic">
				<ec:exportXls  fileName="ClerkList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="STUEMP_NO" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="ѧ/����" 
						width="200"
						/>
					
					<ec:column property="CUT_NAME" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="��    ��" 
						width="250" 
					/>
					<ec:column property="CHECK_DATE" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="��������" 
						width="200" 
					/>
					<ec:column property="FACT_ONTIME" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�ϰ�ʱ��" 
						width="200" 
					/>
					<ec:column property="FACT_OFFTIME" 
						headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title="�°�ʱ��" 
						width="200" 
					/>
				</ec:row>
			</ec:table>

		</div>
		</c:if>
	</body>
</html>
