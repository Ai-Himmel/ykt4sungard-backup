<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
	<head>
		<title>�Ϻ�������ѧ���Ͽ�漰�ִ�����ϵͳ</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/wxg/deptManager.do?method=saveManagerInfo" method="post">

			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="left" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												����Ա��Ϣά��
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<input type="hidden" name="listNum" value="all">
										<tbody>
											<tr align="center" valign=center height="25">
												<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
													��Ա����
												</td>
												<td width="35%" align="left" valign="middle" class="tableHeader3" >
												    <bean:write name="deptManagerForm" property="person.personCode"/>	
												    <html:hidden property="person.personCode"/>												
												</td>
												<html:hidden property="person.id" />
												<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
													��Ա����
												</td>
												<td width="35%" align="left" valign="middle" class="tableHeader3">
													<bean:write name="deptManagerForm" property="person.personName"/>	
													<html:hidden property="person.personName"/>	
												</td>
											</tr>
											<tr align="center" valign=center>
												<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
													����
												</td>
												<td width="35%" align="left" valign="middle" class="tableHeader3"><html:text property="person.officePhone" style="height:18px;width:180px;border:#000000 solid 1px;margin:0px;padding:0px;FONT-SIZE: 12px;" maxlength="30" />
												</td>
												<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
													�ֻ�
												</td>
												<td width="35%" align="left" valign="middle" class="tableHeader3">
													<html:text property="person.phone" style="height:18px;width:150px;border:#000000 solid 1px;margin:0px;padding:0px;FONT-SIZE: 12px;" maxlength="20" />
												</td>												
											</tr>	
											<tr align="center" valign=center>												
												<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:����;font-size: 12px;text-align: right;">
													Email
												</td>
												<td width="35%" align="left" valign="middle" class="tableHeader3" colspan="3"><html:text property="person.email" style="height:18px;width:180px;border:#000000 solid 1px;margin:0px;padding:0px;FONT-SIZE: 12px;" maxlength="30" />
												</td>
											</tr>											
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">

									<input name="Submit" type="button" class="button_nor" value="�� ��" onclick="DoSave()">
									&nbsp;
									<input name="Submit2" type="button" class="button_nor" value="�� ��" onclick="DoBack()">
								</td>

							</tr>
						</table>
						<logic:present name="msg" scope="request">
							<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
						</logic:present>
						<logic:notPresent name="msg" scope="request">
							<input name="hmsg" type="hidden" value="">
						</logic:notPresent>
						<input type="hidden" name="ec_p" value="<%=request.getAttribute("isNew")!=null&&request.getAttribute("isNew").equals("1")?"1":request.getParameter("ec_p") %>">
						<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i") %>">
						<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd") %>">

						<input type="hidden" name="searchCode" value="<%=request.getParameter("searchCode") %>">
						<input type="hidden" name="searchName" value="<%=request.getParameter("searchName") %>">
						</html:form>
	</body>
</html>

<SCRIPT language=javascript>

setTimeout('init()',50);
function init(){
  
  if(document.all.hmsg.value=='1')
       alert("��ӳɹ���");
  else if(document.all.hmsg.value=='2')
       alert("�޸ĳɹ���");
  else if(document.all.hmsg.value=='0')
       alert("����ʧ�ܣ�");
  else if(document.all.hmsg.value=='9')
       alert("����Ա�Ѵ��ڣ�");
} 

function checkEmail(str){
    
    var returnValue = true;
	var re =/^\w+((-\w+)|(\.\w+))*\@[A-Za-z0-9]+((\.|-)[A-Za-z0-9]+)*\.[A-Za-z0-9]+$/;
	if(str.match(re) == null)
	    returnValue=false;
		
	return returnValue;    
}

function checkMobile(str){
	var returnValue = true;
	var re =/^((\(\d{3}\))|(\d{3}\-))?\d{11}$/;	
	if(str.match(re) == null)
	    returnValue=false;
		
	return returnValue;    
}

function DoSave(){

   if(document.deptManagerForm.elements["person.email"].value!=''){
      var flag=checkEmail(document.deptManagerForm.elements["person.email"].value);
       if(!flag){
           alert("��������ȷ�ĵ����ʼ�");
           document.deptManagerForm.elements["person.email"].select();
           document.deptManagerForm.elements["person.email"].focus();
           return;
       } 
   }
   
   if(document.deptManagerForm.elements["person.phone"].value!=''){
      var flag=checkMobile(document.deptManagerForm.elements["person.phone"].value);
       if(!flag){
           alert("��������ȷ���ֻ�����");
           document.deptManagerForm.elements["person.phone"].select();
           document.deptManagerForm.elements["person.phone"].focus();
           return;
       } 
   }
      
   deptManagerForm.action="deptManager.do?method=saveManagerInfo";
   deptManagerForm.submit();
  
}

function DoBack(){  
    deptManagerForm.action="deptManager.do?method=load4AllManager";
    deptManagerForm.submit();     
}
</SCRIPT>
