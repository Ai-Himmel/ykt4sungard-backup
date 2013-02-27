<%@ page language="java" pageEncoding="GBK"%>
<%@page import="java.util.List"%>
<%@ include file="../commons/init.jsp"%>

<html>
	<head>
		<title>校园一卡通综览</title>

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
      if(flag=='1'){
          document.getElementById("detail").style.display='none';
      }else{
          document.getElementById("detail").style.display='';
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
									onclick="javascript: getDevList();">列表</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="NavBarMenu" href="#" onclick="javascript: loginout();">登出</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="NavBarMenu" href="#" target="_blank">帮助</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
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
											<strong>异常节点详细信息</strong>
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
								
								<table width="100%" border="1" align="center" cellpadding="1"
                                    cellspacing="0" bordercolor="#AA817F" bordercolordark="#ffffff">
                                    <logic:present name="serviceList" scope="request">
                                        <logic:iterate name="serviceList" id="service">

                                            <tr align="center">
                                                <td>
                                                    <bean:write name="service" property="rcvman" />
                                                    &nbsp;
                                                </td>
                                                <td>
                                                    <bean:write name="service" property="rcvtime" />
                                                    &nbsp;
                                                </td>
                                                <td>
                                                    <bean:write name="service" property="dealmark" />
                                                    &nbsp;
                                                </td>
                                              
                                                <td>
                                                    <logic:equal name="service" property="dealstatus" value="1">已接受 </logic:equal>
                                                    <logic:equal name="service" property="dealstatus" value="2">已处理</logic:equal>
                                                </td>

                                            </tr>
                                        </logic:iterate>
                                    </logic:present>
                                </table>

									<table width="60%" border="1" cellpadding="1"
										cellspacing="0" bordercolor="#AA817F"
										bordercolordark="#ffffff">
										<tr>
											<td align="center" width="40%">
												设备id
											</td>
											<td align="left">
												<bean:write name="result" property="devphyid" />
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="center">
												设备名
											</td>
											<td align="left">
												<bean:write name="result" property="devicename" />
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="center">
												故障原因
											</td>
											<td align="left">
												<bean:write name="result" property="statename" />
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="center">
												起始时间
											</td>
											<td align="left">
												<bean:write name="result" property="errstarttime" />
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="center">
												持续时间
											</td>
											<td align="left">
												<bean:write name="result" property="errlasttime" />
												&nbsp;
											</td>
										</tr>
									</table>
									<table width="60%" border="1" cellpadding="1"
										cellspacing="0" bordercolor="#AA817F"
										bordercolordark="#ffffff">
										<tr>
											<td COLSPAN="2" align="center">
												<input name="back" type="button" value="返回"
													onclick="javascript:history.go(-1);" />
											</td>
										</tr>
									</table>
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