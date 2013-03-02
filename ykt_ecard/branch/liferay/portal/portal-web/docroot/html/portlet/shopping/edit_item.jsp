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

long itemId = BeanParamUtil.getLong(item, request, "itemId");

long categoryId = BeanParamUtil.getLong(item, request, "categoryId", ShoppingCategoryImpl.DEFAULT_PARENT_CATEGORY_ID);

// Fields

ShoppingItemField[] itemFields = null;

int fieldsCount = ParamUtil.getInteger(request, "fieldsCount");
String fieldsCountParam = request.getParameter("fieldsCount");
if ((fieldsCountParam == null) || (fieldsCountParam.equals(StringPool.NULL))) {
	if (item != null) {
		itemFields = (ShoppingItemField[])ShoppingItemFieldLocalServiceUtil.getItemFields(itemId).toArray(new ShoppingItemField[0]);
		fieldsCount = itemFields.length;
	}
	else {
		itemFields = new ShoppingItemField[0];
	}
}
else {
	itemFields = new ShoppingItemField[fieldsCount];
}

int fieldId = ParamUtil.getInteger(request, "fieldId", -1);

String fieldsQuantities = "";

if (item != null) {
	fieldsQuantities = GetterUtil.getString(item.getFieldsQuantities());
}

// Prices

ShoppingItemPrice[] itemPrices = null;

int pricesCount = ParamUtil.getInteger(request, "pricesCount", 1);
String pricesCountParam = request.getParameter("pricesCount");
if ((pricesCountParam == null) || (pricesCountParam.equals(StringPool.NULL))) {
	if (item != null) {
		itemPrices = (ShoppingItemPrice[])ShoppingItemPriceLocalServiceUtil.getItemPrices(itemId).toArray(new ShoppingItemPrice[0]);
		pricesCount = itemPrices.length;
	}
	else {
		itemPrices = new ShoppingItemPrice[1];
	}
}
else {
	itemPrices = new ShoppingItemPrice[pricesCount];
}

int priceId = ParamUtil.getInteger(request, "priceId", -1);
%>

