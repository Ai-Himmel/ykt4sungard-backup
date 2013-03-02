<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
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
	var startDate=putin.register_sDate.value;
	if(startDate=='')
	{
		alert('请将日期输入完整');
		return false;
	}
}
function registerirre(form, entityName, action,putinForm)
{
 if (!atleaseOneCheck())
        {
            alert('请至少选择一' + entityName + '！');
            return;
        }
        form.ec_ev.value = '';
        form.ec_efn.value = '';
        form.action = action+"&register_startDate="+putinForm.register_sDate.value+"&register_startHour="+putinForm.register_startHour.value+"&register_startMin="+putinForm.register_startMin.value;
       form.submit();

}

</SCRIPT>

</head>
<% String msg=(String)request.getAttribute("msg");
if(msg!=null)
{
%>
<script language="javascript">
	alert('<%=msg%>');
</script>
<%}%>
<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
手工打卡
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
  <form name="menualRegister" action="workInfo.do?method=searchClerk" method="post" >
   <jodd:form bean="request">
姓名:
<input name="register_trueName" class="input_box"  maxlength=20>
&nbsp;&nbsp;
卡号:
<input name="register_cardNumber" class="input_box"  maxlength=20>
&nbsp;&nbsp;
学号:
<input name="register_stuNumber" class="input_box"  maxlength=20>
&nbsp;&nbsp;
部门:
<select name="register_deptId">
						<option value="">
							所有
						</option>
						<c:forEach var="department" items="${departmentTree}">
							<option value="<c:out value="${department.deptId}"/>">
								<c:out value="${department.deptTitle}" />
							</option>
						</c:forEach>
					</select>
&nbsp;&nbsp;&nbsp;
人员性质:
<select name="register_clerkType">
 <option value="1" >
 坐班
 </option>
 <option value="2">
 不坐班
 </option>
</select>
&nbsp;&nbsp;
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
<form name="register" action="workInfo.do?method=searchClerk" method="post" >
	<div id="tableDiv">
         <ec:table items="clerkList" var="clerk" rowsDisplayed="5" action="workInfo.do?method=searchClerk"  form="register">
				<ec:exportXls fileName="clerkList.xls" tooltip="导出 Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${clerk.cut_id}" style="border:0px" />
					</ec:column>
					<ec:column property="departname" title="部门" width="60" />
					<ec:column property="cardnumber" title="卡号" width="60" />
					<ec:column property="clerkname" title="人员" width="60" />
					<ec:column property="confname" title="班制" width="60" />
					<ec:column property="isseat" title="人员性质" width="60" />
				</ec:row>
			</ec:table>
	</div>
</form>

<p>&nbsp;</p>

<div id=lineDiv class="hrLine" >
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>
<div id="tableDiv"  style="display :<c:out value='${show}' default='none'/>">
<form name="putin" method="post" action='workInfo.do?method=manualRegister'>
<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign=center>
              <td height="26" align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >打卡时间</td>
              <td align="left" valign="middle" class="tableHeader3" >
			  <input name="register_sDate" class="input_box"  maxlength=20  readonly="true" >
			  <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
			  <p></p>
			  <select name="register_startHour">
			    <option value="00">00</option>
			   <% for(int i=1;i<24;i++){%>
			   <option value="<%=i%>"><%=i%></option>
			   <%}%>
			   </select>点
			   <select name="register_startMin">
			    <option value="00">00</option>
			   <% for(int i=1;i<61;i++){%>
			   <option value="<%=i%>"><%=i%></option>
			   <%}%>
			   </select>分</td>
			  <script type="text/javascript">
			    new calendar("register_sDate", "calBegin", "%Y-%m-%d");			
               </script>
            </tr>
		<tr> 
      <td height="40" align="right" valign="middle" class="tdborder02"> <input name="Submit" type="button" class="button_nor" value="确 定" onclick="if(check()==false) return false;registerirre(document.forms.register,'考勤人员','<c:url value="workInfo.do?method=manualRegister" />',document.forms.putin);"> 
      </td>
    </tr>
          </tbody>
        </table>
		</form>
</div>
</body>
</html>
