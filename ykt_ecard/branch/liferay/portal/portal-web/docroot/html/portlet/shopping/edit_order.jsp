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
String redirect = ParamUtil.getString(request, "redirect");

ShoppingOrder order = (ShoppingOrder)request.getAttribute(WebKeys.SHOPPING_ORDER);

long orderId = BeanParamUtil.getLong(order, request, "orderId");
%>

<script type="text/javascript">
	function <portlet:namespace />deleteOrder() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.DELETE %>";
		document.<portlet:namespace />fm.<portlet:namespace />redirect.value = "<%= redirect %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />saveOrder() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />sendEmail(emailType) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "sendEmail";
		document.<portlet:namespace />fm.<portlet:namespace />emailType.value = emailType;
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/edit_order" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= currentURL %>" />
<input name="<portlet:namespace />orderId" type="hidden" value="<%= orderId %>" />
<input name="<portlet:namespace />number" type="hidden" value="<%= order.getNumber() %>" />
<input name="<portlet:namespace />emailType" type="hidden" value="" />
<input name="<portlet:namespace />deleteOrderIds" type="hidden" value="<%= orderId %>" />

<c:choose>
	<c:when test="<%= windowState.equals(LiferayWindowState.POP_UP) %>">
		<a href="<%= themeDisplay.getURLHome() %>"><img src="<%= themeDisplay.getCompanyLogo() %>" /></a>

		<br /><br />

		<span style="font-size: small;">
		<b><liferay-ui:message key="invoice" /></b>
		</span>

		<br /><br />
	</c:when>
	<c:otherwise>
		<liferay-ui:tabs
			names="order"
			backURL="<%= redirect %>"
		/>
	</c:otherwise>
</c:choose>

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="order" /> #:
	</td>
	<td>
		<b><%= order.getOrderId() %></b>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="order-date" />:
	</td>
	<td>
		<%= dateFormatDateTime.format(order.getCreateDate()) %>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="last-modified" />:
	</td>
	<td>
		<%= dateFormatDateTime.format(order.getModifiedDate()) %>
	</td>
</tr>
</table>

<br />

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

<br />

