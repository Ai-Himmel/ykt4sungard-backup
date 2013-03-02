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
<%@ include file="/html/extportlet/shopquery/init.jsp" %>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>
<%
PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/ext/extshopbindusersview");
portletURL.setParameter("tabs1", tabs1);

pageContext.setAttribute("portletURL", portletURL);

String portletURLString = portletURL.toString();

request.setAttribute("view.jsp-portletURL", portletURL);
request.setAttribute("view.jsp-portletURLString", portletURLString);
%>

<form action="<%= portletURLString %>" method="get" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<liferay-portlet:renderURLParams varImpl="portletURL" />
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />tabs1" type="hidden" value="<%= tabs1 %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= portletURLString %>" />

<c:if test="<%= SessionErrors.contains(request,EcardConstants.USER_NOT_SELECTEDE) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="user_not_selected" />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.SHOP_BIND_SUCCESS) %>">
		<font class="portlet-msg-success"> <liferay-ui:message
				key="shop_bind_success" /> </font>
	</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.SHOP_BIND_FAILUE) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="shop_bind_failue" />
 </font>
</c:if>

<liferay-util:include page="/html/extportlet/shopquery/shopbind/tabs1.jsp" />

<c:choose>
    <c:when test='<%= tabs1.equals("users") %>'>
        <liferay-util:include page="/html/extportlet/shopquery/shopbind/view_users.jsp" />
    </c:when>	

</c:choose>

</form>

<%!
private static final long[] _DURATIONS = {300, 600, 1800, 3600, 7200, 10800, 21600};
%>