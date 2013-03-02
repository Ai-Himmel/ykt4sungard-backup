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
String tabs2 = ParamUtil.getString(request, "tabs2", "display");
String tabs3 = ParamUtil.getString(request, "tabs3", "email-addresses");
String tabs4 = ParamUtil.getString(request, "tabs4", "phone-numbers");

String redirect = ParamUtil.getString(request, "redirect");
String backURL = ParamUtil.getString(request, "backURL", redirect);

if (portletName.equals(PortletKeys.MY_ACCOUNT)) {
	portletDisplay.setURLBack(backURL);
}

User user2 = PortalUtil.getSelectedUser(request);

boolean editable = false;

if (portletName.equals(PortletKeys.ENTERPRISE_ADMIN) || portletName.equals(PortletKeys.ORGANIZATION_ADMIN) || portletName.equals(PortletKeys.MY_ACCOUNT)) {
	if ((user2 == null) || user2.isActive()) {
		editable = true;

		if ((user2 != null) && !UserPermissionUtil.contains(permissionChecker, user2.getUserId(), ActionKeys.UPDATE)) {
			editable = false;
		}
	}
}

Contact contact2 = null;

if (user2 != null) {
	contact2 = user2.getContact();
}

PasswordPolicy passwordPolicy = null;

if (user2 == null) {
	passwordPolicy = PasswordPolicyLocalServiceUtil.getDefaultPasswordPolicy(company.getCompanyId());
}
else {
	passwordPolicy = user2.getPasswordPolicy();
}

String emailAddress = BeanParamUtil.getString(user2, request, "emailAddress");

request.setAttribute("edit_user.jsp-user2", user2);
%>

<script type="text/javascript">
	function <portlet:namespace />saveUser(cmd) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = cmd;

		var redirect = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_user" /></portlet:renderURL>";

		if (document.<portlet:namespace />fm.<portlet:namespace />tabs2) {
			redirect += "&<portlet:namespace />tabs2=" + document.<portlet:namespace />fm.<portlet:namespace />tabs2.value;
		}

		if (document.<portlet:namespace />fm.<portlet:namespace />tabs3) {
			redirect += "&<portlet:namespace />tabs3=" + document.<portlet:namespace />fm.<portlet:namespace />tabs3.value;
		}

		if (document.<portlet:namespace />fm.<portlet:namespace />tabs4) {
			redirect += "&<portlet:namespace />tabs4=" + document.<portlet:namespace />fm.<portlet:namespace />tabs4.value;
		}

		redirect += "&<portlet:namespace />backURL=<%= HttpUtil.encodeURL(backURL) %>&<portlet:namespace />p_u_i_d=";

		document.<portlet:namespace />fm.<portlet:namespace />redirect.value = redirect;
		submitForm(document.<portlet:namespace />fm, "<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_user" /></portlet:actionURL>");
	}
</script>

<form method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
<input name="<portlet:namespace />tabs3" type="hidden" value="<%= tabs3 %>" />
<input name="<portlet:namespace />tabs4" type="hidden" value="<%= tabs4 %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="" />
<input name="<portlet:namespace />backURL" type="hidden" value="<%= backURL %>" />
<input name="<portlet:namespace />p_u_i_d" type="hidden" value='<%= (user2 != null) ? user2.getUserId() : 0 %>' />

<c:if test="<%= portletName.equals(PortletKeys.DIRECTORY) || portletName.equals(PortletKeys.ENTERPRISE_ADMIN) || portletName.equals(PortletKeys.ORGANIZATION_ADMIN) %>">
	<liferay-ui:tabs
		names="user"
		backURL="<%= backURL %>"
	/>
</c:if>

<liferay-util:include page="/html/portlet/my_account/tabs1.jsp">
	<liferay-util:param name="tabs1" value="profile" />
</liferay-util:include>

<%@ include file="/html/portlet/enterprise_admin/edit_user_profile.jspf" %>

