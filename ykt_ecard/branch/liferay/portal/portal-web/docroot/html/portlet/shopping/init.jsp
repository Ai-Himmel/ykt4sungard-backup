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

<%@ include file="/html/portlet/init.jsp" %>

<%@ page import="com.liferay.portlet.shopping.BillingCityException" %>
<%@ page import="com.liferay.portlet.shopping.BillingCountryException" %>
<%@ page import="com.liferay.portlet.shopping.BillingEmailAddressException" %>
<%@ page import="com.liferay.portlet.shopping.BillingFirstNameException" %>
<%@ page import="com.liferay.portlet.shopping.BillingLastNameException" %>
<%@ page import="com.liferay.portlet.shopping.BillingPhoneException" %>
<%@ page import="com.liferay.portlet.shopping.BillingStateException" %>
<%@ page import="com.liferay.portlet.shopping.BillingStreetException" %>
<%@ page import="com.liferay.portlet.shopping.BillingZipException" %>
<%@ page import="com.liferay.portlet.shopping.CartMinQuantityException" %>
<%@ page import="com.liferay.portlet.shopping.CategoryNameException" %>
<%@ page import="com.liferay.portlet.shopping.CCExpirationException" %>
<%@ page import="com.liferay.portlet.shopping.CCNameException" %>
<%@ page import="com.liferay.portlet.shopping.CCNumberException" %>
<%@ page import="com.liferay.portlet.shopping.CCTypeException" %>
<%@ page import="com.liferay.portlet.shopping.CouponActiveException" %>
<%@ page import="com.liferay.portlet.shopping.CouponCodeException" %>
<%@ page import="com.liferay.portlet.shopping.CouponDateException" %>
<%@ page import="com.liferay.portlet.shopping.CouponDescriptionException" %>
<%@ page import="com.liferay.portlet.shopping.CouponEndDateException" %>
<%@ page import="com.liferay.portlet.shopping.CouponLimitCategoriesException" %>
<%@ page import="com.liferay.portlet.shopping.CouponLimitSKUsException" %>
<%@ page import="com.liferay.portlet.shopping.CouponNameException" %>
<%@ page import="com.liferay.portlet.shopping.CouponStartDateException" %>
<%@ page import="com.liferay.portlet.shopping.DuplicateCouponCodeException" %>
<%@ page import="com.liferay.portlet.shopping.DuplicateItemSKUException" %>
<%@ page import="com.liferay.portlet.shopping.ItemLargeImageNameException" %>
<%@ page import="com.liferay.portlet.shopping.ItemLargeImageSizeException" %>
<%@ page import="com.liferay.portlet.shopping.ItemMediumImageNameException" %>
<%@ page import="com.liferay.portlet.shopping.ItemMediumImageSizeException" %>
<%@ page import="com.liferay.portlet.shopping.ItemNameException" %>
<%@ page import="com.liferay.portlet.shopping.ItemSKUException" %>
<%@ page import="com.liferay.portlet.shopping.ItemSmallImageNameException" %>
<%@ page import="com.liferay.portlet.shopping.ItemSmallImageSizeException" %>
<%@ page import="com.liferay.portlet.shopping.NoSuchCategoryException" %>
<%@ page import="com.liferay.portlet.shopping.NoSuchCouponException" %>
<%@ page import="com.liferay.portlet.shopping.NoSuchItemException" %>
<%@ page import="com.liferay.portlet.shopping.NoSuchOrderException" %>
<%@ page import="com.liferay.portlet.shopping.ShippingCityException" %>
<%@ page import="com.liferay.portlet.shopping.ShippingCountryException" %>
<%@ page import="com.liferay.portlet.shopping.ShippingEmailAddressException" %>
<%@ page import="com.liferay.portlet.shopping.ShippingFirstNameException" %>
<%@ page import="com.liferay.portlet.shopping.ShippingLastNameException" %>
<%@ page import="com.liferay.portlet.shopping.ShippingPhoneException" %>
<%@ page import="com.liferay.portlet.shopping.ShippingStateException" %>
<%@ page import="com.liferay.portlet.shopping.ShippingStreetException" %>
<%@ page import="com.liferay.portlet.shopping.ShippingZipException" %>
<%@ page import="com.liferay.portlet.shopping.model.ShoppingCart" %>
<%@ page import="com.liferay.portlet.shopping.model.ShoppingCartItem" %>
<%@ page import="com.liferay.portlet.shopping.model.ShoppingCategory" %>
<%@ page import="com.liferay.portlet.shopping.model.ShoppingCoupon" %>
<%@ page import="com.liferay.portlet.shopping.model.ShoppingItem" %>
<%@ page import="com.liferay.portlet.shopping.model.ShoppingItemField" %>
<%@ page import="com.liferay.portlet.shopping.model.ShoppingItemPrice" %>
<%@ page import="com.liferay.portlet.shopping.model.ShoppingOrder" %>
<%@ page import="com.liferay.portlet.shopping.model.ShoppingOrderItem" %>
<%@ page import="com.liferay.portlet.shopping.model.impl.ShoppingCategoryImpl" %>
<%@ page import="com.liferay.portlet.shopping.model.impl.ShoppingCouponImpl" %>
<%@ page import="com.liferay.portlet.shopping.model.impl.ShoppingItemPriceImpl" %>
<%@ page import="com.liferay.portlet.shopping.model.impl.ShoppingOrderImpl" %>
<%@ page import="com.liferay.portlet.shopping.search.CouponDisplayTerms" %>
<%@ page import="com.liferay.portlet.shopping.search.CouponSearch" %>
<%@ page import="com.liferay.portlet.shopping.search.CouponSearchTerms" %>
<%@ page import="com.liferay.portlet.shopping.search.OrderDisplayTerms" %>
<%@ page import="com.liferay.portlet.shopping.search.OrderSearch" %>
<%@ page import="com.liferay.portlet.shopping.search.OrderSearchTerms" %>
<%@ page import="com.liferay.portlet.shopping.service.ShoppingCartLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.shopping.service.ShoppingCategoryLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.shopping.service.ShoppingCouponLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.shopping.service.ShoppingCouponServiceUtil" %>
<%@ page import="com.liferay.portlet.shopping.service.ShoppingItemFieldLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.shopping.service.ShoppingItemLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.shopping.service.ShoppingItemPriceLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.shopping.service.ShoppingOrderItemLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.shopping.service.ShoppingOrderLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.shopping.service.permission.ShoppingCategoryPermission" %>
<%@ page import="com.liferay.portlet.shopping.service.permission.ShoppingItemPermission" %>
<%@ page import="com.liferay.portlet.shopping.service.permission.ShoppingOrderPermission" %>
<%@ page import="com.liferay.portlet.shopping.util.ShoppingPreferences" %>
<%@ page import="com.liferay.portlet.shopping.util.ShoppingUtil" %>

<%
PortalPreferences portalPrefs = PortletPreferencesFactoryUtil.getPortalPreferences(request);

ShoppingPreferences shoppingPrefs = ShoppingPreferences.getInstance(company.getCompanyId(), portletGroupId.longValue());

Currency currency = Currency.getInstance(shoppingPrefs.getCurrencyId());

NumberFormat currencyFormat = NumberFormat.getCurrencyInstance(locale);

currencyFormat.setCurrency(currency);

DateFormat dateFormatDateTime = DateFormats.getDateTime(locale, timeZone);

NumberFormat doubleFormat = NumberFormat.getNumberInstance(locale);

doubleFormat.setMaximumFractionDigits(2);
doubleFormat.setMinimumFractionDigits(2);

NumberFormat percentFormat = NumberFormat.getPercentInstance(locale);

NumberFormat taxFormat = NumberFormat.getPercentInstance(locale);

taxFormat.setMinimumFractionDigits(3);
%>