<c:choose>
	<c:when test="<%= shoppingPrefs.usePayPal() %>">
		<b>PayPal</b>

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="status" />:
			</td>
			<td>
				<select name="<portlet:namespace />ppPaymentStatus">

					<%
					for (int i = 0; i < ShoppingOrderImpl.STATUSES.length; i++) {
					%>

						<option <%= ShoppingUtil.getPpPaymentStatus(ShoppingOrderImpl.STATUSES[i]).equals(order.getPpPaymentStatus()) ? "selected" : "" %> value="<%= ShoppingOrderImpl.STATUSES[i] %>"><%= LanguageUtil.get(pageContext, ShoppingOrderImpl.STATUSES[i]) %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="transaction-id" />:
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="ppTxnId" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="payment-gross" />:
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="ppPaymentGross" defaultValue="<%= currencyFormat.format(order.getPpPaymentGross()) %>" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="receiver-email-address" />:
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="ppReceiverEmail" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="payer-email-address" />:
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="ppPayerEmail" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="paypal-order" />:
			</td>
			<td>

				<%
				String payPalLinkOpen = "<a href=\"" + ShoppingUtil.getPayPalRedirectURL(shoppingPrefs, order, ShoppingUtil.calculateTotal(order), ShoppingUtil.getPayPalReturnURL(renderResponse.createActionURL(), order), ShoppingUtil.getPayPalNotifyURL(themeDisplay)) + "\"><b><u>";
				String payPalLinkClose = "</u></b></a>";
				%>

				<%= LanguageUtil.format(pageContext, "please-complete-your-order", new Object[] {payPalLinkOpen, payPalLinkClose}, false) %>
			</td>
		</tr>
		</table>
	</c:when>
	<c:otherwise>
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
	</c:otherwise>
</c:choose>

<br />

<c:if test="<%= Validator.isNotNull(order.getComments()) %>">
	<b><liferay-ui:message key="comments" /></b>

	<br /><br />

	<%= order.getComments() %>

	<br /><br />
</c:if>

<%
StringMaker itemIds = new StringMaker();

SearchContainer searchContainer = new SearchContainer();

List headerNames = new ArrayList();

headerNames.add("sku");
headerNames.add("description");
headerNames.add("quantity");
headerNames.add("price");
headerNames.add("total");

searchContainer.setHeaderNames(headerNames);
searchContainer.setHover(false);

List results = ShoppingOrderItemLocalServiceUtil.getOrderItems(order.getOrderId());
int total = results.size();

searchContainer.setTotal(total);

List resultRows = searchContainer.getResultRows();

Iterator itr = results.iterator();

for (int i = 0; itr.hasNext(); i++) {
	ShoppingOrderItem orderItem = (ShoppingOrderItem)itr.next();

	ShoppingItem item = null;

	try {
		item = ShoppingItemLocalServiceUtil.getItem(ShoppingUtil.getItemId(orderItem.getItemId()));
	}
	catch (Exception e) {
	}

	String[] fieldsArray = StringUtil.split(ShoppingUtil.getItemFields(orderItem.getItemId()), "&");

	int quantity = orderItem.getQuantity();

	ResultRow row = new ResultRow(item, orderItem.getOrderItemId(), i);

	PortletURL rowURL = null;

	if (item != null) {
		rowURL = renderResponse.createRenderURL();

		rowURL.setWindowState(WindowState.MAXIMIZED);

		rowURL.setParameter("struts_action", "/shopping/view_item");
		rowURL.setParameter("itemId", String.valueOf(item.getItemId()));
	}

	// SKU

	row.addText(orderItem.getSku(), rowURL);

	// Description

	StringMaker sm = new StringMaker();

	sm.append(orderItem.getName());

	if (fieldsArray.length > 0) {
		sm.append(" (");
		sm.append(StringUtil.replace(StringUtil.merge(fieldsArray, ", "), "=", ": "));
		sm.append(")");
	}

	row.addText(sm.toString(), rowURL);

	// Quantity

	row.addText(String.valueOf(quantity), rowURL);

	// Price

	row.addText(currencyFormat.format(orderItem.getPrice()), rowURL);

	// Total

	row.addText(currencyFormat.format(orderItem.getPrice() * quantity), rowURL);

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

<br />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="subtotal" />:
	</td>
	<td>
		<%= currencyFormat.format(ShoppingUtil.calculateActualSubtotal(results)) %>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="tax" />:
	</td>
	<td>
		<%= currencyFormat.format(order.getTax()) %>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="shipping" /> <%= Validator.isNotNull(order.getAltShipping()) ? "(" + order.getAltShipping() + ")" : StringPool.BLANK %>
	</td>
	<td>
		<%= currencyFormat.format(order.getShipping()) %>
	</td>
</tr>

<c:if test="<%= order.isInsure() %>">
	<tr>
		<td>
			<liferay-ui:message key="insurance" />:
		</td>
		<td>
			<%= currencyFormat.format(order.getInsurance()) %>
		</td>
	</tr>
</c:if>

<c:if test="<%= Validator.isNotNull(order.getCouponCodes()) %>">
	<tr>
		<td>
			<liferay-ui:message key="coupon-discount" />:
		</td>
		<td>
			<%= currencyFormat.format(order.getCouponDiscount()) %>

			<a href="javascript: var viewCouponWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/shopping/view_coupon" /><portlet:param name="code" value="<%= order.getCouponCodes() %>" /></portlet:renderURL>', 'viewCoupon', 'directories=no,height=200,location=no,menubar=no,resizable=no,scrollbars=yes,status=no,toolbar=no,width=280'); void(''); viewCouponWindow.focus();">
			(<%= order.getCouponCodes() %>)
			</a>
		</td>
	</tr>
</c:if>

<tr>
	<td>
		<liferay-ui:message key="total" />:
	</td>
	<td>
		<%= currencyFormat.format(ShoppingUtil.calculateTotal(order)) %>
	</td>
</tr>
</table>

<c:if test="<%= !windowState.equals(LiferayWindowState.POP_UP) %>">
	<br />

	<c:if test="<%= shoppingPrefs.usePayPal() %>">
		<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />saveOrder();" />
	</c:if>

	<input type="button" value="<liferay-ui:message key="invoice" />" onClick="window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/shopping/edit_order" /><portlet:param name="orderId" value="<%= String.valueOf(orderId) %>" /></portlet:renderURL>');" />

	<input type="button" value='<%= LanguageUtil.get(pageContext, (order.isSendOrderEmail() ? "" : "re") + "send-confirmation-email") %>' onClick="<portlet:namespace />sendEmail('confirmation');" />

	<input type="button" value='<%= LanguageUtil.get(pageContext, (order.isSendShippingEmail() ? "" : "re") + "send-shipping-email") %>' onClick="<portlet:namespace />sendEmail('shipping');" />

	<c:if test="<%= ShoppingOrderPermission.contains(permissionChecker, plid.longValue(), order, ActionKeys.DELETE) %>">
		<input type="button" value="<liferay-ui:message key="delete" />" onClick="<portlet:namespace />deleteOrder();" />
	</c:if>

	<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />
</c:if>

</form>

<c:if test="<%= !windowState.equals(LiferayWindowState.POP_UP) %>">
	<br />

	<liferay-ui:tabs names="comments" />

	<portlet:actionURL var="discussionURL">
		<portlet:param name="struts_action" value="/shopping/edit_order_discussion" />
	</portlet:actionURL>

	<liferay-ui:discussion
		formName="fm2"
		formAction="<%= discussionURL %>"
		className="<%= ShoppingOrder.class.getName() %>"
		classPK="<%= order.getOrderId() %>"
		userId="<%= order.getUserId() %>"
		subject="<%= order.getNumber() %>"
		redirect="<%= currentURL %>"
	/>
</c:if>