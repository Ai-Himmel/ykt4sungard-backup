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

package com.liferay.portlet.shopping.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="ShoppingCouponModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class ShoppingCouponModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.shopping.model.ShoppingCoupon"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.shopping.model.ShoppingCoupon"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCoupon"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_COUPONID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCoupon.couponId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCoupon.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCoupon.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCoupon.description"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_LIMITCATEGORIES = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCoupon.limitCategories"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_LIMITSKUS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCoupon.limitSkus"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DISCOUNTTYPE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCoupon.discountType"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingCouponModel"));

	public ShoppingCouponModel() {
	}

	public ShoppingCouponModel(String couponId) {
		_couponId = couponId;
		setNew(true);
	}

	public ShoppingCouponModel(String couponId, String companyId,
		Date createDate, Date modifiedDate, String name, String description,
		Date startDate, Date endDate, boolean active, String limitCategories,
		String limitSkus, double minOrder, double discount, String discountType) {
		_couponId = couponId;
		_companyId = companyId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_name = name;
		_description = description;
		_startDate = startDate;
		_endDate = endDate;
		_active = active;
		_limitCategories = limitCategories;
		_limitSkus = limitSkus;
		_minOrder = minOrder;
		_discount = discount;
		_discountType = discountType;
	}

	public String getPrimaryKey() {
		return _couponId;
	}

	public String getCouponId() {
		return _couponId;
	}

	public void setCouponId(String couponId) {
		if (((couponId == null) && (_couponId != null)) ||
				((couponId != null) && (_couponId == null)) ||
				((couponId != null) && (_couponId != null) &&
				!couponId.equals(_couponId))) {
			if (!XSS_ALLOW_COUPONID) {
				couponId = Xss.strip(couponId);
			}

			_couponId = couponId;
			setModified(true);
		}
	}

	public String getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(String companyId) {
		if (((companyId == null) && (_companyId != null)) ||
				((companyId != null) && (_companyId == null)) ||
				((companyId != null) && (_companyId != null) &&
				!companyId.equals(_companyId))) {
			if (!XSS_ALLOW_COMPANYID) {
				companyId = Xss.strip(companyId);
			}

			_companyId = companyId;
			setModified(true);
		}
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
			setModified(true);
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
			setModified(true);
		}
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			if (!XSS_ALLOW_NAME) {
				name = Xss.strip(name);
			}

			_name = name;
			setModified(true);
		}
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			if (!XSS_ALLOW_DESCRIPTION) {
				description = Xss.strip(description);
			}

			_description = description;
			setModified(true);
		}
	}

	public Date getStartDate() {
		return _startDate;
	}

	public void setStartDate(Date startDate) {
		if (((startDate == null) && (_startDate != null)) ||
				((startDate != null) && (_startDate == null)) ||
				((startDate != null) && (_startDate != null) &&
				!startDate.equals(_startDate))) {
			_startDate = startDate;
			setModified(true);
		}
	}

	public Date getEndDate() {
		return _endDate;
	}

	public void setEndDate(Date endDate) {
		if (((endDate == null) && (_endDate != null)) ||
				((endDate != null) && (_endDate == null)) ||
				((endDate != null) && (_endDate != null) &&
				!endDate.equals(_endDate))) {
			_endDate = endDate;
			setModified(true);
		}
	}

	public boolean getActive() {
		return _active;
	}

	public boolean isActive() {
		return _active;
	}

	public void setActive(boolean active) {
		if (active != _active) {
			_active = active;
			setModified(true);
		}
	}

	public String getLimitCategories() {
		return _limitCategories;
	}

	public void setLimitCategories(String limitCategories) {
		if (((limitCategories == null) && (_limitCategories != null)) ||
				((limitCategories != null) && (_limitCategories == null)) ||
				((limitCategories != null) && (_limitCategories != null) &&
				!limitCategories.equals(_limitCategories))) {
			if (!XSS_ALLOW_LIMITCATEGORIES) {
				limitCategories = Xss.strip(limitCategories);
			}

			_limitCategories = limitCategories;
			setModified(true);
		}
	}

	public String getLimitSkus() {
		return _limitSkus;
	}

	public void setLimitSkus(String limitSkus) {
		if (((limitSkus == null) && (_limitSkus != null)) ||
				((limitSkus != null) && (_limitSkus == null)) ||
				((limitSkus != null) && (_limitSkus != null) &&
				!limitSkus.equals(_limitSkus))) {
			if (!XSS_ALLOW_LIMITSKUS) {
				limitSkus = Xss.strip(limitSkus);
			}

			_limitSkus = limitSkus;
			setModified(true);
		}
	}

	public double getMinOrder() {
		return _minOrder;
	}

	public void setMinOrder(double minOrder) {
		if (minOrder != _minOrder) {
			_minOrder = minOrder;
			setModified(true);
		}
	}

	public double getDiscount() {
		return _discount;
	}

	public void setDiscount(double discount) {
		if (discount != _discount) {
			_discount = discount;
			setModified(true);
		}
	}

	public String getDiscountType() {
		return _discountType;
	}

	public void setDiscountType(String discountType) {
		if (((discountType == null) && (_discountType != null)) ||
				((discountType != null) && (_discountType == null)) ||
				((discountType != null) && (_discountType != null) &&
				!discountType.equals(_discountType))) {
			if (!XSS_ALLOW_DISCOUNTTYPE) {
				discountType = Xss.strip(discountType);
			}

			_discountType = discountType;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ShoppingCoupon(getCouponId(), getCompanyId(),
			getCreateDate(), getModifiedDate(), getName(), getDescription(),
			getStartDate(), getEndDate(), getActive(), getLimitCategories(),
			getLimitSkus(), getMinOrder(), getDiscount(), getDiscountType());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingCoupon shoppingCoupon = (ShoppingCoupon)obj;
		int value = 0;
		value = getCreateDate().compareTo(shoppingCoupon.getCreateDate());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingCoupon shoppingCoupon = null;

		try {
			shoppingCoupon = (ShoppingCoupon)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = shoppingCoupon.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
	}

	private String _couponId;
	private String _companyId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _name;
	private String _description;
	private Date _startDate;
	private Date _endDate;
	private boolean _active;
	private String _limitCategories;
	private String _limitSkus;
	private double _minOrder;
	private double _discount;
	private String _discountType;
}