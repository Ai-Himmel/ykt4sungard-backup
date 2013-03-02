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
ShoppingCart cart = ShoppingUtil.getCart(renderRequest);

Map items = cart.getItems();

ShoppingCoupon coupon = cart.getCoupon();

int altShipping = cart.getAltShipping();
String altShippingName = shoppingPrefs.getAlternativeShippingName(altShipping);

ShoppingOrder order = (ShoppingOrder)request.getAttribute(WebKeys.SHOPPING_ORDER);
%>

<script type="text/javascript">
	function <portlet:namespace />continueCheckout() {
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/checkout" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.SAVE %>" />
<input name="<portlet:namespace />billingFirstName" type="hidden" value="<%= order.getBillingFirstName() %>" />
<input name="<portlet:namespace />billingLastName" type="hidden" value="<%= order.getBillingLastName() %>" />
<input name="<portlet:namespace />billingEmailAddress" type="hidden" value="<%= order.getBillingEmailAddress() %>" />
<input name="<portlet:namespace />billingCompany" type="hidden" value="<%= order.getBillingCompany() %>" />
<input name="<portlet:namespace />billingStreet" type="hidden" value="<%= order.getBillingStreet() %>" />
<input name="<portlet:namespace />billingCity" type="hidden" value="<%= order.getBillingCity() %>" />
<input name="<portlet:namespace />billingState" type="hidden" value="<%= order.getBillingState() %>" />
<input name="<portlet:namespace />billingZip" type="hidden" value="<%= order.getBillingZip() %>" />
<input name="<portlet:namespace />billingCountry" type="hidden" value="<%= order.getBillingCountry() %>" />
<input name="<portlet:namespace />billingPhone" type="hidden" value="<%= order.getBillingPhone() %>" />
<input name="<portlet:namespace />shipToBilling" type="hidden" value="<%= order.isShipToBilling() %>" />
<input name="<portlet:namespace />shippingFirstName" type="hidden" value="<%= order.getShippingFirstName() %>" />
<input name="<portlet:namespace />shippingLastName" type="hidden" value="<%= order.getShippingLastName() %>" />
<input name="<portlet:namespace />shippingEmailAddress" type="hidden" value="<%= order.getShippingEmailAddress() %>" />
<input name="<portlet:namespace />shippingCompany" type="hidden" value="<%= order.getShippingCompany() %>" />
<input name="<portlet:namespace />shippingStreet" type="hidden" value="<%= order.getShippingStreet() %>" />
<input name="<portlet:namespace />shippingCity" type="hidden" value="<%= order.getShippingCity() %>" />
<input name="<portlet:namespace />shippingState" type="hidden" value="<%= order.getShippingState() %>" />
<input name="<portlet:namespace />shippingZip" type="hidden" value="<%= order.getShippingZip() %>" />
<input name="<portlet:namespace />shippingCountry" type="hidden" value="<%= order.getShippingCountry() %>" />
<input name="<portlet:namespace />shippingPhone" type="hidden" value="<%= order.getShippingPhone() %>" />
<input name="<portlet:namespace />ccName" type="hidden" value="<%= order.getCcName() %>" />
<input name="<portlet:namespace />ccType" type="hidden" value="<%= order.getCcType() %>" />
<input name="<portlet:namespace />ccNumber" type="hidden" value="<%= order.getCcNumber() %>" />
<input name="<portlet:namespace />ccExpMonth" type="hidden" value="<%= order.getCcExpMonth() %>" />
<input name="<portlet:namespace />ccExpYear" type="hidden" value="<%= order.getCcExpYear() %>" />
<input name="<portlet:namespace />ccVerNumber" type="hidden" value="<%= order.getCcVerNumber() %>" />
<input name="<portlet:namespace />comments" type="hidden" value="<%= order.getComments() %>" />

<liferay-util:include page="/html/portlet/shopping/tabs1.jsp">
	<liferay-util:param name="tabs1" value="cart" />
</liferay-util:include>

<table class="lfr-table">
<tr>
	<td>
		<b><liferay-ui:message key="billing-address" /></b>

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="first-name" />:
			</td>
			<td>
				<%= order.getBillingFirstName() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="last-name" />:
			</td>
			<td>
				<%= order.getBillingLastName() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="email-address" />:
			</td>
			<td>
				<%= order.getBillingEmailAddress() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="company" />:
			</td>
			<td>
				<%= order.getBillingCompany() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="street" />:
			</td>
			<td>
				<%= order.getBillingStreet() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="city" />
			</td>
			<td>
				<%= order.getBillingCity() %>:
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="state" />:
			</td>
			<td>
				<%= order.getBillingState() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="zip" />:
			</td>
			<td>
				<%= order.getBillingZip() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="country" />:
			</td>
			<td>
				<%= order.getBillingCountry() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="phone" />:
			</td>
			<td>
				<%= order.getBillingPhone() %>
			</td>
		</tr>
		</table>
	</td>
	<td valign="top">
		<b><liferay-ui:message key="shipping-address" /></b>

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="first-name" />:
			</td>
			<td>
				<%= order.getShippingFirstName() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="last-name" />:
			</td>
			<td>
				<%= order.getShippingLastName() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="email-address" />:
			</td>
			<td>
				<%= order.getShippingEmailAddress() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="company" />:
			</td>
			<td>
				<%= order.getShippingCompany() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="street" />:
			</td>
			<td>
				<%= order.getShippingStreet() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="city" />
			</td>
			<td>
				<%= order.getShippingCity() %>:
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="state" />:
			</td>
			<td>
				<%= order.getShippingState() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="zip" />:
			</td>
			<td>
				<%= order.getShippingZip() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="country" />:
			</td>
			<td>
				<%= order.getShippingCountry() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="phone" />:
			</td>
			<td>
				<%= order.getShippingPhone() %>
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>

<c:if test="<%= !shoppingPrefs.usePayPal() %>">
	<br />

	<b><liferay-ui:message key="credit-card" /></b>

	<br /><br />

	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="full-name" />:
		</td>
		<td>
			<%= order.getCcName() %>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="type" />:
		</td>
		<td>
			<liferay-ui:message key='<%= "cc_" + order.getCcType() %>' />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="number" />:
		</td>
		<td>
			<%= CreditCard.hide(order.getCcNumber()) %>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="expiration-date" />:
		</td>
		<td>
			<%= CalendarUtil.getMonths(locale)[order.getCcExpMonth()] %>, <%= order.getCcExpYear() %>
		</td>
	</tr>

	<c:if test="<%= Validator.isNotNull(order.getCcVerNumber()) %>">
		<tr>
			<td>
				<liferay-ui:message key="verification-number" />:
			</td>
			<td>
				<%= order.getCcVerNumber() %>
			</td>
		</tr>
	</c:if>

	</table>
</c:if>

<br />

<c:if test="<%= Validator.isNotNull(order.getComments()) %>">
	<b><liferay-ui:message key="comments" /></b>

	<br /><br />

	<%= order.getComments() %>

	<br /><br />
</c:if>

<%
boolean showAvailability = PrefsPropsUtil.getBoolean(company.getCompanyId(), PropsUtil.SHOPPING_ITEM_SHOW_AVAILABILITY);

StringMaker itemIds = new StringMaker();

SearchContainer searchContainer = new SearchContainer();

List headerNames = new ArrayList();

headerNames.add("sku");
headerNames.add("description");

if (showAvailability) {
	headerNames.add("availability");
}

headerNames.add("quantity");
headerNames.add("price");
headerNames.add("total");

searchContainer.setHeaderNames(headerNames);
searchContainer.setHover(false);

Set results = items.entrySet();
int total = items.size();

searchContainer.setTotal(total);

List resultRows = searchContainer.getResultRows();

Iterator itr = results.iterator();

for (int i = 0; itr.hasNext(); i++) {
	Map.Entry entry = (Map.Entry)itr.next();

	ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
	Integer count = (Integer)entry.getValue();

	ShoppingItem item = cartItem.getItem();
	String[] fieldsArray = cartItem.getFieldsArray();

	ShoppingItemField[] itemFields = (ShoppingItemField[])ShoppingItemFieldLocalServiceUtil.getItemFields(item.getItemId()).toArray(new ShoppingItemField[0]);

	for (int j = 0; j < count.intValue(); j++) {
		itemIds.append(cartItem.getCartItemId());
		itemIds.append(",");
	}

	ResultRow row = new ResultRow(item, item.getItemId(), i);

	PortletURL rowURL = renderResponse.createRenderURL();

	rowURL.setWindowState(WindowState.MAXIMIZED);

	rowURL.setParameter("struts_action", "/shopping/view_item");
	rowURL.setParameter("itemId", String.valueOf(item.getItemId()));

	// SKU

	row.addText(item.getSku(), rowURL);

	// Description

	StringMaker sm = new StringMaker();

	sm.append(item.getName());

	if (item.isFields()) {
		sm.append(" (");
		sm.append(StringUtil.replace(StringUtil.merge(cartItem.getFieldsArray(), ", "), "=", ": "));
		sm.append(")");
	}

	row.addText(sm.toString(), rowURL);

	// Availability

	sm = new StringMaker();

	if (ShoppingUtil.isInStock(item, itemFields, fieldsArray, count)) {
		sm.append("<span class=\"portlet-msg-success\">");
		sm.append(LanguageUtil.get(pageContext, "in-stock"));
		sm.append("</span>");
	}
	else {
		sm.append("<span class=\"portlet-msg-error\">");
		sm.append(LanguageUtil.get(pageContext, "out-of-stock"));
		sm.append("</span>");
	}

	row.addText(sm.toString(), rowURL);

	// Quantity

	row.addText(count.toString(), rowURL);

	// Price

	row.addText(currencyFormat.format(ShoppingUtil.calculateActualPrice(item, count.intValue()) / count.intValue()), rowURL);

	// Total

	row.addText(currencyFormat.format(ShoppingUtil.calculateActualPrice(item, count.intValue())), rowURL);

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

<input name="<portlet:namespace />itemIds" type="hidden" value="<%= itemIds %>" />
<input name="<portlet:namespace />couponCodes" type="hidden" value="<%= cart.getCouponCodes() %>" />

<br />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="subtotal" />:
	</td>
	<td>
		<%= currencyFormat.format(ShoppingUtil.calculateActualSubtotal(items)) %>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="tax" />:
	</td>
	<td>
		<%= currencyFormat.format(ShoppingUtil.calculateTax(items, order.getBillingState())) %>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="shipping" /> <%= Validator.isNotNull(altShippingName) ? "(" + altShippingName + ")" : StringPool.BLANK %>:
	</td>
	<td>
		<%= currencyFormat.format(ShoppingUtil.calculateAlternativeShipping(items, altShipping)) %>
	</td>
</tr>

<%
double insurance = ShoppingUtil.calculateInsurance(items);
%>

<c:if test="<%= cart.isInsure() && (insurance > 0) %>">
	<tr>
		<td>
			<liferay-ui:message key="insurance" />:
		</td>
		<td>
			<%= currencyFormat.format(insurance) %>
		</td>
	</tr>
</c:if>

<c:if test="<%= coupon != null %>">
	<tr>
		<td>
			<liferay-ui:message key="coupon-discount" />:
		</td>
		<td>
			<%= currencyFormat.format(ShoppingUtil.calculateCouponDiscount(items, order.getBillingState(), coupon)) %>

			<a href="javascript: var viewCouponWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/shopping/view_coupon" /><portlet:param name="couponId" value="<%= String.valueOf(coupon.getCouponId()) %>" /></portlet:renderURL>', 'viewCoupon', 'directories=no,height=200,location=no,menubar=no,resizable=no,scrollbars=yes,status=no,toolbar=no,width=280'); void(''); viewCouponWindow.focus();">
			(<%= coupon.getCouponId() %>)
			</a>
		</td>
	</tr>
</c:if>

<tr>
	<td>
		<liferay-ui:message key="total" />:
	</td>
	<td>
		<%= currencyFormat.format(ShoppingUtil.calculateTotal(items, order.getBillingState(), coupon, altShipping, cart.isInsure())) %>
	</td>
</tr>
</table>

<br />

<input type="button" value='<%= shoppingPrefs.usePayPal() ? LanguageUtil.get(pageContext, "continue") : LanguageUtil.get(pageContext, "finished") %>' onClick="<portlet:namespace />continueCheckout();" />

</form>