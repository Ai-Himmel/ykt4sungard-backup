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
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.shopping.CouponCodeException;
import com.liferay.portlet.shopping.CouponDateException;
import com.liferay.portlet.shopping.CouponDescriptionException;
import com.liferay.portlet.shopping.CouponEndDateException;
import com.liferay.portlet.shopping.CouponLimitCategoriesException;
import com.liferay.portlet.shopping.CouponLimitSKUsException;
import com.liferay.portlet.shopping.CouponNameException;
import com.liferay.portlet.shopping.CouponStartDateException;
import com.liferay.portlet.shopping.DuplicateCouponCodeException;
import com.liferay.portlet.shopping.NoSuchCategoryException;
import com.liferay.portlet.shopping.NoSuchCouponException;
import com.liferay.portlet.shopping.NoSuchItemException;
import com.liferay.portlet.shopping.model.ShoppingCategory;
import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.portlet.shopping.model.ShoppingItem;
import com.liferay.portlet.shopping.service.base.ShoppingCouponLocalServiceBaseImpl;
import com.liferay.util.PwdGenerator;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="ShoppingCouponLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingCouponLocalServiceImpl
	extends ShoppingCouponLocalServiceBaseImpl {

	public ShoppingCoupon addCoupon(
			long userId, long plid, String code, boolean autoCode, String name,
			String description, int startDateMonth, int startDateDay,
			int startDateYear, int startDateHour, int startDateMinute,
			int endDateMonth, int endDateDay, int endDateYear, int endDateHour,
			int endDateMinute, boolean neverExpire, boolean active,
			String limitCategories, String limitSkus, double minOrder,
			double discount, String discountType)
		throws PortalException, SystemException {

		// Coupon

		User user = userPersistence.findByPrimaryKey(userId);
		long groupId = PortalUtil.getPortletGroupId(plid);

		code = code.trim().toUpperCase();

		if (autoCode) {
			code = getCode();
		}

		Date now = new Date();

		Date startDate = PortalUtil.getDate(
			startDateMonth, startDateDay, startDateYear, startDateHour,
			startDateMinute, user.getTimeZone(),
			new CouponStartDateException());

		Date endDate = null;

		if (!neverExpire) {
			endDate = PortalUtil.getDate(
				endDateMonth, endDateDay, endDateYear, endDateHour,
				endDateMinute, user.getTimeZone(),
				new CouponEndDateException());
		}

		if ((endDate != null) && (startDate.after(endDate))) {
			throw new CouponDateException();
		}

		validate(
			user.getCompanyId(), groupId, code, autoCode, name, description,
			limitCategories, limitSkus);

		long couponId = counterLocalService.increment();

		ShoppingCoupon coupon = shoppingCouponPersistence.create(couponId);

		coupon.setGroupId(groupId);
		coupon.setCompanyId(user.getCompanyId());
		coupon.setUserId(user.getUserId());
		coupon.setUserName(user.getFullName());
		coupon.setCreateDate(now);
		coupon.setModifiedDate(now);
		coupon.setCode(code);
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

		shoppingCouponPersistence.update(coupon);

		return coupon;
	}

	public void deleteCoupon(long couponId)
		throws PortalException, SystemException {

		shoppingCouponPersistence.remove(couponId);
	}

	public void deleteCoupons(long groupId) throws SystemException {
		shoppingCouponPersistence.removeByGroupId(groupId);
	}

	public ShoppingCoupon getCoupon(long couponId)
		throws PortalException, SystemException {

		return shoppingCouponPersistence.findByPrimaryKey(couponId);
	}

	public ShoppingCoupon getCoupon(String code)
		throws PortalException, SystemException {

		code = code.trim().toUpperCase();

		return shoppingCouponPersistence.findByCode(code);
	}

	public List search(
			long plid, long companyId, String code, boolean active,
			String discountType, boolean andOperator, int begin, int end)
		throws SystemException {

		long groupId = PortalUtil.getPortletGroupId(plid);

		return shoppingCouponFinder.findByG_C_C_A_DT(
			groupId, companyId, code, active, discountType, andOperator,
			begin, end);
	}

	public int searchCount(
			long groupId, long companyId, String code, boolean active,
			String discountType, boolean andOperator)
		throws SystemException {

		return shoppingCouponFinder.countByG_C_C_A_DT(
			groupId, companyId, code, active, discountType, andOperator);
	}

	public ShoppingCoupon updateCoupon(
			long userId, long couponId, String name, String description,
			int startDateMonth, int startDateDay, int startDateYear,
			int startDateHour, int startDateMinute, int endDateMonth,
			int endDateDay, int endDateYear, int endDateHour, int endDateMinute,
			boolean neverExpire, boolean active, String limitCategories,
			String limitSkus, double minOrder, double discount,
			String discountType)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);

		ShoppingCoupon coupon = shoppingCouponPersistence.findByPrimaryKey(
			couponId);

		Date startDate = PortalUtil.getDate(
			startDateMonth, startDateDay, startDateYear, startDateHour,
			startDateMinute, user.getTimeZone(),
			new CouponStartDateException());

		Date endDate = null;

		if (!neverExpire) {
			endDate = PortalUtil.getDate(
				endDateMonth, endDateDay, endDateYear, endDateHour,
				endDateMinute, user.getTimeZone(),
				new CouponEndDateException());
		}

		if ((endDate != null) && (startDate.after(endDate))) {
			throw new CouponDateException();
		}

		validate(
			coupon.getCompanyId(), coupon.getGroupId(), name, description,
			limitCategories, limitSkus);

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

		shoppingCouponPersistence.update(coupon);

		return coupon;
	}

	protected String getCode() throws SystemException {
		String code =
			PwdGenerator.getPassword(PwdGenerator.KEY1 + PwdGenerator.KEY2, 8);

		try {
			shoppingCouponPersistence.findByCode(code);

			return getCode();
		}
		catch (NoSuchCouponException nsce) {
			return code;
		}
	}

	protected void validate(
			long companyId, long groupId, String code, boolean autoCode,
			String name, String description, String limitCategories,
			String limitSkus)
		throws PortalException, SystemException {

		if (!autoCode) {
			if ((Validator.isNull(code)) ||
				(Validator.isNumber(code)) ||
				(code.indexOf(StringPool.SPACE) != -1)) {

				throw new CouponCodeException();
			}

			try {
				shoppingCouponPersistence.findByCode(code);

				throw new DuplicateCouponCodeException();
			}
			catch (NoSuchCouponException nsce) {
			}
		}

		validate(
			companyId, groupId, name, description, limitCategories, limitSkus);
	}

	protected void validate(
			long companyId, long groupId, String name, String description,
			String limitCategories, String limitSkus)
		throws PortalException, SystemException {

		if (Validator.isNull(name)) {
			throw new CouponNameException();
		}
		else if (Validator.isNull(description)) {
			throw new CouponDescriptionException();
		}

		// Category IDs

		long[] categoryIds = StringUtil.split(limitCategories, 0L);

		List invalidCategoryIds = new ArrayList();

		for (int i = 0; i < categoryIds.length; i++) {
			try {
				ShoppingCategory category =
					shoppingCategoryPersistence.findByPrimaryKey(
						categoryIds[i]);

				if (category.getGroupId() != groupId) {
					invalidCategoryIds.add(new Long(categoryIds[i]));
				}
			}
			catch (NoSuchCategoryException nsce) {
				invalidCategoryIds.add(new Long(categoryIds[i]));
			}
		}

		if (invalidCategoryIds.size() > 0) {
			CouponLimitCategoriesException clce =
				new CouponLimitCategoriesException();

			clce.setCategoryIds(invalidCategoryIds);

			throw clce;
		}

		// SKUs

		String[] skus = StringUtil.split(limitSkus);

		List invalidSkus = new ArrayList();

		for (int i = 0; i < skus.length; i++) {
			try {
				ShoppingItem item = shoppingItemPersistence.findByC_S(
					companyId, skus[i]);

				ShoppingCategory category = item.getCategory();

				if (category.getGroupId() != groupId) {
					invalidSkus.add(skus[i]);
				}
			}
			catch (NoSuchItemException nsie) {
				invalidSkus.add(skus[i]);
			}
		}

		if (invalidSkus.size() > 0) {
			CouponLimitSKUsException clskue = new CouponLimitSKUsException();

			clskue.setSkus(invalidSkus);

			throw clskue;
		}
	}

}