<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
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
	var startDate=extrastatic.extra_startDate.value;
	var endDate=extrastatic.extra_endDate.value;
	if(startDate==''||endDate=='')
	{
		alert('�뽫������������');
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

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
�Ӱ����ͳ��
</font>
</strong>
</div>

<div id=lineDiv class="hrLine" >
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>

<div id="filterDiv" style="text-align: left;">
  <form name="extrastatic" action="extraWork.do?method=staticExtraInfo" method="post" onsubmit="return check();">
	  <jodd:form bean="request">
����:
<input name="extra_trueName" class="input_box"  maxlength=20>
&nbsp;&nbsp;&nbsp;
��λ:
<select name="extra_deptId">
	<option value="">
		����
	</option>
    <c:forEach var="department" items="${departmentTree}">
	  <option value="<c:out value="${department.deptId}"/>">
      <c:out value="${department.deptTitle}" />
	  </option>
	</c:forEach>
</select>
&nbsp;&nbsp;&nbsp;
��ʼ����
<input class="input_box"  maxlength=20 name="extra_startDate" readonly="true" value="<%=request.getParameter("extra_startDate")==null?"":request.getParameter("extra_startDate")%>">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
&nbsp;&nbsp;&nbsp;
��ֹ����
<input  name="extra_endDate" class="input_box"  maxlength=20 readonly="true" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
			  <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
			   <script type="text/javascript">
			    new calendar("extra_startDate", "calBegin", "%Y-%m-%d");
                new calendar("extra_endDate", "calEnd", "%Y-%m-%d");				
               </script>
			   <input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
&nbsp;&nbsp;&nbsp;
 <input name="Submit" type="submit" class="button_nor" value="�� ѯ" > 

		</jodd:form>
	</form>
</div>

<div id=lineDiv class="hrLine" >
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>

	<div id="tableDiv">
         <ec:table items="staticInfoList" var="staticInfo" rowsDisplayed="5" action="extraWork.do?method=staticExtraInfo">
				<ec:exportXls fileName="staticInfoList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="departname" title="����" width="60" />
					<ec:column property="clerkname" title="��Ա" width="60" />
					<ec:column property="tatol" title="�Ӱ�������" width="120" />
					<ec:column property="confname" title="����" width="120" />
					<ec:column property="isseat" title="��Ա����" width="120" />

					<ec:column property="detail" title="��ϸ��Ϣ" width="60" sortable="false" >
					<a href="#"  onclick="window.open('extraWork.do?method=viewExtraDetail&startDate='+extrastatic.extra_startDate.value+'&endDate='+extrastatic.extra_endDate.value+'&clerkId=${staticInfo.cut_id}','��ϸ��Ϣ','height=550,width=500,status=yes,toolbar=no,menubar=no,location=no')">��ϸ��Ϣ</a>					
					</ec:column>
				</ec:row>
			</ec:table>
	</div>
</body>
</html>
