<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<%@ page import="java.util.*" %>
<%@ page import="org.king.check.domain.Department"%>
<html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<%boolean issysadmin = Boolean.parseBoolean(session.getAttribute("issysadmin").toString());%>
		<SCRIPT language="javascript">


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
function docheck(){
   document.forms[0].submit();
}

function shoud(para)
{
     window.open('/check/dailyteacherdetail.do?method=getTeacherShoud'+para,
    	         "a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
}
function real(para)
{
     window.open('/check/dailyteacherdetail.do?method=getTeacherOther'+para,
    	         "a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
}
function late(para)
{
     window.open('/check/dailyteacherdetail.do?method=getTeacherOther'+para,
    	         "a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
}
function leave(para)
{
     window.open('/check/dailyteacherdetail.do?method=getTeacherOther'+para,
    	         "a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
}

<%
	String beginDate="";
	if(request.getAttribute("beginDate")!=null){
		beginDate = request.getAttribute("beginDate").toString();
	}else if(session.getAttribute("beginDate")!=null){
	    beginDate = session.getAttribute("beginDate").toString();
	}
	String endDate="";
	if(request.getAttribute("endDate")!=null){
		endDate = request.getAttribute("endDate").toString();
	}else if(session.getAttribute("endDate")!=null){
	   endDate = session.getAttribute("endDate").toString();
	}
%>
<% 
  if(request.getAttribute("msg")!=null){	
%>
    alert('<%=request.getAttribute("msg").toString()%>')
<%
}    
%>
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ��ʦ�����ձ��� </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
				<html:form action="teacheckreport.do?method=dailyreport" method="post" >
                    <table width="100%">
                        <tr>
                            <td width="20%">
                                &nbsp;��ʦ���ţ�
                                <html:text property="stuempNo" maxlength="50"/>
                            </td>
                            <td width="20%">
                                &nbsp;��ʦ������
                                <html:text property="custName" maxlength="50"/>
                            </td>
                            <td width="50%">
                                &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�̣�
                                <html:select property="courseId">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="course" property="COURSEID" labelProperty="COURSENAME"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;��ʼ���ڣ�
					            <html:text property="beginDate" size="10"readonly="readonly" value="<%=beginDate%>" />
					            <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                            </td>
                            <td>
                                &nbsp;�������ڣ�
					            <html:text property="endDate" size="10" readonly="readonly" value="<%=endDate%>" />
					            <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("beginDate", "calBegin", "%Y%m%d");
                                    new calendar("endDate", "calEnd", "%Y%m%d");
                                </script>
                            </td>
                            <td>
                                &nbsp;<input name="Submit" width="50" type="button" class="button_nor" value="��  ѯ" onclick="docheck()">
                            </td>
                        </tr>
                    </table>
				</html:form>
		</div>
	
		
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="teacheckList" var="tea"  rowsDisplayed="50" action="teacheckreport.do?method=dailyreport">
				<ec:exportXls fileName="teachecklist.xls"  tooltip="���� Excel" />
				<ec:row>			   		
					<ec:column property="stuempno" title="ѧ����" width="12%" escapeAutoFormat="true"/>
					<ec:column property="custname" title="��ʦ" width="12%" />
					<ec:column property="coursename" title="�γ�" width="20%" />
					<ec:column property="coursenum" title="Ӧ���δ�" width="8%" >
						<a href="javascript:void(0);" onclick="shoud('&courseid=${tea.courseid}&stuempno=${tea.stuempno}&begindate=<%=beginDate%>&enddate=<%=endDate%>')">${tea.coursenum}</a>
					</ec:column>
					<ec:column property="checknum" title="ʵ���δ�" width="8%" >
					 	<a href="javascript:void(0);" onclick="real('&courseid=${tea.courseid}&stuempno=${tea.stuempno}&begindate=<%=beginDate%>&enddate=<%=endDate%>&type=real')">${tea.checknum}</a>
					</ec:column>
					<ec:column property="checkrate" title="������" width="8%" />
					<%if(issysadmin==true){ %>
					<ec:column property="comelatenum" title="�ٵ��δ�" width="8%" >
						<a href="javascript:void(0);" onclick="late('&courseid=${tea.courseid}&stuempno=${tea.stuempno}&begindate=<%=beginDate%>&enddate=<%=endDate%>&type=late');">${tea.comelatenum}</a>
					</ec:column>
					<ec:column property="comelaterate" title="�ٵ���" width="8%" />
					<ec:column property="leaveearlynum" title="���˿δ�" width="8%" >
						<a href="javascript:void(0);" onclick="leave('&courseid=${tea.courseid}&stuempno=${tea.stuempno}&begindate=<%=beginDate%>&enddate=<%=endDate%>&type=leave');">${tea.leaveearlynum}</a>
					</ec:column>
					<ec:column property="leaveearlyrate" title="������" width="8%" />
					<%} %>
				</ec:row>
			</ec:table>

		</div>
		
	</body>
</html>

