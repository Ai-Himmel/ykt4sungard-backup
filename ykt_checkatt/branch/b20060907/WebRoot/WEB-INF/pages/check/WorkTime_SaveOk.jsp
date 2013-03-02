<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
<head>
<title>复旦大学校园一卡通考勤管理系统</title>
<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
<body>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
添加成功
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

    <tr> 
      <td align="center" valign="middle" >&nbsp;</td>
    </tr>
    <tr> 
<table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td width="22%" height="26" align="center" valign="middle" bgcolor="#D1DAE9"  ><span class="medium">作休时间参数名称</span>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			  <c:out value="${workTimeComf.confname}" />
			  </td>
			</tr>
			<tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  上班时间1
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			  <c:out value="${workTimeComf.ondutytime1}" />
			  </td>
            </tr>
            <tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  下班时间1
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			 <c:out value="${workTimeComf.offdutytime1}" />
			  </td>
            </tr>
			<tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  上班时间2
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			  <c:out value="${workTimeComf.ondutytime2}" />
			  </td>
            </tr>
            <tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  下班时间2
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			 <c:out value="${workTimeComf.offdutytime2}" />
			  </td>
            </tr>
			<tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  上班时间3
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			  <c:out value="${workTimeComf.ondutytime3}" />
			  </td>
            </tr>
            <tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  下班时间3
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			 <c:out value="${workTimeComf.offdutytime3}" />
			  </td>
            </tr>
			<tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  上班时间4
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			  <c:out value="${workTimeComf.ondutytime4}" />
			  </td>
            </tr>
            <tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  下班时间4
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			 <c:out value="${workTimeComf.offdutytime4}" />
			  </td>
            </tr>
<tr> 
      <td height="30" align="right" valign="middle">
	  </td>
	  <td>
        &nbsp;&nbsp; <input name="Submit22" type="button" class="button_nor" value="返回" onclick="window.location.href='workTime.do?method=goWorkTime'"> 
      </td>
    </tr>
          </tbody>
        </table>
		</tr>
</body>
</table>
</html>
