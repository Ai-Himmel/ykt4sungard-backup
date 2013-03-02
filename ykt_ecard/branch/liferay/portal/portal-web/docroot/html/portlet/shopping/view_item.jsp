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

ShoppingItem item = (ShoppingItem)request.getAttribute(WebKeys.SHOPPING_ITEM);

item = item.toEscapedModel();

ShoppingItemField[] itemFields = (ShoppingItemField[])ShoppingItemFieldLocalServiceUtil.getItemFields(item.getItemId()).toArray(new ShoppingItemField[0]);
ShoppingItemPrice[] itemPrices = (ShoppingItemPrice[])ShoppingItemPriceLocalServiceUtil.getItemPrices(item.getItemId()).toArray(new ShoppingItemPrice[0]);

String orderByCol = portalPrefs.getValue(PortletKeys.SHOPPING, "items-order-by-col", "sku");
String orderByType = portalPrefs.getValue(PortletKeys.SHOPPING, "items-order-by-type", "asc");

OrderByComparator orderByComparator = ShoppingUtil.getItemOrderByComparator(orderByCol, orderByType);

ShoppingItem[] prevAndNext = ShoppingItemLocalServiceUtil.getItemsPrevAndNext(item.getItemId(), orderByComparator);
%>

<script type="text/javascript">
	function <portlet:namespace />addToCart() {
		document.<portlet:namespace />fm.<portlet:namespace />fields.value = "";

		<%
		for (int i = 0; i < itemFields.length; i++) {
			ShoppingItemField itemField = itemFields[i];

			String fieldName = itemField.getName();
			String[] fieldValues = itemField.getValuesArray();
		%>

			if (document.<portlet:namespace />fm.<portlet:namespace />fieldName<%= fieldName %>.value == "") {
				alert("<%= UnicodeLanguageUtil.get(pageContext, "please-select-all-options") %>");

				return;
			}

			document.<portlet:namespace />fm.<portlet:namespace />fields.value = document.<portlet:namespace />fm.<portlet:namespace />fields.value + '<%= fieldName %>=' + document.<portlet:namespace />fm.<portlet:namespace />fieldName<%= fieldName %>.value + '&';

		<%
		}
		%>

		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/cart" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.ADD %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/cart" /><portlet:param name="redirect" value="<%= currentURL %>" /></portlet:renderURL>" />
<input name="<portlet:namespace />itemId" type="hidden" value="<%= item.getItemId() %>" />
<input name="<portlet:namespace />fields" type="hidden" value="" />

<liferay-ui:tabs
	names="item"
	backURL="<%= redirect %>"
/>

<div class="breadcrumbs">
	<%= ShoppingUtil.getBreadcrumbs(item.getCategoryId(), pageContext, renderRequest, renderResponse) %>
</div>

<table border="0" cellpadding="0" cellspacing="0">
<tr>
	<td valign="top">
		<b><%= item.getSku() %></b>

		<br /><br />

		<c:if test="<%= item.isMediumImage() %>">
			<img src="<%= Validator.isNotNull(item.getMediumImageURL()) ? item.getMediumImageURL() : themeDisplay.getPathImage() + "/shopping/item?img_id=" + item.getMediumImageId() + "&t=" + ImageServletTokenUtil.getToken(item.getMediumImageId()) %>" vspace="0" />
		</c:if>

		<c:if test="<%= item.isLargeImage() %>">
			<br />

			<a href="<%= Validator.isNotNull(item.getLargeImageURL()) ? item.getLargeImageURL() : themeDisplay.getPathImage() + "/shopping/item?img_id=" + item.getLargeImageId() + "&t=" + ImageServletTokenUtil.getToken(item.getLargeImageId()) %>" style="font-size: xx-small;" target="_blank">
			<liferay-ui:message key="see-large-photo" />
			</a>
		</c:if>
	</td>
	<td style="padding-left: 30px;"></td>
	<td valign="top">
		<span style="font-size: small;">
		<b><%= item.getName() %></b><br />
		</span>

		<c:if test="<%= Validator.isNotNull(item.getDescription()) %>">
			<br />

			<%= item.getDescription() %>
		</c:if>

		<%
		Properties props = new OrderedProperties();

		//props.load(new ByteArrayInputStream(item.getProperties().getBytes("ISO-8859-1")));
		PropertiesUtil.load(props, item.getProperties());

		Enumeration enu = props.propertyNames();

		while (enu.hasMoreElements()) {
			String propsKey = (String)enu.nextElement();
			String propsValue = props.getProperty(propsKey, StringPool.BLANK);
		%>

			<br />

			<%= propsKey %>: <%= propsValue %>

		<%
		}
		%>

		<br /><br />

		<%
		for (int i = 0; i < itemPrices.length; i++) {
			ShoppingItemPrice itemPrice = itemPrices[i];
		%>

			<c:choose>
				<c:when test="<%= (itemPrice.getMinQuantity()) == 0 && (itemPrice.getMaxQuantity() == 0) %>">
					<liferay-ui:message key="price" />:
				</c:when>
				<c:when test="<%= itemPrice.getMaxQuantity() != 0 %>">
					<%= LanguageUtil.format(pageContext, "price-for-x-to-x-items", new Object[] {"<b>" + new Integer(itemPrice.getMinQuantity()) + "</b>", "<b>" + new Integer(itemPrice.getMaxQuantity()) + "</b>"}, false) %>
				</c:when>
				<c:when test="<%= itemPrice.getMaxQuantity() == 0 %>">
					<%= LanguageUtil.format(pageContext, "price-for-x-items-and-above", "<b>" + new Integer(itemPrice.getMinQuantity()) + "</b>", false) %>
				</c:when>
			</c:choose>

			<c:if test="<%= itemPrice.getDiscount() <= 0 %>">
				<%= currencyFormat.format(itemPrice.getPrice()) %><br />
			</c:if>

			<c:if test="<%= itemPrice.getDiscount() > 0 %>">
				<strike><%= currencyFormat.format(itemPrice.getPrice()) %></strike> <span class="portlet-msg-success"><%= currencyFormat.format(ShoppingUtil.calculateActualPrice(itemPrice)) %></span> / <liferay-ui:message key="you-save" />: <span class="portlet-msg-error"><%= currencyFormat.format(ShoppingUtil.calculateDiscountPrice(itemPrice)) %> (<%= percentFormat.format(itemPrice.getDiscount()) %>)</span><br />
			</c:if>

		<%
		}
		%>

		<br />

		<c:if test="<%= PrefsPropsUtil.getBoolean(company.getCompanyId(), PropsUtil.SHOPPING_ITEM_SHOW_AVAILABILITY) %>">
			<c:choose>
				<c:when test="<%= ShoppingUtil.isInStock(item) %>">
					<liferay-ui:message key="availability" />: <span class="portlet-msg-success"><liferay-ui:message key="in-stock" /></span><br />
				</c:when>
				<c:otherwise>
					<liferay-ui:message key="availability" />: <span class="portlet-msg-error"><liferay-ui:message key="out-of-stock" /></span><br />
				</c:otherwise>
			</c:choose>

			<br />
		</c:if>

		<%
		for (int i = 0; i < itemFields.length; i++) {
			ShoppingItemField itemField = itemFields[i];

			String fieldName = itemField.getName();
			String[] fieldValues = itemField.getValuesArray();
			String fieldDescription = itemField.getDescription();
		%>

			<table class="lfr-table">
			<tr>
				<td>
					<%= fieldName %>:
				</td>
				<td>
					<select name="<portlet:namespace />fieldName<%= fieldName %>">
						<option value=""><liferay-ui:message key="select-option" /></option>

						<%
						for (int j = 0; j < fieldValues.length; j++) {
						%>

							<option value="<%= fieldValues[j] %>"><%= fieldValues[j] %></option>

						<%
						}
						%>

					</select>
				</td>

				<c:if test="<%= Validator.isNotNull(fieldDescription) %>">
					<td>
						<%= fieldDescription %>
					</td>
				</c:if>

			</tr>
			</table>

			<br />

		<%
		}
		%>

		<input type="button" value="<liferay-ui:message key="add-to-shopping-cart" />" onClick="<portlet:namespace />addToCart();" /><br />

		<c:if test="<%= (prevAndNext[0] != null) || (prevAndNext[2] != null) %>">
			<br />

			<c:if test="<%= prevAndNext[0] != null %>">
				<input type="button" value="<liferay-ui:message key="previous" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/view_item" /><portlet:param name="itemId" value="<%= String.valueOf(prevAndNext[0].getItemId()) %>" /></portlet:renderURL>';" />
			</c:if>

			<c:if test="<%= prevAndNext[2] != null %>">
				<input type="button" value="<liferay-ui:message key="next" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/view_item" /><portlet:param name="itemId" value="<%= String.valueOf(prevAndNext[2].getItemId()) %>" /></portlet:renderURL>';" />
			</c:if>
		</c:if>
	</td>
</tr>
</table>

</form>