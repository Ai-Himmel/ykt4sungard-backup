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
String redirect = ParamUtil.getString(request, "redirect");

PasswordPolicy passwordPolicy = (PasswordPolicy)request.getAttribute(WebKeys.PASSWORD_POLICY);

long passwordPolicyId = BeanParamUtil.getLong(passwordPolicy, request, "passwordPolicyId");

boolean defaultPolicy = BeanParamUtil.getBoolean(passwordPolicy, request, "defaultPolicy");
long minAge = BeanParamUtil.getLong(passwordPolicy, request, "minAge");
int historyCount = BeanParamUtil.getInteger(passwordPolicy, request, "historyCount");
long maxAge = BeanParamUtil.getLong(passwordPolicy, request, "maxAge");
long warningTime = BeanParamUtil.getLong(passwordPolicy, request, "warningTime");
long resetFailureCount = BeanParamUtil.getLong(passwordPolicy, request, "resetFailureCount");
boolean requireUnlock = BeanParamUtil.getBoolean(passwordPolicy, request, "requireUnlock");
long lockoutDuration = BeanParamUtil.getLong(passwordPolicy, request, "lockoutDuration");
%>

<liferay-ui:tabs
	names="password-policies"
	backURL="<%= redirect %>"
/>

<form method="post" name="<portlet:namespace />fm" action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_password_policy" /></portlet:actionURL>">
<input name="<portlet:namespace /><%= Constants.CMD %>" value="<%= passwordPolicy == null ? Constants.ADD : Constants.UPDATE %>" type="hidden" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />passwordPolicyId" type="hidden" value="<%= passwordPolicyId %>" />

<liferay-ui:error exception="<%= PasswordPolicyNameException.class %>" message="please-enter-a-valid-name" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="name" />
	</td>
	<td>
		<liferay-ui:input-field disabled="<%= defaultPolicy %>" model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="name" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="description" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="description" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="changeable" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="changeable" />

		<liferay-ui:icon-help message="changeable-help" />
	</td>
</tr>
<tbody id="<portlet:namespace />changeableSettings">
	<tr>
		<td>
			<liferay-ui:message key="change-required" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="changeRequired" />

			<liferay-ui:icon-help message="change-required-help" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="minimum-age" />
		</td>
		<td>
			<select name="<portlet:namespace />minAge">
				<option value="0" <%= (minAge == 0) ? "selected" : "" %>><liferay-ui:message key="none" /></option>

				<%
				for (int i = 0; i < 15; i++) {
				%>

					<option value="<%= _DURATIONS[i] %>" <%= (minAge == _DURATIONS[i]) ? "selected" : "" %>><%= LanguageUtil.getTimeDescription(pageContext, _DURATIONS[i] * 1000) %></option>

				<%
				}
				%>

			</select>

			<liferay-ui:icon-help message="minimum-age-help" />
		</td>
	</tr>
</tbody>
</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

<br /><br />

<liferay-ui:tabs names="password-syntax-checking" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="syntax-checking-enabled" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="checkSyntax" />

		<liferay-ui:icon-help message="syntax-checking-enabled-help" />
	</td>
</tr>
<tbody id="<portlet:namespace />syntaxSettings">
	<tr>
		<td>
			<liferay-ui:message key="allow-dictionary-words" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="allowDictionaryWords" />

			<liferay-ui:icon-help message="allow-dictionary-words-help" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="minimum-length" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="minLength" />

			<liferay-ui:icon-help message="minimum-length-help" />
		</td>
	</tr>
</tbody>
</table>

<br />

<liferay-ui:tabs names="password-history" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="history-enabled" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="history" />

		<liferay-ui:icon-help message="history-enabled-help" />
	</td>
</tr>
<tr id="<portlet:namespace />historySettings">
	<td>
		<liferay-ui:message key="history-count" />
	</td>
	<td>
		<select name="<portlet:namespace />historyCount">

			<%
			for (int i = 2; i < 25; i++) {
			%>

				<option value="<%= i %>" <%= (historyCount == i) ? "selected" : "" %>><%= i %></option>

			<%
			}
			%>

		</select>

		<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="" />

		<liferay-ui:icon-help message="history-count-help" />
	</td>
</tr>
</table>

<br />

