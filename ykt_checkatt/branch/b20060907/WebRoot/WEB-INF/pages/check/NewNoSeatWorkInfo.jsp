<%@page pageEncoding="GBK" import="org.king.check.vo.*,java.util.*"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
<head>
<title>������ѧУ԰һ��ͨ���ڹ���ϵͳ</title>
<% String msg=(String)request.getAttribute("msg");
if(msg!=null)
{
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
<body >

<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
��������Ա������־��ѯ
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
<form action="searchNoSeatWorkInfo.do?method=getNewFormatDutyTimeInfo" method="post" name="noSeat" onsubmit="return validate();">
<table width="100%" border=0 cellPadding=1 cellSpacing=1>
<tbody>
<tr>
<td>
<span class="medium">
��ʼ����
</span>
</td>
<td>
<input class="input_box"  maxlength=20 name="dutyInfo_startDate" readonly="true" value="<%=(String)request.getAttribute("startDate")==null?"":(String)request.getAttribute("startDate")%>">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
</td>
<td >
<span class="medium">
��������
</span >
 </td>
<td>
<input name="dutyInfo_endDate" class="input_box"  maxlength=20  readonly="true" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
</td>
           <script type="text/javascript">
                new calendar("dutyInfo_startDate", "calBegin", "%Y-%m-%d");
                new calendar("dutyInfo_endDate", "calEnd", "%Y-%m-%d");
            </script>
<td>
����:
					<select name="dutyInfo_deptId">
						<!--<option value="all">
							����
						</option>-->
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptTitle}" />
							</option>
						</c:forEach>
					</select>
</td>
<td>
<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
<a href="#" onclick="if(validate()==false) return false;noSeat.submit();">��ѯ</a>

&nbsp;
&nbsp;&nbsp;&nbsp;
<!--<input name="Submit" width="50" type="button" class="button_nor" value="���ɿ�����Ϣ" onclick="noSeat.action='noSeatWorkInfo.do?method=dealWithNoSeatClerkInfo';noSeat.submit();">-->
</td>
</tr>
</tbody>
</table>
</form>
</jodd:form>
</div>
<div id=lineDiv class="hrLine" >
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>
<% String titleStr=(String)request.getAttribute("titleStr");
List newFormatL=(List)request.getAttribute("newFormatL");
if(titleStr==null)
{
	titleStr="��Ϣ";
}
%>
<div>
<form id="infoform">
<table  border="1"  cellspacing="0"  cellpadding="0"  align="left" bordercolor=#445386>
<tbody>
    <tr>
    <% out.print(titleStr);%>
	</tr>
	<% if(newFormatL!=null&&!newFormatL.isEmpty())
	{
		Iterator ite=newFormatL.iterator();
		while(ite.hasNext())
		{
			DutyTimeVo dutyTimeVo=(DutyTimeVo)ite.next();
			out.print(dutyTimeVo.getDutyTimeStr());
		}

	}

	%>
</tbody>
</table>
</form>
</div>


</body>
</html>
