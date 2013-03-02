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

package com.liferay.portlet.shopping.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.shopping.NoSuchCartException;
import com.liferay.portlet.shopping.model.ShoppingCart;
import com.liferay.portlet.shopping.model.ShoppingCartItem;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingItemField;
import com.liferay.portlet.shopping.model.ShoppingItemPrice;
import com.liferay.portlet.shopping.model.ShoppingOrder;
import com.liferay.portlet.shopping.model.ShoppingOrderItem;
import com.liferay.portlet.shopping.model.impl.ShoppingCartImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingCouponImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingItemPriceImpl;
import com.liferay.portlet.shopping.model.impl.ShoppingOrderImpl;
import com.liferay.portlet.shopping.service.ShoppingCartLocalServiceUtil;
import com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceUtil;
import com.liferay.portlet.shopping.service.ShoppingOrderItemLocalServiceUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemPriceUtil;
import com.liferay.portlet.shopping.util.comparator.ItemMinQuantityComparator;
import com.liferay.portlet.shopping.util.comparator.ItemNameComparator;
import com.liferay.portlet.shopping.util.comparator.ItemPriceComparator;
import com.liferay.portlet.shopping.util.comparator.ItemSKUComparator;
import com.liferay.portlet.shopping.util.comparator.OrderDateComparator;
import com.liferay.util.HttpUtil;
import com.liferay.util.MathUtil;

import java.text.NumberFormat;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.portlet.PortletRequest;
import javax.portlet.PortletSession;
import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

import javax.servlet.jsp.PageContext;

