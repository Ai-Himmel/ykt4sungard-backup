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
String orderId = ParamUtil.getString(request, "orderId");

try {
	ShoppingCart cart = ShoppingUtil.getCart(renderRequest);

	ShoppingCartLocalServiceUtil.updateCart(cart.getUserId(), cart.getGroupId(), StringPool.BLANK, StringPool.BLANK, 0, false);
}
catch (Exception e) {
}
%>

<liferay-util:include page="/html/portlet/shopping/tabs1.jsp">
	<liferay-util:param name="tabs1" value="cart" />
</liferay-util:include>

<span class="portlet-msg-success">
<liferay-ui:message key="thank-you-for-your-purchase" />
</span>

<liferay-ui:message key="your-order-number-is" /> <b><%= orderId %></b>. <liferay-ui:message key="you-will-receive-an-email-shortly-with-your-order-summary-and-further-details" />