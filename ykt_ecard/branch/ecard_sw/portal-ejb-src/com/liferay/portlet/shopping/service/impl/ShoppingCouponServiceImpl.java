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

package com.liferay.portlet.shopping.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.shopping.CouponDateException;
import com.liferay.portlet.shopping.CouponDescriptionException;
import com.liferay.portlet.shopping.CouponEndDateException;
import com.liferay.portlet.shopping.CouponIdException;
import com.liferay.portlet.shopping.CouponLimitCategoriesException;
import com.liferay.portlet.shopping.CouponLimitSKUsException;
import com.liferay.portlet.shopping.CouponNameException;
import com.liferay.portlet.shopping.CouponStartDateException;
import com.liferay.portlet.shopping.DuplicateCouponIdException;
import com.liferay.portlet.shopping.NoSuchCategoryException;
import com.liferay.portlet.shopping.NoSuchCouponException;
import com.liferay.portlet.shopping.NoSuchItemException;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.service.persistence.ShoppingCategoryUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingCouponUtil;
import com.liferay.portlet.shopping.service.persistence.ShoppingItemUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingCategoryServiceUtil;
import com.liferay.portlet.shopping.service.spring.ShoppingCouponService;
import com.liferay.util.PwdGenerator;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="ShoppingCouponServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class ShoppingCouponServiceImpl
	extends PrincipalBean implements ShoppingCouponService {

	// Business methods

	public ShoppingCoupon addCoupon(
			String couponId, boolean autoCouponId, String name,
			String description, int startMonth, int startDay, int startYear,
			int endMonth, int endDay, int endYear, boolean neverExpires,
			boolean active, String limitCategories, String limitSkus,
			double minOrder, double discount, String discountType)
		throws PortalException, SystemException {

		couponId = couponId.trim().toUpperCase();

		_validate(
			couponId, autoCouponId, name, description, limitCategories,
			limitSkus);

		if (!ShoppingCategoryServiceUtil.hasAdmin()) {
			throw new PrincipalException();
		}

		User user = getUser();

		if (autoCouponId) {
			couponId = _getCouponId();
		}

		ShoppingCoupon coupon = ShoppingCouponUtil.create(couponId);

		Date now = new Date();

		Date startDate = PortalUtil.getDate(
			startMonth, startDay, startYear, 0, 0, user.getTimeZone(),
			new CouponStartDateException());

		Date endDate = null;
		if (!neverExpires) {
			endDate = PortalUtil.getDate(
				endMonth, endDay, endYear, 23, 59, user.getTimeZone(),
				new CouponEndDateException());
		}

		if ((endDate != null) && (startDate.after(endDate))) {
			throw new CouponDateException();
		}

		coupon.setCompanyId(user.getCompanyId());
		coupon.setCreateDate(now);
		coupon.setModifiedDate(now);
		coupon.setName(name);
		coupon.setDescription(description);
		coupon.setStartDate(startDate);
		coupon.setEndDate(endDate);
		coupon.setActive(active);
		coupon.setLimitCategories(limitCategories);
		coupon.setLimitSkus(limitSkus);
		coupon.setMinOrder(minOrder);
		coupon.setDiscount(discount);
		coupon.setDiscountType(discountType);

		ShoppingCouponUtil.update(coupon);

		return coupon;
	}

	public void deleteCoupon(String couponId)
		throws PortalException, SystemException {

		couponId = couponId.trim().toUpperCase();

		ShoppingCoupon coupon = ShoppingCouponUtil.findByPrimaryKey(couponId);

		if (!ShoppingCategoryServiceUtil.hasAdmin() ||
			!getUser().getCompanyId().equals(coupon.getCompanyId())) {

			throw new PrincipalException();
		}

		ShoppingCouponUtil.remove(couponId);
	}

	public ShoppingCoupon getCoupon(String couponId)
		throws PortalException, SystemException {

		couponId = couponId.trim().toUpperCase();

		ShoppingCoupon coupon = ShoppingCouponUtil.findByPrimaryKey(couponId);

		// Unauthetincated users who know the ID should have access to it

		/*if (!getUser().getCompanyId().equals(coupon.getCompanyId())) {
			throw new PrincipalException();
		}*/

		return coupon;
	}

	public List getCoupons(String companyId)
		throws PortalException, SystemException {

		if (!ShoppingCategoryServiceUtil.hasAdmin() ||
			!getUser().getCompanyId().equals(companyId)) {

			throw new PrincipalException();
		}

		return ShoppingCouponUtil.findByCompanyId(companyId);
	}

	public List getCoupons(
			String companyId, boolean active, String discountType, int begin,
			int end)
		throws PortalException, SystemException {

		if (!ShoppingCategoryServiceUtil.hasAdmin() ||
			!getUser().getCompanyId().equals(companyId)) {

			throw new PrincipalException();
		}

		if (Validator.isNull(discountType)) {
			return ShoppingCouponUtil.findByC_A(companyId, active, begin, end);
		}
		else {
			return ShoppingCouponUtil.findByC_A_D(
				companyId, active, discountType, begin, end);
		}
	}

	public int getCouponsSize(
			String companyId, boolean active, String discountType)
		throws SystemException {

		if (Validator.isNull(discountType)) {
			return ShoppingCouponUtil.countByC_A(companyId, active);
		}
		else {
			return ShoppingCouponUtil.countByC_A_D(
				companyId, active, discountType);
		}
	}

	public ShoppingCoupon updateCoupon(
			String couponId, String name, String description, int startMonth,
			int startDay, int startYear, int endMonth, int endDay, int endYear,
			boolean neverExpires, boolean active, String limitCategories,
			String limitSkus, double minOrder, double discount,
			String discountType)
		throws PortalException, SystemException {

		couponId = couponId.trim().toUpperCase();

		_validate(name, description, limitCategories, limitSkus);

		if (!ShoppingCategoryServiceUtil.hasAdmin()) {
			throw new PrincipalException();
		}

		User user = getUser();

		ShoppingCoupon coupon = ShoppingCouponUtil.findByPrimaryKey(couponId);

		Date startDate = PortalUtil.getDate(
			startMonth, startDay, startYear, 0, 0, user.getTimeZone(),
			new CouponStartDateException());

		Date endDate = null;
		if (!neverExpires) {
			endDate = PortalUtil.getDate(
				endMonth, endDay, endYear, 23, 59, user.getTimeZone(),
				new CouponEndDateException());
		}

		if ((endDate != null) && (startDate.after(endDate))) {
			throw new CouponDateException();
		}

		coupon.setModifiedDate(new Date());
		coupon.setName(name);
		coupon.setDescription(description);
		coupon.setStartDate(startDate);
		coupon.setEndDate(endDate);
		coupon.setActive(active);
		coupon.setLimitCategories(limitCategories);
		coupon.setLimitSkus(limitSkus);
		coupon.setMinOrder(minOrder);
		coupon.setDiscount(discount);
		coupon.setDiscountType(discountType);

		ShoppingCouponUtil.update(coupon);

		return coupon;
	}

	// Private methods

	private String _getCouponId() throws SystemException {
		String couponId =
			PwdGenerator.getPassword(PwdGenerator.KEY1 + PwdGenerator.KEY2, 8);

		try {
			ShoppingCouponUtil.findByPrimaryKey(couponId);

			return _getCouponId();
		}
		catch (NoSuchCouponException nsce) {
			return couponId;
		}
	}

	private void _validate(
			String couponId, boolean autoCouponId, String name,
			String description, String limitCategories, String limitSkus)
		throws PortalException, SystemException {

		if (!autoCouponId) {
			if ((Validator.isNull(couponId)) ||
				(Validator.isNumber(couponId)) ||
				(couponId.indexOf(StringPool.SPACE) != -1)) {

				throw new CouponIdException();
			}

			try {
				ShoppingCouponUtil.findByPrimaryKey(couponId);

				throw new DuplicateCouponIdException();
			}
			catch (NoSuchCouponException nsce) {
			}
		}

		_validate(name, description, limitCategories, limitSkus);
	}

	private void _validate(
			String name, String description, String limitCategories,
			String limitSkus)
		throws PortalException, SystemException {

		if (Validator.isNull(name)) {
			throw new CouponNameException();
		}
		else if (Validator.isNull(description)) {
			throw new CouponDescriptionException();
		}

		String companyId = getUser().getCompanyId();

		if (Validator.isNotNull(limitCategories)) {
			String[] categoryIds = StringUtil.split(limitCategories);

			List invalidCategoryIds = new ArrayList();

			for (int i = 0; i < categoryIds.length; i++) {
				try {
					ShoppingCategory category =
						ShoppingCategoryUtil.findByPrimaryKey(categoryIds[i]);

					if (!category.getCompanyId().equals(companyId)) {
						invalidCategoryIds.add(categoryIds[i]);
					}
				}
				catch (NoSuchCategoryException nsce) {
					invalidCategoryIds.add(categoryIds[i]);
				}
			}

			if (invalidCategoryIds.size() > 0) {
				CouponLimitCategoriesException clce =
					new CouponLimitCategoriesException();

				clce.setCategoryIds(invalidCategoryIds);

				throw clce;
			}
		}

		if (Validator.isNotNull(limitSkus)) {
			String[] skus = StringUtil.split(limitSkus);

			List invalidSkus = new ArrayList();

			for (int i = 0; i < skus.length; i++) {
				try {
					ShoppingItem item =
						ShoppingItemUtil.findByC_S(companyId, skus[i]);
				}
				catch (NoSuchItemException nsie) {
					invalidSkus.add(skus[i]);
				}
			}

			if (invalidSkus.size() > 0) {
				CouponLimitSKUsException clskue =
					new CouponLimitSKUsException();

				clskue.setSkus(invalidSkus);

				throw clskue;
			}
		}
	}

}