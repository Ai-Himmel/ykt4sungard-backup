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

package com.liferay.portlet.shopping.service.spring;

/**
 * <a href="ShoppingCouponServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCouponServiceUtil {
	public static final String PORTLET_ID = "34";

	public static com.liferay.portlet.shopping.model.ShoppingCoupon addCoupon(
		java.lang.String couponId, boolean autoCouponId, java.lang.String name,
		java.lang.String description, int startMonth, int startDay,
		int startYear, int endMonth, int endDay, int endYear,
		boolean neverExpires, boolean active, java.lang.String limitCategories,
		java.lang.String limitSkus, double minOrder, double discount,
		java.lang.String discountType)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCouponService shoppingCouponService = ShoppingCouponServiceFactory.getService();

			return shoppingCouponService.addCoupon(couponId, autoCouponId,
				name, description, startMonth, startDay, startYear, endMonth,
				endDay, endYear, neverExpires, active, limitCategories,
				limitSkus, minOrder, discount, discountType);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteCoupon(java.lang.String couponId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCouponService shoppingCouponService = ShoppingCouponServiceFactory.getService();
			shoppingCouponService.deleteCoupon(couponId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCoupon getCoupon(
		java.lang.String couponId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCouponService shoppingCouponService = ShoppingCouponServiceFactory.getService();

			return shoppingCouponService.getCoupon(couponId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getCoupons(java.lang.String companyId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCouponService shoppingCouponService = ShoppingCouponServiceFactory.getService();

			return shoppingCouponService.getCoupons(companyId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getCoupons(java.lang.String companyId,
		boolean active, java.lang.String discountType, int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCouponService shoppingCouponService = ShoppingCouponServiceFactory.getService();

			return shoppingCouponService.getCoupons(companyId, active,
				discountType, begin, end);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getCouponsSize(java.lang.String companyId,
		boolean active, java.lang.String discountType)
		throws com.liferay.portal.SystemException {
		try {
			ShoppingCouponService shoppingCouponService = ShoppingCouponServiceFactory.getService();

			return shoppingCouponService.getCouponsSize(companyId, active,
				discountType);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCoupon updateCoupon(
		java.lang.String couponId, java.lang.String name,
		java.lang.String description, int startMonth, int startDay,
		int startYear, int endMonth, int endDay, int endYear,
		boolean neverExpires, boolean active, java.lang.String limitCategories,
		java.lang.String limitSkus, double minOrder, double discount,
		java.lang.String discountType)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			ShoppingCouponService shoppingCouponService = ShoppingCouponServiceFactory.getService();

			return shoppingCouponService.updateCoupon(couponId, name,
				description, startMonth, startDay, startYear, endMonth, endDay,
				endYear, neverExpires, active, limitCategories, limitSkus,
				minOrder, discount, discountType);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}