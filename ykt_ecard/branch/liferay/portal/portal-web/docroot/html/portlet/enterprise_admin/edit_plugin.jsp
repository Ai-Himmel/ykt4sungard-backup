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

String moduleId = ParamUtil.getString(request, "moduleId");
String pluginId = ParamUtil.getString(request, "pluginId");
String pluginType = ParamUtil.getString(request, "pluginType");

PluginSetting pluginSetting = PluginSettingLocalServiceUtil.getPluginSetting(company.getCompanyId(), pluginId, pluginType);

boolean active = pluginSetting.isActive();
String[] rolesArray = pluginSetting.getRolesArray();

if (pluginType.equals(PortletImpl.PLUGIN_TYPE)) {
	String portletId = pluginId;

	Portlet portlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), portletId);

	active = portlet.isActive();
	rolesArray = portlet.getRolesArray();
}
%>

<script type="text/javascript">
	function <portlet:namespace />savePlugin() {
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_plugin" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />savePlugin(); return false;">
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />pluginId" type="hidden" value="<%= pluginId %>" />
<input name="<portlet:namespace />pluginType" type="hidden" value="<%= pluginType %>" />

<liferay-ui:tabs
	names="plugin"
	backURL="<%= redirect %>"
/>

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="module-id" />
	</td>
	<td>
		<%= moduleId %>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="plugin-id" />
	</td>
	<td>
		<%= pluginId %>
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="active" />
	</td>
	<td>
		<liferay-ui:input-checkbox param="active" defaultValue="<%= active %>" />
	</td>
</tr>
</table>

<br />

<liferay-ui:message key="enter-one-role-name-per-line-a-user-must-belong-to-one-of-these-roles-in-order-to-add-this-plugin-to-a-page" />

<br /><br />

<textarea class="lfr-textarea" name="<portlet:namespace />roles"><%= StringUtil.merge(rolesArray, "\n") %></textarea>

<br /><br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>