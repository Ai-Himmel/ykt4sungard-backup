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

/**
 * <a href="ShoppingItemPriceModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.16 $
 *
 */
public class ShoppingItemPriceModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.shopping.model.ShoppingItemPrice"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.shopping.model.ShoppingItemPrice"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItemPrice"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_ITEMPRICEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItemPrice.itemPriceId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_ITEMID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItemPrice.itemId"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingItemPriceModel"));

	public ShoppingItemPriceModel() {
	}

	public ShoppingItemPriceModel(String itemPriceId) {
		_itemPriceId = itemPriceId;
		setNew(true);
	}

	public ShoppingItemPriceModel(String itemPriceId, String itemId,
		int minQuantity, int maxQuantity, double price, double discount,
		boolean taxable, double shipping, boolean useShippingFormula, int status) {
		_itemPriceId = itemPriceId;
		_itemId = itemId;
		_minQuantity = minQuantity;
		_maxQuantity = maxQuantity;
		_price = price;
		_discount = discount;
		_taxable = taxable;
		_shipping = shipping;
		_useShippingFormula = useShippingFormula;
		_status = status;
	}

	public String getPrimaryKey() {
		return _itemPriceId;
	}

	public String getItemPriceId() {
		return _itemPriceId;
	}

	public void setItemPriceId(String itemPriceId) {
		if (((itemPriceId == null) && (_itemPriceId != null)) ||
				((itemPriceId != null) && (_itemPriceId == null)) ||
				((itemPriceId != null) && (_itemPriceId != null) &&
				!itemPriceId.equals(_itemPriceId))) {
			if (!XSS_ALLOW_ITEMPRICEID) {
				itemPriceId = Xss.strip(itemPriceId);
			}

			_itemPriceId = itemPriceId;
			setModified(true);
		}
	}

	public String getItemId() {
		return _itemId;
	}

	public void setItemId(String itemId) {
		if (((itemId == null) && (_itemId != null)) ||
				((itemId != null) && (_itemId == null)) ||
				((itemId != null) && (_itemId != null) &&
				!itemId.equals(_itemId))) {
			if (!XSS_ALLOW_ITEMID) {
				itemId = Xss.strip(itemId);
			}

			_itemId = itemId;
			setModified(true);
		}
	}

	public int getMinQuantity() {
		return _minQuantity;
	}

	public void setMinQuantity(int minQuantity) {
		if (minQuantity != _minQuantity) {
			_minQuantity = minQuantity;
			setModified(true);
		}
	}

	public int getMaxQuantity() {
		return _maxQuantity;
	}

	public void setMaxQuantity(int maxQuantity) {
		if (maxQuantity != _maxQuantity) {
			_maxQuantity = maxQuantity;
			setModified(true);
		}
	}

	public double getPrice() {
		return _price;
	}

	public void setPrice(double price) {
		if (price != _price) {
			_price = price;
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

	public boolean getTaxable() {
		return _taxable;
	}

	public boolean isTaxable() {
		return _taxable;
	}

	public void setTaxable(boolean taxable) {
		if (taxable != _taxable) {
			_taxable = taxable;
			setModified(true);
		}
	}

	public double getShipping() {
		return _shipping;
	}

	public void setShipping(double shipping) {
		if (shipping != _shipping) {
			_shipping = shipping;
			setModified(true);
		}
	}

	public boolean getUseShippingFormula() {
		return _useShippingFormula;
	}

	public boolean isUseShippingFormula() {
		return _useShippingFormula;
	}

	public void setUseShippingFormula(boolean useShippingFormula) {
		if (useShippingFormula != _useShippingFormula) {
			_useShippingFormula = useShippingFormula;
			setModified(true);
		}
	}

	public int getStatus() {
		return _status;
	}

	public void setStatus(int status) {
		if (status != _status) {
			_status = status;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ShoppingItemPrice(getItemPriceId(), getItemId(),
			getMinQuantity(), getMaxQuantity(), getPrice(), getDiscount(),
			getTaxable(), getShipping(), getUseShippingFormula(), getStatus());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingItemPrice shoppingItemPrice = (ShoppingItemPrice)obj;
		int value = 0;
		value = getItemId().compareTo(shoppingItemPrice.getItemId());

		if (value != 0) {
			return value;
		}

		value = getItemPriceId().compareTo(shoppingItemPrice.getItemPriceId());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingItemPrice shoppingItemPrice = null;

		try {
			shoppingItemPrice = (ShoppingItemPrice)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = shoppingItemPrice.getPrimaryKey();

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

	private String _itemPriceId;
	private String _itemId;
	private int _minQuantity;
	private int _maxQuantity;
	private double _price;
	private double _discount;
	private boolean _taxable;
	private double _shipping;
	private boolean _useShippingFormula;
	private int _status;
}