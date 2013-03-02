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
 * <a href="ShoppingCartHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCartHBM {
	protected ShoppingCartHBM() {
	}

	protected ShoppingCartHBM(String cartId) {
		_cartId = cartId;
	}

	protected ShoppingCartHBM(String cartId, String companyId, String userId,
		Date createDate, Date modifiedDate, String itemIds, String couponIds,
		int altShipping, boolean insure) {
		_cartId = cartId;
		_companyId = companyId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_itemIds = itemIds;
		_couponIds = couponIds;
		_altShipping = altShipping;
		_insure = insure;
	}

	public String getPrimaryKey() {
		return _cartId;
	}

	protected void setPrimaryKey(String pk) {
		_cartId = pk;
	}

	protected String getCartId() {
		return _cartId;
	}

	protected void setCartId(String cartId) {
		_cartId = cartId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
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

	protected String getItemIds() {
		return _itemIds;
	}

	protected void setItemIds(String itemIds) {
		_itemIds = itemIds;
	}

	protected String getCouponIds() {
		return _couponIds;
	}

	protected void setCouponIds(String couponIds) {
		_couponIds = couponIds;
	}

	protected int getAltShipping() {
		return _altShipping;
	}

	protected void setAltShipping(int altShipping) {
		_altShipping = altShipping;
	}

	protected boolean getInsure() {
		return _insure;
	}

	protected void setInsure(boolean insure) {
		_insure = insure;
	}

	private String _cartId;
	private String _companyId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _itemIds;
	private String _couponIds;
	private int _altShipping;
	private boolean _insure;
}