<c:if test="<%= user2 != null %>">
	<c:if test="<%= (passwordPolicy != null) && user2.getLockout() %>">
		<liferay-ui:tabs names="lockout" />

		<%@ include file="/html/portlet/enterprise_admin/edit_user_lockout.jspf" %>
	</c:if>

	<c:if test="<%= editable %>">
		<liferay-ui:error exception="<%= UserPasswordException.class %>">

			<%
			UserPasswordException upe = (UserPasswordException)errorException;
			%>

			<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_ALREADY_USED %>">
				<liferay-ui:message key="that-password-has-already-been-used-please-enter-in-a-different-password" />
			</c:if>

			<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_CONTAINS_TRIVIAL_WORDS %>">
				<liferay-ui:message key="that-password-uses-common-words-please-enter-in-a-password-that-is-harder-to-guess-i-e-contains-a-mix-of-numbers-and-letters" />
			</c:if>

			<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_INVALID %>">
				<liferay-ui:message key="that-password-is-invalid-please-enter-in-a-different-password" />
			</c:if>

			<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_LENGTH %>">
				<%= LanguageUtil.format(pageContext, "that-password-is-too-short-or-too-long-please-make-sure-your-password-is-between-x-and-512-characters", String.valueOf(passwordPolicy.getMinLength()), false) %>
			</c:if>

			<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_NOT_CHANGEABLE %>">
				<liferay-ui:message key="your-password-cannot-be-changed" />
			</c:if>

			<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_SAME_AS_CURRENT %>">
				<liferay-ui:message key="your-new-password-cannot-be-the-same-as-your-old-password-please-enter-in-a-different-password" />
			</c:if>

			<c:if test="<%= upe.getType() == UserPasswordException.PASSWORD_TOO_YOUNG %>">
				<%= LanguageUtil.format(pageContext, "you-cannot-change-your-password-yet-please-wait-at-least-x-before-changing-your-password-again", LanguageUtil.getTimeDescription(pageContext, passwordPolicy.getMinAge() * 1000), false) %>
			</c:if>

			<c:if test="<%= upe.getType() == UserPasswordException.PASSWORDS_DO_NOT_MATCH %>">
				<liferay-ui:message key="the-passwords-you-entered-do-not-match-each-other-please-re-enter-your-password" />
			</c:if>
		</liferay-ui:error>
		
		<%
        String tabs2Names = "display,password,regular-roles,community-roles,organization-roles";
        if("1".equals(session.getAttribute("j_status").toString())){
            tabs2Names = "display";
        }
        %>

		<liferay-ui:tabs
			names="<%= tabs2Names %>"
			formName="fm"
			param="tabs2"
			refresh="<%= false %>"
		>
			<liferay-ui:section>
				<%@ include file="/html/portlet/enterprise_admin/edit_user_display.jspf" %>
			</liferay-ui:section>

			<c:if test="<%= (passwordPolicy == null) || passwordPolicy.isChangeable() %>">
				<liferay-ui:section>
					<%@ include file="/html/portlet/enterprise_admin/edit_user_password.jspf" %>
				</liferay-ui:section>
			</c:if>

			<liferay-ui:section>

				<%
				request.setAttribute("edit_user.jsp-sectionRedirectParams", sectionRedirectParams);
				%>

				<liferay-util:include page="/html/portlet/enterprise_admin/edit_user_regular_roles.jsp" />
			</liferay-ui:section>
			<liferay-ui:section>

				<%
				request.setAttribute("edit_user.jsp-sectionRedirectParams", sectionRedirectParams);
				%>

				<liferay-util:include page="/html/portlet/enterprise_admin/edit_user_community_roles.jsp" />
			</liferay-ui:section>
			<liferay-ui:section>

				<%
				request.setAttribute("edit_user.jsp-sectionRedirectParams", sectionRedirectParams);
				%>

				<liferay-util:include page="/html/portlet/enterprise_admin/edit_user_organization_roles.jsp" />
			</liferay-ui:section>
		</liferay-ui:tabs>
	</c:if>

	<liferay-ui:tabs
		names="email-addresses,addresses,websites"
		formName="fm"
		param="tabs3"
		refresh="<%= false %>"
	>
		<liferay-ui:section>
			<liferay-util:include page="/html/portlet/enterprise_admin/email_address_iterator.jsp">
				<liferay-util:param name="editable" value="<%= String.valueOf(editable) %>" />
				<liferay-util:param name="redirect" value="<%= currentURL + sectionRedirectParams %>" />
				<liferay-util:param name="className" value="<%= Contact.class.getName() %>" />
				<liferay-util:param name="classPK" value="<%= String.valueOf(contact2.getContactId()) %>" />
			</liferay-util:include>
		</liferay-ui:section>
		<liferay-ui:section>
			<liferay-util:include page="/html/portlet/enterprise_admin/address_iterator.jsp">
				<liferay-util:param name="editable" value="<%= String.valueOf(editable) %>" />
				<liferay-util:param name="redirect" value="<%= currentURL + sectionRedirectParams %>" />
				<liferay-util:param name="className" value="<%= Contact.class.getName() %>" />
				<liferay-util:param name="classPK" value="<%= String.valueOf(contact2.getContactId()) %>" />
				<liferay-util:param name="organizationIds" value="<%= StringUtil.merge(organizationIdsArray) %>" />
			</liferay-util:include>
		</liferay-ui:section>
		<liferay-ui:section>
			<liferay-util:include page="/html/portlet/enterprise_admin/website_iterator.jsp">
				<liferay-util:param name="editable" value="<%= String.valueOf(editable) %>" />
				<liferay-util:param name="redirect" value="<%= currentURL + sectionRedirectParams %>" />
				<liferay-util:param name="className" value="<%= Contact.class.getName() %>" />
				<liferay-util:param name="classPK" value="<%= String.valueOf(contact2.getContactId()) %>" />
			</liferay-util:include>
		</liferay-ui:section>
	</liferay-ui:tabs>

	<liferay-ui:error exception="<%= UserSmsException.class %>" message="please-enter-a-sms-id-that-is-a-valid-email-address" />

	<liferay-ui:tabs
		names="phone-numbers,sms-messenger-id,instant-messenger-ids"
		formName="fm"
		param="tabs4"
		refresh="<%= false %>"
	>
		<liferay-ui:section>
			<liferay-util:include page="/html/portlet/enterprise_admin/phone_iterator.jsp">
				<liferay-util:param name="editable" value="<%= String.valueOf(editable) %>" />
				<liferay-util:param name="redirect" value="<%= currentURL + sectionRedirectParams %>" />
				<liferay-util:param name="className" value="<%= Contact.class.getName() %>" />
				<liferay-util:param name="classPK" value="<%= String.valueOf(contact2.getContactId()) %>" />
				<liferay-util:param name="organizationIds" value="<%= StringUtil.merge(organizationIdsArray) %>" />
			</liferay-util:include>
		</liferay-ui:section>
		<liferay-ui:section>
			<%@ include file="/html/portlet/enterprise_admin/edit_user_sms.jspf" %>
		</liferay-ui:section>
		<liferay-ui:section>
			<%@ include file="/html/portlet/enterprise_admin/edit_user_im.jspf" %>
		</liferay-ui:section>
	</liferay-ui:tabs>

	<%@ include file="/html/portlet/enterprise_admin/edit_user_comments.jspf" %>

	<%
	PortalUtil.setPageSubtitle(user2.getFullName(), request);
	%>

</c:if>

</form>