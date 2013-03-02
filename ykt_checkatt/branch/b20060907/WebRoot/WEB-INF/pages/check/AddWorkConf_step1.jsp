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
	</head>
<body>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

<form name="addConf" action="workConf.do?method=addWorkConf" method="post" onsubmit="return check();">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
考勤制度参数设置
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
              <td width="22%" height="26" align="center" valign="middle" bgcolor="#D1DAE9"  ><span class="medium">考勤参数名称</span>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			  <input 
            name="add_confName" class="input_box"  maxlength=20 ><font color=#ff0000>*</font></td>
			</tr>
			<tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium STYLE5">
			  允许迟到
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" ><input 
            name="add_permitLateTime" class="input_box"  maxlength=5 onblur="count(addConf.add_permitLateTime)"><font color=#ff0000>*</font>分钟</td>
            </tr>
            <tr>
              <td width="22%" align="center" valign="middle" bgcolor="#D1DAE9" >
			  <span class="medium STYLE5">
			  允许早退
			  </span>
			  </td>
              <td align="left" valign="middle" bgcolor="#E7F1F5"><input 
            name="add_permitEarly" class="input_box"  maxlength=5
			onblur="count(addConf.add_permitEarly)"><font color=#ff0000>*</font>分钟</td>
            </tr>
            <tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium STYLE5">
			  上班提前打卡不允许超过
			  </span>			  
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" ><input 
            name="add_ondutyAdvancedTime" class="input_box"  maxlength=5
			onblur="count(addConf.add_ondutyAdvancedTime)"><font color=#ff0000>*</font>分钟</td>
            </tr>
			<tr>
              <td width="22%" align="center" valign="middle" bgcolor="#D1DAE9"  >
			  <span class="medium STYLE5">
			  下班滞后打卡不允许超过
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" ><input 
            name="add_offDutyLastTime" class="input_box"  maxlength=5
			onblur="count(addConf.add_offDutyLastTime)"
			><font color=#ff0000>*</font>分钟</td>
            </tr>
<tr> 
      <td height="30" align="right" valign="middle">
	  </td>
	  <td>
        &nbsp;&nbsp; <input name="Submit22" type="submit" class="button_nor" value="创建"> 
           <input name="Submit22" type="button" class="button_nor" value="取消" onclick="history.back();"> 
     
      </td>
    </tr>
          </tbody>
        </table>
		</tr>
</body>
</form>
</table>
</html>
