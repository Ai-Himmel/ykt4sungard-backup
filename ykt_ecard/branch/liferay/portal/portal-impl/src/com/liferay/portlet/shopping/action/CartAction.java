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

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portlet.shopping.CartMinQuantityException;
import com.liferay.portlet.shopping.CouponActiveException;
import com.liferay.portlet.shopping.CouponEndDateException;
import com.liferay.portlet.shopping.CouponStartDateException;
import com.liferay.portlet.shopping.NoSuchCouponException;
import com.liferay.portlet.shopping.NoSuchItemException;
import com.liferay.portlet.shopping.model.ShoppingCart;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.service.ShoppingCartLocalServiceUtil;
import com.liferay.portlet.shopping.service.ShoppingItemLocalServiceUtil;
import com.liferay.portlet.shopping.util.ShoppingUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="CartAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CartAction extends PortletAction {

public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			updateCart(req);

			String redirect = ParamUtil.getString(req, "redirect");

			if (Validator.isNotNull(redirect)) {
				res.sendRedirect(redirect);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchItemException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.shopping.error");
			}
			else if (e instanceof CartMinQuantityException ||
					 e instanceof CouponActiveException ||
					 e instanceof CouponEndDateException ||
					 e instanceof CouponStartDateException ||
					 e instanceof NoSuchCouponException) {

				SessionErrors.add(req, e.getClass().getName(), e);
			}
			else {
				throw e;
			}
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		return mapping.findForward(getForward(req, "portlet.shopping.cart"));
	}

	protected void updateCart(ActionRequest req) throws Exception {
		String cmd = ParamUtil.getString(req, Constants.CMD);

		ShoppingCart cart = ShoppingUtil.getCart(req);

		if (cmd.equals(Constants.ADD)) {
			long itemId = ParamUtil.getLong(req, "itemId");

			String fields = ParamUtil.getString(req, "fields");

			if (Validator.isNotNull(fields)) {
				fields = "|" + fields;
			}

			ShoppingItem item = ShoppingItemLocalServiceUtil.getItem(itemId);

			if (item.getMinQuantity() > 0) {
				for (int i = 0; i < item.getMinQuantity(); i++) {
					cart.addItemId(itemId, fields);
				}
			}
			else {
				cart.addItemId(itemId, fields);
			}
		}
		else {
			String itemIds = ParamUtil.getString(req, "itemIds");
			String couponCodes = ParamUtil.getString(req, "couponCodes");
			int altShipping = ParamUtil.getInteger(req, "altShipping");
			boolean insure = ParamUtil.getBoolean(req, "insure");

			cart.setItemIds(itemIds);
			cart.setCouponCodes(couponCodes);
			cart.setAltShipping(altShipping);
			cart.setInsure(insure);
		}

		ShoppingCartLocalServiceUtil.updateCart(
			cart.getUserId(), cart.getGroupId(), cart.getItemIds(),
			cart.getCouponCodes(), cart.getAltShipping(), cart.isInsure());

		if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
			SessionMessages.add(req, "request_processed");
		}
	}

}