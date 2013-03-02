/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.shopping.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.language.LanguageUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.admin.model.ShoppingConfig;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
import com.liferay.portlet.shopping.model.ShoppingCartItem;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingItemField;
import com.liferay.portlet.shopping.model.ShoppingItemPrice;
import com.liferay.portlet.shopping.model.ShoppingOrder;
import com.liferay.portlet.shopping.model.ShoppingOrderItem;
import com.liferay.portlet.shopping.service.spring.ShoppingCategoryServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingOrderItemServiceUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.Http;
import com.liferay.util.MathUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;

import java.text.NumberFormat;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.portlet.PortletURL;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.PageContext;

/**
 * <a href="ShoppingUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.44 $
 *
 */
public class ShoppingUtil {

	public static double calculateActualPrice(ShoppingItem item) {
		return item.getPrice() - calculateDiscountPrice(item);
	}

	public static double calculateActualPrice(ShoppingItem item, int count)
		throws PortalException, SystemException {

		return calculatePrice(item, count) -
			calculateDiscountPrice(item, count);
	}

	public static double calculateActualPrice(ShoppingItemPrice itemPrice) {
		return itemPrice.getPrice() - calculateDiscountPrice(itemPrice);
	}

	public static double calculateActualSubtotal(Map items)
		throws PortalException, SystemException {

		return calculateSubtotal(items) - calculateDiscountSubtotal(items);
	}

	public static double calculateActualSubtotal(List orderItems) {
		double subtotal = 0.0;

		Iterator itr = orderItems.iterator();

		while (itr.hasNext()) {
			ShoppingOrderItem orderItem = (ShoppingOrderItem)itr.next();

			subtotal += orderItem.getPrice() * orderItem.getQuantity();
		}

		return subtotal;
	}

	public static double calculateAlternativeShipping(
			Map items, int altShipping)
		throws PortalException, SystemException {

		double shipping = calculateShipping(items);
		double alternativeShipping = shipping;

		ShoppingConfig shoppingConfig = null;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();

			ShoppingItem item = cartItem.getItem();

			if (shoppingConfig == null) {
				shoppingConfig = AdminConfigServiceUtil.getShoppingConfig(
					item.getCompanyId());

				break;
			}
		}

		// Calculate alternative shipping if shopping is configured to use
		// alternative shipping and shipping price is greater than 0

		if ((shoppingConfig != null) &&
			(shoppingConfig.useAlternativeShipping()) && (shipping > 0)) {

			double altShippingDelta = 0.0;

			try {
				altShippingDelta = GetterUtil.getDouble(
					shoppingConfig.getAlternativeShipping()[1][altShipping]);
			}
			catch (Exception e) {
				return alternativeShipping;
			}

			if (altShippingDelta > 0) {
				alternativeShipping = shipping * altShippingDelta;
			}
		}

