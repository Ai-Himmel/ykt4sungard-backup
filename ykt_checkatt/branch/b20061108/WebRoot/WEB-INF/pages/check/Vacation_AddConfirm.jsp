<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
<head>
<title>������ѧУ԰һ��ͨ���ڹ���ϵͳ</title>
<meta http-equiv="Content-Type" content="text/html;">
<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
<body>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

<form name="addConf" action="vacation.do?method=addVacation" method="post" onsubmit="return check_vacation();">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
���ݼ���ȷ��
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
              <td width="22%" height="26" align="center" valign="middle" bgcolor="#D1DAE9"  >
			  <span class="medium">����</span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			  <c:out value="${dptName}"/>
			  <input type="hidden" name="new_departId" value="<c:out value='${new_departId}'/>"/>
			  </td>
			</tr>
			<tr align="center" valign=center> 
              <td width="22%" height="26" align="center" valign="middle" bgcolor="#D1DAE9"  >
			  <span class="medium">������Ϣ</span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			  ����:<c:out value="${new_confname}"/>
			  <input type="hidden" name="new_confName" value="<c:out value='${new_confname}'/>"/>
			  &nbsp;��ʼ
			  <select name="new_startMonth">
			  <option value="<c:out value='${new_startMonth}'/>"><c:out value="${new_startMonth}"/></option>
			  </select>��:
			  <select name="new_startDay">
			  <option value="<c:out value='${new_startDay}'/>"><c:out value='${new_startDay}'/></option>
			  </select>��
              &nbsp;
			  ����
			  <select name="new_endMonth">
			  <option value="<c:out value='${new_endMonth}'/>"><c:out value='${new_endMonth}'/></option>
			  </select>��:
			  <select name="new_endDay">
			  <option value="<c:out value='${new_endDay}'/>"><c:out value='${new_endDay}'/></option>
			  </select>��
			  &nbsp;
			  </td>
			</tr>
			<tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  ȫУ����ʱ��
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
               <c:out value='${globeVa}' escapeXml="{true}"/>
			  </td>
            </tr>
			<tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  ��һ�����Ź���ʱ��
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
              <c:out value='${parantVa}' escapeXml="{true}"/>
			  </td>
            </tr>
			<tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  ��ǰ�������й���ʱ��
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
              <c:out value='${va}' escapeXml="{true}"/>
			  </td>
            </tr>

<tr> 
      <td height="30" align="right" valign="middle">
	  </td>
	  <td>
        &nbsp;&nbsp; <input name="Submit22" type="submit" class="button_nor" value="ȷ��"> 
           <input name="Submit22" type="button" class="button_nor" value="ȡ��" onclick="history.back();"> 
     
      </td>
    </tr>
          </tbody>
        </table>
		</tr>
</body>
</form>
</table>
</html>
