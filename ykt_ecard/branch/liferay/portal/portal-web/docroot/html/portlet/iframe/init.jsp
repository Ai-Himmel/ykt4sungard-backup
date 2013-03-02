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

String src = prefs.getValue("src", StringPool.BLANK);
boolean relative = GetterUtil.getBoolean(prefs.getValue("relative", StringPool.BLANK));

boolean auth = GetterUtil.getBoolean(prefs.getValue("auth", StringPool.BLANK));
String authType = prefs.getValue("auth-type", StringPool.BLANK);
String formMethod = prefs.getValue("form-method", StringPool.BLANK);
String userName = prefs.getValue("user-name", StringPool.BLANK);
String password = prefs.getValue("password", StringPool.BLANK);
String hiddenVariables = prefs.getValue("hidden-variables", StringPool.BLANK);

String border = prefs.getValue("border", "0");
String bordercolor = prefs.getValue("bordercolor", "#000000");
String frameborder = prefs.getValue("frameborder", "0");
String heightMaximized = prefs.getValue("height-maximized", "600");
String heightNormal = prefs.getValue("height-normal", "300");
String hspace = prefs.getValue("hspace", "0");
String scrolling = prefs.getValue("scrolling", "auto");
String vspace = prefs.getValue("vspace", "0");
String width = prefs.getValue("width", "100%");
%>