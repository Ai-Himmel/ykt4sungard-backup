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
CouponSearch searchContainer = (CouponSearch)request.getAttribute("liferay-ui:search:searchContainer");

CouponDisplayTerms displayTerms = (CouponDisplayTerms)searchContainer.getDisplayTerms();
%>

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="code" />
	</td>
	<td>
		<liferay-ui:message key="discount-type" />
	</td>
	<td>
		<liferay-ui:message key="active" />
	</td>
</tr>
<tr>
	<td>
		<input name="<portlet:namespace /><%= displayTerms.CODE %>" size="20" type="text" value="<%= Html.escape(displayTerms.getCode()) %>" />
	</td>
	<td>
		<select name="<%= displayTerms.DISCOUNT_TYPE %>">
			<option value=""></option>

			<%
			for (int i = 0; i < ShoppingCouponImpl.DISCOUNT_TYPES.length; i++) {
			%>

				<option <%= displayTerms.getDiscountType().equals(ShoppingCouponImpl.DISCOUNT_TYPES[i]) ? "selected" : "" %> value="<%= ShoppingCouponImpl.DISCOUNT_TYPES[i] %>"><%= LanguageUtil.get(pageContext, ShoppingCouponImpl.DISCOUNT_TYPES[i]) %></option>

			<%
			}
			%>

		</select>
	</td>
	<td>
		<select name="<portlet:namespace /><%= displayTerms.ACTIVE %>">
			<option <%= displayTerms.isActive() ? "selected" : "" %> value="1"><liferay-ui:message key="yes" /></option>
			<option <%= !displayTerms.isActive() ? "selected" : "" %> value="0"><liferay-ui:message key="no" /></option>
		</select>
	</td>
</tr>
</table>

<br />

<div>
	<select name="<portlet:namespace /><%= displayTerms.AND_OPERATOR %>">
		<option <%= displayTerms.isAndOperator() ? "selected" : "" %> value="1"><liferay-ui:message key="and" /></option>
		<option <%= !displayTerms.isAndOperator() ? "selected" : "" %> value="0"><liferay-ui:message key="or" /></option>
	</select>

	<input type="submit" value="<liferay-ui:message key="search-coupons" />" />

	<input type="button" value="<liferay-ui:message key="add-coupon" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/edit_coupon" /><portlet:param name="redirect" value="<%= currentURL %>" /></portlet:renderURL>';" />
</div>