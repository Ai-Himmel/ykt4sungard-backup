<%@ page language="java" pageEncoding="GBK"%>
<%@ include file="../commons/init.jsp"%>

<html>
	<head>
		<title>У԰һ��ͨ����</title>

		<style type="text/css">
.ViewHeader {
	background-color: #FFDEAD;
	font-family: Arial, Helvetica, sans-serif;
	font-size: 9pt;
}

.NavBarTabs {
	background-color: #D27E00;
	font-family: Arial, Helvetica, sans-serif;
	font-size: 9pt;
}

.NavBarTabs .a:active {
	color: #B22222;
}

.NavBarTabs .a:link {
	color: white;
	text-decoration: none;
}

.Copyright {
	color: #FFDEAD;
	font-size: 9px;
}
</style>

<Script Langage='JavaScript'>
    function getDevList() {
        document.devicestatusForm.action = 'devicestatus.do?method=queryDeviceStatus';
        document.devicestatusForm.submit();
    }
    function loginout() {
        document.devicestatusForm.action = 'login.do?method=loginout';
        document.devicestatusForm.submit();
    }
   function diffshow(flag){
      if(flag=='5'){
          document.getElementById("detail").style.display='none';
          document.getElementById("detail1").style.display='';
      }else{
          document.getElementById("detail").style.display='';
          document.getElementById("detail1").style.display='none';
      }
   }
    function sub(){
        document.devicestatusForm.submit();
    }
</Script>
	</head>
	<body MARGINHEIGHT="0" marginwidth="0" leftmargin="0" topmargin="0">
		<table cellpadding="0" border="0" cellspacing="0" width="100%"
			height="100%">
			<tr valign="top" height="0%">
				<td bgcolor="Black">
					&nbsp;
					<table class="NavBarTabs" width="100%" cellspacing="0"
						cellpadding="0" border="0">
						<tr height="30" valign="bottom">
							<td width="10">
								&nbsp;&nbsp;
							</td>
							<td valign="bottom" align="left" nowrap="nowrap"><img src="/monitorsys/pages/images/tab.select.gif" border="0"></td>
							<td valign="middle" align="center" width="90%">
								&nbsp;&nbsp;
							</td>
						</tr>
					</table>

					<table class="NavBarMenu" width="100%" cellspacing="0"
						cellpadding="0" border="0">
						<tr background="Black">
							<td nowrap="nowrap" class="NavBarMenu" height="25">
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="NavBarMenu" href="#"
									onclick="javascript: getDevList();">�б�</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="NavBarMenu" href="#" onclick="javascript: loginout();">�ǳ�</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="NavBarMenu" href="#" target="_blank">����</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							</td>
							<td class="NavBarMenu" align="right">
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr valign="top" height="100%">
				<td>
					<table cellpadding="0" cellspacing="10" width="100%">
						<tr>
							<td valign="top">

								<table width="70%" border="0" cellpadding="8" cellspacing="0">
									<tr class="ViewHeader">
										<td height="35" align="left" nowrap="nowrap">
											<strong>�쳣�ڵ���ϸ��Ϣ</strong>
										</td>
										<td>
											<table border="0" cellpadding="0" cellspacing="0" width="70%">
												<tr>
													<td align="right" nowrap="nowrap">
														&nbsp;&nbsp;

													</td>
												</tr>
											</table>
										</td>
									</tr>
								</table>

								<html:form action="/devicestatus.do?method=updateDeviceStatus">
									<table width="60%">
										<tr>
											<td>
												����
												<html:radio property="receive" value="2"  
													onclick="javascript:diffshow('2');" />
											</td>
											<td>
												����
												<html:radio property="receive" value="5"
													onclick="javascript:diffshow('5');" />
											</td>
										</tr>
									</table>
									<table width="60%" border="1" cellpadding="1"
										cellspacing="0" bordercolor="#AA817F"
										bordercolordark="#ffffff">
										 <input  name="id" type="hidden" value="<bean:write name="result" property="id" />"/>
                                         <input  name="deviceid" type="hidden" value="<bean:write name="result" property="deviceid" />"/>
										<tr>
											<td align="center" width="40%">
												�豸id
											</td>
											<td align="left">
												<bean:write name="result" property="devphyid" />
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="center">
												�豸��
											</td>
											<td align="left">
												<bean:write name="result" property="devicename" />
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="center">
												����ԭ��
											</td>
											<td align="left">
												<bean:write name="result" property="statename" />
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="center">
												��ʼʱ��
											</td>
											<td align="left">
												<bean:write name="result" property="errstarttime" />
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="center">
												����ʱ��
											</td>
											<td align="left">
												<bean:write name="result" property="errlasttime" />
												&nbsp;
											</td>
										</tr>
									</table>
                                    <table id="detail" width="60%" border="1" cellpadding="1" cellspacing="0"
                                        bordercolor="#AA817F" bordercolordark="#ffffff">
                                        <tr>
                                            <td align="center" width="40%">
                                                                                                                  ����ע
                                            </td>
                                            <td align="left">
                                                <html:textarea property="dealmark"></html:textarea>
                                                &nbsp;
                                            </td>
                                        </tr>
                                    </table>
									<table id="detail1" style="display: none" width="60%" border="1" cellpadding="1" cellspacing="0"
										bordercolor="#AA817F" bordercolordark="#ffffff">
										<tr>
											<td align="center" width="40%">
												���Ե���ʱ
											</td>
											<td align="left">
												<html:text size="15" property="canceltime"></html:text>
												��ʽ:20090731&nbsp;
											</td>

										</tr>

										<tr>
											<td align="center">
												����ԭ��
											</td>
											<td align="left">
												<html:textarea property="cancelreason"></html:textarea>
												&nbsp;
											</td>
										</tr>
									</table>
									
									<table width="60%" border="1" cellpadding="1"
										cellspacing="0" bordercolor="#AA817F"
										bordercolordark="#ffffff">
										<tr>
											<td COLSPAN="2" align="center">
												<input name="send" type="button" value="����" onclick="sub()" />
												<input name="back" type="button" value="����"
													onclick="javascript:history.go(-1);" />
											</td>
										</tr>
									</table>
								</html:form>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr valign="bottom" height="0%">
				<td>
					<table class="NavBarTabs" width="100%" height="20" cellspacing="0"
						cellpadding="0" border="0">
						<tr>
							<td Class="Copyright">
								&nbsp;
							</td>
							<td Class="Copyright" align="center">
								Copyright 2005-2009 Nanjin University All Rights Reserved
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</body>
</html>