<liferay-ui:tabs names="password-expiration" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="expiration-enabled" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="expireable" />

		<liferay-ui:icon-help message="expiration-enabled-help" />
	</td>
</tr>
<tbody id="<portlet:namespace />expirationSettings">
	<tr>
		<td>
			<liferay-ui:message key="maximum-age" />
		</td>
		<td>
			<select name="<portlet:namespace />maxAge">

				<%
				for (int i = 15; i < _DURATIONS.length; i++) {
				%>

					<option value="<%= _DURATIONS[i] %>" <%= (maxAge == _DURATIONS[i]) ? "selected" : "" %>><%= LanguageUtil.getTimeDescription(pageContext, _DURATIONS[i] * 1000) %></option>

				<%
				}
				%>

			</select>

			<liferay-ui:icon-help message="maximum-age-help" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="warning-time" />
		</td>
		<td>
			<select name="<portlet:namespace />warningTime">

				<%
				for (int i = 7; i < 16; i++) {
				%>

					<option value="<%= _DURATIONS[i] %>" <%= (warningTime == _DURATIONS[i]) ? "selected" : "" %>><%= LanguageUtil.getTimeDescription(pageContext, _DURATIONS[i] * 1000) %></option>

				<%
				}
				%>

			</select>

			<liferay-ui:icon-help message="warning-time-help" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="grace-limit" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="graceLimit" />

			<liferay-ui:icon-help message="grace-limit-help" />
		</td>
	</tr>
</tbody>
</table>

<br />

<liferay-ui:tabs names="lockout" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="lockout-enabled" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="lockout" />

		<liferay-ui:icon-help message="lockout-enabled-help" />
	</td>
</tr>
<tbody id="<portlet:namespace />lockoutSettings">
	<tr>
		<td>
			<liferay-ui:message key="maximum-failure" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= PasswordPolicy.class %>" bean="<%= passwordPolicy %>" field="maxFailure" />

			<liferay-ui:icon-help message="maximum-failure-help" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="reset-failure-count" />
		</td>
		<td>
			<select name="<portlet:namespace />resetFailureCount">

				<%
				for (int i = 0; i < 15; i++) {
				%>

					<option value="<%= _DURATIONS[i] %>" <%= (resetFailureCount == _DURATIONS[i]) ? "selected" : "" %>><%= LanguageUtil.getTimeDescription(pageContext, _DURATIONS[i] * 1000) %></option>

				<%
				}
				%>

			</select>

			<liferay-ui:icon-help message="reset-failure-count-help" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="lockout-duration" />
		</td>
		<td>
			<select name="<portlet:namespace />lockoutDuration">

				<option value="0" <%= (requireUnlock) ? "selected" : "" %>><liferay-ui:message key="until-unlocked-by-an-administrator" /></option>

				<%
				for (int i = 0; i < 15; i++) {
				%>

					<option value="<%= _DURATIONS[i] %>" <%= (!requireUnlock && (lockoutDuration == _DURATIONS[i])) ? "selected" : "" %>><%= LanguageUtil.getTimeDescription(pageContext, _DURATIONS[i] * 1000) %></option>

				<%
				}
				%>

			</select>

			<liferay-ui:icon-help message="lockout-duration-help" />
		</td>
	</tr>
</tbody>
</table>

</form>

<script type="text/javascript">
	<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= defaultPolicy ? "description" : "name" %>);
	</c:if>

	Liferay.Util.toggleBoxes('<portlet:namespace />changeableCheckbox', '<portlet:namespace />changeableSettings');
	Liferay.Util.toggleBoxes('<portlet:namespace />checkSyntaxCheckbox', '<portlet:namespace />syntaxSettings');
	Liferay.Util.toggleBoxes('<portlet:namespace />historyCheckbox', '<portlet:namespace />historySettings');
	Liferay.Util.toggleBoxes('<portlet:namespace />expireableCheckbox', '<portlet:namespace />expirationSettings');
	Liferay.Util.toggleBoxes('<portlet:namespace />lockoutCheckbox', '<portlet:namespace />lockoutSettings');
</script>

<%!
private static final long[] _DURATIONS = {300, 600, 1800, 3600, 7200, 10800, 21600, 43200, 86400, 172800, 259200, 345600, 432000, 518400, 604800, 1209600, 1814400, 2419200, 4838400, 7862400, 15724800, 31449600};
%>