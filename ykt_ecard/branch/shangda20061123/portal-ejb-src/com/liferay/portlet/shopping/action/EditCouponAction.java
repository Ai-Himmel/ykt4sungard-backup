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

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.shopping.CouponDateException;
import com.liferay.portlet.shopping.CouponDescriptionException;
import com.liferay.portlet.shopping.CouponEndDateException;
import com.liferay.portlet.shopping.CouponIdException;
import com.liferay.portlet.shopping.CouponLimitCategoriesException;
import com.liferay.portlet.shopping.CouponLimitSKUsException;
import com.liferay.portlet.shopping.CouponNameException;
import com.liferay.portlet.shopping.CouponStartDateException;
import com.liferay.portlet.shopping.DuplicateCouponIdException;
import com.liferay.portlet.shopping.NoSuchCouponException;
import com.liferay.portlet.shopping.RequiredCouponException;
import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.portlet.shopping.service.spring.ShoppingCouponServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditCouponAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class EditCouponAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			_editCoupon(req);
		}
		catch (Exception e) {
			if (e != null &&
				e instanceof NoSuchCouponException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.shopping.error");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			if (cmd.equals(Constants.ADD)) {
				req.removeAttribute(WebKeys.SHOPPING_COUPON);
			}

			try {
				_updateCoupon(config, req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchCouponException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.shopping.error");
				}
				else if (e != null &&
						 e instanceof DuplicateCouponIdException ||
						 e instanceof CouponDateException ||
						 e instanceof CouponDescriptionException ||
						 e instanceof CouponEndDateException ||
						 e instanceof CouponIdException ||
						 e instanceof CouponLimitCategoriesException ||
						 e instanceof CouponLimitSKUsException ||
						 e instanceof CouponNameException ||
						 e instanceof CouponStartDateException) {

					if (e instanceof CouponLimitCategoriesException) {
						CouponLimitCategoriesException clce =
							(CouponLimitCategoriesException)e;

						SessionErrors.add(
							req, e.getClass().getName(), clce.getCategoryIds());
					}
					else if (e instanceof CouponLimitSKUsException) {
						CouponLimitSKUsException clskue =
							(CouponLimitSKUsException)e;

						SessionErrors.add(
							req, e.getClass().getName(), clskue.getSkus());
					}
					else {
						SessionErrors.add(req, e.getClass().getName());
					}

					setForward(req, "portlet.shopping.edit_coupon");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteCoupon(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchCouponException ||
					e instanceof PrincipalException ||
					e instanceof RequiredCouponException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.shopping.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			setForward(req, "portlet.shopping.edit_coupon");
		}
	}

	private void _deleteCoupon(ActionRequest req, ActionResponse res)
		throws Exception {

		String couponId = ParamUtil.getString(req, "coupon_id");

		ShoppingCouponServiceUtil.deleteCoupon(couponId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editCoupon(ActionRequest req) throws Exception {
		String couponId = ParamUtil.getString(req, "coupon_id");

		// Find coupon

		ShoppingCoupon coupon = null;

		if (Validator.isNotNull(couponId)) {
			coupon = ShoppingCouponServiceUtil.getCoupon(couponId);
		}

		req.setAttribute(WebKeys.SHOPPING_COUPON, coupon);
	}

	private void _updateCoupon(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		String couponId = ParamUtil.getString(req, "coupon_id");
		boolean autoCouponId = ParamUtil.get(req, "auto_coupon_id", false);

		String name = ParamUtil.getString(req, "coupon_name");
		String description = ParamUtil.getString(req, "coupon_desc");

		int startMonth = ParamUtil.getInteger(req, "coupon_sd_month");
		int startDay = ParamUtil.getInteger(req, "coupon_sd_day");
		int startYear = ParamUtil.getInteger(req, "coupon_sd_year");
		int endMonth = ParamUtil.getInteger(req, "coupon_ed_month");
		int endDay = ParamUtil.getInteger(req, "coupon_ed_day");
		int endYear = ParamUtil.getInteger(req, "coupon_ed_year");
		boolean neverExpires = ParamUtil.get(
			req, "coupon_never_expires", false);
		boolean active = ParamUtil.get(req, "coupon_active", false);

		String limitCategories = StringUtil.replace(
			ParamUtil.getString(req, "coupon_limit_categories"),
			StringPool.SPACE, StringPool.BLANK);
		String limitSkus = StringUtil.replace(
			ParamUtil.getString(req, "coupon_limit_skus"),
			StringPool.SPACE, StringPool.BLANK);
		double minOrder = ParamUtil.getDouble(req, "coupon_min_order");
		double discount = ParamUtil.getDouble(req, "coupon_discount");
		String discountType = ParamUtil.getString(req, "coupon_discount_type");

		if (cmd.equals(Constants.ADD)) {

			// Add coupon

			ShoppingCouponServiceUtil.addCoupon(
				couponId, autoCouponId, name, description, startMonth, startDay,
				startYear, endMonth, endDay, endYear, neverExpires, active,
				limitCategories, limitSkus, minOrder, discount, discountType);
		}
		else {

			// Update coupon

			ShoppingCouponServiceUtil.updateCoupon(
				couponId, name, description, startMonth, startDay, startYear,
				endMonth, endDay, endYear, neverExpires, active,
				limitCategories, limitSkus, minOrder, discount, discountType);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}