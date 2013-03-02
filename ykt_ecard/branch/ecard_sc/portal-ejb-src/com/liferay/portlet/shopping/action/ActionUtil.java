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

package com.liferay.portlet.shopping.action;

import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.shopping.model.ShoppingCart;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.model.ShoppingOrder;
import com.liferay.portlet.shopping.service.spring.ShoppingCartServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingItemServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingOrderServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletSession;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class ActionUtil {

	public static void getItem(ActionRequest req) throws Exception {
		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();

		getItem(httpReq);
	}

	public static void getItem(RenderRequest req) throws Exception {
		HttpServletRequest httpReq =
			((RenderRequestImpl)req).getHttpServletRequest();

		getItem(httpReq);
	}

	public static void getItem(HttpServletRequest req) throws Exception {
		String itemId = ParamUtil.getString(req, "item_id");

		ShoppingItem item = null;

		if (Validator.isNotNull(itemId)) {
			item = ShoppingItemServiceUtil.getItemById(itemId);
		}

		req.setAttribute(WebKeys.SHOPPING_ITEM, item);
	}

	public static void getOrder(ActionRequest req) throws Exception {
		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();

		getOrder(httpReq);
	}

	public static void getOrder(RenderRequest req) throws Exception {
		HttpServletRequest httpReq =
			((RenderRequestImpl)req).getHttpServletRequest();

		getOrder(httpReq);
	}

	public static void getOrder(HttpServletRequest req) throws Exception {
		String orderId = ParamUtil.getString(req, "order_id");

		ShoppingOrder order = ShoppingOrderServiceUtil.getOrder(orderId);

		req.setAttribute(WebKeys.SHOPPING_ORDER, order);
	}

	public static void updateCart(ActionRequest req, ActionResponse res)
		throws Exception {

		PortletSession ses = req.getPortletSession();

		String companyId = PortalUtil.getCompanyId(req);

		String cmd = ParamUtil.getString(req, "shopping_" + Constants.CMD);

		ShoppingCart cart =
			ShoppingCartServiceUtil.getCart(ses.getId(), companyId);

		if (cmd.equals(Constants.ADD)) {
			String itemId = ParamUtil.getString(req, "item_id");

			String fields = ParamUtil.getString(req, "item_fields");
			if (Validator.isNotNull(fields)) {
				fields = "|" + fields;
			}

			ShoppingItem item = ShoppingItemServiceUtil.getItemById(itemId);

			if (item.getMinQuantity() > 0) {
				for (int i = 0; i < item.getMinQuantity(); i++) {
					cart.addItemId(itemId, fields);
				}
			}
			else {
				cart.addItemId(itemId, fields);
			}
		}
		else if (cmd.equals(Constants.SAVE) || cmd.equals(Constants.UPDATE)) {
			String itemIds = ParamUtil.getString(req, "item_ids");
			String couponIds = ParamUtil.getString(req, "coupon_ids");
			int altShipping = ParamUtil.getInteger(req, "alt_shipping");
			boolean insure = ParamUtil.getBoolean(req, "insure");

			cart.setItemIds(itemIds);
			cart.setCouponIds(couponIds);
			cart.setAltShipping(altShipping);
			cart.setInsure(insure);
		}

		ShoppingCartServiceUtil.updateCart(
			ses.getId(), companyId, cart.getItemIds(), cart.getCouponIds(),
			cart.getAltShipping(), cart.isInsure());

		// Session messages

		SessionMessages.add(req, "cart_updated");
	}

}