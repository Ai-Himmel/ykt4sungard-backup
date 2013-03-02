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
</head>
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
修改特殊休息信息
</font>
</strong>
</div>
<div id="tableDiv" >
<form name="update" method="post" action='irregularRest.do?method=update'>
<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
		  <tr align="center" valign=center>
              <td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >姓名</td>
              <td width="35%" align="left" valign="middle" class="tableHeader3" ><c:out value='${clerkName}' /></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >&nbsp;</td>
              <td align="left" valign="middle" class="tableHeader3" >&nbsp;</td>
			  <input type="hidden" name="new_irregularrestid" value="<c:out value='${irregularrest.irregularrestid}' />"/>
            </tr>

            <tr align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >开始时间</td>
              <td align="left" valign="middle" class="tableHeader3" >
			  <input name="new_startDate" class="input_box"  maxlength=20  readonly="true" value="<c:out value='${new_startDate}' />">
			  <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
			  <p></p>
			  <select name="new_startHour">
			   <option value="<c:out value='${new_startHour}' />" ><c:out value='${new_startHour}' /></option>	
			   <% for(int i=1;i<24;i++){%>
			   <option value="<%=i%>"><%=i%></option>
			   <%}%>
			   </select>点
			   <select name="new_startMin">
			     <option value="<c:out value='${new_startMin}' />" ><c:out value='${new_startMin}' /></option>	
			   <% for(int i=1;i<61;i++){%>
			   <option value="<%=i%>"><%=i%></option>
			   <%}%>
			   </select>分</td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >
			  截止时间
			  </td>
              <td align="left" valign="middle" class="tableHeader3" >
			  <input name="new_endDate" class="input_box"  maxlength=20  readonly="true" value="<c:out value='${new_endDate}' />">
			   <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
			    <p></p>
			   <select name="new_endHour">
			    <option value="<c:out value='${new_endHour}' />" ><c:out value='${new_endHour}' /></option>	  
			   <% for(int i=1;i<24;i++){%>
			   <option value="<%=i%>" ><%=i%></option>
			   <%}%>
			   </select>点
			   <select name="new_endMin">
			     <option value="<c:out value='${new_endMin}' />" ><c:out value='${new_endMin}' /></option>	
			   <% for(int i=1;i<61;i++){%>
			   <option value="<%=i%>"><%=i%></option>
			   <%}%>
			   </select>分
			  </td>
			  <script type="text/javascript">
			    new calendar("new_startDate", "calBegin", "%Y-%m-%d");
                new calendar("new_endDate", "calEnd", "%Y-%m-%d");				
               </script>
            </tr>

		<tr> <td>&nbsp;</td>
      <td height="40" align="right" valign="middle" class="tdborder02"> <input name="Submit" type="submit" class="button_nor" value="确 定" > 
	  <input name="Submit" type="button" class="button_nor" value="返 回" onclick="history.back();"> 
      </td>
    </tr>
          </tbody>
        </table>
		</form>
</div>
