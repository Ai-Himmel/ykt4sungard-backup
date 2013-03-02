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
考勤人员工作时间制度详细信息
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
		  姓名:
		  </td>
		  <td  align="left" valign="middle" bgcolor="#E7F1F5"  width=85%>
		 <c:out value="${clerkInfo.clerkName}"/>
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">部门:
		  </td>
		   <td   align="left" valign="middle" bgcolor="#E7F1F5" >
		  <c:out value="${clerkInfo.deptName}"/>
		  </td>
		  </tr>
		  <tr>
		  <tr align="center" valign=center>
		  <td align="center"  valign="middle" bgcolor="#D1DAE9" >
		  工作时间:
		  </td>
		  <td   align="left" valign="middle" bgcolor="#E7F1F5">
		  名称:<c:out value="${clerkInfo.timeconfname}"/>&nbsp;
		  上班时间一:<c:out value="${clerkInfo.onduty1}"/>&nbsp;
		  下班时间一:<c:out value="${clerkInfo.offduty1}"/>&nbsp;
          上班时间二:<c:out value="${clerkInfo.onduty2}"/>&nbsp;
		  下班时间二:<c:out value="${clerkInfo.offduty2}"/>&nbsp;
		  上班时间三:<c:out value="${clerkInfo.onduty3}"/>&nbsp;
		  下班时间三:<c:out value="${clerkInfo.offduty3}"/>&nbsp;
		  上班时间四:<c:out value="${clerkInfo.onduty4}"/>&nbsp;
		  下班时间四:<c:out value="${clerkInfo.offduty4}"/>&nbsp;
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">
		  考勤制度:
		  </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="left">
		  名称:<c:out value="${clerkInfo.confname}"/> 
          &nbsp;允许早退的时间:<c:out value="${clerkInfo.earlytime}"/>分钟
		  &nbsp;允许迟到的时间:<c:out value="${clerkInfo.latetime}"/>分钟
          &nbsp;上班提前打卡不允许超过时间:<c:out value="${clerkInfo.ontime}"/>分钟
		  &nbsp;下班打卡允许滞后时间:<c:out value="${clerkInfo.offtime}"/>分钟
		  </td>
		  </tr>
		  <tr>
		  <td  valign="middle" bgcolor="#D1DAE9" align="center">类别:
		   </td>
		   <td  valign="middle" bgcolor="#E7F1F5" align="left">
		  <c:out value="${clerkInfo.caption}"/>
		  </td>
		  </tr>
		 <tr align="center" valign=center>
		  <td  valign="middle" >
		  </td>
		  <td  valign="middle"  align="left">
		  <input type="button" value="关闭"  class="button_nor" onclick="window.close()"/>
		  </td>
		  </tr>
		 </table>
	</div>
</body>
</html>
