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

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
���˳����������
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
  <form name="clerkstatic" action="workStatic.do?method=clerkstatic" method="post" onsubmit="return check();">
	  <jodd:form bean="request">
                       ѧ����:&nbsp;<td>&nbsp;&nbsp;&nbsp;&nbsp;</td>
					<input class="text" type="text" name="cs_stuNo" size="10">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;					
��ʼ����
<input class="input_box"  maxlength=20 name="cs_startDate" readonly="readonly" value="<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
&nbsp;&nbsp;&nbsp;
��ֹ����
<input  name="cs_endDate" class="input_box"  maxlength=20 readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
			   
			   <script type="text/javascript">
			    new calendar("cs_startDate", "calBegin", "%Y-%m-%d");
                new calendar("cs_endDate", "calEnd", "%Y-%m-%d");				
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
	<table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#445386 bordercolordark=#ffffff      id=submenu1>
          <tbody>
        	<tr valign=middle>
              <td colspan="2" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader1">
			  	������<%=request.getAttribute("clerkName")==null?"":request.getAttribute("clerkName")%><br>
                  ���ţ�<%=request.getAttribute("cardId")==null?"":request.getAttribute("cardId")%><br>
				���ţ�<%=request.getAttribute("deptName")==null?"":request.getAttribute("deptName")%><br>
				ͳ�����ڣ�<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>��<%=request.getAttribute("endDate")==null?"":request.getAttribute("endDate")%>
			 </td>
              <td colspan="3" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader1"><br>
                  ������������<%=request.getAttribute("workNum")==null?"0":request.getAttribute("workNum")%> &nbsp;&nbsp;&nbsp;&nbsp;������������<%=request.getAttribute("notworkNum")==null?"0":request.getAttribute("notworkNum")%><br>
                  �Ӱ���������<%=request.getAttribute("extraNum")==null?"0":request.getAttribute("extraNum")%> &nbsp;&nbsp;&nbsp;&nbsp;�����������<%=request.getAttribute("leaveNum")==null?"0":request.getAttribute("leaveNum")%><br>
                  ������������<%=request.getAttribute("outNum")==null?"0":request.getAttribute("outNum")%> &nbsp;&nbsp;&nbsp;&nbsp;������Ϣ��������<%=request.getAttribute("irregularNum")==null?"0":request.getAttribute("irregularNum")%>
             </td>
           </tr>
       </tbody>
        </table>
         <ec:table items="staticInfoList" var="staticInfo" rowsDisplayed="10" action="workStatic.do?method=clerkstatic">
			
				<ec:exportXls fileName="clerkstaticList.xls" tooltip="���� Excel" />
				<ec:row>					
					<ec:column property="CHECKDATE" width="30%" title="��������"/>
					<ec:column property="DESCRIPTION" width="60%" title="���ڽ��"/>
					<ec:column property="DETAILS" title="��ϸ��Ϣ" sortable="false">
					<c:choose><c:when test="${staticInfo.DESCRIPTION == '�Ӱ�'}">
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},1)">��ϸ��Ϣ</a>
					</c:when><c:when test="${staticInfo.DESCRIPTION == '������Ϣ'}">
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},2)">��ϸ��Ϣ</a>
					</c:when><c:when test="${staticInfo.DESCRIPTION == '���'}">
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},3)">��ϸ��Ϣ</a>
					</c:when><c:when test="${staticInfo.DESCRIPTION == '����'}">
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},4)">��ϸ��Ϣ</a>
					</c:when><c:when test="${staticInfo.DESCRIPTION == '�������°�'||staticInfo.DESCRIPTION == '����ȱϯ'}">
					------------
					</c:when><c:otherwise>
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},0)">��ϸ��Ϣ</a>
					</c:otherwise></c:choose>				
					</ec:column>
				</ec:row>
			</ec:table>
	</div>
</body>
</html>
<script language="JavaScript">
function DoView(sdate,scid,flag){

   //alert('ok');
   window.open("workStatic.do?method=viewDetail&checkDate="+sdate+"&clerkId="+scid+"&flag="+flag,"��ϸ��Ϣ","height=550,width=800,status=yes,toolbar=no,menubar=no,location=no");

}
</script>