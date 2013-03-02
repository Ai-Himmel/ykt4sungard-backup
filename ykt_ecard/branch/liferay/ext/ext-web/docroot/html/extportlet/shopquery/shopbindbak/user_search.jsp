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
String strutsAction = ParamUtil.getString(request, "struts_action");

UserSearch searchContainer = (UserSearch)request.getAttribute("liferay-ui:search:searchContainer");

UserDisplayTerms displayTerms = (UserDisplayTerms)searchContainer.getDisplayTerms();
%>

<liferay-ui:search-toggle
	id="toggle_id_shop_bind_user_search"
	displayTerms="<%= displayTerms %>"
>
	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="first-name" />
		</td>
	</tr>
	<tr>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.FIRST_NAME %>" size="20" type="text" value="<%= Html.escape(displayTerms.getFirstName()) %>" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="screen-name" />
		</td>
		<td>
			<liferay-ui:message key="email-address" />
		</td>

	</tr>
	<tr>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.SCREEN_NAME %>" size="20" type="text" value="<%= Html.escape(displayTerms.getScreenName()) %>" />
		</td>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.EMAIL_ADDRESS %>" size="20" type="text" value="<%= Html.escape(displayTerms.getEmailAddress()) %>" />
		</td>

	</tr>
	</table>
</liferay-ui:search-toggle>

<br />

<div>
	<input type="submit" value="<liferay-ui:message key="search-users" />" />

</div>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= displayTerms.FIRST_NAME %>);
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= displayTerms.KEYWORDS %>);
	</script>
</c:if>