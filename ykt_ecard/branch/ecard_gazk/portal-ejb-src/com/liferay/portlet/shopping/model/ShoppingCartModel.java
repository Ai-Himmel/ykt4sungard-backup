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
 * <a href="ShoppingCartModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.76 $
 *
 */
public class ShoppingCartModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.shopping.model.ShoppingCart"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.shopping.model.ShoppingCart"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCart"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_CARTID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCart.cartId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCart.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCart.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_ITEMIDS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCart.itemIds"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COUPONIDS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCart.couponIds"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingCartModel"));

	public ShoppingCartModel() {
	}

	public ShoppingCartModel(String cartId) {
		_cartId = cartId;
		setNew(true);
	}

	public ShoppingCartModel(String cartId, String companyId, String userId,
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

	public String getCartId() {
		return _cartId;
	}

	public void setCartId(String cartId) {
		if (((cartId == null) && (_cartId != null)) ||
				((cartId != null) && (_cartId == null)) ||
				((cartId != null) && (_cartId != null) &&
				!cartId.equals(_cartId))) {
			if (!XSS_ALLOW_CARTID) {
				cartId = Xss.strip(cartId);
			}

			_cartId = cartId;
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

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
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

	public String getItemIds() {
		return _itemIds;
	}

	public void setItemIds(String itemIds) {
		if (((itemIds == null) && (_itemIds != null)) ||
				((itemIds != null) && (_itemIds == null)) ||
				((itemIds != null) && (_itemIds != null) &&
				!itemIds.equals(_itemIds))) {
			if (!XSS_ALLOW_ITEMIDS) {
				itemIds = Xss.strip(itemIds);
			}

			_itemIds = itemIds;
			setModified(true);
		}
	}

	public String getCouponIds() {
		return _couponIds;
	}

	public void setCouponIds(String couponIds) {
		if (((couponIds == null) && (_couponIds != null)) ||
				((couponIds != null) && (_couponIds == null)) ||
				((couponIds != null) && (_couponIds != null) &&
				!couponIds.equals(_couponIds))) {
			if (!XSS_ALLOW_COUPONIDS) {
				couponIds = Xss.strip(couponIds);
			}

			_couponIds = couponIds;
			setModified(true);
		}
	}

	public int getAltShipping() {
		return _altShipping;
	}

	public void setAltShipping(int altShipping) {
		if (altShipping != _altShipping) {
			_altShipping = altShipping;
			setModified(true);
		}
	}

	public boolean getInsure() {
		return _insure;
	}

	public boolean isInsure() {
		return _insure;
	}

	public void setInsure(boolean insure) {
		if (insure != _insure) {
			_insure = insure;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ShoppingCart(getCartId(), getCompanyId(), getUserId(),
			getCreateDate(), getModifiedDate(), getItemIds(), getCouponIds(),
			getAltShipping(), getInsure());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingCart shoppingCart = (ShoppingCart)obj;
		String pk = shoppingCart.getPrimaryKey();

		return getPrimaryKey().compareTo(pk);
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingCart shoppingCart = null;

		try {
			shoppingCart = (ShoppingCart)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = shoppingCart.getPrimaryKey();

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