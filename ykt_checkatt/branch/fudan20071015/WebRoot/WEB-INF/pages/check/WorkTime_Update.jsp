<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>������ѧУ԰һ��ͨ���ڹ���ϵͳ</title>
		<meta http-equiv="Content-Type" content="text/html;">
		<script language="javascript">
function check_worktime()
{
	var ontoken="false";
	var offtoken="false";
	var token="false";
	if(addConf.add_confName.value=="")
	{
		alert('����������ʱ������');
		return false;
	}
    <% for(int i=1;i<5;i++) {
		%>	
			if(addConf.add_ondutytime<%=i%>_hour.value!=""&&addConf.add_ondutytime<%=i%>_min.value!="")
		{
		ontoken="true";
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
		alert('��������дһ�����°�ʱ��');
		return false;
	}
	if(ontoken=="false")
	{
		alert('�뽫�ϰ�ʱ����д����,����һ��');
		return false;
	}
	if(offtoken=="false")
	{
		alert('�뽫�°��ʱ����д����,����һ��');
		return false;
	}
	if(token=="true")
	{
		alert('�뽫��Ϣ��д����');
		return false;
	}
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

			<form name="addConf" action="workTime.do?method=update" method="post" onsubmit="return check_worktime();">
				<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium"> ����ʱ���޸� </font> </strong>
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
							<input type="hidden" value='<c:out value="${workTimeComf.worktimeId}" />' name="add_worktimeconfid" />
							<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium">����ʱ������</span>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<input name="add_confName" class="input_box" maxlength=20 value='<c:out value="${workTimeComf.worktimeName}" />'>
								<font color=#ff0000>*</font>
							</td>
						</tr>
						<%for (int num = 1; num < 5; num++) {%>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �ϰ�ʱ��<%=num%> </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<select name="add_ondutytime<%=num%>_hour">
									<option value='<%=(String)request.getAttribute("add_ondutytime"+num+"_hour")==null?"":(String)request.getAttribute("add_ondutytime"+num+"_hour")%>'>
										<%=(String) request.getAttribute("add_ondutytime" + num
								+ "_hour") == null ? "��ѡ��" : (String) request
						.getAttribute("add_ondutytime" + num + "_hour")%>
									</option>
									<%for (int i = 0; i < 24; i++) {%>
									<option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'>
										<%=i < 10 ? "0" + Integer.toString(i) : Integer
							.toString(i)%>
									</option>
									<%}%>
								</select>
								��:
								<select name="add_ondutytime<%=num%>_min">
									<option value='<%=(String)request.getAttribute("add_ondutytime"+num+"_min")==null?"":(String)request.getAttribute("add_ondutytime"+num+"_min")%>'>
										<%=(String) request.getAttribute("add_ondutytime" + num
								+ "_min") == null ? "��ѡ��" : (String) request
						.getAttribute("add_ondutytime" + num + "_min")%>
									</option>
									<%for (int i = 1; i < 60; i++) {%>
									<option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'>
										<%=i < 10 ? "0" + Integer.toString(i) : Integer
							.toString(i)%>
									</option>
									<%}%>
								</select>
								��
							</td>
						</tr>
						<tr>
							<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium"> �°�ʱ��<%=num%> </span>
							</td>
							<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
								<select name="add_offdutytime<%=num%>_hour">
									<option value='<%=(String)request.getAttribute("add_offdutytime"+num+"_hour")==null?"":(String)request.getAttribute("add_offdutytime"+num+"_hour")%>'>
										<%=(String) request.getAttribute("add_offdutytime" + num
								+ "_hour") == null ? "��ѡ��" : (String) request
						.getAttribute("add_offdutytime" + num + "_hour")%>
									</option>
									<%for (int i = 0; i < 24; i++) {%>
									<option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'>
										<%=i < 10 ? "0" + Integer.toString(i) : Integer
							.toString(i)%>
									</option>
									<%}%>
								</select>
								��:
								<select name="add_offdutytime<%=num%>_min">
									<option value='<%=(String)request.getAttribute("add_offdutytime"+num+"_min")==null?"":(String)request.getAttribute("add_offdutytime"+num+"_min")%>'>
										<%=(String) request.getAttribute("add_offdutytime" + num
								+ "_min") == null ? "��ѡ��" : (String) request
						.getAttribute("add_offdutytime" + num + "_min")%>
									</option>
									<%for (int i = 1; i < 60; i++) {%>
									<option value='<%=i<10?"0"+Integer.toString(i):Integer.toString(i)%>'>
										<%=i < 10 ? "0" + Integer.toString(i) : Integer
							.toString(i)%>
									</option>
									<%}%>
								</select>
								��
							</td>
						</tr>
						<%}%>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="submit" class="submitButton" value=" �� �� ">
								<input name="Submit22" type="button" class="submitButton" value=" ȡ �� " onclick="history.back();">

							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</form>
	</table>
</html>
