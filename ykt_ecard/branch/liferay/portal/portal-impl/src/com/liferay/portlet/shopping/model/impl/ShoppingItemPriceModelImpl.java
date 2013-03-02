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
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.shopping.model.ShoppingItemPrice;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="ShoppingItemPriceModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ShoppingItemPrice</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.model.ShoppingItemPrice
 * @see com.liferay.portlet.shopping.service.model.ShoppingItemPriceModel
 * @see com.liferay.portlet.shopping.service.model.impl.ShoppingItemPriceImpl
 *
 */
public class ShoppingItemPriceModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ShoppingItemPrice";
	public static final Object[][] TABLE_COLUMNS = {
			{ "itemPriceId", new Integer(Types.BIGINT) },
			

			{ "itemId", new Integer(Types.BIGINT) },
			

			{ "minQuantity", new Integer(Types.INTEGER) },
			

			{ "maxQuantity", new Integer(Types.INTEGER) },
			

			{ "price", new Integer(Types.DOUBLE) },
			

			{ "discount", new Integer(Types.DOUBLE) },
			

			{ "taxable", new Integer(Types.BOOLEAN) },
			

			{ "shipping", new Integer(Types.DOUBLE) },
			

			{ "useShippingFormula", new Integer(Types.BOOLEAN) },
			

			{ "status", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table ShoppingItemPrice (itemPriceId LONG not null primary key,itemId LONG,minQuantity INTEGER,maxQuantity INTEGER,price DOUBLE,discount DOUBLE,taxable BOOLEAN,shipping DOUBLE,useShippingFormula BOOLEAN,status INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table ShoppingItemPrice";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.shopping.model.ShoppingItemPrice"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingItemPrice"));

	public ShoppingItemPriceModelImpl() {
	}

	public long getPrimaryKey() {
		return _itemPriceId;
	}

	public void setPrimaryKey(long pk) {
		setItemPriceId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_itemPriceId);
	}

	public long getItemPriceId() {
		return _itemPriceId;
	}

	public void setItemPriceId(long itemPriceId) {
		if (itemPriceId != _itemPriceId) {
			_itemPriceId = itemPriceId;
		}
	}

	public long getItemId() {
		return _itemId;
	}

	public void setItemId(long itemId) {
		if (itemId != _itemId) {
			_itemId = itemId;
		}
	}

	public int getMinQuantity() {
		return _minQuantity;
	}

	public void setMinQuantity(int minQuantity) {
		if (minQuantity != _minQuantity) {
			_minQuantity = minQuantity;
		}
	}

	public int getMaxQuantity() {
		return _maxQuantity;
	}

	public void setMaxQuantity(int maxQuantity) {
		if (maxQuantity != _maxQuantity) {
			_maxQuantity = maxQuantity;
		}
	}

	public double getPrice() {
		return _price;
	}

	public void setPrice(double price) {
		if (price != _price) {
			_price = price;
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

	public boolean getTaxable() {
		return _taxable;
	}

	public boolean isTaxable() {
		return _taxable;
	}

	public void setTaxable(boolean taxable) {
		if (taxable != _taxable) {
			_taxable = taxable;
		}
	}

	public double getShipping() {
		return _shipping;
	}

	public void setShipping(double shipping) {
		if (shipping != _shipping) {
			_shipping = shipping;
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
		}
	}

	public int getStatus() {
		return _status;
	}

	public void setStatus(int status) {
		if (status != _status) {
			_status = status;
		}
	}

	public ShoppingItemPrice toEscapedModel() {
		if (isEscapedModel()) {
			return (ShoppingItemPrice)this;
		}
		else {
			ShoppingItemPrice model = new ShoppingItemPriceImpl();

			model.setEscapedModel(true);

			model.setItemPriceId(getItemPriceId());
			model.setItemId(getItemId());
			model.setMinQuantity(getMinQuantity());
			model.setMaxQuantity(getMaxQuantity());
			model.setPrice(getPrice());
			model.setDiscount(getDiscount());
			model.setTaxable(getTaxable());
			model.setShipping(getShipping());
			model.setUseShippingFormula(getUseShippingFormula());
			model.setStatus(getStatus());

			model = (ShoppingItemPrice)Proxy.newProxyInstance(ShoppingItemPrice.class.getClassLoader(),
					new Class[] { ShoppingItemPrice.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ShoppingItemPriceImpl clone = new ShoppingItemPriceImpl();

		clone.setItemPriceId(getItemPriceId());
		clone.setItemId(getItemId());
		clone.setMinQuantity(getMinQuantity());
		clone.setMaxQuantity(getMaxQuantity());
		clone.setPrice(getPrice());
		clone.setDiscount(getDiscount());
		clone.setTaxable(getTaxable());
		clone.setShipping(getShipping());
		clone.setUseShippingFormula(getUseShippingFormula());
		clone.setStatus(getStatus());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingItemPriceImpl shoppingItemPrice = (ShoppingItemPriceImpl)obj;

		int value = 0;

		if (getItemId() < shoppingItemPrice.getItemId()) {
			value = -1;
		}
		else if (getItemId() > shoppingItemPrice.getItemId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		if (getItemPriceId() < shoppingItemPrice.getItemPriceId()) {
			value = -1;
		}
		else if (getItemPriceId() > shoppingItemPrice.getItemPriceId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingItemPriceImpl shoppingItemPrice = null;

		try {
			shoppingItemPrice = (ShoppingItemPriceImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = shoppingItemPrice.getPrimaryKey();

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

	private long _itemPriceId;
	private long _itemId;
	private int _minQuantity;
	private int _maxQuantity;
	private double _price;
	private double _discount;
	private boolean _taxable;
	private double _shipping;
	private boolean _useShippingFormula;
	private int _status;
}