		return alternativeShipping;
	}

	public static double calculateCouponDiscount(
			Map items, ShoppingCoupon coupon)
		throws PortalException, SystemException {

		return calculateCouponDiscount(items, null, coupon);
	}

	public static double calculateCouponDiscount(
			Map items, String stateId, ShoppingCoupon coupon)
		throws PortalException, SystemException {

		double discount = 0.0;

		if ((coupon == null) || !coupon.isActive() ||
			!coupon.hasValidDateRange()) {

			return discount;
		}

		String[] categoryIds = StringUtil.split(coupon.getLimitCategories());
		String[] skus = StringUtil.split(coupon.getLimitSkus());

		if ((categoryIds.length > 0) || (skus.length > 0)) {
			Set categoryIdsSet = new HashSet();

			for (int i = 0; i < categoryIds.length; i++) {
				categoryIdsSet.add(categoryIds[i]);
			}

			Set skusSet = new HashSet();

			for (int i = 0; i < skus.length; i++) {
				skusSet.add(skus[i]);
			}

			Map newItems = new HashMap();

			Iterator itr = items.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
				Integer count = (Integer)entry.getValue();

				ShoppingItem item = cartItem.getItem();

				if (((categoryIdsSet.size() > 0) &&
					 (categoryIdsSet.contains(item.getCategoryId()))) ||
					((skusSet.size() > 0) &&
					 (skusSet.contains(item.getSku())))) {

					newItems.put(cartItem, count);
				}
			}

			items = newItems;
		}

		double actualSubtotal = calculateActualSubtotal(items);

		if ((coupon.getMinOrder() > 0) &&
			(coupon.getMinOrder() > actualSubtotal)) {

			return discount;
		}

		String type = coupon.getDiscountType();

		if (type.equals(ShoppingCoupon.DISCOUNT_TYPE_PERCENTAGE)) {
			discount = actualSubtotal * coupon.getDiscount();
		}
		else if (type.equals(ShoppingCoupon.DISCOUNT_TYPE_ACTUAL)) {
			discount = coupon.getDiscount();
		}
		else if (type.equals(ShoppingCoupon.DISCOUNT_TYPE_FREE_SHIPPING)) {
			discount = calculateShipping(items);
		}
		else if (type.equals(ShoppingCoupon.DISCOUNT_TYPE_TAX_FREE)) {
			if (stateId != null) {
				discount = calculateTax(items, stateId);
			}
		}

		return discount;
	}

	public static double calculateDiscountPercent(Map items)
		throws PortalException, SystemException {

		double discount =
			calculateDiscountSubtotal(items) / calculateSubtotal(items);

		if (Double.isNaN(discount) || Double.isInfinite(discount)) {
			discount = 0.0;
		}

		return discount;
	}

	public static double calculateDiscountPrice(ShoppingItem item) {
		return item.getPrice() * item.getDiscount();
	}

	public static double calculateDiscountPrice(ShoppingItem item, int count)
		throws PortalException, SystemException {

		ShoppingItemPrice itemPrice = _getItemPrice(item, count);

		return itemPrice.getPrice() * itemPrice.getDiscount() * count;
	}

	public static double calculateDiscountPrice(ShoppingItemPrice itemPrice) {
		return itemPrice.getPrice() * itemPrice.getDiscount();
	}

	public static double calculateDiscountSubtotal(Map items)
		throws PortalException, SystemException {

		double subtotal = 0.0;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
			Integer count = (Integer)entry.getValue();

			ShoppingItem item = cartItem.getItem();

			subtotal += calculateDiscountPrice(item, count.intValue());
		}

		return subtotal;
	}

	public static double calculateInsurance(Map items)
		throws PortalException, SystemException {

		double insurance = 0.0;
		double subtotal = 0.0;

		ShoppingConfig shoppingConfig = null;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
			Integer count = (Integer)entry.getValue();

			ShoppingItem item = cartItem.getItem();

			if (shoppingConfig == null) {
				shoppingConfig = AdminConfigServiceUtil.getShoppingConfig(
					item.getCompanyId());
			}

			ShoppingItemPrice itemPrice =
				_getItemPrice(item, count.intValue());

			subtotal += calculateActualPrice(itemPrice) * count.intValue();
		}

		if (shoppingConfig != null && subtotal > 0) {
			double insuranceRate = 0.0;

			double[] range = ShoppingConfig.INSURANCE_RANGE;

			for (int i = 0; i < range.length - 1; i++) {
				if (subtotal > range[i] && subtotal <= range[i + 1]) {
					int rangeId = i / 2;
					if (MathUtil.isOdd(i)) {
						rangeId = (i + 1) / 2;
					}

					insuranceRate = GetterUtil.get(
						shoppingConfig.getInsurance()[rangeId], 0.0);
				}
			}

			String formula = shoppingConfig.getInsuranceFormula();

			if (formula.equals(ShoppingConfig.INSURANCE_FLAT_AMOUNT)) {
				insurance += insuranceRate;
			}
			else if (formula.equals(ShoppingConfig.INSURANCE_PERCENTAGE)) {
				insurance += subtotal * insuranceRate;
			}
		}

		return insurance;
	}

	public static double calculatePrice(ShoppingItem item, int count)
		throws PortalException, SystemException {

		ShoppingItemPrice itemPrice = _getItemPrice(item, count);

		return itemPrice.getPrice() * count;
	}

	public static double calculateShipping(Map items)
		throws PortalException, SystemException {

		double shipping = 0.0;
		double subtotal = 0.0;

		ShoppingConfig shoppingConfig = null;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
			Integer count = (Integer)entry.getValue();

			ShoppingItem item = cartItem.getItem();

			if (shoppingConfig == null) {
				shoppingConfig = AdminConfigServiceUtil.getShoppingConfig(
					item.getCompanyId());
			}

			if (item.isRequiresShipping()) {
				ShoppingItemPrice itemPrice =
					_getItemPrice(item, count.intValue());

				if (itemPrice.isUseShippingFormula()) {
					subtotal +=
						calculateActualPrice(itemPrice) * count.intValue();
				}
				else {
					shipping += itemPrice.getShipping() * count.intValue();
				}
			}
		}

		if (shoppingConfig != null && subtotal > 0) {
			double shippingRate = 0.0;

			double[] range = ShoppingConfig.SHIPPING_RANGE;

			for (int i = 0; i < range.length - 1; i++) {
				if (subtotal > range[i] && subtotal <= range[i + 1]) {
					int rangeId = i / 2;
					if (MathUtil.isOdd(i)) {
						rangeId = (i + 1) / 2;
					}

					shippingRate = GetterUtil.get(
						shoppingConfig.getShipping()[rangeId], 0.0);
				}
			}

			String formula = shoppingConfig.getShippingFormula();

			if (formula.equals(ShoppingConfig.SHIPPING_FLAT_AMOUNT)) {
				shipping += shippingRate;
			}
			else if (formula.equals(ShoppingConfig.SHIPPING_PERCENTAGE)) {
				shipping += subtotal * shippingRate;
			}
		}

		return shipping;
	}

	public static double calculateSubtotal(Map items)
		throws PortalException, SystemException {

		double subtotal = 0.0;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
			Integer count = (Integer)entry.getValue();

			ShoppingItem item = cartItem.getItem();

			subtotal += calculatePrice(item, count.intValue());
		}

		return subtotal;
	}

	public static double calculateTax(Map items, String stateId)
		throws PortalException, SystemException {

		double tax = 0.0;

		ShoppingConfig shoppingConfig = null;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();

			ShoppingItem item = cartItem.getItem();

			if (shoppingConfig == null) {
				shoppingConfig = AdminConfigServiceUtil.getShoppingConfig(
					item.getCompanyId());

				break;
			}
		}

		if (shoppingConfig != null) {
			if (shoppingConfig.getTaxState().equals(stateId)) {
				double subtotal = 0.0;

				itr = items.entrySet().iterator();

				while (itr.hasNext()) {
					Map.Entry entry = (Map.Entry)itr.next();

					ShoppingCartItem cartItem =
						(ShoppingCartItem)entry.getKey();
					Integer count = (Integer)entry.getValue();

					ShoppingItem item = cartItem.getItem();

					if (item.isTaxable()) {
						subtotal += calculatePrice(item, count.intValue());
					}
				}

				tax = shoppingConfig.getTaxRate() * subtotal;
			}
		}

		return tax;
	}

	public static double calculateTotal(
			Map items, String stateId, ShoppingCoupon coupon, int altShipping,
			boolean insure)
		throws PortalException, SystemException {

		double actualSubtotal = calculateActualSubtotal(items);
		double tax = calculateTax(items, stateId);
		double shipping = calculateAlternativeShipping(items, altShipping);

		double insurance = 0.0;
		if (insure) {
			insurance = calculateInsurance(items);
		}

		double couponDiscount = calculateCouponDiscount(items, stateId, coupon);

		double total =
			actualSubtotal + tax + shipping + insurance - couponDiscount;

		if (total < 0) {
			total = 0.0;
		}

		return total;
	}

	public static double calculateTotal(ShoppingOrder order)
		throws PortalException, SystemException {

		List orderItems =
			ShoppingOrderItemServiceUtil.getOrderItems(order.getOrderId());

		double total =
			calculateActualSubtotal(orderItems) + order.getTax() +
				order.getShipping() + order.getInsurance() -
					order.getCouponDiscount();

		if (total < 0) {
			total = 0.0;
		}

		return total;
	}

	public static int getFieldsQuantitiesPos(
		ShoppingItem item, ShoppingItemField[] itemFields,
		String[] fieldsArray) {

		Set fieldsValues = new HashSet();
		for (int i = 0; i < fieldsArray.length; i++) {
			int pos = fieldsArray[i].indexOf("=");

			String fieldValue = fieldsArray[i].substring(
				pos + 1, fieldsArray[i].length()).trim();

			fieldsValues.add(fieldValue);
		}

		List names = new ArrayList();
		List values = new ArrayList();

		for (int i = 0; i < itemFields.length; i++) {
			names.add(itemFields[i].getName());
			values.add(StringUtil.split(itemFields[i].getValues()));
		}

		int numOfRows = 1;
		for (int i = 0; i < values.size(); i++) {
			String[] vArray = (String[])values.get(i);

			numOfRows = numOfRows * vArray.length;
		}

		int rowPos = 0;

		for (int i = 0; i < numOfRows; i++) {
			boolean match = true;

			for (int j = 0; j < names.size(); j++) {
				int numOfRepeats = 1;

				for (int k = j + 1; k < values.size(); k++) {
					String[] vArray = (String[])values.get(k);

					numOfRepeats = numOfRepeats * vArray.length;
				}

				String[] vArray = (String[])values.get(j);

				int arrayPos;
				for (arrayPos = i / numOfRepeats;
					 arrayPos >= vArray.length;
					 arrayPos = arrayPos - vArray.length) {
				}

				if (!fieldsValues.contains(vArray[arrayPos].trim())) {
					match = false;

					break;
				}
			}

			if (match) {
				rowPos = i;

				break;
			}
		}

		return rowPos;
	}

	public static String getItemId(String itemId) {
		int pos = itemId.indexOf("|");

		if (pos == -1) {
			return itemId;
		}
		else {
			return itemId.substring(0, pos);
		}
	}

	public static String getItemFields(String itemId) {
		int pos = itemId.indexOf("|");

		if (pos == -1) {
			return StringPool.BLANK;
		}
		else {
			return itemId.substring(pos + 1, itemId.length());
		}
	}

	public static int getMinQuantity(ShoppingItem item)
		throws PortalException, SystemException {

		int minQuantity = item.getMinQuantity();

		List itemPrices = item.getItemPrices();

		for (int i = 0; i < itemPrices.size(); i++) {
			ShoppingItemPrice itemPrice =
				(ShoppingItemPrice)itemPrices.get(i);

			if (minQuantity > itemPrice.getMinQuantity()) {
				minQuantity = itemPrice.getMinQuantity();
			}
		}

		return minQuantity;
	}

	public static String getNavCategories(
			HttpServletRequest req, PageContext pageContext,
			String className, PortletURL categoriesURL, PortletURL categoryURL)
		throws PortalException, SystemException {

		ShoppingCategory category =
			(ShoppingCategory)req.getAttribute(WebKeys.SHOPPING_CATEGORY);

		FastStringBuffer boxTitleSB = new FastStringBuffer();

		boxTitleSB.append("<a class=\"");
		boxTitleSB.append(className);
		boxTitleSB.append("\" href=\"");
		boxTitleSB.append(categoriesURL.toString());
		boxTitleSB.append("\">");
		boxTitleSB.append(LanguageUtil.get(pageContext, "browse-categories"));
		boxTitleSB.append("</a>");

		List parentCategories =
			ShoppingCategoryServiceUtil.getParentCategories(category);

		for (int i = 0; i < parentCategories.size(); i++) {
			ShoppingCategory parentCategory =
				(ShoppingCategory)parentCategories.get(i);

			boxTitleSB.append("&nbsp;&nbsp;");
			boxTitleSB.append("<span class=\"");
			boxTitleSB.append(className);
			boxTitleSB.append("-neg-alert\">");
			boxTitleSB.append("&raquo;</span>");
			boxTitleSB.append("&nbsp;&nbsp;");

			if (i + 1 < parentCategories.size()) {
				categoryURL.setParameter(
					"category_id", parentCategory.getCategoryId());

				boxTitleSB.append("<a class=\"");
				boxTitleSB.append(className);
				boxTitleSB.append("\" href=\"");
				boxTitleSB.append(categoryURL.toString());
				boxTitleSB.append("\">");
				boxTitleSB.append(parentCategory.getName());
				boxTitleSB.append("</a>");
			}
			else if (i + 1 == parentCategories.size()) {
				boxTitleSB.append("<b>");
				boxTitleSB.append(parentCategory.getName());
				boxTitleSB.append("</b>");
			}
		}

		return boxTitleSB.toString();
	}

	public static String getPayPalNotifyURL(Company company, String mainPath) {
		return "http://" + company.getPortalURL() + mainPath +
			"/shopping/notify";
	}

	public static String getPayPalRedirectURL(
			ShoppingConfig shoppingConfig, ShoppingOrder order, double total,
			String returnURL, String notifyURL)
		throws PortalException, SystemException {

		String payPalEmailAddress = Http.encodeURL(
			shoppingConfig.getPayPalEmailAddress());

		NumberFormat doubleFormat = NumberFormat.getNumberInstance();
		doubleFormat.setMaximumFractionDigits(2);
		doubleFormat.setMinimumFractionDigits(2);

		String amount = doubleFormat.format(total);

		returnURL = Http.encodeURL(returnURL);
		notifyURL = Http.encodeURL(notifyURL);

		String firstName = Http.encodeURL(order.getBillingFirstName());
		String lastName = Http.encodeURL(order.getBillingLastName());
		String address1 = Http.encodeURL(order.getBillingStreet());
		String city = Http.encodeURL(order.getBillingCity());
		String state = Http.encodeURL(order.getBillingState());
		String zip = Http.encodeURL(order.getBillingZip());

		String currencyCode = shoppingConfig.getCurrencyId();

		FastStringBuffer sb = new FastStringBuffer();

		sb.append("https://www.paypal.com/cgi-bin/webscr?");
		sb.append("cmd=_xclick&");
		sb.append("business=").append(payPalEmailAddress).append("&");
		sb.append("item_name=").append(order.getOrderId()).append("&");
		sb.append("item_number=").append(order.getOrderId()).append("&");
		sb.append("invoice=").append(order.getOrderId()).append("&");
		sb.append("amount=").append(amount).append("&");
		sb.append("return=").append(returnURL).append("&");
		sb.append("notify_url=").append(notifyURL).append("&");
		sb.append("first_name=").append(firstName).append("&");
		sb.append("last_name=").append(lastName).append("&");
		sb.append("address1=").append(address1).append("&");
		sb.append("city=").append(city).append("&");
		sb.append("state=").append(state).append("&");
		sb.append("zip=").append(zip).append("&");
		sb.append("no_note=1&");
		sb.append("currency_code=").append(currencyCode).append("");

		return sb.toString();
	}

	public static String getPayPalReturnURL(
		PortletURL portletURL, ShoppingOrder order) {

		portletURL.setParameter(
			"struts_action", "/shopping/checkout");
		portletURL.setParameter(Constants.CMD, Constants.VIEW);
		portletURL.setParameter("order_id", order.getOrderId());

		return portletURL.toString();
	}

	public static String getPpPaymentStatus(String ppPaymentStatus) {
		if ((ppPaymentStatus == null) || (ppPaymentStatus.length() < 2) ||
			(ppPaymentStatus.equals("checkout"))) {

			return ShoppingOrder.STATUS_CHECKOUT;
		}
		else {
			return Character.toUpperCase(ppPaymentStatus.charAt(0)) +
				ppPaymentStatus.substring(1, ppPaymentStatus.length());
		}
	}

	public static String getPpPaymentStatus(
			ShoppingOrder order, PageContext pageContext)
		throws PortalException {

		String ppPaymentStatus = order.getPpPaymentStatus();

		if (ppPaymentStatus.equals(ShoppingOrder.STATUS_CHECKOUT)) {
			ppPaymentStatus = "checkout";
		}
		else {
			ppPaymentStatus = ppPaymentStatus.toLowerCase();
		}

		return LanguageUtil.get(pageContext, ppPaymentStatus);
	}

	public static Set getSupplierUserIds(List orderItems) {
		Set supplierUserIds = new LinkedHashSet();

		Iterator itr = orderItems.iterator();

		while (itr.hasNext()) {
			ShoppingOrderItem orderItem = (ShoppingOrderItem)itr.next();

			String supplierUserId = orderItem.getSupplierUserId();

			if ((Validator.isNotNull(supplierUserId)) &&
				(!supplierUserIds.contains(supplierUserId))) {

				supplierUserIds.add(supplierUserId);
			}
		}

		return supplierUserIds;
	}

	public static boolean isInStock(ShoppingItem item) {
		if (!item.isFields()) {
			if (item.getStockQuantity() > 0) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			String[] fieldsQuantities = item.getFieldsQuantitiesArray();

			for (int i = 0; i < fieldsQuantities.length; i++) {
				if (GetterUtil.getInteger(fieldsQuantities[i]) > 0) {
					return true;
				}
			}

			return false;
		}
	}

	public static boolean isInStock(
		ShoppingItem item, ShoppingItemField[] itemFields,
		String[] fieldsArray) {

		if (!item.isFields()) {
			if (item.getStockQuantity() > 0) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			int rowPos = getFieldsQuantitiesPos(item, itemFields, fieldsArray);

			String[] fieldsQuantities = item.getFieldsQuantitiesArray();

			try {
				if (GetterUtil.getInteger(fieldsQuantities[rowPos]) > 0) {
					return true;
				}
			}
			catch (Exception e) {
			}

			return false;
		}
	}

	public static boolean meetsMinOrder(
			ShoppingConfig shoppingConfig, Map items)
		throws PortalException, SystemException {

		if ((shoppingConfig.getMinOrder() > 0) &&
			(calculateSubtotal(items) < shoppingConfig.getMinOrder())) {

			return false;
		}
		else {
			return true;
		}
	}

	private static ShoppingItemPrice _getItemPrice(ShoppingItem item, int count)
		throws PortalException, SystemException {

		ShoppingItemPrice itemPrice = null;

		List itemPrices = item.getItemPrices();

		for (int i = 0; i < itemPrices.size(); i++) {
			ShoppingItemPrice temp =
				(ShoppingItemPrice)itemPrices.get(i);

			int minQty = temp.getMinQuantity();
			int maxQty = temp.getMaxQuantity();

			if ((temp.getStatus() !=
					ShoppingItemPrice.STATUS_INACTIVE) &&
				(count >= minQty) && (count < maxQty || maxQty == 0))  {

				itemPrice = temp;
			}
		}

		if (itemPrice == null) {
			return new ShoppingItemPrice(null);
		}

		return itemPrice;
	}

}