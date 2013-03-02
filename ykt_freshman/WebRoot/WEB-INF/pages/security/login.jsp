<%@page pageEncoding="GBK"%>
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
						<td width="134" bgcolor="#FDE3E4" valign="top">
							<img name="login1_r3_c1" src="<%=stylePath%>/images/loginleft.jpg" width="134" height="344" border="0">
						</td>
						<td align="center" valign="top">
							<table width="100%" height="344" border="0" cellpadding="0" cellspacing="0">
								<tr>
									<td align="center" valign="top">
										<table width="100%" height="343" border="0" cellpadding="0" cellspacing="0">
											<tr align="left" valign="top">
												<td width="1" bgcolor="#EFA5A2"></td>
												<td align="center" bgcolor="#F9CCC9">

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
																		<td width="70" align="center" valign="middle">
																			<a href="#"><img src="<%=stylePath%>/images/uis.gif" width="42" height="24" border="0" usemap="#Map1"></a>
																		</td>
																		<td width="50" align="center" valign="middle">
																			<a href="#"><img src="<%=stylePath%>/images/login.gif" width="39" height="17" border="0" usemap="#Map2"></a>
																		</td>
																		<td align="center" valign="middle">
																			<a href="http://www.ecampus.fudan.edu.cn/ecampus/server/help_urppeople.jsp" target="_blank" class="login_link"><strong>忘记密码</strong></a>
																		</td>
																	</tr>
																</table>
															</td>
														</tr>
                                                        <tr><td>&nbsp;</td></tr>
														<tr>
															<td align="center" valign="top" class="tdborder04">
																<table width="96%" border="0" cellspacing="0" cellpadding="0">
																	<tr>																	    
																		<td align="left" valign="top" class="small2">
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
												<td width="1" bgcolor="#EFA5A2"></td>
											</tr>
										</table>
									</td>
								</tr>
								<tr>
									<td height="1" align="left" valign="top" bgcolor="#EFA5A2"></td>
								</tr>
							</table>
						</td>
						<td width="661" align="left" bgcolor="#FDE3E4" valign="top">
							<img name="login1_r3_c5" src="<%=stylePath%>/images/loginright.jpg" width="661" height="344" border="0">
						</td>
					</tr>
				</table>
			</td>
		</tr>
		<tr>
			<td align="center" valign="top" bgcolor="FEE4E3" height="3">
			</td>
		</tr>
		<tr>
			<td height="5" align="center" valign="middle" bgcolor="#ED8A85">
				<img src="<%=stylePath%>/images/bottom2.gif" width="1004" height="5">
			</td>
		</tr>
		<tr>
			<td height="75" align="center" valign="middle" bgcolor="#ED8A85">
                <a href="http://www.fudan.edu.cn/" target="_blank" class="white">复旦大学</a>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			    <a href="http://www.fdcollege.fudan.edu.cn/" target="_blank" class="white">复旦学院</a>
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			    <a href="http://www.jwc.fudan.edu.cn/" target="_blank" class="white">教务处</a>
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			    <a href="http://vcampus.fudan.edu.cn/" target="_blank" class="white">虚拟校园</a>
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		    	<a href="http://www.ecampus.fudan.edu.cn/" target="_blank" class="white">信息化校园</a>
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		    	<a href="http://www.fudan.edu.cn/xuanke/" target="_blank" class="white">选课系统</a>	
				<table border="0" align="center" cellpadding="0" cellspacing="0">
					<tr align="center" valign="bottom">
						<td align="right" valign="middle">
							<img src="<%=stylePath%>/images/image_xinxiban.gif" width="37" height="46">
						</td>
						<td width="10" align="left" class="bottom">
							&nbsp;
						</td>
						<td align="left" valign="middle" class="bottom">
							复旦大学&amp;金仕达联合研制
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>

	<map name="Map1">
		<area shape="rect" coords="0,0,42,24" href="http://www.ecampus.fudan.edu.cn/ecampus/campus/soft_uis.jsp" alt="此图标表示本系统使用统一身份认证，用户名为您的工号或者学号" target="_blank">
	</map>
	<map name="Map2">
		<area shape="rect" coords="0,0,39,17" href="javascript:document.loginForm.submit();">
	</map>

</center>
<html:javascript formName="loginForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>

<script language="JavaScript">

function DoNoticeList(){

   document.loginForm.action="noticepubAction.do?method=find";
   document.loginForm.submit();
}
</script>