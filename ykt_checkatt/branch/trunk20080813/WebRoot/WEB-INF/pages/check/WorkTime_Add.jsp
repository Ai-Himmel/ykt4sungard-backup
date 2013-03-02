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

			<form name="addConf" action="workTime.do?method=addworkTime" method="post" onsubmit="return check_worktime();">
				<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium"> 工作时间设置 </font> </strong>
				</div>
				<div id=lineDiv class="hrLine">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td class="tdborderLine"></td>
						</tr>
					</table>
				</div>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr align="center" valign=center>
							<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium">工作时间名称</span>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="add_confName" class="input_box" maxlength=40 style="width: 150">
								<font color=#ff0000>*</font>
							</td>
						</tr>
						<%for (int num = 1; num < 5; num++) {%>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 上班时间<%=num%> </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<select name="add_ondutytime<%=num%>_hour">
									<option value="">
										请选择
									</option>
									<%for (int i = 1; i < 24; i++) {%>
									<option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'>
										<%=i < 10 ? "0" + Integer.toString(i) : Integer.toString(i)%>
									</option>
									<%}%>
								</select>
								点:
								<select name="add_ondutytime<%=num%>_min">
									<option value="">
										请选择
									</option>
									<%for (int i = 0; i < 60; i++) {%>
									<option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'>
										<%=i < 10 ? "0" + Integer.toString(i) : Integer.toString(i)%>
									</option>
									<%}%>
								</select>
								分
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> 下班时间<%=num%> </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<select name="add_offdutytime<%=num%>_hour">
									<option value="">
										请选择
									</option>
									<%for (int i = 1; i < 24; i++) {%>
									<option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'>
										<%=i < 10 ? "0" + Integer.toString(i) : Integer.toString(i)%>
									</option>
									<%}%>
								</select>
								点:
								<select name="add_offdutytime<%=num%>_min">
									<option value="">
										请选择
									</option>
									<%for (int i = 0; i < 60; i++) {%>
									<option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'>
										<%=i < 10 ? "0" + Integer.toString(i) : Integer.toString(i)%>
									</option>
									<%}%>
								</select>
								分
							</td>
						</tr>
						<%}%>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="submit" class="submitButton" value=" 创 建 " >&nbsp;&nbsp;&nbsp;&nbsp;
								<input name="Submit22" type="button" class="submitButton" value=" 取 消 " onclick="history.back();">

							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</form>
	</table>
</html>
<script language="javascript">
function check_worktime()
{
	var ontoken="false";
	var offtoken="false";
	var token="false";
    var msg="开始时间不能大于结束时间";
	if(addConf.add_confName.value=="")
	{
		alert('请输入工作时间名称！');
		return false;
	}
    <% for(int i=1;i<5;i++) {
		%>	
			if(addConf.add_ondutytime<%=i%>_hour.value!=""&&addConf.add_ondutytime<%=i%>_min.value!="")
		{
		ontoken="true";
		if(addConf.add_offdutytime<%=i%>_hour.value=="")
			{
			alert('请输入下班时间'+'<%=i%>'+' <时>的设置');
			addConf.add_offdutytime<%=i%>_hour.focus();
			return false;
			}
		if(addConf.add_offdutytime<%=i%>_min.value=="")
			{
			alert('请输入下班时间'+'<%=i%>'+' <分>的设置');
			addConf.add_offdutytime<%=i%>_min.focus();
			return false;
			}
			
		if (addConf.add_ondutytime<%=i-1%>_hour.value=="" && addConf.add_ondutytime<%=i%>_hour.value!=""){
			alert('请按顺序设置工作时间！');
			return false;
		}

		if (addConf.add_ondutytime<%=i-1%>_min.value=="" && addConf.add_ondutytime<%=i%>_min.value!=""){
			alert('请按顺序设置工作时间！');
			return false;
		}
		
		if(addConf.add_ondutytime<%=i%>_hour.value>addConf.add_offdutytime<%=i%>_hour.value)
			{
              alert(msg);
			  addConf.add_offdutytime<%=i%>_hour.focus();
			  return false;
			}
		if(addConf.add_ondutytime<%=i%>_hour.value==addConf.add_offdutytime<%=i%>_hour.value)
			{
			if(addConf.add_ondutytime<%=i%>_min.value>addConf.add_offdutytime<%=i%>_min.value)
				{
				alert(msg);
                addConf.add_offdutytime<%=i%>_min.focus();
				return false;
				}
			}
		}
		if(addConf.add_ondutytime<%=i%>_hour.value!=""&&addConf.add_ondutytime<%=i%>_min.value=="")
		{
		token="true";
		}
		if(addConf.add_ondutytime<%=i%>_hour.value==""&&addConf.add_ondutytime<%=i%>_min.value!="")
		{
		token="true";
		}
	<%}%>
	<% for(int i=1;i<5;i++) {
		%>	
		if(addConf.add_offdutytime<%=i%>_hour.value!=""&&addConf.add_offdutytime<%=i%>_min.value!="")
		{
		offtoken="true";
		if(addConf.add_ondutytime<%=i%>_hour.value=="")
			{
			alert('请输入上班时间'+'<%=i%>'+' <时>的设置');
			addConf.add_ondutytime<%=i%>_hour.focus();
			return false;
			}
		if(addConf.add_ondutytime<%=i%>_min.value=="")
			{
			alert('请输入上班时间'+'<%=i%>'+' <分>的设置');
			addConf.add_ondutytime<%=i%>_min.focus();
			return false;
			}
		}
		if(addConf.add_offdutytime<%=i%>_hour.value!=""&&addConf.add_offdutytime<%=i%>_min.value=="")
		{
		token="true";
		}
		if(addConf.add_offdutytime<%=i%>_hour.value==""&&addConf.add_offdutytime<%=i%>_min.value!="")
		{
		token="true";
		}
	<%}%>
	if(ontoken=="false"&&offtoken=="false")
	{
		alert('请至少填写一项上下班时间');
		return false;
	}
	if(ontoken=="false")
	{
		alert('请将上班时间填写完整,至少一项');
		return false;
	}
	if(offtoken=="false")
	{
		alert('请将下班班时间填写完整,至少一项');
		return false;
	}
	if(token=="true")
	{
		alert('请将信息填写完整');
		return false;
	}
}
</script>
