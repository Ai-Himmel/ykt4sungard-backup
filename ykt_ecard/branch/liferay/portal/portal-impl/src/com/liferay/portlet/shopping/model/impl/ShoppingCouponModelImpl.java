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

package com.liferay.portlet.shopping.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.shopping.model.ShoppingCoupon;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="ShoppingCouponModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ShoppingCoupon</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.model.ShoppingCoupon
 * @see com.liferay.portlet.shopping.service.model.ShoppingCouponModel
 * @see com.liferay.portlet.shopping.service.model.impl.ShoppingCouponImpl
 *
 */
public class ShoppingCouponModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ShoppingCoupon";
	public static final Object[][] TABLE_COLUMNS = {
			{ "couponId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "code_", new Integer(Types.VARCHAR) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "startDate", new Integer(Types.TIMESTAMP) },
			

			{ "endDate", new Integer(Types.TIMESTAMP) },
			

			{ "active_", new Integer(Types.BOOLEAN) },
			

			{ "limitCategories", new Integer(Types.VARCHAR) },
			

			{ "limitSkus", new Integer(Types.VARCHAR) },
			

			{ "minOrder", new Integer(Types.DOUBLE) },
			

			{ "discount", new Integer(Types.DOUBLE) },
			

			{ "discountType", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table ShoppingCoupon (couponId LONG not null primary key,groupId LONG,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,code_ VARCHAR(75) null,name VARCHAR(75) null,description STRING null,startDate DATE null,endDate DATE null,active_ BOOLEAN,limitCategories STRING null,limitSkus STRING null,minOrder DOUBLE,discount DOUBLE,discountType VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table ShoppingCoupon";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.shopping.model.ShoppingCoupon"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingCoupon"));

	public ShoppingCouponModelImpl() {
	}

	public long getPrimaryKey() {
		return _couponId;
	}

	public void setPrimaryKey(long pk) {
		setCouponId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_couponId);
	}

	public long getCouponId() {
		return _couponId;
	}

	public void setCouponId(long couponId) {
		if (couponId != _couponId) {
			_couponId = couponId;
		}
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		if (groupId != _groupId) {
			_groupId = groupId;
		}
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
		}
	}

	public String getUserName() {
		return GetterUtil.getString(_userName);
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			_userName = userName;
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
		}
	}

	public String getCode() {
		return GetterUtil.getString(_code);
	}

	public void setCode(String code) {
		if (((code == null) && (_code != null)) ||
				((code != null) && (_code == null)) ||
				((code != null) && (_code != null) && !code.equals(_code))) {
			_code = code;
		}
	}

	public String getName() {
		return GetterUtil.getString(_name);
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			_name = name;
		}
	}

	public String getDescription() {
		return GetterUtil.getString(_description);
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			_description = description;
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
		}
	}

	public String getLimitCategories() {
		return GetterUtil.getString(_limitCategories);
	}

	public void setLimitCategories(String limitCategories) {
		if (((limitCategories == null) && (_limitCategories != null)) ||
				((limitCategories != null) && (_limitCategories == null)) ||
				((limitCategories != null) && (_limitCategories != null) &&
				!limitCategories.equals(_limitCategories))) {
			_limitCategories = limitCategories;
		}
	}

	public String getLimitSkus() {
		return GetterUtil.getString(_limitSkus);
	}

	public void setLimitSkus(String limitSkus) {
		if (((limitSkus == null) && (_limitSkus != null)) ||
				((limitSkus != null) && (_limitSkus == null)) ||
				((limitSkus != null) && (_limitSkus != null) &&
				!limitSkus.equals(_limitSkus))) {
			_limitSkus = limitSkus;
		}
	}

	public double getMinOrder() {
		return _minOrder;
	}

	public void setMinOrder(double minOrder) {
		if (minOrder != _minOrder) {
			_minOrder = minOrder;
		}
	}

	public double getDiscount() {
		return _discount;
	}

	public void setDiscount(double discount) {
		if (discount != _discount) {
			_discount = discount;
		}
	}

	public String getDiscountType() {
		return GetterUtil.getString(_discountType);
	}

	public void setDiscountType(String discountType) {
		if (((discountType == null) && (_discountType != null)) ||
				((discountType != null) && (_discountType == null)) ||
				((discountType != null) && (_discountType != null) &&
				!discountType.equals(_discountType))) {
			_discountType = discountType;
		}
	}

	public ShoppingCoupon toEscapedModel() {
		if (isEscapedModel()) {
			return (ShoppingCoupon)this;
		}
		else {
			ShoppingCoupon model = new ShoppingCouponImpl();

			model.setEscapedModel(true);

			model.setCouponId(getCouponId());
			model.setGroupId(getGroupId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setCode(Html.escape(getCode()));
			model.setName(Html.escape(getName()));
			model.setDescription(Html.escape(getDescription()));
			model.setStartDate(getStartDate());
			model.setEndDate(getEndDate());
			model.setActive(getActive());
			model.setLimitCategories(Html.escape(getLimitCategories()));
			model.setLimitSkus(Html.escape(getLimitSkus()));
			model.setMinOrder(getMinOrder());
			model.setDiscount(getDiscount());
			model.setDiscountType(Html.escape(getDiscountType()));

			model = (ShoppingCoupon)Proxy.newProxyInstance(ShoppingCoupon.class.getClassLoader(),
					new Class[] { ShoppingCoupon.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ShoppingCouponImpl clone = new ShoppingCouponImpl();

		clone.setCouponId(getCouponId());
		clone.setGroupId(getGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setCode(getCode());
		clone.setName(getName());
		clone.setDescription(getDescription());
		clone.setStartDate(getStartDate());
		clone.setEndDate(getEndDate());
		clone.setActive(getActive());
		clone.setLimitCategories(getLimitCategories());
		clone.setLimitSkus(getLimitSkus());
		clone.setMinOrder(getMinOrder());
		clone.setDiscount(getDiscount());
		clone.setDiscountType(getDiscountType());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingCouponImpl shoppingCoupon = (ShoppingCouponImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getCreateDate(),
				shoppingCoupon.getCreateDate());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingCouponImpl shoppingCoupon = null;

		try {
			shoppingCoupon = (ShoppingCouponImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = shoppingCoupon.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
	}

	private long _couponId;
	private long _groupId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _code;
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