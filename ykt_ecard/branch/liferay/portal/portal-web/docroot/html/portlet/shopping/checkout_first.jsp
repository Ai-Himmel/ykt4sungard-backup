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
ShoppingOrder order = (ShoppingOrder)request.getAttribute(WebKeys.SHOPPING_ORDER);

String billingState = BeanParamUtil.getString(order, request, "billingState");
String billingStateSel = ParamUtil.getString(request, "billingStateSel");

if (StateUtil.isStateId(billingState)) {
	billingStateSel = billingState;
	billingState = StringPool.BLANK;
}

String shippingState = BeanParamUtil.getString(order, request, "shippingState");
String shippingStateSel = ParamUtil.getString(request, "shippingStateSel");

if (StateUtil.isStateId(shippingState)) {
	shippingStateSel = shippingState;
	shippingState = StringPool.BLANK;
}

String ccType = ParamUtil.getString(request, "ccType");
String ccNumber = ParamUtil.getString(request, "ccNumber");

Calendar cal = CalendarFactoryUtil.getCalendar();

int ccExpMonth = ParamUtil.getInteger(request, "ccExpMonth", cal.get(Calendar.MONTH));
int ccExpYear = ParamUtil.getInteger(request, "ccExpYear", cal.get(Calendar.YEAR));

if (request.getParameter("ccExpMonth") == null) {
	if (ccExpMonth == Calendar.DECEMBER) {
		ccExpMonth = Calendar.JANUARY;
		ccExpYear++;
	}
	else {
		ccExpMonth++;
	}
}

String ccVerNumber = ParamUtil.getString(request, "ccVerNumber");

List addresses = AddressServiceUtil.getAddresses(Contact.class.getName(), contact.getContactId());
%>

