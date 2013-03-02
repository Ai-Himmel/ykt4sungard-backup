<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@page import="com.wiscom.is.*, java.net.*" %>
<%@page import="org.king.web.util.KSConfiguration"%>
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
		<%	
		String logingotoUrl = KSConfiguration.getInstance().getProperty("logingotoUrl");
		String is_config = request.getRealPath("/client.properties");
		IdentityFactory factory = IdentityFactory.createFactory(is_config);
	    IdentityManager im = factory.getIdentityManager();
		String gotoURL = HttpUtils.getRequestURL(request).toString();
		//通过认证接口获取HTTP登录URL
		String loginUrl = im.getLoginURL();
		
		//构建HTTPS登录URL
		String loginUrls = loginUrl.substring(loginUrl.indexOf("//") +2 );
		loginUrls = loginUrls.substring(0,loginUrls.indexOf(':'));
		loginUrls = "https://"+loginUrls+":443/amserver/UI/Login";
				
		//构建最终的登录URL：loginURL
		String loginURL = loginUrls +"?goto=" + logingotoUrl;
		
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
			
													
					<table width="100%" border="0" cellspacing="0" cellpadding="0" >
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
								<html:form action="loginAction?method=login" target="_top" focus="name" onsubmit="return validateLoginForm(this);">
				   	<table width="100%" border="0" cellspacing="0" cellpadding="0" 
																 style='display:block'  id="selectTab">
																   <tr>
									                                  <td height="50" align="center">
									                                  <input type="button" name="Submit2" onclick="location.href='<%=loginURL%>'" value="统一身份认证登录" style="background:url(<%=stylePath%>/images/login-btn2.gif); width:160px; height:40px; border:0px; font-size:14px; font-weight:bold; color:#063971"></td>
									                                </tr>
																 
									                                <tr>
									                                  <td height="50" align="center"><label>
									                                    <input type="button" name="Submit" onclick="document.getElementById('selectTab').style.display='none';
									                                    document.getElementById('localLogin').style.display='block';"  
									                                     value="本地用户密码登录" style="background:url(<%=stylePath%>/images/login-btn.gif); width:146px; height:36px; border:0px; font-size:14px; font-weight:bold; color:#063971">
									                                  </label></td>
									                                </tr>
									                                
                   </table>
								<table width="232" border="0" cellspacing="0" cellpadding="0" style='display:none'  id="localLogin">
								   
								 
									<tr>
										<td width="65" height="29" align="center" valign="middle" nowrap="nowrap" class="mediumwhite">
											用户名：
										</td>
										<td width="167" height="29">
										    <html:text property="name" size="20" maxlength="18" onkeydown="if(event.keyCode==13) {event.keyCode=9}" styleClass="input_box2"/>
											
										</td>
									</tr>
									<tr>
										<td height="29" align="center" valign="middle" nowrap="nowrap" class="mediumwhite">
											密&nbsp;&nbsp;码：
										</td>
										<td height="29">
    										<html:password property="password" maxlength="255" redisplay="false" styleClass="input_box2" onkeydown="if(event.keyCode==13) {event.keyCode=9}" />
										</td>
									</tr>
									<tr>
										<td height="29" align="center" valign="middle" nowrap="nowrap" class="mediumwhite">
											验证码：
										</td>
										<td height="29">
										<input type="text" name="chkCode"  class="input_box2" maxlength=50 onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) {loginForm.submit();}}">
																			<br>
																			<html:img page="/CheckCodeImage" style="border: 1 dotted black" />					
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
						<td align="right" valign="middle">
							<img src="<%=stylePath%>/images/e.gif" width="37" height="46" />
						</td>
						<td width="10" align="left" class="bottom">
							&nbsp;
						</td>
						<td align="left" valign="middle">
							复旦大学&amp;金仕达联合研制 &nbsp;&nbsp;Mail:ecard@fudan.edu.cn &nbsp;&nbsp;服务电话：021-55664064
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

