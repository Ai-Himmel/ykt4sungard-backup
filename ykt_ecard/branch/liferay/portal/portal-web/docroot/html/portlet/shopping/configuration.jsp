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
String tabs2 = ParamUtil.getString(request, "tabs2", "payment-settings");
String tabs3 = ParamUtil.getString(request, "tabs3", "email-from");

String redirect = ParamUtil.getString(request, "redirect");
%>

<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="portletURL" portletConfiguration="true">
	<portlet:param name="tabs2" value="<%= tabs2 %>" />
	<portlet:param name="redirect" value="<%= redirect %>" />
</liferay-portlet:renderURL>

<script type="text/javascript">

	<%
	String emailFromName = ParamUtil.getString(request, "emailFromName", shoppingPrefs.getEmailFromName());
	String emailFromAddress = ParamUtil.getString(request, "emailFromAddress", shoppingPrefs.getEmailFromAddress());

	String emailOrderConfirmationSubject = ParamUtil.getString(request, "emailOrderConfirmationSubject", shoppingPrefs.getEmailOrderConfirmationSubject());
	String emailOrderConfirmationBody = ParamUtil.getString(request, "emailOrderConfirmationBody", shoppingPrefs.getEmailOrderConfirmationBody());

	String emailOrderShippingSubject = ParamUtil.getString(request, "emailOrderShippingSubject", shoppingPrefs.getEmailOrderShippingSubject());
	String emailOrderShippingBody = ParamUtil.getString(request, "emailOrderShippingBody", shoppingPrefs.getEmailOrderShippingBody());

	String editorParam = "";
	String editorContent = "";

	if (tabs3.equals("confirmation-email")) {
		editorParam = "emailOrderConfirmationBody";
		editorContent = emailOrderConfirmationBody;
	}
	else if (tabs3.equals("shipping-email")) {
		editorParam = "emailOrderShippingBody";
		editorContent = emailOrderShippingBody;
	}
	%>

	function initEditor() {
		return "<%= UnicodeFormatter.toString(editorContent) %>";
	}

	function <portlet:namespace />saveConfiguration() {
		<c:if test='<%= tabs2.equals("payment-settings") %>'>
			document.<portlet:namespace />fm.<portlet:namespace />ccTypes.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />current_cc_types);
		</c:if>

		<c:if test='<%= tabs3.endsWith("-email") %>'>
			document.<portlet:namespace />fm.<portlet:namespace /><%= editorParam %>.value = window.<portlet:namespace />editor.getHTML();
		</c:if>

		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<liferay-portlet:actionURL portletConfiguration="true" />" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveConfiguration(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />
<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
<input name="<portlet:namespace />tabs3" type="hidden" value="<%= tabs3 %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />ccTypes" type="hidden" value="" />

<liferay-ui:tabs
	names="payment-settings,shipping-calculation,insurance-calculation,emails"
	param="tabs2"
	url="<%= portletURL %>"
/>

