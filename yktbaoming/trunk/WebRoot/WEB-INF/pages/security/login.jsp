<%@page pageEncoding="GBK"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="../tiles/include.jsp"%>
<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
			String stylePath = context + "/pages/style/" + style;

			response.setHeader("Pragma", "no-cache"); //http 1.0
			response.setHeader("Cache-Control", "no-cache"); //http 1.1
			response.setDateHeader("Expires", 0); //prevents caching at the proxy server

			%>
<bean:define id="loginTitle">
	<bean:message bundle="security" key="login.title" />
</bean:define>
<center>
	<table width="1004" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td align="center" valign="top">
				<img name="login1_r2_c1" src="<%=stylePath%>/images/logintop2.gif" width="1004" height="35" border="0">
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td width="134" valign="top">
							<img name="login1_r3_c1" src="<%=stylePath%>/images/loginleft.jpg" width="134" height="395" border="0">
						</td>
						<td align="center" valign="top">
							<table width="100%" height="344" border="0" cellpadding="0" cellspacing="0">
								<tr>
									<td align="center" valign="top">
										<table width="100%" height="395" border="0" cellpadding="0" cellspacing="0">
											<tr align="left" valign="top">
												<td width="1" bgcolor="0047AA"></td>
												<td align="center" bgcolor="#E7F1F5">

													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td align="left" valign="top">
																<html:form action="loginAction?method=login" target="_top" focus="name" onsubmit="return validateLoginForm(this);">
																	<html:errors />
																	<table border="0" cellspacing="0" cellpadding="0">
																		<tr>
																			<td width="72" height="30" align="right" valign="middle" nowrap class="medium">
																				用户名：
																			</td>
																			<td width="167" height="30">
																				<html:text property="name" size="20" maxlength="18" style="width:120;background: url(none); FONT-SIZE: 12px;  border: 1 solid #000000" onkeydown="if(event.keyCode==13) {event.keyCode=9}" />
																		</tr>
																		<tr>
																			<td height="30" align="right" valign="middle" nowrap class="medium">
																				密&nbsp;&nbsp;&nbsp;码：
																			</td>
																			<td height="30">
																				<html:password property="password" maxlength="255" redisplay="false" style="width:120;background: url(none); FONT-SIZE: 12px;  border: 1 solid #000000" onkeydown="if(event.keyCode==13) {event.keyCode=9}" />

																			</td>
																		</tr>
																		<tr>
																			<td height="30" align="right" valign="middle" nowrap class="medium">
																				验证码：
																			</td>
																			<td height="30">
																				<table width="120" border="0" cellspacing="0" cellpadding="0">
																					<tr>
																						<td align="left" valign="middle">
																							<input name="chkCode" style="width:60;background: url(none); FONT-SIZE: 12px;  border: 1 solid #000000" maxlength=50 onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) {loginForm.submit();}}">
																						</td>
																						<td align="right" valign="middle">
																							<html:img page="/CheckCodeImage" style="border: 1 dotted black" width="52" height="20" />
																						</td>
																					</tr>
																				</table>
																			</td>
																		</tr>

																	</table>
																</html:form>
															</td>
														</tr>
														<tr>
															<td height="24" colspan="2" align="left" valign="top" nowrap class="bottom">
																<table width="100%" height="24" border="0" cellpadding="0" cellspacing="0">
																	<tr>
																		<td width="115" align="center" valign="middle">
																			&nbsp;
																		</td>
																		<td align="center" valign="middle">
																			<a href="#"><img src="<%=stylePath%>/images/login.gif" width="39" height="17" border="0" usemap="#Map2"></a>
																		</td>
																		<td align="center" valign="middle">
																			&nbsp;
																		</td>
																	</tr>
																</table>
															</td>
														</tr>                                                        
														<tr>
															<td align="left" valign="middle" >
															&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<A href="/baoming/testPublicAction.do?method=search4Listview" target="_blank"><B>考试报名信息直通车</B></A>	<img src="<%=stylePath%>/images/arrow.gif" width="25" height="15" border="0">																
														    </td>
														</tr>	
														<tr>
															<td align="center" valign="top" class="tdborder04">
															    <br>
																<table width="96%" border="0" cellspacing="0" cellpadding="0">																	
																	<tr>
																		<logic:present name="noticelist" scope="request">																			 
																		<marquee scrollamount="1.5" direction="up" onmouseover="this.stop()"  onmouseout="this.start()"> 																			 																		      
                                                                              <logic:iterate name="noticelist" id="nl" type="java.util.Map"  indexId="i">	
                                                                              <textarea name="body" style="display:none"><bean:write name="nl" property="body"/></textarea >																		
																			    <script>document.write(document.all.body.value);</script>
                                                                               </logic:iterate>                   
                                                                        </marquee>
                                                                        </logic:present> 
																		</td>
																	</tr>																	
																</table>
															</td>
														</tr>
													</table>
												</td>
												<td width="1" bgcolor="#0047AA"></td>
											</tr>
										</table>
									</td>
								</tr>
								<tr>
									<td height="1" align="left" valign="top" bgcolor="#0047AA"></td>
								</tr>
							</table>
						</td>
						<td width="661" align="left" valign="top">
							<img name="login1_r3_c5" src="<%=stylePath%>/images/loginright.jpg" width="661" height="395" border="0">
						</td>
					</tr>
				</table>
			</td>
		</tr>
		<tr>
			<td align="center" valign="top" bgcolor="#156EAA" height="3">
			</td>
		</tr>		
		<tr>
			<td height="60" align="center" valign="middle" bgcolor="#FFFFFF"> 			
			    <table border="0" align="center" cellpadding="0" cellspacing="0">			        
					<tr align="center" valign="bottom">
						<td align="center" valign="middle" style="font-size: 12px; color: #000000;">
							SUNGARD金仕达 版权所有
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>

	<map name="Map1">
		<area shape="rect" coords="0,0,42,24" href="#" alt="此图标表示本系统使用统一身份认证，用户名为您的工号或者学号" target="_blank">
	</map>
	<map name="Map2">
		<area shape="rect" coords="0,0,39,17" href="javascript:document.loginForm.submit();">
	</map>

</center>
<html:javascript formName="loginForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>
