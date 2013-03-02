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

package com.liferay.portlet.shopping.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="ShoppingCouponSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.shopping.service.http.ShoppingCouponServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.http.ShoppingCouponServiceSoap
 *
 */
public class ShoppingCouponSoap implements Serializable {
	public static ShoppingCouponSoap toSoapModel(ShoppingCoupon model) {
		ShoppingCouponSoap soapModel = new ShoppingCouponSoap();

		soapModel.setCouponId(model.getCouponId());
		soapModel.setGroupId(model.getGroupId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setUserId(model.getUserId());
		soapModel.setUserName(model.getUserName());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setModifiedDate(model.getModifiedDate());
		soapModel.setCode(model.getCode());
		soapModel.setName(model.getName());
		soapModel.setDescription(model.getDescription());
		soapModel.setStartDate(model.getStartDate());
		soapModel.setEndDate(model.getEndDate());
		soapModel.setActive(model.getActive());
		soapModel.setLimitCategories(model.getLimitCategories());
		soapModel.setLimitSkus(model.getLimitSkus());
		soapModel.setMinOrder(model.getMinOrder());
		soapModel.setDiscount(model.getDiscount());
		soapModel.setDiscountType(model.getDiscountType());

		return soapModel;
	}

	public static ShoppingCouponSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			ShoppingCoupon model = (ShoppingCoupon)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (ShoppingCouponSoap[])soapModels.toArray(new ShoppingCouponSoap[0]);
	}

	public ShoppingCouponSoap() {
	}

	public long getPrimaryKey() {
		return _couponId;
	}

	public void setPrimaryKey(long pk) {
		setCouponId(pk);
	}

	public long getCouponId() {
		return _couponId;
	}

	public void setCouponId(long couponId) {
		_couponId = couponId;
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		_groupId = groupId;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		_userName = userName;
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	public String getCode() {
		return _code;
	}

	public void setCode(String code) {
		_code = code;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		_description = description;
	}

	public Date getStartDate() {
		return _startDate;
	}

	public void setStartDate(Date startDate) {
		_startDate = startDate;
	}

	public Date getEndDate() {
		return _endDate;
	}

	public void setEndDate(Date endDate) {
		_endDate = endDate;
	}

	public boolean getActive() {
		return _active;
	}

	public boolean isActive() {
		return _active;
	}

	public void setActive(boolean active) {
		_active = active;
	}

	public String getLimitCategories() {
		return _limitCategories;
	}

	public void setLimitCategories(String limitCategories) {
		_limitCategories = limitCategories;
	}

	public String getLimitSkus() {
		return _limitSkus;
	}

	public void setLimitSkus(String limitSkus) {
		_limitSkus = limitSkus;
	}

	public double getMinOrder() {
		return _minOrder;
	}

	public void setMinOrder(double minOrder) {
		_minOrder = minOrder;
	}

	public double getDiscount() {
		return _discount;
	}

	public void setDiscount(double discount) {
		_discount = discount;
	}

	public String getDiscountType() {
		return _discountType;
	}

	public void setDiscountType(String discountType) {
		_discountType = discountType;
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