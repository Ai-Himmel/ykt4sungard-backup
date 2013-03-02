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

package com.liferay.portlet.shopping.action;

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingOrder;
import com.liferay.portlet.shopping.model.impl.ShoppingCategoryImpl;
import com.liferay.portlet.shopping.service.ShoppingCategoryServiceUtil;
import com.liferay.portlet.shopping.service.ShoppingCouponServiceUtil;
import com.liferay.portlet.shopping.service.ShoppingItemServiceUtil;
import com.liferay.portlet.shopping.service.ShoppingOrderServiceUtil;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActionUtil {

	public static void getCategory(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getCategory(httpReq);
	}

	public static void getCategory(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getCategory(httpReq);
	}

	public static void getCategory(HttpServletRequest req) throws Exception {
		long categoryId = ParamUtil.getLong(req, "categoryId");

		ShoppingCategory category = null;

		if ((categoryId > 0) &&
			(categoryId != ShoppingCategoryImpl.DEFAULT_PARENT_CATEGORY_ID)) {

			category = ShoppingCategoryServiceUtil.getCategory(categoryId);
		}

		req.setAttribute(WebKeys.SHOPPING_CATEGORY, category);
	}

	public static void getCoupon(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getCoupon(httpReq);
	}

	public static void getCoupon(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getCoupon(httpReq);
	}

	public static void getCoupon(HttpServletRequest req) throws Exception {
		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long couponId = ParamUtil.getLong(req, "couponId");

		ShoppingCoupon coupon = null;

		if (couponId > 0) {
			coupon = ShoppingCouponServiceUtil.getCoupon(
				themeDisplay.getPlid(), couponId);
		}

		req.setAttribute(WebKeys.SHOPPING_COUPON, coupon);
	}

	public static void getItem(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getItem(httpReq);
	}

	public static void getItem(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getItem(httpReq);
	}

	public static void getItem(HttpServletRequest req) throws Exception {
		long itemId = ParamUtil.getLong(req, "itemId");

		ShoppingItem item = null;

		if (itemId > 0) {
			item = ShoppingItemServiceUtil.getItem(itemId);
		}

		req.setAttribute(WebKeys.SHOPPING_ITEM, item);
	}

	public static void getOrder(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getOrder(httpReq);
	}

	public static void getOrder(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getOrder(httpReq);
	}

	public static void getOrder(HttpServletRequest req) throws Exception {
		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long orderId = ParamUtil.getLong(req, "orderId");

		ShoppingOrder order = null;

		if (orderId > 0) {
			order = ShoppingOrderServiceUtil.getOrder(
				themeDisplay.getPlid(), orderId);
		}

		req.setAttribute(WebKeys.SHOPPING_ORDER, order);
	}

}