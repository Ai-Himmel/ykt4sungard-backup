<%@page pageEncoding="GBK" import="org.king.check.vo.*,java.util.*"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>һ��ͨ���ڹ���ϵͳ</title>
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
		function validate() {
			var form = document.forms[0];
			var startDate=form.startDate.value;
			var endDate=form.endDate.value;
			if(startDate==''||endDate=='') {
				alert("�뽫������������");
				return false;
			}
			if(startDate>endDate) {		
				alert("��ʼ���ڲ��ܴ��ڽ���ʱ��");
				return false;
			}
			return true;
		}
		function queryCheckInfo() {
			if(validate()) {
				document.forms[0].submit();
			}
		}
		</SCRIPT>
	</head>
	<body>

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ������ϸ�� </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<html:form action="checkInfo.do?method=viewCheckDetail" method="post">
				<jodd:form bean="request">
					<table>
						<tr align="left">
							<td width="25%">
								��������
			                    <html:select property="locationId">
			                        <html:option value="">��ѡ��</html:option>
			                        <html:options collection="locationList" property="ID" labelProperty="NAME"/>
			                    </html:select>
							</td>
							<td width="25%">
								��ʼ����
								<html:text property="startDate" size="12" readonly="true"/>
								<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
							</td>
							<td width="50%">
								��������
								<html:text property="endDate" size="12" readonly="true"/>
								<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
								<script type="text/javascript">
								    new calendar("startDate", "calBegin", "%Y%m%d");
					                new calendar("endDate", "calEnd", "%Y%m%d");				
					            </script>
							</td>
							<td>
							</td>
						</tr>
						<tr>
							<td>
								ѧ&nbsp;&nbsp;��&nbsp;&nbsp;��
								<html:text property="stuempNo"  size="16" maxlength="50"/>
							</td>
							<td>
								��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��
								<html:text property="custName"  size="16" maxlength="50"/>
							</td>
							<td>
								�༶����
								<html:text property="className"  size="24" maxlength="100"/>
								&nbsp;&nbsp;
								<input name="Submit" type="button" class="submitButton" value=" �� ѯ " onclick="queryCheckInfo();">
							</td>
							<td>
							</td>
						</tr>
					</table>
				</jodd:form>
			</html:form>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="result" var="checkInfo" rowsDisplayed="50" action="checkInfo.do?method=viewCheckDetail">
				<ec:exportXls  fileName="checkInfoList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="STUEMPNO" headerStyle="text-align:left" style="text-align:left" filterable="false" 
						escapeAutoFormat="true" sortable="true" title="ѧ����" width="15%"/>
					<ec:column property="CUSTNAME" headerStyle="text-align:left" style="text-align:left" filterable="false" 
						sortable="true" title="����" width="15%" />
					<ec:column property="CLASSNAME" headerStyle="text-align:left" style="text-align:left" filterable="false" 
						sortable="true" title="�༶" width="25%" />
					<ec:column property="CHECKDATE" headerStyle="text-align:left" style="text-align:left" filterable="false" 
						sortable="true" title="��������" width="15%" />
					<ec:column property="CHECKTIME" headerStyle="text-align:left" style="text-align:left" filterable="false" 
						sortable="true" title="����ʱ��" width="15%" />
					<ec:column property="LOCATIONNAME" headerStyle="text-align:left" style="text-align:left" filterable="false" 
						sortable="true" title="��������" width="15%" />
				</ec:row>
			</ec:table>
		</div>
	</body>
</html>
