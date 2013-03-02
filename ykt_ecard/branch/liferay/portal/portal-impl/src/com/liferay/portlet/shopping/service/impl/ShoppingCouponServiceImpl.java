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

package com.liferay.portlet.shopping.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.portlet.shopping.service.base.ShoppingCouponServiceBaseImpl;

import java.util.List;

/**
 * <a href="ShoppingCouponServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingCouponServiceImpl extends ShoppingCouponServiceBaseImpl {

	public ShoppingCoupon addCoupon(
			long plid, String code, boolean autoCode, String name,
			String description, int startDateMonth, int startDateDay,
			int startDateYear, int startDateHour, int startDateMinute,
			int endDateMonth, int endDateDay, int endDateYear, int endDateHour,
			int endDateMinute, boolean neverExpire, boolean active,
			String limitCategories, String limitSkus, double minOrder,
			double discount, String discountType)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.SHOPPING,
			ActionKeys.MANAGE_COUPONS);

		return shoppingCouponLocalService.addCoupon(
			getUserId(), plid, code, autoCode, name, description,
			startDateMonth, startDateDay, startDateYear, startDateHour,
			startDateMinute, endDateMonth, endDateDay, endDateYear, endDateHour,
			endDateMinute, neverExpire, active, limitCategories, limitSkus,
			minOrder, discount, discountType);
	}

	public void deleteCoupon(long plid, long couponId)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.SHOPPING,
			ActionKeys.MANAGE_COUPONS);

		shoppingCouponLocalService.deleteCoupon(couponId);
	}

	public ShoppingCoupon getCoupon(long plid, long couponId)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.SHOPPING,
			ActionKeys.MANAGE_COUPONS);

		return shoppingCouponLocalService.getCoupon(couponId);
	}

	public List search(
			long plid, long companyId, String code, boolean active,
			String discountType, boolean andOperator, int begin, int end)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.SHOPPING,
			ActionKeys.MANAGE_COUPONS);

		return shoppingCouponLocalService.search(
			plid, companyId, code, active, discountType, andOperator, begin,
			end);
	}

	public ShoppingCoupon updateCoupon(
			long plid, long couponId, String name, String description,
			int startDateMonth, int startDateDay, int startDateYear,
			int startDateHour, int startDateMinute, int endDateMonth,
			int endDateDay, int endDateYear, int endDateHour, int endDateMinute,
			boolean neverExpire, boolean active, String limitCategories,
			String limitSkus, double minOrder, double discount,
			String discountType)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.SHOPPING,
			ActionKeys.MANAGE_COUPONS);

		return shoppingCouponLocalService.updateCoupon(
			getUserId(), couponId, name, description, startDateMonth,
			startDateDay, startDateYear, startDateHour, startDateMinute,
			endDateMonth, endDateDay, endDateYear, endDateHour, endDateMinute,
			neverExpire, active, limitCategories, limitSkus, minOrder, discount,
			discountType);
	}

}