<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
<head>
<title>上海电大校园一卡通考勤管理系统</title>
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
	if(document.all.ds_deptId.value=='')
	{
		alert('请选择需要统计的部门名称！');
		return false;
	}
	if(document.all.ds_startDate.value==''||document.all.ds_endDate.value=='')
	{
		alert('请将日期输入完整');
		return false;
	}
		if(document.all.ds_startDate.value>document.all.ds_endDate.value)
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
按部门出勤情况统计
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
  <form name="clerkstatic" action="workStatic.do?method=deptstatic" method="post" onsubmit="return check();">
	  <jodd:form bean="request">
                       部门:&nbsp;<td>&nbsp;&nbsp;&nbsp;&nbsp;</td>
					<select name="ds_deptId" style="width:130">
						<option value="" selected>
							请选择
						</option>	
						<logic:present name="departments" scope="request">
                        <logic:iterate name="departments" id="dl" type="java.util.Map">
                          <option value="<bean:write name="dl" property="deptId"/>"><bean:write name="dl" property="deptTitle"/></option>
                        </logic:iterate>
                        </logic:present>		
					</select>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;					
开始日期
<input class="input_box"  maxlength=20 name="ds_startDate" readonly="readonly" value="<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>">
<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
&nbsp;&nbsp;&nbsp;
截止日期
<input  name="ds_endDate" class="input_box"  maxlength=20 readonly="readonly" value="<%=(String)request.getAttribute("endDate")==null?"":(String)request.getAttribute("endDate")%>">
<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
			   
			   <script type="text/javascript">
			    new calendar("ds_startDate", "calBegin", "%Y-%m-%d");
                new calendar("ds_endDate", "calEnd", "%Y-%m-%d");				
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
              <td colspan="5" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader1">
			  	部门：<%=request.getAttribute("deptName")==null?"":request.getAttribute("deptName")%><br>                  
				统计日期：<%=request.getAttribute("startDate")==null?"":request.getAttribute("startDate")%>～<%=request.getAttribute("endDate")==null?"":request.getAttribute("endDate")%>
			 </td>
           </tr>
       </tbody>
        </table>
         <ec:table items="staticInfoList" var="staticInfo" rowsDisplayed="50" action="workStatic.do?method=deptstatic">
			
				<ec:exportXls fileName="clerkstaticList.xls" tooltip="导出 Excel" />
				<ec:row>					
					<ec:column property="STUNUMBER" width="6%" title="学工号"/>
					<ec:column property="cardId" width="10%" title="正常卡号"/>
					<ec:column property="clerkName" width="8%" title="姓名"/>
					<ec:column property="checkNum" width="5%" title="出勤天数"/>
					<ec:column property="extraNum" width="5%" title="加班天数"/>
					<ec:column property="outNum" width="5%" title="出差天数"/>
					<ec:column property="leaveNum" width="5%" title="请假天数"/>
					<ec:column property="irregularNum" width="5%" title="特休天数"/>
					<ec:column property="notcheckNum" width="5%" title="旷工天数"/>
					<ec:column property="lateNum" width="5%" title="迟到天数"/>
					<ec:column property="earlyNum" width="5%" title="早退天数"/>
					<ec:column property="checkPer" width="6%" title="出勤率"/>
					<ec:column property="extraPer" width="6%" title="加班率"/>
					<ec:column property="outPer" width="6%" title="出差率"/>
					<ec:column property="notcheckPer" width="6%" title="旷工率"/>
					<ec:column property="latePer" width="6%" title="迟到率"/>
					<ec:column property="earlyPer" title="早退率" />
				</ec:row>
			</ec:table>
	</div>
</body>
</html>
<script language="JavaScript">

var deptid='<%=request.getAttribute("deptId")==null?"":request.getAttribute("deptId")%>';

setTimeout('init()',50);
function init(){
  for(var i=0;i<document.all.ds_deptId.length;i++){
  
    if(document.all.ds_deptId[i].value==deptid){
      document.all.ds_deptId[i].selected=true;
    }
  }
}  
</script>