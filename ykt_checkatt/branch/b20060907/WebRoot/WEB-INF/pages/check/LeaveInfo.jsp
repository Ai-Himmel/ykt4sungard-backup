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

function update(url,clerkname)
{
	var new_url=url+"&pre_clerkName="+encodeURI(clerkname);
	ec.action=new_url;
	ec.submit();
}
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
	var startDate=leave.leave_startDate.value;
	var endDate=leave.leave_endDate.value;
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
<% String msg=(String)request.getAttribute("msg");
if(msg!=null)
{
%>
	alert('<%=msg%>');
<%}%>
</SCRIPT>

</head>
<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
��������ѯ
</font>
</strong>
</div>
<tr>
&nbsp;
</tr>
<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
<div id="filterDiv" style="text-align: left;">
<jodd:form bean="request">
  <form action="leaveInfo.do?method=searchLeaveInfo" method="post" name="leave" onsubmit="return validate();">
��ʼ����
<input class="input_box"  maxlength=20 name="leave_startDate" readonly="true" value="<%=request.getParameter("leave_startDate")==null?"":request.getParameter("leave_startDate")%>">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
��������
<input name="leave_endDate" class="input_box"  maxlength=20  readonly="true" value="<%=request.getParameter("leave_endDate")==null?"":request.getParameter("leave_endDate")%>">
<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
           <script type="text/javascript">
                new calendar("leave_startDate", "calBegin", "%Y-%m-%d");
                new calendar("leave_endDate", "calEnd", "%Y-%m-%d");
            </script>
�� ��
<input class="input_box"  maxlength=20 name="leave_trueName" value="<%=request.getParameter("leave_trueName")==null?"":request.getParameter("leave_trueName")%>">
�� λ
<select name="leave_deptId">
						<option value="">
							����
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptTitle}" />
							</option>
						</c:forEach>
					</select>
<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">&nbsp;
<a href="#" onclick="if(validate()==false) return false;leave.submit();">��ѯ</a>
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
        <div id="operationDiv">
			<%@ include file="/pages/common/messages.jsp"%>
			<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_delete_leaveInfo(document.forms.ec,'�����Ϣ','<c:url value="leaveInfo.do?method=delete" />');">ɾ ��</A> </span>
		</div>
		<div id="tableDiv">
			<ec:table items="leaveInfoList" var="leaveinfo" rowsDisplayed="5" action="leaveInfo.do?method=searchLeaveInfo">
				<ec:exportXls fileName="leaveInfoList.xls" tooltip="���� Excel" />
				<ec:row>
				<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${leaveinfo.leaveinfoId}" style="border:0px" />
					</ec:column>
					<ec:column property="cardnumber" title="����" width="60" />
					<ec:column property="clerkname" title="����" width="60" />
					<ec:column property="departname" title="��λ" width="80" />
					<ec:column property="startdate" title="��ٿ�ʼʱ��" width="120" />
					<ec:column property="enddate" title="��ٽ���ʱ��" width="120" />
					<ec:column property="description" title="���ԭ��" width="120" />
                    <ec:column property="confname" title="����" width="60" />
					<ec:column property="isseat" title="��Ա����" width="60" />
					<ec:column property="recordDate" title="��¼ʱ��" width="60" />
					<ec:column property="operatorName" title="��¼��Ա" width="60" />
					<ec:column property="update" title="�޸�" width="40" sortable="false" >
					<a href="#" onclick="update('leaveInfo.do?method=preUpdate&pre_leaveinfoId=${leaveinfo.leaveinfoId}','${leaveinfo.clerkname}');">�޸�</a>
					</ec:column>
				</ec:row>
			</ec:table>

		</div>
</body>
</html>
