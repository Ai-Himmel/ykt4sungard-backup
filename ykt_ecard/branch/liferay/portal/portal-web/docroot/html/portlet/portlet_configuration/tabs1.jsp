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
String returnToFullPageURL = ParamUtil.getString(request, "returnToFullPageURL");

String portletResource = ParamUtil.getString(request, "portletResource");
String previewWidth = ParamUtil.getString(request, "previewWidth");

Portlet portlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), portletResource);

// Configuration

PortletURL configurationURL = renderResponse.createRenderURL();

configurationURL.setWindowState(WindowState.MAXIMIZED);

configurationURL.setParameter("struts_action", "/portlet_configuration/edit_configuration");
configurationURL.setParameter("redirect", redirect);
configurationURL.setParameter("returnToFullPageURL", returnToFullPageURL);
configurationURL.setParameter("portletResource", portletResource);
configurationURL.setParameter("previewWidth", previewWidth);

// Supported clients

PortletURL supportedClientsURL = renderResponse.createRenderURL();

supportedClientsURL.setWindowState(WindowState.MAXIMIZED);

supportedClientsURL.setParameter("struts_action", "/portlet_configuration/edit_supported_clients");
supportedClientsURL.setParameter("redirect", redirect);
supportedClientsURL.setParameter("returnToFullPageURL", returnToFullPageURL);
supportedClientsURL.setParameter("portletResource", portletResource);
configurationURL.setParameter("previewWidth", previewWidth);

// Permissions

PortletURL permissionsURL = renderResponse.createRenderURL();

permissionsURL.setWindowState(WindowState.MAXIMIZED);

permissionsURL.setParameter("struts_action", "/portlet_configuration/edit_permissions");
permissionsURL.setParameter("redirect", redirect);
permissionsURL.setParameter("returnToFullPageURL", returnToFullPageURL);
permissionsURL.setParameter("portletResource", portletResource);
permissionsURL.setParameter("resourcePrimKey", PortletPermissionUtil.getPrimaryKey(layout.getPlid(), portletResource));
permissionsURL.setParameter("previewWidth", previewWidth);

// LAR

PortletURL larURL = renderResponse.createRenderURL();

larURL.setWindowState(WindowState.MAXIMIZED);

larURL.setParameter("struts_action", "/portlet_configuration/export_import");
larURL.setParameter("redirect", redirect);
larURL.setParameter("returnToFullPageURL", returnToFullPageURL);
larURL.setParameter("portletResource", portletResource);

int pos = 0;

String tabsNames = StringPool.BLANK;

if (Validator.isNotNull(portlet.getConfigurationActionClass())) {
	tabsNames += ",setup";

	request.setAttribute("liferay-ui:tabs:url" + pos++, configurationURL.toString());
}

if (portlet.hasMultipleMimeTypes()) {
	tabsNames += ",supported-clients";

	request.setAttribute("liferay-ui:tabs:url" + pos++, supportedClientsURL.toString());
}

tabsNames += ",permissions";

request.setAttribute("liferay-ui:tabs:url" + pos++, permissionsURL.toString());

tabsNames += ",export-import";

request.setAttribute("liferay-ui:tabs:url" + pos++, larURL.toString());

if (tabsNames.startsWith(",")) {
	tabsNames = tabsNames.substring(1);
}
%>

<liferay-ui:tabs names="<%= tabsNames %>" />