<c:choose>
	<c:when test='<%= tabs2.equals("payment-settings") %>'>
		<liferay-ui:message key="enter-a-paypal-email-address-to-send-all-payments-to-paypal" /> <%= LanguageUtil.format(pageContext, "go-to-paypal-and-set-up-ipn-to-post-to-x", "<b>" + PortalUtil.getPortalURL(request) + themeDisplay.getPathMain() + "/shopping/notify</b>", false) %>

		<br /><br />

		<liferay-ui:message key="enter-a-blank-paypal-email-address-to-disable-paypal" />

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="paypal-email-address" />
			</td>
			<td>
				<input class="lfr-input-text" name="<portlet:namespace />payPalEmailAddress" type="text" value="<%= shoppingPrefs.getPayPalEmailAddress() %>" />
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="credit-cards" />
			</td>
			<td>

				<%

				String[] ccTypes1 = ShoppingPreferences.CC_TYPES;
				String[] ccTypes2 = shoppingPrefs.getCcTypes();

				// Left list

				List leftList = new ArrayList();

				for (int i = 0; i < ccTypes2.length; i++) {
					String ccType = (String)ccTypes2[i];

					leftList.add(new KeyValuePair(ccType, LanguageUtil.get(pageContext, "cc_" + ccType)));
				}

				// Right list

				List rightList = new ArrayList();

				for (int i = 0; i < ccTypes1.length; i++) {
					String ccType = (String)ccTypes1[i];

					if (!ArrayUtil.contains(ccTypes2, ccType)) {
						rightList.add(new KeyValuePair(ccType, LanguageUtil.get(pageContext, "cc_" + ccType)));
					}
				}
				%>

				<liferay-ui:input-move-boxes
					leftTitle="current"
					rightTitle="available"
					leftBoxName="current_cc_types"
					rightBoxName="available_cc_types"
					leftReorder="true"
					leftList="<%= leftList %>"
					rightList="<%= rightList %>"
				/>
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="currency" />
			</td>
			<td>
				<select name="<portlet:namespace />currencyId">

					<%
					for (int i = 0; i < ShoppingPreferences.CURRENCY_IDS.length; i++) {
					%>

						<option <%= shoppingPrefs.getCurrencyId().equals(ShoppingPreferences.CURRENCY_IDS[i]) ? "selected" : "" %> value="<%= ShoppingPreferences.CURRENCY_IDS[i] %>"><%= ShoppingPreferences.CURRENCY_IDS[i] %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="tax-state" />
			</td>
			<td>
				<select name="<portlet:namespace />taxState">

					<%
					for (int i = 0; i < StateUtil.STATES.length; i++) {
					%>

						<option <%= shoppingPrefs.getTaxState().equals(StateUtil.STATES[i].getId()) ? "selected" : "" %> value="<%= StateUtil.STATES[i].getId() %>"><%= StateUtil.STATES[i].getName() %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="tax-rate" />
			</td>
			<td>
				<input maxlength="7" name="<portlet:namespace />taxRate" type="text" size="7" value="<%= taxFormat.format(shoppingPrefs.getTaxRate()) %>" />
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="minimum-order" />
			</td>
			<td>
				<input maxlength="7" name="<portlet:namespace />minOrder" type="text" size="7" value="<%= currencyFormat.format(shoppingPrefs.getMinOrder()) %>" />
			</td>
		</tr>
		</table>
	</c:when>
	<c:when test='<%= tabs2.equals("shipping-calculation") %>'>
		<liferay-ui:message key="calculate-a-flat-shipping-amount-based-on-the-total-amount-of-the-purchase" /> <span style="font-size: xx-small;">-- <%= LanguageUtil.get(pageContext, "or").toUpperCase() %> --</span> <liferay-ui:message key="calculate-the-shipping-based-on-a-percentage-of-the-total-amount-of-the-purchase" />

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="formula" />
			</td>
			<td>
				<select name="<portlet:namespace />shippingFormula">
					<option <%= shoppingPrefs.getShippingFormula().equals("flat") ? "selected" : "" %> value="flat"><liferay-ui:message key="flat-amount" /></option>
					<option <%= shoppingPrefs.getShippingFormula().equals("percentage") ? "selected" : "" %> value="percentage"><liferay-ui:message key="percentage" /></option>
				</select>
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="values" />
			</td>
			<td>
				<table class="lfr-table">

				<%
				int shippingRange = 0;

				for (int i = 0; i < 5; i++) {
					double shippingRangeA = ShoppingPreferences.INSURANCE_RANGE[shippingRange++];
					double shippingRangeB = ShoppingPreferences.INSURANCE_RANGE[shippingRange++];
				%>

					<tr>
						<td>
							<%= currencyFormat.format(shippingRangeA) %>

							<c:if test="<%= !Double.isInfinite(shippingRangeB) %>">
								- <%= currencyFormat.format(shippingRangeB) %>
							</c:if>

							<c:if test="<%= Double.isInfinite(shippingRangeB) %>">
								and over
							</c:if>
						</td>
						<td>
							<input maxlength="6" name="<portlet:namespace />shipping<%= i %>" size="6" type="text" value="<%= GetterUtil.getString(shoppingPrefs.getShipping()[i]) %>" />
						</td>
					</tr>

				<%
				}
				%>

				</table>
			</td>
		</tr>
		</table>
	</c:when>
	<c:when test='<%= tabs2.equals("insurance-calculation") %>'>
		<liferay-ui:message key="calculate-a-flat-insurance-amount-based-on-the-total-amount-of-the-purchase" /> <span style="font-size: xx-small;">-- <%= LanguageUtil.get(pageContext, "or").toUpperCase() %> --</span> <liferay-ui:message key="calculate-the-insurance-based-on-a-percentage-of-the-total-amount-of-the-purchase" />

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="formula" />
			</td>
			<td>
				<select name="<portlet:namespace />insuranceFormula">
					<option <%= shoppingPrefs.getInsuranceFormula().equals("flat") ? "selected" : "" %> value="flat"><liferay-ui:message key="flat-amount" /></option>
					<option <%= shoppingPrefs.getInsuranceFormula().equals("percentage") ? "selected" : "" %> value="percentage"><liferay-ui:message key="percentage" /></option>
				</select>
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="values" />
			</td>
			<td>
				<table class="lfr-table">

				<%
				int insuranceRange = 0;

				for (int i = 0; i < 5; i++) {
					double insuranceRangeA = ShoppingPreferences.INSURANCE_RANGE[insuranceRange++];
					double insuranceRangeB = ShoppingPreferences.INSURANCE_RANGE[insuranceRange++];
				%>

					<tr>
						<td>
							<%= currencyFormat.format(insuranceRangeA) %>

							<c:if test="<%= !Double.isInfinite(insuranceRangeB) %>">
								- <%= currencyFormat.format(insuranceRangeB) %>
							</c:if>

							<c:if test="<%= Double.isInfinite(insuranceRangeB) %>">
								and over
							</c:if>
						</td>
						<td>
							<input maxlength="6" name="<portlet:namespace />insurance<%= i %>" size="6" type="text" value="<%= GetterUtil.getString(shoppingPrefs.getInsurance()[i]) %>" />
						</td>
					</tr>

				<%
				}
				%>

				</table>
			</td>
		</tr>
		</table>
	</c:when>
	<c:when test='<%= tabs2.equals("emails") %>'>
		<liferay-ui:tabs
			names="email-from,confirmation-email,shipping-email"
			param="tabs3"
			url="<%= portletURL.toString() %>"
		/>

		<liferay-ui:error key="emailFromAddress" message="please-enter-a-valid-email-address" />
		<liferay-ui:error key="emailFromName" message="please-enter-a-valid-name" />
		<liferay-ui:error key="emailOrderShippingBody" message="please-enter-a-valid-body" />
		<liferay-ui:error key="emailOrderShippingSubject" message="please-enter-a-valid-subject" />
		<liferay-ui:error key="emailOrderConfirmationBody" message="please-enter-a-valid-body" />
		<liferay-ui:error key="emailOrderConfirmationSubject" message="please-enter-a-valid-subject" />

		<c:choose>
			<c:when test='<%= tabs3.endsWith("-email") %>'>
				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="enabled" />
					</td>
					<td>
						<c:choose>
							<c:when test='<%= tabs3.equals("confirmation-email") %>'>
								<liferay-ui:input-checkbox param="emailOrderConfirmationEnabled" defaultValue="<%= shoppingPrefs.getEmailOrderConfirmationEnabled() %>" />
							</c:when>
							<c:when test='<%= tabs3.equals("shipping-email") %>'>
								<liferay-ui:input-checkbox param="emailOrderShippingEnabled" defaultValue="<%= shoppingPrefs.getEmailOrderShippingEnabled() %>" />
							</c:when>
						</c:choose>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<br />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="subject" />
					</td>
					<td>
						<c:choose>
							<c:when test='<%= tabs3.equals("confirmation-email") %>'>
								<input class="lfr-input-text" name="<portlet:namespace />emailOrderConfirmationSubject" type="text" value="<%= emailOrderConfirmationSubject %>" />
							</c:when>
							<c:when test='<%= tabs3.equals("shipping-email") %>'>
								<input class="lfr-input-text" name="<portlet:namespace />emailOrderShippingSubject" type="text" value="<%= emailOrderShippingSubject %>" />
							</c:when>
						</c:choose>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<br />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="body" />
					</td>
					<td>
						<liferay-ui:input-editor editorImpl="<%= EDITOR_WYSIWYG_IMPL_KEY %>" />

						<input name="<portlet:namespace /><%= editorParam %>" type="hidden" value="" />
					</td>
				</tr>
				</table>

				<br />

				<b><liferay-ui:message key="definition-of-terms" /></b>

				<br /><br />

				<table class="lfr-table">
				<tr>
					<td>
						<b>[$FROM_ADDRESS$]</b>
					</td>
					<td>
						<%= emailFromAddress %>
					</td>
				</tr>
				<tr>
					<td>
						<b>[$FROM_NAME$]</b>
					</td>
					<td>
						<%= emailFromName %>
					</td>
				</tr>
				<tr>
					<td>
						<b>[$ORDER_BILLING_ADDRESS$]</b>
					</td>
					<td>
						The order billing address
					</td>
				</tr>
				<tr>
					<td>
						<b>[$ORDER_CURRENCY$]</b>
					</td>
					<td>
						The order currency
					</td>
				</tr>
				<tr>
					<td>
						<b>[$ORDER_NUMBER$]</b>
					</td>
					<td>
						The order ID
					</td>
				</tr>
				<tr>
					<td>
						<b>[$ORDER_SHIPPING_ADDRESS$]</b>
					</td>
					<td>
						The order shipping address
					</td>
				</tr>
				<tr>
					<td>
						<b>[$ORDER_TOTAL$]</b>
					</td>
					<td>
						The order total
					</td>
				</tr>
				<tr>
					<td>
						<b>[$PORTAL_URL$]</b>
					</td>
					<td>
						<%= company.getVirtualHost() %>
					</td>
				</tr>
				<tr>
					<td>
						<b>[$PORTLET_NAME$]</b>
					</td>
					<td>
						<%= ((RenderResponseImpl)renderResponse).getTitle() %>
					</td>
				</tr>
				<tr>
					<td>
						<b>[$TO_ADDRESS$]</b>
					</td>
					<td>
						The address of the email recipient
					</td>
				</tr>
				<tr>
					<td>
						<b>[$TO_NAME$]</b>
					</td>
					<td>
						The name of the email recipient
					</td>
				</tr>
				</table>
			</c:when>
			<c:otherwise>
				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="name" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />emailFromName" type="text" value="<%= emailFromName %>" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="address" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />emailFromAddress" type="text" value="<%= emailFromAddress %>" />
					</td>
				</tr>
				</table>
			</c:otherwise>
		</c:choose>
	</c:when>
</c:choose>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<%!
public static final String EDITOR_WYSIWYG_IMPL_KEY = "editor.wysiwyg.portal-web.docroot.html.portlet.shopping.edit_configuration.jsp";
%>