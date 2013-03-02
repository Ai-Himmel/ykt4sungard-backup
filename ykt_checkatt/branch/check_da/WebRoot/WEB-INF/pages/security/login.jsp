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

<center>
	<table width="770" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="34" align="left" valign="top" bgcolor="#FFFFFF">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td height="424" align="left" valign="top" background="<%=stylePath%>/images/login_bg.jpg">
				<html:form action="loginAction?method=login" target="_top" focus="name" onsubmit="return validateLoginForm(this);">
													
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td width="46%" height="294">
								&nbsp;
							</td>
							<td>
								&nbsp;<html:errors />
							</td>
						</tr>
						<tr>
							<td>
							&nbsp; 
							</td>
							<td width="54%">
								<table width="232" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td width="65" height="30" align="center" valign="middle" nowrap="nowrap" class="mediumwhite">
											用户名：
										</td>
										<td width="167" height="30">
										    <html:text property="name" size="20" maxlength="18" onkeydown="if(event.keyCode==13) {event.keyCode=9}" styleClass="input_box2"/>
											
										</td>
									</tr>
									<tr>
										<td height="30" align="center" valign="middle" nowrap="nowrap" class="mediumwhite">
											密&nbsp;&nbsp;码：
										</td>
										<td height="30">
    										<html:password property="password" maxlength="255" redisplay="false" styleClass="input_box2" onkeydown="if(event.keyCode==13) {event.keyCode=9}" />
										</td>
									</tr>
									<tr>
										<td height="30" align="center" valign="middle" nowrap="nowrap" class="mediumwhite">
											验证码：
										</td>
										<td height="30">
										<input type="text" name="chkCode"  class="input_box2" maxlength=50 onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) {loginForm.submit();}}">
																			<br>
																			<html:img page="/CheckCodeImage" style="border: 1 dotted black" />					
										</td>
									</tr>
									<tr>
										<td height="20" align="left" nowrap="nowrap" class="bottom">
											&nbsp;
										</td>
										<td height="20" align="left" valign="top">
											&nbsp;
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
			<td align="left" valign="top">
				<img src="<%=stylePath%>/images/button.jpg" width="770" height="61" border="0" usemap="#Map" />
				
			</td>
		</tr>
		
		<tr>
			<td height="81" align="center" valign="top" bgcolor="#EDEDEF">
				<table border="0" align="center" cellpadding="0" cellspacing="0">
					<tr align="center" valign="bottom">
						<!-- 
						<td align="right" valign="middle">
							<img src="<%=stylePath%>/images/e.gif" width="37" height="46" />
						</td>
						
						<td width="10" align="left" class="bottom">
							&nbsp;
						</td>-->
						<td align="left" valign="middle">
							上海远程教育集团版权所有
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>

	<map name="Map" id="Map">
		<area shape="circle" coords="557,32,27" href="javascript:document.loginForm.submit();" />
	</map>
</center>
<html:javascript formName="loginForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>

