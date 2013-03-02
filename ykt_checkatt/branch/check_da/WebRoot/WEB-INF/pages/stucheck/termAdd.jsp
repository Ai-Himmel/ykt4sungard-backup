<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>

<html:html>
	<head>
		<title>上海电大校园一卡通考勤管理系统</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel="stylesheet">
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel="stylesheet">
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
	<body>
	
	<html:form  action="/term.do?method=saveTerm" method="post" >
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium"> 学期定义 </font> </strong>
				</div>
				<div id="lineDiv" class="hrLine">
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
				<table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
					<tbody>
						<tr align="center" valign="center">
							<td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium">学期名称</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">					  				   
							    <html:text property="termName" styleClass="input_box" maxlength="30" />					
								<font color="#ff0000">*</font>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">第一周开始日期 </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
						     	
								<html:text property="beginDate" readonly="true" styleClass="input_box" maxlength="10" />
								<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">				
								<font color="#ff0000">*</font>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">最末周结束日期 </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="endDate" readonly="true" styleClass="input_box" maxlength="10"/>
								<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
								<font color="#ff0000">*</font>
							</td>
						</tr>
					<script type="text/javascript">
	                   new calendar("beginDate", "calBegin", "%Y%m%d");
	                   new calendar("endDate", "calEnd", "%Y%m%d");
				     </script>
						
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="button" class="submitButton" value=" 创 建 " onclick="if(validate()==false) return false;forms[0].submit();">
								<input name="Submit22" type="button" class="submitButton" value=" 取 消 " onclick="history.back();">

							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</table>
</html:form>
	 
</html:html>
<SCRIPT language="javascript">
function validate()
{   var termName=document.forms[0].termName.value;
	var startDate=document.forms[0].beginDate.value;
	var endDate=document.forms[0].endDate.value;
	if(termName==""){
		alert("学期名称必填");
		return false;
	}
	if(startDate=="" || endDate==""){
		alert("开始日期和结束日期不能为空");
		return false;
	}
	if(startDate>=endDate)
	{		
		alert("开始日期要早于结束日期");
		return false;
	}
	
	
}
</script>