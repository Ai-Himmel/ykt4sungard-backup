<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>

<html:html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
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
					<strong> <font class="medium"> ѧ�ڶ��� </font> </strong>
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
								<span class="medium">ѧ������</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">					  				   
							    <html:text property="termName" styleClass="input_box" maxlength="30" />					
								<font color="#ff0000">*</font>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">��һ�ܿ�ʼ���� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
						     	
								<html:text property="beginDate" readonly="true" styleClass="input_box" maxlength="10" />
								<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">				
								<font color="#ff0000">*</font>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">��ĩ�ܽ������� </span>
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
								<input name="Submit22" type="button" class="submitButton" value=" �� �� " onclick="if(validate()==false) return false;forms[0].submit();">
								<input name="Submit22" type="button" class="submitButton" value=" ȡ �� " onclick="history.back();">

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
		alert("ѧ�����Ʊ���");
		return false;
	}
	if(startDate=="" || endDate==""){
		alert("��ʼ���ںͽ������ڲ���Ϊ��");
		return false;
	}
	if(startDate>=endDate)
	{		
		alert("��ʼ����Ҫ���ڽ�������");
		return false;
	}
	
	
}
</script>