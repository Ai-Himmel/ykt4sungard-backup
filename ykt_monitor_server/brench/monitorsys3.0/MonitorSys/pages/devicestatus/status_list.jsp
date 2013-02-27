<%@ page language="java" pageEncoding="UTF-8"%>
<%@page import="java.util.List"%>
<%@ include file="../commons/init.jsp"%>

<html>
	<head>
		<meta http-equiv="REFRESH"
			content="120; URL=/monitorsys/devicestatus.do?method=queryDeviceStatus">
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
		document.devicestatusForm.submit();
	}
	function loginout() {
		document.devicestatusForm.action = 'login.do?method=loginout';
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
								<a class="NavBarMenu" href="#">帮助</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
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
											<strong>异常节点查询</strong>
										</td>
										<td>
											<table border="0" cellpadding="0" cellspacing="0"
												width="70%">
												<tr>
													<td align="right" nowrap="nowrap">
														&nbsp;&nbsp;

													</td>
												</tr>
											</table>
										</td>
									</tr>
								</table>


								<table width="70%" border="0" cellpadding="5" cellspacing="0">
									<html:form action="devicestatus.do?method=queryDeviceStatus">
										<tr class="ViewHeader">
											<td width="100px">
												设备名称
												<br>
												<html:text property="devicename" />
											</td>
											<td width="100px">
												异常原因
												<br>
												<html:select property="errreason">
													<html:option value="">-------------</html:option>
													<html:options collection="stateDict"
														labelProperty="itemName" property="itemNo" />
												</html:select>
											</td>
											<td width="100px" valign="middle">
												设备状态
												<br>
												<html:select property="devstatus">
													<html:option value="">-------------</html:option>
													<html:option value="1">新增</html:option>
													<html:option value="2">维护中</html:option>
													<html:option value="3">人工修复</html:option>
													<html:option value="4">自动恢复</html:option>
													<html:option value="5">已忽略</html:option>
													<html:option value="6">报废</html:option>
												</html:select>
											</td>
											<td width="40%">
												&nbsp;
												<br>
												<input name="Submit" type="image"
													src="/monitorsys/pages/images/SmallButton.Search.gif"
													width="57" height="18">
											</td>
										</tr>
										<tr class="ViewHeader">

											<td colspan="4" height="15">
												&nbsp;
											</td>
										</tr>
									</html:form>
								</table>
								<br>
								<!-- Title=Last 25 Events -->
								<!-- Advanced=TRUE -->

								<!-- Level=6 -->

								<table width="100%" border="0" cellpadding="8" cellspacing="0">
									<tr class="ViewHeader">
										<td height="35" align="left" nowrap="nowrap">
										<% 
                                           List resList = (List)request.getAttribute("result");       
                                         %>
											<B>所有<%= resList==null?"0":String.valueOf(resList.size())%>条异常信息</b>
										</td>
										<td>
											<table border="0" cellpadding="0" cellspacing="0"
												width="100%">
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
									<tr align="center">
										<td>
											对象名称
										</td>
										<td>
											故障原因
										</td>
										<td>
											起始时间
										</td>
										<td>
											修复时间
										</td>
										<td>
											异常持续时间
										</td>
										<td>
											负责人
										</td>
										<td>
											接收人
										</td>
										<td>
											维护状态
										</td>
									</tr>

									<logic:present name="result" scope="request">
										<logic:iterate name="result" id="dev">

											<tr align="center">
												<td>
													<bean:write name="dev" property="devicename" />
													&nbsp;
												</td>
												<td>
													<bean:write name="dev" property="statename" />
													&nbsp;
												</td>
												<td>
													<bean:write name="dev" property="errstarttime" />
													&nbsp;
												</td>
												<td>
													<bean:write name="dev" property="errendtime" />
													&nbsp;
												</td>
												<td>
													<bean:write name="dev" property="errlastdate" />
													&nbsp;
												</td>
												<td>
													<bean:write name="dev" property="contactname" />
													&nbsp;
												</td>
												<td>
													&nbsp;
													<bean:write name="dev" property="rcvman" />
												</td>
												<td>
													<logic:equal name="dev" property="devstatus" value="1">
														<html:link
															href="/monitorsys/devicestatus.do?method=editDeviceStatus&status=1"
															paramId="id" paramName="dev" paramProperty="id"> 
								                                                               新增
								                       </html:link>
													</logic:equal>
													<logic:equal name="dev" property="devstatus" value="2">
														<html:link
															href="/monitorsys/devicestatus.do?method=editDeviceStatus&status=2"
															paramId="id" paramName="dev" paramProperty="id"> 
								                                                                    维护中
								                         </html:link>
													</logic:equal>
													<logic:equal name="dev" property="devstatus" value="3"><html:link
                                                            href="/monitorsys/devicestatus.do?method=editDeviceStatus&status=3"
                                                            paramId="id" paramName="dev" paramProperty="id"> 
                                                                                                手工修复
                                                         </html:link></logic:equal>
													<logic:equal name="dev" property="devstatus" value="4"><html:link
                                                            href="/monitorsys/devicestatus.do?method=editDeviceStatus&status=4"
                                                            paramId="id" paramName="dev" paramProperty="id"> 
                                                                                                 自动恢复 
                                                         </html:link> </logic:equal>
                                                     <logic:equal name="dev" property="devstatus" value="5"><html:link
                                                            href="/monitorsys/devicestatus.do?method=editDeviceStatus&status=5"
                                                            paramId="id" paramName="dev" paramProperty="id"> 
                                                                                                 已忽略
                                                         </html:link> </logic:equal>
                                                          <logic:equal name="dev" property="devstatus" value="6"><html:link
                                                            href="/monitorsys/devicestatus.do?method=editDeviceStatus&status=6"
                                                            paramId="id" paramName="dev" paramProperty="id"> 
                                                                                                 报废
                                                         </html:link> </logic:equal>

												</td>

											</tr>
										</logic:iterate>
									</logic:present>
								</table>

								<br>

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