<script type="text/javascript">
	function <portlet:namespace />addField() {
		document.<portlet:namespace />fm.scroll.value = "<portlet:namespace />fields";
		document.<portlet:namespace />fm.<portlet:namespace />fieldsCount.value = <%= fieldsCount + 1 %>;
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />addPrice() {
		document.<portlet:namespace />fm.scroll.value = "<portlet:namespace />prices";
		document.<portlet:namespace />fm.<portlet:namespace />pricesCount.value = <%= pricesCount + 1 %>;
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />deleteField(i) {
		document.<portlet:namespace />fm.scroll.value = "<portlet:namespace />fields";
		document.<portlet:namespace />fm.<portlet:namespace />fieldsCount.value = <%= fieldsCount - 1 %>;
		document.<portlet:namespace />fm.<portlet:namespace />fieldId.value = i;
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />deletePrice(i) {
		if (document.<portlet:namespace />fm.<portlet:namespace />defaultPrice[i].checked) {
			alert("<%= UnicodeLanguageUtil.get(pageContext, "you-cannot-delete-or-deactivate-a-default-price") %>");
		}
		else if (document.<portlet:namespace />fm.<portlet:namespace />pricesCount.value > 1) {
			document.<portlet:namespace />fm.scroll.value = "<portlet:namespace />prices";
			document.<portlet:namespace />fm.<portlet:namespace />pricesCount.value = <%= pricesCount - 1 %>;
			document.<portlet:namespace />fm.<portlet:namespace />priceId.value = i;
			submitForm(document.<portlet:namespace />fm);
		}
	}

	function <portlet:namespace />editItemQuantities() {
		var itemQuantitiesURL = "<liferay-portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>" anchor="false"><portlet:param name="struts_action" value="/shopping/edit_item_quantities" /></liferay-portlet:renderURL>&<portlet:namespace />fieldsQuantities=" + document.<portlet:namespace />fm.<portlet:namespace />fieldsQuantities.value;

		<%
		for (int i = 0; i < fieldsCount; i++) {
		%>

			itemQuantitiesURL += "&<portlet:namespace />n<%= i %>=" + encodeURIComponent(document.<portlet:namespace />fm.<portlet:namespace />fieldName<%= i %>.value);
			itemQuantitiesURL += "&<portlet:namespace />v<%= i %>=" + encodeURIComponent(document.<portlet:namespace />fm.<portlet:namespace />fieldValues<%= i %>.value);

		<%
		}
		%>

		var itemQuantitiesWindow = window.open(itemQuantitiesURL, "itemQuantities", "directories=no,height=400,location=no,menubar=no,resizable=no,scrollbars=yes,status=no,toolbar=no,width=300");

		void("");

		itemQuantitiesWindow.focus();
	}

	function <portlet:namespace />saveItem() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= item == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectCategory(categoryId, categoryName) {
		document.<portlet:namespace />fm.<portlet:namespace />categoryId.value = categoryId;

		var nameEl = document.getElementById("<portlet:namespace />categoryName");

		nameEl.href = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/view" /></portlet:renderURL>&<portlet:namespace />categoryId=" + categoryId;
		nameEl.innerHTML = categoryName + "&nbsp;";
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/edit_item" /></portlet:actionURL>" enctype="multipart/form-data" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveItem(); return false;">
<input name="scroll" type="hidden" value="" />
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />categoryId" type="hidden" value="<%= categoryId %>" />
<input name="<portlet:namespace />itemId" type="hidden" value="<%= itemId %>" />
<input name="<portlet:namespace />fieldsCount" type="hidden" value="<%= fieldsCount %>" />
<input name="<portlet:namespace />fieldId" type="hidden" value="" />
<input name="<portlet:namespace />fieldsQuantities" type="hidden" value="<%= fieldsQuantities %>" />
<input name="<portlet:namespace />pricesCount" type="hidden" value="<%= pricesCount %>" />
<input name="<portlet:namespace />priceId" type="hidden" value="" />

<liferay-ui:tabs
	names="item"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= DuplicateItemSKUException.class %>" message="the-item-sku-you-requested-is-already-taken" />
<liferay-ui:error exception="<%= ItemNameException.class %>" message="please-enter-a-valid-name" />
<liferay-ui:error exception="<%= ItemSKUException.class %>" message="please-enter-a-valid-item-sku" />

<div class="breadcrumbs">
	<%= ShoppingUtil.getBreadcrumbs(categoryId, pageContext, renderRequest, renderResponse) %>
</div>

<table class="lfr-table">

<c:if test="<%= item != null %>">
	<tr>
		<td>
			<liferay-ui:message key="category" />
		</td>
		<td>

			<%
			ShoppingCategory category = ShoppingCategoryLocalServiceUtil.getCategory(categoryId);

			category = category.toEscapedModel();
			%>

			<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/shopping/view" /><portlet:param name="categoryId" value="<%= String.valueOf(categoryId) %>" /></portlet:renderURL>" id="<portlet:namespace />categoryName">
			<%= category.getName() %></a>

			<input type="button" value="<liferay-ui:message key="select" />" onClick="var categoryWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/shopping/select_category" /><portlet:param name="categoryId" value="<%= String.valueOf(categoryId) %>" /></portlet:renderURL>', 'category', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=no,status=no,toolbar=no,width=680'); void(''); categoryWindow.focus();" />
		</td>
	</tr>
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
</c:if>

<tr>
	<td>
		<liferay-ui:message key="sku" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="sku" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="name" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="name" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="description" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="description" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="properties" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="properties" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="requires-shipping" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="requiresShipping" />
			</td>
			<td>
				<liferay-ui:message key="featured" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="featured" />
			</td>

			<c:if test="<%= fieldsCount == 0 %>">
				<td>
					<liferay-ui:message key="stock-quantity" />
				</td>
				<td>
					<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="stockQuantity" />
				</td>
			</c:if>
		</tr>
		</table>
	</td>
</tr>

<c:if test="<%= item == null %>">
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="permissions" />
		</td>
		<td>
			<liferay-ui:input-permissions
				modelName="<%= ShoppingItem.class.getName() %>"
			/>
		</td>
	</tr>
</c:if>

</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

<br /><br />

<liferay-ui:tabs names="fields" />

<input name="<portlet:namespace />fields" type="hidden" value="" />

<liferay-ui:message key="fields-are-added-if-you-need-to-distinguish-items-based-on-criteria-chosen-by-the-user" />

<br /><br />

<table class="lfr-table">

<%
for (int i = 0; i < fieldsCount; i++) {
	int curFieldId = i;

	if ((fieldId > -1) && (i >= fieldId)) {
		curFieldId++;
	}

	String fieldName = ParamUtil.getString(request, "fieldName" + curFieldId);
	String fieldNameParam = request.getParameter("fieldName" + curFieldId);
	if ((fieldNameParam == null) || (fieldNameParam.equals(StringPool.NULL))) {
		if (itemFields[curFieldId] != null) {
			fieldName = itemFields[curFieldId].getName();
		}
	}

	String[] fieldValues = StringUtil.split(ParamUtil.getString(request, "fieldValues" + curFieldId));
	String fieldValuesParam = request.getParameter("fieldValues" + curFieldId);
	if ((fieldValuesParam == null) || (fieldValuesParam.equals(StringPool.NULL))) {
		if (itemFields[curFieldId] != null) {
			fieldValues = itemFields[curFieldId].getValuesArray();
		}
	}

	String fieldDescription = ParamUtil.getString(request, "fieldDescription" + curFieldId);
	String fieldDescriptionParam = request.getParameter("fieldDescription" + curFieldId);
	if ((fieldDescriptionParam == null) || (fieldDescriptionParam.equals(StringPool.NULL))) {
		if (itemFields[curFieldId] != null) {
			fieldDescription = itemFields[curFieldId].getDescription();
		}
	}
%>

	<tr>
		<td>
			<liferay-ui:message key="name" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= ShoppingItemField.class %>" field="name" fieldParam='<%= "fieldName" + i %>' defaultValue="<%= fieldName %>" />
		</td>
		<td>
			<liferay-ui:message key="values" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= ShoppingItemField.class %>" field="values" fieldParam='<%= "fieldValues" + i %>' defaultValue='<%= StringUtil.merge(fieldValues, ", ") %>' />
		</td>
		<td>
			<liferay-ui:message key="description" />
		</td>
		<td>
			<liferay-ui:input-field model="<%= ShoppingItemField.class %>" field="description" fieldParam='<%= "fieldDescription" + i %>' defaultValue="<%= fieldDescription %>" />
		</td>

		<c:if test="<%= fieldsCount > 0 %>">
			<td>
				<input type="button" value="<liferay-ui:message key="delete" />" onClick="<portlet:namespace />deleteField(<%= i %>);" />
			</td>
		</c:if>
	</tr>

<%
}
%>

</table>

<c:if test="<%= fieldsCount > 0 %>">
	<br />
</c:if>

<input type="button" value="<liferay-ui:message key="add-field" />" onClick="<portlet:namespace />addField();" />

<c:if test="<%= fieldsCount > 0 %>">
	<input type="button" value="<liferay-ui:message key="edit-stock-quantity" />" onClick="<portlet:namespace />editItemQuantities();" />
</c:if>

<br /><br />

<liferay-ui:tabs names="prices" />

<input name="<portlet:namespace />prices" type="hidden" value="" />

<table class="lfr-table">

<%
for (int i = 0; i < pricesCount; i++) {
	int curPriceId = i;

	if (priceId > -1 && i >= priceId) {
		curPriceId++;
	}

	int minQuantity = ParamUtil.getInteger(request, "minQuantity" + curPriceId, 0);
	String minQuantityParam = request.getParameter("minQuantity" + curPriceId);
	if ((minQuantityParam == null) || (minQuantityParam.equals(StringPool.NULL))) {
		if (itemPrices[curPriceId] != null) {
			minQuantity = itemPrices[curPriceId].getMinQuantity();
		}
	}

	int maxQuantity = ParamUtil.getInteger(request, "maxQuantity" + curPriceId);
	String maxQuantityParam = request.getParameter("maxQuantity" + curPriceId);
	if ((maxQuantityParam == null) || (maxQuantityParam.equals(StringPool.NULL))) {
		if (itemPrices[curPriceId] != null) {
			maxQuantity = itemPrices[curPriceId].getMaxQuantity();
		}
	}

	double price = ParamUtil.getDouble(request, "price" + curPriceId);
	String priceParam = request.getParameter("price" + curPriceId);
	if ((priceParam == null) || (priceParam.equals(StringPool.NULL))) {
		if (itemPrices[curPriceId] != null) {
			price = itemPrices[curPriceId].getPrice();
		}
	}

	double discount = ParamUtil.getDouble(request, "discount" + curPriceId) / 100;
	String discountParam = request.getParameter("discount" + curPriceId);
	if ((discountParam == null) || (discountParam.equals(StringPool.NULL))) {
		if (itemPrices[curPriceId] != null) {
			discount = itemPrices[curPriceId].getDiscount();
		}
	}

	boolean taxable = ParamUtil.getBoolean(request, "taxable" + curPriceId, true);
	String taxableParam = request.getParameter("taxable" + curPriceId);
	if ((taxableParam == null) || (taxableParam.equals(StringPool.NULL))) {
		if (itemPrices[curPriceId] != null) {
			taxable = itemPrices[curPriceId].isTaxable();
		}
	}

	double shipping = ParamUtil.getDouble(request, "shipping" + curPriceId);
	String shippingParam = request.getParameter("shipping" + curPriceId);
	if ((shippingParam == null) || (shippingParam.equals(StringPool.NULL))) {
		if (itemPrices[curPriceId] != null) {
			shipping = itemPrices[curPriceId].getShipping();
		}
	}

	boolean useShippingFormula = ParamUtil.getBoolean(request, "useShippingFormula" + curPriceId, true);
	String useShippingFormulaParam = request.getParameter("useShippingFormula" + curPriceId);
	if ((useShippingFormulaParam == null) || (useShippingFormulaParam.equals(StringPool.NULL))) {
		if (itemPrices[curPriceId] != null) {
			useShippingFormula = itemPrices[curPriceId].isUseShippingFormula();
		}
	}

	boolean active = ParamUtil.getBoolean(request, "active" + curPriceId, true);
	String activeParam = request.getParameter("active" + curPriceId);
	if ((activeParam == null) || (activeParam.equals(StringPool.NULL))) {
		if (itemPrices[curPriceId] != null) {
			int status = itemPrices[curPriceId].getStatus();

			if (status == ShoppingItemPriceImpl.STATUS_ACTIVE_DEFAULT || status == ShoppingItemPriceImpl.STATUS_ACTIVE) {
				active = true;
			}
			else {
				active = false;
			}
		}
	}

	String defaultPriceParam = request.getParameter("defaultPrice");
	boolean defaultPrice = (curPriceId == 0 ? true : false);
	if (Validator.isNotNull(defaultPriceParam)) {
		if (ParamUtil.getInteger(request, "defaultPrice") == curPriceId) {
			defaultPrice = true;
		}
		else {
			defaultPrice = false;
		}
	}
	else {
		if (itemPrices[curPriceId] != null) {
			int status = itemPrices[curPriceId].getStatus();

			if (status == ShoppingItemPriceImpl.STATUS_ACTIVE_DEFAULT) {
				defaultPrice = true;
			}
			else {
				defaultPrice = false;
			}
		}
	}
%>

	<tr>
		<td>
			<table class="lfr-table">
			<tr>
				<td>
					<liferay-ui:message key="min-qty" />
				</td>
				<td>
					<liferay-ui:input-field model="<%= ShoppingItemPrice.class %>" field="minQuantity" fieldParam='<%= "minQuantity" + i %>' defaultValue="<%= String.valueOf(minQuantity) %>" />
				</td>
				<td>
					<liferay-ui:message key="max-qty" />
				</td>
				<td>
					<liferay-ui:input-field model="<%= ShoppingItemPrice.class %>" field="maxQuantity" fieldParam='<%= "maxQuantity" + i %>' defaultValue="<%= String.valueOf(maxQuantity) %>" />
				</td>
				<td>
					<liferay-ui:message key="price" />
				</td>
				<td>
					<liferay-ui:input-field model="<%= ShoppingItemPrice.class %>" field="price" fieldParam='<%= "price" + i %>' defaultValue="<%= currencyFormat.format(price) %>" />
				</td>
				<td>
					<liferay-ui:message key="discount" />
				</td>
				<td>
					<liferay-ui:input-field model="<%= ShoppingItemPrice.class %>" field="discount" fieldParam='<%= "discount" + i %>' defaultValue="<%= percentFormat.format(discount) %>" />
				</td>
				<td>
					<liferay-ui:message key="taxable" />
				</td>
				<td>
					<liferay-ui:input-checkbox param='<%= "taxable" + i %>' defaultValue="<%= taxable %>" />
				</td>
			</tr>
			</table>

			<table class="lfr-table">
			<tr>
				<td>
					<liferay-ui:message key="shipping" />
				</td>
				<td>
					<liferay-ui:input-field model="<%= ShoppingItemPrice.class %>" field="shipping" fieldParam='<%= "shipping" + i %>' defaultValue="<%= currencyFormat.format(shipping) %>" />
				</td>
				<td>
					<liferay-ui:message key="use-shipping-formula" />
				</td>
				<td>
					<liferay-ui:input-checkbox param='<%= "useShippingFormula" + i %>' defaultValue="<%= useShippingFormula %>" />
				</td>
				<td>
					<liferay-ui:message key="active" />
				</td>
				<td>
					<liferay-ui:input-checkbox param='<%= "active" + i %>' defaultValue="<%= active %>" />
				</td>
				<td>
					<liferay-ui:message key="default" />
				</td>
				<td>
					<input <%= defaultPrice ? "checked" : "" %> name="<portlet:namespace />defaultPrice" type="radio" value="<%= i %>" onClick="document.<portlet:namespace />fm.<portlet:namespace />active<%= i %>.checked = true;">
				</td>

				<c:if test="<%= pricesCount > 1 %>">
					<td>
						<input type="button" value="<liferay-ui:message key="delete" />" onClick="<portlet:namespace />deletePrice(<%= i %>);" />
					</td>
				</c:if>
			</tr>
			</table>

			<c:if test="<%= (i + 1) < pricesCount %>">
				<br />
			</c:if>
		</td>
	</tr>

<%
}
%>

</table>

<br />

<input type="button" value="<liferay-ui:message key="add-price" />" onClick="<portlet:namespace />addPrice();" />

<br /><br />

<liferay-ui:tabs names="images" />

<liferay-ui:error exception="<%= ItemLargeImageNameException.class %>">

	<%
	String[] imageExtensions = PropsUtil.getArray(PropsUtil.SHOPPING_IMAGE_EXTENSIONS);
	%>

	<liferay-ui:message key="image-names-must-end-with-one-of-the-following-extensions" /> <%= StringUtil.merge(imageExtensions, ", ") %>.
</liferay-ui:error>

<liferay-ui:error exception="<%= ItemLargeImageSizeException.class %>" message="please-enter-a-file-with-a-valid-file-size" />

<liferay-ui:error exception="<%= ItemMediumImageNameException.class %>">

	<%
	String[] imageExtensions = PropsUtil.getArray(PropsUtil.SHOPPING_IMAGE_EXTENSIONS);
	%>

	<liferay-ui:message key="image-names-must-end-with-one-of-the-following-extensions" /> <%= StringUtil.merge(imageExtensions, ", ") %>.
</liferay-ui:error>

<liferay-ui:error exception="<%= ItemMediumImageSizeException.class %>" message="please-enter-a-file-with-a-valid-file-size" />

<liferay-ui:error exception="<%= ItemSmallImageNameException.class %>">

	<%
	String[] imageExtensions = PropsUtil.getArray(PropsUtil.SHOPPING_IMAGE_EXTENSIONS);
	%>

	<liferay-ui:message key="image-names-must-end-with-one-of-the-following-extensions" /> <%= StringUtil.merge(imageExtensions, ", ") %>.
</liferay-ui:error>

<liferay-ui:error exception="<%= ItemSmallImageSizeException.class %>" message="please-enter-a-file-with-a-valid-file-size" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="small-image-url" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="smallImageURL" />
	</td>
</tr>
<tr>
	<td>
		<span style="font-size: xx-small;">-- <%= LanguageUtil.get(pageContext, "or").toUpperCase() %> --</span> <liferay-ui:message key="small-image" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />smallFile" type="file" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="use-small-image" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="smallImage" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="medium-image-url" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="mediumImageURL" />
	</td>
</tr>
<tr>
	<td>
		<span style="font-size: xx-small;">-- <%= LanguageUtil.get(pageContext, "or").toUpperCase() %> --</span> <liferay-ui:message key="medium-image" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />mediumFile" type="file" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="use-medium-image" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="mediumImage" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="large-image-url" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="largeImageURL" />
	</td>
</tr>
<tr>
	<td>
		<span style="font-size: xx-small;">-- <%= LanguageUtil.get(pageContext, "or").toUpperCase() %> --</span> <liferay-ui:message key="large-image" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />largeFile" type="file" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="use-large-image" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= ShoppingItem.class %>" bean="<%= item %>" field="largeImage" />
	</td>
</tr>
</table>