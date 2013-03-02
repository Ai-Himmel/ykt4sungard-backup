<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
<head>
<title>详细信息</title>
<meta http-equiv="Content-Type" content="text/html;">

<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>


</head>

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
详细信息
</font>
</strong>
</div>
<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>
	<div id="tableDiv">
<table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
		  <tr align="center" valign=center>
		  <td  valign="middle" bgcolor="#D1DAE9" >
		  节日名称:
		  </td>
		  <td  valign="middle" bgcolor="#E7F1F5">
		  <c:out value='${confname}' />
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">部门:
		  </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="center">
		  <c:out value='${dptName}' />
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">开始时间:
		   </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="center">
		  <c:out value='${startMonth}' />月<c:out value='${startDay}' />日
		  </td>
		  </tr>
		  <tr>
          <td  valign="middle" bgcolor="#D1DAE9" align="center">结束时间:
		   </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="center">
		   <c:out value='${endMonth}' />月<c:out value='${endDay}' />日
		  </td>
		  </tr>
		 <tr align="center" valign=center>
		  <td  valign="middle" >
		  </td>
		  <td  valign="middle"  align="left">
		  <input type="button" value="返回"  class="button_nor" onclick="window.location.href='vacation.do?method=goVacation';"/>
		  </td>
		  </tr>
		 </table>
	</div>
</body>
</html>
