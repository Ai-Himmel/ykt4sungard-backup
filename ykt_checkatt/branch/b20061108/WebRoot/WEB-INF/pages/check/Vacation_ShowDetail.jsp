<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
<head>
<title>��ϸ��Ϣ</title>
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
��ϸ��Ϣ
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
		  ��������:
		  </td>
		  <td  valign="middle" bgcolor="#E7F1F5">
		  <c:out value='${confname}' />
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">����:
		  </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="center">
		  <c:out value='${dptName}' />
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">��ʼʱ��:
		   </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="center">
		  <c:out value='${startMonth}' />��<c:out value='${startDay}' />��
		  </td>
		  </tr>
		  <tr>
          <td  valign="middle" bgcolor="#D1DAE9" align="center">����ʱ��:
		   </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="center">
		   <c:out value='${endMonth}' />��<c:out value='${endDay}' />��
		  </td>
		  </tr>
		 <tr align="center" valign=center>
		  <td  valign="middle" >
		  </td>
		  <td  valign="middle"  align="left">
		  <input type="button" value="����"  class="button_nor" onclick="window.location.href='vacation.do?method=goVacation';"/>
		  </td>
		  </tr>
		 </table>
	</div>
</body>
</html>