/**
 * <a href="ShoppingUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
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

		ShoppingPreferences prefs = null;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();

			ShoppingItem item = cartItem.getItem();

			if (prefs == null) {
				ShoppingCategory category = item.getCategory();

				prefs = ShoppingPreferences.getInstance(
					category.getCompanyId(), category.getGroupId());

				break;
			}
		}

		// Calculate alternative shipping if shopping is configured to use
		// alternative shipping and shipping price is greater than 0

		if ((prefs != null) &&
			(prefs.useAlternativeShipping()) && (shipping > 0)) {

			double altShippingDelta = 0.0;

			try {
				altShippingDelta = GetterUtil.getDouble(
					prefs.getAlternativeShipping()[1][altShipping]);
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
					 (categoryIdsSet.contains(
						new Long(item.getCategoryId())))) ||
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

		if (type.equals(ShoppingCouponImpl.DISCOUNT_TYPE_PERCENTAGE)) {
			discount = actualSubtotal * coupon.getDiscount();
		}
		else if (type.equals(ShoppingCouponImpl.DISCOUNT_TYPE_ACTUAL)) {
			discount = coupon.getDiscount();
		}
		else if (type.equals(ShoppingCouponImpl.DISCOUNT_TYPE_FREE_SHIPPING)) {
			discount = calculateShipping(items);
		}
		else if (type.equals(ShoppingCouponImpl.DISCOUNT_TYPE_TAX_FREE)) {
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

		ShoppingPreferences prefs = null;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
			Integer count = (Integer)entry.getValue();

			ShoppingItem item = cartItem.getItem();

			if (prefs == null) {
				ShoppingCategory category = item.getCategory();

				prefs = ShoppingPreferences.getInstance(
					category.getCompanyId(), category.getGroupId());
			}

			ShoppingItemPrice itemPrice =
				_getItemPrice(item, count.intValue());

			subtotal += calculateActualPrice(itemPrice) * count.intValue();
		}

		if ((prefs != null) && (subtotal > 0)) {
			double insuranceRate = 0.0;

			double[] range = ShoppingPreferences.INSURANCE_RANGE;

			for (int i = 0; i < range.length - 1; i++) {
				if (subtotal > range[i] && subtotal <= range[i + 1]) {
					int rangeId = i / 2;
					if (MathUtil.isOdd(i)) {
						rangeId = (i + 1) / 2;
					}

					insuranceRate = GetterUtil.getDouble(
						prefs.getInsurance()[rangeId]);
				}
			}

			String formula = prefs.getInsuranceFormula();

			if (formula.equals("flat")) {
				insurance += insuranceRate;
			}
			else if (formula.equals("percentage")) {
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

		ShoppingPreferences prefs = null;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
			Integer count = (Integer)entry.getValue();

			ShoppingItem item = cartItem.getItem();

			if (prefs == null) {
				ShoppingCategory category = item.getCategory();

				prefs = ShoppingPreferences.getInstance(
					category.getCompanyId(), category.getGroupId());
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

		if ((prefs != null) && (subtotal > 0)) {
			double shippingRate = 0.0;

			double[] range = ShoppingPreferences.SHIPPING_RANGE;

			for (int i = 0; i < range.length - 1; i++) {
				if (subtotal > range[i] && subtotal <= range[i + 1]) {
					int rangeId = i / 2;
					if (MathUtil.isOdd(i)) {
						rangeId = (i + 1) / 2;
					}

					shippingRate = GetterUtil.getDouble(
						prefs.getShipping()[rangeId]);
				}
			}

			String formula = prefs.getShippingFormula();

			if (formula.equals("flat")) {
				shipping += shippingRate;
			}
			else if (formula.equals("percentage")) {
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

		ShoppingPreferences prefs = null;

		Iterator itr = items.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();

			ShoppingItem item = cartItem.getItem();

			if (prefs == null) {
				ShoppingCategory category = item.getCategory();

				prefs = ShoppingPreferences.getInstance(
					category.getCompanyId(), category.getGroupId());

				break;
			}
		}

		if ((prefs != null) &&
			(prefs.getTaxState().equals(stateId))) {

			double subtotal = 0.0;

			itr = items.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				ShoppingCartItem cartItem = (ShoppingCartItem)entry.getKey();
				Integer count = (Integer)entry.getValue();

				ShoppingItem item = cartItem.getItem();

				if (item.isTaxable()) {
					subtotal += calculatePrice(item, count.intValue());
				}
			}

			tax = prefs.getTaxRate() * subtotal;
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

		List orderItems = ShoppingOrderItemLocalServiceUtil.getOrderItems(
			order.getOrderId());

		double total =
			calculateActualSubtotal(orderItems) + order.getTax() +
				order.getShipping() + order.getInsurance() -
					order.getCouponDiscount();

		if (total < 0) {
			total = 0.0;
		}

		return total;
	}

	public static String getBreadcrumbs(
			long categoryId, PageContext pageContext, RenderRequest req,
			RenderResponse res)
		throws Exception {

		ShoppingCategory category = null;

		try {
			category = ShoppingCategoryLocalServiceUtil.getCategory(categoryId);
		}
		catch (Exception e) {
		}

		return getBreadcrumbs(category, pageContext, req, res);
	}

	public static String getBreadcrumbs(
			ShoppingCategory category, PageContext pageContext,
			RenderRequest req, RenderResponse res)
		throws Exception {

		PortletURL categoriesURL = res.createRenderURL();

		WindowState windowState = req.getWindowState();

		if (windowState.equals(LiferayWindowState.POP_UP)) {
			categoriesURL.setWindowState(LiferayWindowState.POP_UP);

			categoriesURL.setParameter(
				"struts_action", "/shopping/select_category");
		}
		else {
			categoriesURL.setWindowState(WindowState.MAXIMIZED);

			categoriesURL.setParameter("struts_action", "/shopping/view");
			categoriesURL.setParameter("tabs1", "categories");
		}

		String categoriesLink =
			"<a href=\"" + categoriesURL.toString() + "\">" +
				LanguageUtil.get(pageContext, "categories") + "</a>";

		if (category == null) {
			return categoriesLink;
		}

		String breadcrumbs = StringPool.BLANK;

		if (category != null) {
			for (int i = 0;; i++) {
				category = category.toEscapedModel();

				PortletURL portletURL = res.createRenderURL();

				if (windowState.equals(LiferayWindowState.POP_UP)) {
					portletURL.setWindowState(LiferayWindowState.POP_UP);

					portletURL.setParameter(
						"struts_action", "/shopping/select_category");
					portletURL.setParameter(
						"categoryId", String.valueOf(category.getCategoryId()));
				}
				else {
					portletURL.setWindowState(WindowState.MAXIMIZED);

					portletURL.setParameter("struts_action", "/shopping/view");
					portletURL.setParameter("tabs1", "categories");
					portletURL.setParameter(
						"categoryId", String.valueOf(category.getCategoryId()));
				}

				String categoryLink =
					"<a href=\"" + portletURL.toString() + "\">" +
						category.getName() + "</a>";

				if (i == 0) {
					breadcrumbs = categoryLink;
				}
				else {
					breadcrumbs = categoryLink + " &raquo; " + breadcrumbs;
				}

				if (category.isRoot()) {
					break;
				}

				category = ShoppingCategoryLocalServiceUtil.getCategory(
					category.getParentCategoryId());
			}
		}

		breadcrumbs = categoriesLink + " &raquo; " + breadcrumbs;

		return breadcrumbs;
	}

	public static ShoppingCart getCart(ThemeDisplay themeDisplay) {
		ShoppingCart cart = new ShoppingCartImpl();

		cart.setGroupId(themeDisplay.getPortletGroupId());
		cart.setCompanyId(themeDisplay.getCompanyId());
		cart.setUserId(themeDisplay.getUserId());
		cart.setItemIds(StringPool.BLANK);
		cart.setCouponCodes(StringPool.BLANK);
		cart.setAltShipping(0);
		cart.setInsure(false);

		return cart;
	}

	public static ShoppingCart getCart(PortletRequest req)
		throws PortalException, SystemException {

		PortletSession ses = req.getPortletSession();

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		String sesCartId =
			ShoppingCart.class.getName() + themeDisplay.getPortletGroupId();

		if (themeDisplay.isSignedIn()) {
			ShoppingCart cart = (ShoppingCart)ses.getAttribute(sesCartId);

			if (cart != null) {
				ses.removeAttribute(sesCartId);
			}

			if ((cart != null) && (cart.getItemsSize() > 0)) {
				cart = ShoppingCartLocalServiceUtil.updateCart(
					themeDisplay.getUserId(), themeDisplay.getPortletGroupId(),
					cart.getItemIds(), cart.getCouponCodes(),
					cart.getAltShipping(), cart.isInsure());
			}
			else {
				try {
					cart = ShoppingCartLocalServiceUtil.getCart(
						themeDisplay.getUserId(),
						themeDisplay.getPortletGroupId());
				}
				catch (NoSuchCartException nsce) {
					cart = getCart(themeDisplay);

					cart = ShoppingCartLocalServiceUtil.updateCart(
						themeDisplay.getUserId(),
						themeDisplay.getPortletGroupId(), cart.getItemIds(),
						cart.getCouponCodes(), cart.getAltShipping(),
						cart.isInsure());
				}
			}

			return cart;
		}
		else {
			ShoppingCart cart = (ShoppingCart)ses.getAttribute(sesCartId);

			if (cart == null) {
				cart = getCart(themeDisplay);

				ses.setAttribute(sesCartId, cart);
			}

			return cart;
		}
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

	public static long getItemId(String itemId) {
		int pos = itemId.indexOf(StringPool.PIPE);

		if (pos != -1) {
			itemId = itemId.substring(0, pos);
		}

		return GetterUtil.getLong(itemId);
	}

	public static String getItemFields(String itemId) {
		int pos = itemId.indexOf(StringPool.PIPE);

		if (pos == -1) {
			return StringPool.BLANK;
		}
		else {
			return itemId.substring(pos + 1, itemId.length());
		}
	}

	public static OrderByComparator getItemOrderByComparator(
		String orderByCol, String orderByType) {

		boolean orderByAsc = false;

		if (orderByType.equals("asc")) {
			orderByAsc = true;
		}

		OrderByComparator orderByComparator = null;

		if (orderByCol.equals("min-qty")) {
			orderByComparator = new ItemMinQuantityComparator(orderByAsc);
		}
		else if (orderByCol.equals("name")) {
			orderByComparator = new ItemNameComparator(orderByAsc);
		}
		else if (orderByCol.equals("price")) {
			orderByComparator = new ItemPriceComparator(orderByAsc);
		}
		else if (orderByCol.equals("sku")) {
			orderByComparator = new ItemSKUComparator(orderByAsc);
		}
		else if (orderByCol.equals("order-date")) {
			orderByComparator = new OrderDateComparator(orderByAsc);
		}

		return orderByComparator;
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

	public static String getPayPalNotifyURL(ThemeDisplay themeDisplay) {
		return themeDisplay.getURLPortal() + themeDisplay.getPathMain() +
			"/shopping/notify";
	}

	public static String getPayPalRedirectURL(
			ShoppingPreferences prefs, ShoppingOrder order, double total,
			String returnURL, String notifyURL)
		throws PortalException, SystemException {

		String payPalEmailAddress = HttpUtil.encodeURL(
			prefs.getPayPalEmailAddress());

		NumberFormat doubleFormat = NumberFormat.getNumberInstance();

		doubleFormat.setMaximumFractionDigits(2);
		doubleFormat.setMinimumFractionDigits(2);

		String amount = doubleFormat.format(total);

		returnURL = HttpUtil.encodeURL(returnURL);
		notifyURL = HttpUtil.encodeURL(notifyURL);

		String firstName = HttpUtil.encodeURL(order.getBillingFirstName());
		String lastName = HttpUtil.encodeURL(order.getBillingLastName());
		String address1 = HttpUtil.encodeURL(order.getBillingStreet());
		String city = HttpUtil.encodeURL(order.getBillingCity());
		String state = HttpUtil.encodeURL(order.getBillingState());
		String zip = HttpUtil.encodeURL(order.getBillingZip());

		String currencyCode = prefs.getCurrencyId();

		StringMaker sm = new StringMaker();

		sm.append("https://www.paypal.com/cgi-bin/webscr?");
		sm.append("cmd=_xclick&");
		sm.append("business=").append(payPalEmailAddress).append("&");
		sm.append("item_name=").append(order.getOrderId()).append("&");
		sm.append("item_number=").append(order.getOrderId()).append("&");
		sm.append("invoice=").append(order.getOrderId()).append("&");
		sm.append("amount=").append(amount).append("&");
		sm.append("return=").append(returnURL).append("&");
		sm.append("notify_url=").append(notifyURL).append("&");
		sm.append("first_name=").append(firstName).append("&");
		sm.append("last_name=").append(lastName).append("&");
		sm.append("address1=").append(address1).append("&");
		sm.append("city=").append(city).append("&");
		sm.append("state=").append(state).append("&");
		sm.append("zip=").append(zip).append("&");
		sm.append("no_note=1&");
		sm.append("currency_code=").append(currencyCode).append("");

		return sm.toString();
	}

	public static String getPayPalReturnURL(
		PortletURL portletURL, ShoppingOrder order) {

		portletURL.setParameter(
			"struts_action", "/shopping/checkout");
		portletURL.setParameter(Constants.CMD, Constants.VIEW);
		portletURL.setParameter("orderId", String.valueOf(order.getOrderId()));

		return portletURL.toString();
	}

	public static String getPpPaymentStatus(String ppPaymentStatus) {
		if ((ppPaymentStatus == null) || (ppPaymentStatus.length() < 2) ||
			(ppPaymentStatus.equals("checkout"))) {

			return ShoppingOrderImpl.STATUS_CHECKOUT;
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

		if (ppPaymentStatus.equals(ShoppingOrderImpl.STATUS_CHECKOUT)) {
			ppPaymentStatus = "checkout";
		}
		else {
			ppPaymentStatus = ppPaymentStatus.toLowerCase();
		}

		return LanguageUtil.get(pageContext, ppPaymentStatus);
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
		String[] fieldsArray, Integer orderedQuantity) {

		if (!item.isFields()) {
			int stockQuantity = item.getStockQuantity();

			if ((stockQuantity > 0)  &&
			    (stockQuantity >= orderedQuantity.intValue())) {

				return true;
			}
			else {
				return false;
			}
		}
		else {
			int rowPos = getFieldsQuantitiesPos(item, itemFields, fieldsArray);

			String[] fieldsQuantities = item.getFieldsQuantitiesArray();

			int stockQuantity = GetterUtil.getInteger(fieldsQuantities[rowPos]);

			try {
				if ((stockQuantity > 0) &&
					(stockQuantity >= orderedQuantity.intValue())) {

					return true;
				}
			}
			catch (Exception e) {
			}

			return false;
		}
	}

	public static boolean meetsMinOrder(ShoppingPreferences prefs, Map items)
		throws PortalException, SystemException {

		if ((prefs.getMinOrder() > 0) &&
			(calculateSubtotal(items) < prefs.getMinOrder())) {

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
					ShoppingItemPriceImpl.STATUS_INACTIVE) &&
				(count >= minQty) && (count < maxQty || maxQty == 0))  {

				itemPrice = temp;
			}
		}

		if (itemPrice == null) {
			return ShoppingItemPriceUtil.create(0);
		}

		return itemPrice;
	}

}