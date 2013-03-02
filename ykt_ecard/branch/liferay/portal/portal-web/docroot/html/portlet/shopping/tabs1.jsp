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

<%@ include file="/html/portlet/shopping/init.jsp" %>

<%
String tabs1 = ParamUtil.getString(request, "tabs1", "categories");

String tabs1Names = "categories,cart";

if (!user.isDefaultUser()) {
	tabs1Names += ",orders";
}

if (PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.SHOPPING, ActionKeys.MANAGE_COUPONS)) {
	tabs1Names += ",coupons";
}

// View

PortletURL viewURL = renderResponse.createRenderURL();

viewURL.setWindowState(WindowState.MAXIMIZED);

viewURL.setParameter("struts_action", "/shopping/view");

// Cart

PortletURL cartURL = renderResponse.createRenderURL();

cartURL.setWindowState(WindowState.MAXIMIZED);

cartURL.setParameter("struts_action", "/shopping/cart");

if (!tabs1.equals("cart")) {
	cartURL.setParameter("redirect", currentURL);
}

// Back URL

String backURL = ParamUtil.getString(request, "backURL");
%>

<liferay-ui:tabs
	names="<%= tabs1Names %>"
	url="<%= viewURL.toString() %>"
	url1="<%= cartURL.toString() %>"
	backURL="<%= backURL %>"
/>