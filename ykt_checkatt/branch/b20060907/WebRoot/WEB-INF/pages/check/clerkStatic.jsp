<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
<head>
<title>复旦大学校园一卡通考勤管理系统</title>
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
		alert('请输入考勤人员的学工号！');
		return false;
	}
	if(document.all.cs_startDate.value==''||document.all.cs_endDate.value=='')
	{
		alert('请将日期输入完整');
		return false;
	}
		if(document.all.cs_startDate.value>document.all.cs_endDate.value)
	{		
		alert("开始日期不能大于结束时间");
		return false;
	}

}

</SCRIPT>

</head>

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
个人出勤情况报表
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
                       学工号:&nbsp;<td>&nbsp;&nbsp;&nbsp;&nbsp;</td>
					<input class="text" type="text" name="cs_stuNo" size="10">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;					
开始日期
<input class="input_box"  maxlength=20 name="cs_startDate" readonly="readonly" value="<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
&nbsp;&nbsp;&nbsp;
截止日期
<input  name="cs_endDate" class="input_box"  maxlength=20 readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
			   
			   <script type="text/javascript">
			    new calendar("cs_startDate", "calBegin", "%Y-%m-%d");
                new calendar("cs_endDate", "calEnd", "%Y-%m-%d");				
               </script>
               
<input type="image" src="<c:url value="/pages/images/icon/16x16/search.gif"/>" align="middle" class="nullBorder">
&nbsp;&nbsp;&nbsp;
<input name="Submit" type="submit" class="button_nor" value="查 询" > 

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
			  	姓名：<%=request.getAttribute("clerkName")==null?"":request.getAttribute("clerkName")%><br>
                  卡号：<%=request.getAttribute("cardId")==null?"":request.getAttribute("cardId")%><br>
				部门：<%=request.getAttribute("deptName")==null?"":request.getAttribute("deptName")%><br>
				统计日期：<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>～<%=request.getAttribute("endDate")==null?"":request.getAttribute("endDate")%>
			 </td>
              <td colspan="3" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader1"><br>
                  出勤总天数：<%=request.getAttribute("workNum")==null?"0":request.getAttribute("workNum")%> &nbsp;&nbsp;&nbsp;&nbsp;旷工总天数：<%=request.getAttribute("notworkNum")==null?"0":request.getAttribute("notworkNum")%><br>
                  加班总天数：<%=request.getAttribute("extraNum")==null?"0":request.getAttribute("extraNum")%> &nbsp;&nbsp;&nbsp;&nbsp;请假总天数：<%=request.getAttribute("leaveNum")==null?"0":request.getAttribute("leaveNum")%><br>
                  出差总天数：<%=request.getAttribute("outNum")==null?"0":request.getAttribute("outNum")%> &nbsp;&nbsp;&nbsp;&nbsp;特殊休息总天数：<%=request.getAttribute("irregularNum")==null?"0":request.getAttribute("irregularNum")%>
             </td>
           </tr>
       </tbody>
        </table>
         <ec:table items="staticInfoList" var="staticInfo" rowsDisplayed="10" action="workStatic.do?method=clerkstatic">
			
				<ec:exportXls fileName="clerkstaticList.xls" tooltip="导出 Excel" />
				<ec:row>					
					<ec:column property="CHECKDATE" width="30%" title="考勤日期"/>
					<ec:column property="DESCRIPTION" width="60%" title="考勤结果"/>
					<ec:column property="DETAILS" title="详细信息" sortable="false">
					<c:choose><c:when test="${staticInfo.DESCRIPTION == '加班'}">
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},1)">详细信息</a>
					</c:when><c:when test="${staticInfo.DESCRIPTION == '特殊休息'}">
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},2)">详细信息</a>
					</c:when><c:when test="${staticInfo.DESCRIPTION == '请假'}">
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},3)">详细信息</a>
					</c:when><c:when test="${staticInfo.DESCRIPTION == '出差'}">
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},4)">详细信息</a>
					</c:when><c:when test="${staticInfo.DESCRIPTION == '正常上下班'||staticInfo.DESCRIPTION == '旷工缺席'}">
					------------
					</c:when><c:otherwise>
					<a href="javascript:DoView(${staticInfo.CHECKDATE},${staticInfo.CLERKID},0)">详细信息</a>
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
   window.open("workStatic.do?method=viewDetail&checkDate="+sdate+"&clerkId="+scid+"&flag="+flag,"详细信息","height=550,width=800,status=yes,toolbar=no,menubar=no,location=no");

}
</script>