<%@ include file="/html/portal/init.jsp" %>


<%
String cmd = ParamUtil.getString(request, "my_account_cmd");

String emailAddress = request.getParameter("my_account_email_address");
if ((emailAddress == null) || (emailAddress.equals(StringPool.NULL))) {
	emailAddress = "";
}

String login = LoginAction.getLogin(request, "my_account_login", company);
String authCode = ParamUtil.getString(request, "authCode");
/*String password = request.getParameter(SessionParameters.get(request, "my_account_password"));
if ((password == null) || (password.equals(StringPool.NULL))) {
	password = "";
}*/

boolean rememberMe = ParamUtil.get(request, "my_account_r_m", false);

PortletURL createAccountURL = new PortletURLImpl(request, PortletKeys.MY_ACCOUNT, layoutId, true);

createAccountURL.setWindowState(WindowState.MAXIMIZED);
createAccountURL.setPortletMode(PortletMode.VIEW);

createAccountURL.setParameter("struts_action", "/my_account/create_account");

String createAccountURLToString = createAccountURL.toString();
%>

<script language="JavaScript">
	function signIn() {
		document.fm.my_account_cmd.value = "auth";
		document.fm.referer.value = "<%= themeDisplay.getPathMain() %>";
		submitForm(document.fm);
	}
</script>

<form action="<%= themeDisplay.getPathMain() %>/portal/login" method="post" name="fm">
<input name="my_account_cmd" type="hidden" value="">
<input name="referer" type="hidden" value="<%= themeDisplay.getPathMain() %>">
<input name="my_account_r_m" type="hidden" value="<%= rememberMe %>">



<c:if test="<%= SessionErrors.contains(request, PrincipalException.class.getName()) %>">
	<table border="0" cellpadding="0" cellspacing="0" width="95%">
	<tr>
		<td align=center>
			<a class="portlet-msg-error"><span class="gamma-neg-alert">

			<%= LanguageUtil.get(pageContext, "you-have-attempted-to-access-a-section-of-the-site-that-requires-authentication") %>

			<c:if test="<%= !company.isStrangers() %>">
				<%= LanguageUtil.get(pageContext, "please-sign-in-to-continue") %>
			</c:if>

			<c:if test="<%= company.isStrangers() %>">

				<%
				String createAccountLinkOpen = "<a class=\"gamma-neg-alert\" href=\"" + createAccountURLToString + "\"><u>";
				String createAccountLinkClose = "</u></a>";
				%>

				<%= LanguageUtil.format(pageContext, "please-sign-in-or-create-an-account-to-continue", new Object[] {createAccountLinkOpen, createAccountLinkClose}, false) %>
			</c:if>

			<br></span></a>

			<br>
		</td>
	</tr>
	</table>
</c:if>



<table border="0" cellpadding="0" cellspacing="0" width="95%">
<tr>
	<td class=text_brown>
		
&nbsp;
		
	</td>
	<td width="10">
		&nbsp;
	</td>
	<td>
		&nbsp;
	</td>
</tr>
<tr>
	
	<td width="30%">
		&nbsp;
	</td>
	<td valign="top" width="50%">
		

			<c:if test='<%= cmd.equals("auth") && SessionErrors.contains(request, AuthException.class.getName()) %>'>
				<table border="0" cellpadding="0" cellspacing="2">
				<tr>
					<td>
						<a class="portlet-msg-error"><span class="gamma-neg-alert"><%= LanguageUtil.get(pageContext, "authentication-failed") %></span></a>
					</td>
				</tr>
				</table>
			</c:if>

			<table border="0" cellpadding="0" cellspacing="2">
			<tr>
				<td colspan="2">
				</td>
				<td>
					<c:if test='<%= cmd.equals("auth") && (SessionErrors.contains(request, NoSuchUserException.class.getName()) || 
											SessionErrors.contains(request, UserEmailAddressException.class.getName()) || 
											SessionErrors.contains(request, UserIdException.class.getName())) %>'>
						<table border="0" cellpadding="0" cellspacing="0">
						<tr>
							<td>
								<a class="portlet-msg-error"><span class="gamma-neg-alert"><%= LanguageUtil.get(pageContext, "please-enter-a-valid-login") %></span></a>
							</td>
						</tr>
						</table>
					</c:if>
				</td>
			</tr>
			<tr>
				<td class=text_brown>
					

					<c:if test="<%= company.getAuthType().equals(Company.AUTH_TYPE_EA) %>">
						<%= LanguageUtil.get(pageContext, "email-address") %>
					</c:if>

					<c:if test="<%= company.getAuthType().equals(Company.AUTH_TYPE_ID) %>">
						<%= LanguageUtil.get(pageContext, "cardinfo.content.personId") %>
					</c:if>

					
				</td>
				<td width="10">
					&nbsp;
				</td>
				<td>
					<input class="textbox" name="my_account_login" style="width:153px" type="text" value="<%= login %>"  onKeyPress="if (event.keyCode == 13) { signIn(); }">
				</td>
			</tr>
			
	

			<c:if test='<%= cmd.equals("auth") && SessionErrors.contains(request, UserPasswordException.class.getName()) %>'>
				<tr>
					<td colspan="2">
					</td>
					<td>
						<a class="portlet-msg-error" ><span class="gamma-neg-alert"><%= LanguageUtil.get(pageContext, "please-enter-a-valid-password") %></span></a>
					</td>
				</tr>
			</c:if>

			<tr>
				<td class=text_brown>
					<%= LanguageUtil.get(pageContext, "password") %>
				</td>
				<td width="10">
					&nbsp;
				</td>
				<td>
					<input class="textbox" name="my_account_password" style="width:153px" type="password" value="" onKeyPress="if (event.keyCode == 13) { signIn(); }">
				</td>
			</tr>
			<c:if test='<%= SessionErrors.contains(request, ValidAuthCodeException.class.getName()) %>'>
				<tr>
					<td colspan="2">
					</td>
					<td>
						<a class="portlet-msg-error"><span class="gamma-neg-alert"><%= LanguageUtil.get(pageContext, "ecard.error.validcode") %></span></a>
					</td>
				</tr>
			</c:if>
			<tr>
				<td class=text_brown>
					<%= LanguageUtil.get(pageContext, "ecard.authcode") %>
				</td>
				<td width="10">
					&nbsp;
				</td>
				<td>
					<input class="textbox" name="authCode" style="width:153px" type="text" value="<%= authCode%>" onKeyPress="if (event.keyCode == 13) { signIn(); }">					
				</td>
			</tr>
			<tr>
				<td>
					&nbsp;
				</td>
				<td width="10">
					&nbsp;
				</td>
				<td>
					<img border="0" width=153 height=55 hspace="0" src="<%= themeDisplay.getPathCaptcha() %>/challenge" vspace="0" >
				</td>
			</tr>

			
			<tr> 
				<td align="right" colspan="3">
					<input class="button_blank" type="button" value="<%= LanguageUtil.get(pageContext, "sign-in") %>" onClick="signIn();">
				</td>
			</tr>
			</table>
		
	</td>
	<td width="20%">
		&nbsp;
	</td>
</tr>
</table>

</form>

<c:if test='<%= SessionErrors.contains(request, "authentication_required") %>'>
	<script language="JavaScript">
		document.fm.my_account_login.focus();
	</script>
</c:if>
