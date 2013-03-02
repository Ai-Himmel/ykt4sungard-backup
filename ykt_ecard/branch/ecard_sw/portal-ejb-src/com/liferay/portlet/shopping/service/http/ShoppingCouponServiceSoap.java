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

package com.liferay.portlet.shopping.service.http;

import com.liferay.portlet.shopping.service.spring.ShoppingCouponServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ShoppingCouponServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCouponServiceSoap {
	public static com.liferay.portlet.shopping.model.ShoppingCouponModel addCoupon(
		java.lang.String couponId, boolean autoCouponId, java.lang.String name,
		java.lang.String description, int startMonth, int startDay,
		int startYear, int endMonth, int endDay, int endYear,
		boolean neverExpires, boolean active, java.lang.String limitCategories,
		java.lang.String limitSkus, double minOrder, double discount,
		java.lang.String discountType) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCoupon returnValue = ShoppingCouponServiceUtil.addCoupon(couponId,
					autoCouponId, name, description, startMonth, startDay,
					startYear, endMonth, endDay, endYear, neverExpires, active,
					limitCategories, limitSkus, minOrder, discount, discountType);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteCoupon(java.lang.String couponId)
		throws RemoteException {
		try {
			ShoppingCouponServiceUtil.deleteCoupon(couponId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCouponModel getCoupon(
		java.lang.String couponId) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCoupon returnValue = ShoppingCouponServiceUtil.getCoupon(couponId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCouponModel[] getCoupons(
		java.lang.String companyId) throws RemoteException {
		try {
			java.util.List returnValue = ShoppingCouponServiceUtil.getCoupons(companyId);

			return (com.liferay.portlet.shopping.model.ShoppingCoupon[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingCoupon[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCouponModel[] getCoupons(
		java.lang.String companyId, boolean active,
		java.lang.String discountType, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingCouponServiceUtil.getCoupons(companyId,
					active, discountType, begin, end);

			return (com.liferay.portlet.shopping.model.ShoppingCoupon[])returnValue.toArray(new com.liferay.portlet.shopping.model.ShoppingCoupon[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getCouponsSize(java.lang.String companyId,
		boolean active, java.lang.String discountType)
		throws RemoteException {
		try {
			int returnValue = ShoppingCouponServiceUtil.getCouponsSize(companyId,
					active, discountType);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCouponModel updateCoupon(
		java.lang.String couponId, java.lang.String name,
		java.lang.String description, int startMonth, int startDay,
		int startYear, int endMonth, int endDay, int endYear,
		boolean neverExpires, boolean active, java.lang.String limitCategories,
		java.lang.String limitSkus, double minOrder, double discount,
		java.lang.String discountType) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCoupon returnValue = ShoppingCouponServiceUtil.updateCoupon(couponId,
					name, description, startMonth, startDay, startYear,
					endMonth, endDay, endYear, neverExpires, active,
					limitCategories, limitSkus, minOrder, discount, discountType);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}