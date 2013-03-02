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

<%@ include file="/html/portlet/init.jsp" %>

<%
PortletPreferences prefs = renderRequest.getPreferences();

String portletResource = ParamUtil.getString(request, "portletResource");

if (Validator.isNotNull(portletResource)) {
	prefs = PortletPreferencesFactoryUtil.getPortletSetup(request, portletResource, true, true);
}

String initUrl = prefs.getValue("initUrl", StringPool.BLANK);
String scope = prefs.getValue("scope", StringPool.BLANK);
String proxyHost = prefs.getValue("proxyHost", StringPool.BLANK);
String proxyPort = prefs.getValue("proxyPort", StringPool.BLANK);
String proxyAuthentication = prefs.getValue("proxyAuthentication", StringPool.BLANK);
String proxyAuthenticationUsername = prefs.getValue("proxyAuthenticationUsername", StringPool.BLANK);
String proxyAuthenticationPassword = prefs.getValue("proxyAuthenticationPassword", StringPool.BLANK);
String proxyAuthenticationHost = prefs.getValue("proxyAuthenticationHost", StringPool.BLANK);
String proxyAuthenticationDomain = prefs.getValue("proxyAuthenticationDomain", StringPool.BLANK);
String stylesheet = prefs.getValue("stylesheet", StringPool.BLANK);
%>