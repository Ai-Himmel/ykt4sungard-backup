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

<%@ include file="/html/portlet/web_proxy/init.jsp" %>

<form action="<liferay-portlet:actionURL portletConfiguration="true" />" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="url" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />initUrl" value="<%= initUrl %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="scope" /> (<liferay-ui:message key="regex" />)
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />scope" value="<%= scope %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="proxy-host" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />proxyHost" value="<%= proxyHost %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="proxy-port" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />proxyPort" value="<%= proxyPort %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="proxy-authentication" />
	</td>
	<td>
		<select name="<portlet:namespace />proxyAuthentication">
			<option <%= proxyAuthentication.equals("none") ? "selected" : "" %> value="none"><liferay-ui:message key="none" /></option>
			<option <%= proxyAuthentication.equals("basic") ? "selected" : "" %> value="basic"><liferay-ui:message key="basic" /></option>
			<option <%= proxyAuthentication.equals("ntlm") ? "selected" : "" %> value="ntlm"><liferay-ui:message key="ntlm" /></option>
		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="proxy-authentication-username" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />proxyAuthenticationUsername" value="<%= proxyAuthenticationUsername %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="proxy-authentication-password" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />proxyAuthenticationPassword" value="<%= proxyAuthenticationPassword %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="proxy-authentication-host" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />proxyAuthenticationHost" value="<%= proxyAuthenticationHost %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="proxy-authentication-domain" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />proxyAuthenticationDomain" value="<%= proxyAuthenticationDomain %>" />
	</td>
</tr>
<tr>
	<td colspan="3">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="stylesheet" />
	</td>
	<td>
		<textarea class="lfr-textarea" name="<portlet:namespace />stylesheet" wrap="soft" onKeyDown="Liferay.Util.checkTab(this); Liferay.Util.disableEsc();"><%= stylesheet %></textarea>
	</td>
</tr>
</table>

<br />

<input type="button" value="<liferay-ui:message key="save" />" onClick="submitForm(document.<portlet:namespace />fm);" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />initUrl);
	</script>
</c:if>