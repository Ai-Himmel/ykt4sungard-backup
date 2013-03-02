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

<%@ include file="/html/portlet/portlet_configuration/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

String portletResource = ParamUtil.getString(request, "portletResource");

PortletPreferences portletSetup = PortletPreferencesFactoryUtil.getPortletSetup(request, portletResource, true, true);

Portlet portlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), portletResource);

Set allPortletModes = portlet.getAllPortletModes();

PortletURL supportedClientsRedirect = new PortletURLImpl(request, PortletKeys.PORTLET_CONFIGURATION, plid.longValue(), false);

supportedClientsRedirect.setWindowState(WindowState.MAXIMIZED);
supportedClientsRedirect.setPortletMode(PortletMode.VIEW);

supportedClientsRedirect.setParameter("struts_action", "/portlet_configuration/edit_supported_clients");
supportedClientsRedirect.setParameter("redirect", redirect);
supportedClientsRedirect.setParameter("portletResource", portletResource);
%>

<liferay-util:include page="/html/portlet/portlet_configuration/tabs1.jsp">
	<liferay-util:param name="tabs1" value="supported-clients" />
</liferay-util:include>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/portlet_configuration/edit_supported_clients" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />supportedClientsRedirect" type="hidden" value="<%= supportedClientsRedirect %>" />
<input name="<portlet:namespace />portletResource" type="hidden" value="<%= portletResource %>" />

<%
Iterator itr = allPortletModes.iterator();

while (itr.hasNext()) {
	String curPortletMode = (String)itr.next();

	String mobileDevicesParam = "portlet-setup-supported-clients-mobile-devices-" + curPortletMode;
	boolean mobileDevicesDefault = portlet.hasPortletMode(ContentTypes.XHTML_MP, new PortletMode(curPortletMode));

	boolean mobileDevices = GetterUtil.getBoolean(portletSetup.getValue(mobileDevicesParam, String.valueOf(mobileDevicesDefault)));
%>

	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="portlet-mode" />
		</td>
		<td>
			<b><liferay-ui:message key="<%= curPortletMode %>" /></b>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="regular-browsers" />
		</td>
		<td>
			<liferay-ui:input-checkbox param='<%= "regularBrowsersEnabled" + curPortletMode %>' defaultValue="<%= true %>" disabled="<%= true %>" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="mobile-devices" />
		</td>
		<td>
			<liferay-ui:input-checkbox param="<%= mobileDevicesParam %>" defaultValue="<%= mobileDevices %>" />
		</td>
	</tr>
	</table>

	<c:if test="<%= itr.hasNext() %>">
		<br />
	</c:if>

<%
}
%>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>