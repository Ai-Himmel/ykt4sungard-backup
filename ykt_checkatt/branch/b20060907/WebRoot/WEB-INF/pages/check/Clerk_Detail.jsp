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
������Ա����ʱ���ƶ���ϸ��Ϣ
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
		  <td align="center" valign="middle" bgcolor="#D1DAE9" width=15%>
		  ����:
		  </td>
		  <td  align="left" valign="middle" bgcolor="#E7F1F5"  width=85%>
		 <c:out value="${clerkInfo.clerkName}"/>
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">����:
		  </td>
		   <td   align="left" valign="middle" bgcolor="#E7F1F5" >
		  <c:out value="${clerkInfo.deptName}"/>
		  </td>
		  </tr>
		  <tr>
		  <tr align="center" valign=center>
		  <td align="center"  valign="middle" bgcolor="#D1DAE9" >
		  ����ʱ��:
		  </td>
		  <td   align="left" valign="middle" bgcolor="#E7F1F5">
		  ����:<c:out value="${clerkInfo.timeconfname}"/>&nbsp;
		  �ϰ�ʱ��һ:<c:out value="${clerkInfo.onduty1}"/>&nbsp;
		  �°�ʱ��һ:<c:out value="${clerkInfo.offduty1}"/>&nbsp;
          �ϰ�ʱ���:<c:out value="${clerkInfo.onduty2}"/>&nbsp;
		  �°�ʱ���:<c:out value="${clerkInfo.offduty2}"/>&nbsp;
		  �ϰ�ʱ����:<c:out value="${clerkInfo.onduty3}"/>&nbsp;
		  �°�ʱ����:<c:out value="${clerkInfo.offduty3}"/>&nbsp;
		  �ϰ�ʱ����:<c:out value="${clerkInfo.onduty4}"/>&nbsp;
		  �°�ʱ����:<c:out value="${clerkInfo.offduty4}"/>&nbsp;
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">
		  �����ƶ�:
		  </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="left">
		  ����:<c:out value="${clerkInfo.confname}"/> 
          &nbsp;�������˵�ʱ��:<c:out value="${clerkInfo.earlytime}"/>����
		  &nbsp;����ٵ���ʱ��:<c:out value="${clerkInfo.latetime}"/>����
          &nbsp;�ϰ���ǰ�򿨲�������ʱ��:<c:out value="${clerkInfo.ontime}"/>����
		  &nbsp;�°�������ͺ�ʱ��:<c:out value="${clerkInfo.offtime}"/>����
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">���:
		   </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="left">
		  <c:out value="${clerkInfo.caption}"/>
		  </td>
		  </tr>
		 <tr align="center" valign=center>
		  <td  valign="middle" >
		  </td>
		  <td  valign="middle"  align="left">
		  <input type="button" value="�ر�"  class="button_nor" onclick="window.close()"/>
		  </td>
		  </tr>
		 </table>
	</div>
</body>
</html>
