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

package com.liferay.portlet.shopping.service.persistence;

import java.util.Date;

/**
 * <a href="ShoppingCouponHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCouponHBM {
	protected ShoppingCouponHBM() {
	}

	protected ShoppingCouponHBM(String couponId) {
		_couponId = couponId;
	}

	protected ShoppingCouponHBM(String couponId, String companyId,
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

	protected void setPrimaryKey(String pk) {
		_couponId = pk;
	}

	protected String getCouponId() {
		return _couponId;
	}

	protected void setCouponId(String couponId) {
		_couponId = couponId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	protected Date getModifiedDate() {
		return _modifiedDate;
	}

	protected void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected String getDescription() {
		return _description;
	}

	protected void setDescription(String description) {
		_description = description;
	}

	protected Date getStartDate() {
		return _startDate;
	}

	protected void setStartDate(Date startDate) {
		_startDate = startDate;
	}

	protected Date getEndDate() {
		return _endDate;
	}

	protected void setEndDate(Date endDate) {
		_endDate = endDate;
	}

	protected boolean getActive() {
		return _active;
	}

	protected void setActive(boolean active) {
		_active = active;
	}

	protected String getLimitCategories() {
		return _limitCategories;
	}

	protected void setLimitCategories(String limitCategories) {
		_limitCategories = limitCategories;
	}

	protected String getLimitSkus() {
		return _limitSkus;
	}

	protected void setLimitSkus(String limitSkus) {
		_limitSkus = limitSkus;
	}

	protected double getMinOrder() {
		return _minOrder;
	}

	protected void setMinOrder(double minOrder) {
		_minOrder = minOrder;
	}

	protected double getDiscount() {
		return _discount;
	}

	protected void setDiscount(double discount) {
		_discount = discount;
	}

	protected String getDiscountType() {
		return _discountType;
	}

	protected void setDiscountType(String discountType) {
		_discountType = discountType;
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