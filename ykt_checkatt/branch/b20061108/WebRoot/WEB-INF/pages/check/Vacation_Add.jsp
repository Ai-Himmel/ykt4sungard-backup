<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
<head>
<title>复旦大学校园一卡通考勤管理系统</title>
<meta http-equiv="Content-Type" content="text/html;">
<script language="javascript">
function check_vacation()
{
	var ontoken="false";
	var offtoken="false";
	var token="false";
	if(addConf.new_confName.value=="")
	{
		alert('请输入节日名称');
		return false;
	}
	if(addConf.new_startMonth.value==""||addConf.new_startDay.value=="")
	{
		alert('请将开始时间填写完整!');
		return false;
	}
	if(addConf.new_endMonth.value==""||addConf.new_endDay.value=="")
	{
		alert('请将结束时间填写完整!');
		return false;
	}
	if(addConf.new_startMonth.value>addConf.new_endMonth.value)
	{
		if(addConf.judge.checked!=true)
		{
			alert('开始日期不能大于结束日期!');
			addConf.new_startMonth.focus();
			return false;
		}
	}
	if(addConf.new_startMonth.value==addConf.new_endMonth.value)
	{
		if(addConf.new_startDay.value>addConf.new_endDay.value)
		{
			alert('开始日期不能大于结束日期!');
			addConf.new_startDay.focus();
			return false;
		}
	}
	m_sCheckKey	= DataFrame.GetAllCheckData();
    if(m_sCheckKey==""){
       alert("请选择部门！");
       return false;
    }
	var sSelKey	= "#$#$#$" ;	// 数据分隔符(显示值text与数据值value)
    
    var aCheckdata	= m_sCheckKey.split(sSelKey);
    sVal	= aCheckdata[1];
    sText	= aCheckdata[0];

    document.addConf.new_departId.value = sVal;
}
</script>
<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
<body>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

<form name="addConf" action="vacation.do?method=addConfirm" method="post" onsubmit="return check_vacation();">
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
公休假日设置
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
              <td width="22%" height="26" align="center" valign="middle" bgcolor="#D1DAE9"  ><span class="medium">公休假日名称</span>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			  <input 
            name="new_confName" class="input_box"  maxlength=20 ><font color=#ff0000>*</font></td>
			</tr>
			<tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  公休日期
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >开始
			  <select name="new_startMonth">
			  <option value="">请选择</option>
			  <% for(int i=1;i<13;i++) {%>
			  <option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'><%=i<10?"0"+Integer.toString(i):Integer.toString(i)%></option>
			  <%}%>
			  </select><font color=#ff0000>*</font>月:
			  <select name="new_startDay">
			  <option value="">请选择</option>
			  <% for(int i=1;i<32;i++) {%>
			  <option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'><%=i<10?"0"+Integer.toString(i):Integer.toString(i)%></option>
			  <%}%>
			  </select><font color=#ff0000>*</font>日
              &nbsp;
			  结束
			  <select name="new_endMonth">
			  <option value="">请选择</option>
			  <% for(int i=1;i<13;i++) {%>
			  <option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'><%=i<10?"0"+Integer.toString(i):Integer.toString(i)%></option>
			  <%}%>
			  </select><font color=#ff0000>*</font>月:
			  <select name="new_endDay">
			  <option value="">请选择</option>
			  <% for(int i=1;i<32;i++) {%>
			  <option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'><%=i<10?"0"+Integer.toString(i):Integer.toString(i)%></option>
			  <%}%>
			  </select><font color=#ff0000>*</font>日
			  &nbsp;<input type="checkbox" name="judge" value="1">是跨年假日(eg:12.30--1.2)
			  </td>
            </tr>
            <tr>
              <td width="22%" align="center" valign="middle"  bgcolor="#D1DAE9" >
			  <span class="medium">
			  部门
			  </span>
			  </td>
              <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5" >
			 <IFRAME name='DataFrame' src="departmentManager.do?method=loadDepartmentTree" width="220" height="200" SCROLLING="auto"></IFRAME>
                    <input type="hidden" name ="new_departId"/>
			  </td>
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
