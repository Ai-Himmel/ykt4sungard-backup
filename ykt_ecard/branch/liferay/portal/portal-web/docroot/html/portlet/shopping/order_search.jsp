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
OrderSearch searchContainer = (OrderSearch)request.getAttribute("liferay-ui:search:searchContainer");

OrderDisplayTerms displayTerms = (OrderDisplayTerms)searchContainer.getDisplayTerms();
%>

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="number" />
	</td>
	<td>
		<liferay-ui:message key="status" />
	</td>
	<td>
		<liferay-ui:message key="first-name" />
	</td>
	<td>
		<liferay-ui:message key="last-name" />
	</td>
	<td>
		<liferay-ui:message key="email-address" />
	</td>
</tr>
<tr>
	<td>
		<input name="<portlet:namespace /><%= displayTerms.NUMBER %>" size="20" type="text" value="<%= Html.escape(displayTerms.getNumber()) %>" />
	</td>
	<td>
		<select name="<%= displayTerms.STATUS %>">
			<option value=""></option>

			<%
			for (int i = 0; i < ShoppingOrderImpl.STATUSES.length; i++) {
			%>

				<option <%= displayTerms.getStatus().equals(ShoppingOrderImpl.STATUSES[i]) ? "selected" : "" %> value="<%= ShoppingOrderImpl.STATUSES[i] %>"><%= LanguageUtil.get(pageContext, ShoppingOrderImpl.STATUSES[i]) %></option>

			<%
			}
			%>

		</select>
	</td>
	<td>
		<input name="<portlet:namespace /><%= displayTerms.FIRST_NAME %>" size="20" type="text" value="<%= Html.escape(displayTerms.getFirstName()) %>" />
	</td>
	<td>
		<input name="<portlet:namespace /><%= displayTerms.LAST_NAME %>" size="20" type="text" value="<%= Html.escape(displayTerms.getLastName()) %>" />
	</td>
	<td>
		<input name="<portlet:namespace /><%= displayTerms.EMAIL_ADDRESS %>" size="20" type="text" value="<%= Html.escape(displayTerms.getEmailAddress()) %>" />
	</td>
</tr>
</table>

<br />

<div>
	<select name="<portlet:namespace /><%= displayTerms.AND_OPERATOR %>">
		<option <%= displayTerms.isAndOperator() ? "selected" : "" %> value="1"><liferay-ui:message key="and" /></option>
		<option <%= !displayTerms.isAndOperator() ? "selected" : "" %> value="0"><liferay-ui:message key="or" /></option>
	</select>

	<input type="submit" value="<liferay-ui:message key="search-orders" />" />
</div>