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
	<%
	UserSearch searchContainer = (UserSearch)request.getAttribute("liferay-ui:search:searchContainer");

	String redirect = searchContainer.getIteratorURL().toString();

	UserSearchTerms searchTerms = (UserSearchTerms)searchContainer.getSearchTerms();

	ResultRow row = (ResultRow)request.getAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW);

	User user2 = (User)row.getObject();

	long userId = user2.getUserId();
	%>

	<liferay-ui:icon-menu>

			<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="editUserURL">
				<portlet:param name="struts_action" value="/ext/shop_admin_edit_user" />
				<portlet:param name="redirect" value="<%= redirect %>" />
				<portlet:param name="p_u_i_d" value="<%= String.valueOf(userId) %>" />
			</portlet:renderURL>

			<liferay-ui:icon image="edit" url="<%= editUserURL %>" />

	</liferay-ui:icon-menu>