<%@ include file="/html/portlet/login/init.jsp" %>

<%
String login = LoginAction.getLogin(request, "login", company);
String password = ParamUtil.getString(request, "password");
String authCode = ParamUtil.getString(request, "authCode");
boolean rememberMe = ParamUtil.getBoolean(request, "remember_me");
%>

<c:if test="<%= !themeDisplay.isSignedIn() %>">
	<form action="<portlet:actionURL><portlet:param name="struts_action" value="/login/view" /><portlet:param name="<%= Constants.CMD %>" value="<%= Constants.UPDATE %>" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
	<input name="<portlet:namespace />remember_me" type="hidden" value="<%= rememberMe %>">

	<table height=100% width=100% border="0" align=center cellpadding="2" cellspacing="0">

	<c:if test='<%= SessionErrors.contains(renderRequest, AuthException.class.getName()) %>'>
		<tr>
			<td colspan="2">
				<a class="portlet-msg-error"><%= LanguageUtil.get(pageContext, "authentication-failed") %></a>
			</td>
		</tr>
	</c:if>

	<c:if test='<%= SessionErrors.contains(renderRequest, NoSuchUserException.class.getName()) || SessionErrors.contains(renderRequest, UserEmailAddressException.class.getName()) ||
								SessionErrors.contains(renderRequest, UserIdException.class.getName()) %>'>
		<tr>
			<td colspan="2">
				<a class="portlet-msg-error"><%= LanguageUtil.get(pageContext, "please-enter-a-valid-login") %></a>
			</td>
		</tr>
	</c:if>
	
	<c:if test='<%= SessionErrors.contains(renderRequest, ValidAuthCodeException.class.getName()) %>'>
		<tr>
			<td colspan="2">
				<a class="portlet-msg-error" ><%= LanguageUtil.get(pageContext, "ecard.error.validcode") %></a>
			</td>
		</tr>
	</c:if>
	<tr>
		<td>&nbsp;</td>
		<td>&nbsp;</td>
	</tr>
	<tr>
		<td class=text_brown valign="top">
			<bean:message key="cardinfo.content.personId" />
		</td>
		<td >
			<input class="textbox" style="width:153px" name="<portlet:namespace />login" type="text" value="<%= login %>">
		</td>
	</tr>

	<c:if test='<%= SessionErrors.contains(renderRequest, UserPasswordException.class.getName()) %>'>
		<tr>
			<td colspan="2">
				<font class="portlet-msg-error" style="font-size: 11;"><%= LanguageUtil.get(pageContext, "please-enter-a-valid-password") %></font>
			</td>
		</tr>
	</c:if>

	<tr>
		<td  class=text_brown valign="top">
			<bean:message key="password" />
		</td>	
		<td>
			<input class="textbox" style="width:153px" name="<portlet:namespace />password" type="password" value="<%= password %>">
		</td>
	</tr>
	<tr>
		<td class=text_brown valign="top">
			<bean:message key="ecard.authcode" />
		</td>
		<td >
			<input class="textbox" style="width:153px" name="authCode" type="text" value="<%= authCode%>">			
		</td>
	</tr>
	<tr>
		<td>&nbsp;</td>
		<td>
			<img border="0" hspace="0" src="<%= themeDisplay.getPathCaptcha() %>/challenge" vspace="0" width=153 height=55>
		</td>
	</tr>
	
	<tr>
		<td aligh="left">
		<A HREF="https://www.ecard.fudan.edu.cn/web/guest/ecardfaq" >
			<FONT SIZE=2 COLOR="0000ff"><bean:message key="ecard.link.losepwd" /></FONT>
		</A>
		</td>
		<td align="right">
			<input type=submit class="button_blank" value="<%= LanguageUtil.get(pageContext, "sign-in") %>">
		</td>
	</tr>
	</table>

	</form>

	<script language="JavaScript">
		document.<portlet:namespace />fm.<portlet:namespace />login.focus();
	</script>
</c:if>
		