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
		<script type="text/javascript" src="pages/scripts/My97DatePicker/WdatePicker.js"></script>
	</head>
	<body>
	
	<html:form  action="/classTimes.do?method=updateClasssTimes" method="post" >
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
				<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium">�Ͽ�ʱ������ </font> </strong>
				</div>
				<div id="lineDiv" class="hrLine">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td class="tdborderLine"></td>
						</tr>
						<tr>
							<td align="center"><logic:present name="result" ><bean:write name="result"/></logic:present> </td>
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
						
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">�Ͽοδ�  </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="classNum"  maxlength="10" readonly="true" />															
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">��ʼʱ��</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="beginTime"  maxlength="10" readonly="true"/>
								<a href="#"><img
													src="pages/components/calendar/skins/aqua/cal.gif"
													 border="0"
													onclick="WdatePicker({el:'beginTime',dateFmt:'H:mm'})"  /> </a>
							</td>
							
								
						</tr>
					 
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">����ʱ��    </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="endTime" maxlength="10" readonly="true"/>
								<a href="#"><img
													src="pages/components/calendar/skins/aqua/cal.gif"
													border="0"
													onclick="WdatePicker({el:'endTime',dateFmt:'H:mm'})"  /> </a>
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="submit" class="submitButton" value=" ��  �� ">
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
