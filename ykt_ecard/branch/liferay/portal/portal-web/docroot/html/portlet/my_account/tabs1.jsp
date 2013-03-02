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

<%@ include file="/html/portlet/my_account/init.jsp" %>

<%
String backURL = ParamUtil.getString(request, "backURL");
%>

<c:if test="<%= user.isLayoutsRequired() %>">
	<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="portletURL">
		<portlet:param name="struts_action" value="/my_account/edit_pages" />
		<portlet:param name="tabs2" value='<%= layout.isPrivateLayout() ? "private" : "public" %>' />
		<portlet:param name="backURL" value="<%= backURL %>" />
		<portlet:param name="groupId" value="<%= String.valueOf(user.getGroup().getGroupId()) %>" />
	</portlet:renderURL>

	<c:if test="<%= portletName.equals(PortletKeys.MY_ACCOUNT) %>">
		<liferay-ui:tabs
			names="profile,pages"
			url0="<%= themeDisplay.getURLMyAccount().toString() %>"
			url1="<%= portletURL %>"
		/>
	</c:if>
</c:if>