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
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.shopping.CouponCodeException;
import com.liferay.portlet.shopping.CouponDateException;
import com.liferay.portlet.shopping.CouponDescriptionException;
import com.liferay.portlet.shopping.CouponEndDateException;
import com.liferay.portlet.shopping.CouponLimitCategoriesException;
import com.liferay.portlet.shopping.CouponLimitSKUsException;
import com.liferay.portlet.shopping.CouponNameException;
import com.liferay.portlet.shopping.CouponStartDateException;
import com.liferay.portlet.shopping.DuplicateCouponCodeException;
import com.liferay.portlet.shopping.NoSuchCouponException;
import com.liferay.portlet.shopping.service.ShoppingCouponServiceUtil;
import com.liferay.util.servlet.SessionErrors;

import java.util.Calendar;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditCouponAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditCouponAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateCoupon(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteCoupons(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchCouponException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.shopping.error");
			}
			else if (e instanceof CouponCodeException ||
					 e instanceof CouponDateException ||
					 e instanceof CouponDescriptionException ||
					 e instanceof CouponEndDateException ||
					 e instanceof CouponLimitCategoriesException ||
					 e instanceof CouponLimitSKUsException ||
					 e instanceof CouponNameException ||
					 e instanceof CouponStartDateException ||
					 e instanceof DuplicateCouponCodeException) {

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

		try {
			ActionUtil.getCoupon(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchCouponException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.shopping.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.shopping.edit_coupon"));
	}

	protected void deleteCoupons(ActionRequest req) throws Exception {
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long[] deleteCouponIds = StringUtil.split(
			ParamUtil.getString(req, "deleteCouponIds"), 0L);

		for (int i = 0; i < deleteCouponIds.length; i++) {
			ShoppingCouponServiceUtil.deleteCoupon(
				layout.getPlid(), deleteCouponIds[i]);
		}
	}

	protected void updateCoupon(ActionRequest req) throws Exception {
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long couponId = ParamUtil.getLong(req, "couponId");

		String code = ParamUtil.getString(req, "code");
		boolean autoCode = ParamUtil.getBoolean(req, "autoCode");

		String name = ParamUtil.getString(req, "name");
		String description = ParamUtil.getString(req, "description");

		int startDateMonth = ParamUtil.getInteger(req, "startDateMonth");
		int startDateDay = ParamUtil.getInteger(req, "startDateDay");
		int startDateYear = ParamUtil.getInteger(req, "startDateYear");
		int startDateHour = ParamUtil.getInteger(req, "startDateHour");
		int startDateMinute = ParamUtil.getInteger(req, "startDateMinute");
		int startDateAmPm = ParamUtil.getInteger(req, "startDateAmPm");

		if (startDateAmPm == Calendar.PM) {
			startDateHour += 12;
		}

		int endDateMonth = ParamUtil.getInteger(req, "endDateMonth");
		int endDateDay = ParamUtil.getInteger(req, "endDateDay");
		int endDateYear = ParamUtil.getInteger(req, "endDateYear");
		int endDateHour = ParamUtil.getInteger(req, "endDateHour");
		int endDateMinute = ParamUtil.getInteger(req, "endDateMinute");
		int endDateAmPm = ParamUtil.getInteger(req, "endDateAmPm");
		boolean neverExpire = ParamUtil.getBoolean(req, "neverExpire");

		if (endDateAmPm == Calendar.PM) {
			endDateHour += 12;
		}

		boolean active = ParamUtil.getBoolean(req, "active");
		String limitCategories = ParamUtil.getString(req, "limitCategories");
		String limitSkus = ParamUtil.getString(req, "limitSkus");
		double minOrder = ParamUtil.getDouble(req, "minOrder");
		double discount = ParamUtil.getDouble(req, "discount");
		String discountType = ParamUtil.getString(req, "discountType");

		if (couponId <= 0) {

			// Add coupon

			ShoppingCouponServiceUtil.addCoupon(
				layout.getPlid(), code, autoCode, name, description,
				startDateMonth, startDateDay, startDateYear, startDateHour,
				startDateMinute, endDateMonth, endDateDay, endDateYear,
				endDateHour, endDateMinute, neverExpire, active,
				limitCategories, limitSkus, minOrder, discount, discountType);
		}
		else {

			// Update coupon

			ShoppingCouponServiceUtil.updateCoupon(
				layout.getPlid(), couponId, name, description, startDateMonth,
				startDateDay, startDateYear, startDateHour, startDateMinute,
				endDateMonth, endDateDay, endDateYear, endDateHour,
				endDateMinute, neverExpire, active, limitCategories, limitSkus,
				minOrder, discount, discountType);
		}
	}

}