<script type="text/javascript">
	function <portlet:namespace />updateAddress(addressId, type) {

		<%
		for (int i = 0; addresses != null && i < addresses.size(); i++) {
			Address address = (Address)addresses.get(i);

			Region region = address.getRegion();
			Country country = address.getCountry();
		%>

			if ("<%= address.getAddressId() %>" == addressId) {
				//document.getElementById("<portlet:namespace />" + type + "FirstName").value = "<%= user.getFirstName() %>";
				//document.getElementById("<portlet:namespace />" + type + "LastName").value = "<%= user.getLastName() %>";
				//document.getElementById("<portlet:namespace />" + type + "EmailAddress").value = "<%= user.getEmailAddress() %>";
				document.getElementById("<portlet:namespace />" + type + "Street").value = "<%= address.getStreet1() %>";
				document.getElementById("<portlet:namespace />" + type + "City").value = "<%= address.getCity() %>";

				var stateSel = document.getElementById("<portlet:namespace />" + type + "StateSel");
				var stateSelValue = "<%= region.getRegionCode() %>";

				for (var i = 0; i < stateSel.length; i++) {
					if (stateSel[i].value == stateSelValue) {
						stateSel.selectedIndex = i;

						break;
					}
				}

				document.getElementById("<portlet:namespace />" + type + "Zip").value = "<%= address.getZip() %>";
				document.getElementById("<portlet:namespace />" + type + "Country").value = "<%= country.getName() %>";
			}

		<%
		}
		%>

	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/checkout" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />

<liferay-util:include page="/html/portlet/shopping/tabs1.jsp">
	<liferay-util:param name="tabs1" value="cart" />
</liferay-util:include>

<liferay-ui:tabs names="billing-address" />

<liferay-ui:error exception="<%= BillingCityException.class %>" message="please-enter-a-valid-city" />
<liferay-ui:error exception="<%= BillingCountryException.class %>" message="please-enter-a-valid-country" />
<liferay-ui:error exception="<%= BillingEmailAddressException.class %>" message="please-enter-a-valid-email-address" />
<liferay-ui:error exception="<%= BillingFirstNameException.class %>" message="please-enter-a-valid-first-name" />
<liferay-ui:error exception="<%= BillingLastNameException.class %>" message="please-enter-a-valid-last-name" />
<liferay-ui:error exception="<%= BillingPhoneException.class %>" message="please-enter-a-valid-phone" />
<liferay-ui:error exception="<%= BillingStateException.class %>" message="please-enter-a-valid-state" />
<liferay-ui:error exception="<%= BillingStreetException.class %>" message="please-enter-a-valid-street" />
<liferay-ui:error exception="<%= BillingZipException.class %>" message="please-enter-a-valid-zip" />

<c:if test="<%= addresses.size() > 0 %>">
	<select onChange="<portlet:namespace />updateAddress(this[this.selectedIndex].value, 'billing');">
		<option value="">-- <liferay-ui:message key="my-addresses" /> --</option>

		<%
		for (int i = 0; addresses != null && i < addresses.size(); i++) {
			Address address = (Address)addresses.get(i);
		%>

			<option value="<%= address.getAddressId() %>"><%= address.getStreet1() %></option>

		<%
		}
		%>

	</select>

	<br /><br />
</c:if>

<table class="lfr-table">
<tr>
	<td>
		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="first-name" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="billingFirstName" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="last-name" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="billingLastName" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="email-address" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="billingEmailAddress" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="company" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="billingCompany" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="street" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="billingStreet" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="city" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="billingCity" />
			</td>
		</tr>
		</table>
	</td>
	<td valign="top">
		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="state" />
			</td>
			<td>
				<select id="<portlet:namespace />billingStateSel" name="<portlet:namespace />billingStateSel">
					<option value=""><liferay-ui:message key="outside-us" /></option>

					<%
					for (int i = 0; i < StateUtil.STATES.length; i++) {
					%>

						<option <%= billingStateSel.equals(StateUtil.STATES[i].getId()) ? "selected" : "" %> value="<%= StateUtil.STATES[i].getId() %>"><%= StateUtil.STATES[i].getName() %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="other-state" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= null %>" field="billingState" defaultValue="<%= billingState %>" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="zip" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="billingZip" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="country" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="billingCountry" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="phone" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="billingPhone" />
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>

<br />

<liferay-ui:tabs names="shipping-address" />

<liferay-ui:error exception="<%= ShippingCityException.class %>" message="please-enter-a-valid-city" />
<liferay-ui:error exception="<%= ShippingCountryException.class %>" message="please-enter-a-valid-country" />
<liferay-ui:error exception="<%= ShippingEmailAddressException.class %>" message="please-enter-a-valid-email-address" />
<liferay-ui:error exception="<%= ShippingFirstNameException.class %>" message="please-enter-a-valid-first-name" />
<liferay-ui:error exception="<%= ShippingLastNameException.class %>" message="please-enter-a-valid-last-name" />
<liferay-ui:error exception="<%= ShippingPhoneException.class %>" message="please-enter-a-valid-phone" />
<liferay-ui:error exception="<%= ShippingStateException.class %>" message="please-enter-a-valid-state" />
<liferay-ui:error exception="<%= ShippingStreetException.class %>" message="please-enter-a-valid-street" />
<liferay-ui:error exception="<%= ShippingZipException.class %>" message="please-enter-a-valid-zip" />

<table class="lfr-table">
<tr>
	<c:if test="<%= addresses.size() > 0 %>">
		<td>
			<select onChange="<portlet:namespace />updateAddress(this[this.selectedIndex].value, 'shipping');">
				<option value="">-- <liferay-ui:message key="my-addresses" /> --</option>

				<%
				for (int i = 0; addresses != null && i < addresses.size(); i++) {
					Address address = (Address)addresses.get(i);
				%>

					<option value="<%= address.getAddressId() %>"><%= address.getStreet1() %></option>

				<%
				}
				%>

			</select>
		</td>
	</c:if>

	<td>
		<liferay-ui:message key="same-as-billing" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shipToBilling" />
	</td>
</tr>
</table>

<br />

<table class="lfr-table">
<tr>
	<td>
		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="first-name" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shippingFirstName" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="last-name" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shippingLastName" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="email-address" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shippingEmailAddress" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="company" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shippingCompany" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="street" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shippingStreet" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="city" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shippingCity" />
			</td>
		</tr>
		</table>
	</td>
	<td valign="top">
		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="state" />
			</td>
			<td>
				<select id="<portlet:namespace />shippingStateSel" name="<portlet:namespace />shippingStateSel">
					<option value=""><liferay-ui:message key="outside-us" /></option>

					<%
					for (int i = 0; i < StateUtil.STATES.length; i++) {
					%>

						<option <%= shippingStateSel.equals(StateUtil.STATES[i].getId()) ? "selected" : "" %> value="<%= StateUtil.STATES[i].getId() %>"><%= StateUtil.STATES[i].getName() %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="other-state" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= null %>" field="shippingState" defaultValue="<%= shippingState %>" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="zip" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shippingZip" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="country" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shippingCountry" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="phone" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="shippingPhone" />
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>

<br />

<%
String[] ccTypes = shoppingPrefs.getCcTypes();
%>

<c:if test="<%= !shoppingPrefs.usePayPal() && (ccTypes.length > 0) %>">
	<liferay-ui:tabs names="credit-card" />

	<liferay-ui:error exception="<%= CCExpirationException.class %>" message="please-enter-a-valid-credit-card-expiration-date" />
	<liferay-ui:error exception="<%= CCNameException.class %>" message="please-enter-the-full-name-exactly-as-it-is-appears-on-your-credit-card" />
	<liferay-ui:error exception="<%= CCNumberException.class %>" message="please-enter-a-valid-credit-card-number" />
	<liferay-ui:error exception="<%= CCTypeException.class %>" message="please-enter-a-valid-credit-card-type" />

	<%
	for (int i = 0; i < ccTypes.length; i++) {
	%>

		<img src="<%= themeDisplay.getPathThemeImages() %>/shopping/cc_<%= ccTypes[i] %>.png" />

	<%
	}
	%>

	<br /><br />

	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="full-name" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="ccName" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="type" />
		</td>
		<td>
			<select name="<portlet:namespace />ccType">
				<option value=""></option>

				<%
				for (int i = 0; i < ccTypes.length; i++) {
				%>

					<option <%= ccTypes[i].equals(ccType) ? "selected" : "" %> value="<%= ccTypes[i] %>"><liferay-ui:message key='<%= "cc_" + ccTypes[i] %>' /></option>

				<%
				}
				%>

			</select>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="number" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= null %>" field="ccNumber" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="expiration-date" />
		</td>
		<td>
			<select name="<portlet:namespace />ccExpMonth">

				<%
				String[] months = CalendarUtil.getMonths(locale);

				for (int i = 0; i < months.length; i++) {
				%>

					<option <%= (i == ccExpMonth) ? "selected" : "" %> value="<%= i %>"><%= months[i] %></option>

				<%
				}
				%>

			</select>

			<select name="<portlet:namespace />ccExpYear">

				<%
				int currentYear = cal.get(Calendar.YEAR);

				for (int i = currentYear; i <= currentYear + 5; i++) {
				%>

					<option <%= (i == ccExpYear) ? "selected" : "" %> value="<%= i %>"><%= i %></option>

				<%
				}
				%>

			</select>
		</td>
	</tr>
	</table>

	<br />

	<img src="<%= themeDisplay.getPathThemeImages() %>/shopping/cc_ver_number.png" />

	<br /><br />

	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="verification-number" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= null %>" field="ccVerNumber" />
		</td>
	</tr>
	</table>

	<br />
</c:if>

<liferay-ui:tabs names="comments" />

<liferay-ui:input-field model="<%= ShoppingOrder.class %>" bean="<%= order %>" field="comments" />

<br /><br />

<input type="button" value="<liferay-ui:message key="continue" />" onClick="submitForm(document.<portlet:namespace />fm);" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />billingFirstName);
	</script>
</c:if>