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
	
	if(document.all.log_startDate.value==''||document.all.log_endDate.value=='')
	{
		alert('�뽫������������');
		return false;
	}
		if(document.all.log_startDate.value>document.all.log_endDate.value)
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
������־��ѯ
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
  <form name="clerkstatic" action="workStatic.do?method=checklog" method="post" onsubmit="return check();">
	  <jodd:form bean="request">		
��ʼ����
<input class="input_box"  maxlength=20 name="log_startDate" readonly="readonly" value="<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
&nbsp;&nbsp;&nbsp;
��ֹ����
<input  name="log_endDate" class="input_box"  maxlength=20 readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
			   
			   <script type="text/javascript">
			    new calendar("log_startDate", "calBegin", "%Y-%m-%d");
                new calendar("log_endDate", "calEnd", "%Y-%m-%d");				
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
    <ec:table items="staticInfoList" var="staticInfo" rowsDisplayed="10" action="workStatic.do?method=checklog">
               
        <ec:exportXls fileName="WorkinfoList.xls" tooltip="���� Excel"/>
        <ec:row>
            <ec:column property="CHECKTIME" width="12%" title="��ʱ��"/>
            <ec:column property="CARDNUMBER" width="12%" title="����"/>                          
            <ec:column property="STUNUMBER" width="8%" title="ѧ��"/>
            <ec:column property="clerkName" width="8%" title="����"/>
            <ec:column property="deptName" width="10%" title="����"/>            
            <ec:column property="CONFNAME" width="8%" title="����"/>
            <ec:column property="isseatName" width="8%" title="��Ա����"/>
            <ec:column property="DESCRIPTION" width="25%" title="���ڽ��"/>
            <ec:column property="EXCEPTIONMINS" title="ʱ��(����)"/>
        </ec:row>
    </ec:table>
</div>
</body>
</html>

