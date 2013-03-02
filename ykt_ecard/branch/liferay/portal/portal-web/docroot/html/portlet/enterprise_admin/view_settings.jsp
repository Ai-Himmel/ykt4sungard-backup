<%
/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
%>

<%@ include file="/html/portlet/enterprise_admin/init.jsp" %>

<%
String tabs2 = ParamUtil.getString(request, "tabs2");
String tabs3 = ParamUtil.getString(request, "tabs3");

String portletURLString = (String)request.getAttribute("view.jsp-portletURLString");
%>

<liferay-ui:tabs
	names="general,authentication,default-user-associations,reserved-screen-names,mail-host-names,email-notifications"
	param="tabs2"
	url="<%= portletURLString %>"
/>

<c:choose>
	<c:when test='<%= tabs2.equals("authentication") %>'>
		<liferay-ui:tabs
			names="general,ldap,cas,ntlm,open-id,open-sso"
			param="tabs3"
			url="<%= portletURLString %>"
		/>

		<c:choose>
			<c:when test='<%= tabs3.equals("ldap") %>'>
				<%@ include file="/html/portlet/enterprise_admin/authentication_ldap.jspf" %>
			</c:when>
			<c:when test='<%= tabs3.equals("cas") %>'>
				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="enabled" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="enabled" defaultValue='<%= PrefsPropsUtil.getBoolean(company.getCompanyId(), PropsUtil.CAS_AUTH_ENABLED, PropsValues.CAS_AUTH_ENABLED) %>' />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="import-cas-users-from-ldap" />

						<liferay-ui:icon-help message="import-cas-users-from-ldap-help" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="importFromLdap" defaultValue='<%= PrefsPropsUtil.getBoolean(company.getCompanyId(), PropsUtil.CAS_IMPORT_FROM_LDAP) %>' />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="login-url" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />loginUrl" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.CAS_LOGIN_URL) %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="logout-url" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />logoutUrl" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.CAS_LOGOUT_URL) %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="server-name" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />serverName" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.CAS_SERVER_NAME) %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="service-url" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />serviceUrl" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.CAS_SERVICE_URL) %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="validate-url" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />validateUrl" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.CAS_VALIDATE_URL) %>" />
					</td>
				</tr>
				</table>

				<br />

				<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveSettings('updateCAS');" />
			</c:when>
			<c:when test='<%= tabs3.equals("ntlm") %>'>
				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="enabled" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="enabled" defaultValue='<%= PrefsPropsUtil.getBoolean(company.getCompanyId(), PropsUtil.NTLM_AUTH_ENABLED) %>' />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="domain-controller" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />domainController" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.NTLM_DOMAIN_CONTROLLER) %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="domain" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />domain" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.NTLM_DOMAIN) %>" />
					</td>
				</tr>
				</table>

				<br />

				<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveSettings('updateNtlm');" />
			</c:when>
			<c:when test='<%= tabs3.equals("open-id") %>'>
				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="enabled" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="enabled" defaultValue='<%= PrefsPropsUtil.getBoolean(company.getCompanyId(), PropsUtil.OPEN_ID_AUTH_ENABLED, PropsValues.OPEN_ID_AUTH_ENABLED) %>' />
					</td>
				</tr>
				</table>

				<br />

				<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveSettings('updateOpenId');" />
			</c:when>
			<c:when test='<%= tabs3.equals("open-sso") %>'>
				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="enabled" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="enabled" defaultValue='<%= PrefsPropsUtil.getBoolean(company.getCompanyId(), PropsUtil.OPEN_SSO_AUTH_ENABLED, PropsValues.OPEN_SSO_AUTH_ENABLED) %>' />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="login-url" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />loginUrl" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.OPEN_SSO_LOGIN_URL, PropsValues.OPEN_SSO_LOGIN_URL) %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="logout-url" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />logoutUrl" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.OPEN_SSO_LOGOUT_URL, PropsValues.OPEN_SSO_LOGOUT_URL) %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="service-url" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />serviceUrl" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.OPEN_SSO_SERVICE_URL, PropsValues.OPEN_SSO_SERVICE_URL) %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="cookie-name" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />subjectCookieName" type="text" value="<%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.OPEN_SSO_SUBJECT_COOKIE_NAME, PropsValues.OPEN_SSO_SUBJECT_COOKIE_NAME) %>" />
					</td>
				</tr>
				</table>

				<br />

				<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveSettings('updateOpenSSO');" />
			</c:when>
			<c:otherwise>
				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="how-do-users-authenticate" />
					</td>
					<td>
						<select name="<portlet:namespace />authType">
							<option <%= company.getAuthType().equals(CompanyImpl.AUTH_TYPE_EA) ? "selected" : "" %> value="<%= CompanyImpl.AUTH_TYPE_EA %>"><liferay-ui:message key="by-email-address" /></option>
							<option <%= company.getAuthType().equals(CompanyImpl.AUTH_TYPE_SN) ? "selected" : "" %> value="<%= CompanyImpl.AUTH_TYPE_SN %>"><liferay-ui:message key="by-screen-name" /></option>
							<option <%= company.getAuthType().equals(CompanyImpl.AUTH_TYPE_ID) ? "selected" : "" %> value="<%= CompanyImpl.AUTH_TYPE_ID %>"><liferay-ui:message key="by-user-id" /></option>
						</select>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<br />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="allow-users-to-automatically-login" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="autoLogin" defaultValue="<%= company.isAutoLogin() %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="allow-users-to-request-forgotten-passwords" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="sendPassword" defaultValue="<%= company.isSendPassword() %>" />
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<br />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="allow-strangers-to-create-accounts" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="strangers" defaultValue="<%= company.isStrangers() %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="allow-strangers-to-create-accounts-with-a-company-email-address" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="strangersWithMx" defaultValue="<%= company.isStrangersWithMx() %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="require-strangers-to-verify-their-email-address" />
					</td>
					<td>
						<liferay-ui:input-checkbox param="strangersVerify" defaultValue="<%= company.isStrangersVerify() %>" />
					</td>
				</tr>
				</table>

				<br />

				<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveSettings('updateSecurity');" />
			</c:otherwise>
		</c:choose>
	</c:when>
	<c:when test='<%= tabs2.equals("default-user-associations") %>'>
		<liferay-ui:message key="enter-the-default-community-names-per-line-that-are-associated-with-newly-created-users" />

		<br /><br />

		<textarea class="lfr-textarea" name="<portlet:namespace />defaultGroupNames"><%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.ADMIN_DEFAULT_GROUP_NAMES) %></textarea>

		<br /><br />

		<liferay-ui:message key="enter-the-default-role-names-per-line-that-are-associated-with-newly-created-users" />

		<br /><br />

		<textarea class="lfr-textarea" name="<portlet:namespace />defaultRoleNames"><%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.ADMIN_DEFAULT_ROLE_NAMES) %></textarea>

		<br /><br />

		<liferay-ui:message key="enter-the-default-user-group-names-per-line-that-are-associated-with-newly-created-users" />

		<br /><br />

		<textarea class="lfr-textarea" name="<portlet:namespace />defaultUserGroupNames"><%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.ADMIN_DEFAULT_USER_GROUP_NAMES) %></textarea>

		<br /><br />

		<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveSettings('updateDefaultGroupsAndRoles');" />
	</c:when>
	<c:when test='<%= tabs2.equals("reserved-screen-names") %>'>
		<liferay-ui:message key="enter-one-screen-name-per-line-to-reserve-the-screen-name" />

		<br /><br />

		<textarea class="lfr-textarea" name="<portlet:namespace />reservedScreenNames"><%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.ADMIN_RESERVED_SCREEN_NAMES) %></textarea>

		<br /><br />

		<liferay-ui:message key="enter-one-user-email-address-per-line-to-reserve-the-user-email-address" />

		<br /><br />

		<textarea class="lfr-textarea" name="<portlet:namespace />reservedEmailAddresses"><%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.ADMIN_RESERVED_EMAIL_ADDRESSES) %></textarea>

		<br /><br />

		<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveSettings('updateReservedUsers');" />
	</c:when>
	<c:when test='<%= tabs2.equals("mail-host-names") %>'>
		<%= LanguageUtil.format(pageContext, "enter-one-mail-host-name-per-line-for-all-additional-mail-host-names-besides-x", company.getMx(), false) %>

		<br /><br />

		<textarea class="lfr-textarea" name="<portlet:namespace />mailHostNames"><%= PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.ADMIN_MAIL_HOST_NAMES) %></textarea>

		<br /><br />

		<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveSettings('updateMailHostNames');" />
	</c:when>
	<c:when test='<%= tabs2.equals("email-notifications") %>'>
		<script type="text/javascript">

			<%
			String emailFromName = ParamUtil.getString(request, "emailFromName", PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.ADMIN_EMAIL_FROM_NAME));
			String emailFromAddress = ParamUtil.getString(request, "emailFromAddress", PrefsPropsUtil.getString(company.getCompanyId(), PropsUtil.ADMIN_EMAIL_FROM_ADDRESS));

			String emailUserAddedSubject = ParamUtil.getString(request, "emailUserAddedSubject", PrefsPropsUtil.getContent(company.getCompanyId(), PropsUtil.ADMIN_EMAIL_USER_ADDED_SUBJECT));
			String emailUserAddedBody = ParamUtil.getString(request, "emailUserAddedBody", PrefsPropsUtil.getContent(company.getCompanyId(), PropsUtil.ADMIN_EMAIL_USER_ADDED_BODY));

			String emailPasswordSentSubject = ParamUtil.getString(request, "emailPasswordSentSubject", PrefsPropsUtil.getContent(company.getCompanyId(), PropsUtil.ADMIN_EMAIL_PASSWORD_SENT_SUBJECT));
			String emailPasswordSentBody = ParamUtil.getString(request, "emailPasswordSentBody", PrefsPropsUtil.getContent(company.getCompanyId(), PropsUtil.ADMIN_EMAIL_PASSWORD_SENT_BODY));

			String editorParam = "";
			String editorContent = "";

			if (tabs3.equals("account-created-notification")) {
				editorParam = "emailUserAddedBody";
				editorContent = emailUserAddedBody;
			}
			else if (tabs3.equals("password-changed-notification")) {
				editorParam = "emailPasswordSentBody";
				editorContent = emailPasswordSentBody;
			}
			%>

			function initEditor() {
				return "<%= UnicodeFormatter.toString(editorContent) %>";
			}

			function <portlet:namespace />saveEmails() {
				document.<portlet:namespace />fm.method = "post";
				document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "updateEmails";

				<c:if test='<%= tabs3.endsWith("-notification") %>'>
					document.<portlet:namespace />fm.<portlet:namespace /><%= editorParam %>.value = window.<portlet:namespace />editor.getHTML();
				</c:if>

				submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_settings" /></portlet:actionURL>");
			}
		</script>

		<liferay-ui:tabs
			names="general,account-created-notification,password-changed-notification"
			param="tabs3"
			url="<%= portletURLString %>"
		/>

		<liferay-ui:error key="emailFromAddress" message="please-enter-a-valid-email-address" />
		<liferay-ui:error key="emailFromName" message="please-enter-a-valid-name" />
		<liferay-ui:error key="emailPasswordSentBody" message="please-enter-a-valid-body" />
		<liferay-ui:error key="emailPasswordSentSubject" message="please-enter-a-valid-subject" />
		<liferay-ui:error key="emailUserAddedBody" message="please-enter-a-valid-body" />
		<liferay-ui:error key="emailUserAddedSubject" message="please-enter-a-valid-subject" />

		<c:choose>
			<c:when test='<%= tabs3.endsWith("-notification") %>'>
				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="enabled" />
					</td>
					<td>
						<c:choose>
							<c:when test='<%= tabs3.equals("account-created-notification") %>'>
								<liferay-ui:input-checkbox param="emailUserAddedEnabled" defaultValue="<%= PrefsPropsUtil.getBoolean(company.getCompanyId(), PropsUtil.ADMIN_EMAIL_USER_ADDED_ENABLED) %>" />
							</c:when>
							<c:when test='<%= tabs3.equals("password-changed-notification") %>'>
								<liferay-ui:input-checkbox param="emailPasswordSentEnabled" defaultValue="<%= PrefsPropsUtil.getBoolean(company.getCompanyId(), PropsUtil.ADMIN_EMAIL_PASSWORD_SENT_ENABLED) %>" />
							</c:when>
						</c:choose>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<br />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="subject" />
					</td>
					<td>
						<c:choose>
							<c:when test='<%= tabs3.equals("account-created-notification") %>'>
								<input class="lfr-input-text" name="<portlet:namespace />emailUserAddedSubject" type="text" value="<%= emailUserAddedSubject %>" />
							</c:when>
							<c:when test='<%= tabs3.equals("password-changed-notification") %>'>
								<input class="lfr-input-text" name="<portlet:namespace />emailPasswordSentSubject" type="text" value="<%= emailPasswordSentSubject %>" />
							</c:when>
						</c:choose>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<br />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="body" />
					</td>
					<td>
						<liferay-ui:input-editor editorImpl="<%= EDITOR_WYSIWYG_IMPL_KEY %>" />

						<input name="<portlet:namespace /><%= editorParam %>" type="hidden" value="" />
					</td>
				</tr>
				</table>

				<br />

				<b><liferay-ui:message key="definition-of-terms" /></b>

				<br /><br />

				<table class="lfr-table">
				<tr>
					<td>
						<b>[$FROM_ADDRESS$]</b>
					</td>
					<td>
						<%= emailFromAddress %>
					</td>
				</tr>
				<tr>
					<td>
						<b>[$FROM_NAME$]</b>
					</td>
					<td>
						<%= emailFromName %>
					</td>
				</tr>
				<tr>
					<td>
						<b>[$PORTAL_URL$]</b>
					</td>
					<td>
						<%= company.getVirtualHost() %>
					</td>
				</tr>

				<c:if test='<%= tabs3.equals("password-changed-notification") %>'>
					<tr>
						<td>
							<b>[$REMOTE_ADDRESS$]</b>
						</td>
						<td>
							The browser's remote address
						</td>
					</tr>
					<tr>
						<td>
							<b>[$REMOTE_HOST$]</b>
						</td>
						<td>
							The browser's remote host
						</td>
					</tr>
				</c:if>

				<tr>
					<td>
						<b>[$TO_ADDRESS$]</b>
					</td>
					<td>
						The address of the email recipient
					</td>
				</tr>
				<tr>
					<td>
						<b>[$TO_NAME$]</b>
					</td>
					<td>
						The name of the email recipient
					</td>
				</tr>

				<c:if test='<%= tabs3.equals("password-changed-notification") %>'>
					<tr>
						<td>
							<b>[$USER_AGENT$]</b>
						</td>
						<td>
							The browser's user agent
						</td>
					</tr>
				</c:if>

				<tr>
					<td>
						<b>[$USER_ID$]</b>
					</td>
					<td>
						The user ID
					</td>
				</tr>
				<tr>
					<td>
						<b>[$USER_PASSWORD$]</b>
					</td>
					<td>
						The user password
					</td>
				</tr>
				</table>
			</c:when>
			<c:otherwise>
				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="name" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />emailFromName" type="text" value="<%= emailFromName %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="address" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />emailFromAddress" type="text" value="<%= emailFromAddress %>" />
					</td>
				</tr>
				</table>
			</c:otherwise>
		</c:choose>

		<br />

		<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveEmails();" />
	</c:when>
	<c:otherwise>
		<%@ include file="/html/portlet/enterprise_admin/company.jspf" %>
	</c:otherwise>
</c:choose>

<%!
public static final String EDITOR_WYSIWYG_IMPL_KEY = "editor.wysiwyg.portal-web.docroot.html.portlet.enterprise_admin.view.jsp";
%>